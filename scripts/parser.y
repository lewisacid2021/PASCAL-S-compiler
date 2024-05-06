%{
#include "parser.h"`
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

%}

%union {
    //主程序
    // ast::ProgramStruct* program_node;
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
};
%parse-param {pascals::ast::AST *real_ast}
%start program
%token PROGRAM FUNCTION PROCEDURE TO DOWNTO 
%token ARRAY TYPE CONST RECORD STRING
%token IF THEN ELSE CASE OF WHILE DO FOR REPEAT UNTIL BEGIN_ END
%token ADDOP NOT PLUS UMINUS CONSTASSIGNOP  
%token <token_info> ID CHAR INT_NUM REAL_NUM RELOP MULOP STRING_ VAR SUBCATALOG
%token <token_info> ASSIGNOP SEP TRUE FALSE ';'

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
	    ProgramNode* headnode = new ProgramNode();
        headnode->append_child($1);
        headnode->append_child($2);
    };

program_head : PROGRAM ID '(' id_list ')' ';' {
        // program_head -> PROGRAM ID '(' id_list ')' ';'
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($3)
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
        $$ = new IdList(IdList::GrammarType::MULTIPLE_ID)
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$.id_list_node->append_child($1);
        $$.id_list_node->append_child(leaf_node);
    } | ID {
        // id_list -> ID
        $$ = new IdList(IdList::GrammarType::SINGLE_ID)
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$.id_list_node->append_child(leaf_node);
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
        $$ = new ConstDeclaration(ConstDeclarationNode::GrammarType::MULTIPLE_ID, $5->get_type());
        $$->append_child($1);
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode($5.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        
    }
    | ID '=' const_value
    {   
        // const_declaration -> ID '=' const_value
        $$ = new ConstDeclaration(ConstDeclarationNode::GrammarType::SINGLE_ID, $3->get_type());
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode($5.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
    };

const_value : PLUS INT_NUM
    // const_value的节点为ConstValue类型
    {
        // const_value -> + INT_NUM
        $$ = new ConstValue($1.value);
    }
    | UMINUS INT_NUM
    {
        // const_value -> - INT_NUM
        $$ = new ConstValue($1.value);
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
        $$ = new ConstValue($1.value);
    }
    | UMINUS REAL_NUM
    {   
        // const_value -> REAL_NUM
        $$ = new ConstValue($1.value);
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
        $$ = new RecordDeclarations(RecordDelcarations::GrammarType::EPSILON);
    }
    | record_declaration
    {
        // record_declarations -> ε | record_declaration
        $$ = new RecordDeclarations(RecordDelcarations::GrammarType::DECLARATION);
        $$->append_child($1);
    }

record_declaration : TYPE CHAR CONSTASSIGNOP RECORD  var_declaration END ';'
    {
        // record_declaration -> def-record | record_declaration def-record
        $$ = new RecordDeclaration(RecordDelcaration::GrammarType::SINGLE_DECLARATION);
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($5);

    }
    | record_declaration TYPE CHAR CONSTASSIGNOP RECORD  var_declaration END ';'
    {
        $$ = new RecordDeclaration(RecordDelcaration::GrammarType::MULTI_DECLARATION);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($6);
    }

var_declarations : 
    {
        // var_declarations -> ε
        $$ = new VaDeclarations(VarDeclarations::GrammarType::EPSILON);
    }
    | VAR var_declaration ';'
    {
        // var_declarations -> VAR var_declaration ';'
        $$ = new VaDeclarations(VarDeclarations::GrammarType::DECLARATION);
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
        if ($6->var_type == TypeNode::VarType::STRING_TYPE || $6->var_type == TypeNode::VarType::RECORD_TYPE){
            // 不支持数组的元素类型为string
            // 不支持在array的type中声明record
            $$ = new ArrayTypeNode("error");
        }
        else if($6->var_type == TypeNode::VarType::ID_TYPE){
            $$ = new ArrayTypeNode($6->get_type_name());
        }
        else {
            $$ = new ArrayTypeNode("array");
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
        StringType* string_info = new StringType(StringType::Grammar::TypeLIMIT, $3.value.get<int>());
        $$ = new StringTypeNode(string_info);
    }
    | STRING
    {
        StringType* string_info = new StringType(StringType::Grammar::TypeLIMIT, 0);
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
        $$ = new SubprogramHead(SubprogramHead::GrammarType::FUNCTION);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
    }
    | PROCEDURE ID formal_parameter ';'
    {
        // subprogram_head -> PROCEDURE ID formal_parameter ';'
        $$ = new SubprogramHead(SubprogramHead::GrammarType::PROCEDURE);
        LeafNode *leaf_node = new LeafNode($2.value);
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
        $$ = new ParamListsNode(ParamListsNode::GrammarType::SINGLE_PARAM_LIST);
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
        $$ = new Statement(Statement::StatementrType::COMPOUND_STATEMENT);
        $$->append_child($1);
    }
    | ifstatement
    {   
        // statement -> IF expression THEN statement else_part
        $$ = new Statement(Statement::GrammarType::IF_STATEMENT);
        $$->append_child($1);
    }
    | loopstatement
    {
        // statement -> CASE expression OF case_body END
        $$ = new Statement(Statement::GrammarType::LOOP_STATEMENT);
        $$->append_child($1);
    }
    | 
    {
        // statement -> ε
        $$ = new Statement(Statement::GrammarType::EPSILON);
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
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::WITHOUT_LIST, $1.value.get<string>());
    }
    | ID '(' ')'
    {
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::WITHOUT_LIST, $1.value.get<string>());
    }
    | ID '(' expression_list ')'
    {
        // procedure_call -> id ( expression_list )
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::WITHOUT_LIST, $1.value.get<string>());
        $$->append_child($3);
    };

