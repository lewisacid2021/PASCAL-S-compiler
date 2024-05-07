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
  
}