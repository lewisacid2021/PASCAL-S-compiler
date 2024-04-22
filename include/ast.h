#pragma once

#include "type.h"
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

    virtual void accept(Visitor *visitor, FILE *fs);  //访问者接口
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

  protected:
    AstNode *pnode;
    std::vector<AstNode *> cnode_list;
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

    void accept(Visitor *visitor, FILE *fs);  //访问者接口

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
    LeafNode() {}
    LeafNode(ConstValue val, LeafType lt)
        : value_(val), leaf_type(lt)
    {}
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
    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

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

    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

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
    void print_type(FILE *fs);

    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
    ConstValue::ConstvalueType type;  // 记录该常变量的类型。
};

class RecordDelcarations: public AstNode
{
    // 子节点为单个RecordDelcaration节点或者没有
    // record_declarations -> ε | record_declaration ;
    enum class GrammarType
    {
        EPSILON,
        DECLARATION,
    };

    RecordDelcarations(GrammarType gt)
        : grammar_type(gt){};
    GrammarType GetGrammarType()
    {
        return grammar_type;
    };

  private:
    GrammarType grammar_type;
};

class RecordDelcaration: public AstNode
{
    // 子节点为RecordDelcaration节点，叶子节点id，以及var_declaration节点。
    // record_declaration -> def-record | record_declaration def-record
    // def-record -> type 
    //               record-name = record
    //               var_declaration
    //               end;
    enum class GrammarType
    {
        SINGLE_DECLARATION,
        MULTI_DECLARATION,
    };

    RecordDelcaration(GrammarType gt)
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

    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

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
    TypeNode(VarType vt, std::string &tn)
        : var_type(vt), type_name(tn)
    {}
    VarType GetVarType() { return var_type; }
    std::string get_type_name() { return type_name; }
    
    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

  private:
    VarType var_type;
    std::string type_name;
};

class ArrayTypeNode: public AstNode
{
    // 子节点为 PeriodsNode 与 TypeNode
  public:
    ArrayTypeNode() {}
    ArrayTypeNode(std::string &type)
        : type_name(type)
    {}

    void set_type(std::string &type) { type_name = type; }
    void set_info(ArrayType *at) { array_info = at; }
    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口
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
    void set_dm(std::vector<ArrayType::Dimension> &low_dm){
      dm = low_dm;
    }
    std::vector<ArrayType::Dimension> get_dm(){
      return dm;
    }
    PeriodsNode get_type(){
      return period_type;
    }
    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口

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
    void accept(Visitor *visitor, FILE *fs) override;  //访问者接口
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
        PROCEDURE,  // subprogram_head -> procedure id formal_parameter
        FUNCTION    // subprogram_head -> function id formal_parameter : basic_type
    };

    SubprogramHead(SubprogramType st)
        : subprogram_type(st)
    {}
    SubprogramType get_type() { return subprogram_type; }
    void set_id(std::string &id) { subprogram_id = id; }
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

  private:
    GrammarType grammar_type;
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

class VarParam: public AstNode
{
    // 子节点为ValueParam
    // var_param -> var value_param
};

class ValueParam: public AstNode
{
    // 子节点为IdList和TypeNode
    // ValueParam -> idlist : basic_type
};

/**************************************************
                    语句部分节点
***************************************************/
class CompoundStatement: public AstNode
{
    // CompoundStatement -> begin StatementList end
};

class StatementList: public AstNode
{
    // statement_list -> statement | statement_list ; statement
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
    void accept(Visitor *visitor, FILE *fs);  //访问者接口
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
 void accept(Visitor *visitor, FILE *fs);  //访问者接口
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

    ProcedureCall(ProcedureType pt, std::string &id)
        : procedure_type(pt), procedure_id(id)
    {}
    std::string get_id() { return procedure_id; }

 void accept(Visitor *visitor, FILE *fs);  //访问者接口
  private:
    ProcedureType procedure_type;
    std::string procedure_id;
};

class IfStatement: public AstNode
{
    // if_statement -> if expression then statement else_part
};

class LoopStatement: public AstNode
{
  public:
    enum class LoopType
    {
        FORUP,
        FORDOWN,
        WHILE,
        REAPT,
    };
    // loop-statement -> for id assignop(:=) expression to expression do statement
    //                 | for id assignop expression downto expression do statement
    //                 | while expression do statement
    //                 | repeat statement until expression
 void accept(Visitor *visitor, FILE *fs);  //访问者接口
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
    // Statement *GetStatement() {
    //     return cnode_list[0]->DynamicCast<StatementNode>();
    // }
 void accept(Visitor *visitor, FILE *fs);  //访问者接口
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
        VAR,                // variable_list -> variable
        VAR_LIST_VAR,       // variable_list -> variable_list , variable
    };

    VariableList(GrammarType gt)
        : grammar_type(gt)
    {}
    std::string FormatString();
    bool set_types(std::vector<BaseType *> *type_list);
  
  void accept(Visitor *visitor, FILE *fs);  //访问者接口
  private:
    std::vector<std::string> *variable_type_list;
    GrammarType grammar_type;
};

