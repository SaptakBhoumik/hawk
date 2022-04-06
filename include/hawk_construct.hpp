#ifndef CONSTRUCT__HAWK__H
#define CONSTRUCT__HAWK__H
#include "hawk.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#define $ _reg
namespace HAWK_VM{  
struct HawkOperation;
HawkType $(uint16_t);
HawkType str(std::string);
HawkType number(num);
HawkType array(std::vector<HawkType>);
HawkType array(std::vector<std::string>);
HawkType array(std::vector<num>);
HawkType label(std::vector<HawkType>);
HawkOperation operator +(HawkType, HawkType);//OP_ADD
HawkOperation operator -(HawkType);//OP_NEG
HawkOperation operator -(HawkType, HawkType);//OP_SUB
HawkOperation operator *(HawkType, HawkType);//OP_MUL
HawkOperation operator /(HawkType, HawkType);//OP_DIV
HawkOperation operator %(HawkType, HawkType);//OP_MOD
HawkOperation operator ^(HawkType, HawkType);//OP_BIT_XOR
HawkOperation operator ==(HawkType, HawkType);//OP_EQ
HawkOperation operator !=(HawkType, HawkType);//OP_NEQ
HawkOperation operator <(HawkType, HawkType);//OP_LT
HawkOperation operator >(HawkType, HawkType);//OP_GT
HawkOperation operator <=(HawkType, HawkType);//OP_LE
HawkOperation operator >=(HawkType, HawkType);//OP_GE
HawkOperation operator &&(HawkType, HawkType);//OP_AND
HawkOperation operator ||(HawkType, HawkType);//OP_OR
HawkOperation operator !(HawkType);//OP_NOT
HawkOperation operator &(HawkType, HawkType);//OP_BIT_AND
HawkOperation operator |(HawkType, HawkType);//OP_BIT_OR
HawkOperation operator ~(HawkType);//OP_BIT_NOT
HawkOperation operator <<(HawkType, HawkType);//OP_SHL
HawkOperation operator >>(HawkType, HawkType);//OP_SHR
HawkOperation ptr(HawkType);
HawkOperation operator *(HawkType);
HawkOperation array_eq(HawkType);
HawkOperation append(HawkType);
HawkOperation insert(HawkType,HawkType);
HawkOperation at(HawkType,HawkType);
HawkOperation allocate(HawkType);
HawkOperation reallocate(HawkType);
HawkOperation len(HawkType);
HawkOperation dlopen(HawkType);
HawkOperation back(HawkType);
class HAWK_CONSTRUCT{
    HawkType* code=nullptr;
    std::vector<HawkType> m_code;
    public:
    HAWK_CONSTRUCT()=default;
    HawkType* get_code();
    size_t get_code_size();
    void clean_up();
    void operation(HawkType,HawkOperation);
    void load_ptr_val(HawkType,HawkType);
    void load(HawkType,HawkType);
    void mov(HawkType,HawkType);
    void jmp(HawkType);
    void ret();
    void jmp_if(HawkType,HawkType);
    void jmp_if(HawkOperation,HawkType);
    void jmp_else(HawkType);
    void destroy(HawkType);
    void dlclose(HawkType);
    void pop(HawkType);
    void dlcall(HawkType,HawkType,HawkType);
};
struct HawkOperation{
    HawkType left;
    HawkType right;
    opcode op;
    bool is_uni=false;
};
}
#endif