#pragma once

#include <iostream>
#include <vector>

namespace ast {

class astnode
{
  public:
    //构造及析构函数
    astnode()
        : pnode(nullptr){};
    virtual ~astnode()
    {
        for (auto child : cnode_list) {
            delete child;
        }
    }

    //添加父节点及查看父节点的方法
    void set_parent(astnode *parent)
    {
        pnode = parent;
    }
    astnode *parent()
    {
        return pnode;
    }

    //添加子节点及查看子节点的方法
    void append_child(astnode *child)
    {
        cnode_list.emplace_back(child);
    }
    astnode *get(int pos)
    {
        return cnode_list[pos];
    }

  protected:
    astnode *pnode;
    std::vector<astnode *> cnode_list;
};

class AST
{
  public:
    ~AST()
    {
        if (astroot != nullptr)
            delete astroot;
    }
    void set_root(astnode *root) { astroot = root; }

  private:
    astnode *astroot = nullptr;
};

class LeafNode: public astnode
{
  public:
    LeafNode() {}
    LeafNode(ConstValue val)
        : value_(val)
    {}

    // getter and setter
    const std::string id_ref()
    {
        return is_ref_ ? "(*" + value_.get<std::string>() + ")"
                       : value_.get<std::string>();
    }
    void set_value(ConstValue value) { value_ = value; }
    void set_ref(bool ref) { is_ref_ = ref; }
    // template value getter
    template<typename T>
    T value()
    {
        return value_.get<T>();
    }
    BasicType *type() { return value_.type(); }

    // Analyze reference
    bool AnalyzeReference(TableSet *ts, FunctionSymbol *fn);
    // override formater
    void Format(FILE *dst) override;

  private:
    ConstValue value_;     // const values
    bool is_ref_ = false;  // is referenced
};

class ProgramStruct: public astnode
{
    //program_head -> program id ( idlist ) | program id
    //
};

class ProgramHead: public astnode
{
    //program_head -> program id ( idlist ) | program id
};

class ProgramBody: public astnode
{
    // program_body -> const_declarations
    //                 var_declarations
    //                 subprogram_declarations
    //                 compound_statement
    //共四个子节点
};

class IdList: public astnode
{
    //idlist -> id | idlist , id
  public:
    enum class GrammarType
    {
        SINGLE_ID,   // idlists -> id
        MULTIPLE_ID  // idlists -> idlist,id
    };
    IdList(GrammarType gt)
        : grammar_type_(gt)
    {}
    std::vector<LeafNode *> Lists();

  private:
    GrammarType grammar_type_;
};

class ConstDeclarations: public astnode
{
  public:
    enum class GrammarType
    {
        SINGLE_ID,   // const_declaration -> id = const_value
        MULTIPLE_ID  // const_declaration -> const_declaration ; id = const_value
    };
    ConstDeclarations(GrammarType gt, BasicType *bt)
        : grammar_type_(gt)
        , type_(bt)
    {}

  private:
    GrammarType grammar_type_;
    BasicType *type_;
};

class ConstDeclaration: public astnode
{
    // const_variable ->  +num | -num | num | 'letter'
};

class VarDeclarations: public astnode
{
    //拥有n个子节点VarDeclaration
    //var_declarations -> ε | var var_declaration ;
};

class VarDeclaration: public astnode
{
    //子节点为一个TypeNode节点以及IdList节点
  public:
    enum class GrammarType
    {
        SINGLE_DECL,   // variable_declaration -> idlist : xx
        MULTIPLE_DECL  // variable_declaration -> variable_declaration ; idlist : xx
    };
    enum class ListType
    {
        TYPE,
        ID
    };
    VarDeclaration(GrammarType gt)
        : grammar_type_(gt)
    {}

  private:
    GrammarType grammar_type_;
};

class TypeNode: public astnode
{
    //子节点为各个类型节点
  public:
    enum class VarType
    {
        BASIC_TYPE,
        ARRAY,
        RECORD_TYPE,
        STRING_TYPE
    };

    TypeNode(VarType vt)
        : var_type(vt)
    {}

    VarType GeVartype() { return var_type; }

