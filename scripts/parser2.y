/*--紧急恢复--*/
program : error
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

programstruct : program_head ';' program_body error
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
    | program_head ';' error '.'
    { //ERROR program_body识别失败 unchecked
        ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child($1);
        headnode->append_child($2);
        $$->set_rownum(line_count);
        Ast->set_root(headnode);
        yyerror("fatal error in program body");
    }
    |error program_head ';' program_body '.'
    { //ERROR program_head前包含非法字符 checked
        ParseTreeHead=$$=new Type;
        $$->token = "programstruct";
        yyerror("invalid symbol before program head", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
    }|error program_head error program_body '.'{ //ERROR program_head前包含非法记号、缺失分号 checked
        ParseTreeHead=$$=new Type;
        $$->token = "programstruct";
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yyerror("missing a semicolon here", @2.last_line, @2.last_column+1);
    }|error program_head ';' program_body error{ //ERROR program_head前包含非法记号、缺失点号 checked
        ParseTreeHead=$$=new Type;
        $$->token = "programstruct";
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yyerror("missing a dot here", @4.last_line, @4.last_column+1);
    }|error program_head ';' error '.'{ //ERROR program_head前包含非法记号、program_body识别失败 unchecked
        ParseTreeHead=$$=new Type;
        $$->token = "programstruct";
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yyerror("fatal error in program body", @3.last_line, @3.last_column+1, @5.first_line, @5.first_column-1);
    };

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

var_declaration : id_list ':' error
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