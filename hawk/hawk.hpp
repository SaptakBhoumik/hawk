#ifndef MAIN__HAWK__HPP
#define MAIN__HAWK__HPP
#include <vector>
#include <iostream>
#include <string>
namespace HAWK{
typedef long double num;
enum curr_type{
    TYPE_NONE=0,
    TYPE_NUM=1,
    TYPE_LABEL=2,
    TYPE_STR=3
};
class TYPE{
    num m_number=0;
    std::string m_str;
    std::vector<TYPE> m_label;
    curr_type m_type=TYPE_NONE;
    public:
    //constructors
    TYPE();
    TYPE(num);
    TYPE(std::string);
    TYPE(std::vector<TYPE>);
    //get value
    curr_type get_type();
    num get_num();
    std::string get_str();
    std::vector<TYPE> get_label();
    //operators
    TYPE operator+(TYPE);
    TYPE operator-(TYPE);
    TYPE operator-();
    TYPE operator*(TYPE);
    TYPE operator/(TYPE);
    TYPE operator%(TYPE);
    TYPE operator^(TYPE);
    TYPE operator==(TYPE);
    TYPE operator!=(TYPE);
    TYPE operator<(TYPE);
    TYPE operator>(TYPE);
    TYPE operator<=(TYPE);
    TYPE operator>=(TYPE);
    TYPE operator&&(TYPE);
    TYPE operator||(TYPE);
    TYPE operator!();
    TYPE operator&(TYPE);
    TYPE operator|(TYPE);
    TYPE operator~();
    TYPE operator<<(TYPE);
    TYPE operator>>(TYPE); 
};
class memory{
    TYPE m_mem[UINT16_MAX];
    public:
    memory()=default;
    TYPE& operator[](TYPE i){
        return m_mem[(uint64_t)i.get_num()];
    }
    memory operator=(memory)=delete;
};
typedef enum {
    OP_NONE,
    OP_LOAD,
    OP_MOV,
    OP_POP,
    OP_PRINT,
    OP_ADD,
    OP_SUB,
    OP_NEG,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_BIT_XOR,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_BIT_AND,
    OP_BIT_OR,
    OP_BIT_NOT,
    OP_SHL,
    OP_SHR,
    OP_JMP,
    OP_RET,
    OP_EXIT,
    OP_IF,
    OP_ELSE
}opcode;
class VM {
    public:
    std::vector<TYPE> m_code;
    VM();
    VM(std::vector<TYPE> code);
    memory m_memory;
    void execute(std::vector<TYPE> code);
    void execute();
    void add_item(std::vector<TYPE> item);
    void add_item(TYPE item);
};
}
#endif