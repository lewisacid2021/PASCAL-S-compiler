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
    switch(leafnode->get_type()) {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "%d", leafnode->get_value<int>());  
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "%f", leafnode->get_value<float>()); 
            break;
        case ConstValue::ConstvalueType::BOOLEAN:
            fprintf(fs, "%s", leafnode->get_value<bool>()?"true":"false");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "%c", leafnode->get_value<char>());
            break;
        case ConstValue::ConstvalueType::STRING:
            fprintf(fs, "\"%s\"", leafnode->get_value<string>().c_str());
            break;
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
    switch(type)
    {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "int");
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "float");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "char");
            break;
        case ConstValue::ConstvalueType::STRING:
            fprintf(fs, "string");
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(ConstDeclaration *constdeclaration, FILE *fs)
{
    auto type=constdeclaration->GetGrammarType();
    if (type == ConstDeclaration::GrammarType::MULTIPLE_ID)
    {
        constdeclaration->getCnodeList()[0]->accept(this, fs);
        
        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->getCnodeList()[1]->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->getCnodeList()[2]->accept(this, fs);
        fprintf(fs, ";\n");
    } 
    else if (type == ConstDeclaration::GrammarType::SINGLE_ID)
     {
        fprintf(fs, "const ");
        constdeclaration->print_type(fs);
        constdeclaration->getCnodeList()[0]->accept(this, fs);
        fprintf(fs, " = ");
        constdeclaration->getCnodeList()[1]->accept(this, fs);
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



}  // namespace ast