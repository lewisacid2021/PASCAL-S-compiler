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
    { //ERROR 缺少点号  
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("missing a dot  ", line_count);
    }
    | error program_body '.'
    { //ERROR program_head识别失败  
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($2);
        error_flag = 1;
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program head, maybe missing keyword \"program\"",line_count);
    }
    | program_head error '.'
    { //ERROR program_body识别失败 un 
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        error_flag = 1;
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program body", line_count);
    }

    /*定义语句相关*/

program_head : PROGRAM error '(' id_list ')' ';'
    { //ERROR 缺少主程序名  
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing program name  ", line_count);
    }
    | PROGRAM ID error id_list ')' ';'
    { //ERROR 缺少左括号  
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a left bracket  ", line_count);
    }
    | PROGRAM ID '(' error ')' ';'
    { //ERROR id_list识别失败  
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    }
    | PROGRAM ID '(' id_list error ';'
    { //ERROR 缺少右括号  
        $$ = new ProgramHead();
        LeafNode* leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child($4);
        $$->append_child(leaf_node);
        $$->set_rownum(line_count);
        yyerror("missing a right bracket  ", line_count);
    }
    | PROGRAM error ';'
    { //ERROR program head  
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program head imcomplete", line_count);
    }
    |PROGRAM ID error ';'
    { //ERROR id_list缺失  
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    }
    |PROGRAM ID '(' error ';'
    { //ERROR id_list缺失  
        $$ = new ProgramHead();
        error_flag = 1;
        yyerror("program identifier list missing or imcomplete", line_count);
    };

const_declarations : CONST error ';' 
    { //ERROR 常量定义出现错误  
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("fatal error in const declarations", line_count);
    }
    | CONST const_declaration error 
    { //ERROR 缺少分号  
        $$ = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a semicolon  ", line_count);
    };

const_declaration : const_declaration ';' ID CONSTASSIGNOP error
    { //常数初始化右值缺失  
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, $5->type());
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("constant definition missing initial r-value", line_count);
    }
    | ID CONSTASSIGNOP error
    { //常数初始化右值缺失  
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("constant definition missing initial r-value", line_count);
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
        yyerror("missing a semicolon  ", line_count);
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
        yyerror("missing a equal sign  ",line_count);
    }
    | ID error const_value
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号）  
        $$ = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, $3->type());
        $$->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode($1.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        leaf_node = new LeafNode(*$3, LeafNode::LeafType::VALUE);
        $$->append_child(leaf_node);
        yyerror("missing a equal sign  ", line_count);
    };

var_declarations : VAR error ';'
    { //ERROR 变量定义出现错误  
        $$ = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("fatal error in variant declarations", line_count);
    }

var_declaration: var_declaration id_list ':' type error
    { //ERROR 缺少分号  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a semicolon  ", line_count);
    }
    | var_declaration id_list error type ';'
    { //ERROR 缺少冒号  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        $$->append_child($5);
        yyerror("missing a colon  ", line_count);
    }
    | var_declaration id_list ':' error 
    { //ERROR type识别失败  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a type  ", line_count);
    }
    | id_list ':' error ';'
    { //ERROR type识别失败  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        yyerror("missing a type  ", line_count);
    }
    |id_list error type ';'
    { //ERROR 缺少冒号  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon  ", line_count);
    }
    |id_list ':' type ';'
    { //ERROR 缺少冒号  
        $$ = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon  ", line_count);
    };

/*其他*/

array_type : ARRAY error period ']' OF type
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
        yyerror("missing a left square bracket", line_count);
    }
    | ARRAY '[' period ']' error type
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
        yyerror("missing keyword \"OF\" ", line_count);
    } 
    | ARRAY '[' period ']' OF error
    { //ERROR 数组元素类型识别失败  
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("missing a base type keyword", line_count);
    }
    | ARRAY error
    { //ERROR 不完整的数组类型  
        $$ = new ArrayTypeNode();
        error_flag = 1;
        yyerror("incomplete array type", line_count);
    }
    | ARRAY '[' error
    { //ERROR 不完整的数组类型  
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete array type", line_count);
    }
    | ARRAY '[' period error
    { //ERROR 不完整的数组类型  
        $$ = new ArrayTypeNode();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete array type",line_count);
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
        yyerror("missing a comma  ", line_count);
    }

period : INT_NUM error INT_NUM
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        $$ = new PeriodNode($1.value.get<int>(), $3.value.get<int>());
        $$->set_rownum(line_count);
        $$->append_child(new LeafNode($1.value.get<int>(), LeafNode::LeafType::VALUE));
        $$->append_child(new LeafNode($3.value.get<int>(), LeafNode::LeafType::VALUE));
        yyerror("missing range dot ..  ", line_count);
    };

