%{
#include "../include/parser.h"
using namespace ast;
using std::string;
extern "C"			
{					
    void yyerror(const char *s);
    extern int yylex(void);
    extern int line_count;
    extern bool new_line_flag;
    extern int yyleng;
    extern int last_line_count;
}
extern std::string cur_line_info;
extern std::string last_line_info;
extern int lex_error_flag;
int semantic_error_flag = 0;

int error_flag=0;

void yyerror(AST* Ast,const char *msg);

%}

/* %union {
    Token token_info;
    //主程序
    //ast::ProgramStruct* program;
    ast::ProgramHead* program_head_node;
    ast::ProgramBody* program_body_node;
    ast::IdList* idlist_node;
    ast::RecordDelcarations* record_declarations_node;
    ast::RecordDelcaration* record_declaration_node;
    ast::ConstDeclarations* const_declarations_node;
    ast::ConstDeclaration* const_declaration_node;
    ast::VarDeclarations* var_declarations_node;
    ast::VarDeclaration* var_declaration_node;
    //类型
    ast::TypeNode* type_node;
    ast::ArrayTypeNode array_node;
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
}; */
%parse-param {ast::AST *Ast}
%start program
%token PROGRAM FUNCTION PROCEDURE TO DOWNTO 
%token ARRAY TYPE CONST RECORD STRING
%token IF THEN ELSE OF WHILE DO FOR REPEAT UNTIL BEGIN_ END
%token ADDOP NOT PLUS CASE UMINUS CONSTASSIGNOP  
%token <token_info> ID CHAR INT_NUM REAL_NUM RELOP MULOP STRING_ VAR SUBCATALOG
%token <token_info> ASSIGNOP ';'

%type <program_head_node> program_head
%type <program_body_node> program_body
%type <const_declarations_node> const_declarations
%type <const_declaration_node> const_declaration
%type <idlist_node> id_list
%type <record_declarations_node> record_declarations
%type <record_declaration_node> record_declaration
%type <var_declarations_node> var_declarations
%type <var_declaration_node> var_declaration

%type <type_node> type
%type <array_node> array_type
%type <string_node> string_type
%type <periods_node> periods
%type <period_node> period

%type <subprogram_declarations_node> subprogram_declarations
%type <subprogram_declaration_node> subprogram_declaration
%type <subprogram_head_node> subprogram_head
%type <subprogram_body_node> subprogram_body

%type <formal_param_node> formal_parameter
%type <paramlists_node> parameter_lists
%type <paramlist_node> parameter_list
%type <var_param_node> var_parameter
%type <value_param_node> value_parameter

%type <compound_statement_node> compound_statement
%type <statement_list_node> statement_list
%type <statement_node> statement
%type <assignop_statement_node> assignop_statement
%type <procedure_call_node> procedure_call
%type <ifstatement_node> ifstatement
%type <loopstatement_node> loopstatement
%type <elsepart_node> else_part

%type <variablelist_node> variable_list
%type <variable_node> variable
%type <idvarparts_node> id_varparts
%type <idvarpart_node> id_varpart

%type <expression_list_node> expression_list
%type <expression_node> expression
%type <simple_expression_node> simple_expression
%type <term_node> term
%type <factor_node> factor;

%type <const_value_node> const_value

%%

program : program_head program_body '.'
    {   
        // prgram -> program_head program_body '.'
	    ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);

        Ast->set_root(headnode);
    };

program_head : PROGRAM ID '(' id_list ')' ';' {
        // program_head -> PROGRAM ID '(' id_list ')' ';'
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
    } | PROGRAM ID '('  ')' ';' {
        // program_head -> PROGRAM ID '('  ')' ';'
        $$ = new ProgramHead();
    } | PROGRAM ID ';' {
        // program_head -> PROGRAM ID ';'
        $$ = new ProgramHead();
    }

program_body : const_declarations record_declarations var_declarations subprogram_declarations compound_statement {
        // program_body -> const_declarations type_declarations var_declarations subprogram_declarations compound_statement
        $$ = new ProgramBody();
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($3);
        $$->append_child($4);
        $$->append_child($5);
    };

