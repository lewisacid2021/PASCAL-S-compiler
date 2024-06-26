#include "ast.h"
#include "symbolTable.h"
#include "type.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <sys/types.h>
#include <tuple>
#include <utility>
#include <vector>

using std::string;
using std::vector;

extern SymbolTable *MainTable;
extern SymbolTable *CurrentTable;
extern TypeTable *TheTypeTable;
extern int math_flag;
extern int semantic_error;

//检查是否与库函数重名
bool checkDuplicateNameError(string id, int lineNumber)
{
    for (int i = 0; i < 4; i++) {
        if (id == MainTable->records[i]->id) {
            //与库函数同名
            std::cout << "Error: Same name as library function. Line: " << lineNumber << std::endl;
            return true;
        }
    }
    return false;
}

namespace ast {
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
    int rn    = programhead->get(0)->DynamicCast<LeafNode>()->get_rownum();
    set<string> lib;
    lib.insert("read");
    lib.insert("write");
    lib.insert("writeln");
    lib.insert("exit");
    //检查主程序是否与库函数重名
    if (lib.count(id))
    {
        //错误处理
        std::cout << "Error: Same name as library function. Line: " << programhead->get_rownum() << std::endl;
    }

    //添加read过程
    MainTable->addProcedure("read", -1, -1, NULL);
    //添加write过程
    MainTable->addProcedure("write", -1, -1, NULL);
    //添加writeln过程
    MainTable->addProcedure("writeln", -1, -1, NULL);
    //添加exit过程
    MainTable->addProcedure("exit", -1, 0, NULL);
}

void SemanticVisitor::visit(ConstDeclaration *constdeclaration)
{
    auto lists = constdeclaration->Lists();
    for (auto p : lists)
    {
        string id           = std::get<1>(p);
        int rn              = std::get<0>(p);

        TableRecord *record = findID(CurrentTable, id, 1);
        if (checkDuplicateNameError(id, rn))
        {
            return;
        } else if (record != NULL)
        {
            //重定义错误
            std::cout << "Error: Redefine. Line: " << constdeclaration->get_rownum() << std::endl;
            return;
        }

        string type;
        string value;
        ConstValue *const_value                     = std::get<2>(p);
        ConstValue::ConstvalueType const_value_type = const_value->type();
        bool isMinus                                = const_value->get_uminus();

        switch (const_value_type) {
            case ConstValue::ConstvalueType::INTEGER:
                type  = "integer";
                value = std::to_string(const_value->get<int>());
                break;
            case ConstValue::ConstvalueType::REAL:
                type  = "real";
                value = const_value->get<string>();
                break;
            case ConstValue::ConstvalueType::BOOLEAN:
                type = "boolean";
                if (const_value->get<bool>() == true)
                    value = "true";
                else
                    value = "false";
                break;
            case ConstValue::ConstvalueType::CHAR:
                type = "char";
                value.push_back(const_value->get<char>());
                break;
            case ConstValue::ConstvalueType::STRING:
                type  = "string";
                value = const_value->get<string>();
                break;
        }

        CurrentTable->addConst(id, rn, type, isMinus, value);
    }
}

void SemanticVisitor::visit(RecordDeclaration *recorddeclaration)
{
    string id;
    int rn;
    if (recorddeclaration->GetGrammarType() == RecordDeclaration::GrammarType::MULTI_DECLARATION) {
        recorddeclaration->get(0)->accept(this);

        id = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_value<string>();
        rn = recorddeclaration->get(1)->DynamicCast<LeafNode>()->get_rownum();
    } else {
        id = recorddeclaration->get(0)->DynamicCast<LeafNode>()->get_value<string>();
        rn = recorddeclaration->get(0)->DynamicCast<LeafNode>()->get_rownum();
    }
    TableRecord *record = findID(CurrentTable, id, 1);
    if (checkDuplicateNameError(id, rn))
    {
        return;
    } else if (record != NULL)
    {
        //重定义错误
        std::cout << "Error: Redefine. Line: " << recorddeclaration->get_rownum() << std::endl;
        return;
    }

    SymbolTable *subTable = new SymbolTable();

    TheTypeTable->addType(id, false, subTable);

    SymbolTable *PreviousTable = CurrentTable;
    CurrentTable               = subTable;

    if (recorddeclaration->GetGrammarType() == RecordDeclaration::GrammarType::MULTI_DECLARATION) {
        recorddeclaration->get(2)->accept(this);
    } else
        recorddeclaration->get(1)->accept(this);
    CurrentTable = PreviousTable;
}

