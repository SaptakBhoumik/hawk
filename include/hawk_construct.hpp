#ifndef CONSTRUCT__HAWK__H
#define CONSTRUCT__HAWK__H
#include "hawk.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#define $ _hawktype_init
namespace HAWK_VM{  
struct HawkOperation;
HawkType $();
HawkType $(num);
HawkType str(std::string);
HawkType number(num);
HawkType array(HawkType, num);
HawkType array(std::vector<HawkType>);
HawkType func(HawkType, num);
HawkType func(std::vector<HawkType>);
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
HawkOperation jmp(HawkType);//OP_JMP
HawkOperation ret();//OP_RET

}
#endif