#include "hawk.hpp"
extern "C" void __execute(HawkType* code,HawkType* m_memory) noexcept;
namespace HAWK_VM {
HAWK::HAWK() noexcept{
    m_code=nullptr;
    m_memory=nullptr;

}
HAWK::HAWK(HawkType* code,HawkType* memory) noexcept{
    m_code=code;
    m_memory=memory;
}
void HAWK::execute() noexcept{
    __execute(m_code,m_memory);
}
void HAWK::execute(HawkType* code,HawkType* memory) noexcept{
    __execute(code,memory);
}
}