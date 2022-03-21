#include "hawk.hpp"
#include <stdio.h>
#include <stdlib.h>
#define bin_op(op_arg)  {\
                    code++;\
                    num r1=m_memory[(long long)code->number].number;\
                    code++;\
                    num r2=m_memory[(long long)code->number].number;\
                    code++;\
                    m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=r1 op_arg r2};\
                    }

#define if_bin_op(curr_operator)code++;\
        HawkType r1=m_memory[(long long)code->number];\
        code++;\
        HawkType r2=m_memory[(long long)code->number];\
        code++;\
        if((int)(r1.number curr_operator r2.number)){\
            __execute(m_memory[(long long)code->number].label,m_memory);\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
            }\
        }\
        else{\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
                __execute(m_memory[(long long)code->number].label,m_memory);\
            }\
        }

#define unary_op(op_arg) code++;\
                        num r1=m_memory[(long long)code->number].number;\
                        code++;\
                        m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=op_arg r1};

#define unary_int_op(op_arg) code++;\
                        long long r1=(long long)m_memory[(long long)code->number].number;\
                        code++;\
                        m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=op_arg r1};


#define bin_int_op(op_arg)  {\
                    code++;\
                    long long r1=(long long)m_memory[(long long)code->number].number;\
                    code++;\
                    long long r2=(long long)m_memory[(long long)code->number].number;\
                    code++;\
                    m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=r1 op_arg r2};\
                    }

#define advance() code++;
#define DISPATCH()  {\
                    code++;\
                    goto *dispatch[(opcode)code->number];\
                    }
#define insert(op) [OP_##op] = &&_OP_##op

int equality_array(HawkType* array1,num size1,HawkType* array2,num size){
    int res=0;
    for(long long i=0;i<size1;i++){
        if(array2[i].type==TYPE_ARRAY){
           res=equality_array(array1[i].array,array1[i].size,array2[i].array,array2[i].size);
           if(!res){
                res = 0;
                break;
           } 
        }
        else if(array1[i].number!=array2[i].number){
            res=0;
            break;
        }
        else{
            res=1;
        }
    }
    return res;
}

