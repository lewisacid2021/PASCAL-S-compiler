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

    void GenerationVisitor::visit(StatementList *statementList, FILE *fs)  
    {
         // 获取表达式节点列表
    std::vector<AstNode *> &statements = statementList->getCnodeList();
    
    size_t numChildren = statements.size(); 
    // 递归访问子节点
    for (size_t i = 0; i < numChildren; ++i)
    {
        // 访问当前子节点
        statementList->get(i)->accept(this, fs);

        // 如果不是最后一个语句节点，则输出分号
        if (i != numChildren - 1)
        {
            fprintf(fs, "; ");
        }
    }
    }
    
    void GenerationVisitor::visit(IfStatement *ifStatement, FILE *fs)  {
    fprintf(fs, "if (");
    visit(ifStatement->get(0), fs); // 访问 expression
    fprintf(fs, ")\n{\n");
    visit(ifStatement->get(1), fs); // 访问 then statement
    fprintf(fs, "}\n");

    visit(ifStatement->get(2), fs); // 访问 else_part
}
 
    void GenerationVisitor::visit(ElsePart *elseNode, FILE *fs)  
    {
        switch (elseNode->grammar_type_)
        {
        case ElsePart::ELSEType::EPSILON:
            return;
        case ElsePart::ELSEType::ELSE_STATEMENT:
            fprintf(fs, "else {\n");
            visit(ifStatement->get(0), fs); // 访问 expression
            fprintf(fs, "}\n");
        }
    } 

 void GenerationVisitor::visit(ProcedureCall *procedureCall, FILE *fs)  {
   fprintf(fs, "%s", procedureCall->get_id().c_str());
    // 根据调用类型决定是否输出参数列表
    if (procedureCall->procedure_type == ProcedureCall::ProcedureType::NO_LIST)
    {
        fprintf(fs, "();\n"); // 输出空参数列表
    }
    else if (procedureCall->procedure_type == ProcedureCall::ProcedureType::EXP_LIST)
    {
        fprintf(fs, "(");
        procedureCall->get(1)->accept(this, fs);//expressionlist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
    else if (procedureCall->procedure_type == ProcedureCall::ProcedureType::VAR_LIST)
    {
        fprintf(fs, "(");
        procedureCall->get(1)->accept(this, fs);//variablelist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
 }

void GenerationVisitor::visit(AssignopStatement *assignopStatement, FILE *fs)  
    {
        auto assignment_node = dynamic_cast<AssignmentNode *>(statement->get(0));
        auto exp = assignment_node->get(1)->DynamicCast<ExpressionNode>();
        // 根据左侧类型决定生成的代码逻辑
        switch (assignopStatement->left_type)
        {
        case AssignopStatement::LEFTTYPE::VARIABLE:
        case AssignopStatement::LEFTTYPE::FUNC:
        {
            // 生成函数调用的代码
            assignopStatement->get(0)->accept(this, fs);

            // 输出赋值操作符
            fprintf(fs, " = ");

            // 生成右侧表达式的代码
            assignopStatement->get(1)->accept(this, fs);

            // 输出分号以结束语句
            fprintf(fs, ";\n");
            break;
        }
        default:
            // 其他情况下，什么也不做
            break;
        }
    }

void GenerationVisitor::visit(LoopStatement *loopStatement, FILE *fs)  
    {
          switch (loopStatement->loop_type)
        {
        case LoopStatement::LoopType::FORUP:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id->accept(this, fs);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)->accept(this, fs);//expression
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, " <= ");
            loopStatement->get(2)->accept(this, fs);//中间的expression
            fprintf(fs, "; ");
            
            id->accept(this, fs);
            fprintf(fs, "++) {\n");
            loopStatement->get(3)->accept(this, fs);//statement
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::FORDOWN:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id->accept(this, fs);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, " >= ");
            loopStatement->get(2)->accept(this, fs);
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, "--) {\n");
            loopStatement->get(3)->accept(this, fs);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::WHILE:
        {
            fprintf(fs, "while (");
            loopStatement->get(0)->accept(this, fs);
            fprintf(fs, ") {\n");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::REAPT:
        {
            fprintf(fs, "do {\n");
            loopStatement->get(0)->accept(this, fs);
            fprintf(fs, "} while (!(");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "));\n");
            break;
        }
        }
    }


void GenerationVisitor::visit(Variable *variable, FILE *fs)  {
    // 访问第一个子节点
    variable->get(0)->accept(this, fs);
    // 访问第二个子节点
    variable->get(1)->accept(this, fs);
}

