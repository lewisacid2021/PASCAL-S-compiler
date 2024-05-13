#include "ast.h"
#include "type.h"
#include "symbolTable.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sys/types.h>

extern FILE *fs;

using std::string;
using std::vector;

extern SymbolTable* MainTable;
extern SymbolTable* CurrentTable;
extern TypeTable* TheTypeTable;

namespace ast {

void GenerationVisitor::visit(AST *AST)
{
    fprintf(fs,"#include<stdio.h>\n");    //for test
    fprintf(fs,"#include<stdbool.h>\n");
    AST->getRoot()->accept(this);
}

void GenerationVisitor::visit(AstNode *astnode)
{
    for (auto child : astnode->getCnodeList())
        child->accept(this);
}

void GenerationVisitor::visit(LeafNode *leafnode)
{
    switch (leafnode->get_type()) {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "%d", leafnode->get_value<int>());
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "%s", leafnode->get_value<string>().c_str());
            break;
        case ConstValue::ConstvalueType::BOOLEAN:
            fprintf(fs, "%s", leafnode->get_value<bool>() ? "true" : "false");
            break;
        case ConstValue::ConstvalueType::CHAR:
            fprintf(fs, "\'%c\'", leafnode->get_value<char>());
            break;
        case ConstValue::ConstvalueType::STRING:
        {
            if (leafnode->getLeafType() == LeafNode::LeafType::VALUE)
                fprintf(fs, "\"%s\"", leafnode->get_value<string>().c_str());
            else{
                string leaf_id = leafnode->get_value<string>();
                auto record_info = findID(CurrentTable, leaf_id, 1);
                if(record_info != NULL){
                    if(record_info->flag == "var parameter"){
                        leafnode->set_ref(true);
                    }
                }
                fprintf(fs, "%s", leafnode->id_ref().c_str());
            }
            break;
        }
        default:
            break;
    }
}

void GenerationVisitor::visit(IdList *idlist)
{
    idlist->get(0)->accept(this);
    if (idlist->GetGrammarType() == IdList::GrammarType::MULTIPLE_ID) {
        fprintf(fs, ", ");
        idlist->get(1)->accept(this);
    }
}

