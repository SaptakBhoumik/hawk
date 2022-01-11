#include "fvm.hpp"
#define bin_op(op_arg,T1,T2) advance();auto r1=(size_t)op;advance();auto r2=(size_t)op;advance();memory[(size_t)op]=(T1)memory[r1] op_arg (T2)memory[r2];
#define uranary_op(op_arg,T1) advance();auto r1=(size_t)op;advance();memory[(size_t)op]=op_arg (T1)memory[r1];
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
            bin_op(+,num,num)
        }
        else if (op==OP_SUB){
            //sub <register1> <register2> <register>
            bin_op(-,num,num)
        }
        else if (op==OP_DIV){
            //div <register1> <register2> <register>
            bin_op(/,num,num)
        }
        else if (op==OP_MUL){
            //mul <register1> <register2> <register>
            bin_op(*,num,num)
        }
        else if (op==OP_MOD){
            //mod <register1> <register2> <register>
            bin_op(%,int64_t,int64_t)
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
        else if (op==OP_NEG){
            //neg <register1> <register>
            uranary_op(-,num)
        }
        else if (op==OP_POP){
            //pop <register>
            advance();
            memory[(size_t)op]=0;
        }
        else if ((code.size()-1)>curr_index){printf("Invalid optcode %Lf at %ld\n",op,curr_index+1);exit(1);}
        if((code.size()-1)<=curr_index){break;}
        advance();
    }
}
void VM::add_item(num item){
    code.push_back(item);
}
void VM::advance(){
    curr_index++;
    op=code[curr_index];
}
void VM::write(std::string filename){
    std::ofstream out(filename, std::ios::binary);
    for(size_t i=0;i<code.size();++i){
            out.write(reinterpret_cast<char*>(&code[i]),sizeof(num));
    }
    out.close();
}
void VM::input(std::string filename){ 
	std::ifstream r(filename, std::ios::binary);
	num i=0;
	while (r.read((char*)&i, sizeof(num))) {
		code.push_back((num)i);
	}
    r.close();
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
    x.advance();
    x.add_item(OP_POP);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==0);
    x.advance();
    x.add_item(OP_NEG);
    x.add_item(1);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==-3);
    x.advance();
    x.add_item(OP_MOD);
    x.add_item(2);
    x.add_item(1);
    x.add_item(3);
    x.execute();
    assert(x.memory[3]==1);
    std::cout<<x.memory[3]<<"\n";
    // x.advance();
    // x.add_item(OP_EXIT);
    // x.add_item(3);
    // x.add_item(OP_HAULT);
    // x.execute();
    x.write("data.bin");
    auto y=VM();
    y.input("data.bin");
    y.execute();
    std::cout<<y.memory[3]<<"\n";
    return 0;
}