void GenerationVisitor::visit(VariableList *variableList, FILE *fs)   {
    
    std::vector<AstNode *> &children = variableList->getCnodeList();
    
    // 处理单个表达式节点
    if (variableList->grammar_type() ==  VariableList::GrammarType::VAR_)
    {
        variableList->get(0)->accept(this, fs);
    }
    // 处理多个表达式节点
    else if (variableList->grammar_type() == VariableList::GrammarType::VAR_LIST_VAR)
    {
        size_t numChildren=children.size();
        // 遍历子节点列表并逐个访问
        for (size_t i = 0; i < numChildren; ++i) {
            children[i]->accept(this, fs);

            // 如果不是最后一个节点，则输出逗号
            if (variableList->grammar_type() == VariableList::GrammarType:: VAR_LIST_VAR && i != numChildren - 1) {
                fprintf(fs, ", ");
            }
        }
    }
}
void GenerationVisitor::visit(IDVarPart *idVarPart, FILE *fs)  
    {
    if (grammar_type_ == GrammarType::_ID)
      {
        fprintf(fs, ".");
        visit(switchStatement->get(0), fs); // 访问 id
      }
      else if (grammar_type_ == GrammarType::EXP_LIST)
      {
        fprintf(fs, "[");
       visit(switchStatement->get(0), fs); // 访问 expression_list
        if (array_lb_ > 0)
          PRINT(" - %d", array_lb_)
        else if (array_lb_ < 0)
          PRINT(" + %d", -array_lb_)
        fprintf(fs, "]");
      }
    }
void GenerationVisitor::visit(IDVarParts *idVarParts, FILE *fs)   {
    // 获取子节点列表
    std::vector<AstNode *> &children = idVarParts->getCnodeList();

    // 遍历子节点列表并逐个访问
    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->accept(this, fs);

        // 如果不是最后一个节点，则输出空格
        if (i != children.size() - 1) {
            fprintf(fs, " ");
        }
    }
}

 void GenerationVisitor::visit(Term *term, FILE *fs)  
{
    if (term->GetSymType() == Term::SymbolType::SINGLE)
    {
        // term -> factor 的情况
        term->get(0)->accept(this, fs); // 访问 factor 节点
    }
    else
    {
        // term -> term MULOP factor 的情况
        term->get(0)->accept(this, fs); // 访问左侧 term 节点
      
        // 根据乘法操作符类型输出相应的符号
        switch (term->GetSymType())
        {
        case Term::SymbolType::MULTIPLY:
            fprintf(fs, " * ");
            break;
        case Term::SymbolType::DIVIDE:
            fprintf(fs, " / ");
            break;
        case Term::SymbolType::MOD:
            fprintf(fs, " % ");
            break;
        case Term::SymbolType::AND:
            fprintf(fs, " && ");
            break;
        case Term::SymbolType::SINGLE:
            break;
        }
        term->get(2)->accept(this, fs); // 访问右侧 factor 节点
    }
}

    void GenerationVisitor::visit(Factor *factor, FILE *fs)  
    {
        switch (factor->get_factor_type())
        {
        case Factor::FactorType::NUM:
        case Factor::FactorType::VARIABLE:
            factor->get(0)->accept(this, fs);
            break;
        case Factor::FactorType::EXP:
            fprintf(fs, "(");
            factor->get(0)->accept(this, fs);
            fprintf(fs, ")");
            break;
        case Factor::FactorType::ID_EXP_LIST:
            factor->get(0)->accept(this, fs);
            fprintf(fs, "(");
            factor->get(1)->accept(this, fs);
            fprintf(fs, ")");
            break;
        case Factor::FactorType::NOT_:
            fprintf(fs, "!");
            factor->get(0)->accept(this, fs);
            break;
        case Factor::FactorType::UMINUS_:
            fprintf(fs, "-");
            factor->get(0)->accept(this, fs); // 访问因子节点
            break;
        case Factor::FactorType::CHAR_:
            fprintf(fs, "'");
            factor->get(0)->accept(this, fs); // 'letter'
            fprintf(fs, "'");
            break;
        case Factor::FactorType::STR:
        case Factor::FactorType::BOOL:
            factor->get(0)->accept(this, fs);
            break;
        default:
            break;
        }
    }

<<<<<<< HEAD:src/visitor.cpp
void ConstDeclaration::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void TypeNode::accept(Visitor *visitor, FILE *fs)
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

