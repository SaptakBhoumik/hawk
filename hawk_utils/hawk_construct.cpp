#include "../include/hawk_construct.hpp"
#include <iostream>
namespace HAWK_VM{
std::vector<HawkType**> to_clean_up;

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
HawkType get_op(opcode op){
    HawkType reg;
    reg.type=TYPE_OP;
    reg.number=op;
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
HawkOperation ptr(HawkType left,HawkType right){
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
HawkOperation operator &(HawkType left){
    HawkOperation op;
    op.left=left;
    op.op=OP_GETPTR;
    op.is_uni=true;
    return op;
}
HawkOperation operator *(HawkType left){
    HawkOperation op;
    op.left=left;
    op.op=OP_LDPTR_VAL;
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
HawkOperation at(HawkType left,HawkType right){
    HawkOperation op;
    op.left=left;
    op.right=right;
    op.op=OP_AT;
    return op;
}
HawkOperation allocate(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;
    op.op=OP_MALLOC;
    return op;
}
HawkOperation reallocate(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;
    op.op=OP_REALLOC;
    return op;
}
HawkOperation len(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;
    op.op=OP_LEN;
    return op;
}
HawkOperation dlopen(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;
    op.op=OP_DL_OPEN;
    return op;
}
HawkOperation back(HawkType left){
    HawkOperation op;
    op.left=left;
    op.is_uni=true;
    op.op=OP_BACK;
    return op;
}
HawkType* HAWK_CONSTRUCT::get_code(){
    m_code.push_back(get_op(OP_RET));
    code=(HawkType*)malloc(sizeof(HawkType)*m_code.size());
    for(int i=0;i<m_code.size();i++){
        code[i]=m_code[i];
    }
    return code;
}
size_t HAWK_CONSTRUCT::get_code_size(){
    return m_code.size();
}
void HAWK_CONSTRUCT::clean_up(){
    m_code.clear();
    if(code!=NULL){
        for(auto&i:to_clean_up){
            if((*i)!=NULL) {
                free(*i);
                *i=NULL;
            }
        }
        free(code);
        code=NULL;
    }
}
void HAWK_CONSTRUCT::load_ptr_val(HawkType reg1,HawkType reg2){
    m_code.push_back(get_op(OP_LDPTR_VAL));
    m_code.push_back(reg1);
    m_code.push_back(reg2);
}
void HAWK_CONSTRUCT::operation(HawkType reg,HawkOperation op){
    m_code.push_back(get_op(op.op));
    m_code.push_back(op.left);
    if(op.is_uni!=true){
        m_code.push_back(op.right);
    }
    m_code.push_back(reg);
}
void HAWK_CONSTRUCT::load(HawkType reg,HawkType value){
    m_code.push_back(get_op(OP_LOAD));
    m_code.push_back(value);
    m_code.push_back(reg);
}
void HAWK_CONSTRUCT::mov(HawkType reg1,HawkType reg2){
    m_code.push_back(get_op(OP_MOV));
    m_code.push_back(reg1);
    m_code.push_back(reg2);
}
void HAWK_CONSTRUCT::jmp(HawkType loc){
    m_code.push_back(get_op(OP_JMP));
    m_code.push_back(loc);
}
void HAWK_CONSTRUCT::ret(){
    m_code.push_back(get_op(OP_RET));
}
void HAWK_CONSTRUCT::jmp_if(HawkType reg,HawkType loc){
    m_code.push_back(get_op(OP_IF));
    m_code.push_back(reg);
    m_code.push_back(loc);
}
void HAWK_CONSTRUCT::jmp_else(HawkType loc){
    m_code.push_back(get_op(OP_ELSE));
    m_code.push_back(loc);
}
void HAWK_CONSTRUCT::destroy(HawkType loc){
    m_code.push_back(get_op(OP_FREE));
    m_code.push_back(loc);
}
void HAWK_CONSTRUCT::dlclose(HawkType reg){
    m_code.push_back(get_op(OP_DL_CLOSE));
    m_code.push_back(reg);
}
void HAWK_CONSTRUCT::pop(HawkType reg){
    m_code.push_back(get_op(OP_POP));
    m_code.push_back(reg);
}
void HAWK_CONSTRUCT::dlcall(HawkType r1,HawkType r2,HawkType r3){
    m_code.push_back(get_op(OP_DL_CALL));
    m_code.push_back(r1);
    m_code.push_back(r2);
    m_code.push_back(r3);
}
void HAWK_CONSTRUCT::jmp_if(HawkOperation op,HawkType reg){
    switch (op.op){
        case OP_NEQ:{
            m_code.push_back(get_op(OP_IF_NEQ));
            break;
        }
        case OP_EQ:{
            m_code.push_back(get_op(OP_IF_EQ));
            break;
        }
        case OP_LT:{
            m_code.push_back(get_op(OP_IF_LT));
            break;
        }
        case OP_GT:{
            m_code.push_back(get_op(OP_IF_GT));
            break;
        }
        case OP_LE:{
            m_code.push_back(get_op(OP_IF_LE));
            break;
        }
        case OP_GE:{
            m_code.push_back(get_op(OP_IF_GE));
            break;
        }
        case OP_AND:{
            m_code.push_back(get_op(OP_IF_AND));
            break;
        }
        case OP_OR:{
            m_code.push_back(get_op(OP_IF_OR));
            break;
        }
        default:{
            std::cout << "Opcode " <<op.op << "cant be in a if branch"<< std::endl;
        }
    }
    m_code.push_back(op.left);
    m_code.push_back(op.right);
    m_code.push_back(reg);
}
}