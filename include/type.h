#pragma once

#include <string.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

class BaseType {
public:
    enum class TYPE { BASIC, RECORD, ARRAY, STRING};
    BaseType() {}
    BaseType(TYPE tt) : template_type(tt) {}
    virtual ~BaseType() {}
    template <typename T>
    T *DynamicCast() {
        return dynamic_cast<T *>(this);
    }

    TYPE GetType() { return template_type; }

protected:
    TYPE template_type;
};

class BasicType : public BaseType {
public:
    enum class BASIC_TYPE { INTEGER, REAL, BOOLEAN, CHAR, NONE};

    BasicType() : BaseType(TYPE::BASIC), basic_type(BASIC_TYPE::NONE) {}
    BasicType(BASIC_TYPE basic_type)
        : BaseType(TYPE::BASIC), basic_type(basic_type) {}

    ~BasicType() {}

    // getter and setter
    BASIC_TYPE type() { return basic_type; }

private:
    BASIC_TYPE basic_type;
};

class ArrayType : public BaseType {
public:
    struct Dimension {
        int lowbound;
        int upbound;

        Dimension(int low = 0, int up = 0) : lowbound(low), upbound(up){};
    };

    ArrayType() : BaseType(TYPE::ARRAY), base_type(nullptr) {}
    ArrayType(BaseType *type) : BaseType(TYPE::ARRAY), base_type(type) {}
    ArrayType(const ArrayType &a);
    ~ArrayType() {}

    // getter and setter
    void SetDimension(std::vector<Dimension> dim) { dimensions = dim; }
    BaseType *GetBasetype() { return base_type; }
    size_t GetDimsum() { return dimensions.size(); }               // get dimensions
    std::vector<Dimension> GetDimensions() { return dimensions; }  // get bounds
    Dimension GetDimension(size_t i) { return dimensions[i]; }  // get bound of dimension i

private:
    BaseType *base_type;         // basic types or record type
    std::vector<Dimension> dimensions;  // multi-dims bounds
};

constexpr int MAX_STRING_LEN = 256;

class StringType : public BaseType {
public:
    enum class GrammarType{
        LIMIT,    
        NOLIMIT,
    };
    StringType(GrammarType gt, int len): grammar_type(gt), length(len){};
    int GetLen() { return length; }
    GrammarType GetGrammarType() { return grammar_type; }

private:
    GrammarType grammar_type;
    int length = 0;
};


class RecordType : public BaseType {
public:
    RecordType() : BaseType(TYPE::RECORD) {}
    RecordType(std::unordered_map<std::string, BaseType *> types_map)
        : BaseType(TYPE::RECORD), types_map_(std::move(types_map)) {}
    ~RecordType() {}


    // add elements
    bool add(std::string name, BaseType *type);
    // find by names
    BaseType *Find(std::string name);
    // visit by names
    BaseType *Visit(std::vector<std::string> names);

private:
    std::unordered_map<std::string, BaseType *> types_map_;
};

class ConstValue {
public:
    enum class ConstvalueType{
        INTEGER, 
        REAL, 
        BOOLEAN, 
        CHAR,
        STRING,
    };
    ConstValue() {}
    ~ConstValue() {}
    // 拷贝构造函数
    ConstValue(const ConstValue &cv){
        switch(cv.value_type){
            case ConstvalueType::INTEGER:
                value_type = cv.value_type;
                C_INT = cv.C_INT;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::REAL:
                value_type = cv.value_type;
                C_STRING = cv.C_STRING;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::BOOLEAN:
                value_type = cv.value_type;
                C_BOOLEAN = cv.C_BOOLEAN;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::CHAR:
                value_type = cv.value_type;
                C_CHAR = cv.C_CHAR;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::STRING:
                value_type = cv.value_type;
                C_STRING = cv.C_STRING;
                Is_Uminus = cv.Is_Uminus;
                break;
        }
    }
    ConstValue(bool v) { 
        value_type =  ConstvalueType::BOOLEAN;
        C_BOOLEAN = v;
     }
    ConstValue(char v) { 
        value_type =  ConstvalueType::CHAR;
        C_CHAR = v;
     }
    ConstValue(int v) { 
        value_type =  ConstvalueType::INTEGER;
        C_INT = v;
    }
    ConstValue(std::string &v) { 
        C_STRING = v;
        if(isValidFloat(v))
            value_type =  ConstvalueType::REAL;
        else    value_type =  ConstvalueType::STRING;
    }

    bool isValidFloat(const std::string& str) {
    try {
        std::size_t pos = 0;
        std::stof(str, &pos);
        return pos == str.size();  // Make sure the entire string was converted
    } catch (const std::exception&) {
        return false;
    }
}

    // get by type
    template <typename T>
    T get() {
        if (std::is_same<T, int>::value)
        return *(T *)(&C_INT);
        else if (std::is_same<T, char>::value)
        return *(T *)(&C_CHAR);
        else if (std::is_same<T, float>::value)
        return *((T *)(&C_STRING));
        else if (std::is_same<T, bool>::value)
        return *(T *)(&C_BOOLEAN);
        else if (std::is_same<T, std::string>::value)
        return *((T *)(&C_STRING));
        else {
        throw std::runtime_error("ConstValue : get() : type " +
                                std::string(typeid(T).name()) +
                                " not supported");
        }
    }
    void set_int(int v) {
        value_type =  ConstvalueType::INTEGER;
        C_INT = v;
    }
    void set_float(std::string v) {
        value_type =  ConstvalueType::REAL;
        C_STRING = v;
    }
    void set_string(std::string v) {
        value_type =  ConstvalueType::STRING;
        C_STRING = v;
    }
    void set_bool(bool v) {
        value_type =  ConstvalueType::BOOLEAN;
        C_BOOLEAN = v;
    }
    void set_char(char v) {
        value_type =  ConstvalueType::CHAR;
        C_CHAR = v;
    }
    
    ConstvalueType type() { return value_type; }
    ConstValue &operator= (const ConstValue &cv){
        switch(cv.value_type){
            case ConstvalueType::INTEGER:
                value_type = cv.value_type;
                C_INT = cv.C_INT;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::REAL:
                value_type = cv.value_type;
                C_STRING = cv.C_STRING;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::BOOLEAN:
                value_type = cv.value_type;
                C_BOOLEAN = cv.C_BOOLEAN;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::CHAR:
                value_type = cv.value_type;
                C_CHAR = cv.C_CHAR;
                Is_Uminus = cv.Is_Uminus;
                break;
            case ConstvalueType::STRING:
                value_type = cv.value_type;
                C_STRING = cv.C_STRING;
                Is_Uminus = cv.Is_Uminus;
                break;
        }
        return *this;
    }
    void set_uminus(){ Is_Uminus = true; }
    bool get_uminus(){return Is_Uminus;}

private:
    ConstvalueType value_type;
    union {
        int C_INT;
        char C_CHAR;
        bool C_BOOLEAN;
    };
    std::string C_STRING;
    bool Is_Uminus = false;
};