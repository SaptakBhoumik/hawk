#include "fvm.hpp"
namespace FVM{
VM::VM(){}
void VM::execute(){
    op=code[curr_index];
}
void VM::add_item(TYPE item){
    code.push_back(item);
}
void VM::advance(){
    curr_index++;
    op=code[curr_index];
}
void VM::write(std::string filename){
    
}
void VM::input(std::string filename){ 
	
}
}
int main(){
    
    return 0;
}