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
        yyerror("missing a dot here", @3.last_line, @3.last_column+1);
    }
    | error program_body '.'
    { //ERROR program_head识别失败 checked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program head, maybe missing keyword \"program\"",@1.first_line, @1.first_column, @1.last_line, @1.last_column);
    }
    | program_head error '.'
    { //ERROR program_body识别失败 unchecked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program body");
    }

    /*定义语句相关*/

program_head : PROGRAM error '(' idlist ')'
    { //ERROR 缺少主程序名 checked
        $$ = new ProgramHead();
        yyerror("missing program name here", @1.last_line, @1.last_column+1);
    }
    | PROGRAM ID error idlist ')'
    { //ERROR 缺少左括号 checked
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a left bracket here", @4.first_line, @4.first_column-1);
    }
    | PROGRAM ID '(' error ')'
    { //ERROR idlist识别失败 checked
        $$ = new ProgramHead();
        yyerror("program identifier list missing or imcomplete", @4.first_line, @4.first_column, @4.last_line, @4.last_column);
    }
    | PROGRAM IDENTIFIER '(' idlist error
    { //ERROR 缺少右括号 checked
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a right bracket here", @4.last_line, @4.last_column+1);
    }
    | PROGRAM error
    { //ERROR program head checked
        $$ = new ProgramHead();
        yyerror("program head imcomplete", @1.first_line, @1.first_column, @1.last_line, @1.last_column);
    }
    |PROGRAM ID error
    { //ERROR idlist缺失 checked
        $$ = new ProgramHead();
        yyerror("program identifier list missing or imcomplete", @1.first_line, @1.first_column, @2.last_line, @2.last_column);
    }
    |PROGRAM ID '(' error
    { //ERROR idlist缺失 checked
        $$ = new ProgramHead();
        yyerror("program identifier list missing or imcomplete", @1.first_line, @1.first_column, @2.last_line, @2.last_column);
    };

const_declarations : CONST error ';' 
    { //ERROR 常量定义出现错误 checked
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
        yyerror("fatal error in const declarations", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
    }
    | CONST const_declaration error 
    { //ERROR 缺少分号 checked
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a semicolon here", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
    };

const_declaration : const_declaration ';' ID '=' error
    { //常数初始化右值缺失 checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        $$->append_child($1);
        LeafNode* leaf_node = new LeafNode($3.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        yyerror("constant definition missing initial r-value", @4.first_line, @4.first_column, @4.last_line, @4.last_column);
    }
    | ID '=' error
    { //常数初始化右值缺失 checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        yyerror("constant definition missing initial r-value", @3.first_line, @3.first_column, @3.last_line, @3.last_column);
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
        yyerror("missing a semicolon here", @1.first_line, @1.first_column, @1.last_line, @1.last_column+1);
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
        yyerror("missing a equal sign here",@3.first_line, @3.first_column, @3.last_line, @3.last_column);
    }
    | ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） checked
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("missing a equal sign here", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
    };

var_declarations : VAR error ';'
    { //ERROR 变量定义出现错误 checked
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        yyerror("fatal error in variant declarations", @1.first_line, @1.first_column, @1.last_line, @1.last_column);
    }
    | VAR var_declaration error
    { //ERROR 缺少分号 checked
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a semicolon here", @2.last_line, @2.last_column+1);
    };

var_declaration: var_declaration error idlist ':' type 
    { //ERROR 缺少分号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a semicolon here", @1.last_line, @1.last_column+1);
    }
    | var_declaration ';' idlist error type 
    { //ERROR 缺少冒号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a colon here", @3.last_line, @3.last_column+1);
    }
    | var_declaration ';' idlist ':' error 
    { //ERROR type识别失败 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a type here", @4.last_line, @4.last_column+1);
    }
    |idlist ':' error 
    { //ERROR type识别失败 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        yyerror("missing a type here", @3.last_line, @3.last_column+1);
    }
    |idlist error type 
    { //ERROR 缺少分号 checked
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon here", @1.last_line, @1.last_column+1);
    };

/*其他*/

array_type : ARRAY error period ']' OF TYPE
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
        yyerror("missing a left square bracket here", @1.last_line, @1.last_column+1);
    }
    | ARRAY '[' period ']' error TYPE
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
        yyerror("missing keyword \"OF\" here", @4.last_line, @4.last_column+1, @6.first_line, @6.first_column-1);
    } 
    | ARRAY '[' period ']' OF error
    { //ERROR 数组元素类型识别失败 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        ArrayType* at = new ArrayType();
        at->SetDimension($3->get_dm());
        $$->set_info(at);
        $$->append_child($3);
        yyerror("missing a base type keyword here", @5.last_line, @5.last_column+1);
    }
    | ARRAY error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        yyerror("incomplete array type", &@$);
    }
    | ARRAY '[' error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        yyerror("incomplete array type", &@$);
    }
    | ARRAY '[' period error
    { //ERROR 不完整的数组类型 checked
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        yyerror("incomplete array type", &@$);
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
        yyerror("missing a comma here", @1.last_line, @1.last_column+1);
    }

period : INT_NUM error INT_NUM
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        $$ = new PeriodNode($1.value.get<int>(), $3.value.get<int>());
        $$->set_rownum(line_count);
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
        yyerror("missing range dot .. here", @3.last_line, @3.last_column+1);
    };