void SemanticVisitor::visit(VarDeclaration *vardeclaration)
{
    IdList *idlist;
    TypeNode *typenode;

    if (vardeclaration->GetGrammarType() == VarDeclaration::GrammarType::SINGLE_DECL)
    {
        idlist   = vardeclaration->get(0)->DynamicCast<IdList>();
        typenode = vardeclaration->get(1)->DynamicCast<TypeNode>();
    } else
    {
        idlist   = vardeclaration->get(1)->DynamicCast<IdList>();
        typenode = vardeclaration->get(2)->DynamicCast<TypeNode>();
        vardeclaration->get(0)->accept(this);
    }

    if (typenode->GetVarType() == TypeNode::VarType::ID_TYPE)
    {
        for (auto i : idlist->Lists())
        {
            string id           = i->get_value<string>();
            int rn              = i->get_rownum();

            TableRecord *record = findID(CurrentTable, id, 1);
            if (checkDuplicateNameError(id, rn))
            {
                return;
            } else if (record != NULL)
            {
                //重定义错误
                std::cout << "Error: Redefine. Line: " << vardeclaration->get_rownum() << std::endl;
                return;
            }

            string type = typenode->get_type_name();
            if(TheTypeTable->findID(type) != NULL && TheTypeTable->findID(type)->RecordTable){
                CurrentTable->addRecord(id, type, rn, TheTypeTable->findID(type)->RecordTable);
            }
            else
                CurrentTable->addVar(id, rn, type);
        }
    } else if (typenode->GetVarType() == TypeNode::VarType::ARRAY_TYPE)
    {
        auto array_type = typenode->get(0)->DynamicCast<ArrayTypeNode>();
        auto info       = array_type->info();
        string type     = array_type->type();
        int amount      = info->GetDimsum();
        vector<pair<int, int>> bound;

        for (auto j : info->GetDimensions())
        {
            bound.push_back(make_pair(j.lowbound, j.upbound));
        }
        //数组上下界检查
        for (auto p : bound)
        {
            if (p.first > p.second)
            {
                cout << "Array low bound higher than up bound at" << vardeclaration->get_rownum() <<endl;
                //数组下界大于上界
            }
        }

        for (auto i : idlist->Lists())
        {
            string id           = i->get_value<string>();
            int rn              = i->get_rownum();

            TableRecord *record = findID(CurrentTable, id, 1);
            if (checkDuplicateNameError(id, rn))
            {
                return;
            } else if (record != NULL)
            {
                //重定义错误
                std::cout << "Error: Redefine. Line: " << vardeclaration->get_rownum() << std::endl;
                return;
            }

            CurrentTable->addArray(id, rn, type, amount, bound);
        }
    } else if (typenode->GetVarType() == TypeNode::VarType::STRING_TYPE)
    {
        auto string_type = typenode->get(0)->DynamicCast<StringTypeNode>();
        auto string_info = string_type->type();
        string type      = "STRING";
        int amount       = string_info->GetLen();

        for (auto i : idlist->Lists())
        {
            string id           = i->get_value<string>();
            int rn              = i->get_rownum();

            TableRecord *record = findID(CurrentTable, id, 1);
            if (checkDuplicateNameError(id, rn))
            {
                return;
            } else if (record != NULL)
            {
                //重定义错误
                std::cout << "Error: Redefine. Line: " << vardeclaration->get_rownum() << std::endl;
                return;
            }

            CurrentTable->addString(id, rn, type, amount);
        }
    } else if (typenode->GetVarType() == TypeNode::VarType::RECORD_TYPE)
    {
        SymbolTable *subTable = new SymbolTable();
        string recordname     = "record" + std::to_string(TheTypeTable->records.size());
        while (findID(CurrentTable, recordname, 1) != NULL)
        {
            recordname.append("_");
        }
        TheTypeTable->addType(recordname, false, subTable);

        for (auto i : idlist->Lists())
        {
            string id           = i->get_value<string>();
            int rn              = i->get_rownum();

            TableRecord *record = findID(CurrentTable, id, 1);
            if (checkDuplicateNameError(id, rn))
            {
                return;
            } else if (record != NULL)
            {
                //重定义错误
                std::cout << "Error: Redefine. Line: " << vardeclaration->get_rownum() << std::endl;
                return;
            }

            CurrentTable->addRecord(id, recordname, rn, subTable);
        }

        SymbolTable *PreviousTable = CurrentTable;
        CurrentTable               = subTable;

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
    auto type           = subprogramhead->get_type();

    TableRecord *record = findID(MainTable, subprogramhead->get_id(), 1);
    if (record != NULL)
    {
        //重定义错误,返回主表检查
        std::cout << "Error: Redefine. Line: " << subprogramhead->get_rownum() << std::endl;
        return;
    }

    if (type == SubprogramHead::SubprogramType::PROC)
    {
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", 0, "");
    } else
    {
        auto ret_type = subprogramhead->get(2)->DynamicCast<TypeNode>()->get_type_name();
        CurrentTable->addProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "function", 0, ret_type);
    }

    int amount        = 0;
    auto formal_param = subprogramhead->get(1)->DynamicCast<FormalParam>();


    if (formal_param->getCnodeList().size() != 0)
    {
        auto list = formal_param->get(0)->DynamicCast<ParamLists>()->Lists();
        for (auto p : list)
        {
            auto ptype = p->get_type();
            std::vector<LeafNode *> idlist;
            TypeNode *idtype;
            if (ptype == ParamList::ParamType::VarParam)
            {
                idlist = p->get(0)->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(0)->get(1)->DynamicCast<TypeNode>();
                for (auto id : idlist)
                {
                    TableRecord *para_record = findID(CurrentTable, id->get_value<string>(), 1);

                    if (para_record != NULL)
                    {
                        //重定义错误
                        std::cout << "Error: Redefine. Line: " << subprogramhead->get_rownum() << std::endl;
                        return;
                    }
                    if (idtype->get_type_name() == "array") {
                        auto array_type = idtype->get(0)->DynamicCast<ArrayTypeNode>();
                        auto info       = array_type->info();
                        vector<pair<int, int>> bound;
                        for (auto j : info->GetDimensions())
                        {
                            bound.push_back(make_pair(j.lowbound, j.upbound));
                        }
                        CurrentTable->addArrayVarPara("array", id->get_value<string>(), id->get_rownum(), idtype->get(0)->DynamicCast<ArrayTypeNode>()->type(), bound);
                    } else if (idtype->get_type_name() == "integer" || idtype->get_type_name() == "real" || idtype->get_type_name() == "char" || idtype->get_type_name() == "boolean") {
                        CurrentTable->addVarPara("variant", id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    } else {
                        CurrentTable->addVarPara("record", id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    }
                    id->set_ref(true);
                    amount++;
                }
            } else
            {
                idlist = p->get(0)->get(0)->DynamicCast<IdList>()->Lists();
                idtype = p->get(0)->get(1)->DynamicCast<TypeNode>();
                for (auto id : idlist)
                {
                    TableRecord *para_record = findID(CurrentTable, id->get_value<string>(), 1);
                    if (para_record != NULL)
                    {
                        //重定义错误
                        std::cout << "Error: Redefine. Line: " << subprogramhead->get_rownum() << std::endl;
                        return;
                    }
                    if (idtype->get_type_name() == "array") {
                        auto array_type = idtype->get(0)->DynamicCast<ArrayTypeNode>();
                        auto info       = array_type->info();
                        vector<pair<int, int>> bound;
                        for (auto j : info->GetDimensions())
                        {
                            bound.push_back(make_pair(j.lowbound, j.upbound));
                        }
                        CurrentTable->addArrayPara("array", id->get_value<string>(), id->get_rownum(), idtype->get(0)->DynamicCast<ArrayTypeNode>()->type(), bound);
                    } else if (idtype->get_type_name() == "integer" || idtype->get_type_name() == "real" || idtype->get_type_name() == "char" || idtype->get_type_name() == "boolean") {
                        CurrentTable->addPara("variant", id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    } else {
                        CurrentTable->addPara("record", id->get_value<string>(), id->get_rownum(), idtype->get_type_name());
                    }
                    amount++;
                }
            }
        }
    }

    if (type == SubprogramHead::SubprogramType::PROC)
    {
        MainTable->addProcedure(subprogramhead->get_id(), subprogramhead->get_rownum(), amount, CurrentTable);
        CurrentTable->records[0]->setProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "procedure", amount, "");
    } else
    {
        auto ret_type = subprogramhead->get(2)->DynamicCast<TypeNode>()->get_type_name();
        MainTable->addFunction(subprogramhead->get_id(), subprogramhead->get_rownum(), ret_type, amount, CurrentTable);
        CurrentTable->records[0]->setProgramName(subprogramhead->get_id(), subprogramhead->get_rownum(), "function", amount, ret_type);
    }
}

void SemanticVisitor::visit(VariableList *variablelist)
{
    vector<AstNode * > lists = variablelist->Lists();

    std::vector<std::string> *type_list;
    for (auto a : lists) {
        Variable *var = a->DynamicCast<Variable>();
        if (var->get_vn() == "unknown") {
            var->accept(this);
        }
        type_list->emplace_back(var->get_vn());
    }
    variablelist->set_types(type_list);
}

void SemanticVisitor::visit(Variable *variable)
{
    LeafNode *leaf_node = variable->get(0)->DynamicCast<LeafNode>();
    string id           = leaf_node->get_value<string>();
    auto record_info    = findID(CurrentTable, id, 0);
    if (record_info != NULL) {
        //暂未考虑记录型
        if (record_info->flag == "array") {
            variable->set_vn(record_info->type);
        }
        else if (record_info->flag == "record"||(TheTypeTable->findID(record_info->type)!=NULL&&TheTypeTable->findID(record_info->type)->RecordTable)){
            if(variable->getCnodeList().size() == 1){
                cout << "Error: Not support record direct operation. Line: " << variable->get_rownum() << std::endl;
                return;
            } else {
                auto namelist = variable->get(1)->DynamicCast<IDVarParts>()->get_pointer();
                SymbolTable *curtable;
                curtable = TheTypeTable->findID(record_info->type)->RecordTable;
                for (auto p : *namelist) {
                    if (p != "none") {
                        if (curtable != NULL) {
                            auto r = findID(curtable, p, 1);
                            if (r == NULL) {
                                //错误处理，record没有该子成员
                                std::cout << "Error: Record does not have this child member. Line: " << variable->get_rownum() << std::endl;
                            } else {
                                variable->set_vn(r->type);
                                curtable = r->subSymbolTable;
                            }
                        } else {
                            //错误处理,不是record类型
                            std::cout << "Error: Not a record type. Line: " << variable->get_rownum() << std::endl;
                        }
                    }
                }
            }
        } else {
            variable->set_vn(record_info->type);
        }
    }
}

void SemanticVisitor::visit(AssignopStatement *assignstatement)
{
    string id        = assignstatement->get(0)->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    auto record_info = findID(CurrentTable, id, 0);
    if (record_info == NULL)
    {
        cout << "Error: Undefined. Line: " << assignstatement->get_rownum() << endl;
        return;
    }

    assignstatement->get(0)->accept(this);
    string left_type = assignstatement->get(0)->DynamicCast<Variable>()->get_vn();
    string right_type;
    auto expression = assignstatement->get(1)->DynamicCast<Expression>();
    if (expression->GetExpType() == "unknown") {
        expression->accept(this);
    }
    right_type = expression->GetExpType();
    // cout<<left_type<<" "<<right_type<<endl;

    if (record_info->flag == "constant") {
        //错误处理，左值不能为常量
        std::cout << "Error: Lvalue cannot be constant. Line: " << assignstatement->get_rownum() << std::endl;
        return;
    }
    if (record_info->flag == "function" || record_info->flag == "procedure") {
        // 使用非作用域内函数
        return;
    }
    if (record_info->flag == "(sub)program name") {
        if (record_info->type == "") {
            //错误处理，过程无返回值
            std::cout << "Error: The procedure has no return value. Line: " << assignstatement->get_rownum() << std::endl;
            return;
        }

        assignstatement->set_type(AssignopStatement::LeftType::FUNCID);
    }
    if (left_type != right_type && !(left_type == "real" && right_type == "integer")) {
        //错误处理，类型不匹配  影响oj
        std::cout << "Error: Type mismatch. Line: "  << assignstatement->get_rownum() << std::endl;
    }
}

void SemanticVisitor::visit(ProcedureCall *procedurecall)
{
    string id        = procedurecall->get_id();
    if (id == "break") {  //遇到break直接return
        return;
    }
    auto record_info = findID(MainTable, id, 1);    
    if (record_info->id == "write") {
        if (procedurecall->get_type() == ProcedureCall::ProcedureType::NO_LIST) {
            //错误处理,write的参数个数不能为0
            semantic_error = 1;
            std::cout << "Error: The number of read() and write() arguments cannot be 0. Line: " << procedurecall->get_rownum() << std::endl;
            return;
        }
    }
    if (record_info->id == "writeln") {
        if (procedurecall->get_type() == ProcedureCall::ProcedureType::NO_LIST) {
            //错误处理,writeln的参数个数不能为0
            semantic_error = 1;
            std::cout << "Error: The number of readln() arguments cannot be 0. Line: " << procedurecall->get_rownum() << std::endl;
            return;
        }
    }
    if (record_info->id == "read") {  //参数只能是变量或数组元素，不能是常量、表达式等
        if (procedurecall->get_type() == ProcedureCall::ProcedureType::NO_LIST) {
            //错误处理,read、write的参数个数不能为0
            std::cout << "Error: The number of read() and write() arguments cannot be 0. Line: " << procedurecall->get_rownum() << std::endl;
            semantic_error = 1;
            return;
        }
    }
    
    if(record_info == NULL){
        //错误处理，未定义   //影响OJ
        std::cout << "Error: Undefined. Line: " << procedurecall->get_rownum() << std::endl;
        return;
    }

    if (procedurecall->get_type() == ProcedureCall::ProcedureType::NO_LIST) {
        if (record_info->id == "exit") {
            if (CurrentTable->records[0]->programInfo == "function") {
                // 错误处理，function需要参数
                return;
            }
        }
    }

    if (procedurecall->get_type() == ProcedureCall::ProcedureType::EXP_LIST) {
        procedurecall->get(-1)->accept(this);
        auto exp_types = procedurecall->get(-1)->DynamicCast<ExpressionList>()->get_types();
        if (record_info->id == "write") {
            return;
        }
        if (record_info->id == "writeln") {
            return;
        }
        if (record_info->id == "read") {  //参数只能是变量或数组元素，不能是常量、表达式等
            return;
        }
        if (record_info->id == "exit") {
            if (CurrentTable->records[0]->programInfo == "procedure") {
                // 错误处理，procedure不需要参数
                return;
            }
            if (exp_types->size() != 1) {
                // 错误处理,exit的参数个数只能为1
                return;
            }
            // 正常
            return;
        }
        
        if (exp_types->size() != record_info->amount) {  //checked
            //错误处理，参数数量不匹配
            std::cout << "Error: The number of arguments does not match. Line: " << procedurecall->get_rownum() << std::endl;
            semantic_error = 1;
            return;
        }
        for (int i = 0; i < exp_types->size(); i++) {
            string para_type = record_info->subSymbolTable->records[i + 1]->type;
            if (para_type != (*exp_types)[i] && !(para_type == "real" &&(*exp_types)[i] == "integer")) {
                //错误处理，参数类型错误  影响OJ
                std::cout << "Error: Param Type error. Line: " << procedurecall->get_rownum() << std::endl;   
            }
        }
    }
}

void SemanticVisitor::visit(IfStatement *ifstatement)
{
    auto expression = ifstatement->get(0)->DynamicCast<Expression>();
    if (expression->GetExpType() == "unknown") {
        expression->accept(this);
    }
    string expression_type = expression->GetExpType();
    if (expression_type != "boolean") {
        //错误处理，类型错误
        std::cout << "Error: IFcondition Type error. Line: " << ifstatement->get_rownum() << std::endl;
    }
    ifstatement->get(1)->accept(this);
    auto elsepart = ifstatement->get(2)->DynamicCast<ElsePart>();
    if (elsepart->get_type() == ElsePart::ELSEType::ELSE_STATEMENT)
        elsepart->get(0)->accept(this);
}

void SemanticVisitor::visit(LoopStatement *loopstatement)
{
    switch (loopstatement->get_type()) {
        case LoopStatement::LoopType::FORUP:
        case LoopStatement::LoopType::FORDOWN:
        {
            string id        = loopstatement->get(0)->DynamicCast<LeafNode>()->get_value<string>();
            auto record_info = findID(CurrentTable, id, 0);
            if (record_info == NULL)
            {
                //错误处理，循环变量未定义
                std::cout << "Error: Loop variable undefined. Line: " << loopstatement->get_rownum() << std::endl;
                return;
            }
            if (!(record_info->flag == "variant"))
            {
                //错误处理，不能作为循环变量
                std::cout << "Error: Cannot be used as a loop variable. Line: " << loopstatement->get_rownum() << std::endl;
            }
            if (record_info->type != "integer")
            {
                //错误处理，循环变量类型错误
                std::cout << "Error: Loop variable type error. Line: " << loopstatement->get_rownum() << std::endl;
            }
            auto expression1 = loopstatement->get(1)->DynamicCast<Expression>();
            auto expression2 = loopstatement->get(2)->DynamicCast<Expression>();
            if (expression1->GetExpType() == "unknown") {
                expression1->accept(this);
            }
            string expression_type1 = expression1->GetExpType();
            if (expression_type1 != "integer")
            {
                //错误处理，类型错误
                std::cout << "Error: Looptimes Type error. Line: " << loopstatement->get_rownum() << std::endl;
            }
            if (expression2->GetExpType() == "unknown") {
                expression2->accept(this);
            }
            string expression_type2 = expression1->GetExpType();
            if (expression_type2 != "integer")
            {
                //错误处理，类型错误
                std::cout << "Error: Looptimes Type error. Line: " << loopstatement->get_rownum() << std::endl;
            }
            loopstatement->get(3)->accept(this);
            break;
        }
        case LoopStatement::LoopType::WHILE_:
        {
            auto expression = loopstatement->get(0)->DynamicCast<Expression>();
            if (expression->GetExpType() == "unknown") {
                expression->accept(this);
            }
            string expression_type = expression->GetExpType();
            if (expression_type != "boolean") {
                //错误处理，类型错误
                std::cout << "Error: Looptimes Type error. Line: " << loopstatement->get_rownum() << std::endl;
            }
            loopstatement->get(0)->accept(this);
            break;
        }
        case LoopStatement::LoopType::REPEAT_:
        {
            auto expression = loopstatement->get(1)->DynamicCast<Expression>();
            if (expression->GetExpType() == "unknown") {
                expression->accept(this);
            }
            string expression_type = expression->GetExpType();
            if (expression_type != "boolean") {
                //错误处理，类型错误
                std::cout << "Error: Looptimes Type error. Line: " << loopstatement->get_rownum() << std::endl;
            }
            loopstatement->get(1)->accept(this);
            break;
        }
    }
}

void SemanticVisitor::visit(ExpressionList *expressionlist)
{
    vector<AstNode *> lists             = expressionlist->Lists();
    std::vector<std::string> *exp_types = expressionlist->get_types();
    for (int i = 0; i < exp_types->size(); i++) {
        Expression *exp = lists[i]->DynamicCast<Expression>();
        if ((*exp_types)[i] == "unknown") {
            exp->accept(this);
        }
        (*exp_types)[i] = exp->GetExpType();
    }
}

void SemanticVisitor::visit(Expression *expression)
{
    if (expression->GetExpType() == "unknown") {
        switch (expression->GetGraType()) {
            case Expression::GrammarType::DOUBLE:
            {
                if (expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown") {
                    expression->get(0)->accept(this);
                }
                string sexpression_type1 = expression->get(0)->DynamicCast<SimpleExpression>()->GetExpType();
                if (expression->get(1)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown") {
                    expression->get(1)->accept(this);
                }
                string sexpression_type2 = expression->get(1)->DynamicCast<SimpleExpression>()->GetExpType();
                // 类型检查
                if ((sexpression_type2 == "integer" || sexpression_type2 == "char" || sexpression_type2 == "real") &&
                    (sexpression_type1 == "integer" || sexpression_type1 == "char" || sexpression_type1 == "real")) {
                    expression->SetExpType("boolean");
                } else if(sexpression_type2 == "boolean" && sexpression_type1 == "boolean"){
                    expression->SetExpType("boolean");
                }else{
                    std::cout << "Error:Expression Type error. Line: " << expression->get_rownum() << std::endl;
                }
                break;
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
    if (sexpression->GetExpType() == "unknown") {
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
                if (sexpression->getCnodeList().size() == 1) {
                    if (sexpression->get(0)->DynamicCast<Term>()->GetTerType() == "unknown") {
                        sexpression->get(0)->accept(this);
                    }
                    string term_type = sexpression->get(0)->DynamicCast<Term>()->GetTerType();
                    //类型检查
                    if (term_type == "real" || term_type == "integer" || term_type == "char") {
                        sexpression->SetExpType(term_type);
                    } else {
                        //error
                        std::cout << "Error: SimpleExpression Type error. Line: " << sexpression->get_rownum() << std::endl;
                    }
                } else {
                    if (sexpression->get(0)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown") {
                        sexpression->get(0)->accept(this);
                    }
                    string term_type1 = sexpression->get(0)->DynamicCast<SimpleExpression>()->GetExpType();
                    if (sexpression->get(1)->DynamicCast<Term>()->GetTerType() == "unknown") {
                        sexpression->get(1)->accept(this);
                    }
                    string term_type2 = sexpression->get(1)->DynamicCast<Term>()->GetTerType();
                    //类型检查
                    if ((term_type1 == "real" || term_type1 == "integer" || term_type1 == "char") &&
                        (term_type2 == "real" || term_type2 == "integer" || term_type2 == "char")) {
                        if (term_type1 == "real" || term_type2 == "real") {
                            sexpression->SetExpType("real");
                        } else {
                            sexpression->SetExpType("integer");
                        }
                    } else {
                        //error
                        std::cout << "Error: SimpleExpression Type error. Line: " << sexpression->get_rownum() << std::endl;
                    }
                }
                break;
            }
            case SimpleExpression::SymbolType::OR_:
            {
                if (sexpression->get(0)->DynamicCast<SimpleExpression>()->GetExpType() == "unknown") {
                    sexpression->get(0)->accept(this);
                }
                string term_type1 = sexpression->get(0)->DynamicCast<SimpleExpression>()->GetExpType();
                if (sexpression->get(1)->DynamicCast<Term>()->GetTerType() == "unknown") {
                    sexpression->get(1)->accept(this);
                }
                string term_type2 = sexpression->get(1)->DynamicCast<Term>()->GetTerType();
                //类型检查
                if ((term_type1 == "real" || term_type1 == "integer" || term_type1 == "char" || term_type1 == "boolean") && (term_type2 == "boolean" || term_type2 == "real" || term_type2 == "integer" || term_type2 == "char")) {
                    sexpression->SetExpType("boolean");
                } else {
                    //error
                    std::cout << "Error: SimpleExpression Type error. Line: " << sexpression->get_rownum() << std::endl;
                }
                break;
            }
        }
    }
}

void SemanticVisitor::visit(Term *term)
{
    if (term->GetTerType() == "unknown") {
        switch (term->GetSymType()) {
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
                if (term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown") {
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if (term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown") {
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if ((term_type == "real" || term_type == "integer" || term_type == "char") &&
                    (fac_type == "real" || fac_type == "integer" || fac_type == "char"))
                {
                    if (term_type == "real" || fac_type == "real")
                    {
                        term->SetTerType("real");
                    } else
                    {
                        term->SetTerType("integer");
                    }
                } else {
                    //错误处理
                    std::cout << "Error: Term Type error. Line: " << term->get_rownum() << std::endl;
                }
                break;
            }
            case Term::SymbolType::MOD:
            {
                if (term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown") {
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if (term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown") {
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if ((term_type == "integer" || term_type == "char") && (fac_type == "integer" || fac_type == "char"))
                {
                    term->SetTerType("integer");
                } else {
                    //错误处理
                    std::cout << "Error: Term Type error. Line: " << term->get_rownum() << std::endl;
                }
                break;
            }
            case Term::SymbolType::AND:
            {
                if (term->get(0)->DynamicCast<Term>()->GetTerType() == "unknown") {
                    term->get(0)->accept(this);
                }
                string term_type = term->get(0)->DynamicCast<Term>()->GetTerType();
                if (term->get(1)->DynamicCast<Factor>()->GetFacType() == "unknown") {
                    term->get(1)->accept(this);
                }
                string fac_type = term->get(1)->DynamicCast<Factor>()->GetFacType();
                //类型检查
                if ((term_type == "real" || term_type == "integer" || term_type == "char" || term_type == "boolean") &&
                    (fac_type == "real" || fac_type == "integer" || fac_type == "char" || fac_type == "boolean"))
                {
                    term->SetTerType("boolean");
                } else {
                    //错误处理
                    std::cout << "Error: Term Type error. Line: " << term->get_rownum() << std::endl;
                }
                break;
            }
        }
    }
}

void SemanticVisitor::visit(Factor *factor)
{
    if (factor->GetFacType() == "unknown") {
        switch (factor->get_type()) {
            case Factor::GrammerType::ID_EXP_LIST:
            {
                // 对于函数直接获取其返回值类型
                auto id = factor->get(0)->DynamicCast<LeafNode>()->get_value<string>();

                if (id == "cos" || id == "sin")
                {
                    math_flag = 1;
                    factor->SetFacType("real");
                } else {
                    TableRecord *tr = findID(MainTable, id, 0);
                    if (tr == NULL)
                    {
                        //错误处理
                        std::cout << "Error: Undefined. Line: " << factor->get_rownum() << std::endl;
                    } else {
                        factor->get(1)->accept(this);
                        auto exp_types = factor->get(1)->DynamicCast<ExpressionList>()->get_types();
                        auto record_info = findID(MainTable, id, 1);
                        if (exp_types->size() != record_info->amount) {  //checked
                            //错误处理，参数数量不匹配
                            std::cout << "Error: The number of arguments does not match. Line: " << factor->get_rownum() << std::endl;
                            semantic_error = 1;
                            return;
                        }
                        for (int i = 0; i < exp_types->size(); i++) {
                            string para_type = record_info->subSymbolTable->records[i + 1]->type;
                            if (para_type != (*exp_types)[i] && !(para_type == "real" &&(*exp_types)[i] == "integer")) {
                                //错误处理，参数类型错误  影响OJ
                                std::cout << "Error: Type mismatch. Line: " << factor->get_rownum() << std::endl;   
                            }
                        }
                        factor->SetFacType(tr->type);
                    }
                }
                break;
            }
            case Factor::GrammerType::VARIABLE:
            {
                // 对于变量直接获取其类型
                factor->get(0)->accept(this);
                Variable *var = factor->get(0)->DynamicCast<Variable>();
                factor->SetFacType(var->get_vn());
                break;
            }
            case Factor::GrammerType::EXP:
            {
                // 对于表达式直接获取表达式的类型
                Expression *exp = factor->get(0)->DynamicCast<Expression>();
                if (exp->GetExpType() == "unknown") {
                    factor->get(0)->accept(this);
                }
                factor->SetFacType(exp->GetExpType());
                break;
            }
            case Factor::GrammerType::UPLUS:
            case Factor::GrammerType::UMINUS_:
            {
                // 对于负号直接与子节点的factor类型相同
                Factor *fac = factor->get(0)->DynamicCast<Factor>();
                if (fac->GetFacType() == "unknown") {
                    factor->get(0)->accept(this);
                }
                string fac_type = fac->GetFacType();
                // 类型检查(只有实数、整数、字符可以)
                if (fac_type == "real" || fac_type == "char" || fac_type == "integer") {
                    factor->SetFacType(fac->GetFacType());
                } else {
                    std::cout << "Error: Factor Type error. Line: " << factor->get_rownum() << std::endl;
                }
                break;
            }
            case Factor::GrammerType::NOT_:
            {
                Factor *fac = factor->get(0)->DynamicCast<Factor>();
                if (fac->GetFacType() == "unknown") {
                    factor->get(0)->accept(this);
                }
                string fac_type = fac->GetFacType();
                // 类型检查(实数、整数、字符、布尔型都可以)
                factor->SetFacType(fac_type);
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

    while (gtype == GrammarType::MULTIPLE_PARAM_LIST)  //如果多层 进入循环
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

std::vector<tuple<int, string, ConstValue *>> ConstDeclaration::Lists()
{
    std::vector<tuple<int, string, ConstValue *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_ID)  //如果多层 进入循环
    {
        int rn                              = cur_node->get_rownum();
        auto id                             = cur_node->get(1)->DynamicCast<LeafNode>()->get_value<string>();
        auto const_value                    = cur_node->get(2)->DynamicCast<LeafNode>()->getConstValue();
        tuple<int, string, ConstValue *> ln = make_tuple(rn, id, const_value);

        lists.insert(lists.begin(), ln);

        cur_node = cur_node->cnode_list[0]->DynamicCast<ConstDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    int rn                              = cur_node->get_rownum();
    auto id                             = cur_node->get(0)->DynamicCast<LeafNode>()->get_value<string>();
    auto const_value                    = cur_node->get(1)->DynamicCast<LeafNode>()->getConstValue();
    tuple<int, string, ConstValue *> ln = make_tuple(rn, id, const_value);

    lists.insert(lists.begin(), ln);

    return lists;
}

std::vector<tuple<vector<LeafNode *>, AstNode *>> VarDeclaration::Lists()
{
    std::vector<tuple<vector<LeafNode *>, AstNode *>> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::MULTIPLE_DECL)  //如果多层 进入循环
    {
        auto idlist                             = cur_node->get(1)->DynamicCast<IdList>()->Lists();
        auto node                               = cur_node->get(2);
        tuple<vector<LeafNode *>, AstNode *> ln = make_tuple(idlist, node);

        lists.insert(lists.begin(), ln);

        cur_node = cur_node->cnode_list[0]->DynamicCast<VarDeclaration>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    auto idlist                             = cur_node->get(1)->DynamicCast<IdList>()->Lists();
    auto node                               = cur_node->get(2);
    tuple<vector<LeafNode *>, AstNode *> ln = make_tuple(idlist, node);

    lists.insert(lists.begin(), ln);

    return lists;
}

std::vector<AstNode *> ExpressionList::Lists()
{
    std::vector<AstNode *> lists;
    auto *cur_node       = this;
    ExpressionType gtype = expression_type;

    while (gtype == ExpressionType::MULTIPLE)  //如果多层 进入循环
    {
        AstNode *ln = cur_node->cnode_list[1];
        lists.insert(lists.begin(), ln);

        cur_node = cur_node->cnode_list[0]->DynamicCast<ExpressionList>();
        gtype    = cur_node->expression_type;
    }

    // 插入最后一个节点
    AstNode *ln = cur_node->cnode_list[0];
    lists.insert(lists.begin(), ln);
    return lists;
}

std::vector<AstNode *> VariableList::Lists()
{
    std::vector<AstNode *> lists;
    auto *cur_node    = this;
    GrammarType gtype = grammar_type;

    while (gtype == GrammarType::VAR_LIST_VAR)  //如果多层 进入循环
    {
        AstNode *ln = cur_node->cnode_list[1];
        lists.insert(lists.begin(), ln);

        cur_node = cur_node->cnode_list[0]->DynamicCast<VariableList>();
        gtype    = cur_node->grammar_type;
    }

    // 插入最后一个节点
    AstNode *ln = cur_node->cnode_list[0];
    lists.insert(lists.begin(), ln);
    return lists;
}


}  // namespace ast