void PeriodsNode::accept(Visitor *visitor, FILE *fs)
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

void GenerationVisitor::visit(Expression *expression, FILE *fs)  {
    if (expression->GetGraType() == SimpleExpression::GrammarType::SINGLE)
    {
        // expression -> simple_expression 的情况
        expression->get(0)->accept(this, fs); // 访问 term 节点
    }
    if (expression->GetGraType() == SimpleExpression::GrammarType::DOUBLE)
    {
        // expression -> expression relop simple_expression 的情况
        expression->get(0)->accept(this, fs); // 访问左侧 expression 节点
        if(expression->GetSymType()==Expression::SymbolType::PLUS_) fprintf(fs, "+ ");
        if(expression->GetSymType()==Expression::SymbolType::MINUS_) fprintf(fs, "- ");
        if(expression->GetSymType()==Expression::SymbolType::OR_) fprintf(fs, "or ");

        expression->get(1)->accept(this, fs); // 访问右侧 simple_expression 节点
    
    }
}

void GenerationVisitor::visit(SimpleExpression *simpleExpression, FILE *fs)  {
    if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::SINGLE)
    {
        // simple_expression -> term 的情况
        simpleExpression->get(0)->accept(this, fs); // 访问 term 节点
    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::PLUS_)
    {
        // simple_expression -> + term 的情况
        fprintf(fs, "+ ");
        simpleExpression->get(0)->accept(this, fs); // 访问 term 节点
    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::MINUS_)
    {
        // simple_expression -> - term 的情况
        fprintf(fs, "- ");
        simpleExpression->get(0)->accept(this, fs); // 访问 term 节点
    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::OR_)
    {
        // simple_expression -> simple_expression or term 的情况
        simpleExpression->get(0)->accept(this, fs); // 访问左侧 simple_expression 节点
        fprintf(fs, " or ");
        simpleExpression->get(1)->accept(this, fs); // 访问右侧 term 节点
    }
   }

    void GenerationVisitor::visit(ExpressionList *expressionList, FILE *fs)  {
    // 获取表达式列表类型
    ExpressionList::ExpressionType type = expressionList->expression_type;

    // 获取表达式节点列表
    std::vector<AstNode *> &expressions = expressionList->getCnodeList();
    
    // 处理单个表达式节点
    if (type == ExpressionList::ExpressionType::SINGLE)
    {
        expressions[0]->accept(this, fs);
    }
    // 处理多个表达式节点
    else if (type == ExpressionList::ExpressionType::MULTIPLE)
    {
        size_t numExpressions = expressions.size(); // 获取表达式列表的大小
    
        for (size_t i = 0; i < numExpressions; ++i)
        {
            expressions[i]->accept(this, fs);
            // 如果不是最后一个表达式，则输出逗号分隔符
            if (i != numExpressions - 1)
            {
                fprintf(fs, ", ");
            }
        }
    }
}
    void GenerationVisitor::visit(Statement *statement, FILE *fs)  
    {
        switch (statement->statement_type)
        {
        case Statement::StatementType::EPSILON:
            return;
        case Statement::StatementType::ASSIGN_OP_STATEMENT:
        case Statement::StatementType::PROCEDURE_CALL:
        case Statement::StatementType::COMPOUND_STATEMENT:
        case Statement::StatementType::IF_STATEMENT:
            visit(statement->get(0), fs);
            break;

        // case Statement::StatementType::READ_STATEMENT:
        // case Statement::StatementType::READLN_STATEMENT:
        //     break;
        // case Statement::StatementType::WRITE_STATEMENT:
        // case Statement::StatementType::WRITELN_STATEMENT:
        //     break;
        }
    }

    void GenerationVisitor::visit(CompoundStatement *compoundStatement, FILE *fs)  {
    fprintf(fs, "{\n");
    visit(compoundStatement->get(0), fs); // 访问  StatementList
    fprintf(fs, "}\n");
}

    void GenerationVisitor::visit(StatementList *statementList, FILE *fs)  
    {
         // 获取表达式节点列表
    std::vector<AstNode *> &statements = statementList->getCnodeList();
    
    size_t numChildren = statements.size(); 
    // 递归访问子节点
    for (size_t i = 0; i < numChildren; ++i)
    {
        // 访问当前子节点
        statementList->get(i)->accept(this, fs);

        // 如果不是最后一个语句节点，则输出分号
        if (i != numChildren - 1)
        {
            fprintf(fs, "; ");
        }
    }
    }
    
    void GenerationVisitor::visit(IfStatement *ifStatement, FILE *fs)  {
    fprintf(fs, "if (");
    visit(ifStatement->get(0), fs); // 访问 expression
    fprintf(fs, ")\n{\n");
    visit(ifStatement->get(1), fs); // 访问 then statement
    fprintf(fs, "}\n");

    visit(ifStatement->get(2), fs); // 访问 else_part
}
 
    void GenerationVisitor::visit(ElsePart *elseNode, FILE *fs)  
    {
        switch (elseNode->grammar_type_)
        {
        case ElsePart::ELSEType::EPSILON:
            return;
        case ElsePart::ELSEType::ELSE_STATEMENT:
            fprintf(fs, "else {\n");
            visit(ifStatement->get(0), fs); // 访问 expression
            fprintf(fs, "}\n");
        }
    } 

 void GenerationVisitor::visit(ProcedureCall *procedureCall, FILE *fs)  {
   fprintf(fs, "%s", procedureCall->get_id().c_str());
    // 根据调用类型决定是否输出参数列表
    if (procedureCall->procedure_type == ProcedureCall::ProcedureType::NO_LIST)
    {
        fprintf(fs, "();\n"); // 输出空参数列表
    }
    else if (procedureCall->procedure_type == ProcedureCall::ProcedureType::EXP_LIST)
    {
        fprintf(fs, "(");
        procedureCall->get(1)->accept(this, fs);//expressionlist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
    else if (procedureCall->procedure_type == ProcedureCall::ProcedureType::VAR_LIST)
    {
        fprintf(fs, "(");
        procedureCall->get(1)->accept(this, fs);//variablelist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
 }

void GenerationVisitor::visit(AssignopStatement *assignopStatement, FILE *fs)  
    {
        auto assignment_node = dynamic_cast<AssignmentNode *>(statement->get(0));
        auto exp = assignment_node->get(1)->DynamicCast<ExpressionNode>();
        // 根据左侧类型决定生成的代码逻辑
        switch (assignopStatement->left_type)
        {
        case AssignopStatement::LEFTTYPE::VARIABLE:
        case AssignopStatement::LEFTTYPE::FUNC:
        {
            // 生成函数调用的代码
            assignopStatement->get(0)->accept(this, fs);

            // 输出赋值操作符
            fprintf(fs, " = ");

            // 生成右侧表达式的代码
            assignopStatement->get(1)->accept(this, fs);

            // 输出分号以结束语句
            fprintf(fs, ";\n");
            break;
        }
        default:
            // 其他情况下，什么也不做
            break;
        }
    }

void GenerationVisitor::visit(LoopStatement *loopStatement, FILE *fs)  
    {
          switch (loopStatement->loop_type)
        {
        case LoopStatement::LoopType::FORUP:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id->accept(this, fs);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)->accept(this, fs);//expression
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, " <= ");
            loopStatement->get(2)->accept(this, fs);//中间的expression
            fprintf(fs, "; ");
            
            id->accept(this, fs);
            fprintf(fs, "++) {\n");
            loopStatement->get(3)->accept(this, fs);//statement
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::FORDOWN:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id->accept(this, fs);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, " >= ");
            loopStatement->get(2)->accept(this, fs);
            fprintf(fs, "; ");
            id->accept(this, fs);
            fprintf(fs, "--) {\n");
            loopStatement->get(3)->accept(this, fs);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::WHILE:
        {
            fprintf(fs, "while (");
            loopStatement->get(0)->accept(this, fs);
            fprintf(fs, ") {\n");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::REAPT:
        {
            fprintf(fs, "do {\n");
            loopStatement->get(0)->accept(this, fs);
            fprintf(fs, "} while (!(");
            loopStatement->get(1)->accept(this, fs);
            fprintf(fs, "));\n");
            break;
        }
        }
    }


