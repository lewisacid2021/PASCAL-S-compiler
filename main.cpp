#include <cstdio>
#include <iostream>
#include "ast.h"
#include "type.h"
#include "parser.h"
#include "y.tab.h"

extern FILE *yyin; 

int main(int argc, char *argv[]){
    ast::AST *ast = new ast::AST();
    ast::GenerationVisitor* Codegen_Visitor=new ast::GenerationVisitor();

    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == nullptr){
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::string outfile(argv[1]);   
    outfile=outfile.substr(0,outfile.find_last_of('.'))+".c"; 

    FILE *fs=fopen(outfile.c_str(),"w");

    //lexical and grammar analysis
    yyparse(ast);

    Codegen_Visitor->visit(ast, fs);

    fclose(yyin);
    fclose(fs); 
    return 0;
}
