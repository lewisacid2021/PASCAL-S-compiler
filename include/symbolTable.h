#pragma once

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class SymbolTable;

class TableRecord
{
  public:
    string flag;                              //种类标志,
    string id;                                //标识符名字
    int rowNumber;                            //行号
    string type;                              //变量/常量类型，数组类型，返回值类型
    string value;                             //常量取值
    bool isPara;
    bool isRefered;
    bool isMinus;                             //常量前是否有负号
    int amount;                               //参数个数/数组维数/字符串字符数
    vector<pair<int, int>> arrayRange;        //数组各维上下界
    SymbolTable *subSymbolTable;              //指向函数/过程子符号表的指针
    string programInfo;                       //当前符号表对应的程序相关信息

    void setPara(string flag, string id_para, int rowNumber_para, string type_para);
    void setVarPara(string flag, string id_para, int rowNumber_para, string type_para);
    void setVar(string id_para, int rowNumber_para, string type_para);
    void setConst(string id_para, int rowNumber_para, string type_para, bool isMinus_para, string value_para);
    void setArray(string id_para, int rowNumber_para, string type_para, int amount_para, vector<pair<int, int>> arrayRange_para);
    void setString(string id_para, int rowNumber_para, string type_para, int amount_para);
    void setRecord(string id_para, string recordName, int rowNumber_para, SymbolTable *subSymbolTable_para);
    void setProcedure(string id_para, int rowNumber_para, int amount_para, SymbolTable *subSymbolTable_para);
    void setFunction(string id_para, int rowNumber_para, string type_para, int amount_para, SymbolTable *subSymbolTable_para);
    void setProgramName(string id_para, int rowNumber_para, string programInfo_para, int amount_para, string returnType_para);
    void setVoidPara(string id_para, int rowNumber_para);

    TableRecord()
    {
        arrayRange.clear();
        subSymbolTable = NULL;
    }
    ~TableRecord() {}
};

class SymbolTable
{
  public:
    string tableType;               //类型，主符号表或子符号表
    vector<TableRecord *> records;  //指向record成员的指针
    unordered_map<string, int> idLoc;         //存储标识符在records中的下标，加快查询速度

    void addPara(string flag,string id, int rowNumber, string type);
    void addVarPara(string flag, string id, int rowNumber, string type);
    void addVar(string id, int rowNumber, string type);
    void addConst(string id, int rowNumber, string type, bool isMinus, string value);
    void addArray(string id, int rowNumber, string type, int amount, vector<pair<int, int>> arrayRange);
    void addString(string id, int rowNumber,string type,int amount);
    void addRecord(string id,string recordName, int rowNumber,SymbolTable *subSymbolTable);
    void addProcedure(string id, int rowNumber, int amount, SymbolTable *subSymbolTable);
    void addFunction(string id, int rowNumber, string type, int amount, SymbolTable *subSymbolTable);
    void addProgramName(string id, int rowNumber, string programInfo, int amount, string returnType);
    void addVoidPara(string id, int rowNumber);

    SymbolTable(string type = "sub");
    ~SymbolTable() {}
};

class TypeTableRecord
{
  public:
  string id;
  bool isCoverd = false;
  SymbolTable* RecordTable;

  void setType(string id, bool isCoverd, SymbolTable *RecordTable);

  TypeTableRecord(){}
  ~TypeTableRecord(){}
};

class TypeTable
{
  public:
  vector<TypeTableRecord *> records;
  unordered_map<string, int> idLoc;

  void addType(string id,bool isCoverd,SymbolTable* RecordTable);
  TypeTableRecord *findID(string id);

  TypeTable(){
    addType("integer",false,NULL);
    addType("real",false,NULL);
    addType("boolean",false,NULL);
  }
  ~TypeTable(){}
};

extern TableRecord *findID(SymbolTable *currentSymbolTable, string id, int mode);
extern TableRecord *findID(SymbolTable *currentSymbolTable, string id, int mode, string type);
#endif