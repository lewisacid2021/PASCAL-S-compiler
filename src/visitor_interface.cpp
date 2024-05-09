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

void CompoundStatement::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void Statement::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void StatementList::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void IfStatement::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void ProcedureCall::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void AssignopStatement::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void ElsePart::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void LoopStatement::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void VariableList::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void Variable::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void IDVarPart::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void IDVarParts::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void Expression::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void SimpleExpression::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void ExpressionList::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void Term::accept(Visitor *visitor )
{
    visitor->visit(this );
}

void Factor::accept(Visitor *visitor )
{
    visitor->visit(this );
}

}

