#include "hawk.hpp"
#include <sys/resource.h>
#define advance() i++;curr_data=code[i]
#define bin_op(op_arg) i++;curr_data=code[i]; auto r1=m_memory[curr_data]; i++;curr_data=code[i]; auto r2=m_memory[curr_data]; i++;curr_data=code[i]; m_memory[curr_data]=r1 op_arg r2
#define unary_op(op_arg) i++;curr_data=code[i]; auto r1=m_memory[curr_data]; i++;curr_data=code[i];  m_memory[curr_data]= op_arg r1
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
    while (i<size){
        TYPE curr_data=code[i];
        opcode op=(opcode)curr_data.get_num();
        switch(op){
            case OP_LOAD:{
                //LOAD <data> <address>
                //Assign <data> to register <address>
                advance();
                TYPE value=curr_data;
                advance();
                m_memory[curr_data]=value;
                break;
            }
            case OP_MOV:{
                //MOV <address1> <address2>
                //Assign the value of register <address1> to register <address2>
                advance();
                TYPE value=m_memory[curr_data];
                advance();
                m_memory[curr_data]=value;
                break;
            }
            case OP_POP:{
                //POP <address>
                //delete the value <address>
                advance();
                m_memory[curr_data]=TYPE();
                break;
            }
            case OP_PRINT:{
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
                break;
            }
            case OP_ADD:{
                //ADD <address1> <address2> <address3>
                //Assign the value of <address1>+<address2> to <address3>
                bin_op(+);
                break;
            }
            case OP_SUB:{
                //SUB <address1> <address2> <address3>
                //Assign the value of <address1>-<address2> to <address3>
                bin_op(-);
                break;
            }
            case OP_NEG:{
                //NEG <address1> <address2>
                //Assign the value of -<address1> to <address2>
                unary_op(-);
                break;
            }
            case OP_MUL:{
                //MUL <address1> <address2> <address3>
                //Assign the value of <address1>*<address2> to <address3>
                bin_op(*);
                break;
            }
            case OP_DIV:{
                //DIV <address1> <address2> <address3>
                //Assign the value of <address1>/<address2> to <address3>
                bin_op(/);
                break;
            }
            case OP_MOD:{
                //MOD <address1> <address2> <address3>
                //Assign the value of <address1>%<address2> to <address3>
                bin_op(%);
                break;
            }
            case OP_BIT_XOR:{
                //BIT_XOR <address1> <address2> <address3>
                //Assign the value of <address1>^<address2> to <address3>
                bin_op(^);
                break;
            }
            case OP_EQ:{
                //EQ <address1> <address2> <address3>
                //Assign the value of <address1>==<address2> to <address3>
                bin_op(==);
                break;
            }
            case OP_NEQ:{
                //NEQ <address1> <address2> <address3>
                //Assign the value of <address1>!=<address2> to <address3>
                bin_op(!=);
                break;
            }
            case OP_LT:{
                //LT <address1> <address2> <address3>
                //Assign the value of <address1><<address2> to <address3>
                bin_op(<);
                break;
            }
            case OP_GT:{
                //GT <address1> <address2> <address3>
                //Assign the value of <address1>><address2> to <address3>
                bin_op(>);
                break;
            }
            case OP_LE:{
                //LE <address1> <address2> <address3>
                //Assign the value of <address1><=<address2> to <address3>
                bin_op(<=);
                break;
            }
            case OP_GE:{
                //GE <address1> <address2> <address3>
                //Assign the value of <address1>>=<address2> to <address3>
                bin_op(>=);
                break;
            }
            case OP_AND:{
                //AND <address1> <address2> <address3>
                //Assign the value of <address1>&&<address2> to <address3>
                bin_op(&&);
                break;
            }
            case OP_OR:{
                //OR <address1> <address2> <address3>
                //Assign the value of <address1>||<address2> to <address3>
                bin_op(||);
                break;
            }
            case OP_NOT:{
                //NOT <address1> <address2>
                //Assign the value of !<address1> to <address2>
                unary_op(!);
                break;
            }
            case OP_BIT_AND:{
                //BIT_AND <address1> <address2> <address3>
                //Assign the value of <address1>&<address2> to <address3>
                bin_op(&);
                break;
            }
            case OP_BIT_OR:{
                //BIT_OR <address1> <address2> <address3>
                //Assign the value of <address1>|<address2> to <address3>
                bin_op(|);
                break;
            }
            case OP_BIT_NOT:{
                //BIT_NOT <address1> <address2>
                //Assign the value of ~<address1> to <address2>
                unary_op(~);
                break;
            }
            case OP_SHL:{
                //BIT_SHL <address1> <address2> <address3>
                //Assign the value of <address1><<<address2> to <address3>
                bin_op(<<);
                break;
            }
            case OP_SHR:{
                //BIT_SHR <address1> <address2> <address3>
                //Assign the value of <address1>><address2> to <address3>
                bin_op(>>);
                break;
            }
            case OP_JMP:{
                //JMP <address>
                //Jump label <address> and execute it
                advance();
                execute(m_memory[curr_data].get_label());
                break;
            }
            case OP_RET:{
                //RET
                //Stop execution of a label or exit if at a global scope
                return;
            }
            case OP_EXIT:{
                //EXIT <address>
                //EXIT with error code at label <address>
                advance();
                exit(m_memory[curr_data].get_num());
                break;
            }
            case OP_IF:{
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
                break;
            }
            
            default:{
                std::cout<<"Unknown opcode: "<<op<<std::endl;
                exit(0);
                break;
            }
        }
        i++; 
    }
}
void VM::add_item(TYPE item){
    m_code.push_back(item);
}

void VM::add_item(std::vector<TYPE> item){
    m_code.push_back(item);
}
}