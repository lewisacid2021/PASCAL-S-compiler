#ifndef PASCC_TYPE_H_
#define PASCC_TYPE_H_

#include <string.h>

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

class TypeTemplate {
public:
    enum class TYPE { BASIC, RECORD, ARRAY };
    TypeTemplate() {}
    TypeTemplate(TYPE template_type) : template_type_(template_type) {}
    virtual ~TypeTemplate() {}
    template <typename T>
    T *DynamicCast() {
        return dynamic_cast<T *>(this);
    }

    TYPE template_type() { return template_type_; }
    virtual std::string name() = 0;
    bool StringLike();  // check if stringlike (array of char)

protected:
    TYPE template_type_;
};

/**
 * @brief basic type, including INT, REAL, CHAR, BOOL
 */
class BasicType : public TypeTemplate {
public:
    enum class BASIC_TYPE { INTEGER, REAL, BOOLEAN, CHAR};

    BasicType() : TypeTemplate(TYPE::BASIC), basic_type_(BASIC_TYPE::NONE) {}
    BasicType(BASIC_TYPE basic_type)
        : TypeTemplate(TYPE::BASIC), basic_type_(basic_type) {}

    ~BasicType() {}

    // getter and setter
    BASIC_TYPE type() { return basic_type_; }
    std::string c_name() {
        switch (basic_type_) {
        case BASIC_TYPE::INT:
            return "int";
        case BASIC_TYPE::REAL:
            return "float";
        case BASIC_TYPE::BOOL:
            return "int";
        case BASIC_TYPE::CHAR:
            return "char";
        default:
            return "void";
        }
    }
    std::string name() override;

private:
    BASIC_TYPE basic_type_;
};

class ConstValue {
    public:
    ConstValue() {}
    ~ConstValue() {}
    ConstValue(const ConstValue &other);
    ConstValue(int v, bool to_float = false) {
        if (to_float)
        set((float)v);
        else
        set(v);
    }
    ConstValue(float v) { set(v); }
    ConstValue(bool v) { set(v); }
    ConstValue(char v) { set(v); }
    ConstValue(const char *v) { set(std::string(v)); }
    ConstValue(std::string v) { set(v); }

    void set(int v) {
        m_Type = TYPE_INT;
        m_INT = v;
    }
    void set(float v) {
        m_Type = TYPE_REAL;
        m_REAL = v;
    }
    void set(bool v) {
        m_Type = TYPE_BOOL;
        m_BOOLEAN = v;
    }
    void set(char v) {
        m_Type = TYPE_CHAR;
        m_CHAR = v;
    }
    void set(std::string v) {
        m_Type = TYPE_STRINGLIKE;
        m_STRING = v;
    }
    void set_unimus();

    BasicType *type() { return m_Type; }

    // get by type
    template <typename T>
    T get() {
        if (std::is_same<T, int>::value)
        return *(T *)(&m_INT);
        else if (std::is_same<T, char>::value)
        return *(T *)(&m_CHAR);
        else if (std::is_same<T, float>::value)
        return *(T *)(&m_REAL);
        else if (std::is_same<T, bool>::value)
        return *(T *)(&m_BOOLEAN);
        else if (std::is_same<T, std::string>::value)
        return *((T *)(&m_STRING));
        else {
        throw std::runtime_error("ConstValue : get() : type " +
                                std::string(typeid(T).name()) +
                                " not supported");
        }
    }
    // copy by =
    ConstValue &operator=(const ConstValue &other);
    // operation +
    ConstValue operator+(const ConstValue &other);
    // operation -
    ConstValue operator-(const ConstValue &other);
    // operation *
    ConstValue operator*(const ConstValue &other);
    // operation /
    ConstValue operator/(const ConstValue &other);

    private:
    BasicType *m_Type = nullptr;
    union {
        int m_INT;
        float m_REAL;
        char m_CHAR;
        bool m_BOOLEAN;
    };
    std::string m_STRING;
};


#endif