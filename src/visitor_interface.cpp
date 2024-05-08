#include "ast.h"

namespace ast{

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
    
void ConstDeclaration::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void TypeNode::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void StringTypeNode::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void VarDeclaration::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void PeriodsNode::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void SubprogramDeclaration::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void SubprogramHead::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void ParamLists::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void ValueParam::accept(Visitor *visitor)
{
    visitor->visit(this);
}

}