ifstatement : IF expression THEN statement else_part
    {
        // if_statement -> if expression then statement else_part
        $$ = new IfStatement();
        $$->append_child($1);
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
        $$ = new LoopStatement(LoopStatement::LoopType::WHILE);
        $$->append_child($2);
        $$->append_child($4);

    } 
    | REPEAT statement_list UNTIL expression
    {
        // statement -> repeat statement until expression
        $$ = new LoopStatement(LoopStatement::LoopType::REAPT);
        $$->append_child($2);
        $$->append_child($4);
    }
    | FOR ID ASSIGNOP expression DOWNTO expression DO statement
    {
        // statement -> FOR ID ASSIGNOP expression downto expression DO statement
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        LeafNode *leaf_node = new LeafNode(LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
    }
    | FOR ID ASSIGNOP expression TO expression DO statement
    {
        $$ = new LoopStatement(LoopStatement::LoopType::FORUP);
        LeafNode *leaf_node = new LeafNode(LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
    };

variable_list : variable
    { 
        // variable_list -> variable
        $$ = new VariableList(VariableList::GrammarType::VARIABLE);
        $$->append_child($1);
    } 
    | variable_list ',' variable
    {
        // variable_list -> variable_list ',' variable
        $$ = new VariableList(VariableList::GrammarType::VARIABLE_LIST_VARIABLE);
        $$->append_child($1);
        $$->append_child($3);
    };

variable : ID id_varparts
    {
        // variable -> ID id_varparts
        $$ = new Variable();
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        $$.variable_node->append_child(leaf_node);
        $$.variable_node->append_child($2);
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
        $$ = new Expression(Expression::GrammarType::DOUBLE, $2.value.get<string>(), "bool");
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression
    {
        // expression -> simple_expression.
        $$ = new Expression(Expression::ExpressionType::SINGLE, " ", $1->GetExpType());
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
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS, $2->GetTerType());
        $$->append_child($2);
    }
    | UMINUS term
    {
        // simple_expression -> - term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::UMINUS, $2->GetTerType());
        $$->append_child($2);
    }
    | simple_expression ADDOP term
    {
        // simple_expression -> simple_expression or term.、
        $$ = new SimpleExpression(SimpleExpression::SymbolType::OR, 'bool');
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression PLUS term
    { 
        // simple_expression -> simple_expression + term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS, $3->GetTerType());
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression UMINUS term
    {
        $$ = new SimpleExpression(SimpleExpression::SymbolType::UNIMUS, $3->GetTerType());
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
        sym_type = $2.value.get<string>();
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
        $$ = new Factor(GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("INT");
        $$->append_child($1);
    }
    | REAL_NUM
    {   
        // factor -> num
        $$ = new Factor(GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("INT");
        $$->append_child($1);
    }
    | STRING_
    {
        // factor -> STRING
        if($1.value.get<string>() == "TRUE"){
            //boolean true
            $$ = new Factor(GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("BOOL");
            
        }
        else if($1.value.get<string>() == "FALSE"){
            //boolean false
            $$ = new Factor(GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("BOOL");
        }
        else {
            //字符
            $$ = new Factor(GrammerType::STRING);
            LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
            $$->SetFacType("STRING");
        }
        $$->append_child($1);
    }
    | CHAR
    {
        // factor -> char
        $$ = new Factor(GrammerType::CHAR);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("CHAR");
        $$->append_child($1);
    }
    | variable
    {   
        // factor -> variable.
        $$ = new Factor(GrammerType::VARIABLE);
        // $$->SetFacType("STRING");
        $$->append_child($1);
    }
    |ID '(' expression_list ')'
    {
        $$ = new Factor(GrammerType::ID_EXP_LIST);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME)
        // 类型需要靠符号表确认
        // $$->SetFacType("STRING");
        $$->append_child(leaf_node);
        $$->append_child($3);
    }
    | '(' expression ')'
    {
        // factor -> (expression).
        $$ = new Factor(GrammerType::EXP);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
    }
    | NOT factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(GrammerType::NOT);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    | UMINUS factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(GrammerType::UMINUS);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    
/*---------------.
| Error handler  |
`---------------*/
/*--紧急恢复--*/
/* program : error
    {
        location_pointer_refresh();
        new_line_flag=false;
        yyerror(real_ast,"unrecoverable errors occurred");
        while (new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        while (yychar!= YYEOF){
            yychar = yylex();
        }        
    }; */
/*--短语级恢复--*/

    /*PROGRAM相关错误*/

/* program_head: PROGRAM error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }; 

program: program_head program_body error
    {
        location_pointer_refresh();
        table_set_queue.push(top_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
        ProgramNode* node = new ProgramNode();
	node->append_child($1);
	node->append_child($2);
	real_ast->set_root(node);
	delete top_table_set;

        int length=cur_line_info.size();
        if(length==0){
            length = last_line_info.size();
            char msg[]="expected '.' at the end of the program";
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }else{        
            yyerror(real_ast,"expected '.' at the end of the program");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }; */

    /*定义语句相关*/

const_declarations: CONST error
    {
        if(yychar==TYPE || yychar==BEGIN_ || yychar==VAR || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar=='=')
                yyerror(real_ast,"expected identifier before '='");
            else
                yyerror(real_ast,"unrecoverable errors occurred in const_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }    
        while (yychar!=TYPE && yychar!= VAR && yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
            yychar = yylex();
        }
    };

type_declarations: TYPE  error
    {
        if(yychar==BEGIN_ || yychar==VAR || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{     
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar=='=')
                yyerror(real_ast,"expected identifier before '='");
            else
                yyerror(real_ast,"unrecoverable errors occurred in type_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }
        while (yychar!= VAR && yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
            yychar = yylex();
        }
    };

var_declarations: VAR error
    {
        if( yychar==BEGIN_ || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expcted ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){      
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar==':')
                yyerror(real_ast,"expected identifier before ':'");
            else
                yyerror(real_ast,"unrecoverable errors occurred in var_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }
        while (yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
           yychar = yylex();
        }
        
    };

const_declaration: ID const_variable
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before const value");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

const_declaration: const_declaration ';' ID const_variable
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before const value");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };     

const_declaration: ID '=' error  
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected const value before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }; 

const_declaration: ID ASSIGNOP 
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
    const_variable 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };
    
const_declaration: const_declaration ';' ID ASSIGNOP
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
    const_variable
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

const_declaration: ID ':' 
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
    const_variable 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };
    
const_declaration: const_declaration ';' ID ':'
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
    const_variable
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };    
     
const_declaration: const_declaration ';' ID '=' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected const value before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }; 

const_declaration: const_declaration ';'error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar=='=')
            yyerror(real_ast,"expected identifier before '='");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type_declaration: ID type
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type_declaration: type_declaration ';' ID type
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };    

type_declaration: ID '=' error  
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }; 

type_declaration: ID ASSIGNOP 
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
    type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type_declaration: type_declaration ';' ID ASSIGNOP 
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
    type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type_declaration: ID ':' 
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
    type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type_declaration: type_declaration ';' ID ':' 
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
    type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };    
     
type_declaration: type_declaration ';' ID '=' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };     

type_declaration: type_declaration ';' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar=='=')
            yyerror(real_ast,"expected identifier before '='");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };
    
