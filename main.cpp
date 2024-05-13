#include "ast.h"
#include "parser.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>

extern FILE *yyin;
extern int error_flag;
FILE *fs;
SymbolTable *MainTable;
SymbolTable *CurrentTable;
TypeTable *TheTypeTable;
int math_flag = 0;

int main(int argc, char *argv[])
{
    ast::AST *ast                           = new ast::AST();
    ast::GenerationVisitor *Codegen_Visitor = new ast::GenerationVisitor();
    ast::SemanticVisitor *Semantic_Visitor  = new ast::SemanticVisitor();
    MainTable                               = new SymbolTable("main");
    CurrentTable                            = MainTable;
    TheTypeTable                            = new TypeTable();

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "-option <filename>" << std::endl;
        std::cout << "\t-i: output to file\n\t-o: output to terminal\n";
        return 1;
    }

    string option(argv[1]);
    size_t pos = option.find('-');
    if (pos != std::string::npos) {
        // 提取 '-' 后的子串
        std::string substr = option.substr(pos + 1);
        if (substr.size() != 1) {
            std::cout << "Invalid option, Usage: -option" << std::endl;
            std::cout << "\t-i: output to file\n\t-o: output to terminal\n";
            return 1;
        } else {
            switch (substr[0]) {
                case 'i':
                case 'o':
                {
                    yyin = fopen(argv[2], "r");
                    if (yyin == nullptr) {
                        std::cerr << "Cannot open file " << argv[2] << std::endl;
                        return 1;
                    }

                    std::string outfile(argv[2]);
                    outfile = outfile.substr(0, outfile.find_last_of('.')) + ".c";

                    if (substr[0] == 'i')
                    {
                        fs = fopen(outfile.c_str(), "w");

                        if (fs == nullptr) {
                            std::cerr << "Cannot create file " << outfile.c_str() << std::endl;
                            return 1;
                        }
                    } else
                        fs = stdout;
                    //lexical and grammar analysis
                    yyparse(ast);
                    if (error_flag == 1 || ast == NULL) {
                        std::cout << "unrecoverable errors occurred" << endl;
                        return 0;
                    }
                    //std::cout<<"Parsing finished"<<std::endl;
                    Semantic_Visitor->visit(ast);
                    // std::cout<<"Semantic analysis finished"<<std::endl;
                    Codegen_Visitor->visit(ast);
                    // std::cout<<"Code generation finished"<<std::endl;

                    fclose(yyin);
                    fclose(fs);
                    // std::cout<<"Result output finished"<<std::endl;
                    break;
                } break;
                default:
                    std::cout << "Invalid option, Usage: -option" << std::endl;
                    std::cout << "\t-i: output to file\n\t-o: output to terminal\n";
                    return 1;
            }
        }
    } else {
        std::cout << "Invalid option format, Use: \'-\'" << std::endl;
    }

    system("cls");

    return 0;
}