id_list : id_list ',' ID { 
        // id_list -> id_list ',' ID
        // 插入idlist node以及叶子节点
        $$ = new IdList(IdList::GrammarType::MULTIPLE_ID);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child($1);
        $$->append_child(leaf_node);
    } | ID {
        // id_list -> ID
        $$ = new IdList(IdList::GrammarType::SINGLE_ID);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
    };

const_declarations :{
        // const_declarations -> ε
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
    }
    | CONST const_declaration ';'
    {   
        // const_declarations -> CONST const_declaration ';'
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->append_child($2);
    };

const_declaration : const_declaration ';' ID '=' const_value
    {
        // const_declaration -> const_declaration ';' ID '=' const_value
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->append_child($1);
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        
    }
    | ID '=' const_value
    {   
        // const_declaration -> ID '=' const_value
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
    };

const_value : PLUS INT_NUM
    // const_value的节点为ConstValue类型
    {
        // const_value -> + INT_NUM
        $$ = new ConstValue($2.value);
    }
    | UMINUS INT_NUM
    {
        // const_value -> - INT_NUM
        $$ = new ConstValue($2.value);
        $$->set_uminus();
    }
    | INT_NUM
    {
        // const_value -> INT_NUM
        $$ = new ConstValue($1.value);
    }
    | PLUS REAL_NUM
    {   
        // const_value -> REAL_NUM
        $$ = new ConstValue($2.value);
    }
    | UMINUS REAL_NUM
    {   
        // const_value -> REAL_NUM
        $$ = new ConstValue($2.value);
        $$->set_uminus();
    }
    | REAL_NUM
    {   
        // const_value -> REAL_NUM
        $$ = new ConstValue($1.value);
    }
    | STRING_
    {
        // const_variable -> string
        if($1.value.get<string>() == "TRUE"){
            //boolean true
            $$ = new ConstValue(true);
        }
        else if($1.value.get<string>() == "FALSE"){
            //boolean false
            $$ = new ConstValue(false);
        }
        else {
            //字符
            $$ = new ConstValue($1.value);
        }
    }
    | CHAR
    {
        // const_variable -> CHAR | TRUE | FALSE
        $$ = new ConstValue($1.value);
    }

record_declarations :
    {
        $$ = new RecordDeclarations(RecordDeclarations::GrammarType::EPSILON);
    }
    | record_declaration
    {
        // record_declarations -> ε | record_declaration
        $$ = new RecordDeclarations(RecordDeclarations::GrammarType::DECLARATION);
        $$->append_child($1);
    }

record_declaration : TYPE CHAR CONSTASSIGNOP RECORD  var_declaration END ';'
    {
        // record_declaration -> def-record | record_declaration def-record
        $$ = new RecordDeclaration(RecordDeclaration::GrammarType::SINGLE_DECLARATION);
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($5);

    }
    | record_declaration TYPE CHAR CONSTASSIGNOP RECORD  var_declaration END ';'
    {
        $$ = new RecordDeclaration(RecordDeclaration::GrammarType::MULTI_DECLARATION);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($6);
    }

var_declarations : 
    {
        // var_declarations -> ε
        $$ = new VarDeclarations(VarDeclarations::GrammarType::EPSILON);
    }
    | VAR var_declaration ';'
    {
        // var_declarations -> VAR var_declaration ';'
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->append_child($2);
    };

var_declaration : var_declaration ';' id_list ':' type 
    {
        // var_declaration -> var_declaration ';' id_list ':' type
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
    }
    | id_list ':' type 
    {
        // var_declaration -> id_list ':' type
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->append_child($1);
        $$->append_child($3);
    };

type : ID 
    {
        // type -> ID
        // 由于我们将integer等都设为保留字，都识别为ID（integer char boolean string real）
        $$ = new TypeNode(TypeNode::VarType::ID_TYPE, $1.value.get<string>());
        //IdTypeNode* idnode = new IdTypeNode($1.value.get());
        //$$->append_child(idnode);
    }
    | array_type
    {
        $$ = new TypeNode(TypeNode::VarType::ARRAY_TYPE, "array");
        $$->append_child($1);
    }
    | RECORD var_declaration END ';'
    {
        // recordtype -> record var_declaration end;
        $$ = new TypeNode(TypeNode::VarType::RECORD_TYPE, "record");
        $$->append_child($2);
    };
    | string_type
    {
        $$ = new TypeNode(TypeNode::VarType::STRING_TYPE, "string");
        $$->append_child($1);
    };