  private:
    VarType var_type;
};

class BasicType: public astnode
{
    // BasicType -> integer|real|boolean|char
  public:
    BasicType() {}
    BasicType(BasicType *type)
        : btype(type)
    {}

    void set_type(BasicType *type) { btype = type; }
    BasicType *type() { return btype; }

  private:
    BasicType *btype;
};

/**************************************************
                    子程序部分节点
***************************************************/
class SubprogramDeclarations: public astnode
{
    //subprogram_declarations -> ε | subprogram_declarations subprogram ;
};

class SubprogramDeclaration: public astnode
{
    //subprogram -> subprogram_head ; subprogram_body
};

class SubprogramBody: public astnode
{
    // subprogram_body -> const_declarations
    //                   var_declarations
    //                   compound_statement
};

class SubprogramHead: public astnode
{
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
    void set_id(std::string id) { subprogram_id = id; }
    std::string get_id() { return subprogram_id; }

  private:
    std::string subprogram_id;
    SubprogramType subprogram_type;
};

class FormalParam: public astnode
{
    // 子节点为ParamLists
    // formal_parameter -> EPSILON
    //                  | ( parameter_lists )
};

class ParamLists: public astnode
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

  private:
    GrammarType grammar_type;
};

class ParamList: public astnode
{
    //  parameter_list -> var_parameter | value_parameter
  public:
    enum class ParamType
    {
        VarParam,
        ValueParam
    };

  private:
    ParamType param_type;
};

class VarParam: public astnode
{
    // 子节点为ValueParam
    // var_param -> var value_param
};

class ValueParam: public astnode
{
    // 子节点为IdList和BasicType
    // ValueParam -> idlist : basic_type
};

/**************************************************
                    语句部分节点
***************************************************/
class CompoundStatement: public astnode
{
    // CompoundStatement -> begin StatementList end
};

class StatementList: public astnode
{
    // statement_list -> statement | statement_list ;
};

class Statement: public astnode
{
  public:
    enum class StatementType
    {
        EPSILON,             // statement -> EPSILON
        ASSIGN_OP_STATEMENT,

        PROCEDURE_CALL,      // statement -> procedure_call
        COMPOUND_STATEMENT,  // statement -> compound_statement
        IF_STATEMENT,        // statement -> if-statement
        LOOP_STATEMENT,      // statement -> loop-statement

        READ_STATEMENT,      // statement -> read ( variable_list )
        READLN_STATEMENT,    // statement -> readln ( variable_list )
        WRITE_STATEMENT,     // statement -> write ( expression_list )
        WRITELN_STATEMENT,   // statement -> writeln ( expression_list )
    };

    Statement(StatementType st)
        : statement_type(st)
    {}

  private:
    StatementType statement_type;
};

class AssignopStatement: public astnode
{
    //
  public:
    enum class LEFTTYPE
    {
        VARIABLE,  // statement -> variable assignop expression
        FUNC,      // statement -> func_id assignop expression
    };

  private:
    LEFTTYPE left_type;
};

class ProcedureCall : public astnode {
public:
    enum class ProcedureType {
        LIST,           // procedure_call -> id
        WITHOUT_LIST,   // procedure_call -> id ( expression_list )
    };

    ProcedureCall(ProcedureType pt)
        : procedure_type(pt)
    {}

  private:
    ProcedureType procedure_type;
};

class IfStatement: public astnode
{
    // if_statement -> if expression then statement else_part
};

class LoopStatement: public astnode
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
  private:
    LoopType loop_type;
};

class ElsePart : public astnode {
public:
    enum class ELSEType {
        EPSILON,         // else_part -> EPSILON
        ELSE_STATEMENT,  // else_part -> else statement
    };

    ElsePart(ELSEType gt)
        : grammar_type_(gt)
    {}
    // Statement *GetStatement() {
    //     return cnode_list[0]->DynamicCast<StatementNode>();
    // }

  private:
    ELSEType grammar_type_;
};

/*函数的参数节点*/
class VariableList: public astnode
{
    // 子节点为多个Variable节点
public:
    enum class GrammarType {
        VARIABLE,                // variable_list -> variable
        VARIABLE_LIST_VARIABLE,  // variable_list -> variable_list , variable
    };