void __execute(HawkType* code,HawkType* m_memory){
    void* dispatch[]={
        insert(LOAD),
        insert(MOV),
        insert(POP),
        insert(ADD),
        insert(SUB),
        insert(NEG),
        insert(MUL),
        insert(DIV),
        insert(MOD),
        insert(BIT_XOR),
        insert(EQ),
        insert(NEQ),
        insert(LT),
        insert(GT),
        insert(LE),
        insert(GE),
        insert(AND),
        insert(OR),
        insert(NOT),
        insert(BIT_AND),
        insert(BIT_OR),
        insert(BIT_NOT),
        insert(SHL),
        insert(SHR),
        insert(JMP),
        insert(RET),
        insert(EXIT),
        insert(IF),
        insert(ELSE),
        insert(IF_NEQ),
        insert(IF_EQ),
        insert(IF_LT),
        insert(IF_GT),
        insert(IF_LE),
        insert(IF_GE),
        insert(IF_AND),
        insert(IF_OR),
        insert(EQ_ARRAY),
        insert(INSERT),
        insert(APPEND),
    };
    goto *dispatch[(opcode)code->number];
    _OP_INSERT:{
        advance();
        HawkType r1=m_memory[(long long)code->number];
        advance();
        HawkType r2=m_memory[(long long)code->number];
        advance();
        m_memory[(long long)code->number].array[(long long)r2.number]=r1;
        DISPATCH();
    }
    _OP_APPEND:{
        advance();
        HawkType r1=m_memory[(long long)code->number];
        advance();
        HawkType* arr=&m_memory[(long long)code->number];
        arr->array[(long long)arr->size]=r1;
        arr->size++;
        DISPATCH();
    }
    _OP_EQ_ARRAY:{
        advance();
        HawkType* array1=m_memory[(long long)code->number].array;
        num size1=m_memory[(long long)code->number].size;
        advance();
        HawkType* array2=m_memory[(long long)code->number].array;
        num size2=m_memory[(long long)code->number].size;
        advance();
        int res=0;
        if(size1==size2){
            res=equality_array(array1,size1,array2,size2);
        }
        m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=res};
        DISPATCH();
    }
    _OP_IF_NEQ:{
        if_bin_op(!=);
        DISPATCH();
    }
    _OP_IF_EQ:{
        if_bin_op(==);
        DISPATCH();
    }
    _OP_IF_LT:{
        if_bin_op(<);
        DISPATCH();
    }
    _OP_IF_GT:{
        if_bin_op(>);
        DISPATCH();
    }
    _OP_IF_LE:{
        if_bin_op(<=);
        DISPATCH();
    }
    _OP_IF_GE:{
        if_bin_op(>=);
        DISPATCH();
    }
    _OP_IF_AND:{
        if_bin_op(&&);
        DISPATCH();
    }
    _OP_IF_OR:{
        if_bin_op(||);
        DISPATCH();
    }
    
    _OP_IF:{
        //IF <address1> <address2>
        //If <address1> is true, jump to label <address2>
        advance();
        if((int)m_memory[(long long)code->number].number){
            advance();
            __execute(m_memory[(long long)code->number].label,m_memory);
            if((opcode)(*(code+1)).number==OP_ELSE){
                advance();
                advance();
            }
        }
        else{
            advance();
            if((opcode)(*(code+1)).number==OP_ELSE){
                advance();
                advance();
                __execute(m_memory[(long long)code->number].label,m_memory);
            }
        }
        DISPATCH();
    }
    
    _OP_ELSE:{
        printf("Error: else without a previous if op\n");
        exit(1);
    }
    _OP_EXIT:{
        advance();
        exit(m_memory[(long)code->number].number);  
    }
    
    _OP_LOAD:{
        //LOAD <data> <address>
        //Assign <data> to register <address>
        advance();
        HawkType value=(*code);
        advance();
        m_memory[(long long)code->number]=value;
        DISPATCH();
    }
    _OP_MOV:{
        //MOV <address> <address>
        //Assign register <address> to register <address>
        advance();
        HawkType address=(*code);
        advance();
        m_memory[(long long)address.number]=m_memory[(long long)code->number];
        DISPATCH();
    }    
    _OP_POP:{
        //POP <address>
        //delete the value <address>
        advance();
        m_memory[(long long)code->number]=(HawkType){.type=TYPE_NONE,.number=0};
        DISPATCH();
    }
    _OP_ADD:{
        //ADD <address> <address> <address>
        //Assign <address> to <address> + <address>
        bin_op(+);
        DISPATCH();
    }
    _OP_SUB:{
        //SUB <address> <address> <address>
        //Assign <address> to <address> - <address>
        bin_op(-);
        DISPATCH();
    }
    _OP_MUL:{
        //MUL <address> <address> <address>
        //Assign <address> to <address> * <address>
        bin_op(*);
        DISPATCH();
    }
    _OP_DIV:{
        //DIV <address> <address> <address>
        //Assign <address> to <address> / <address>
        bin_op(/);
        DISPATCH();
    }
    _OP_MOD:{
        //MOD <address> <address> <address>
        //Assign <address> to <address> % <address>
        bin_int_op(%);
        DISPATCH();
    }
    _OP_BIT_XOR:{
        //BIT_XOR <address> <address> <address>
        //Assign <address> to <address> ^ <address>
        bin_int_op(^);
        DISPATCH();
    }
    _OP_EQ:{
        //EQ <address> <address> <address>
        //Assign <address> to 1 if <address> == <address>
        bin_op(==);
        DISPATCH();
    }
    _OP_NEQ:{
        //NEQ <address> <address> <address>
        //Assign <address> to 1 if <address> != <address>
        bin_op(!=);
        DISPATCH();
    }
    _OP_LT:{
        //LT <address> <address> <address>
        //Assign <address> to 1 if <address> < <address>
        bin_op(<);
        DISPATCH();
    }
    _OP_GT:{
        //GT <address> <address> <address>
        //Assign <address> to 1 if <address> > <address>
        bin_op(>);
        DISPATCH();
    }
    _OP_LE:{
        //LE <address> <address> <address>
        //Assign <address> to 1 if <address> <= <address>
        bin_op(<=);
        DISPATCH();
    }
    _OP_GE:{
        //GE <address> <address> <address>
        //Assign <address> to 1 if <address> >= <address>
        bin_op(>=);
        DISPATCH();
    }
    _OP_AND:{
        //AND <address> <address> <address>
        //Assign <address> to 1 if <address> && <address>
        bin_op(&&);
        DISPATCH();
    }
    _OP_OR:{
        //OR <address> <address> <address>
        //Assign <address> to 1 if <address> || <address>
        bin_op(||);
        DISPATCH();
    }
    
    _OP_BIT_AND:{
        //BIT_AND <address> <address> <address>
        //Assign <address> to <address> & <address>
        bin_int_op(&);
        DISPATCH();
    }
    _OP_BIT_OR:{
        //BIT_OR <address> <address> <address>
        //Assign <address> to <address> | <address>
        bin_int_op(|);
        DISPATCH();
    }
    
    _OP_SHL:{
        //SHL <address> <address> <address>
        //Assign <address> to <address> << <address>
        bin_int_op(<<);
        DISPATCH();
    }
    _OP_SHR:{
        //SHR <address> <address> <address>
        //Assign <address> to <address> >> <address>
        bin_int_op(>>);
        DISPATCH();
    }
    _OP_NEG:{
        //NEG <address> <address>
        //Assign <address> to -<address>
        unary_op(-);
        DISPATCH();
    }
    _OP_NOT:{
        //NOT <address> <address>
        //Assign <address> to !<address>
        unary_op(!);
        DISPATCH();
    }
    _OP_BIT_NOT:{
        //BIT_NOT <address> <address>
        //Assign <address> to ~<address>
        unary_int_op(~);
        DISPATCH();
    }
    _OP_JMP:{
        //JMP <address>
        //Jump to <address>
        advance();
        __execute(m_memory[(long long)code->number].label,m_memory);
        DISPATCH();
    }
    _OP_RET:{
        return;
    }
}