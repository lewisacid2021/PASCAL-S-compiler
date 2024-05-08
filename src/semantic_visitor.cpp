#include "ast.h"
#include "symbolTable.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sys/types.h>

using std::string;
using std::vector;

extern SymbolTable* MainTable;

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


void SemanticVisitor::visit(ConstDeclaration *constdeclaration)
{

}

void SemanticVisitor::visit(SubprogramHead *subprogramhead)
{
    auto type = subprogramhead->get_type();
    int amount = 0;
    auto formal_param = subprogramhead->get(1)->DynamicCast<FormalParam>();
    SymbolTable* subTable = new SymbolTable();

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
                    subTable->addVarPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
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
                    subTable->addPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    amount++;
                }
            }
            
        }
    }

    if(type == SubprogramHead::SubprogramType::PROC)
    {
        MainTable->addProcedure(subprogramhead->get_id(), subprogramhead->get_rownum(), amount, subTable);
    }
    else
    {
        auto ret_type = subprogramhead->get(2)->DynamicCast<TypeNode>()->get_type_name();
        MainTable->addFunction(subprogramhead->get_id(), subprogramhead->get_rownum(),ret_type, amount, subTable);
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

}