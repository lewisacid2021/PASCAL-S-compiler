#include "ast.h"
#include "type.h"
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
            fprintf(fs,"%s", typenode->get_type_name().c_str());
            break;
        case TypeNode::VarType::STRING_TYPE:  
            typenode->get(0)->accept(this, fs);
            break;
    }
}

void GenerationVisitor::visit(StringTypeNode *stringtypenode, FILE *fs)
{
    auto type=stringtypenode->type();
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
    auto type_node = vardeclaration->get(-1)->DynamicCast<TypeNode>();
    auto grammar_type = vardeclaration->GetGrammarType();

    if (grammar_type == VarDeclaration::GrammarType::MULTIPLE_DECL)
        vardeclaration->get(0)->accept(this, fs);

    //type
    vardeclaration->get(-1)->accept(this, fs);
    fprintf(fs, " ");

    if(type_node->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
    
        auto ArrayType=type_node->get(0)->DynamicCast<ArrayTypeNode>();
        
        auto id_list=vardeclaration->get(-2)->getCnodeList();
        for(uint i=0;i<id_list.size();i++)
        {
            id_list[i]->accept(this, fs);
            ArrayType->get(0)->accept(this,fs);
            if(i!=id_list.size()-1)
                fprintf(fs, ",");
            else
                fprintf(fs, ";\n");
        }
    }
    else {
        //idlist
        vardeclaration->get(-2)->accept(this, fs);
        fprintf(fs, ";\n");   
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

}  // namespace ast