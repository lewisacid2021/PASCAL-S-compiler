#pragma once

#include "type.h"
#include "symbolTable.h"
#include <cmath>
#include <iostream>
#include <vector>

namespace ast {

class Visitor;

class AstNode
{
  public:
    //构造及析构函数
    AstNode()
        : pnode(nullptr){};
    virtual ~AstNode()
    {
        for (auto child : cnode_list) {
            delete child;
        }
    }

    template <typename T>
    T *DynamicCast() {
      return dynamic_cast<T *>(this);
    }

    virtual void accept(Visitor *visitor);  //访问者接口
    //添加父节点及查看父节点的方法
    void set_parent(AstNode *parent)
    {
        pnode = parent;
    }
    AstNode *parent()
    {
        return pnode;
    }

    //添加子节点及查看子节点的方法
    void append_child(AstNode *child)
    {
        cnode_list.emplace_back(child);
    }
    AstNode *get(int pos)
    {
        return cnode_list[pos<0?cnode_list.size()+pos:pos];
    }

    std::vector<AstNode *> &getCnodeList()
    {
        return cnode_list;
    }

    void set_rownum(int rn)
    {
      row_num = rn;
    }

    int get_rownum(){return row_num;}

  protected:
    AstNode *pnode;
    std::vector<AstNode *> cnode_list;
    int row_num;
};

class AST
{
  public:
    ~AST()
    {
        if (astroot != nullptr)
            delete astroot;
    }

    void set_root(AstNode *root) { astroot = root; }
    AstNode *getRoot() { return astroot; }

    void accept(Visitor *visitor);  //访问者接口

  private:
    AstNode *astroot = nullptr;
};

class LeafNode: public AstNode
{
  public:
    enum class LeafType{
      VALUE,
      NAME,
    };
    LeafNode(){}
    LeafNode(ConstValue val, LeafType lt)
        : value_(val), leaf_type(lt)
    {}

    // id_ref()返回变量名或者引用的变量名
    const std::string id_ref() {
    return is_ref ? "(*" + value_.get<std::string>() + ")"
                   : value_.get<std::string>();
    }

    // getter and setter
    void set_value(ConstValue value) { value_ = value; }
    void set_ref(bool ref) { is_ref = ref; }
    // template value getter
    template<typename T>
    T get_value()
    {
        return value_.get<T>();
    }
    ConstValue::ConstvalueType get_type() { return value_.type(); }
    LeafType getLeafType() { return leaf_type; }
    ConstValue * getConstValue(){return &value_;}
    void accept(Visitor *visitor) override;  //访问者接口

    // Analyze reference
    //bool AnalyzeReference(TableSet *ts, FunctionSymbol *fn);

  private:
    ConstValue value_;    // const values（包括常量与变量名）
    LeafType leaf_type;
    bool is_ref = false;  // 是否为引用
};

class ProgramStruct: public AstNode
{
    //program_head -> program id ( idlist ) | program id
};

class ProgramHead: public AstNode
{
    // program_head -> program id ( idlist ) | program id
};

class ProgramBody: public AstNode
{
    // program_body -> const_declarations
    //                 record_delcarations
    //                 var_declarations
    //                 subprogram_declarations
    //                 compound_statement
    // 共四个子节点
};

class IdList: public AstNode
{
    // idlist -> id | idlist , id
    // 子节点为单个id叶子节点或者一个IdList节点后跟着id叶子节点。
  public:
    enum class GrammarType
    {
        SINGLE_ID,   // idlist -> id
        MULTIPLE_ID  // idlist -> idlist , id
    };
    IdList(GrammarType gt)
        : grammar_type_(gt)
    {}

    std::vector<LeafNode *> Lists();
    void accept(Visitor *visitor) override;  //访问者接口

    GrammarType GetGrammarType()
    {
        return grammar_type_;
    };

  private:
    GrammarType grammar_type_;
};

class ConstDeclarations: public AstNode
{
    // 子节点为单个ConstDeclaration节点或者没有
    // const_declarations -> ε | const const_declaration ;
  public:
    enum class GrammarType
    {
        EPSILON,
        DECLARATION,
    };

