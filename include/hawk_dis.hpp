#ifndef HAWK__DIS__H
#define HAWK__DIS__H
#include "hawk.hpp"
#include <fstream>
#include <string>
#include <vector>
namespace HAWK_VM{
class HAWK_DIS{
    std::string m_result="";
    std::string disassemble(std::string);
    HawkType* m_code=nullptr;
    public:
    HAWK_DIS()=default;
    HAWK_DIS(HawkType*);
    std::string disassemble();
    std::string disassemble(HawkType*);
};
}
#endif