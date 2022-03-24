#include "../include/hawk_dis.hpp"
#include <iostream>
#define advance() code++;
#define op_print(text) std::cout<<"\e[1m\e[91m"<<text<<"\e[0m\e[0m";
#define reg_print(text) std::cout<<"\e[94m$"<<text<<"\e[0m";
#define num_print(text) std::cout<<"\e[36m"<<text<<"\e[0m";
#define comment_print(text) std::cout<<"\e[90m"<<text<<"\e[0m";
#define bin_op(text,op) {\
                        op_print(text);\
                        std::cout<<" ";\
                        code++;\
                        auto r1=*code;\
                        code++;\
                        auto r2=*code;\
                        code++;\
                        auto r3=*code;\
                        reg_print(r1.number)\
                        std::cout<<" ";\
                        reg_print(r2.number)\
                        std::cout<<" ";\
                        reg_print(r3.number)\
                        std::cout<<"\t";\
                        comment_print(";$"<<r3.number<<"=$"<<r1.number<<op<<r2.number<<"\n");\
                        }
        
namespace HAWK_VM{
void print_array(HawkType* arr,size_t size,bool is_comment=false){
    std::cout<<"[";
    for(size_t i=0;i<size;++i){
        if(arr[i].type==TYPE_NUM){
            if(is_comment){
                comment_print(arr[i].number);
            }
            else{
                num_print(arr[i].number);
            }
        }
        else if(arr[i].type==TYPE_ARRAY){
            print_array(arr[i].array,arr[i].size,is_comment);
        }
        else if(arr[i].type==TYPE_PTR){
            if(is_comment){
                comment_print(arr[i].PTR);
            }
            else{
                num_print(arr[i].PTR);
            }
        }
        if(i<size-1){
            std::cout<<",";
        }
    }
    std::cout<<"]";
}
HAWK_DIS::HAWK_DIS(HawkType* code){
    m_code=code;
}
void HAWK_DIS::disassemble(HawkType* code){
    m_code=code;
    return disassemble();
}
void HAWK_DIS::disassemble(){
    disassemble(m_code,"");
}
void HAWK_DIS::disassemble(HawkType* code,std::string spacing){
    while(true){
        std::cout<<spacing;
        switch((opcode)code->number){
            case OP_LOAD:{
                if((code+1)->type!=TYPE_LABEL){
                    op_print("load");
                    std::cout<<" ";
                }
                else{
                    std::cout<<"label ";
                    reg_print((code+2)->number);
                }
                advance(); 
                auto val=*code;       
                if(code->type==TYPE_NUM){
                    num_print(code->number);
                }
                else if(code->type==TYPE_ARRAY){
                    print_array(code->array,code->size);
                }
                else if(code->type==TYPE_PTR){
                    num_print(code->PTR);
                }
                else if(code->type==TYPE_LABEL){
                    std::cout<<":\n";
                    disassemble(code->array,spacing+"  ");
                }
                advance();
                std::cout<<" ";
                auto reg=*code;
                reg_print(code->number);
                if(val.type!=TYPE_LABEL){
                    std::cout<<"\t";
                    comment_print(";$"<<reg.number<<"=");
                    if(val.type==TYPE_NUM){
                        comment_print(val.number);
                    }
                    else if(val.type==TYPE_ARRAY){
                        print_array(val.array,val.size,true);
                    }
                    else if(val.type==TYPE_PTR){
                        comment_print(val.PTR);
                    }
                }
                std::cout<<"\n";
                break;
            }
            case OP_MOV:{
                op_print("mov");
                std::cout<<" ";
                advance();
                auto r1=*code;
                reg_print(code->number);
                std::cout<<" ";
                advance();
                auto r2=*code;
                reg_print(code->number);
                std::cout<<"\t";
                comment_print(";$"<<r2.number<<"=$"<<r1.number<<"\n");
                break;
            }
            case OP_RET:{
                op_print("ret");
                std::cout<<"\n";
                goto end;
            }
            case OP_ADD:{
                bin_op("add ","+");
                break;
            }
            case OP_SUB:{
                bin_op("add ","+");
                break;
            }
            case OP_MUL:{
                bin_op("mul ","*");
                break;
            }
            case OP_DIV:{
                bin_op("div ","/");
                break;
            }
            case OP_MOD:{
                bin_op("mod ","%");
                break;
            }
            case OP_BIT_XOR:{
                bin_op("bit_xor","^");
                break;
            }
            case OP_EQ:{
                bin_op("eq ","==");
                break;
            }
            case OP_NEQ:{
                bin_op("neq ","!=");
                break;
            }
            case OP_LT:{
                bin_op("lt ","<");
                break;
            }
            case OP_GT:{
                bin_op("gt ",">");
                break;
            }
            case OP_LE:{
                bin_op("le ","<=");
                break;
            }
            case OP_GE:{
                bin_op("ge ",">=");
                break;
            }
            case OP_AND:{
                bin_op("and ","&&");
                break;
            }
            case OP_OR:{
                bin_op("or ","||");
                break;
            }
            case OP_BIT_AND:{
                bin_op("bit_and","&");
                break;
            }
            case OP_BIT_OR:{
                bin_op("bit_or","|");
                break;
            }
            case OP_SHL:{
                bin_op("shl ","<<");
                break;
            }
            case OP_SHR:{
                bin_op("shr ",">>");
                break;
            }
            case OP_IF:{
                op_print("if");
                std::cout<<" ";
                advance();
                auto r1=*code;
                reg_print(code->number);
                std::cout<<" ";
                advance();
                auto r2=*code;
                reg_print(code->number);
                std::cout<<" ";
                std::cout<<"\t";
                comment_print(";if($"<<r1.number<<"):jmp $"<<r2.number);
                std::cout<<"\n";
                break;
            }
            // default:{
            //     std::cout<<"Invalid opcode "<<(opcode)code->number<<std::endl;
            //     exit(1);
            // }
        }
        code++;
    }
    end:{}
}
}