class Variable: public AstNode
{
    // 子节点为 ID叶子节点 与 IDVarParts节点
    // variable -> id id_varparts
  public:
    Variable(std::string &vn): var_name(vn){}
    std::string get_vn() { return var_name; }

  private:
    std::string var_name;   // 类型名
};

class IDVarParts: public AstNode
{
  public:
    //id_varparts -> ε | id_varparts id_varpart
    // void set_lb(std::vector<ArrayType::ArrayBound> &bound) {
    //     if (child_list_.size() == 0) return;
    //     child_list_[0]->DynamicCast<IDVarPartsNode>()->set_lb(bound);

    //     if (child_list_[1]->DynamicCast<IDVarPartNode>()->grammar_type() ==
    //         IDVarPartNode::GrammarType::EXP_LIST) {
    //         child_list_[1]->DynamicCast<IDVarPartNode>()->set_array_lb(bound[0].lb_);
    //         bound.erase(bound.begin());
    //     }
    // }
  private:
    std::vector<std::string> *parts;
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

  private:
    int array_lb_ = 0;
    std::string part_type;
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
    Expression(GrammarType gt, std::string& st, std::string &et)
        : grammar_type(gt), symbol_type(st), expression_type(et)
    {}
    GrammarType GetGraType() { return grammar_type; }  // 返回语法类型
    std::string GetSymType() { return symbol_type; }   // 返回符号类型
    std::string GetExpType() { return expression_type;}  // 返回表达式类型

 void accept(Visitor *visitor, FILE *fs);  // 访问者接口
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
        PLUS,
        UMINUS,
        OR,
        SINGLE
    };
    SimpleExpression(SymbolType st, std::string &et)
        : symbol_type(st)
        , expression_type(et)
    {}
    SymbolType GetSymType() { return symbol_type; } // 返回符号类型
    std::string GetExpType() { return expression_type; }  // 返回表达式类型
 void accept(Visitor *visitor, FILE *fs);  // 访问者接口
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
    Term(SymbolType st, std::string &et)
        : symbol_type(st)
        , term_type(et){};
    SymbolType GetSymType() { return symbol_type; }
    std::string GetTerType() { return term_type; }

 void accept(Visitor *visitor, FILE *fs);  //访问者接口
  private:
    SymbolType symbol_type;
    std::string term_type;
};

class Factor: public AstNode
{
  public:
    enum class GrammerType
    {
        NUM,          // factor -> num
        VARIABLE,     // factor -> variable
        EXP,          // factor -> ( expression )
        ID_EXP_LIST,  // factor -> id ( expression_list )
        NOT,          // factor -> not factor
        UMINUS,       // factor -> - factor
        CHAR,         // factor -> ′ letter ′
        STRING
    };

    Factor(GrammerType gt)
        : grammer_type(gt)
    {}
    std::string GetFacType(){ return factor_type; }

 void accept(Visitor *visitor, FILE *fs);  //访问者接口
  private:
    GrammerType grammer_type;
    std::string factor_type;

};

class Visitor
{
  public:
    virtual void visit(AST *AST, FILE *fs)                           = 0;
    virtual void visit(AstNode *astnode, FILE *fs)                   = 0;
    virtual void visit(LeafNode *leafnode, FILE *fs)                 = 0;
    virtual void visit(IdList *idlist, FILE *fs)                     = 0;
    virtual void visit(ConstDeclaration *constdeclaration, FILE *fs) = 0;
    virtual void visit(TypeNode *typenode, FILE *fs) = 0;
    virtual void visit(ArrayTypeNode *arraytypenode, FILE *fs) = 0;
    virtual void visit(StringTypeNode *stringtypenode, FILE *fs) = 0;
    virtual void visit(VarDeclaration *vardeclaration, FILE *fs) = 0;
    virtual void visit(PeriodsNode *periodsnode, FILE *fs) = 0;
};

class GenerationVisitor: public Visitor
{
  public:
    void visit(AST *AST, FILE *fs) override;
    void visit(AstNode *astnode, FILE *fs) override;
    void visit(LeafNode *leafnode, FILE *fs) override;
    void visit(IdList *idlist, FILE *fs) override;
    void visit(ConstDeclaration *constdeclaration, FILE *fs) override;
    void visit(TypeNode *typenode, FILE *fs) override;
    void visit(StringTypeNode *stringtypenode, FILE *fs) override;
    void visit(VarDeclaration *vardeclaration, FILE *fs) override;
    void visit(PeriodsNode *periodsnode, FILE *fs) override;
};

}  // namespace ast
