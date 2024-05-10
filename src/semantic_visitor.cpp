#include "ast.h"
#include "symbolTable.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <set>
#include <sys/types.h>
#include <tuple>
#include <utility>

using std::string;
using std::vector;

extern SymbolTable* MainTable;
SymbolTable* CurrentTable = MainTable;

void addDuplicateNameError();

namespace ast{
void SemanticVisitor::visit(AST *AST)
{
    AST->getRoot()->accept(this);
}

void SemanticVisitor::visit(AstNode *astnode)
{
    for (auto child : astnode->getCnodeList())
        child->accept(this);
}

void SemanticVisitor::visit(ProgramHead *programhead)
{
    string id = programhead->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    int rn = programhead->get(0)->DynamicCast<LeafNode>()->get_rownum();

    set<string> lib;
    lib.insert("read");
    lib.insert("write");
    lib.insert("writeln");
    lib.insert("exit");
    //检查主程序是否与库函数重名
    if(lib.count(id))
    {
        addDuplicateNameError();
    }

    if(programhead->getCnodeList().size() == 1)
    {
        int amount = 0;
        MainTable->addProgramName(id, rn, "program", amount, "");
    }
    else
    {
        auto idlist = programhead->get(1)->DynamicCast<IdList>()->Lists();
        int amount = idlist.size();
        CurrentTable->addProgramName(id, rn, "program", amount, "");
        for (auto p : idlist)
        {
            string para_id = p->get_value<string>();
            int para_rn = p->get_rownum();

            //检查参数是否与主程序。库函数同名
            if(para_id == id)
            {
                addDuplicateNameError();
            }
            else if(lib.count(para_id))
            {
                addDuplicateNameError();
            }

            MainTable->addVoidPara(para_id, para_rn);
        }
    }

    MainTable->addProcedure("read", -1, -1, NULL);
    //添加write过程，该过程变参
    MainTable->addProcedure("write", -1, -1, NULL);
    //添加writeln过程，该过程变参
    MainTable->addProcedure("writeln", -1, -1, NULL);
    //添加exit过程，该过程的参数个数需要分情况讨论，程序里会有特判，这里指定为0没有特殊含义
    MainTable->addProcedure("exit", -1, 0, NULL);
}

void SemanticVisitor::visit(ConstDeclaration *constdeclaration)
{
    auto lists = constdeclaration->Lists();
    for(auto p:lists)
    {
        string id = std::get<1>(p);
        int rn = std::get<0>(p);
        string type;
        string value;
        ConstValue * const_value = std::get<2>(p);
        ConstValue::ConstvalueType const_value_type = const_value->type();
        bool isMinus = const_value->get_uminus();

        switch(const_value_type){
            case ConstValue::ConstvalueType::INTEGER:
<<<<<<< HEAD
                type = "interger";
=======
                type = "integer";
>>>>>>> 2a4dee8ebd8a59d254e9f5592c236d42e152b88a
                value = std::to_string(const_value->get<int>());
                break;
            case ConstValue::ConstvalueType::REAL:
                type = "real";
                value = std::to_string(const_value->get<float>());
                break;
            case ConstValue::ConstvalueType::BOOLEAN:
                type = "boolean";
                if(const_value->get<bool>() == true)
                    value = "true";
                else
                    value = "false";
                break;
            case ConstValue::ConstvalueType::CHAR:
                type = "char";
                value.push_back(const_value->get<char>());
                break;
            case ConstValue::ConstvalueType::STRING:
                type = "string";
                value = const_value->get<string>();
                break;
        }

        CurrentTable->addConst(id, rn, type, isMinus, value);
    }
}

void SemanticVisitor::visit(RecordDeclaration *recorddeclaration)
{
    recorddeclaration->get(0)->accept(this);

    string id = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_value<string>();
    int rn = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_rownum();

    SymbolTable *subTable = new SymbolTable();

    CurrentTable->addRecord(id, rn, subTable);

    SymbolTable *PreviousTable = CurrentTable;
    CurrentTable               = subTable;

    recorddeclaration->get(2)->accept(this);

    CurrentTable = PreviousTable;
}

void SemanticVisitor::visit(VarDeclaration *vardeclaration)
{
    IdList* idlist;
    TypeNode* typenode; 

    if(vardeclaration->GetGrammarType() == VarDeclaration::GrammarType::SINGLE_DECL)
    {
        idlist = vardeclaration->get(0)->DynamicCast<IdList>();
        typenode = vardeclaration->get(1)->DynamicCast<TypeNode>();
    }
    else
    {
        idlist = vardeclaration->get(1)->DynamicCast<IdList>();
        typenode = vardeclaration->get(2)->DynamicCast<TypeNode>();
        vardeclaration->get(0)->accept(this);
    }

    if(typenode->GetVarType() == TypeNode::VarType::ID_TYPE)
    {
        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            string type = typenode->get_type_name();
            CurrentTable->addVar(id, rn, type);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto array_type = typenode->get(0)->DynamicCast<ArrayTypeNode>();
        auto info = array_type->info();
        string type = array_type->type();
        int amount = info->GetDimsum();
        vector<pair<int,int>> bound;

        for(auto j:info->GetDimensions())
        {
            bound.push_back(make_pair(j.lowbound, j.upbound));
        }

        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addArray(id, rn, type, amount, bound);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::STRING_TYPE)
    {
        auto string_type = typenode->get(0)->DynamicCast<StringTypeNode>();
        auto string_info = string_type->type();
        string type = "STRING";
        int amount = string_info->GetLen();

        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addString(id, rn, type, amount);
        }
    }
    else if(typenode->GetVarType() == TypeNode::VarType::RECORD_TYPE)
    {
        SymbolTable * subTable = new SymbolTable();
        
        for(auto i:idlist->Lists())
        {
            string id = i->get_value<string>();
            int rn = i->get_rownum();
            CurrentTable->addRecord(id, rn, subTable);
        }

        SymbolTable* PreviousTable = CurrentTable;
        CurrentTable = subTable;

        typenode->get(0)->accept(this);

        CurrentTable = PreviousTable;
    }

    
}

void SemanticVisitor::visit(SubprogramDeclaration *subprogramdeclaration)
{
    SymbolTable *subTable = new SymbolTable();
    CurrentTable          = subTable;
    subprogramdeclaration->get(0)->DynamicCast<SubprogramHead>()->accept(this);
    subprogramdeclaration->get(1)->DynamicCast<SubprogramBody>()->accept(this);
    CurrentTable = MainTable;

}

void SemanticVisitor::visit(SubprogramHead *subprogramhead)
{
    auto type = subprogramhead->get_type();
    string id = subprogramhead->get_id();
    int amount = 0;
    auto formal_param = subprogramhead->get(1)->DynamicCast<FormalParam>();

    if(formal_param->getCnodeList().size() != 0)
    {
        auto list = formal_param->get(0)->DynamicCast<ParamLists>()->Lists();
        for(auto p:list)
        {
            auto ptype = p->get_type();
            std::vector<LeafNode*> idlist;
            TypeNode* idtype;
            if(ptype == ParamList::ParamType::VarParam)
            {
                idlist = p->get(0)->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(0)->get(1)->DynamicCast<TypeNode>();
                for(auto id:idlist)
                {
                    CurrentTable->addVarPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    id->set_ref(true);
                    amount++;
                }
            }
            else
            {
                idlist = p->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(1)->DynamicCast<TypeNode>();
                for(auto id:idlist)
                {
                    CurrentTable->addPara(id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    amount++;
                }
            }
            
        }
    }

    if(type == SubprogramHead::SubprogramType::PROC)
    {
        MainTable->addProcedure(subprogramhead->get_id(), subprogramhead->get_rownum(), amount, CurrentTable);
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", amount, "");
    }
    else
    {
        auto ret_type = subprogramhead->get(2)->DynamicCast<TypeNode>()->get_type_name();
        MainTable->addFunction(subprogramhead->get_id(), subprogramhead->get_rownum(),ret_type, amount, CurrentTable);
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", amount, ret_type);
    }
}

void SemanticVisitor::visit(VariableList* variablelist)
{
    vector<AstNode* > lists = variablelist->Lists();
    for(auto a : lists){
        Variable* var = a->DynamicCast<Variable>();
        if(var->get_vn() == "unknown"){
            var->accept(this);
        }
    }
}

void SemanticVisitor::visit(Variable *variable)
{
    LeafNode* leaf_node = variable->get(0)->DynamicCast<LeafNode>();
    string id = leaf_node->get_value<string>();
    auto record_info = findID(CurrentTable, id, 0);
    if(record_info != NULL){
        //暂未考虑记录型
        variable->set_vn(record_info->type); 
    }
    else{
        //子表未找到，到主表找
        record_info = findID(MainTable, id, 0);
        if(record_info != NULL){
            variable->set_vn(record_info->type); 
        }
        else{
            //错误处理，找到未定义变量

        }
    }
}

void SemanticVisitor::visit(AssignopStatement *assignstatement)
{
    LeafNode* leaf_node = assignstatement->get(0)->get(0)->DynamicCast<LeafNode>();
    auto record_info = findID(MainTable, leaf_node->get_value<string>(), 0);
    if(record_info != NULL){
        assignstatement->set_type(AssignopStatement::LeftType::FUNCID);
    }
}

void SemanticVisitor::visit(ExpressionList *expressionlist)
{
    vector<AstNode*> lists = expressionlist->Lists();
    for(auto a : lists){
        Expression* exp = a->DynamicCast<Expression>();
        if(exp->GetExpType() == "unknown"){
            exp->accept(this);
        } 
    }
}

void SemanticVisitor::visit(Expression *expression)
{
    if(expression->GetExpType() == "unknown"){
        switch (expression->GetGraType()) {
            case Expression::GrammarType::DOUBLE:
            {
                if(expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown"){
                    expression->get(0)->accept(this);
                }
                string sexpression_type1 = expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType();
                if(expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown"){
                    expression->get(1)->accept(this);
                }
                string sexpression_type2 = expression->get(1)->DynamicCast<SimpleExpression>()->GetExpType();
                // 类型检查
                if((sexpression_type2 == "integer" || sexpression_type2 == "char" || sexpression_type2 == "real")&&
                (sexpression_type1 == "integer" || sexpression_type1 == "char" || sexpression_type1 == "real")){
                    expression->SetExpType("boolean");
                }
                else{

                }
            }
            case Expression::GrammarType::SINGLE:
            {
                expression->get(0)->accept(this);
                string etype = expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType();
                expression->SetExpType(etype);
                break;
            }
        }
    }
}

void SemanticVisitor::visit(SimpleExpression *sexpression)
{
    if(sexpression->GetExpType() == "unknown"){
        switch (sexpression->GetSymType()) {
            case SimpleExpression::SymbolType::SINGLE:
            {
                sexpression->get(0)->accept(this);
                string stype = sexpression->get(0)->DynamicCast<Term>()->GetTerType();
                sexpression->SetExpType(stype);
                break;
            }
            case SimpleExpression::SymbolType::PLUS_:
            case SimpleExpression::SymbolType::MINUS_:
            {
                if(sexpression->getCnodeList().size() == 1){
                    if(sexpression->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                        sexpression->get(0)->accept(this);
                    }
                    string term_type = sexpression->get(0)->DynamicCast<Term>()->GetTerType();
                    //类型检查
                    if(term_type == "real" || term_type == "interger"){
                        sexpression->SetExpType(term_type);
                    }
                    else{
                        //error
                    }
                }
                else{
                    if(sexpression->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                        sexpression->get(0)->accept(this);
                    }
                    string term_type1 = sexpression->get(0)->DynamicCast<Term>()->GetTerType();
                    if(sexpression->get(1)->DynamicCast<Term>()->GetTerType() == "unknown"){
                        sexpression->get(1)->accept(this);
                    }
                    string term_type2 = sexpression->get(1)->DynamicCast<Term>()->GetTerType();
                    //类型检查
                    if((term_type1 == "real" || term_type1 == "interger")&&(term_type2 == "real" || term_type2 == "interger")){
                        if(term_type1 == "real" || term_type1 == "real"){
                            sexpression->SetExpType("real");
                        }
                        else{
                            sexpression->SetExpType("integer");
                        }
                    }
                    else{
                        //error
                    }
                }
                break;
            }
            case SimpleExpression::SymbolType::OR_:
            {
                if(sexpression->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                    sexpression->get(0)->accept(this);
                }
                string term_type1 = sexpression->get(0)->DynamicCast<Term>()->GetTerType();
                if(sexpression->get(1)->DynamicCast<Term>()->GetTerType() == "unknown"){
                    sexpression->get(1)->accept(this);
                }
                string term_type2 = sexpression->get(1)->DynamicCast<Term>()->GetTerType();
                //类型检查
                if(term_type1 == "boolean" && term_type2 == "boolean" ){
                        sexpression->SetExpType("boolean");
                }
                else{
                    //error
                }
                break;
            }
        }
    }
}

void SemanticVisitor::visit(Term *term)
{
    if(term->GetTerType() == "unknown"){
        switch(term->GetSymType()){
            case Term::SymbolType::SINGLE:
            {
                term->get(0)->accept(this);
                string fac_type = term->get(0)->DynamicCast<Factor>()->GetFacType();
                term->SetTerType(fac_type);
                break;
            }
            case Term::SymbolType::MULTIPLY:
            case Term::SymbolType::DEVIDE:
            {
                if(term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if(term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown"){
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if((term_type == "real" || term_type == "integer" || term_type == "char")&&
                (fac_type == "real" || fac_type == "integer" || term_type == "char"))
                {
                    if(term_type == "real" || fac_type == "real")
                    {
                        term->SetTerType("real");
                    }
                    else
                    {
                        term->SetTerType("integer");
                    }
                }
                else{
                    //错误处理
                }
                break;
            }
            case Term::SymbolType::MOD:
            {
                if(term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if(term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown"){
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if((term_type == "integer" || term_type == "char")&&(fac_type == "integer" || term_type == "char"))
                {
                    term->SetTerType("integer");
                }
                else{
                    //错误处理
                }
                break;
            }
            case Term::SymbolType::AND:
            {
                if(term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown"){
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if(term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown"){
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if( term_type == "boolean" && fac_type == "boolean")
                {
                    term->SetTerType("boolean");
                }
                else{
                    //错误处理
                }
                break;
            }
        }
    }
}

void SemanticVisitor::visit(Factor *factor)
{
    if(factor->GetFacType() == "unknown"){
        switch(factor->get_type()){
            case Factor::GrammerType::ID_EXP_LIST:
            {
            // 对于函数直接获取其返回值类型
                auto id = factor->get(0)->DynamicCast<LeafNode>()->get_value<string>();
                TableRecord *tr = findID(MainTable, id, 0);
                factor->SetFacType(tr->type);
                break;
            }
            case Factor::GrammerType::VARIABLE:
            {
            // 对于变量直接获取其类型
                factor->get(0)->accept(this);
                Variable* var = factor->get(0)->DynamicCast<Variable>();
                factor->SetFacType(var->get_vn());
                break;
            }
            case Factor::GrammerType::EXP:
            {
            // 对于表达式直接获取表达式的类型
                Expression* exp = factor->get(0)->DynamicCast<Expression>();
                if(exp->GetExpType() == "unknown"){
                    factor->get(0)->accept(this);
                }
                factor->SetFacType(exp->GetExpType());
                break;
            }
            case Factor::GrammerType::UMINUS_:
            {
            // 对于负号直接与子节点的factor类型相同
                Factor* fac = factor->get(0)->DynamicCast<Factor>();
                if(fac->GetFacType() == "unknown"){
                    factor->get(0)->accept(this);
                }
                string fac_type = fac->GetFacType();
            // 类型检查(只有实数、整数、字符可以)
                if(fac_type == "real" || fac_type == "char" || fac_type == "integer"){
                    factor->SetFacType(fac->GetFacType());
                }
                else{

                }
                break;
            }
            case Factor::GrammerType::NOT_:
            {
                Factor* fac = factor->get(0)->DynamicCast<Factor>();
                if(fac->GetFacType() == "unknown"){
                    factor->get(0)->accept(this);
                }
                string fac_type = fac->GetFacType();
            // 类型检查(只有布尔值可以)
                if(fac_type == "boolean" ){
                    factor->SetFacType(fac->GetFacType());
                }
                else{
                    
                }
                break;
            }
            default:
                break;
        }
    }
}


std::vector<ParamList *> ParamLists::Lists()
{
    std::vector<ParamList *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_PARAM_LIST) //如果多层 进入循环
    {
        ParamList *ln = cur_node->cnode_list[1]->DynamicCast<ParamList>();
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<ParamLists>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    ParamList *ln = (*cur_node->cnode_list.rbegin())->DynamicCast<ParamList>();
    lists.insert(lists.begin(), ln);
    return lists;
}

std::vector<tuple<int,string,ConstValue *>> ConstDeclaration::Lists()
{
    std::vector<tuple<int,string,ConstValue *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_ID) //如果多层 进入循环
    {
        int rn = cur_node->get_rownum();
        auto id = cur_node->get(1)->DynamicCast<LeafNode>()->get_value<string>();
        auto const_value = cur_node->get(2)->DynamicCast<LeafNode>()->getConstValue();
        tuple<int,string,ConstValue *> ln = make_tuple(rn,id,const_value);
        
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<ConstDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    int rn = cur_node->get_rownum();
    auto id = cur_node->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    auto const_value = cur_node->get(1)->DynamicCast<LeafNode>()->getConstValue();
    tuple<int,string,ConstValue *> ln = make_tuple(rn,id,const_value);
        
    lists.insert(lists.begin(), ln);

    return lists;
}

std::vector<tuple<vector<LeafNode *>,AstNode *>> VarDeclaration::Lists()
{
    std::vector<tuple<vector<LeafNode *>,AstNode *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_DECL) //如果多层 进入循环
    {
        auto idlist = cur_node->get(1)->DynamicCast<IdList>()->Lists();
        auto node = cur_node->get(2);
        tuple<vector<LeafNode *>,AstNode *> ln = make_tuple(idlist,node);
        
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<VarDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    auto idlist = cur_node->get(1)->DynamicCast<IdList>()->Lists();
        auto node = cur_node->get(2);
        tuple<vector<LeafNode *>,AstNode *> ln = make_tuple(idlist,node);
        
        lists.insert(lists.begin(), ln);

    return lists;

}

std::vector<AstNode *> ExpressionList::Lists()
{
    std::vector<AstNode *> lists;
    auto *cur_node    = this;
    ExpressionType gtype = expression_type;

    while (gtype == ExpressionType::MULTIPLE) //如果多层 进入循环
    {
        AstNode * ln = cur_node->cnode_list[1];
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<ExpressionList>();
        gtype    = cur_node->expression_type;
    }

    // 插入最后一个节点
    AstNode * ln = cur_node->cnode_list[1];
    lists.insert(lists.begin(), ln);
    return lists;
}

std::vector<AstNode *> VariableList::Lists()
{
    std::vector<AstNode *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::VAR_LIST_VAR) //如果多层 进入循环
    {
        AstNode * ln = cur_node->cnode_list[1];
        lists.insert(lists.begin(), ln);
        
        cur_node = cur_node->cnode_list[0]->DynamicCast<VariableList>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    AstNode * ln = cur_node->cnode_list[1];
    lists.insert(lists.begin(), ln);
    return lists;
}

}