#include "ast.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sys/types.h>

using std::string;
using std::vector;

namespace ast {

void GenerationVisitor::visit(AST *AST, FILE *fs)
{
    AST->getRoot()->accept(this, fs);
}

void GenerationVisitor::visit(AstNode *astnode, FILE *fs)
{
    for (auto child : astnode->getCnodeList())
        child->accept(this, fs);
}

void GenerationVisitor::visit(LeafNode *leafnode, FILE *fs)
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

void GenerationVisitor::visit(IdList *idlist, FILE *fs)
{
    idlist->get(0)->accept(this, fs);
    if (idlist->GetGrammarType() == IdList::GrammarType::MULTIPLE_ID) {
        fprintf(fs, ", ");
        idlist->get(1)->accept(this, fs);
    }
}

void ConstDeclaration::print_type(FILE *fs)
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

void GenerationVisitor::visit(ConstDeclaration *constdeclaration, FILE *fs)
{
    if (constdeclaration->GetGrammarType() == ConstDeclaration::GrammarType::MULTIPLE_ID)
    {
        constdeclaration->get(0)->accept(this, fs);

        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->get(1)->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->get(2)->accept(this, fs);
        fprintf(fs, ";\n");
    } else
    {
        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->get(0)->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->get(1)->accept(this, fs);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(TypeNode *typenode, FILE *fs)
{
    switch (typenode->GetVarType()) {
        case TypeNode::VarType::RECORD_TYPE:
            fprintf(fs, "struct ");
        case TypeNode::VarType::ID_TYPE:
        case TypeNode::VarType::ARRAY_TYPE:
            fprintf(fs, "%s", typenode->get_type_name().c_str());
            break;
        case TypeNode::VarType::STRING_TYPE:
            typenode->get(0)->accept(this, fs);
            break;
    }
}

void GenerationVisitor::visit(StringTypeNode *stringtypenode, FILE *fs)
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

void GenerationVisitor::visit(VarDeclaration *vardeclaration, FILE *fs)
{
    //check if it is a array type
    auto type_node    = vardeclaration->get(-1)->DynamicCast<TypeNode>();
    auto grammar_type = vardeclaration->GetGrammarType();

    if (grammar_type == VarDeclaration::GrammarType::MULTIPLE_DECL)
        vardeclaration->get(0)->accept(this, fs);  //vardeclaration

    //type
    vardeclaration->get(-1)->accept(this, fs);
    fprintf(fs, " ");

    if (type_node->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto ArrayType = type_node->get(0)->DynamicCast<ArrayTypeNode>();

        auto id_list   = vardeclaration->get(-2)->getCnodeList();
        for (uint i = 0; i < id_list.size(); i++)
        {
            id_list[i]->accept(this, fs);
            ArrayType->get(0)->accept(this, fs);  //periods
            if (i != id_list.size() - 1)
                fprintf(fs, ",");
            else
                fprintf(fs, ";\n");
        }
    } else {
        //idlist
        vardeclaration->get(-2)->accept(this, fs);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(PeriodsNode *periodsnode, FILE *fs)
{
    for (auto &dm : periodsnode->get_dm())
    {
        fprintf(fs, "[%d]", dm.upbound - dm.lowbound + 1);
    }
}

void GenerationVisitor::visit(SubprogramDeclaration *subprogramdeclaration, FILE *fs)
{
    auto headnode = subprogramdeclaration->get(0)->DynamicCast<SubprogramHead>();
    bool isFunc   = (headnode->get_type() == SubprogramHead::SubprogramType::FUNCTION);

    string id;
    TypeNode *type;
    if (isFunc)  //判断是函数还是过程 过程类型为void 无返回值
    {
        id   = headnode->get_id();
        id   = "__" + id + "__";
        type = subprogramdeclaration->get(2)->DynamicCast<TypeNode>();
    }

    headnode->accept(this, fs);  //subprogramhead

    fprintf(fs, "{\n");

    if (isFunc)  //声明函数的返回值 pascal用函数名表示返回值 转换成C时需要额外声明一个变量
    {
        type->accept(this, fs);
        fprintf(fs, " %s;\n", id.c_str());
    }

    subprogramdeclaration->get(1)->accept(this, fs);

    if (isFunc)  //函数返回值
        fprintf(fs, "return %s;\n", id.c_str());

    fprintf(fs, "}\n");
}

void GenerationVisitor::visit(SubprogramHead *subprogramhead, FILE *fs)
{
    if (subprogramhead->get_type() == SubprogramHead::SubprogramType::PROCEDURE)
        fprintf(fs, "void ");
    else
    {
        subprogramhead->get(2)->accept(this, fs);  //type
        fprintf(fs, " ");
    };

    subprogramhead->get(0)->accept(this, fs);  //id

    fprintf(fs, "(");
    subprogramhead->get(1)->accept(this, fs);  //formal_param
    fprintf(fs, ")\n");
}

void GenerationVisitor::visit(ParamLists *paramlists, FILE *fs)
{
    auto child_list = paramlists->getCnodeList();
    size_t n        = child_list.size();
    for (size_t i = 0; i < n; i++)
    {
        child_list[i]->accept(this, fs);
        if (i < n - 1)
            fprintf(fs, ",");
    }
}

void GenerationVisitor::visit(ValueParam *valueparam, FILE *fs)
{
    auto id_list = valueparam->get(0)->DynamicCast<IdList>();
    auto type    = valueparam->get(1)->DynamicCast<TypeNode>();

    vector<LeafNode *> list = id_list->Lists();
    size_t n=list.size();
    for(size_t i=0;i<n;i++)
    {
        type->accept(this, fs);
        fprintf(fs, " %s",list[i]->id_ref().c_str());
        if(i<n-1)
            fprintf(fs, ",");
    }
}

void AST::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void AstNode::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void LeafNode::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void IdList::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
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

void ConstDeclaration::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void TypeNode::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ArrayTypeNode::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void StringTypeNode::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void VarDeclaration::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void SubprogramDeclaration::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void SubprogramHead::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ParamLists::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ValueParam::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

}  // namespace ast