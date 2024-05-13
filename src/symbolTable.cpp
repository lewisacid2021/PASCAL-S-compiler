#include "symbolTable.h"
#include <cstddef>
#include <iostream>

using namespace std;

extern SymbolTable * MainTable;;  //主符号表

//添加传值参数
void SymbolTable::addPara(string id, int rowNumber, string type)
{
    TableRecord *temp = new TableRecord;
    temp->setPara(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加引用参数
void SymbolTable::addVarPara(string id, int rowNumber, string type)
{
    TableRecord *temp = new TableRecord;
    temp->setVarPara(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加变量
void SymbolTable::addVar(string id, int rowNumber, string type)
{
    TableRecord *temp = new TableRecord;
    temp->setVar(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加常量
void SymbolTable::addConst(string id, int rowNumber, string type, bool isMinusShow, string value)
{
    TableRecord *temp = new TableRecord;
    temp->setConst(id, rowNumber, type, isMinusShow, value);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加数组
void SymbolTable::addArray(string id, int rowNumber, string type, int amount, vector< pair<int, int> > arrayRange)
{
    TableRecord *temp = new TableRecord;
    temp->setArray(id, rowNumber, type, amount, arrayRange);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加字符串
void SymbolTable::addString(string id, int rowNumber, string type, int amount)
{
    TableRecord *temp = new TableRecord;
    temp->setString(id, rowNumber, type, amount);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加record
void SymbolTable::addRecord(string id, string recordName, int rowNumber, SymbolTable *subSymbolTable)
{
    TableRecord *temp = new TableRecord;
    temp->setRecord(id, recordName, rowNumber, subSymbolTable);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加过程
void SymbolTable::addProcedure(string id, int rowNumber, int amount, SymbolTable *subSymbolTable)
{
    TableRecord *temp = new TableRecord;
    temp->setProcedure(id, rowNumber, amount, subSymbolTable);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加函数
void SymbolTable::addFunction(string id, int rowNumber, string type, int amount, SymbolTable *subSymbolTable)
{
    TableRecord *temp = new TableRecord;
    temp->setFunction(id, rowNumber, type, amount, subSymbolTable);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加程序名
void SymbolTable::addProgramName(string id, int rowNumber, string programInfo, int amount, string returnType)
{
    if (records.size() != 0)
    {
        for (auto i : records) {
            cout << i->flag << i->type << i->id << endl;
        }
        cout << "[addProgramName Error]:records is not null";
        return;
    }
    TableRecord *temp = new TableRecord;
    temp->setProgramName(id, rowNumber, programInfo, amount, returnType);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//添加程序参数
void SymbolTable::addVoidPara(string id, int rowNumber)
{
    TableRecord *temp = new TableRecord;
    temp->setVoidPara(id, rowNumber);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

//构造函数
SymbolTable::SymbolTable(string type)
{
    records.clear();
    idLoc.clear();
    this->tableType = type;
}

void TableRecord::setPara(string id_para, int rowNumber_para, string type_para)
{
    flag            = "value parameter";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
    this->type      = type_para;
}

void TableRecord::setVarPara(string id_para, int rowNumber_para, string type_para)
{
    flag            = "var parameter";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
    this->type      = type_para;
}

void TableRecord::setVar(string id_para, int rowNumber_para, string type_para)
{
    flag            = "variant";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
    this->type      = type_para;
}

void TableRecord::setConst(string id_para, int rowNumber_para, string type_para, bool isMinus_para, string value_para)
{
    flag            = "constant";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
    this->type      = type_para;
    this->isMinus   = isMinus_para;
}

void TableRecord::setArray(string id_para, int rowNumber_para, string type_para, int amount_para, vector< pair<int, int> > arrayRange_para)
{
    flag             = "array";
    this->id         = id_para;
    this->rowNumber  = rowNumber_para;
    this->type       = type_para;
    this->amount     = amount_para;
    this->arrayRange = arrayRange_para;
}

void TableRecord::setString(string id_para, int rowNumber_para, string type_para, int amount_para)
{
    flag            = "string";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
    this->type      = type_para;
    this->amount    = amount_para;
}

void TableRecord::setRecord(string id_para, string recordName, int rowNumber_para, SymbolTable *subSymbolTable_para)
{
    flag                 = "record";
    this->id             = id_para;
    this->type           = recordName;
    this->rowNumber      = rowNumber_para;
    this->subSymbolTable = subSymbolTable_para;
}

void TableRecord::setProcedure(string id_para, int rowNumber_para, int amount_para, SymbolTable *subSymbolTable_para)
{
    flag                 = "procedure";
    this->id             = id_para;
    this->rowNumber      = rowNumber_para;
    this->amount         = amount_para;
    this->subSymbolTable = subSymbolTable_para;
}

void TableRecord::setFunction(string id_para, int rowNumber_para, string type_para, int amount_para, SymbolTable *subSymbolTable_para)
{
    flag                 = "function";
    this->id             = id_para;
    this->rowNumber      = rowNumber_para;
    this->type           = type_para;
    this->amount         = amount_para;
    this->subSymbolTable = subSymbolTable_para;
}

void TableRecord::setProgramName(string id_para, int rowNumber_para, string programInfo_para, int amount_para, string returnType)
{
    flag              = "(sub)program name";
    this->id          = id_para;
    this->rowNumber   = rowNumber_para;
    this->programInfo = programInfo_para;
    this->amount      = amount_para;
    this->type        = returnType;
}

void TableRecord::setVoidPara(string id_para, int rowNumber_para)
{
    flag            = "parameter of program";
    this->id        = id_para;
    this->rowNumber = rowNumber_para;
}

void TypeTable::addType(string id, bool isCoverd, SymbolTable *RecordTable)
{
    TypeTableRecord *temp = new TypeTableRecord;
    if (id == "integer" || id == "char" || id == "real" || id == "boolean")
        isCoverd = true;
    temp->setType(id, isCoverd, RecordTable);
    this->records.push_back(temp);
    this->idLoc[id] = int(records.size() - 1);
}

void TypeTableRecord::setType(string id, bool isCoverd, SymbolTable *RecordTable)
{
    this->id          = id;
    this->isCoverd    = isCoverd;
    this->RecordTable = RecordTable;
}

TypeTableRecord *TypeTable::findID(string id)
{
    if (this->idLoc.count(id))
    {
        size_t loc = static_cast<size_t>(this->idLoc[id]);
        return this->records[loc];
    }
    return NULL;
}

//找出标识符在符号表中的位置
TableRecord *findID(SymbolTable *currentSymbolTable, string id, int mode)
{
    if (currentSymbolTable->idLoc.count(id)) {
        size_t loc = static_cast<size_t>(currentSymbolTable->idLoc[id]);
        return currentSymbolTable->records[loc];
    }
    if (mode != 0)
        return NULL;
    if (MainTable->idLoc.count(id)) {
        size_t loc = static_cast<size_t>(MainTable->idLoc[id]);
        return MainTable->records[loc];
    }
    return NULL;
}

TableRecord *findID(SymbolTable *currentSymbolTable, string id, int mode, string flag)
{
    if (currentSymbolTable->idLoc.count(id)) {
        size_t loc = static_cast<size_t>(currentSymbolTable->idLoc[id]);
        if(currentSymbolTable->records[loc]->flag == flag){
            return currentSymbolTable->records[loc];
        }
    }
    if (mode != 0)
        return NULL;
    if (MainTable->idLoc.count(id)) {
        size_t loc = static_cast<size_t>(MainTable->idLoc[id]);
        //cout << loc << endl;
        if(MainTable->records[loc]->flag == flag){
            return MainTable->records[loc];
        }
    }
    return NULL;
}
