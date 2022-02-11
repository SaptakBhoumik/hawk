#include "hawk.hpp"
#define advance() i++;curr_data=code[i]
#define bin_op(op_arg) i++;curr_data=code[i]; auto r1=m_memory[curr_data]; i++;curr_data=code[i]; auto r2=m_memory[curr_data]; i++;curr_data=code[i]; m_memory[curr_data]=r1 op_arg r2
#define unary_op(op_arg) i++;curr_data=code[i]; auto r1=m_memory[curr_data]; i++;curr_data=code[i];  m_memory[curr_data]= op_arg r1
#define DISPATCH()  if(i<size){i++;curr_data=code[i];op=(opcode)curr_data.get_num();goto *dispatch[op];}else{return;}

namespace HAWK{
VM::VM(){}
VM::VM(std::vector<TYPE> code){
    m_code=code;
}
void VM::execute(){
    execute(m_code);
}
void VM::execute(std::vector<TYPE> code){
    size_t size=code.size();
    size_t i=0;
    TYPE curr_data=code[i];
    opcode op=(opcode)curr_data.get_num();
    void* dispatch[END+1]={
        &&_OP_LOAD,
        &&_OP_MOV,
        &&_OP_POP,
        &&_OP_PRINT,
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
    };
        
    goto *dispatch[op];
    _OP_LOAD:{
        //LOAD <data> <address>
        //Assign <data> to register <address>
        advance();
        TYPE value=curr_data;
        advance();
        m_memory[curr_data]=value;
        DISPATCH();
    }
    _OP_MOV:{
        //MOV <address1> <address2>
        //Assign the value of register <address1> to register <address2>
        advance();
        TYPE value=m_memory[curr_data];
        advance();
        m_memory[curr_data]=value;
        DISPATCH();
    }
    _OP_POP:{
        //POP <address>
        //delete the value <address>
        advance();
        m_memory[curr_data]=TYPE();
        DISPATCH();
    }
    _OP_PRINT:{
        //PRINT <address>
        //print the value of register <address>
        advance();
        TYPE& value=m_memory[curr_data];
        auto val_type=value.get_type();
        if(val_type==TYPE_NUM){
            std::cout<<value.get_num()<<"\n";
        }
        else if(val_type==TYPE_STR){
            std::cout<<value.get_str()<<"\n";
        }
        else if(val_type==TYPE_NONE){
            std::cout<<"NULL"<<"\n";
        }
        else{
            std::cout<<"OBJECT<"<<&value<<">"<<"\n";
        }
        DISPATCH();
    }
    _OP_ADD:{
        //ADD <address1> <address2> <address3>
        //Assign the value of <address1>+<address2> to <address3>
        bin_op(+);
        DISPATCH();
    }
    _OP_SUB:{
        //SUB <address1> <address2> <address3>
        //Assign the value of <address1>-<address2> to <address3>
        bin_op(-);
        DISPATCH();
    }
    _OP_NEG:{
        //NEG <address1> <address2>
        //Assign the value of -<address1> to <address2>
        unary_op(-);
        DISPATCH();
    }
    _OP_MUL:{
        //MUL <address1> <address2> <address3>
        //Assign the value of <address1>*<address2> to <address3>
        bin_op(*);
        DISPATCH();
    }
    _OP_DIV:{
        //DIV <address1> <address2> <address3>
        //Assign the value of <address1>/<address2> to <address3>
        bin_op(/);
        DISPATCH();
    }
    _OP_MOD:{
        //MOD <address1> <address2> <address3>
        //Assign the value of <address1>%<address2> to <address3>
        bin_op(%);
        DISPATCH();
    }
    _OP_BIT_XOR:{
        //BIT_XOR <address1> <address2> <address3>
        //Assign the value of <address1>^<address2> to <address3>
        bin_op(^);
        DISPATCH();
    }
    _OP_EQ:{
        //EQ <address1> <address2> <address3>
        //Assign the value of <address1>==<address2> to <address3>
        bin_op(==);
        DISPATCH();
        
    }
    _OP_NEQ:{
        //NEQ <address1> <address2> <address3>
        //Assign the value of <address1>!=<address2> to <address3>
        bin_op(!=);
        DISPATCH();
        
    }
    _OP_LT:{
        //LT <address1> <address2> <address3>
        //Assign the value of <address1><<address2> to <address3>
        bin_op(<);
        DISPATCH();
        
    }
    _OP_GT:{
        //GT <address1> <address2> <address3>
        //Assign the value of <address1>><address2> to <address3>
        bin_op(>);
        DISPATCH();
    }
    _OP_LE:{
        //LE <address1> <address2> <address3>
        //Assign the value of <address1><=<address2> to <address3>
        bin_op(<=);
        DISPATCH();
        
    }
    _OP_GE:{
        //GE <address1> <address2> <address3>
        //Assign the value of <address1>>=<address2> to <address3>
        bin_op(>=);
        DISPATCH();       
    }
    _OP_AND:{
        //AND <address1> <address2> <address3>
        //Assign the value of <address1>&&<address2> to <address3>
        bin_op(&&);
        DISPATCH();
        
    }
    _OP_OR:{
        //OR <address1> <address2> <address3>
        //Assign the value of <address1>||<address2> to <address3>
        bin_op(||);
        DISPATCH();
        
    }
    _OP_NOT:{
        //NOT <address1> <address2>
        //Assign the value of !<address1> to <address2>
        unary_op(!); 
        DISPATCH();   
    }
    _OP_BIT_AND:{
        //BIT_AND <address1> <address2> <address3>
        //Assign the value of <address1>&<address2> to <address3>
                bin_op(&);
    DISPATCH();
    }
    _OP_BIT_OR:{
        //BIT_OR <address1> <address2> <address3>
        //Assign the value of <address1>|<address2> to <address3>
        bin_op(|);
        DISPATCH();
        
    }
    _OP_BIT_NOT:{
        //BIT_NOT <address1> <address2>
        //Assign the value of ~<address1> to <address2>
        unary_op(~);
        DISPATCH();
        
    }
    _OP_SHL:{
        //BIT_SHL <address1> <address2> <address3>
        //Assign the value of <address1><<<address2> to <address3>
        bin_op(<<);
        DISPATCH();
        
    }
    _OP_SHR:{
        //BIT_SHR <address1> <address2> <address3>
        //Assign the value of <address1>><address2> to <address3>
        bin_op(>>);
        DISPATCH();
        
    }
    _OP_JMP:{
        //JMP <address>
        //Jump label <address> and execute it
        advance();
        execute(m_memory[curr_data].get_label());
        DISPATCH();
        
    }
    _OP_RET:{
        //RET
        //Stop execution of a label or exit if at a global scope
        return;
    }
    _OP_EXIT:{
        //EXIT <address>
        //EXIT with error code at label <address>
        advance();
        exit(m_memory[curr_data].get_num());    
    }
    _OP_IF:{
        //IF <address1> <address2>
        //If <address1> is true, jump to label <address2>
        advance();
        if((bool)m_memory[curr_data].get_num()==true){
            advance();
            execute(m_memory[curr_data].get_label());
            if(i<size-1){
                if((opcode)code[i+1].get_num()==OP_ELSE){
                    advance();
                    advance();
                }
            }
        }
        else{
            advance();
            if(i<size-1){
               if((opcode)code[i+1].get_num()==OP_ELSE){
                    advance();
                    advance();
                    execute(m_memory[curr_data].get_label());
                }
            }
        }
        DISPATCH();
    }
}
void VM::add_item(TYPE item){
    m_code.push_back(item);
}

void VM::add_item(std::vector<TYPE> item){
    m_code.push_back(item);
}
}