    ConstDeclarations(GrammarType gt)
        : grammar_type(gt){};
    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};

class ConstDeclaration: public AstNode
{
    // 若GrammarType为SINGLE_ID，则子节点为两个叶子节点（id 、const_value)
    // 若GrammarType为MULTIPLE_ID，则子节点为ConstDeclaration节点与两个叶子节点（id 、const_value)
  public:
    enum class GrammarType
    {
        SINGLE_ID,   // const_declaration -> id = const_value
        MULTIPLE_ID  // const_declaration -> const_declaration ; id = const_value
    };
    ConstDeclaration(GrammarType gt, ConstValue::ConstvalueType bt)
        : grammar_type(gt)
        , type(bt){};
    void print_type();
    ConstValue::ConstvalueType get_value_type(){return type;}

    void accept(Visitor *visitor) override;  //访问者接口
    std::vector<tuple<int,string,ConstValue *>> Lists();

    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
    ConstValue::ConstvalueType type;  // 记录该常变量的类型。
};

class RecordDeclarations: public AstNode
{
    // 子节点为单个RecordDeclaration节点或者没有
    // record_declarations -> ε | record_declaration ;
  public:
    enum class GrammarType
    {
        EPSILON,
        DECLARATION,
    };

    RecordDeclarations(GrammarType gt)
        : grammar_type(gt){};
    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};

class RecordDeclaration: public AstNode
{
    // 子节点为RecordDeclaration节点，叶子节点id，以及var_declaration节点。
    // record_declaration -> def-record | record_declaration def-record
    // def-record -> type 
    //               record-name = record
    //               var_declaration
    //               end;
  public:
    enum class GrammarType
    {
        SINGLE_DECLARATION,
        MULTI_DECLARATION,
    };

    RecordDeclaration(GrammarType gt)
        : grammar_type(gt){};
    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};

class VarDeclarations: public AstNode
{
    // 拥有单个子节点VarDeclaration或没有
    // var_declarations -> ε | var var_declaration ;
  public:
    enum class GrammarType
    {
        EPSILON,
        DECLARATION,
    };
    VarDeclarations(GrammarType gt)
        : grammar_type(gt){};
    GrammarType GetType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};

class VarDeclaration: public AstNode
{
    // 子节点为一个TypeNode节点以及IdList节点
    // 若GrammarType为SINGLE_ID，则子节点为两个节点TypeNode与IdList
    // 若GrammarType为MULTIPLE_ID，则子节点为VarDeclaration节点与两个节点TypeNode与IdList
    // 顺序为先IdList后TypeNode
  public:
    enum class GrammarType
    {
        SINGLE_DECL,   // var_declaration -> idlist : type
        MULTIPLE_DECL  // var_declaration -> var_declaration ; idlist : type
    };
    VarDeclaration(GrammarType gt)
        : grammar_type(gt)
    {}

    void accept(Visitor *visitor) override;  //访问者接口
    std::vector<tuple<vector<LeafNode *>,AstNode *>> Lists();

    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};


/************************************************
                    类型节点
*************************************************/
class TypeNode: public AstNode
{
    //子节点为
    //ID_TYPE 无子节点
    //STRING_TYPE 对应 StringTypeNode
    //ARRAY_TYPE 对应 ArrayTypeNode
  public:
    enum class VarType
    {
        ARRAY_TYPE,
        ID_TYPE,
        RECORD_TYPE,
        STRING_TYPE
    };

    TypeNode(VarType vt)
        : var_type(vt)
    {}
    TypeNode(VarType vt, std::string tn)
        : var_type(vt), type_name(tn)
    {}
    VarType GetVarType() { return var_type; }
    std::string get_type_name() { return type_name; }
    
    void accept(Visitor *visitor) override;  //访问者接口

  private:
    VarType var_type;
    std::string type_name;
};

class ArrayTypeNode: public AstNode
{
    // 子节点为 PeriodsNode 与 TypeNode
  public:
    ArrayTypeNode() {}
    ArrayTypeNode(std::string type)
        : type_name(type)
    {}

    void set_type(std::string type) { type_name = type; }
    void set_info(ArrayType *at) { array_info = at; }
    std::string type() { return type_name; }
    ArrayType *info() { return array_info; }