void ConstDeclaration::print_type()
{
    switch (type)
    {
        case ConstValue::ConstvalueType::INTEGER:
            fprintf(fs, "int ");
            break;
        case ConstValue::ConstvalueType::REAL:
            fprintf(fs, "float ");
            break;
        case ConstValue::ConstvalueType::CHAR:
        case ConstValue::ConstvalueType::STRING:
            fprintf(fs, "char ");
            if(type == ConstValue::ConstvalueType::STRING)
                fprintf(fs, "*");
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(ConstDeclaration *constdeclaration)
{   
    if (constdeclaration->GetGrammarType() == ConstDeclaration::GrammarType::MULTIPLE_ID)
    {
        constdeclaration->get(0)->accept(this);

        fprintf(fs, "const ");
        constdeclaration->print_type();
        constdeclaration->get(1)->accept(this);
        fprintf(fs, " = ");
        constdeclaration->get(2)->accept(this);
        fprintf(fs, ";\n");
    } else
    {
        fprintf(fs, "const ");
        constdeclaration->print_type();
        constdeclaration->get(0)->accept(this);
        fprintf(fs, " = ");
        constdeclaration->get(1)->accept(this);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(TypeNode *typenode)
{
    switch (typenode->GetVarType()) {
        case TypeNode::VarType::RECORD_TYPE:
            fprintf(fs, "struct ");
            break;
        case TypeNode::VarType::ARRAY_TYPE:{
            string type = typenode->get(0)->DynamicCast<ArrayTypeNode>()->type();
            if(type=="integer"&&true)   //todo 查符号表 预定义标识符是否没被覆盖
                fprintf(fs, "int");
            else if(type=="boolean"&&true) 
                fprintf(fs, "bool");
            else if(type=="real"&&true) 
                fprintf(fs, "float");
            else  fprintf(fs, "%s", type.c_str());
            break;
        }
        case TypeNode::VarType::ID_TYPE:
        {
            if(typenode->get_type_name()=="integer"&&TheTypeTable->findID("integer")->RecordTable==nullptr)   //todo 查类型表 预定义标识符是否没被覆盖
                fprintf(fs, "int");
            else if(typenode->get_type_name()=="boolean"&&TheTypeTable->findID("boolean")->RecordTable==nullptr) 
                fprintf(fs, "bool");
            else if(typenode->get_type_name()=="real"&&TheTypeTable->findID("real")->RecordTable==nullptr) 
                fprintf(fs, "float");
            else 
            {
                //todo 查询类型表判断是否为record
                if(TheTypeTable->findID(typenode->get_type_name())->RecordTable!=nullptr) fprintf(fs,"struct ");
                fprintf(fs, "%s", typenode->get_type_name().c_str());
            }
            break;
        }
        case TypeNode::VarType::STRING_TYPE:
            typenode->get(0)->accept(this);
            break;
    }
}

void GenerationVisitor::visit(StringTypeNode *stringtypenode)
{
    auto type = stringtypenode->type();
    switch (type->GetGrammarType())
    {
        case StringType::GrammarType::LIMIT:
            fprintf(fs, "char[%d] ", type->GetLen());
            break;
        case StringType::GrammarType::NOLIMIT:
            fprintf(fs, "char[%d] ", MAX_STRING_LEN);
            break;
        default:
            break;
    }
}

void GenerationVisitor::visit(VarDeclaration *vardeclaration)
// 缺少对record的处理
{
    //check if it is a array type
    auto type_node    = vardeclaration->get(-1)->DynamicCast<TypeNode>();
    auto grammar_type = vardeclaration->GetGrammarType();

    if (grammar_type == VarDeclaration::GrammarType::MULTIPLE_DECL)
        vardeclaration->get(0)->accept(this);  //vardeclaration

    //type
    vardeclaration->get(-1)->accept(this);
    fprintf(fs, " ");

    if (type_node->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto ArrayType = type_node->get(0)->DynamicCast<ArrayTypeNode>();

        auto id_list   = vardeclaration->get(-2)->DynamicCast<IdList>()->Lists();
        for (unsigned int i = 0; i < id_list.size(); i++)
        {
            id_list[i]->accept(this);
            ArrayType->get(0)->accept(this);  //periods
            if (i != id_list.size() - 1)
                fprintf(fs, ",");
            else
                fprintf(fs, ";\n");
        }
    }else {
        //idlist
        vardeclaration->get(-2)->accept(this);
        fprintf(fs, ";\n");
    }
}

void GenerationVisitor::visit(PeriodsNode *periodsnode)
{
    for (auto &dm : periodsnode->get_dm())
    {
        fprintf(fs, "[%d]", dm.upbound - dm.lowbound + 1);
    }
}

void GenerationVisitor::visit(SubprogramDeclaration *subprogramdeclaration)
{
    auto headnode = subprogramdeclaration->get(0)->DynamicCast<SubprogramHead>();
    string id = headnode->get_id();
    bool isFunc   = (headnode->get_type() == SubprogramHead::SubprogramType::FUNC);
   
    auto record_info = findID(MainTable, id, 0);
    CurrentTable = record_info->subSymbolTable;

    if (isFunc)  //判断是函数还是过程 过程类型为void 无返回值
        id   = "_" + id + "_";

    headnode->accept(this);  //subprogramhead

    fprintf(fs, "{\n");

    if (isFunc)  //声明函数的返回值 pascal用函数名表示返回值 转换成C时需要额外声明一个变量
    {
        subprogramdeclaration->get(0)->get(2)->accept(this);
        fprintf(fs, " %s;\n", id.c_str());
    }

    subprogramdeclaration->get(1)->accept(this);

    if (isFunc)  //函数返回值
        fprintf(fs, "return %s;\n", id.c_str());

    fprintf(fs, "}\n");


    CurrentTable = MainTable;
}

void GenerationVisitor::visit(SubprogramHead *subprogramhead)
{   
    if (subprogramhead->get_type() == SubprogramHead::SubprogramType::PROC)
        fprintf(fs, "void ");
    else
    {
        subprogramhead->get(2)->accept(this);  //type
        fprintf(fs, " ");
    };

    subprogramhead->get(0)->accept(this);  //id

    fprintf(fs, "(");
    subprogramhead->get(1)->accept(this);  //formal_param
    fprintf(fs, ")\n");

}

void GenerationVisitor::visit(ParamLists *paramlists)
{
    auto child_list = paramlists->getCnodeList();
    size_t n        = child_list.size();
    for (size_t i = 0; i < n; i++)
    {
        child_list[i]->accept(this);
        if (i < n - 1)
            fprintf(fs, ",");
    }
}

void GenerationVisitor::visit(ValueParam *valueparam)
{
    auto id_list = valueparam->get(0)->DynamicCast<IdList>();
    auto type    = valueparam->get(1)->DynamicCast<TypeNode>();

    vector<LeafNode *> list = id_list->Lists();
    size_t n=list.size();
    for(size_t i=0;i<n;i++)
    {
        type->accept(this);
        fprintf(fs, " %s",list[i]->id_ref().c_str());
        if(type->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
        {
            auto dim_info=type->get(0)->DynamicCast<ArrayTypeNode>()->info();
            auto dim_size = dim_info->GetDimsum();  //获取数组维数
            for(size_t i=0;i<dim_size;i++)
                if(i!=dim_size-1)
                    fprintf(fs,"[]");     //除了最后一维，打印[]
                else fprintf(fs,"[%d]",dim_info->GetDimension(i).upbound-dim_info->GetDimension(i).lowbound+1); //最后一维打印长度
        }

        if(i<n-1)
            fprintf(fs, ",");
    }
}

void GenerationVisitor::visit(ProgramBody *programbody)
{
    programbody->get(0)->accept(this);  //const declaration
    //to do record declaration
    programbody->get(1)->accept(this);  //record declaration
    programbody->get(2)->accept(this);  //var declaration
    programbody->get(3)->accept(this);  //subprogram declarations

    fprintf(fs,"int main() {\n");
    programbody->get(4)->accept(this);  //comp_stmt
    fprintf(fs,"return 0;\n");
    fprintf(fs,"}\n");
}

void GenerationVisitor::visit(RecordDeclaration *recorddeclaration)
{
    if(recorddeclaration->GetGrammarType()==RecordDeclaration::GrammarType::MULTI_DECLARATION)
        recorddeclaration->get(0)->accept(this);
    
    fprintf(fs, "struct ");
    recorddeclaration->get(-2)->accept(this);  //id
    fprintf(fs, "{\n");
    recorddeclaration->get(-1)->accept(this);  //field_decl_list
    fprintf(fs, "};\n");
}

std::vector<LeafNode *> IdList::Lists()
{
    std::vector<LeafNode *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type_;

    while (gtype == GrammarType::MULTIPLE_ID) //如果多层 进入循环
    {
        LeafNode *ln = cur_node->cnode_list[1]->DynamicCast<LeafNode>();
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<IdList>();
        gtype    = cur_node->grammar_type_;
    }

    // 插入最后一个节点
    LeafNode *ln = (*cur_node->cnode_list.rbegin())->DynamicCast<LeafNode>();
    lists.insert(lists.begin(), ln);
    return lists;
}

void GenerationVisitor::visit(StatementList *statementList)  
    {
         // 获取表达式节点列表
    std::vector<AstNode *> &statements = statementList->getCnodeList();
    
    size_t numChildren = statements.size(); 

    // 递归访问子节点
    for (size_t i = 0; i < numChildren; ++i)
    {
        // 访问当前子节点
        statementList->get(i)->accept(this);

        // 如果不是最后一个语句节点，则输出分号
        // if (i != numChildren - 1)
        // {
        //     fprintf(fs, "; ");
        // }
    }
    }
    
void GenerationVisitor::visit(IfStatement *ifStatement )  {
    fprintf(fs, "if (");
    ifStatement->get(0)->accept(this); // 访问 expression
    fprintf(fs, ")\n{\n");
    ifStatement->get(1)->accept(this); // 访问 then statement
    fprintf(fs, "}\n");

    ifStatement->get(2)->accept(this); // 访问 else_part
}
 
void GenerationVisitor::visit(ElsePart *elseNode )  
    {
        switch (elseNode->get_type())
        {
        case ElsePart::ELSEType::EPSILON:
            return;
        case ElsePart::ELSEType::ELSE_STATEMENT:
            fprintf(fs, "else {\n");
            elseNode->get(0)->accept(this); // 访问 expression
            fprintf(fs, "}\n");
        }
    } 

 std::string generateFormatString(ExpressionList* expressionList) {
    std::string formatString = "\"";
    std::vector<std::string>* types = expressionList->get_types();

    for(const auto& type : *types) {
        if (type == "string") {
            formatString += "%s";
        } else if (type == "char") {
            formatString += "%c";
        } else if (type == "integer") {
            formatString += "%d";
        } else if (type == "real") {
            formatString += "%f";
        } else if (type == "boolean") {
            formatString += "%d";
        } else if (type == "unknown"){
            formatString += "%i";
        } 
        // 添加逗号和空格
        //formatString += ", ";
    }
    formatString += "\",";
    
    return formatString;
}

std::string generateFormatString2(ExpressionList* expressionList) {
    std::string formatString = "\"";
    std::vector<std::string>* types = expressionList->get_types();

    for(const auto& type : *types) {
        if (type == "string") {
            formatString += "%s";
        } else if (type == "char") {
            formatString += "%c";
        } else if (type == "integer") {
            formatString += "%d";
        } else if (type == "real") {
            formatString += "%f";
        } else if (type == "boolean") {
            formatString += "%d";
        } else if (type == "unknown"){
            formatString += "%i";
        } 
        // 添加逗号和空格
        //formatString += " ";
    }
    formatString += "\\n\",";
    
    return formatString;
}

void GenerationVisitor::visit(ProcedureCall *procedureCall)  {
    //fprintf(fs, "here");
    if(procedureCall->get_id()=="break"){
        fprintf(fs, "break;\n");
        return;
    }
    if(procedureCall->get_id()=="writeln"){
        fprintf(fs, "printf(");
        auto expressionList = procedureCall->get(0)->DynamicCast<ExpressionList>(); // 假设 procedureCall 是指向 ProcedureCall 对象的指针
        std::string formatString = generateFormatString2(expressionList);

        // 使用 fprintf 打印生成的格式化字符串
        fprintf(fs, "%s", formatString.c_str());
        procedureCall->get(0)->accept(this); // expressionlist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
        }
    if(procedureCall->get_id()=="readln"){
        fprintf(fs, "char input[100000];\n  fgets(input, sizeof(input), stdin);sscanf(input, ");
        ExpressionList* expressionList = procedureCall->get(0)->DynamicCast<ExpressionList>(); // 假设 procedureCall 是指向 ProcedureCall 对象的指针
        std::string formatString = generateFormatString(expressionList);

        // 使用 fprintf 打印生成的格式化字符串
        fprintf(fs, "%s", formatString.c_str());
        vector<AstNode*> lists= procedureCall->get(0)->DynamicCast<ExpressionList>()->Lists();
        for(int i = 0; i < lists.size(); i++){
            if(lists[i]->DynamicCast<Expression>()->GetGraType() == Expression::GrammarType::SINGLE){
                if(lists[i]->get(0)->DynamicCast<SimpleExpression>()->getCnodeList().size() == 1){
                    if(lists[i]->get(0)->get(0)->DynamicCast<Term>()->GetSymType() == Term::SymbolType::SINGLE){
                        if(lists[i]->get(0)->get(0)->get(0)->DynamicCast<Factor>()->get_type() == Factor::GrammerType::VARIABLE){
                        // 找到相应变量的表项
                            auto var = lists[i]->get(0)->get(0)->get(0)->get(0)->DynamicCast<Variable>();
                            string id = var->get(0)->DynamicCast<LeafNode>()->get_value<string>();
                            auto table_info = findID(MainTable, procedureCall->get_id(), 0);
                            if(table_info != NULL){                  
                                auto record_info = findID(CurrentTable, id, 0);
                                if(record_info != NULL){
                                    if(record_info->flag == "variant" || record_info->flag == "array"){
                                        fprintf(fs, "&");
                                    }
                                    else if( record_info->flag == "(sub)program name" ){
                                        string func_id = record_info->id;
                                        func_id   = "&_" + id + "_";
                                        fprintf(fs, "%s", func_id.c_str());
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lists[i]->accept(this);
            if(i != lists.size() - 1){
                fprintf(fs, ", ");
            }
        }
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
        }
    if(procedureCall->get_id()=="write"){
        fprintf(fs, "printf(");
        auto expressionList = procedureCall->get(0)->DynamicCast<ExpressionList>(); // 假设 procedureCall 是指向 ProcedureCall 对象的指针
        std::string formatString = generateFormatString(expressionList);

        // 使用 fprintf 打印生成的格式化字符串
        fprintf(fs, "%s", formatString.c_str());
        procedureCall->get(0)->accept(this); // expressionlist
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
    else if(procedureCall->get_id()=="read"){
        fprintf(fs, "scanf(");
        ExpressionList* expressionList = procedureCall->get(0)->DynamicCast<ExpressionList>(); // 假设 procedureCall 是指向 ProcedureCall 对象的指针
        std::string formatString = generateFormatString(expressionList);

        // 使用 fprintf 打印生成的格式化字符串
        fprintf(fs, "%s", formatString.c_str());
        vector<AstNode*> lists= procedureCall->get(0)->DynamicCast<ExpressionList>()->Lists();
        for(int i = 0; i < lists.size(); i++){
            if(lists[i]->DynamicCast<Expression>()->GetGraType() == Expression::GrammarType::SINGLE){
                if(lists[i]->get(0)->DynamicCast<SimpleExpression>()->getCnodeList().size() == 1){
                    if(lists[i]->get(0)->get(0)->DynamicCast<Term>()->GetSymType() == Term::SymbolType::SINGLE){
                        if(lists[i]->get(0)->get(0)->get(0)->DynamicCast<Factor>()->get_type() == Factor::GrammerType::VARIABLE){
                        // 找到相应变量的表项
                            auto var = lists[i]->get(0)->get(0)->get(0)->get(0)->DynamicCast<Variable>();
                            string id = var->get(0)->DynamicCast<LeafNode>()->get_value<string>();
                            auto table_info = findID(MainTable, procedureCall->get_id(), 0);
                            if(table_info != NULL){                  
                                auto record_info = findID(CurrentTable, id, 0);
                                if(record_info != NULL){
                                    if(record_info->flag == "variant" || record_info->flag == "array"){
                                        fprintf(fs, "&");
                                    }
                                    else if( record_info->flag == "(sub)program name" ){
                                        string func_id = record_info->id;
                                        func_id   = "&_" + id + "_";
                                        fprintf(fs, "%s", func_id.c_str());
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lists[i]->accept(this);
            if(i != lists.size() - 1){
                fprintf(fs, ", ");
            }
        }
        fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
    }
        else if(procedureCall->get_id()=="sin"){
        fprintf(fs, "sin((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="cos"){
        fprintf(fs, "cos((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="sin"){
        fprintf(fs, "sin((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="sqr"){
        fprintf(fs, "(");
        procedureCall->get(0)->accept(this);
        fprintf(fs, "*");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="odd"){
        fprintf(fs, "(");
        procedureCall->get(0)->accept(this);
        fprintf(fs, "%2==1)");
    }
    else if(procedureCall->get_id()=="chr"){
        fprintf(fs, "(char)");
        procedureCall->get(0)->accept(this);
    }
    else if(procedureCall->get_id()=="ord"){
        fprintf(fs, "(int)");
        procedureCall->get(0)->accept(this);
    }
    else if(procedureCall->get_id()=="succ"){
        fprintf(fs, "(");
        procedureCall->get(0)->accept(this);
        fprintf(fs, "+1)");
    }
    else if(procedureCall->get_id()=="pred"){
        fprintf(fs, "(");
        procedureCall->get(0)->accept(this);
        fprintf(fs, "-1)");
    }
    else if(procedureCall->get_id()=="round"){
        fprintf(fs, "(int)(");
        procedureCall->get(0)->accept(this);
        fprintf(fs, "+0.5)");
    }
    else if(procedureCall->get_id()=="trunc"){
        fprintf(fs, "(int)");
        procedureCall->get(0)->accept(this);
    }
    else if(procedureCall->get_id()=="exp"){
        fprintf(fs, "exp((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="ln"){
        fprintf(fs, "log((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    }
    else if(procedureCall->get_id()=="sqrt"){
        fprintf(fs, "sqrt((float)");
        procedureCall->get(0)->accept(this);
        fprintf(fs, ")");
    } 
    else{
        fprintf(fs, "%s", procedureCall->get_id().c_str());
        // 根据调用类型决定是否输出参数列表
        if (procedureCall->get_type() == ProcedureCall::ProcedureType::NO_LIST)
        {
            fprintf(fs, "();\n"); // 输出空参数列表
        }
        else if (procedureCall->get_type() == ProcedureCall::ProcedureType::EXP_LIST)
        {
            fprintf(fs, "(");
            //procedureCall->get(0)->accept(this);//expressionlist
            vector<AstNode*> lists= procedureCall->get(0)->DynamicCast<ExpressionList>()->Lists();
            for(int i = 0; i < lists.size(); i++){
                if(lists[i]->DynamicCast<Expression>()->GetGraType() == Expression::GrammarType::SINGLE){
                    if(lists[i]->get(0)->DynamicCast<SimpleExpression>()->getCnodeList().size() == 1){
                        if(lists[i]->get(0)->get(0)->DynamicCast<Term>()->GetSymType() == Term::SymbolType::SINGLE){
                            if(lists[i]->get(0)->get(0)->get(0)->DynamicCast<Factor>()->get_type() == Factor::GrammerType::VARIABLE){
                                auto table_info = findID(MainTable, procedureCall->get_id(), 0);
                                if(table_info != NULL){                  
                                    if(table_info->subSymbolTable->records[i+1]->flag == "var parameter"){
                                        fprintf(fs, "&");
                                    }  
                                }
                            }
                        }
                    }
                }
                lists[i]->accept(this);
                if(i != lists.size() - 1){
                    fprintf(fs, ", ");
                }
            }
            
            fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
        }
        else if (procedureCall->get_type() == ProcedureCall::ProcedureType::VAR_LIST)
        {
            fprintf(fs, "(");
            procedureCall->get(0)->accept(this);//variablelist
            fprintf(fs, ");\n"); // 输出包含表达式列表的参数列表
        }
    }
}

void GenerationVisitor::visit(AssignopStatement *assignopStatement )  
{
        auto assignment_node = dynamic_cast<AssignopStatement *>(assignopStatement->get(0));
 
        // 根据左侧类型决定生成的代码逻辑
        switch (assignopStatement->get_type())
        {
        case AssignopStatement::LeftType::VARIABLE:
        
            // 生成函数调用的代码
            assignopStatement->get(0)->accept(this);

            // 输出赋值操作符
            fprintf(fs, " = ");

            // 生成右侧表达式的代码
            assignopStatement->get(1)-> accept(this);

            // 输出分号以结束语句
            fprintf(fs, ";\n");
            break;
        case AssignopStatement::LeftType::FUNCID:
             // 生成函数调用的代码
            fprintf(fs, "_");
            assignopStatement->get(0)->get(0)->accept(this);
            fprintf(fs, "_");
            // 输出赋值操作符
            fprintf(fs, " = ");
            // 生成右侧表达式的代码
            assignopStatement->get(1)-> accept(this);

            // 输出分号以结束语句
            fprintf(fs, ";\n");
            break;
        default:
            // 其他情况下，什么也不做
            break;
        }
    }

void GenerationVisitor::visit(LoopStatement *loopStatement )  
    {
          switch (loopStatement->get_type())
        {
        case LoopStatement::LoopType::FORUP:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id-> accept(this);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)-> accept(this);//expression
            fprintf(fs, "; ");
            id-> accept(this);
            fprintf(fs, " <= ");
            loopStatement->get(2)-> accept(this);//中间的expression
            fprintf(fs, "; ");
            
            id-> accept(this);
            fprintf(fs, "++) {\n");
            loopStatement->get(3)-> accept(this);//statement
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::FORDOWN:
        {
            fprintf(fs, "for (");
            auto id = loopStatement->get(0)->DynamicCast<LeafNode>();
            if (id)
            {
                id-> accept(this);
            }
            fprintf(fs, " = ");
            loopStatement->get(1)-> accept(this);
            fprintf(fs, "; ");
            id-> accept(this);
            fprintf(fs, " >= ");
            loopStatement->get(2)-> accept(this);
            fprintf(fs, "; ");
            id-> accept(this);
            fprintf(fs, "--) {\n");
            loopStatement->get(3)-> accept(this);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::WHILE_:
        {
            fprintf(fs, "while (");
            loopStatement->get(0)-> accept(this);
            fprintf(fs, ") {\n");
            loopStatement->get(1)-> accept(this);
            fprintf(fs, "}\n");
            break;
        }
        case LoopStatement::LoopType::REPEAT_:
        {
            fprintf(fs, "do {\n");
            loopStatement->get(0)-> accept(this);
            fprintf(fs, "} while (!(");
            loopStatement->get(1)-> accept(this);
            fprintf(fs, "));\n");
            break;
        }
        }
    }


void GenerationVisitor::visit(Variable *variable )  {
    // 访问第一个子节点
    variable->get(0)-> accept(this);
    string id = variable->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    auto record_info = findID(MainTable, id, 0);
    if(record_info != NULL){
        if(record_info->flag == "function"){
            fprintf(fs, "()");
        }
    }
    // 访问第二个子节点
    if(variable->getCnodeList().size() == 2){
        std::vector<AstNode *> list = variable->get(1)->DynamicCast<IDVarParts>()->Lists();

        // 遍历子节点列表并逐个访问
        for (auto i : list) {
            IDVarPart *idvarpart = i->DynamicCast<IDVarPart>();
            if (idvarpart->get_type() == IDVarPart::GrammarType::_ID)
            {
                fprintf(fs, ".");
                idvarpart->get(0)->accept(this);// 访问 id
            }
            else if (idvarpart->get_type() == IDVarPart::GrammarType::EXP_LIST)
            {   
                auto exp_list = idvarpart->get(0)->DynamicCast<ExpressionList>()->Lists();
                auto record_info = findID(CurrentTable, id, 0, "array");
                if(record_info == NULL){
                    // 错误处理
                    cout << "notfound" <<endl;
                    return;
                }
                vector< pair<int, int> > bound = record_info->arrayRange;
                int i = 0;
                for(auto exp : exp_list){
                    fprintf(fs, "[");
                    exp->accept(this);
                    if(bound[i].first!=0){
                        fprintf(fs, " - ");
                        fprintf(fs,"%d",bound[i].first);
                    }
                    fprintf(fs, "]");
                    i++;
                }
            }
        }
    }
}

void GenerationVisitor::visit(VariableList *variableList )   {
    
    std::vector<AstNode *> &children = variableList->getCnodeList();
    
    // 处理单个表达式节点
    if (variableList->get_type() ==  VariableList::GrammarType::VAR_)
    {
        variableList->get(0)-> accept(this);
    }
    // 处理多个表达式节点
    else if (variableList->get_type() == VariableList::GrammarType::VAR_LIST_VAR)
    {
        size_t numChildren=children.size();
        // 遍历子节点列表并逐个访问
        for (size_t i = 0; i < numChildren; ++i) {
            children[i]-> accept(this);

            // 如果不是最后一个节点，则输出逗号
            if (variableList->get_type() == VariableList::GrammarType:: VAR_LIST_VAR && i != numChildren - 1) {
                fprintf(fs, ", ");
            }
        }
    }
}
// void GenerationVisitor::visit(IDVarPart *idVarPart )  
// {
//     if (idVarPart->get_type() == IDVarPart::GrammarType::_ID)
//     {
//         fprintf(fs, ".");
//         idVarPart->get(0)->accept(this);// 访问 id
//     }
//     else if (idVarPart->get_type() == IDVarPart::GrammarType::EXP_LIST)
//     {   
//         auto exp_list = idVarPart->get(0)->DynamicCast<ExpressionList>()->Lists();
//         for(auto exp : exp_list){
//             fprintf(fs, "[");
//             exp->accept(this);
//             auto record_info = findID(CurrentTable, , 0);
//             fprintf(fs, "]");
//         }
//     }
// }
// void GenerationVisitor::visit(IDVarParts *idVarParts )   {
//     // 获取子节点列表
//     std::vector<AstNode *> &children = idVarParts->getCnodeList();

//     // 遍历子节点列表并逐个访问
//     for (size_t i = 0; i < children.size(); ++i) {
//         children[i]-> accept(this);

//         // 如果不是最后一个节点，则输出空格
        
//     }
// }

 void GenerationVisitor::visit(Term *term )  
{
    if (term->GetSymType() == Term::SymbolType::SINGLE)
    {
        // term -> factor 的情况
        term->get(0)-> accept(this); // 访问 factor 节点
    }
    else
    {
        // term -> term MULOP factor 的情况
        term->get(0)-> accept(this); // 访问左侧 term 节点
      
        // 根据乘法操作符类型输出相应的符号
        switch (term->GetSymType())
        {
        case Term::SymbolType::MULTIPLY:
            fprintf(fs, " * ");
            break;
        case Term::SymbolType::DEVIDE:
            fprintf(fs, " / ");
            break;
        case Term::SymbolType::MOD:
            fprintf(fs, " %% ");
            break;
        case Term::SymbolType::AND:
            fprintf(fs, " && ");
            break;
        case Term::SymbolType::SINGLE:
            break;
        }
        term->get(1)-> accept(this); // 访问右侧 factor 节点
    }
}

    void GenerationVisitor::visit(Factor *factor )  
    {
        switch (factor->get_type())
        {
        case Factor::GrammerType::NUM:
        case Factor::GrammerType::VARIABLE:
            factor->get(0)-> accept(this);
            break;
        case Factor::GrammerType::EXP:
            fprintf(fs, "(");
            factor->get(0)-> accept(this);
            fprintf(fs, ")");
            break;
        case Factor::GrammerType::ID_EXP_LIST:
        {   
            factor->get(0)-> accept(this);
            fprintf(fs, "(");
            vector<AstNode*> lists= factor->get(1)->DynamicCast<ExpressionList>()->Lists();
            for(int i = 0; i < lists.size(); i++){
                if(lists[i]->DynamicCast<Expression>()->GetGraType() == Expression::GrammarType::SINGLE){
                    if(lists[i]->get(0)->DynamicCast<SimpleExpression>()->getCnodeList().size() == 1){
                        if(lists[i]->get(0)->get(0)->DynamicCast<Term>()->GetSymType() == Term::SymbolType::SINGLE){
                            if(lists[i]->get(0)->get(0)->get(0)->DynamicCast<Factor>()->get_type() == Factor::GrammerType::VARIABLE){
                                auto table_info = findID(MainTable, factor->get(0)->DynamicCast<LeafNode>()->get_value<string>(), 0);
                                if(table_info != NULL){                  
                                    if(table_info->subSymbolTable->records[i+1]->flag == "var parameter"){
                                        fprintf(fs, "&");
                                    }  
                                }
                            }
                        }
                    }
                }
                lists[i]->accept(this);
                if(i != lists.size() - 1){
                    fprintf(fs, ", ");
                }
            }
            //factor->get(1)-> accept(this);
            fprintf(fs, ")");
            break;
        }
        case Factor::GrammerType::NOT_:
            fprintf(fs, "~");
            factor->get(0)-> accept(this);
            break;
        case Factor::GrammerType::UPLUS:  
            fprintf(fs, "(+");
            factor->get(0)-> accept(this); // 访问因子节点
            fprintf(fs, ")");
            break;
        case Factor::GrammerType::UMINUS_:
            fprintf(fs, "(-");
            factor->get(0)-> accept(this); // 访问因子节点
            fprintf(fs, ")");
            break;
        case Factor::GrammerType::CHAR_:
            factor->get(0)-> accept(this); // 'letter'
            break;
        case Factor::GrammerType::STR:
        case Factor::GrammerType::BOOL:
            factor->get(0)-> accept(this);
            break;
        default:
            break;
        }
    }

void GenerationVisitor::visit(Expression *expression )  {
    if (expression->GetGraType() == Expression::GrammarType::SINGLE)
    {
        // expression -> simple_expression 的情况
        expression->get(0)-> accept(this); // 访问 term 节点
    }
    if (expression->GetGraType() == Expression::GrammarType::DOUBLE)
    {
        // expression -> expression relop simple_expression 的情况
        expression->get(0)-> accept(this); // 访问左侧 expression 节点
        if(expression->GetSymType() == "<>"){
            fprintf(fs, " != ");
        }
        else if(expression->GetSymType() == "="){
            fprintf(fs, " == ");
        }
        else{
            string symbol = " " + expression->GetSymType() + " ";
            fprintf(fs, "%s", symbol.c_str());
        }
        expression->get(1)-> accept(this); // 访问右侧 simple_expression 节点
    
    }
}

void GenerationVisitor::visit(SimpleExpression *simpleExpression )  {
    if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::SINGLE)
    {
        // simple_expression -> term 的情况
        simpleExpression->get(0)-> accept(this); // 访问 term 节点
    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::PLUS_)
    {
        // simple_expression -> + term / simple_exp + term 的情况
        if(simpleExpression->getCnodeList().size() == 2){
            simpleExpression->get(0)-> accept(this); 
            fprintf(fs, " + ");
            simpleExpression->get(1)-> accept(this); // 访问 term 节点
        }
        else{
            fprintf(fs, "+");
            simpleExpression->get(0)-> accept(this); // 访问 term 节点
        }
    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::MINUS_)
    {
        // simple_expression -> - term / simple_exp - term 的情况
        if(simpleExpression->getCnodeList().size() == 2){
            simpleExpression->get(0)-> accept(this); 
            fprintf(fs, " - ");
            simpleExpression->get(1)-> accept(this); // 访问 term 节点
        }
        else{
            fprintf(fs, "-");
            simpleExpression->get(0)-> accept(this); // 访问 term 节点
        }

    }
    else if (simpleExpression->GetSymType() == SimpleExpression::SymbolType::OR_)
    {
        // simple_expression -> simple_expression or term 的情况
        simpleExpression->get(0)-> accept(this); // 访问左侧 simple_expression 节点
        fprintf(fs, " || ");
        simpleExpression->get(1)-> accept(this); // 访问右侧 term 节点
    }
   }

void GenerationVisitor::visit(ExpressionList *expressionList )  {
    // 获取表达式列表类型
    ExpressionList::ExpressionType type = expressionList->get_type();

    // 获取表达式节点列表
    std::vector<AstNode *> &expressions = expressionList->getCnodeList();
    
    // 处理单个表达式节点
    if (type == ExpressionList::ExpressionType::SINGLE)
    {
        expressions[0]-> accept(this);
    }
    // 处理多个表达式节点
    else if (type == ExpressionList::ExpressionType::MULTIPLE)
    {
        size_t numExpressions = expressions.size(); // 获取表达式列表的大小
    
        for (size_t i = 0; i < numExpressions; ++i)
        {
            expressions[i]-> accept(this);
            // 如果不是最后一个表达式，则输出逗号分隔符
            if (i != numExpressions - 1)
            {
                fprintf(fs, ", ");
            }
        }
    }
}

void GenerationVisitor::visit(Statement *statement )  
{
    switch (statement->get_type())
    {
    case Statement::StatementType::EPSILON:
        return;
    case Statement::StatementType::ASSIGN_OP_STATEMENT:
    case Statement::StatementType::PROCEDURE_CALL:
    case Statement::StatementType::COMPOUND_STATEMENT:
    case Statement::StatementType::IF_STATEMENT:
    case Statement::StatementType::LOOP_STATEMENT:
        statement->get(0)->accept(this);
        break;

    // case Statement::StatementType::READ_STATEMENT:
    // case Statement::StatementType::READLN_STATEMENT:
    //     break;
    // case Statement::StatementType::WRITE_STATEMENT:
    // case Statement::StatementType::WRITELN_STATEMENT:
    //     break;
    }
}

void GenerationVisitor::visit(CompoundStatement *compoundStatement )  {
    compoundStatement->get(0)->accept(this); // 访问  StatementList
}

vector<AstNode*> IDVarParts::Lists(){
    std::vector<AstNode *> lists;
    auto *cur_node    = this;
   
    while (cur_node->getCnodeList().size() == 2) //如果多层 进入循环
    {
        AstNode * ln = cur_node->cnode_list[1];
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<IDVarParts>();
    }
    return lists;
}

}  // namespace ast