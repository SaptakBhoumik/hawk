#ifndef HAWK__FILE__H
#define HAWK__FILE__H
#include "hawk.hpp"
#include <fstream>
#include <string>
namespace HAWK_VM{
class HAWK_FILE{
    std::string m_filename="";
    HawkType* m_code=nullptr;
    size_t m_size=0;
    std::ofstream m_output_file;
    std::ifstream m_read_file;
    void write(HawkType*,size_t);
    void read(HawkType*,size_t);
    public:
    HAWK_FILE()=default;
    HAWK_FILE(HawkType*,size_t,std::string);
    HAWK_FILE(std::string);
    void write(HawkType*,size_t,std::string);
    void write();
    HawkType* read(std::string);
    HawkType* read();
};
}
#endif