  private:
    std::string type_name;  // array的类型名("array"表示为数组类型)
    ArrayType *array_info;  // 指向储存array信息的对象
};

class RecordNode: public AstNode
{
    // recordtype -> record var_declaration end;
    // 子节点为VarDeclaration节点
};

class PeriodsNode: public AstNode
{
    // period -> digits .. digits 子节点为PeriodNode
    // period -> period ， digits .. digits 子节点为PeriodsNode和PeriodNode
  public:
    enum class PeriodType{
      SINGLE,
      MULTI
    } ;
    PeriodsNode(PeriodType pt) : period_type(pt) {};
    void set_dm(std::vector<ArrayType::Dimension> low_dm){
      dm = low_dm;
    }
    std::vector<ArrayType::Dimension> get_dm(){
      return dm;
    }
    PeriodsNode get_type(){
      return period_type;
    }
    void accept(Visitor *visitor) override;  //访问者接口

  private:
    PeriodType period_type; // 语法类型
    std::vector<ArrayType::Dimension> dm; // 自底向上累积至当前节点的各维度信息
};


class PeriodNode: public AstNode
{
    // Period → const_var ... const var
  public:
    PeriodNode(int low, int up): lowb(low), upb(up){}
    int get_lowb(){
      return lowb;
    }
    int get_upb(){
      return upb;
    }

  private:
    int lowb = 0;
    int upb = 0;
};

class StringTypeNode : public AstNode {
public:
    StringTypeNode() {}
    StringTypeNode(StringType *type) : string_info(type) {}

    void set_type(StringType *type) { string_info = type; }
    void accept(Visitor *visitor) override;  //访问者接口
    StringType *type() { return string_info; }

private:
    StringType* string_info;
};

/**************************************************
                    子程序部分节点
***************************************************/
class SubprogramDeclarations: public AstNode
{
    //subprogram_declarations -> ε | subprogram_declarations subprogram ;
};

class SubprogramDeclaration: public AstNode
{
    //subprogram -> subprogram_head ; subprogram_body
    void accept(Visitor *visitor) override;  //访问者接口
};

class SubprogramBody: public AstNode
{
    // subprogram_body -> const_declarations
    //                   var_declarations
    //                   compound_statement
};

class SubprogramHead: public AstNode
{
  //子节点为叶子节点id、FormalParam节点以及可能的type节点
  public:
    enum class SubprogramType
    {
        PROC,  // subprogram_head -> procedure id formal_parameter
        FUNC    // subprogram_head -> function id formal_parameter : basic_type
    };

    SubprogramHead(SubprogramType st)
        : subprogram_type(st)
    {}
    void accept(Visitor *visitor) override;

    SubprogramType get_type() { return subprogram_type; }
    void set_id(std::string id) { subprogram_id = id; }
    std::string get_id() { return subprogram_id; }

  private:
    std::string subprogram_id;
    SubprogramType subprogram_type;
};

class FormalParam: public AstNode
{
    // 子节点为ParamLists
    // formal_parameter -> EPSILON
    //                  | ( parameter_lists )
};

class ParamList: public AstNode
{
    //  parameter_list -> var_parameter | value_parameter
  public:
    enum class ParamType
    {
        VarParam,
        ValueParam
    };
    ParamList(ParamType pt)
        : param_type(pt)
    {}
    ParamType get_type() { return param_type;}

  private:
    ParamType param_type;
};

class ParamLists: public AstNode
{
  public:
    enum class GrammarType
    {
        SINGLE_PARAM_LIST,    // param_lists -> param_list
        MULTIPLE_PARAM_LIST,  // param_lists -> param_lists ; param_list
    };

    ParamLists(GrammarType gt)
        : grammar_type(gt)
    {}
    GrammarType get_type() { return grammar_type;}
    void accept(Visitor *visitor) override;
    std::vector<ParamList*> Lists();

  private:
    GrammarType grammar_type;
};

class VarParam: public AstNode
{
    // 子节点为ValueParam
    // var_param -> var value_param
};

class ValueParam: public AstNode
{
    // 子节点为IdList和TypeNode
    // ValueParam -> idlist : basic_type
  public:  
    ValueParam(){};
    bool is_ref() { return isVar; }
    void set_ref() { isVar = true; }
    
