#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <map>
#include <string>
#include <vector>

using namespace std;

class SymbolTable;

class TableRecord
{
  public:
    string flag;                        //种类标志
    string id;                          //标识符名字
    int rowNumber;                      //行号
    string type;                        //类型
    string value;                       //常量取值
    bool isMinus;                       //常量前是否有负号
    int amount;                         //参数个数/数组维数/字符串字符数
    vector<pair<int, int>> arrayRange;  //数组各维上下界
    SymbolTable* subSymbolTable;        //指向函数/过程子符号表的指针
    string programInfo;                 //当前符号表对应的程序相关信息

    void setPara(string id, int rowNumber, string type);
    void setVarPara(string id, int rowNumber, string type);
    void setVar(string id, int rowNumber, string type);
    void setConst(string id, int rowNumber, string type, bool isMinus, string value);
    void setArray(string id, int rowNumber, string type, int amount, vector<pair<int, int>> arrayRange);
    void setProcedure(string id, int rowNumber, int amount, SymbolTable *subSymbolTable);
    void setFunction(string id, int rowNumber, string type, int amount, SymbolTable *subSymbolTable);
    void setProgramName(string id, int rowNumber, string programInfo, int amount, string returnType);
    void setVoidPara(string id, int rowNumber);

    string findXthFormalParaType(int X);             //找到第X个形式参数的类型
    bool isXthFormalParaRefered(int X);              //检查第X个形式参数是否是引用调用
    bool checkArrayXthIndexRange(int X, int index);  //检查第X维下标是否越界，true表示越界，false表示未越界

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
    string tableType;                    //类型，主符号表或子符号表
    vector<TableRecord *> records;  //指向record成员的指针
    map<string, int> idLoc;         //存储标识符在records中的下标，加快查询速度
    map<string, int> idCount;

    void addPara(string id, int rowNumber, string type);
    void addVarPara(string id, int rowNumber, string type);
    void addVar(string id, int rowNumber, string type);
    void addConst(string id, int rowNumber, string type, bool isMinus, string value);
    void addArray(string id, int rowNumber, string type, int amount, vector<pair<int, int>> arrayRange);
    void addProcedure(string id, int rowNumber, int amount, SymbolTable *subSymbolTable);
    void addFunction(string id, int rowNumber, string type, int amount, SymbolTable *subSymbolTable);
    void addSubSymbolTable(string id, SymbolTable *subSymbolTable);
    void addProgramName(string id, int rowNumber, string programInfo, int amount, string returnType);
    void addVoidPara(string id, int rowNumber);

    SymbolTable(string type = "sub");
    ~SymbolTable() {}
};

#endif