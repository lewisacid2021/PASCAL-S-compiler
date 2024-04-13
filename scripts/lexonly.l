%option case-insensitive 
%{   
//#include "parser.h"
//#include "log.h"
//#include "parser.tab.h"
    
int line_count = 1;             // 当前行 号
int char_count = 1;             // 当前列 号
int left_brackets_num = 0;      // 当前未被匹配的左小括号数
int left_Mbrackets_num = 0;     // 当前未被匹配的左中括号数
bool new_line_flag;             // 标志换行符的读入 
int i;
int last_line_count;            // 当前行的前一个非空行 号
std::string cur_line_info;      // 当前行已读入信息
std::string last_line_info;     // 当前行的前一个非空行 信息
int lex_error_flag = 0;         // 标志词法分析过程中是否出现错误

void wrap();
void skip_error_token();
void skip_anno();
void write_cache();
void print_syntax_error(const char *msg);
void print_lex_error(const char *msg);

void to_str();
void to_str_case_sensitive();
void to_int();
void to_float();
void to_char();

extern "C"
{
    int yywrap();
    int yylex();
    void yyerror(const char *s);
}

%}

delim                   [ ]
white_spaces            {delim}+
letter                  [a-zA-Z]
digit                   [0-9]
digits                  {digit}+
fraction                (\.{digits})

/* 保留字 */
ARRAY                   "array"
BEGIN_                  "begin"
CASE                    "case"
CONST                   "const"
DO                      "do"
DOWNTO                  "downto"
ELSE                    "else"
END                     "end"
FOR                     "for"
FUNCTION                "function"
IF                      "if"
NOT                     "not"
OF                      "of"
PROCEDURE               "procedure"
PROGRAM                 "program"
RECORD                  "record"
REPEAT                  "repeat"
THEN                    "then"
TO                      "to"
TYPE                    "type"
UNTIL                   "until"
VAR                     "var"
WHILE                   "while"

/* 运算符 */
PLUS                    "+"
UMINUS                  "-"
CONSTASSIGNOP           "="
RELOP                   ("<>"|"<"|"<="|">"|">=")      
ADDOP                   "or"
MULOP                   ("*"|"/"|"div"|"mod"|"and")
ASSIGNOP                ":="

/* 常数 */
INT_NUM                 {digits}
REAL_NUM                {digits}{fraction}

/* 注释 */
ANNO                    (\{|\(\*)[^\{\}(\(\*)(\*\))]*(\}|\*\))

/* 标识符 */
ID                      {letter}({letter}|{digit})*

/* 字符 */
CHAR                    ('[^'\n]')