var_declaration:id_list ID_or_type
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected ':' before identifier or type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: var_declaration ';' id_list ID_or_type
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected ':' before identifier or type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };     

var_declaration: id_list ':' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    };

var_declaration: var_declaration ';' id_list ':' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: var_declaration ';' error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==':')
            yyerror(real_ast,"expected identifier before ':'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: id_list ASSIGNOP 
    {
        yyerror(real_ast,"expected ':' (have ':=')");
        location_pointer_refresh();
    }
    ID_or_type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: var_declaration ';' id_list ASSIGNOP 
    {
        yyerror(real_ast,"expected ':' (have ':=')");
        location_pointer_refresh();
    }
    ID_or_type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: ID '=' 
    {
        yyerror(real_ast,"expected ':' (have '=')");
        location_pointer_refresh();
    }
    ID_or_type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

var_declaration: var_declaration ';' ID '=' 
    {
        yyerror(real_ast,"expected ':' (have '=')");
        location_pointer_refresh();
    }
    ID_or_type 
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

ID_or_type:ID
    | type
    ;       
/*其他*/

type: ARRAY '[' periods ']' error
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"expected 'of' before type.");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type: ARRAY  error
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"Invaild periods.");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

type: ARRAY '[' periods ']' OF error
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"unknown error!");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };    

