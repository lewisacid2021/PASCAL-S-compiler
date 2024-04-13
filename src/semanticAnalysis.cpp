#include "ast.h"
#include "symbolTable.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace ast;

extern SymbolTable *mainSymbolTable;

void symbolTableInit();

void semanticAnalysis()
{
    symbolTableInit();
}

void SemanticAnalyseProgram(AstNode *astroot)
{
    if (astroot == NULL) {
        cout << "[SemanticAnalyseProgram] pointer of _Program is null" << endl;
        return;
    }
    //库函数名、主程序名、主程序参数，在检查是否重定义时，优先级按照前面列举的顺序，
    //即主程序名不能和库函数名，主程序参数不能和库函数名、主程序名同名
    //添加主程序名、行号、参数个数等信息
    set<string> lib;
    lib.insert("read");
    lib.insert("write");
    lib.insert("writeln");
    lib.insert("exit");
    if (lib.count(astroot->programId.first))  //checked
        addGeneralErrorInformation("[Duplicate defined error!] <Line " + itos(astroot->programId.second) + "> Name of astroot \"" + astroot->programId.first + "\" has been defined as a lib astroot.");
    mainSymbolTable->addProgramName(astroot->programId.first, astroot->programId.second, "procedure", int(astroot->paraList.size()), "");
    //将主程序的参数添加到主符号表中，flag定为"parameter of astroot"
    for (int i = 0; i < astroot->paraList.size(); i++) {             //检查主程序参数是否和主程序名同名
        if (astroot->paraList[i].first == astroot->programId.first)  //checked
            addGeneralErrorInformation("[Duplicate defined error!] <Line " + itos(astroot->programId.second) + "> parameter of astroot \"" + astroot->programId.first + "\" is the same as name of astroot.");
        else if (lib.count(astroot->paraList[i].first))              //checked
            addGeneralErrorInformation("[Dulicate defined error!] <Line " + itos(astroot->paraList[i].second) + "> parameter of astroot \"" + astroot->paraList[i].first + "\" has been defined as a lib astroot.");
        mainSymbolTable->addVoidPara(astroot->paraList[i].first, astroot->paraList[i].second);
    }
    //主符号表需提前加入read、write、exit等库函数
    //对于库函数来说，setProcedure的后三个参数,lineNumber,amount,subSymbolTable是没有用的
    //lineNumber=-1且subSymbolTable=NULL表示是库函数
    //amount=-1表示变参
    //添加read过程，该过程变参
    mainSymbolTable->addProcedure("read", -1, -1, NULL);
    //添加write过程，该过程变参
    mainSymbolTable->addProcedure("write", -1, -1, NULL);
    //添加writeln过程，该过程变参
    mainSymbolTable->addProcedure("writeln", -1, -1, NULL);
    //添加exit过程，该过程的参数个数需要分情况讨论，程序里会有特判，这里指定为0没有特殊含义
    mainSymbolTable->addProcedure("exit", -1, 0, NULL);
    SemanticAnalyseSubprogram(astroot->subProgram);
}