#include "../include/hawk.hpp"
#include <stdio.h>
#include <stdlib.h>
#if defined _WIN32 || defined __CYGWIN__
#include <windows.h>
#else
#include <dlfcn.h>
#endif
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
            __execute(m_memory[(long long)code->number].array,m_memory);\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
            }\
        }\
        else{\
            if((opcode)(*(code+1)).number==OP_ELSE){\
                code++;\
                code++;\
                __execute(m_memory[(long long)code->number].array,m_memory);\
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

typedef struct HawkType HawkType;
typedef void (*ext_func)(HawkType ,HawkType*);
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
        else if(array2[i].type==TYPE_PTR){
            if(array1[i].PTR!=array2[i].PTR){
                res=0;
                break;
            }
            else{
                res=1;
            }
        }
        else if(TYPE_NONE==array2[i].type==array1[i].type){
            res=1;
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
inline char* to_str(HawkType item){
    char* res=malloc(sizeof(char)*(item.size+1));
    for(long long i=0;i<item.size;i++){
        if(item.array[i].type!=TYPE_NUM){break;}
        res[i]=item.array[i].number;
    }
    res[(long long)item.size]='\0';
    return res;
}
void __execute(HawkType* code,HawkType* m_memory){
    void* dispatch[]={
        insert(LOAD),
        insert(MOV),
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
        insert(MALLOC),
        insert(FREE),
        insert(REALOC),
        insert(LEN),
        insert(GETPTR),
        insert(LDPTR_VAL),
        insert(ASPTR_VAL),
        insert(AT),
        insert(CMALLOC),
        insert(CREALOC),
        insert(DL_OPEN),
        insert(DL_CLOSE),
        insert(DL_CALL),
    };
    goto *dispatch[(opcode)code->number];
    
    _OP_AT:{
        advance();
        HawkType r1=m_memory[(long long)code->number];
        advance();
        HawkType r2=m_memory[(long long)code->number];
        advance();
        m_memory[(long long)code->number]=r1.array[(long long)r2.number];
        DISPATCH();
    }
    _OP_ASPTR_VAL:{
        advance();
        HawkType* ptr=m_memory[(long long)code->number].PTR;
        advance();
        *ptr=m_memory[(long long)code->number];
        DISPATCH();
    }
    _OP_LDPTR_VAL:{
        advance();
        HawkType* ptr=m_memory[(long long)code->number].PTR;
        advance();
        m_memory[(long long)code->number]=*ptr;
        DISPATCH();
    }
    _OP_GETPTR:{
        advance();
        num index=m_memory[(long long)code->number].number;
        advance();
        m_memory[(long long)code->number].PTR=&m_memory[(long long)index];
        DISPATCH();
    }
    _OP_LEN:{
        advance();
        HawkType array=m_memory[(long long)code->number];
        advance();
        m_memory[(long long)code->number]=(HawkType){.type=TYPE_NUM,.number=array.size};
        DISPATCH();
    }
    _OP_FREE:{
        advance();
        free(m_memory[(long long)code->number].array);
        m_memory[(long long)code->number].array=NULL;
        m_memory[(long long)code->number].size=0;
        DISPATCH();        
    }
    _OP_MALLOC:{
        advance();
        num size=m_memory[(long long)code->number].number;
        advance();
        m_memory[(long long)code->number].array=malloc(size);
        DISPATCH();
    }
    _OP_REALOC:{
        advance();
        num size=m_memory[(long long)code->number].number;
        advance();
        m_memory[(long long)code->number].array=realloc(m_memory[(long long)code->number].array,size);
        DISPATCH();
    }
    _OP_CMALLOC:{
        advance();
        num size=code->number;
        advance();
        m_memory[(long long)code->number].array=malloc(size);
        DISPATCH();
    }
    _OP_CREALOC:{
        advance();
        num size=code->number;
        advance();
        m_memory[(long long)code->number].array=realloc(m_memory[(long long)code->number].array,size);
        DISPATCH();
    }
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
            __execute(m_memory[(long long)code->number].array,m_memory);
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
                __execute(m_memory[(long long)code->number].array,m_memory);
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
        __execute(m_memory[(long long)code->number].array,m_memory);
        DISPATCH();
    }

    _OP_DL_OPEN:{
        advance();
        HawkType r1=m_memory[(long long)code->number];
        char* r1_str=to_str(r1);
        advance();
        #if defined _WIN32 || defined __CYGWIN__
        m_memory[(long long)code->number].so = LoadLibrary(r1_str);   
        #else
        m_memory[(long long)code->number].so = dlopen(r1_str, RTLD_NOW);   
        #endif  
        free(r1_str);
        r1_str=NULL;
        DISPATCH();
    }  
    _OP_DL_CLOSE:{
        advance();
        #if defined _WIN32 || defined __CYGWIN__
        FreeLibrary(m_memory[(long long)code->number].so);   
        #else
        dlclose(m_memory[(long long)code->number].so); 
        #endif    
        DISPATCH();
    }
    _OP_DL_CALL:{
        advance();
        char* r1=to_str(m_memory[(long long)code->number]);
        advance();
        #if defined _WIN32 || defined __CYGWIN__
        ext_func func = GetProcAddress(m_memory[(long long)code->number].so, r1);
        #else
        ext_func func = dlsym(m_memory[(long long)code->number].so, r1);
        #endif
        free(r1);
        r1=NULL;
        advance();
        (*func)(m_memory[(long long)code->number],m_memory);
        DISPATCH();
    }
    _OP_RET:{
        return;
    }
}