#include "ast.h"
#include "type.h"
#include <cstdio>
#include <iostream>

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
    idlist->getCnodeList()[0]->accept(this, fs);
    if (idlist->GetGrammarType() == IdList::GrammarType::MULTIPLE_ID) {
        fprintf(fs, ", ");
        idlist->getCnodeList()[1]->accept(this, fs);
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
        constdeclaration->getCnodeList()[0]->accept(this, fs);

        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->getCnodeList()[1]->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->getCnodeList()[2]->accept(this, fs);
        fprintf(fs, ";\n");
    } else
    {
        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->getCnodeList()[0]->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->getCnodeList()[1]->accept(this, fs);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(TypeNode *typenode, FILE *fs)
{
    switch (typenode->GetVarType()) {
        case TypeNode::VarType::BASIC_TYPE:
            {
                
                break;
            }
        case TypeNode::VarType::ARRAY_TYPE:
        case TypeNode::VarType::STRING_TYPE:  
            typenode->getCnodeList()[0]->accept(this, fs);
            break;
        case TypeNode::VarType::RECORD_TYPE:
            fprintf(fs, "struct {\n");
            typenode->getCnodeList()[0]->accept(this, fs);
            fprintf(fs, "}");
            break;
    }
}

void GenerationVisitor::visit(ArrayTypeNode *arraytypenode, FILE *fs)
{
    switch (arraytypenode->type()->type()) {
        case BasicType::BASIC_TYPE::INTEGER:
            fprintf(fs, "int");
            break;
        case BasicType::BASIC_TYPE::REAL:
            fprintf(fs, "float");
            break;
        case BasicType::BASIC_TYPE::BOOLEAN:
            fprintf(fs, "bool");
            break;
        case BasicType::BASIC_TYPE::CHAR:
            fprintf(fs, "char");
            break;
        default:
            break;
    }
    arraytypenode->getCnodeList()[0]->accept(this, fs);
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
    auto type = vardeclaration->GetGrammarType();
    if (type == VarDeclaration::GrammarType::MULTIPLE_DECL)
    {
        vardeclaration->getCnodeList()[0]->accept(this, fs);
        fprintf(fs, " ");
        vardeclaration->getCnodeList()[1]->accept(this, fs);
        fprintf(fs, ";\n");
    } else
    {
        vardeclaration->getCnodeList()[0]->accept(this, fs);
        fprintf(fs, " ");
        vardeclaration->getCnodeList()[1]->accept(this, fs);
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