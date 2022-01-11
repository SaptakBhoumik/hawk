#include "fvm.hpp"
#define bin_op(op_arg) advance();auto r1=(size_t)op;advance();auto r2=(size_t)op;advance();memory[(size_t)op]=memory[r1] op_arg memory[r2];
namespace FVM{
VM::VM(){}
void VM::execute(){
    op=code[curr_index];
    while(true){
        if (op==OP_MOV){
            //mov <value> <register>
            advance();
            auto value=op;
            advance();
            memory[(size_t)op]=value;
        }
        else if (op==OP_ADD){
            //add <register1> <register2> <register>
            bin_op(+)
        }
        else if (op==OP_SUB){
            //sub <register1> <register2> <register>
            bin_op(-)
        }
        else if (op==OP_DIV){
            //div <register1> <register2> <register>
            bin_op(/)
        }
        else if (op==OP_MUL){
            //mul <register1> <register2> <register>
            bin_op(*)
        }
        else if (op==OP_EXIT){
            //exit <register>
            advance();
            exit(memory[(size_t)op]);
        }
        else if (op==OP_HAULT){
            //htl
            return;
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
    assert(x.memory[3]==7);
    x.advance();
    x.add_item(OP_SUB);
    x.add_item(1);
    x.add_item(2);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==-1);
    x.advance();
    x.add_item(OP_DIV);
    x.add_item(1);
    x.add_item(2);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==0.75);
    x.advance();
    x.add_item(OP_MUL);
    x.add_item(1);
    x.add_item(2);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==12);
    std::cout<<x.memory[3]<<"\n";
    x.advance();
    // x.add_item(OP_EXIT);
    // x.add_item(3);
    x.add_item(OP_HAULT);
    x.execute();

    return 0;
}