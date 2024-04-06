#include "ast.h"
#include <iostream>

using std::string;
using std::vector;

namespace ast {
void GenerationVisitor::visit(LeafNode &leafnode, FILE *fs)
{
    switch(leafnode.value()) {
        case BasicType::BASIC_TYPE::INTEGER:
            fprintf(fs, "%d", value_.get<int>());
            break;
        case BasicType::BASIC_TYPE::REAL:
            fprintf(fs, "%.2f", value_.get<float>());
            break;
        case BasicType::BASIC_TYPE::BOOLEAN:
            fprintf(fs, "%d", value_.get<bool>());
            break;
        case BasicType::BASIC_TYPE::CHAR:
            fprintf(fs, "'%c'", value_.get<char>());
            break;
        case BasicType::BASIC_TYPE::STRING:
            fprintf(fs, "%s", value_.get<string>().c_str());
            break;
        default:
            break;
    }
}
void GenerationVisitor::visit(astnode &astnode, FILE *fs)
{
    for (auto child : astnode.getCnodeList())
        visit(*child, fs);
}
void GenerationVisitor::visit(AST &AST, FILE *fs)
{
    std::cout << "Visiting AST\n";
    visit(*(AST.getRoot()), fs);
}
void AST::accept(Visitor &visitor, FILE *fs)
{
    visitor.visit(*this, fs);
}



}  // namespace ast