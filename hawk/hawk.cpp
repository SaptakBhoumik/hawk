#include "hawk.hpp"
extern "C" void __execute(HawkType* code,HawkType* m_memory);
namespace HAWK_VM {
HAWK::HAWK(){
    m_code=nullptr;
    m_memory=nullptr;

}
HAWK::HAWK(HawkType* code,HawkType* memory){
    m_code=code;
    m_memory=memory;
}
void HAWK::execute(){
    __execute(m_code,m_memory);
}
void HAWK::execute(HawkType* code,HawkType* memory){
    __execute(code,memory);
}
}