array_type : ARRAY '[' periods ']' OF type
    {   
        $$ = new ArrayTypeNode();
        if ($6->GetVarType() == TypeNode::VarType::STRING_TYPE || $6->GetVarType() == TypeNode::VarType::RECORD_TYPE){
            // 不支持数组的元素类型为string
            // 不支持在array的type中声明record
            $$ -> set_type("error");
        }
        else if($6->GetVarType() == TypeNode::VarType::ID_TYPE){
            $$ -> set_type($6->get_type_name());
        }
        else {
            $$ -> set_type("array");
        }
        // 添加数组信息
        ArrayType* at = new ArrayType();
        at->SetDimension($3->get_dm());
        $$->set_info(at);

        $$->append_child($3);
        $$->append_child($6);
    };

/* record_body :
    {
        // record_body -> ε
        $$.record_info = new std::unordered_map<std::string, TypeTemplate*>();
        if(error_flag)
            break;
        $$.record_body_node = new RecordBodyNode();
    } 
    | var_declaration 
    {
	$$.record_info = $1.record_info;
	if(error_flag)
	    break;
	$$.record_body_node = new RecordBodyNode();
	$$.record_body_node->append_child($1.variable_declaration_node);
	delete $1.pos_info;
    } 
    | var_declaration ';'
    {
        // record_body -> var_declaration ';'
        $$.record_info = $1.record_info;
        if(error_flag)
            break;
        $$.record_body_node = new RecordBodyNode();
        $$.record_body_node->append_child($1.variable_declaration_node);
        delete $1.pos_info;
    }; */
    
periods : periods ',' period
    {
        // periods -> periods ',' period
        $$ = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        
        // 插入新的维度
        std::vector<ArrayType::Dimension> dim;
        dim = $1->get_dm();
        ArrayType::Dimension nd($3->get_lowb(), $3->get_upb());
        dim.emplace_back(nd);
        $$->set_dm(dim);

        $$->append_child($1);
        $$->append_child($3);
    }
    | period
    {
        // periods -> period
        $$ = new PeriodsNode(PeriodsNode::PeriodType::SINGLE);
        
        // 底层新建维度vector
        std::vector<ArrayType::Dimension> dim;
        ArrayType::Dimension nd($1->get_lowb(), $1->get_upb());
        dim.emplace_back(nd);
        $$->set_dm(dim);
        $$->append_child($1);
    };

period : INT_NUM SUBCATALOG INT_NUM
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        $$ = new PeriodNode($1.value.get<int>(), $3.value.get<int>());
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
    };

string_type : STRING '[' INT_NUM ']'
    {
        StringType* string_info = new StringType(StringType::GrammarType::LIMIT, $3.value.get<int>());
        $$ = new StringTypeNode(string_info);
    }
    | STRING
    {
        StringType* string_info = new StringType(StringType::GrammarType::NOLIMIT, 0);
        $$ = new StringTypeNode(string_info);
    };

subprogram_declarations : 
    {
        // subprogram_declarations -> ε
        $$ = new SubprogramDeclarations();
    }
    | subprogram_declarations subprogram_declaration ';'
    {
        // subprogram_declarations -> subprogram_declarations subprogram_declaration ';'
        $$ = new SubprogramDeclarations();
        $$->append_child($1);
        $$->append_child($2);
    };

subprogram_declaration : subprogram_head subprogram_body
    {
        // subprogram_declaration -> subprogram_head subprogram_body
        $$ = new SubprogramDeclaration();
        $$->append_child($1);
        $$->append_child($2);
    };
subprogram_body : const_declarations var_declarations compound_statement
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        $$ = new SubprogramBody();
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($3);
    };
    