    VariableList(GrammarType gt)
        : grammar_type_(gt)
    {}
    std::string FormatString();
    bool set_types(std::vector<TypeTemplate *> *type_list);

  private:
    std::vector<BasicType *> basic_types;
    GrammarType grammar_type_;
};

class Variable : public astnode {
    // 子节点为IDVarParts
    // variable -> id id_varparts
};

class IDVarParts : public astnode {
public:
    //id_varparts -> ε | id_varparts id_varpart
    void set_lb(std::vector<ArrayType::ArrayBound> &bound) {
        if (child_list_.size() == 0) return;
        child_list_[0]->DynamicCast<IDVarPartsNode>()->set_lb(bound);
        if (child_list_[1]->DynamicCast<IDVarPartNode>()->grammar_type() ==
            IDVarPartNode::GrammarType::EXP_LIST) {
            child_list_[1]->DynamicCast<IDVarPartNode>()->set_array_lb(bound[0].lb_);
            bound.erase(bound.begin());
        }
    }
};

class IDVarPart : public astnode {
public:
    enum class GrammarType {
        _ID,       // id_varpart -> .id
        EXP_LIST,  // id_varpart -> [ expression_list ]
    };

    IDVarPartNode(GrammarType gt)
        : grammar_type_(gt)
    {}
    GrammarType grammar_type() { return grammar_type_; }
    void Format(FILE *dst) override;
    void set_array_lb(int lb) { array_lb_ = lb; }

  private:
    int array_lb_ = 0;
    GrammarType grammar_type_;
};

/*表达式节点*/
class ExpressionList : public astnode {
    //子节点为多个Expression节点
public:
    enum class ExpressionType {
        SINGLE,           // expression_list -> expression
        MULTIPLE,         // expression_list -> expression_list , expression
    };

    ExpressionList(ExpressionType et) : grammar_type_(et) {}
    bool set_types(std::vector<TypeTemplate *> *type_list);

private:
    std::vector<BasicType *> basic_types;
    ExpressionType expression_type;
};

class Expression : public astnode {
    //子节点为至多两个SimpleExpression节点
    // expression -> simple_expression
    //            | simple_expression relop simple_expression
public:
    enum class ExpressionType {
        EXPRESSION,
        VAR_ARRAY,
    };
    Expression(SymbolType st) : symbol_type(st) {}
    SymbolType GetType() { return symbol_type; }

private:
    ExpressionType expression_type;
    SymbolType symbol_type;   

};

class SimpleExpression: public astnode {
    // 子节点为可能存在的 SimpleExpression 节点 与 一个 Term 节点
    // simple_expression -> term | simple_expression addop term
public:
    enum class SymbolType{
        AND,
        MINUS,
        OR,
    };
    enum class ExpressionType{

    };
    SimpleExpression(SymbolType st) : symbol_type(st) {}
    SymbolType GetType() { return symbol_type; }

private:
    SymbolType symbol_type;
    ExpressionType expression_type;
};

class Term : public astnode {
    // 子节点为可能存在的 Term 节点 与 一个 Factor 节点
    // term -> factor | term mulop factor
public:
    enum class SymbolType{
        MULTIPLY,
        DEVIDE,
        MOD,
        AND,
    };
    enum class TermType{

    };
    Term(SymbolType st) : symbol_type(st) {}
    SymbolType GetType() { return symbol_type; }

private:
    SymbolType symbol_type; 
    TermType term_type;
};

class Factor : public astnode {
public:
    enum class FactorType {
        NUM,          // factor -> num
        VARIABLE,     // factor -> variable
        EXP,          // factor -> ( expression )
        ID_EXP_LIST,  // factor -> id ( expression_list )
        NOT,          // factor -> not factor
        UMINUS,       // factor -> - factor
        RECORD,       // factor -> record-id . record-member
        STRING,       // factor -> ′ letter ′
    };

    Factor(FactorType ft) : factor_type(ft) {}

private:
    FactorType factor_type;
};

}  // namespace ast

#endif

