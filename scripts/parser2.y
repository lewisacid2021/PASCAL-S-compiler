/*--紧急恢复--*/
program : error
    {
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
    };
/*--短语级恢复--*/

    /*PROGRAM相关错误*/

program_head : PROGRAM error
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

programstruct : program_head program_body error
    { //ERROR 缺少点号 checked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("missing a dot here", line_count);
    }
    | error program_body '.'
    { //ERROR program_head识别失败 checked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($2);
        error_flag = 1;
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program head, maybe missing keyword \"program\"",line_count);
    }
    | program_head error '.'
    { //ERROR program_body识别失败 unchecked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        error_flag = 1;
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program body", line_count);
    }

    /*定义语句相关*/

program_head : PROGRAM error '(' id_list ')' ';'
    { //ERROR 缺少主程序名 checked
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing program name here", line_count);
    }
    | PROGRAM ID error id_list ')' ';'
    { //ERROR 缺少左括号 checked
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a left bracket here", line_count);
    }
    | PROGRAM ID '(' error ')' ';'
    { //ERROR id_list识别失败 checked
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    }
    | PROGRAM ID '(' id_list error ';'
    { //ERROR 缺少右括号 checked
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a right bracket here", line_count);
    }
    | PROGRAM error ';'
    { //ERROR program head checked
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program head imcomplete", line_count);
    }
    |PROGRAM ID error ';'
    { //ERROR id_list缺失 checked
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    }
    |PROGRAM ID '(' error ';'
    { //ERROR id_list缺失 checked
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    };

const_declarations : CONST error ';' 
    { //ERROR 常量定义出现错误 checked
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("fatal error in const declarations", line_count);
    }
    | CONST const_declaration error 
    { //ERROR 缺少分号 checked
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a semicolon here", line_count);
    };

const_declaration : const_declaration ';' ID CONSTASSIGNOP error
    { //常数初始化右值缺失 checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("constant definition missing initial r-value", line_count);
    }
    | ID CONSTASSIGNOP error
    { //常数初始化右值缺失 checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("constant definition missing initial r-value", line_count);
    }
    | const_declaration error ID '=' const_value
    { //ERROR 缺少分号 checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("missing a semicolon here", line_count);
    }
    | const_declaration ';' ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$5, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("missing a equal sign here",line_count);
    }
    | ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("missing a equal sign here", line_count);
    };

var_declarations : VAR error ';'
    { //ERROR 变量定义出现错误 checked
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("fatal error in variant declarations", line_count);
    }

var_declaration: var_declaration id_list ':' type error
    { //ERROR 缺少分号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a semicolon here", line_count);
    }
    | var_declaration id_list error type ';'
    { //ERROR 缺少冒号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a colon here", line_count);
    }
    | var_declaration id_list ':' error 
    { //ERROR type识别失败 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a type here", line_count);
    }
    | id_list ':' error ';'
    { //ERROR type识别失败 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        yyerror("missing a type here", line_count);
    }
    |id_list error type ';'
    { //ERROR 缺少冒号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon here", line_count);
    }
    |id_list ':' type ';'
    { //ERROR 缺少冒号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon here", line_count);
    };

/*其他*/

array_type : ARRAY error period ']' OF type
    { //ERROR 缺少左中括号 checked
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
        yyerror("missing a left square bracket", line_count);
    }
    | ARRAY '[' period ']' error type
    { //ERROR 缺少OF关键字 checked
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
        yyerror("missing keyword \"OF\" ", line_count);
    } 
    | ARRAY '[' period ']' OF error
    { //ERROR 数组元素类型识别失败 checked
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("missing a base type keyword", line_count);
    }
    | ARRAY error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("incomplete array type", line_count);
    }
    | ARRAY '[' error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete array type", line_count);
    }
    | ARRAY '[' period error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete array type",line_count);
    };

periods : periods error period
    { //ERROR 缺少逗号 checked
        $$ = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        $$->set_rownum(line_count);
        std::vector<ArrayType::Dimension> dim;
        dim = $1->get_dm();
        ArrayType::Dimension nd($3->get_lowb(), $3->get_upb());
        dim.emplace_back(nd);
        $$->set_dm(dim);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a comma here", line_count);
    }

period : INT_NUM error INT_NUM
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        $$ = new PeriodNode($1.value.get<int>(), $3.value.get<int>());
        $$->set_rownum(line_count);
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
        yyerror("missing range dot .. here", line_count);
    };

subprogram_declarations : subprogram_declarations subprogram error
    { //ERROR 缺少分号 checked
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        yyerror("missing a semicolon", line_count);
    }

