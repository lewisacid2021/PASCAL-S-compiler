#include "ast.h"
#include "symbolTable.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <tuple>
#include <utility>

using std::string;
using std::vector;

extern SymbolTable* MainTable;
SymbolTable* CurrentTable = MainTable;

namespace ast{
void SemanticVisitor::visit(AST *AST)
{
    AST->getRoot()->accept(this);
}

void SemanticVisitor::visit(AstNode *astnode)
{
    for (auto child : astnode->getCnodeList())
        child->accept(this);
}

void SemanticVisitor::visit(ProgramHead *programhead)
{
    string id = programhead->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    int rn = programhead->get(0)->DynamicCast<LeafNode>()->get_rownum();
    if(programhead->getCnodeList().size() == 1)
    {
        int amount = 0;
        MainTable->addProgramName(id, rn, "program", amount, "");
    }
    else
    {
        auto idlist = programhead->get(1)->DynamicCast<IdList>()->Lists();
        int amount = idlist.size();
        CurrentTable->addProgramName(id, rn, "program", amount, "");
        for (auto p : idlist)
        {
            string para_id = p->get_value<string>();
            int para_rn = p->get_rownum();
            MainTable->addVoidPara(para_id, para_rn);
        }
    }

    MainTable->addProcedure("read", -1, -1, NULL);
    //添加write过程，该过程变参
    MainTable->addProcedure("write", -1, -1, NULL);
    //添加writeln过程，该过程变参
    MainTable->addProcedure("writeln", -1, -1, NULL);
    //添加exit过程，该过程的参数个数需要分情况讨论，程序里会有特判，这里指定为0没有特殊含义
    MainTable->addProcedure("exit", -1, 0, NULL);
}

void SemanticVisitor::visit(ConstDeclaration *constdeclaration)
{
    auto lists = constdeclaration->Lists();
    for(auto p:lists)
    {
        string id = std::get<1>(p);
        int rn = std::get<0>(p);
        string type;
        string value;
        ConstValue * const_value = std::get<2>(p);
        ConstValue::ConstvalueType const_value_type = const_value->type();
        bool isMinus = const_value->get_uminus();

        switch(const_value_type){
            case ConstValue::ConstvalueType::INTEGER:
                type = "integer";
                value = std::to_string(const_value->get<int>());
                break;
            case ConstValue::ConstvalueType::REAL:
                type = "real";
                value = std::to_string(const_value->get<float>());
                break;
            case ConstValue::ConstvalueType::BOOLEAN:
                type = "boolean";
                if(const_value->get<bool>() == true)
                    value = "true";
                else
                    value = "false";
                break;
            case ConstValue::ConstvalueType::CHAR:
                type = "char";
                value.push_back(const_value->get<char>());
                break;
            case ConstValue::ConstvalueType::STRING:
                type = "string";
                value = const_value->get<string>();
                break;
        }

        CurrentTable->addConst(id, rn, type, isMinus, value);
    }
}

void SemanticVisitor::visit(RecordDeclaration *recorddeclaration)
{
    recorddeclaration->get(0)->accept(this);

    string id = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_value<string>();
    int rn = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_rownum();

    SymbolTable *subTable = new SymbolTable();

    CurrentTable->addRecord(id, rn, subTable);

    SymbolTable *PreviousTable = CurrentTable;
    CurrentTable               = subTable;

    recorddeclaration->get(2)->accept(this);

    CurrentTable = PreviousTable;
}

void SemanticVisitor::visit(VarDeclaration *vardeclaration)
{
    IdList* idlist;
    TypeNode* typenode; 

    if(vardeclaration->GetGrammarType() == VarDeclaration::GrammarType::SINGLE_DECL)
    {
        idlist = vardeclaration->get(0)->DynamicCast<IdList>();
        typenode = vardeclaration->get(1)->DynamicCast<TypeNode>();
    }
    else
    {
        idlist = vardeclaration->get(1)->DynamicCast<IdList>();
        typenode = vardeclaration->get(2)->DynamicCast<TypeNode>();
        vardeclaration->get(0)->accept(this);
    }

    if(typenode->GetVarType() == TypeNode::VarType::ID_TYPE)
    {
        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            string type = typenode->get_type_name();
            CurrentTable->addVar(id, rn, type);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto array_type = typenode->get(0)->DynamicCast<ArrayTypeNode>();
        auto info = array_type->info();
        string type = array_type->type();
        int amount = info->GetDimsum();
        vector<pair<int,int>> bound;

        for(auto j:info->GetDimensions())
        {
            bound.push_back(make_pair(j.lowbound, j.upbound));
        }

        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addArray(id, rn, type, amount, bound);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::STRING_TYPE)
    {
        auto string_type = typenode->get(0)->DynamicCast<StringTypeNode>();
        auto string_info = string_type->type();
        string type = "STRING";
        int amount = string_info->GetLen();

        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addString(id, rn, type, amount);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::RECORD_TYPE)
    {
        SymbolTable * subTable = new SymbolTable();
        
        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addRecord(id, rn, subTable);
        }

        SymbolTable* PreviousTable = CurrentTable;
        CurrentTable = subTable;

        typenode->get(0)->accept(this);

        CurrentTable = PreviousTable;
    }

    
}

