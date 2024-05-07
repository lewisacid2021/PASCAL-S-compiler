#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

#include "type.h"
#include "ast.h"
extern int yydebug;

struct Token {
  ConstValue value;
  int length;
  int line_num;
  int column_num;
};
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
struct YYSTYPE {
  Token token_info;
  union {
    ast::ProgramHead* program_head_node;
    ast::ProgramBody* program_body_node;
    ast::IdList* idlist_node;
    ast::RecordDeclarations* record_declarations_node;
    ast::RecordDeclaration* record_declaration_node;
    ast::ConstDeclarations* const_declarations_node;
    ast::ConstDeclaration* const_declaration_node;
    ast::VarDeclarations* var_declarations_node;
    ast::VarDeclaration* var_declaration_node;
    //类型
    ast::TypeNode* type_node;
    ast::ArrayTypeNode* array_node;
    ast::RecordNode* record_node; 
    ast::StringTypeNode* string_node;
    ast::PeriodsNode* periods_node;
    ast::PeriodNode* period_node;
    //子程序
    ast::SubprogramDeclarations* subprogram_declarations_node;
    ast::SubprogramDeclaration* subprogram_declaration_node;
    ast::SubprogramHead* subprogram_head_node;
    ast::SubprogramBody* subprogram_body_node;
    //子程序声明中的参数
    ast::FormalParam* formal_param_node;
    ast::ParamLists* paramlists_node;
    ast::ParamList* paramlist_node;
    ast::VarParam* var_param_node;
    ast::ValueParam* value_param_node;
    //语句
    ast::CompoundStatement* compound_statement_node;
    ast::StatementList* statement_list_node;
    ast::Statement* statement_node;
    ast::AssignopStatement* assignop_statement_node;
    ast::ProcedureCall* procedure_call_node;
    ast::IfStatement* ifstatement_node;
    ast::LoopStatement* loopstatement_node;
    ast::ElsePart* elsepart_node;
    //函数与过程的参数
    ast::VariableList* variablelist_node;
    ast::Variable* variable_node;
    ast::IDVarParts* idvarparts_node;
    ast::IDVarPart* idvarpart_node;
    //表达式
    ast::ExpressionList* expression_list_node;
    ast::Expression* expression_node;
    ast::SimpleExpression* simple_expression_node;
    ast::Term* term_node;
    ast::Factor* factor_node;

    ConstValue* const_value_node;
  };
};

typedef struct YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif
