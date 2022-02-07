#ifndef MAIN__FVM__HPP
#define MAIN__FVM__HPP
#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
namespace FVM{
typedef long double num;
enum curr_type{
    TYPE_NONE,
    TYPE_NUM,
    TYPE_LABEL,
    TYPE_STR
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

class VM {
    size_t curr_index=0;
    std::vector<TYPE> code;
    TYPE op=TYPE();
    public:
    VM();
    void write(std::string filename);
    void input(std::string filename);
    void advance();
    TYPE memory[UINT16_MAX];
    void execute();
    void add_item(TYPE item);
};
}
#endif