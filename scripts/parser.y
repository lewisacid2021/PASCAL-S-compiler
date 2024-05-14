%{
#include "parser.h"
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

int error_flag = 0;

void yyerror(const char *s, int line);
void yyerror(ast::AST* Ast,const char *msg);

%}

%parse-param {ast::AST *Ast}
%start program
%token PROGRAM FUNCTION PROCEDURE TO DOWNTO 
%token ARRAY TYPE CONST RECORD STRING
%token IF THEN ELSE OF WHILE DO FOR REPEAT UNTIL BEGIN_ END
%token ADDOP NOT PLUS CASE UMINUS CONSTASSIGNOP  
%token <token_info> ID CHAR INT_NUM REAL_NUM RELOP MULOP STRING_ VAR SUBCATALOG BOOL
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
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->set_rownum(line_count);
    } | PROGRAM ID '('  ')' ';' {
        // program_head -> PROGRAM ID '('  ')' ';'
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
    } | PROGRAM ID ';' {
        // program_head -> PROGRAM ID ';'
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
    }

program_body : const_declarations record_declarations var_declarations subprogram_declarations compound_statement {
        // program_body -> const_declarations type_declarations var_declarations subprogram_declarations compound_statement
        $$ = new ProgramBody();
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child($1);
        $$->append_child(leaf_node);
    } 
    | ID 
    {
        // id_list -> ID
        $$ = new IdList(IdList::GrammarType::SINGLE_ID);
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
    };

