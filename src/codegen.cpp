#include "ast.h"
#include "type.h"
#include <cstdio>
#include <iostream>

using std::string;
using std::vector;

namespace ast {

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

void GenerationVisitor::visit(ConstDeclaration &constdeclaration, FILE *fs)
{
    auto type=constdeclaration.GetGrammarType();
    if (type == ConstDeclaration::GrammarType::MULTIPLE_ID)
    {
        visit(*(constdeclaration.getCnodeList()[0]), fs);
        
        fprintf(fs, "const ");
        constdeclaration.print_type(fs);
        visit(*(constdeclaration.getCnodeList()[1]), fs);
        fprintf(fs, " = ");
        visit(*(constdeclaration.getCnodeList()[2]), fs);
        fprintf(fs, ";\n");
    } 
    else if (type == ConstDeclaration::GrammarType::SINGLE_ID)
     {
        fprintf(fs, "const ");
        constdeclaration.print_type(fs);
        visit(*(constdeclaration.getCnodeList()[0]), fs);
        fprintf(fs, " = ");
        visit(*(constdeclaration.getCnodeList()[1]), fs);
        fprintf(fs, ";\n");
  }
}

void GenerationVisitor::visit(IdList &idlist, FILE *fs)
{
    visit(*(idlist.getCnodeList()[0]), fs);
    if (idlist.GetGrammarType() == IdList::GrammarType::MULTIPLE_ID) {
        fprintf(fs, ", ");
        visit(*(idlist.getCnodeList()[1]), fs);
  }
}

void GenerationVisitor::visit(LeafNode &leafnode, FILE *fs)  
{
    switch(leafnode.get_type()) {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "%d", leafnode.get_value<int>());  
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "%f", leafnode.get_value<float>()); 
            break;
        case ConstValue::ConstvalueType::BOOLEAN:
            fprintf(fs, "%s", leafnode.get_value<bool>()?"true":"false");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "%c", leafnode.get_value<char>());
            break;
        case ConstValue::ConstvalueType::STRING:
            fprintf(fs, "\"%s\"", leafnode.get_value<string>().c_str());
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(AstNode &astnode, FILE *fs)
{
    for (auto child : astnode.getCnodeList())
        visit(*child, fs);
}
void GenerationVisitor::visit(AST &AST, FILE *fs)
{
    visit(*(AST.getRoot()), fs);
}
void AST::accept(Visitor &visitor, FILE *fs)
{
    visitor.visit(*this, fs);
}



}  // namespace ast