/*字符串*/
STRING_                 (\'([^\\\'\n]|(\\.)){2,}\')


/* 分隔符 */
SEP                     (";"|"."|","|":")
SUBCATALOG              ".."
  
%% 
"\t"                    { write_cache(); char_count += 4; }
"\n"                    { wrap(); new_line_flag = true;}
{white_spaces}          { write_cache(); char_count += yyleng; }

{PROGRAM}               { write_cache(); to_str(); }
{CONST}                 { write_cache(); to_str(); }
{TYPE}                  { write_cache(); to_str(); }
{ARRAY}                 { write_cache(); to_str(); }
{RECORD}                { write_cache(); to_str(); }
{OF}                    { write_cache(); to_str(); }
{VAR}                   { write_cache(); to_str(); }
{FUNCTION}              { write_cache(); to_str(); }
{PROCEDURE}             { write_cache(); to_str(); }
{BEGIN_}                { write_cache(); to_str(); }
{END}                   { write_cache(); to_str();  }
{IF}                    { write_cache(); to_str(); }
{THEN}                  { write_cache(); to_str(); }
{ELSE}                  { write_cache(); to_str(); }
{CASE}                  { write_cache(); to_str(); }
{WHILE}                 { write_cache(); to_str(); }
{REPEAT}                { write_cache(); to_str();  }
{UNTIL}                 { write_cache(); to_str(); }
{FOR}                   { write_cache(); to_str();  }
{TO}                    { write_cache(); to_str(); }
{DOWNTO}                { write_cache(); to_str(); }
{DO}                    { write_cache(); to_str(); }

{NOT}                   { write_cache(); to_str();}
{PLUS}                  { write_cache(); to_str(); }
{UMINUS}                { write_cache(); to_str();  }

{INT_NUM}               { write_cache(); to_int(); }
{REAL_NUM}              { write_cache(); to_float(); }

{ANNO}                { skip_anno(); }

{CHAR}                  { write_cache(); to_char(); }
{STRING_}               { write_cache(); to_str_case_sensitive();}

{RELOP}                 { write_cache(); to_str();  }
{ADDOP}                 { write_cache(); to_str();  }
{MULOP}                 { write_cache(); to_str();  }
{ASSIGNOP}              { write_cache(); to_str(); }

{ID}                    { write_cache(); to_str(); }

{CONSTASSIGNOP}         { write_cache(); to_str(); }
{SEP}                   { write_cache(); to_str(); }
{SUBCATALOG}            { write_cache(); to_str();  }

("[")                   { write_cache(); to_str(); }    
("(")                   { write_cache(); to_str(); }
("]")                   { 
                            write_cache(); to_str(); 
                            left_Mbrackets_num--;
                            if(left_Mbrackets_num<0){
                                left_Mbrackets_num=0;
                                print_syntax_error("expected '['");
                            }
                            return yytext[0];
                        }
(")")                   { 
                            write_cache(); to_str(); 
                            left_brackets_num--;
                            if(left_brackets_num<0){
                                left_brackets_num=0;
                                print_syntax_error("expected '('");
                            }
                            return yytext[0];
                        }

('')                        { write_cache(); print_lex_error("illegal character constant"); }
(''')                       { write_cache(); print_lex_error("illegal character constant"); }
('\n')                      { write_cache(); print_lex_error("illegal character constant"); skip_error_token(); }

('[^'\n][^']*(\n)[^']*')    { write_cache(); print_lex_error("illegal string constant"); skip_error_token(); }
('[^']*(\n)[^']*[^'\n]')    { write_cache(); print_lex_error("illegal string constant"); skip_error_token(); }
              
(\{|\(\*)[^\{\}(\(\*)(\*\))]*)                  { write_cache(); print_lex_error("unclosed comment"); skip_error_token(); }
('[^']*)                    { write_cache(); print_lex_error("unclosed string constant"); skip_error_token(); }

.                           { write_cache(); print_lex_error("illegal character"); char_count++; }

%%
void wrap()
{
    // 跳过空行
    if(cur_line_info.size() != 0){ 
        last_line_info = cur_line_info;
        cur_line_info.clear();
        last_line_count = line_count;
    }
    line_count++; 
    char_count = 1;
}

void skip_error_token()
{
    for(i = 0; i < strlen(yytext); i++)
    {
        if(yytext[i] == '\n') wrap();
        else char_count++;
    }  
}

void skip_anno()
{
    // log_debug("ANNO\t\t%s\t\t\t%d\t\t%d", yytext, line_count, char_count);
    for(i = 0; i < strlen(yytext); i++)
    {
        if(yytext[i] == '\n') wrap();
        else char_count++;
    }
}

void write_cache()
{
    cur_line_info += yytext;
    // if(yydebug){
    //     std::cout<<"cur_line_info is "<<cur_line_info<<std::endl;
    // }
}

void print_lex_error(const char *msg)
{
    lex_error_flag = 1;
    fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s - %s\n", line_count, char_count, msg, yytext);
}

void print_syntax_error(const char *msg)
{
    lex_error_flag = 1;
    fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s at '%s'\n", line_count, char_count, msg, yytext);
}

void to_str()
{
    // std::string str = std::string(yytext);
    // std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // yylval.token_info.value.set(str);
    // yylval.token_info.line_num = line_count;
    // yylval.token_info.column_num = char_count;
    // yylval.token_info.length = yyleng;

    char_count += yyleng;
}

void to_str_case_sensitive()
{
    // std::string str = std::string(yytext);
    // str = str.substr(1, str.length() - 2);  
    // yylval.token_info.value.set(str);
    // yylval.token_info.line_num = line_count;
    // yylval.token_info.column_num = char_count;
    // yylval.token_info.length = yyleng;

    char_count += yyleng;
}

void to_int()
{
    // yylval.token_info.value.set(std::stoi(yytext));
    // yylval.token_info.line_num = line_count;
    // yylval.token_info.column_num = char_count;
    // yylval.token_info.length = yyleng;

    char_count += yyleng;
}

void to_float()
{
    // yylval.token_info.value.set(std::stof(yytext));
    // yylval.token_info.line_num = line_count;
    // yylval.token_info.column_num = char_count;
    // yylval.token_info.length = yyleng;

    char_count += yyleng;
}

void to_char()
{
    // yylval.token_info.value.set(yytext[1]);
    // yylval.token_info.line_num = line_count;
    // yylval.token_info.column_num = char_count;
    // yylval.token_info.length = yyleng;

    char_count += yyleng;
}


int main(int argc, char **argv)
{
  yylex();
  yywrap();
}

int yywrap()
{
    return 1;
}