    void accept(Visitor *visitor) override;
  private:
    bool isVar = false;
};

/**************************************************
                    语句部分节点
***************************************************/
class CompoundStatement: public AstNode
{
    // CompoundStatement -> begin StatementList end
  public:
    void accept(Visitor *visitor) override;
};

class StatementList: public AstNode
{
    // statement_list -> statement | statement_list ; statement
  public:
    void accept(Visitor *visitor) override;
};

class Statement: public AstNode
{
  // 子节点为各种statement节点
  public:
    enum class StatementType
    {
        EPSILON,             // statement -> EPSILON
        ASSIGN_OP_STATEMENT, // 子节点为AssignopStatement

        PROCEDURE_CALL,      // statement -> procedure_call
                             // 子节点为ProcedureCall
        COMPOUND_STATEMENT,  // statement -> compound_statement
                             // 子节点为CompoundStatement
        IF_STATEMENT,        // statement -> if-statement
                             // 子节点为IfStatement
        LOOP_STATEMENT,      // statement -> loop-statement
                             // 子节点为LoopStatement
    };

    Statement(StatementType st)
        : statement_type(st)
    {}
    void accept(Visitor *visitor);  //访问者接口
    StatementType get_type(){ return statement_type;}
  private:
    StatementType statement_type;
};

class AssignopStatement: public AstNode
{
    // 其子节点为 Variable 节点和 Expression 节点
  public:
    enum class LeftType
    {
        VARIABLE,  // statement -> variable assignop expression
        FUNCID,      // statement -> func_id assignop expression
    };
    AssignopStatement(LeftType lt)
        : left_type(lt)
    {}
    LeftType get_type() { return left_type;}
    void set_type(LeftType lt) { left_type = lt;}
  void accept(Visitor *visitor);  //访问者接口
  private:
    LeftType left_type;
    //std::string varname;
};

class ProcedureCall: public AstNode
{
  // 其子节点为 id 叶子节点和可能存在的 ExpressionList 节点
  public:
    enum class ProcedureType
    {
        NO_LIST,          // procedure_call -> id
        EXP_LIST,      // procedure_call -> id ( expression_list )
        VAR_LIST,      // procedure_call -> id ( variable_list )
    };

    ProcedureCall(ProcedureType pt, std::string id)
        : procedure_type(pt), procedure_id(id)
    {}
    std::string get_id() { return procedure_id; }
    ProcedureType get_type() { return procedure_type;}

  void accept(Visitor *visitor);  //访问者接口
  private:
    ProcedureType procedure_type;
    std::string procedure_id;
};

class IfStatement: public AstNode
{
    // if_statement -> if expression then statement else_part
  public:
    void accept(Visitor *visitor) override;
};

class LoopStatement: public AstNode
{
  public:
    enum class LoopType
    {
        FORUP,
        FORDOWN,
        WHILE_,
        REPEAT_,
    };
    // loop-statement -> for id assignop(:=) expression to expression do statement
    //                 | for id assignop expression downto expression do statement
    //                 | while expression do statement
    //                 | repeat statement until expression
    LoopStatement(LoopType lt): loop_type(lt){};
    LoopType get_type() { return loop_type; }

 void accept(Visitor *visitor);  //访问者接口
  private:
    LoopType loop_type;
};

class ElsePart: public AstNode
{
  public:
    enum class ELSEType
    {
        EPSILON,         // else_part -> EPSILON
        ELSE_STATEMENT,  // else_part -> else statement
    };

    ElsePart(ELSEType gt)
        : grammar_type_(gt)
    {}
    ELSEType get_type() { return grammar_type_; }
    // Statement *GetStatement() {
    //     return cnode_list[0]->DynamicCast<StatementNode>();
    // }
 void accept(Visitor *visitor);  //访问者接口
  private:
    ELSEType grammar_type_;
};

/*函数的参数节点*/
class VariableList: public AstNode
{
    // 子节点为Variable节点或VariableList节点与Variable节点
  public:
    enum class GrammarType
    {
        VAR_,                // variable_list -> variable
        VAR_LIST_VAR,       // variable_list -> variable_list , variable
    };

