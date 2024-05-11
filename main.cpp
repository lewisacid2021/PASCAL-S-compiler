#include <cstdio>
#include <iostream>
#include "ast.h"
#include "symbolTable.h"
#include "type.h"
#include "parser.h"
#include "parser.tab.h"

extern FILE *yyin; 
FILE * fs;
SymbolTable * MainTable;
SymbolTable* CurrentTable;

int main(int argc, char *argv[]){
    ast::AST *ast = new ast::AST();
    ast::GenerationVisitor* Codegen_Visitor=new ast::GenerationVisitor();
    ast::SemanticVisitor* Semantic_Visitor = new ast::SemanticVisitor();
    MainTable=new SymbolTable();
    CurrentTable = MainTable;
    
    if (argc < 3){
        std::cerr << "Usage: " << argv[0] << "-i <filename>" << std::endl;
        return 1;
    }
    yyin = fopen(argv[2], "r");
    if (yyin == nullptr){
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::string outfile(argv[2]);   
    outfile=outfile.substr(0,outfile.find_last_of('.'))+".c"; 

    fs=fopen(outfile.c_str(),"w");

        if (fs == nullptr){
        std::cerr << "Cannot create file " << outfile.c_str() << std::endl;
        return 1;
    }



    //lexical and grammar analysis
    yyparse(ast);

    Semantic_Visitor->visit(ast);
    Codegen_Visitor->visit(ast);

    fclose(yyin);
    fclose(fs); 
    return 0;
}
