#include "symbolTable.h"
#include <cstddef>
#include <iostream>

using namespace std;

//添加传值参数
void SymbolTable::addPara(string id,int rowNumber,string type)
{
    TableRecord* temp=new TableRecord;
    temp->setPara(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
    if(this->idCount.count(id))
    {
        this->idCount[id]++;
    }
    else 
    {
        this->idCount[id]=1;
    }
}

//添加引用参数
void SymbolTable::addVarPara(string id,int rowNumber,string type)
{
    TableRecord* temp=new TableRecord;
    temp->setVarPara(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
    if(this->idCount.count(id))
    {
        this->idCount[id]++;
    }
    else 
    {
        this->idCount[id]=1;
    }
}

//添加变量
void SymbolTable::addVar(string id,int rowNumber,string type)
{
    TableRecord* temp=new TableRecord;
    temp->setVar(id, rowNumber, type);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
}

//添加常量
void SymbolTable::addConst(string id,int rowNumber,string type, bool isMinusShow, string value)
{
    TableRecord* temp=new TableRecord;
    temp->setConst(id, rowNumber, type, isMinusShow, value);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
}

//添加数组
void SymbolTable::addArray(string id,int rowNumber,string type, int amount, vector< pair<int, int> > arrayRange)
{
    TableRecord* temp=new TableRecord;
    temp->setArray(id, rowNumber, type, amount, arrayRange);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
}

//添加过程
void SymbolTable::addProcedure(string id,int rowNumber, int amount, SymbolTable* subSymbolTable)
{
    TableRecord* temp=new TableRecord;
    temp->setProcedure(id, rowNumber, amount, subSymbolTable);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
}

//添加函数
void SymbolTable::addFunction(string id,int rowNumber, string type, int amount, SymbolTable* subSymbolTable)
{
    TableRecord* temp=new TableRecord;
    temp->setFunction(id, rowNumber, type, amount, subSymbolTable);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
}

//添加子符号表
void SymbolTable::addSubSymbolTable(string id,SymbolTable* subSymbolTable)
{
    if(idLoc.count(id))
    {
        size_t loc = static_cast<size_t>(idLoc[id]);
        records[loc]->subSymbolTable=subSymbolTable;
    }
    else 
    {
        cout << "[addSubSymbolTable Error]:no such program\n";
    }
}

//添加程序名
void SymbolTable::addProgramName(string id, int rowNumber, string programInfo, int amount, string returnType)
{
    if(records.size()!=0)
    {
        cout << "[addProgramName Error]:records is not null";
        return;
    }
    TableRecord* temp=new TableRecord;
    temp->setProgramName(id, rowNumber, programInfo, amount, returnType);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
    if(this->idCount.count(id))
    {
        this->idCount[id]++;
    }
    else 
    {
        this->idCount[id]=1;
    }
}

//添加程序参数
void SymbolTable::addVoidPara(string id, int rowNumber)
{
    TableRecord* temp=new TableRecord;
    temp->setVoidPara(id, rowNumber);
    this->records.push_back(temp);
    this->idLoc[id]=int(records.size()-1);
    if(this->idCount.count(id))
    {
        this->idCount[id]++;
    }
    else 
    {
        this->idCount[id]=1;
    }
}

//构造函数
SymbolTable::SymbolTable(string type) {
	records.clear();
	idLoc.clear();
	this->tableType=type;
}

void TableRecord::setPara(string id, int rowNumber, string type) {
	flag = "value parameter";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
}

void TableRecord::setVarPara(string id,int rowNumber, string type) {
	flag = "var parameter";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
}

void TableRecord::setVar(string id, int rowNumber, string type) {
	flag = "normal variant";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
}

void TableRecord::setConst(string id, int rowNumber, string type, bool isMinusShow, string value) {
	flag = "constant";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
	this->isMinusShow = isMinusShow;
	if (type == "char")
		this->value += "'";
	this->value += value;
	if (type == "char")
		this->value += "'";
}

void TableRecord::setArray(string id, int rowNumber, string type, int amount, vector< pair<int,int> > arrayRange) {
	flag = "array";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
	this->amount = amount;
	this->arrayRange = arrayRange;
}

void TableRecord::setProcedure(string id, int rowNumber, int amount, _SymbolTable *subSymbolTable) {
	flag = "procedure";
	this->id = id;
	this->rowNumber = rowNumber;
	this->amount = amount;
	this->subSymbolTable = subSymbolTable;
}

void TableRecord::setFunction(string id, int rowNumber, string type, int amount, _SymbolTable *subSymbolTable) {
	flag = "function";
	this->id = id;
	this->rowNumber = rowNumber;
	this->type = type;
	this->amount = amount;
	this->subSymbolTable = subSymbolTable;
}

void TableRecord::setProgramName(string id, int rowNumber, string subprogramType, int amount, string returnType) {
	flag = "(sub)program name";
	this->id = id;
	this->rowNumber = rowNumber;
	this->subprogramType = subprogramType;
	this->amount = amount;
	this->type = returnType;
}

void TableRecord::setVoidPara(string id, int rowNumber) {
	flag = "parameter of program";
	this->id = id;
	this->rowNumber = rowNumber;
}