subprogram_head : FUNCTION ID formal_parameter ':' type ';'
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' standrad_type ';'
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
    }
    | PROCEDURE ID formal_parameter ';'
    {
        // subprogram_head -> PROCEDURE ID formal_parameter ';'
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->set_id($2.value.get<string>());
        $$->append_child(leaf_node);
        $$->append_child($3);
    };
    
formal_parameter :
    {   
        // formal_parameter -> ε
        $$ = new FormalParam();
    }
    | '(' parameter_lists ')'
    {
        // formal_parameter -> '(' parameter_lists ')'
        $$ = new FormalParam();
        $$->append_child($2);
    };

parameter_lists : parameter_lists ';' parameter_list
    {   
        // parameter_lists -> parameter_lists ';' parameter_list
        $$ = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        $$->append_child($1);
        $$->append_child($3);
    }
    | parameter_list
    {  
        // parameter_lists -> parameter_list
        $$ = new ParamLists(ParamLists::GrammarType::SINGLE_PARAM_LIST);
        $$->append_child($1);
    };

parameter_list : var_parameter
    {   
        // parameter_list -> var_parameter
        $$ = new ParamList(ParamList::ParamType::VarParam);
        $$->append_child($1);
    }
    | value_parameter
    {   
        // parameter_list -> value_parameter
        $$ = new ParamList(ParamList::ParamType::ValueParam);
        $$->append_child($1);
    };

var_parameter : VAR value_parameter
    {   
        // var_parameter -> VAR value_parameter
        $$ = new VarParam();
        $$->append_child($2);
    };

value_parameter : id_list ':' type
    {   
        // value_parameter -> id_list ':' standrad_type
        $$ = new ValueParam();
        $$->append_child($1);
        $$->append_child($3);
    };

compound_statement : BEGIN_ statement_list END 
    {
        // compound_statement -> Begin statement_list end
        $$ = new CompoundStatement();
        $$->append_child($2);
    };

statement_list : statement_list ';' statement
    {
        // statement_list -> statement_list ';' statement
        $$ = new StatementList();
        $$->append_child($1);
        $$->append_child($3);
    } 
    | statement
    {
        // statement_list -> statement
        $$ = new StatementList();
        $$->append_child($1);
    };

statement : assignop_statement
    {   
        //statement -> AssignopStatement
        $$ = new Statement(Statement::StatementType::ASSIGN_OP_STATEMENT);
        $$->append_child($1);
    }
    | procedure_call
    {
        // statement -> call_procedure_statement
        $$ = new Statement(Statement::StatementType::PROCEDURE_CALL);
        $$->append_child($1);
    }
    | compound_statement
    {
        // statement -> compound_statement
        $$ = new Statement(Statement::StatementType::COMPOUND_STATEMENT);
        $$->append_child($1);
    }
    | ifstatement
    {   
        // statement -> IF expression THEN statement else_part
        $$ = new Statement(Statement::StatementType::IF_STATEMENT);
        $$->append_child($1);
    }
    | loopstatement
    {
        // statement -> CASE expression OF case_body END
        $$ = new Statement(Statement::StatementType::LOOP_STATEMENT);
        $$->append_child($1);
    }
    | 
    {
        // statement -> ε
        $$ = new Statement(Statement::StatementType::EPSILON);
    };

assignop_statement : variable ASSIGNOP expression
    {
        // assignop_statement -> variable ASSIGNOP expression
        $$ = new AssignopStatement(AssignopStatement::LeftType::VARIABLE);
        $$->append_child($1);
        $$->append_child($3);
    };

procedure_call : ID
    {
        // procedure_call -> id
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, $1.value.get<string>());
    }
    | ID '(' ')'
    {
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, $1.value.get<string>());
    }
    | ID '(' expression_list ')'
    {
        // procedure_call -> id ( expression_list )
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, $1.value.get<string>());
        $$->append_child($3);
    }
    | ID '(' variable_list ')'
    {
        // procedure_call -> id ( expression_list )
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::VAR_LIST, $1.value.get<string>());
        $$->append_child($3);
    };