void GenerationVisitor::visit(Variable *variable, FILE *fs)  {
    // 访问第一个子节点
    variable->get(0)->accept(this, fs);
    // 访问第二个子节点
    variable->get(1)->accept(this, fs);
}

void GenerationVisitor::visit(VariableList *variableList, FILE *fs)   {
    
    std::vector<AstNode *> &children = variableList->getCnodeList();
    
    // 处理单个表达式节点
    if (variableList->grammar_type() ==  VariableList::GrammarType::VAR_)
    {
        variableList->get(0)->accept(this, fs);
    }
    // 处理多个表达式节点
    else if (variableList->grammar_type() == VariableList::GrammarType::VAR_LIST_VAR)
    {
        size_t numChildren=children.size();
        // 遍历子节点列表并逐个访问
        for (size_t i = 0; i < numChildren; ++i) {
            children[i]->accept(this, fs);

            // 如果不是最后一个节点，则输出逗号
            if (variableList->grammar_type() == VariableList::GrammarType:: VAR_LIST_VAR && i != numChildren - 1) {
                fprintf(fs, ", ");
            }
        }
    }
}
void GenerationVisitor::visit(IDVarPart *idVarPart, FILE *fs)  
    {
    if (grammar_type_ == GrammarType::_ID)
      {
        fprintf(fs, ".");
        visit(switchStatement->get(0), fs); // 访问 id
      }
      else if (grammar_type_ == GrammarType::EXP_LIST)
      {
        fprintf(fs, "[");
       visit(switchStatement->get(0), fs); // 访问 expression_list
        if (array_lb_ > 0)
          PRINT(" - %d", array_lb_)
        else if (array_lb_ < 0)
          PRINT(" + %d", -array_lb_)
        fprintf(fs, "]");
      }
    }
