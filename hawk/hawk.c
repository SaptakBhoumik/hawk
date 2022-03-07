#include "hawk.h"
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
            execute(m_memory[(long long)code->number].label,m_memory);\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
            }\
        }\
        else{\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
                execute(m_memory[(long long)code->number].label,m_memory);\
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
#define PREPARE(name,size){\
                    code->number=(num)&&_OP_#name;\
                    code+=size;\
                    goto *dispatch[(opcode)code->number];\
                    }
void execute(HawkType* code,HawkType* m_memory){
    void* dispatch[]={
        &&_OP_LOAD,
        &&_OP_MOV,
        &&_OP_POP,
        &&_OP_PRINT_INT,
        &&_OP_ADD,
        &&_OP_SUB,
        &&_OP_NEG,
        &&_OP_MUL,
        &&_OP_DIV,
        &&_OP_MOD,
        &&_OP_BIT_XOR,
        &&_OP_EQ,
        &&_OP_NEQ,
        &&_OP_LT,
        &&_OP_GT,
        &&_OP_LE,
        &&_OP_GE,
        &&_OP_AND,
        &&_OP_OR,
        &&_OP_NOT,
        &&_OP_BIT_AND,
        &&_OP_BIT_OR,
        &&_OP_BIT_NOT,
        &&_OP_SHL,
        &&_OP_SHR,
        &&_OP_JMP,
        &&_OP_RET,
        &&_OP_EXIT,
        &&_OP_IF,
        &&_OP_ELSE,
        &&_OP_IF_NEQ,
        &&_OP_IF_EQ,
        &&_OP_IF_LT,
        &&_OP_IF_GT,
        &&_OP_IF_LE,
        &&_OP_IF_GE,
        &&_OP_IF_AND,
        &&_OP_IF_OR,
    };
    goto *dispatch[(opcode)code->number];
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
            execute(m_memory[(long long)code->number].label,m_memory);
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
                execute(m_memory[(long long)code->number].label,m_memory);
            }
        }
        DISPATCH();
    }
    _OP_RET:{
        return;
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
    _OP_PRINT_INT:{
        //PRINT <address>
        //print the value <address>
        advance();
        HawkType data=m_memory[(long long)code->number];
        printf("%f\n",data.number);
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
        execute(m_memory[(long long)code->number].label,m_memory);
        DISPATCH();
    }
}