    VariableList(GrammarType gt)
        : grammar_type(gt)
    {}
    std::string FormatString();
    vector<AstNode* > Lists();
    bool set_types(std::vector<BaseType *> *type_list);
    GrammarType get_type() { return grammar_type;}
  
  void accept(Visitor *visitor);  //访问者接口
  private:
    std::vector<std::string> *variable_type_list;
    GrammarType grammar_type;
};

class Variable: public AstNode
{
    // 子节点为 ID叶子节点 与 IDVarParts节点
    // variable -> id id_varparts
  public:
    Variable() {}
    Variable(std::string vn): var_type(vn){}
    std::string get_vn() { return var_type; }
    void set_vn(string vn) { var_type = vn;}

    void accept(Visitor *visitor) override;
  private:
    std::string var_type;   // 类型名
};

class IDVarParts: public AstNode
{
  public:
    
    void set_pointer(std::vector<std::string> * pn){ parts_name = pn;}
    std::vector<std::string> *get_pointer(){ return parts_name; }
    void accept(Visitor *visitor) override;

  private:
    std::vector<std::string> *parts_name;
};

class IDVarPart: public AstNode
{
  public:
    enum class GrammarType
    {
        _ID,       // id_varpart -> .id
        EXP_LIST,  // id_varpart -> [ expression_list ]
    };

    IDVarPart(GrammarType gt)
        : grammar_type(gt)
    {}
    GrammarType get_type() { return grammar_type; }
    void set_array_lb(int lb) { array_lb_ = lb; }
    void set_part_name(std::string pn) { part_name = pn; }
    std::string get_part_name() { return part_name; }

    void accept(Visitor *visitor) override;

  private:
    int array_lb_ = 0;
    std::string part_name = "none";
    GrammarType grammar_type;
};

/*********************************
            表达式节点
*********************************/
class ExpressionList: public AstNode
{
    // 子节点为单个Expression节点或ExpressionList节点与Expression节点
  public:
    enum class ExpressionType
    {
        SINGLE,    // expression_list -> expression
        MULTIPLE,  // expression_list -> expression_list , expression
    };

    ExpressionList(ExpressionType et, std::vector<std::string> *tl)
        : expression_type(et), exp_type(tl)
    {}
    std::vector<std::string> * get_types(){
      return exp_type;
    };
    ExpressionType get_type() { return expression_type;}
    std::vector<AstNode *> Lists();
    void accept(Visitor *visitor) override;

  private:
    std::vector<std::string> *exp_type;    // 存储从左到当前expression的类型
    ExpressionType expression_type;
};

class Expression: public AstNode
{
    // 子节点为至多两个SimpleExpression节点
    // expression -> simple_expression
    //            | simple_expression relop simple_expression
  public:
    enum class GrammarType
    {
        SINGLE,          // simple_expression
        DOUBLE,             // simple_expression relop simple_expression
    };
    Expression(GrammarType gt, std::string st, std::string et)
        : grammar_type(gt), symbol_type(st), expression_type(et)
    {}
    GrammarType GetGraType() { return grammar_type; }  // 返回语法类型
    std::string GetSymType() { return symbol_type; }   // 返回符号类型
    std::string GetExpType() { return expression_type;}  // 返回表达式类型
    void SetExpType(std::string et) { expression_type = et;}

 void accept(Visitor *visitor);  // 访问者接口
  private:
    GrammarType grammar_type;
    std::string symbol_type;
    std::string expression_type;
};

class SimpleExpression: public AstNode
{
    // 子节点为可能存在的 SimpleExpression 节点 与 一个 Term 节点
    // simple_expression -> term | simple_expression addop term
  public:
    enum class SymbolType
    {
        PLUS_,
        MINUS_,
        OR_,
        SINGLE
    };
    SimpleExpression(SymbolType st, std::string et)
        : symbol_type(st)
        , expression_type(et)
    {}
    SymbolType GetSymType() { return symbol_type; } // 返回符号类型
    std::string GetExpType() { return expression_type; }  // 返回表达式类型
    void SetExpType(std::string et) { expression_type = et;}