const_declarations :{
        // const_declarations -> ε
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
    }
    | CONST const_declaration ';'
    {   
        // const_declarations -> CONST const_declaration ';'
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

const_declaration : const_declaration ';' ID CONSTASSIGNOP const_value
    {
        // const_declaration -> const_declaration ';' ID '=' const_value
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        
    }
    | ID CONSTASSIGNOP const_value
    {   
        // const_declaration -> ID '=' const_value
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        //初始化 id 叶子节点
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::VALUE);
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
    | BOOL
    {
        // const_value -> BOOL
        $$ = new ConstValue($1.value);
    }
    | STRING_
    {
        // const_variable -> string
        $$ = new ConstValue($1.value);
    }
    | CHAR
    {
        // const_variable -> CHAR 
        $$ = new ConstValue($1.value);
    }

record_declarations :
    {
        $$ = new RecordDeclarations(RecordDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
    }
    | record_declaration
    {
        // record_declarations -> ε | record_declaration
        $$ = new RecordDeclarations(RecordDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }

record_declaration : TYPE ID CONSTASSIGNOP RECORD  var_declaration END ';'
    {
        // record_declaration -> def-record | record_declaration def-record
        $$ = new RecordDeclaration(RecordDeclaration::GrammarType::SINGLE_DECLARATION);
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($5);
    }
    | record_declaration TYPE ID CONSTASSIGNOP RECORD var_declaration END ';'
    {
        $$ = new RecordDeclaration(RecordDeclaration::GrammarType::MULTI_DECLARATION);
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($6);
    }

var_declarations : 
    {
        // var_declarations -> ε
        $$ = new VarDeclarations(VarDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
    }
    | VAR var_declaration 
    {
        // var_declarations -> VAR var_declaration ';'
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

var_declaration : var_declaration  id_list ':' type ';'
    {
        // var_declaration -> var_declaration ';' id_list ':' type
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($4);
    }
    | id_list ':' type ';'
    {
        // var_declaration -> id_list ':' type
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    };

type : ID 
    {
        // type -> ID
        // 由于我们将integer等都设为保留字，都识别为ID（integer char boolean string real）
        $$ = new TypeNode(TypeNode::VarType::ID_TYPE, $1.value.get<string>());
        $$->set_rownum(line_count);
    }
    | array_type
    {
        $$ = new TypeNode(TypeNode::VarType::ARRAY_TYPE, "array");
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | RECORD var_declaration END 
    {
        // recordtype -> record var_declaration end;
        $$ = new TypeNode(TypeNode::VarType::RECORD_TYPE, "record");
        $$->set_rownum(line_count);
        $$->append_child($2);
    };
    | string_type
    {
        $$ = new TypeNode(TypeNode::VarType::STRING_TYPE, "string");
        $$->set_rownum(line_count);
        $$->append_child($1);
    };

array_type : ARRAY '[' periods ']' OF type
    {   
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
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
    
periods : periods ',' period
    {
        // periods -> periods ',' period
        $$ = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
    };

string_type : STRING '[' INT_NUM ']'
    {
        StringType* string_info = new StringType(StringType::GrammarType::LIMIT, $3.value.get<int>());
        $$ = new StringTypeNode(string_info);
        $$->set_rownum(line_count);
    }
    | STRING
    {
        StringType* string_info = new StringType(StringType::GrammarType::NOLIMIT, 0);
        $$ = new StringTypeNode(string_info);
        $$->set_rownum(line_count);
    };

subprogram_declarations : 
    {
        // subprogram_declarations -> ε
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
    }
    | subprogram_declarations subprogram_declaration ';'
    {
        // subprogram_declarations -> subprogram_declarations subprogram_declaration ';'
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
    };

subprogram_declaration : subprogram_head subprogram_body
    {
        // subprogram_declaration -> subprogram_head subprogram_body
        $$ = new SubprogramDeclaration();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
    };
subprogram_body : const_declarations var_declarations compound_statement
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        $$ = new SubprogramBody();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($3);
    };
    
subprogram_head : FUNCTION ID formal_parameter ':' type ';'
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' standrad_type ';'
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->set_id($2.value.get<string>());
        $$->append_child(leaf_node);
        $$->append_child($3);
    };
    
formal_parameter :
    {   
        // formal_parameter -> ε
        $$ = new FormalParam();
        $$->set_rownum(line_count);
    }
    | '(' ')'
    {
        $$ = new FormalParam();
        $$->set_rownum(line_count);
    }
    | '(' parameter_lists ')'
    {
        // formal_parameter -> '(' parameter_lists ')'
        $$ = new FormalParam();
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

parameter_lists : parameter_lists ';' parameter_list
    {   
        // parameter_lists -> parameter_lists ';' parameter_list
        $$ = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    }
    | parameter_list
    {  
        // parameter_lists -> parameter_list
        $$ = new ParamLists(ParamLists::GrammarType::SINGLE_PARAM_LIST);
        $$->set_rownum(line_count);
        $$->append_child($1);
    };

parameter_list : var_parameter
    {   
        // parameter_list -> var_parameter
        $$ = new ParamList(ParamList::ParamType::VarParam);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | value_parameter
    {   
        // parameter_list -> value_parameter
        $$ = new ParamList(ParamList::ParamType::ValueParam);
        $$->set_rownum(line_count);
        $$->append_child($1);
    };

var_parameter : VAR value_parameter
    {   
        // var_parameter -> VAR value_parameter
        $$ = new VarParam();
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

value_parameter : id_list ':' type
    {   
        // value_parameter -> id_list ':' standrad_type
        $$ = new ValueParam();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    };

compound_statement : BEGIN_ statement_list END 
    {
        // compound_statement -> Begin statement_list end
        $$ = new CompoundStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

statement_list : statement_list ';' statement
    {
        // statement_list -> statement_list ';' statement
        $$ = new StatementList();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    } 
    | statement
    {
        // statement_list -> statement
        $$ = new StatementList();
        $$->set_rownum(line_count);
        $$->append_child($1);
    };

statement : assignop_statement
    {   
        //statement -> AssignopStatement
        $$ = new Statement(Statement::StatementType::ASSIGN_OP_STATEMENT);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | procedure_call
    {
        // statement -> call_procedure_statement
        $$ = new Statement(Statement::StatementType::PROCEDURE_CALL);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | compound_statement
    {
        // statement -> compound_statement
        $$ = new Statement(Statement::StatementType::COMPOUND_STATEMENT);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | ifstatement
    {   
        // statement -> IF expression THEN statement else_part
        $$ = new Statement(Statement::StatementType::IF_STATEMENT);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | loopstatement
    {
        // statement -> CASE expression OF case_body END
        $$ = new Statement(Statement::StatementType::LOOP_STATEMENT);
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | 
    {
        // statement -> ε
        $$ = new Statement(Statement::StatementType::EPSILON);
        $$->set_rownum(line_count);
    };

assignop_statement : variable ASSIGNOP expression
    {
        // assignop_statement -> variable ASSIGNOP expression
        $$ = new AssignopStatement(AssignopStatement::LeftType::VARIABLE);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    };

procedure_call : ID
    {
        // procedure_call -> id
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
    }
    | ID '(' ')'
    {
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
    }
    | ID '(' expression_list ')'
    {
        // procedure_call -> id ( expression_list )
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
        $$->append_child($3);
    }
    /* | ID '(' variable_list ')'
    {
        // procedure_call -> id ( expression_list )
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::VAR_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
        $$->append_child($3);
    }; */

ifstatement : IF expression THEN statement else_part
    {
        // if_statement -> if expression then statement else_part
        $$ = new IfStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
        $$->append_child($5);
    };

else_part : 
    {
        // else_part -> ε | else statement
        $$ = new ElsePart(ElsePart::ELSEType::EPSILON);
        $$->set_rownum(line_count);
    }
    | ELSE statement
    {   
        // else_part -> else statement
        $$ = new ElsePart(ElsePart::ELSEType::ELSE_STATEMENT);
        $$->set_rownum(line_count);
        $$->append_child($2);
    };

loopstatement : WHILE expression DO statement
    {
        // statement -> WHILE expression DO statement
        $$ = new LoopStatement(LoopStatement::LoopType::WHILE_);
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);

    } 
    | REPEAT statement_list UNTIL expression
    {
        // statement -> repeat statement until expression
        $$ = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
    }
    | FOR ID ASSIGNOP expression DOWNTO expression DO statement
    {
        // statement -> FOR ID ASSIGNOP expression downto expression DO statement
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
    }
    | FOR ID ASSIGNOP expression TO expression DO statement
    {
        $$ = new LoopStatement(LoopStatement::LoopType::FORUP);
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
        $$->append_child($1);
    } 
    | variable_list ',' variable
    {
        // variable_list -> variable_list ',' variable
        $$ = new VariableList(VariableList::GrammarType::VAR_LIST_VAR);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    };

variable : ID id_varparts
    {
        // variable -> ID id_varparts
        $$ = new Variable();
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        $$->append_child(leaf_node);
        $$->append_child($2);
    }
    | ID '(' ')'
    {
        // variable -> ID id_varparts
        $$ = new Variable();
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        $$->append_child(leaf_node);
    };

id_varparts :
    {
        // id_varparts -> ε.
        $$ = new IDVarParts();
        $$->set_rownum(line_count);
        std::vector<std::string> *name_list = new std::vector<std::string>;
        $$->set_pointer(name_list);
    }
    | id_varparts id_varpart
    {
        // id_varparts -> id_varparts id_varpart.
        $$ = new IDVarParts();
        $$->set_rownum(line_count);
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
        $$->set_rownum(line_count);
        $$->append_child($2);
    }
    | '.' ID
    {
        // id_varpart -> .id.
        $$ = new IDVarPart(IDVarPart::GrammarType::_ID);
        $$->set_rownum(line_count);
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
        $$ = new Expression(Expression::GrammarType::DOUBLE, $2.value.get<string>(), "unknown");
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression CONSTASSIGNOP simple_expression
    {
        // expression -> simple_expression '=' simple_expression.
        $$ = new Expression(Expression::GrammarType::DOUBLE, "=", "unknown");
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression
    {
        // expression -> simple_expression.
        $$ = new Expression(Expression::GrammarType::SINGLE, " ", $1->GetExpType());
        $$->set_rownum(line_count);
        $$->append_child($1);
    };

simple_expression : term
    {   
        // simple_expression -> term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::SINGLE, $1->GetTerType());
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | PLUS term
    {
        // simple_expression -> + term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, $2->GetTerType());
        $$->set_rownum(line_count);
        $$->append_child($2);
    }
    | UMINUS term
    {
        // simple_expression -> - term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, $2->GetTerType());
        $$->set_rownum(line_count);
        $$->append_child($2);
    }
    | simple_expression ADDOP term
    {
        // simple_expression -> simple_expression or term.、
        $$ = new SimpleExpression(SimpleExpression::SymbolType::OR_, "unknown");
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression PLUS term
    { 
        // simple_expression -> simple_expression + term.
        $$ = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, "unknown");
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    }
    | simple_expression UMINUS term
    {
        $$ = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, "unknown");
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
    };

term : factor
    {   
        // term -> factor.
        
        $$ = new Term(Term::SymbolType::SINGLE, $1->GetFacType());
        $$->set_rownum(line_count);
        $$->append_child($1);
    }
    | term MULOP factor
    {  
        // term -> term mulop factor. 
        $$ = new Term;
        $$->set_rownum(line_count);
        std::string sym_type = $2.value.get<string>();
        if(sym_type == "*"){
            $$->SetSymType(Term::SymbolType::MULTIPLY);
            $$->SetTerType("unknown");
        }
        if(sym_type == "/"){
            $$->SetSymType(Term::SymbolType::DEVIDE);
            $$->SetTerType("unknown");
        }
        if(sym_type == "mod"){
            $$->SetSymType(Term::SymbolType::MOD);
            $$->SetTerType("unknown");
        }
        if(sym_type == "and"){
            $$->SetSymType(Term::SymbolType::AND);
            $$->SetTerType("unknown");
        }
        if(sym_type == "div"){
            $$->SetSymType(Term::SymbolType::DEVIDE);
            $$->SetTerType("unknown");
        }
        $$->append_child($1);
        $$->append_child($3);
    };

factor : INT_NUM
    {
        // factor -> num
        $$ = new Factor(Factor::GrammerType::NUM);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("integer");
        $$->append_child(leaf_node);
    }
    | REAL_NUM
    {   
        // factor -> num
        $$ = new Factor(Factor::GrammerType::NUM);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("real");
        $$->append_child(leaf_node);
    }
    | PLUS factor
    {
        // factor -> num
        $$ = new Factor(Factor::GrammerType::UPLUS);
        $$->set_rownum(line_count);
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    }
    | BOOL
    {
        // factor -> BOOL
        $$ = new Factor(Factor::GrammerType::BOOL);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("boolean");
        $$->append_child(leaf_node);
    }
    | STRING_
    {
    // factor -> STRING
        //字符
        $$ = new Factor(Factor::GrammerType::STR);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("string");
        $$->append_child(leaf_node);
    }
    | CHAR
    {
        // factor -> char
        $$ = new Factor(Factor::GrammerType::CHAR_);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::VALUE);
        $$->SetFacType("char");
        $$->append_child(leaf_node);
    }
    | variable
    {   
        // factor -> variable.
        $$ = new Factor(Factor::GrammerType::VARIABLE);
        $$->set_rownum(line_count);
        $$->SetFacType("unknown");
        $$->append_child($1);
    }
    |ID '(' expression_list ')'
    {
        $$ = new Factor(Factor::GrammerType::ID_EXP_LIST);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        $$->SetFacType("unknown");
        $$->append_child(leaf_node);
        $$->append_child($3);
    }
    | '(' expression ')'
    {
        // factor -> (expression).
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
    }
    | NOT factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(Factor::GrammerType::NOT_);
        $$->set_rownum(line_count);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    | UMINUS factor
    {   
        // factor -> not factor.
        // 类型检查
        $$ = new Factor(Factor::GrammerType::UMINUS_);
        $$->set_rownum(line_count);
        $$->SetUminus();
        $$->SetFacType($2->GetFacType());
        $$->append_child($2);
    };
    
/*---------------.
| Error handler  |
`---------------*/
program_head : PROGRAM error '(' id_list ')' ';'
    { //ERROR 缺少主程序名 
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("Grammar Error: missing program name", line_count);
    }
    | PROGRAM ID '(' id_list ')' error
    { //ERROR 缺少主程序名 
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("Grammar Error: missing semicolon", line_count);
    }
    | PROGRAM ID error id_list ')' ';'
    { //ERROR 缺少左括号 
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("Grammar Error: missing a left bracket", line_count);
    }
    | PROGRAM ID '(' error ')' ';'
    { //ERROR idlist识别失败 
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
    | PROGRAM ID '(' id_list error ';'
    { //ERROR 缺少右括号 
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("Grammar Error: missing a right bracket", line_count);
    }
    | PROGRAM error ';'
    { //ERROR program head 
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program head imcomplete", line_count);
    }
    |PROGRAM ID error ';'
    { //ERROR idlist缺失 
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
    |PROGRAM ID '(' error ';'
    { //ERROR idlist缺失 
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
    |PROGRAM ID error
    { //ERROR idlist缺失 
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        yyerror("Grammar Error: missing a semicolon", line_count - 1);
    }

const_declarations : CONST error ';' 
    { //ERROR 常量定义出现错误 
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: fatal error in const declarations", line_count);
    }
    | CONST const_declaration error 
    { //ERROR 缺少分号 
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("Grammar Error: missing a semicolon", line_count);
    };

const_declaration : const_declaration ';' ID CONSTASSIGNOP error
    { //常数初始化右值缺失 
        error_flag = 1;
        yyerror("Grammar Error: constant definition missing initial r-value", line_count);
    }
    | ID CONSTASSIGNOP error
    { //常数初始化右值缺失 
        error_flag = 1;
        yyerror("Grammar Error: constant definition missing initial r-value", line_count);
    }
    | const_declaration error ID '=' const_value
    { //ERROR 缺少分号 
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
    | const_declaration ';' ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） 
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("Grammar Error: missing a equal sign",line_count);
    }
    | ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） 
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("Grammar Error: missing a equal sign", line_count);
    };

var_declarations : VAR error
    { //ERROR 变量定义出现错误 
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: fatal error in variant declarations", line_count);
    }

var_declaration: var_declaration id_list ':' type error
    { //ERROR 缺少分号 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($4);
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
    | var_declaration id_list error type ';'
    { //ERROR 缺少冒号 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        $$->append_child($4);
        yyerror("Grammar Error: missing a colon", line_count);
    }
    | var_declaration id_list ':' error 
    { //ERROR type识别失败 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a type", line_count);
    }
    | id_list ':' error ';'
    { //ERROR type识别失败 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        error_flag = 1;
        yyerror("missing a type", line_count);
    }
    | id_list error type ';'
    { //ERROR 缺少冒号 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a colon", line_count);
    }
    | id_list ':' type error
    { //ERROR 缺少分号 
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a semicolon", line_count - 1);
    };

/*其他*/

array_type : ARRAY error periods ']' OF type
    { //ERROR 缺少左中括号 
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        if($6->GetVarType() == TypeNode::VarType::ID_TYPE){
            $$ -> set_type($6->get_type_name());
        }
        ArrayType* at = new ArrayType();
        at->SetDimension($3->get_dm());
        $$->set_info(at);
        $$->append_child($3);
        $$->append_child($6);
        yyerror("Grammar Error: missing a left square bracket", line_count);
    }
    | ARRAY '[' periods ']' error type
    { //ERROR 缺少OF关键字 
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        if($6->GetVarType() == TypeNode::VarType::ID_TYPE){
            $$ -> set_type($6->get_type_name());
        }
        ArrayType* at = new ArrayType();
        at->SetDimension($3->get_dm());
        $$->set_info(at);
        $$->append_child($3);
        $$->append_child($6);
        yyerror("Grammar Error: missing keyword \"OF\" ", line_count);
    } 
    | ARRAY '[' periods ']' OF error
    { //ERROR 数组元素类型识别失败 
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
    | ARRAY error
    { //ERROR 不完整的数组类型 
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type", line_count);
    }
    | ARRAY '[' error
    { //ERROR 不完整的数组类型 
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type", line_count);
    }
    | ARRAY '[' periods error
    { //ERROR 不完整的数组类型 
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type",line_count);
    };

periods : periods error period
    { //ERROR 缺少逗号 
        $$ = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        $$->set_rownum(line_count);
        std::vector<ArrayType::Dimension> dim;
        dim = $1->get_dm();
        ArrayType::Dimension nd($3->get_lowb(), $3->get_upb());
        dim.emplace_back(nd);
        $$->set_dm(dim);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a comma ", line_count);
    }

period : INT_NUM error INT_NUM
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        $$ = new PeriodNode($1.value.get<int>(), $3.value.get<int>());
        $$->set_rownum(line_count);
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
        yyerror("Grammar Error: missing range dot .. ", line_count);
    };

subprogram_declarations : subprogram_declarations subprogram_declaration error
    { //ERROR 缺少分号 
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        yyerror("Grammar Error: missing a semicolon", line_count);
    }

subprogram_head : FUNCTION ID formal_parameter ':' type error
    { //ERROR 缺少分号 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
         yyerror("Grammar Error: missing semicolon", line_count);
    }
    | FUNCTION error formal_parameter ':' type ';'
    { //ERROR 函数名缺失 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing function name", line_count);
    }
    | FUNCTION ID formal_parameter error type ';'
    { //ERROR 缺少冒号 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("Grammar Error: missing a colon", line_count);
    }
    | FUNCTION ID formal_parameter ':' error ';'
    { //ERROR 缺少基本类型关键字 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
    | FUNCTION ID formal_parameter error
    { //ERROR 缺少基本类型关键字 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag =1 ;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
    | PROCEDURE ID formal_parameter error
    { //ERROR 缺少分号 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
    | FUNCTION error 
    { //ERROR 不完整的函数头 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete function head", line_count);
    }
    | PROCEDURE error 
    { //ERROR 不完整的过程头 
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete procedure head", line_count);
    };

formal_parameter: '(' error
    { //ERROR 不完整的形参列表
        $$ = new FormalParam();
        $$->set_rownum(line_count);
        yyerror("Grammar Error: incomplete formal parameter list", line_count);
    }
    |'(' parameter_lists error
    { //ERROR 右括号缺失
        $$ = new FormalParam();
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("Grammar Error: missing a right bracket", line_count);
    };

parameter_lists : parameter_lists error parameter_list
    { //ERROR 缺少分号 
        $$ = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
		yyerror("Grammar Error: missing a semicolon", line_count);
	}

var_parameter : VAR error
    { //ERROR 不完整的引用参数列表 
        $$ = new VarParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete refereced parameter list", line_count);
	};

value_parameter : id_list error type
    { //ERROR 缺少分号 
       $$ = new ValueParam();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a colon", line_count);
    }
    | id_list ':' error
    { //ERROR 缺少基本类型关键字 
        $$ = new ValueParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
    | id_list error
    { //ERROR 缺少基本类型关键字 
        $$ = new ValueParam();
        error_flag = 1;
        $$->set_rownum(line_count);
        yyerror("Grammar Error: missing a base type keyword", line_count);
    };
compound_statement: BEGIN_ statement_list error
    { //ERROR 缺少END关键字  
        $$ = new CompoundStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("Grammar Error: missing keyword \"end\"", line_count);
	};

statement_list : statement_list error statement
    { //ERROR 缺失分号 这里引发了3个规约规约冲突  
        $$ = new StatementList();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a semicolon  ", line_count);
    };

ifstatement : IF expression error statement else_part
    { //ERROR 缺少then关键字  
        $$ = new IfStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
        $$->append_child($5);
        yyerror("Grammar Error: missing keyword \"then\"", line_count);
	}

loopstatement : FOR ID error expression TO expression DO statement
    { //ERROR 缺少赋值号  
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
        yyerror("Grammar Error: missing assignop \":=\"", line_count);
    }
    |FOR ID ASSIGNOP expression error expression DO statement
    { //ERROR 缺少关键字to  
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
        yyerror("Grammar Error: missing keywrod \"to\"", line_count);
    }
    |FOR ID ASSIGNOP expression TO expression error statement
    { //ERROR 缺少关键字do  
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
        yyerror("Grammar Error: missing keywrod \"do\"", line_count);
    }
    | WHILE expression error statement
    { //ERROR 缺少关键字do  
        $$ = new LoopStatement(LoopStatement::LoopType::WHILE_);
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
        yyerror("Grammar Error: missing keywrod \"do\"", line_count);
    }
    | REPEAT statement error expression
    { //ERROR 缺少关键字until  
        $$ = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
        yyerror("Grammar Error: missing keywrod \"until\"", line_count);
	}

procedure_call : ID '(' expression_list error
    { //ERROR 缺少右括号  
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
        $$->append_child($3);
        yyerror("Grammar Error: missing a right bracket", line_count);
    };

expression_list : expression_list error expression
    { //ERROR 缺少逗号 这里引发了一个移进规约冲突 
        std::vector<std::string> *type_list = $1->get_types();
        type_list->emplace_back($3->GetExpType());
        $$ = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("Grammar Error: missing a comma", line_count);
    };

id_varpart: '[' error
    { //ERROR 不完整的数组下标列表 
        $$ = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete expression list of array subindex", line_count);
    }
    |'[' expression_list error
    { //ERROR 缺失右中括号 
		$$ = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("Grammar Error: missing a right square bracket", line_count);
	};

factor: ID '(' expression_list error
    { //ERROR 缺少右括号 这里引发了一个移进规约冲突
        $$ = new Factor(Factor::GrammerType::ID_EXP_LIST);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        $$->SetFacType("unknown");
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("Grammar Error: missing a right bracket", line_count);
	}
    | ID '(' error
    { //ERROR 函数调用的表达式列表缺失
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing actual parameter list of function call", line_count);
	}
    |'(' expression error
    { //ERROR 缺少右括号
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
        yyerror("Grammar Error: missing a right bracket", line_count);
    };


%%
 

void yyerror(ast::AST* Ast,const char *msg){
    if(strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    
}

void yyerror(const char *s, int line){
	string errorInformation;//定义错误信息
	errorInformation += string(s);//添加错误信息
	cout << errorInformation << " at line " << line << endl;
}

int yywrap(){
    return 1;
} 