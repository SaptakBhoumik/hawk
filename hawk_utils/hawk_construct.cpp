#include "../include/hawk_construct.hpp"
#include <iostream>
namespace HAWK_VM{
std::vector<HawkType**> to_clean_up;
struct HawkOperation{
    HawkType left;
    HawkType right;
    opcode op;
    bool is_uni=false;
};
HawkType $(uint16_t number){
    HawkType reg;
    reg.type=TYPE_REGISTER;
    reg.number=number;
    return reg;
}
HawkType number(num number){
    HawkType reg;
    reg.type=TYPE_NUM;
    reg.number=number;
    return reg;
}
HawkType str(std::string string){
    HawkType reg;
    reg.type=TYPE_STR;
    reg.size=string.size();
    reg.ptr=(HawkType*)malloc(sizeof(HawkType)*reg.size);
    to_clean_up.push_back(&reg.ptr);
    for(int i=0;i<reg.size;i++){
        reg.ptr[i].type=TYPE_NUM;
        reg.ptr[i].number=string[i];
    }
    return reg;
}
HawkType array(std::vector<HawkType> array){
    HawkType reg;
    reg.type=TYPE_ARRAY;
    reg.size=array.size();
    reg.ptr=(HawkType*)malloc(sizeof(HawkType)*reg.size);
    to_clean_up.push_back(&reg.ptr);
    for(int i=0;i<reg.size;i++){
        reg.ptr[i]=array[i];
    }
    return reg;
}
HawkType array(std::vector<std::string> array){
    HawkType reg;
    reg.type=TYPE_ARRAY;
    reg.size=array.size();
    reg.ptr=(HawkType*)malloc(sizeof(HawkType)*reg.size);
    to_clean_up.push_back(&reg.ptr);
    for(int i=0;i<reg.size;i++){
        reg.ptr[i]=str(array[i]);
    }
    return reg;
}
HawkType array(std::vector<num> array){
    HawkType reg;
    reg.type=TYPE_ARRAY;
    reg.size=array.size();
    reg.ptr=(HawkType*)malloc(sizeof(HawkType)*reg.size);
    to_clean_up.push_back(&reg.ptr);
    for(int i=0;i<reg.size;i++){
        reg.ptr[i]=number(array[i]);
    }
    return reg;
}
HawkType label(std::vector<HawkType> label){
    HawkType reg;
    reg.type=TYPE_LABEL;
    reg.size=label.size();
    reg.ptr=(HawkType*)malloc(sizeof(HawkType)*reg.size);
    to_clean_up.push_back(&reg.ptr);
    for(int i=0;i<reg.size;i++){
        reg.ptr[i]=label[i];
    }
    return reg;
}
HawkOperation operator +(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_ADD;
    return op;
}
HawkOperation operator -(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_SUB;
    return op;
}
HawkOperation operator *(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_MUL;
    return op;
}
HawkOperation operator /(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_DIV;
    return op;
}
HawkOperation operator %(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_MOD;
    return op;
}
HawkOperation operator ^(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_BIT_XOR;
    return op;
}
HawkOperation operator &(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_BIT_AND;
    return op;
}
HawkOperation operator |(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_BIT_OR;
    return op;
}
HawkOperation operator <<(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_SHL;
    return op;
}
HawkOperation operator >>(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_SHR;
    return op;
}
HawkOperation operator ==(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_EQ;
    return op;
}
HawkOperation operator !=(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_NEQ;
    return op;
}
HawkOperation operator >(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_GT;
    return op;
}
HawkOperation operator <(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_LT;
    return op;
}
HawkOperation operator >=(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_GE;
    return op;
}
HawkOperation operator <=(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_LE;
    return op;
}
HawkOperation operator &&(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_AND;
    return op;
}
HawkOperation operator ||(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_OR;
    return op;
}
HawkOperation operator !(HawkType left){
    HawkOperation op;
    op.left=left;
    op.op=OP_NOT;
    return op;
}
HawkOperation operator -(HawkType left){
    HawkOperation op;
    op.left=left;
    op.op=OP_NEG;
    op.is_uni=true;
    return op;
}
HawkOperation operator ~(HawkType left){
    HawkOperation op;
    op.left=left;
    op.op=OP_BIT_NOT;
    op.is_uni=true;
    return op;
}
HawkOperation array_eq(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_EQ_ARRAY;
    return op;
}
HawkOperation append(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;    
    op.op=OP_APPEND;
    return op;
}
HawkOperation insert(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_INSERT;
    return op;
}
}