ifstatement : IF expression THEN statement else_part
    {
        // if_statement -> if expression then statement else_part
        $$ = new IfStatement();
        $$->append_child($2);
        $$->append_child($4);
        $$->append_child($5);
    };

else_part : 
    {
        // else_part -> ε | else statement
        $$ = new ElsePart(ElsePart::ELSEType::EPSILON);
    }
    | ELSE statement
    {   
        // else_part -> else statement
        $$ = new ElsePart(ElsePart::ELSEType::ELSE_STATEMENT);
        $$->append_child($2);
    };

loopstatement : WHILE expression DO statement
    {
        // statement -> WHILE expression DO statement
        $$ = new LoopStatement(LoopStatement::LoopType::WHILE_);
        $$->append_child($2);
        $$->append_child($4);

    } 
    | REPEAT statement_list UNTIL expression
    {
        // statement -> repeat statement until expression
        $$ = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        $$->append_child($2);
        $$->append_child($4);
    }
    | FOR ID ASSIGNOP expression DOWNTO expression DO statement
    {
        // statement -> FOR ID ASSIGNOP expression downto expression DO statement
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
    }
    | FOR ID ASSIGNOP expression TO expression DO statement
    {
        $$ = new LoopStatement(LoopStatement::LoopType::FORUP);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
    };

variable_list : variable
    { 
        // variable_list -> variable
        $$ = new VariableList(VariableList::GrammarType::VAR_);
        $$->append_child($1);
    } 
    | variable_list ',' variable
    {
        // variable_list -> variable_list ',' variable
        $$ = new VariableList(VariableList::GrammarType::VAR_LIST_VAR);
        $$->append_child($1);
        $$->append_child($3);
    };

variable : ID id_varparts
    {
        // variable -> ID id_varparts
        $$ = new Variable();
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        $$->append_child(leaf_node);
        $$->append_child($2);
    };

id_varparts :
    {
        // id_varparts -> ε.
        $$ = new IDVarParts();
        std::vector<std::string> *name_list = new std::vector<std::string>;
        $$->set_pointer(name_list);
    }
    | id_varparts id_varpart
    {
        // id_varparts -> id_varparts id_varpart.
        $$ = new IDVarParts();
        std::vector<std::string> *name_list = $1->get_pointer();
        name_list->emplace_back($2->get_part_name());
        $$->set_pointer(name_list);
        $$->append_child($1);
        $$->append_child($2);
    };

id_varpart : '[' expression_list ']'
    {   
        // id_varpart -> [expression_list].
        $$ = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        
        $$->append_child($2);
    }
    | '.' ID
    {
        // id_varpart -> .id.
        $$ = new IDVarPart(IDVarPart::GrammarType::_ID);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->set_part_name($2.value.get<string>());
        $$->append_child(leaf_node);
    };

expression_list : expression_list ',' expression
    {
        // expression_list -> expression_list ',' expression
        
        std::vector<std::string> *type_list = $1->get_types();
        type_list->emplace_back($3->GetExpType());
        $$ = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        $$->append_child($1);
        $$->append_child($3);
    }
    | expression
    {
        // expression_list -> expression
        std::string type = $1->GetExpType();
        std::vector<std::string> *type_list = new std::vector<std::string>;
        type_list->emplace_back(type);
        $$ = new ExpressionList(ExpressionList::ExpressionType::SINGLE, type_list);
        $$->append_child($1);
    };

