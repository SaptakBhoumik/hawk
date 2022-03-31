#ifndef CONSTRUCT__HAWK__H
#define CONSTRUCT__HAWK__H
#include "hawk.hpp"
#include <dlfcn.h>
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
HawkOperation operator &(HawkType);//TODO:
HawkOperation operator *(HawkType);//TODO:
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
    public:
    HAWK_CONSTRUCT();
    void clean_up();
    void operation(HawkType,HawkOperation);
    void operation(HawkOperation,HawkType);
    void load(HawkType,HawkType);
    void mov(HawkType,HawkType);
    void jmp(HawkType);
    void ret();
    void if_branch(HawkType,HawkType);
    void if_branch(HawkOperation,HawkType);
    void else_branch(HawkType);
    void free(HawkType);
    void dlclose(HawkType);
    void pop(HawkType);
    void clear_up();
    void dlcall(HawkType,HawkType,HawkType);
};
}
#endif