#ifndef HAWK__DIS__H
#define HAWK__DIS__H
#include "hawk.hpp"
#include <string>
#include <vector>
namespace HAWK_VM{
class HAWK_DIS{
    void disassemble(HawkType*,std::string);
    HawkType* m_code=nullptr;
    public:
    HAWK_DIS()=default;
    HAWK_DIS(HawkType*);
    void disassemble();
    void disassemble(HawkType*);
};
}
#endif