subprogram_declarations : subprogram_declarations subprogram error
    { //ERROR 缺少分号  
        $$ = new SubprogramDeclarations();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($2);
        yyerror("missing a semicolon", line_count);
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
    }
    | FUNCTION error formal_parameter ':' TYPE ';'
    { //ERROR 函数名缺失  
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing function name", line_count);
    }
    | FUNCTION ID formal_parameter error TYPE ';'
    { //ERROR 缺少冒号  
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
    { //ERROR 缺少基本类型关键字  
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a base type keyword  ", line_count);
    }
    | FUNCTION ID formal_parameter error
    { //ERROR 缺少基本类型关键字  
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a base type keyword  ", line_count);
    }
    | PROCEDURE ID formal_parameter error
    { //ERROR 缺少分号  
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        $$->set_id($2.value.get<string>());
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME);
        $$->append_child(leaf_node);
        $$->append_child($3);
        yyerror("missing a semicolon", line_count);
    }
    | FUNCTION error 
    { //ERROR 不完整的函数头  
        $$ = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete function head", &@$);
    }
    | PROCEDURE error 
    { //ERROR 不完整的过程头  
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
        yyerror("missing a right bracket  ", line_count);
    };

parameter_lists : parameter_lists error arameter_list
    { //ERROR 缺少分号  
        $$ = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
		yyerror("missing a semicolon  ", line_count);
	}

var_parameter : VAR error
    { //ERROR 不完整的引用参数列表  
        $$ = new VarParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete refereced parameter list", line_count);
	};

value_parameter : id_list error type
    { //ERROR 缺少分号  
        $$=new Type;
        $$->token="value_parameter";
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a colon  ", line_count);
    }
    | id_list ':' error
    { //ERROR 缺少基本类型关键字  
        $$ = new ValueParam();
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing a base type keyword  ", line_count);
    }
    | id_list error
    { //ERROR 缺少基本类型关键字  
        $$ = new ValueParam();
        error_flag = 1;
        $$->set_rownum(line_count);
        yyerror("missing a base type keyword  ", line_count);
    };


/*statement相关*/
// compound_statement: BEGIN_ statement_list END
// IF expression THEN statement else_part
compound_statement: BEGIN_ statement_list error
    { //ERROR 缺少END关键字  
        $$ = new CompoundStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing keyword \"end\"", line_count);
	};

statement_list : statement_list error statement
    { //ERROR 缺失分号 这里引发了3个规约规约冲突  
        $$ = new StatementList();
        $$->set_rownum(line_count);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a semicolon  ", line_count);
    };

ifstatement : IF expression error statement else_part
    { //ERROR 缺少then关键字  
        $$ = new IfStatement();
        $$->set_rownum(line_count);
        $$->append_child($2);
        $$->append_child($4);
        $$->append_child($5);
        yyerror("missing keyword \"then\"", line_count);
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
        yyerror("missing assignop \":=\"", line_count);
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
        yyerror("missing keywrod \"to\"", line_count);
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
        yyerror("missing keywrod \"do\"", line_count);
    }
    | WHILE expression error statement
    { //ERROR 缺少关键字do  
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
        yyerror("missing keywrod \"do\"", line_count);
    }
    | REPEAT statement error expression
    { //ERROR 缺少关键字until  
        $$ = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        $$->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode($2.value, LeafNode::LeafType::NAME); 
        $$->append_child(leaf_node);
        $$->append_child($4);
        $$->append_child($6);
        $$->append_child($8);
        yyerror("missing keywrod \"until\"", line_count);
	}

procedure_call : ID '(' expression_list error
    { //ERROR 缺少右括号  
        $$ = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, $1.value.get<string>());
        $$->set_rownum(line_count);
        $$->append_child($3);
        yyerror("missing a right bracket", line_count);
    };

expression_list : expression_list error expression
    { //ERROR 缺少逗号 这里引发了一个移进规约冲突 checked
        std::vector<std::string> *type_list = $1->get_types();
        type_list->emplace_back($3->GetExpType());
        $$ = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        $$->append_child($1);
        $$->append_child($3);
        yyerror("missing a comma", line_count);
    };

id_varpart: '[' error
    { //ERROR 不完整的数组下标列表 checked
        $$ = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("incomplete expression list of array subindex", line_count);
    }
    |'[' expression_list error
    { //ERROR 缺失右中括号 checked
		$$ = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        $$->set_rownum(line_count);
        $$->append_child($2);
        yyerror("missing a right square bracket", line_count);
	};

factor: ID '(' expression_list error
    { //ERROR 缺少右括号 这里引发了一个移进规约冲突
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
        yyerror("missing a right bracket here", line_count);
	}
    | ID '(' error
    { //ERROR 函数调用的表达式列表缺失
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        error_flag = 1;
        yyerror("missing actual parameter list of function call", line_count);
	}
    |'(' expression error
    { //ERROR 缺少右括号
        $$ = new Factor(Factor::GrammerType::EXP);
        $$->set_rownum(line_count);
        $$->SetFacType($2->GetExpType());
        $$->append_child($2);
        yyerror("missing a right bracket here", line_count);
    };


%%
 

void yyerror(ast::AST* real_ast,const char *msg){
    if(yydebug || strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void yynote(std::string msg ,int line){
    fprintf(stderr,"%d:\033[01;32m \tnote\033[0m : previous definition of \"%s\" was  \n", line, msg.c_str());
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