 void accept(Visitor *visitor);  // 访问者接口
  private:
    SymbolType symbol_type;
    std::string expression_type;
};

class Term: public AstNode
{
    // 子节点为可能存在的 Term 节点 与 一个 Factor 节点
    // term -> factor | term mulop factor
  public:
    enum class SymbolType
    {
        MULTIPLY,
        DEVIDE,
        MOD,
        AND,
        SINGLE
    };
    Term(SymbolType st, std::string et)
        : symbol_type(st)
        , term_type(et){};
    Term(){};
    void SetSymType(SymbolType st){
      symbol_type = st;
    }
    void SetTerType(std::string tt){
      term_type = tt;
    }
    SymbolType GetSymType() { return symbol_type; }
    std::string GetTerType() { return term_type; }

 void accept(Visitor *visitor);  //访问者接口
  private:
    SymbolType symbol_type;
    std::string term_type;
};

class Factor: public AstNode
{
  public:
    enum class GrammerType
    {
        NUM,          // factor -> num 子节点为叶子节点
        VARIABLE,     // factor -> variable 子节点为Variable节点
        EXP,          // factor -> ( expression ) 子节点为Expression节点
        ID_EXP_LIST,  // factor -> id ( expression_list ) 子节点为叶子节点和 expression_list节点
        NOT_,          // factor -> not factor 子节点为factor节点
        UMINUS_,       // factor -> - factor 子节点为factor节点
        CHAR_,         // factor -> ′ letter ′ 子节点为叶子节点
        STR,       // 子节点为叶子节点
        BOOL          // 子节点为叶子节点
    };

    Factor(GrammerType gt)
        : grammer_type(gt)
    {}
    std::string GetFacType(){ return factor_type; }
    GrammerType get_type(){ return grammer_type; }
    bool GetNot() {return is_uminus; }
    void SetFacType(std::string ft){ factor_type = ft; }
    void SetUminus(){ is_uminus = true; }


 void accept(Visitor *visitor);  //访问者接口
  private:
    GrammerType grammer_type;
    bool is_uminus = false; // 若为not factor与- factor则为true
    std::string factor_type = "unknown";

};

class Visitor
{
  public:
    virtual void visit(AST *AST)                           = 0;
    virtual void visit(AstNode *astnode)                   = 0;
    virtual void visit(LeafNode *leafnode)                 = 0;
    //virtual void visit(ProgramHead *programhead)                 = 0;
    virtual void visit(IdList *idlist)                     = 0;
    virtual void visit(ConstDeclaration *constdeclaration) = 0;
    virtual void visit(TypeNode *typenode) = 0;
    virtual void visit(StringTypeNode *stringtypenode) = 0;
    virtual void visit(VarDeclaration *vardeclaration) = 0;
    virtual void visit(PeriodsNode *periodsnode) = 0;
    virtual void visit(SubprogramDeclaration *subprogramdeclaration) = 0;
    virtual void visit(SubprogramHead *subprogramhead) = 0;
    virtual void visit(ParamLists *paramlists) = 0;
    virtual void visit(ValueParam *valueparam) = 0;

    virtual void visit(StatementList *statementList) = 0;
    virtual void visit(IfStatement *ifStatement ) = 0;
    virtual void visit(ElsePart *elseNode )  = 0;
    virtual void visit(ProcedureCall *procedureCall ) = 0;
    virtual void visit(AssignopStatement *assignopStatement ) = 0;
    virtual void visit(LoopStatement *loopStatement ) = 0;
    virtual void visit(Variable *variable ) = 0;
    virtual void visit(VariableList *variableList ) = 0;
    virtual void visit(IDVarPart *idVarPart ) = 0;
    virtual void visit(IDVarParts *idVarParts ) = 0;
    virtual void visit(Term *term ) = 0;
    virtual void visit(Factor *factor ) = 0;
    virtual void visit(Expression *expression ) = 0;
    virtual void visit(SimpleExpression *simpleExpression ) = 0;
    virtual void visit(Statement *statement ) = 0;
    virtual void visit(CompoundStatement *compoundStatement ) = 0;
    virtual void visit(ExpressionList *expressionList ) = 0;
};

class GenerationVisitor: public Visitor
{
  public:
    void visit(AST *AST) override;
    void visit(AstNode *astnode) override;
    void visit(LeafNode *leafnode) override;
    void visit(IdList *idlist) override;
    void visit(ConstDeclaration *constdeclaration) override;
    void visit(TypeNode *typenode) override;
    void visit(StringTypeNode *stringtypenode) override;
    void visit(VarDeclaration *vardeclaration) override;
    void visit(PeriodsNode *periodsnode) override;
    void visit(SubprogramDeclaration *subprogramdeclaration) override;
    void visit(SubprogramHead *subprogramhead) override;
    void visit(ParamLists *paramlists) override;
    void visit(ValueParam *valueparam) override;

