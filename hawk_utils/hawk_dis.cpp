#include "../include/hawk_dis.hpp"
#include <iostream>

namespace HAWK_VM{
HAWK_DIS::HAWK_DIS(HawkType* code){
    m_code=code;
}
std::string HAWK_DIS::disassemble(HawkType* code){
    m_code=code;
    return disassemble();
}
std::string HAWK_DIS::disassemble(){
    return disassemble("");
}
std::string HAWK_DIS::disassemble(std::string spacing){
    while(true){
        switch((opcode)m_code->number){
            default:{
                std::cout<<"Invalid opcode "<<(opcode)m_code->number<<std::endl;
                goto end;
            }
        }
        m_code++;
    }
    end:{}
    return m_result;
}
}