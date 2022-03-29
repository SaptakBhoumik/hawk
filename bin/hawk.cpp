#include "../include/hawk_file.hpp"
#include "../include/hawk_dis.hpp"
#include "../include/hawk.hpp"
#include <iostream>
#include <string>
#include <sys/resource.h>
using namespace HAWK_VM;
int main(int argc,char* argv[]){
    struct rlimit R;
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);
    if(argc!=3){
        std::cout<<"Expected 2 arguments but got "<<argc<<" argument instead"<<"\n";
        std::cout<<"Usage: "<<argv[0]<<" <mode> <file>"<<"\n";
        std::cout<<"Mode:\n  '-dis' - to disassemble\n  '-run' - to execute"<<"\n";
        return 1;
    }
    auto s1=std::string(argv[1]);
    auto s2=std::string(argv[2]);
    HAWK_FILE f2(s2);
    auto codes=f2.read();
    HawkType* m_memory=(HawkType*)malloc(MAX_LIMIT*sizeof(HawkType));
    auto x= HAWK(codes,m_memory);
    auto y=HAWK_DIS(codes);
    if(s1=="-dis"){
        y.disassemble();
    }
    else if(s1=="-run"){
        x.execute();
    }
    else{
        std::cout<<"Unknown mode: "<<s1<<"\n";
        std::cout<<"Usage: "<<argv[0]<<" <mode> <file>"<<"\n";
        std::cout<<"Mode:\n  '-dis' - to disassemble\n  '-run' - to execute"<<"\n";
        return 1;
    }
    f2.clean_up();
    free(m_memory);
    m_memory=NULL;
    return 0;
}