subprogram_head : FUNCTION ID formal_parameter ':' type error
    { //ERROR 缺少分号 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
    }
    | FUNCTION error formal_parameter ':' TYPE ';'
    { //ERROR 函数名缺失 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing function name", line_count);
    }
    | FUNCTION ID formal_parameter error TYPE ';'
    { //ERROR 缺少冒号 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a colon", line_count);
    }
    | FUNCTION ID formal_parameter ':' error ';'
    { //ERROR 缺少基本类型关键字 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a base type keyword here", line_count);
    }
    | FUNCTION ID formal_parameter error
    { //ERROR 缺少基本类型关键字 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a base type keyword here", line_count);
    }
    | PROCEDURE ID formal_parameter error
    { //ERROR 缺少分号 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a semicolon", line_count);
    }
    | FUNCTION error 
    { //ERROR 不完整的函数头 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete function head", &@$);
    }
    | PROCEDURE error 
    { //ERROR 不完整的过程头 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        $$->set_rownum(line_count);
        yyerror("incomplete procedure head", &@$);
    };

formal_parameter: '(' error
    { //ERROR 不完整的形参列表
        $$ = new FormalParam();
        $$->set_rownum(line_count);
        yyerror("incomplete formal parameter list", line_count);
    }
    |'(' parameter_lists error
    { //ERROR 右括号缺失
        $$ = new FormalParam();
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a right bracket here", line_count);
    };

parameter_lists : parameter_lists error arameter_list
    { //ERROR 缺少分号 checked
        $$ = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
		yyerror("missing a semicolon here", line_count);
	}

var_parameter : VAR error
    { //ERROR 不完整的引用参数列表 checked
        $$ = new VarParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete refereced parameter list", line_count);
	};

value_parameter : id_list error type
    { //ERROR 缺少分号 checked
        $$=new Type;
        $$->token="value_parameter";
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon here", line_count);
    }
    | id_list ':' error
    { //ERROR 缺少基本类型关键字 checked
        $$ = new ValueParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a base type keyword here", line_count);
    }
    | id_list error
    { //ERROR 缺少基本类型关键字 checked
        $$ = new ValueParam();
        error_flag = 1;
        $$->set_rownum(line_count);
        yyerror("missing a base type keyword here", line_count);
    };


/*statement相关*/
// compound_statement: BEGIN_ statement_list END
// IF expression THEN statement else_part
compound_statement: _BEGIN statement_list error{ //ERROR 缺少END关键字 checked
						$$=new Type;
						$$->token="compound_statement";
						yyerror("missing keyword \"end\"", line_count);
					};

statement_list: statement_list error statement
    { //ERROR 缺失分号 这里引发了3个规约规约冲突 checked
					$$=new Type;
					$$->token="statement_list";
					yyerror("missing a semicolon here", line_count);
				}
ifstatement : IF expression error statement else_part
    { //ERROR 缺少then关键字 checked
        $$=new Type;
        $$->token="statement";
        yyerror("missing keyword \"then\"", line_count);
	}
loopstatement : FOR IDENTIFIER error expression TO expression DO statement{ //ERROR 缺少赋值号 checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing assignop \":=\"", line_count);
			}|FOR IDENTIFIER ASSIGNOP expression error expression DO statement{ //ERROR 缺少关键字to checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"to\"", line_count);
			}|FOR IDENTIFIER ASSIGNOP expression TO expression error statement{ //ERROR 缺少关键字do checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"do\"", @6.last_line, @4.last_column+1);
			}|WHILE expression error statement{ //ERROR 缺少关键字do checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"do\"", line_count);
			}|REPEAT statement error expression{ //ERROR 缺少关键字until checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"until\"", @4.first_line, @4.first_column);
			}

procedure_call: IDENTIFIER{ //正常
				$$=new Type;
				$$->token="procedure_call";
				$$->children.push_back($1);
			}
            |IDENTIFIER '(' expression_list ')'
            { //正常
				$$=new Type;
				$$->token="procedure_call";
				$$->children.push_back($1);$$->children.push_back($2);
				$$->children.push_back($3);$$->children.push_back($4);
			}
            |IDENTIFIER '(' expression_list error
            { //ERROR 缺少右括号 checked
				$$=new Type;
				$$->token="procedure_call";
				yyerror("missing a right bracket here", line_count);
			};
// REPEAT statement_list UNTIL expression

    

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

statement:FOR ID ASSIGNOP expression updown error
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