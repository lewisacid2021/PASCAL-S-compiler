#include "ast.h"

namespace ast{
    
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