id_varpart: '[' error 
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';'){
            yyerror(real_ast,"expected ']' before ';'");
        }else if(yychar == ASSIGNOP){
            yyerror(real_ast,"expected ']' before ':='");
        }else
            yyerror(real_ast,"invalid expression");
        int left_num = 1;   // 括号匹配
        while (yychar!=';' && yychar!=ASSIGNOP && new_line_flag==false && yychar!= YYEOF ){
            if(yychar=='[') left_num++;
            if(yychar==']'&& left_num == 1) break; 
            yychar = yylex();
        }
        if(yychar==']'){
            yychar=yylex();
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==ASSIGNOP){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    };

type: ARRAY '[' periods ']' OF ID
    {
        yyerror(real_ast,"unsupported definition of array using customized type");
        location_pointer_refresh();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }; 

factor: '(' error 
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected ')' before ';'");
        else
            yyerror(real_ast,"invalid expression");
        int left_num = 1;   // 括号匹配
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF ){
            if(yychar=='(') left_num++;
            if(yychar==')'&& left_num == 1) break; 
            yychar = yylex();
        }
        if(yychar==')'){
            yychar=yylex();
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    };

subprogram_head: FUNCTION ID formal_parameter ':' error
    {
        new_line_flag=false;
        location_pointer_refresh();
        if(yychar==ARRAY||yychar==RECORD||yychar==ID)
        {
            yyerror(real_ast,"return type of function should be integer, real, boolean or char");
        }
        while(yychar!=';'&&!new_line_flag)
            yychar=yylex();
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            yychar=yylex();
        }
    }    


/*statement相关*/
// compound_statement: BEGIN_ statement_list END
// IF expression THEN statement else_part
statement: IF error
    {
        new_line_flag=false;
        location_pointer_refresh();
        while(yychar!=THEN && !new_line_flag&&yychar!=';')
            yychar=yylex();
        if(yychar==THEN){
            yyerror(real_ast,"invalid expression");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            yychar=yylex();
        }
        else if(yychar==';'){
            char msg[] = "'THEN' might be missing";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            yyerror(real_ast,"Syntax error");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        while(yychar!=';'&&yychar!=END)
            yychar=yylex();
    }
    ;
// REPEAT statement_list UNTIL expression
statement: REPEAT error 
    {
        new_line_flag=false;
        if(yychar=='='||yychar==RELOP||yychar==END)
            yyerror(real_ast,"'UNTIL' might be missing");
        else
            yyerror(real_ast,"Syntax error");
        location_pointer_refresh();
        while(yychar!=';'&&!new_line_flag && yychar!=END)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

// statement:FOR ID ASSIGNOP expression updown expression DO statement 

// WHILE expression DO statement

statement: WHILE error
{
    new_line_flag=false;
    location_pointer_refresh();
    char msg[] = "'do' might be missing";
    int length = last_line_info.size();
    if(yychar==ID)
        fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
    else{
        fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,"Syntax error");   
    }
    while(yychar!=';'&&!new_line_flag && yychar!=END)
        yychar=yylex();
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
    fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
    fprintf(stderr,"\t| %s",location_pointer);
};

statement:WHILE expression  DO error
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&&!new_line_flag && yychar!=END)
        yychar=yylex();
    fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
    fprintf(stderr,"\t| %s",location_pointer);
}; 

statement:FOR ID ASSIGNOP expression  updown expression DO error
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
};

statement:FOR ID ASSIGNOP expression  updown error
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
};

statement:FOR ID ASSIGNOP error
{
    new_line_flag=false;
    if(yychar==INT_NUM)
        yyerror(real_ast,"'to' or 'downto' might be missing");
    else
        yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
};


statement: variable ASSIGNOP type
    {
        yyerror(real_ast,"type identifier not allowed");
        location_pointer_refresh();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    };

statement: variable ASSIGNOP error
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected expression before ';'");
        else
            yyerror(real_ast,"invalid expression");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    };

statement: variable ':' 
    {
        yyerror(real_ast,"expected ':=' (have ':' and '=')");
        location_pointer_refresh();
    } '=' expression
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    ; 


%%
 

void yyerror(ast::AST* real_ast,const char *msg){
    if(yydebug || strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void yynote(std::string msg ,int line){
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
}
int yywrap(){
    return 1;
} 