void SemanticVisitor::visit(SubprogramDeclaration *subprogramdeclaration)
{
    SymbolTable *subTable = new SymbolTable();
    CurrentTable          = subTable;
    subprogramdeclaration->get(0)->DynamicCast<SubprogramHead>()->accept(this);
    subprogramdeclaration->get(1)->DynamicCast<SubprogramBody>()->accept(this);
    CurrentTable = MainTable;

}

void SemanticVisitor::visit(SubprogramHead *subprogramhead)
{
    auto type = subprogramhead->get_type();
    string id = subprogramhead->get_id();
    int amount = 0;
    auto formal_param = subprogramhead->get(1)->DynamicCast<FormalParam>();

    if(formal_param->getCnodeList().size() != 0)
    {
        auto list = formal_param->get(0)->DynamicCast<ParamLists>()->Lists();
        for(auto p:list)
        {
            auto ptype = p->get_type();
            std::vector<LeafNode*> idlist;
            TypeNode* idtype;
            if(ptype == ParamList::ParamType::VarParam)
            {
                idlist = p->get(0)->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(0)->get(1)->DynamicCast<TypeNode>();
                for(auto id:idlist)
                {
                    CurrentTable->addVarPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    id->set_ref(true);
                    amount++;
                }
            }
            else
            {
                idlist = p->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(1)->DynamicCast<TypeNode>();
                for(auto id:idlist)
                {
                    CurrentTable->addPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    amount++;
                }
            }
            
        }
    }

    if(type == SubprogramHead::SubprogramType::PROC)
    {
        MainTable->addProcedure(subprogramhead->get_id(), subprogramhead->get_rownum(), amount, subTable);
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", amount, "");
    }
    else
    {
        auto ret_type = subprogramhead->get(2)->DynamicCast<TypeNode>()->get_type_name();
        MainTable->addFunction(subprogramhead->get_id(), subprogramhead->get_rownum(),ret_type, amount, subTable);
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", amount, ret_type);
    }
}

std::vector<ParamList *> ParamLists::Lists()
{
    std::vector<ParamList *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_PARAM_LIST) //如果多层 进入循环
    {
        ParamList *ln = cur_node->cnode_list[1]->DynamicCast<ParamList>();
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<ParamLists>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    ParamList *ln = (*cur_node->cnode_list.rbegin())->DynamicCast<ParamList>();
    lists.insert(lists.begin(), ln);
    return lists;
}

std::vector<tuple<int,string,ConstValue *>> ConstDeclaration::Lists()
{
    std::vector<tuple<int,string,ConstValue *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_ID) //如果多层 进入循环
    {
        int rn = cur_node->get_rownum();
        auto id = cur_node->get(1)->DynamicCast<LeafNode>()->get_value<string>();
        auto const_value = cur_node->get(2)->DynamicCast<LeafNode>()->getConstValue();
        tuple<int,string,ConstValue *> ln = make_tuple(rn,id,const_value);
        
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<ConstDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    int rn = cur_node->get_rownum();
    auto id = cur_node->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    auto const_value = cur_node->get(1)->DynamicCast<LeafNode>()->getConstValue();
    tuple<int,string,ConstValue *> ln = make_tuple(rn,id,const_value);
        
    lists.insert(lists.begin(), ln);

    return lists;
}

std::vector<tuple<vector<LeafNode *>,AstNode *>> VarDeclaration::Lists()
{
    std::vector<tuple<vector<LeafNode *>,AstNode *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_DECL) //如果多层 进入循环
    {
        auto idlist = cur_node->get(1)->DynamicCast<IdList>()->Lists();
        auto node = cur_node->get(2);
        tuple<vector<LeafNode *>,AstNode *> ln = make_tuple(idlist,node);
        
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<VarDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    auto idlist = cur_node->get(1)->DynamicCast<IdList>()->Lists();
        auto node = cur_node->get(2);
        tuple<vector<LeafNode *>,AstNode *> ln = make_tuple(idlist,node);
        
        lists.insert(lists.begin(), ln);

    return lists;

}

}