void GenerationVisitor::visit(IDVarParts *idVarParts, FILE *fs)   {
    // 获取子节点列表
    std::vector<AstNode *> &children = idVarParts->getCnodeList();

    // 遍历子节点列表并逐个访问
    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->accept(this, fs);

        // 如果不是最后一个节点，则输出空格
        if (i != children.size() - 1) {
            fprintf(fs, " ");
        }
    }
}

 void GenerationVisitor::visit(Term *term, FILE *fs)  
{
    if (term->GetSymType() == Term::SymbolType::SINGLE)
    {
        // term -> factor 的情况
        term->get(0)->accept(this, fs); // 访问 factor 节点
    }
    else
    {
        // term -> term MULOP factor 的情况
        term->get(0)->accept(this, fs); // 访问左侧 term 节点
      
        // 根据乘法操作符类型输出相应的符号
        switch (term->GetSymType())
        {
        case Term::SymbolType::MULTIPLY:
            fprintf(fs, " * ");
            break;
        case Term::SymbolType::DIVIDE:
            fprintf(fs, " / ");
            break;
        case Term::SymbolType::MOD:
            fprintf(fs, " % ");
            break;
        case Term::SymbolType::AND:
            fprintf(fs, " && ");
            break;
        case Term::SymbolType::SINGLE:
            break;
        }
        term->get(2)->accept(this, fs); // 访问右侧 factor 节点
    }
}

    void GenerationVisitor::visit(Factor *factor, FILE *fs)  
    {
        switch (factor->get_factor_type())
        {
        case Factor::FactorType::NUM:
        case Factor::FactorType::VARIABLE:
            factor->get(0)->accept(this, fs);
            break;
        case Factor::FactorType::EXP:
            fprintf(fs, "(");
            factor->get(0)->accept(this, fs);
            fprintf(fs, ")");
            break;
        case Factor::FactorType::ID_EXP_LIST:
            factor->get(0)->accept(this, fs);
            fprintf(fs, "(");
            factor->get(1)->accept(this, fs);
            fprintf(fs, ")");
            break;
        case Factor::FactorType::NOT_:
            fprintf(fs, "!");
            factor->get(0)->accept(this, fs);
            break;
        case Factor::FactorType::UMINUS_:
            fprintf(fs, "-");
            factor->get(0)->accept(this, fs); // 访问因子节点
            break;
        case Factor::FactorType::CHAR_:
            fprintf(fs, "'");
            factor->get(0)->accept(this, fs); // 'letter'
            fprintf(fs, "'");
            break;
        case Factor::FactorType::STR:
        case Factor::FactorType::BOOL:
            factor->get(0)->accept(this, fs);
            break;
        default:
            break;
        }
    }

void Statement::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void CompoundStatement::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void StatementList::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void IfStatement::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ProcedureCall::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void AssignopStatement::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ElsePart::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void LoopStatement::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void VariableList::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void Variable::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void IDVarPart::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void IDVarParts::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void Expression::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void SimpleExpression::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void ExpressionList::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void Term::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

void Factor::accept(Visitor *visitor, FILE *fs)
{
    visitor->visit(this, fs);
}

}  // namespace ast
=======
}  // namespace ast
>>>>>>> 2e8df6f659dc28235ebde21c391d09b0b7304b64:src/generation_visitor.cpp
