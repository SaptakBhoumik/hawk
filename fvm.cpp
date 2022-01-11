#include "fvm.hpp"
#define bin_op(op_arg) {advance();auto r1=(size_t)op;advance();auto r2=(size_t)op;advance();memory[(size_t)op]=memory[r1]+memory[r2];}
namespace FVM{
VM::VM(){}
void VM::execute(){
    op=code[0];
    while(true){
        if (op==OP_MOV){
            //mov <value> <register>
            advance();
            auto value=op;
            advance();
            memory[(size_t)op]=value;
        }
        else if (op==OP_ADD){
            //ADD <register1> <register2> <register>
            bin_op(+)
        }
        else if ((len-1)>curr_index){printf("Invalid optcode %f at %ld\n",op,curr_index+1);exit(1);}
        if((len-1)<=curr_index){break;}
        advance();
    }
}
void VM::add_item(double item){
    code[len]=item;
    len++;
}
void VM::advance(){
    curr_index++;
    op=code[curr_index];
}

}
int main(){
    using namespace FVM;
    auto x=VM();
    x.add_item(OP_MOV);
    x.add_item(3);
    x.add_item(1);
    x.add_item(OP_MOV);
    x.add_item(4);
    x.add_item(2);
    x.add_item(OP_ADD);
    x.add_item(1);
    x.add_item(2);
    x.add_item(3);
    // x.add_item(7);
    x.execute();
    std::cout<<x.memory[3];
    return 0;
}