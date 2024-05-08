#include "ast.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sys/types.h>

extern FILE *fs;

using std::string;
using std::vector;

namespace ast {

void GenerationVisitor::visit(AST *AST)
{
    AST->getRoot()->accept(this);
}

void GenerationVisitor::visit(AstNode *astnode)
{
    for (auto child : astnode->getCnodeList())
        child->accept(this);
}

void GenerationVisitor::visit(LeafNode *leafnode)
{
    switch (leafnode->get_type()) {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "%d", leafnode->get_value<int>());
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "%f", leafnode->get_value<float>());
            break;
        case ConstValue::ConstvalueType::BOOLEAN:
            fprintf(fs, "%s", leafnode->get_value<bool>() ? "true" : "false");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "\'%c\'", leafnode->get_value<char>());
            break;
        case ConstValue::ConstvalueType::STRING:
        {
            if (leafnode->getLeafType() == LeafNode::LeafType::VALUE)
                fprintf(fs, "\"%s\"", leafnode->get_value<string>().c_str());
            else
                fprintf(fs, "%s", leafnode->get_value<string>().c_str());
            break;
        }
        default:
            break;
    }
}

void GenerationVisitor::visit(IdList *idlist)
{
    idlist->get(0)->accept(this);
    if (idlist->GetGrammarType() == IdList::GrammarType::MULTIPLE_ID) {
        fprintf(fs, ", ");
        idlist->get(1)->accept(this);
    }
}

void ConstDeclaration::print_type()
{
    switch (type)
    {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "int ");
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "float ");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "char ");
            break;
        case ConstValue::ConstvalueType::STRING:
            fprintf(fs, "string ");
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(ConstDeclaration *constdeclaration)
{
    if (constdeclaration->GetGrammarType() == ConstDeclaration::GrammarType::MULTIPLE_ID)
    {
        constdeclaration->get(0)->accept(this);

        fprintf(fs, "const ");
        constdeclaration->print_type();
        constdeclaration->get(1)->accept(this);
        fprintf(fs, " = ");
        constdeclaration->get(2)->accept(this);
        fprintf(fs, ";\n");
    } else
    {
        fprintf(fs, "const ");
        constdeclaration->print_type();
        constdeclaration->get(0)->accept(this);
        fprintf(fs, " = ");
        constdeclaration->get(1)->accept(this);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(TypeNode *typenode)
{
    switch (typenode->GetVarType()) {
        case TypeNode::VarType::RECORD_TYPE:
            fprintf(fs, "struct ");
        case TypeNode::VarType::ID_TYPE:
        case TypeNode::VarType::ARRAY_TYPE:
            fprintf(fs, "%s", typenode->get_type_name().c_str());
            break;
        case TypeNode::VarType::STRING_TYPE:
            typenode->get(0)->accept(this);
            break;
    }
}

void GenerationVisitor::visit(StringTypeNode *stringtypenode)
{
    auto type = stringtypenode->type();
    switch (type->GetGrammarType())
    {
        case StringType::GrammarType::LIMIT:
            fprintf(fs, "char[%d] ", type->GetLen());
            break;
        case StringType::GrammarType::NOLIMIT:
            fprintf(fs, "char[%d] ", MAX_STRING_LEN);
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(VarDeclaration *vardeclaration)
{
    //check if it is a array type
    auto type_node    = vardeclaration->get(-1)->DynamicCast<TypeNode>();
    auto grammar_type = vardeclaration->GetGrammarType();

    if (grammar_type == VarDeclaration::GrammarType::MULTIPLE_DECL)
        vardeclaration->get(0)->accept(this);  //vardeclaration

    //type
    vardeclaration->get(-1)->accept(this);
    fprintf(fs, " ");

    if (type_node->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto ArrayType = type_node->get(0)->DynamicCast<ArrayTypeNode>();

        auto id_list   = vardeclaration->get(-2)->getCnodeList();
        for (uint i = 0; i < id_list.size(); i++)
        {
            id_list[i]->accept(this);
            ArrayType->get(0)->accept(this);  //periods
            if (i != id_list.size() - 1)
                fprintf(fs, ",");
            else
                fprintf(fs, ";\n");
        }
    } else {
        //idlist
        vardeclaration->get(-2)->accept(this);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(PeriodsNode *periodsnode)
{
    for (auto &dm : periodsnode->get_dm())
    {
        fprintf(fs, "[%d]", dm.upbound - dm.lowbound + 1);
    }
}

void GenerationVisitor::visit(SubprogramDeclaration *subprogramdeclaration)
{
    auto headnode = subprogramdeclaration->get(0)->DynamicCast<SubprogramHead>();
    bool isFunc   = (headnode->get_type() == SubprogramHead::SubprogramType::FUNC);

    string id;
    TypeNode *type;
    if (isFunc)  //判断是函数还是过程 过程类型为void 无返回值
    {
        id   = headnode->get_id();
        id   = "__" + id + "__";
        type = subprogramdeclaration->get(2)->DynamicCast<TypeNode>();
    }

    headnode->accept(this);  //subprogramhead

    fprintf(fs, "{\n");

    if (isFunc)  //声明函数的返回值 pascal用函数名表示返回值 转换成C时需要额外声明一个变量
    {
        type->accept(this);
        fprintf(fs, " %s;\n", id.c_str());
    }

    subprogramdeclaration->get(1)->accept(this);

    if (isFunc)  //函数返回值
        fprintf(fs, "return %s;\n", id.c_str());

    fprintf(fs, "}\n");
}

void GenerationVisitor::visit(SubprogramHead *subprogramhead)
{
    if (subprogramhead->get_type() == SubprogramHead::SubprogramType::PROC)
        fprintf(fs, "void ");
    else
    {
        subprogramhead->get(2)->accept(this);  //type
        fprintf(fs, " ");
    };

    subprogramhead->get(0)->accept(this);  //id

    fprintf(fs, "(");
    subprogramhead->get(1)->accept(this);  //formal_param
    fprintf(fs, ")\n");
}

void GenerationVisitor::visit(ParamLists *paramlists)
{
    auto child_list = paramlists->getCnodeList();
    size_t n        = child_list.size();
    for (size_t i = 0; i < n; i++)
    {
        child_list[i]->accept(this);
        if (i < n - 1)
            fprintf(fs, ",");
    }
}

void GenerationVisitor::visit(ValueParam *valueparam)
{
    auto id_list = valueparam->get(0)->DynamicCast<IdList>();
    auto type    = valueparam->get(1)->DynamicCast<TypeNode>();

    vector<LeafNode *> list = id_list->Lists();
    size_t n=list.size();
    for(size_t i=0;i<n;i++)
    {
        type->accept(this);
        fprintf(fs, " %s",list[i]->id_ref().c_str());
        if(i<n-1)
            fprintf(fs, ",");
    }
}

void AST::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void AstNode::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void LeafNode::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void IdList::accept(Visitor *visitor)
{
    visitor->visit(this);
}

std::vector<LeafNode *> IdList::Lists()
{
    std::vector<LeafNode *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type_;

    while (gtype == GrammarType::MULTIPLE_ID) //如果多层 进入循环
    {
        LeafNode *ln = cur_node->cnode_list[1]->DynamicCast<LeafNode>();
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<IdList>();
        gtype    = cur_node->grammar_type_;
    }

    // 插入最后一个节点
    LeafNode *ln = (*cur_node->cnode_list.rbegin())->DynamicCast<LeafNode>();
    lists.insert(lists.begin(), ln);
    return lists;
}

}  // namespace ast