subprogram_declarations : subprogram_declarations subprogram error
    { //ERROR 缺少分号 checked
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        yyerror("missing a semicolon here", @2.last_line, @2.last_column+1);
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
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing function name", @1.last_line, @1.last_column+1);
    }
    | FUNCTION IDENTIFIER formal_parameter error TYPE ';'
    { //ERROR 缺少冒号 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a colon here", @3.last_line, @3.last_column);
    }
    | FUNCTION IDENTIFIER formal_parameter ':' error ';'
    { //ERROR 缺少基本类型关键字 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a base type keyword here", @4.last_line, @4.last_column+1);
    }
    | FUNCTION IDENTIFIER formal_parameter error
    { //ERROR 缺少基本类型关键字 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a base type keyword here", @3.last_line, @3.last_column+1);
    }
    | FUNCTION error 
    { //ERROR 不完整的函数头 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("incomplete function head", &@$);
    }
    | PROCEDURE error 
    { //ERROR 不完整的过程头 checked
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        $$->set_rownum(line_count);
        yyerror("incomplete procedure head", &@$);
    };

var_parameter: 	VAR value_parameter
    { //正常
        $$=new Type;
        $$->token="var_parameter";
        $$->children.push_back($1);$$->children.push_back($2);
    }
    | VAR error
    { //ERROR 不完整的引用参数列表 checked
        $$=new Type;
        $$->token="var_parameter";
        yyerror("incomplete refereced parameter list", &@$);
    };

formal_parameter: '(' error
    { //ERROR 不完整的形参列表
        $$=new Type;
        $$->token="formal_parameter";
        yyerror("incomplete formal parameter list", &@$);
    }
    |'(' parameter_list error
    { //ERROR 右括号缺失
        $$=new Type;
        $$->token="formal_parameter";
        yyerror("missing a right bracket here", @2.last_line, @2.last_column+1);
    };

parameter_list: parameter_list ';' parameter{ //正常
					$$=new Type;
					$$->token="parameter_list";
					$$->children.push_back($1);$$->children.push_back($2);$$->children.push_back($3);
				}|parameter_list error parameter{ //ERROR 缺少分号 checked
					$$=new Type;
					$$->token="parameter_list";
					yyerror("missing a semicolon here", @1.last_line, @1.last_column+1);
				}|parameter{ //正常
					$$=new Type;
					$$->token="parameter_list";
					$$->children.push_back($1);
				};

var_parameter: 	VAR error{ //ERROR 不完整的引用参数列表 checked
					$$=new Type;
					$$->token="var_parameter";
					yyerror("incomplete refereced parameter list", &@$);
				};

value_parameter: 	idlist error TYPE{ //ERROR 缺少分号 checked
						$$=new Type;
						$$->token="value_parameter";
						yyerror("missing a colon here", @1.first_line, @1.last_column+1);
					}|idlist ':' error{ //ERROR 缺少基本类型关键字 checked
						$$=new Type;
						$$->token="value_parameter";
						yyerror("missing a base type keyword here", @2.last_line, @2.last_column+1);
					}|idlist error{ //ERROR 缺少基本类型关键字 checked
						$$=new Type;
						$$->token="value_parameter";
						yyerror("missing a base type keyword here", @1.last_line, @1.last_column+1);
					};


/*statement相关*/
// compound_statement: BEGIN_ statement_list END
// IF expression THEN statement else_part
compound_statement: _BEGIN statement_list error{ //ERROR 缺少END关键字 checked
						$$=new Type;
						$$->token="compound_statement";
						yyerror("missing keyword \"end\"", @2.last_line, @2.last_column+1);
					};

statement_list: statement_list error statement
    { //ERROR 缺失分号 这里引发了3个规约规约冲突 checked
					$$=new Type;
					$$->token="statement_list";
					yyerror("missing a semicolon here", @1.last_line, @1.last_column+1);
				}
ifstatement : IF expression error statement else_part
    { //ERROR 缺少then关键字 checked
        $$=new Type;
        $$->token="statement";
        yyerror("missing keyword \"then\"", @2.last_line, @2.last_column+1);
	}
loopstatement : FOR IDENTIFIER error expression TO expression DO statement{ //ERROR 缺少赋值号 checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing assignop \":=\"", @2.last_line, @2.last_column+1);
			}|FOR IDENTIFIER ASSIGNOP expression error expression DO statement{ //ERROR 缺少关键字to checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"to\"", @4.last_line, @4.last_column+1);
			}|FOR IDENTIFIER ASSIGNOP expression TO expression error statement{ //ERROR 缺少关键字do checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"do\"", @6.last_line, @4.last_column+1);
			}|WHILE expression error statement{ //ERROR 缺少关键字do checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"do\"", @2.last_line, @2.last_column+1);
			}|REPEAT statement error expression{ //ERROR 缺少关键字until checked
				$$=new Type;
				$$->token="statement";
				yyerror("missing keywrod \"until\"", @4.first_line, @4.first_column);
			}

procedure_call: IDENTIFIER{ //正常
				$$=new Type;
				$$->token="procedure_call";
				$$->children.push_back($1);
			}|IDENTIFIER '(' expression_list ')'{ //正常
				$$=new Type;
				$$->token="procedure_call";
				$$->children.push_back($1);$$->children.push_back($2);
				$$->children.push_back($3);$$->children.push_back($4);
			}|IDENTIFIER '(' expression_list error{ //ERROR 缺少右括号 checked
				$$=new Type;
				$$->token="procedure_call";
				yyerror("missing a right bracket here", @3.last_line, @3.last_column+1);
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