expression : simple_expression RELOP simple_expression
    {
        // expression -> simple_expression RELOP simple_expression.
        $$ = new Expression(Expression::GrammarType::DOUBLE, $2.value.get<string>(), "bool");
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression CONSTASSIGNOP simple_expression
    {
        // expression -> simple_expression '=' simple_expression.
        $$ = new Expression(Expression::GrammarType::DOUBLE, "=", "bool");
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression
    {
        // expression -> simple_expression.
        $$ = new Expression(Expression::GrammarType::SINGLE, " ", $1->GetExpType());
        $$->append_child($1);
    };

simple_expression : term
    {   
        // simple_expression -> term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::SINGLE, $1->GetTerType());
        $$->append_child($1);
    }
    | PLUS term
    {
        // simple_expression -> + term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, $2->GetTerType());
        $$->append_child($2);
    }
    | UMINUS term
    {
        // simple_expression -> - term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, $2->GetTerType());
        $$->append_child($2);
    }
    | simple_expression ADDOP term
    {
        // simple_expression -> simple_expression or term.、
        $$ = new SimpleExpression(SimpleExpression::SymbolType::OR_, "bool");
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression PLUS term
    { 
        // simple_expression -> simple_expression + term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, $3->GetTerType());
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression UMINUS term
    {
        $$ = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, $3->GetTerType());
        $$->append_child($1);
        $$->append_child($3);
    };

term : factor
    {   
        // term -> factor.
        $$ = new Term(Term::SymbolType::SINGLE, $1->GetFacType());
        $$->append_child($1);
    }
    | term MULOP factor
    {  
        // term -> term mulop factor. 
        $$ = new Term;
        std::string sym_type = $2.value.get<string>();
        if(sym_type == "*"){
            $$->SetSymType(Term::SymbolType::MULTIPLY);
            $$->SetTerType("REAL");
        }
        if(sym_type == "/"){
            $$->SetSymType(Term::SymbolType::DEVIDE);
            $$->SetTerType("REAL");
        }
        if(sym_type == "mod"){
            $$->SetSymType(Term::SymbolType::MOD);
            $$->SetTerType("REAL");
        }
        if(sym_type == "and"){
            $$->SetSymType(Term::SymbolType::AND);
            $$->SetTerType("BOOL");
        }
        if(sym_type == "div"){
            $$->SetSymType(Term::SymbolType::DEVIDE);
            $$->SetTerType("REAL");
        }
        $$->append_child($1);
        $$->append_child($3);
    };

//从这里开始
factor : INT_NUM
    {
        // factor -> num
        $$ = new Factor(Factor::GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("INT");
        $$->append_child(leaf_node);
    }
    | REAL_NUM
    {   
        // factor -> num
        $$ = new Factor(Factor::GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("INT");
        $$->append_child(leaf_node);
    }
    | STRING_
    {
        // factor -> STRING
        if($1.value.get<string>() == "TRUE"){
            //boolean true
            $$ = new Factor(Factor::GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("BOOL");
            
        }
        else if($1.value.get<string>() == "FALSE"){
            //boolean false
            $$ = new Factor(Factor::GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("BOOL");
            $$->append_child(leaf_node);
        }
        else {
            //字符
            $$ = new Factor(Factor::GrammerType::STR);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("STRING");
            $$->append_child(leaf_node);
        }
        
    }
    | CHAR
    {
        // factor -> char
        $$ = new Factor(Factor::GrammerType::CHAR_);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("CHAR");
        $$->append_child(leaf_node);
    }
    | variable
    {   
        // factor -> variable.
        $$ = new Factor(Factor::GrammerType::VARIABLE);
        // $$->SetFacType("STRING");
        $$->append_child($1);
    }
    |ID '(' expression_list ')'
    {
        $$ = new Factor(Factor::GrammerType::ID_EXP_LIST);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        // $$->SetFacType("STRING");
        $$->append_child(leaf_node);
        $$->append_child($3);
    }
    | '(' expression ')'
    {
        // factor -> (expression).
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
    }
    | NOT factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(Factor::GrammerType::NOT_);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    | UMINUS factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(Factor::GrammerType::UMINUS_);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    
/*---------------.
| Error handler  |
`---------------*/


%%
 

void yyerror(ast::AST* Ast,const char *msg){
    if(strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
     Ast->set_root(nullptr);
    
}

/*void yynote(std::string msg ,int line){
    fprintf(stderr,"%d:\033[01;32m \tnote\033[0m : previous definition of \"%s\" was here\n", line, msg.c_str());
}

void yyerror_var(AST* real_ast,int line){
    fprintf(stderr,"%d:\033[01;31m \terror\033[0m : %s\n", line, "redifinition of variable");
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void location_pointer_refresh(){
    int length = cur_line_info.size()-yyleng;
    if(length<0)
        length=0;
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
} */
int yywrap(){
    return 1;
} 