    void visit(StatementList *statementList) override;
    void visit(IfStatement *ifStatement ) override;
    void visit(ElsePart *elseNode )  override;
    void visit(ProcedureCall *procedureCall ) override;
    void visit(AssignopStatement *assignopStatement ) override;
    void visit(LoopStatement *loopStatement ) override;
    void visit(Variable *variable ) override;
    void visit(VariableList *variableList ) override;
    void visit(IDVarPart *idVarPart ) override;
    void visit(IDVarParts *idVarParts ) override;
    void visit(Term *term ) override;
    void visit(Factor *factor ) override;
    void visit(Expression *expression ) override;
    void visit(SimpleExpression *simpleExpression ) override;
    void visit(Statement *statement ) override;
    void visit(CompoundStatement *compoundStatement ) override;
    void visit(ExpressionList *expressionList ) override;
};

class SemanticVisitor: public Visitor
{
  public:
    void visit(AST *AST) override;
    void visit(AstNode *astnode) override;
    void visit(LeafNode *leafnode) override {leafnode->DynamicCast<AstNode>()->accept(this);};
    void visit(IdList *idlist) override { idlist->DynamicCast<AstNode>()->accept(this);};
    //void visit(ProgramHead *programhead) override;
    void visit(ConstDeclaration *constdeclaration) override;
    void visit(TypeNode *typenode) override {typenode->DynamicCast<AstNode>()->accept(this);};
    void visit(StringTypeNode *stringtypenode) override {stringtypenode->DynamicCast<AstNode>()->accept(this);};
    void visit(VarDeclaration *vardeclaration) override;
    void visit(PeriodsNode *periodsnode) override { periodsnode->DynamicCast<AstNode>()->accept(this);};
    void visit(SubprogramDeclaration *subprogramdeclaration) override { subprogramdeclaration->DynamicCast<AstNode>()->accept(this);};
    void visit(SubprogramHead *subprogramhead) override;
    void visit(ParamLists *paramlists) override { paramlists->DynamicCast<AstNode>()->accept(this);};
    void visit(ValueParam *valueparam) override { valueparam->DynamicCast<AstNode>()->accept(this);};
    
    void visit(CompoundStatement *compoundStatement ) override { compoundStatement->DynamicCast<AstNode>()->accept(this);};
    void visit(StatementList *statementList) override { statementList->DynamicCast<AstNode>()->accept(this);};
    void visit(Statement *statement ) override { statement->DynamicCast<AstNode>()->accept(this);};
    void visit(IfStatement *ifStatement ) override { ifStatement->DynamicCast<AstNode>()->accept(this);};
    void visit(ElsePart *elseNode )  override { elseNode->DynamicCast<AstNode>()->accept(this);};
    void visit(ProcedureCall *procedureCall ) override { procedureCall->DynamicCast<AstNode>()->accept(this);};
    void visit(AssignopStatement *assignopStatement ) override ;
    void visit(LoopStatement *loopStatement ) override { loopStatement->DynamicCast<AstNode>()->accept(this);};
    void visit(Variable *variable ) override ;
    void visit(VariableList *variableList ) override ;
    void visit(IDVarPart *idVarPart ) override { idVarPart->DynamicCast<AstNode>()->accept(this);};
    void visit(IDVarParts *idVarParts ) override { idVarParts->DynamicCast<AstNode>()->accept(this);};
    void visit(ExpressionList *expressionList ) override ;
    void visit(Expression *expression ) override ;
    void visit(SimpleExpression *simpleExpression ) override ;
    void visit(Term *term ) override ;
    void visit(Factor *factor ) override ;
};


}  // namespace ast
