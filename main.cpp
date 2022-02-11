
#include "hawk/hawk.hpp"
#include <sys/resource.h>
int main(){
    rlimit R;
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);
    using namespace HAWK;
    VM vm;
    vm.add_item(OP_LOAD);
    vm.add_item(10);
    vm.add_item(0);
    vm.add_item(OP_LOAD);
    vm.add_item({OP_PRINT,1});
    vm.add_item(1);
    vm.add_item(OP_PRINT);
    vm.add_item(0);
    vm.add_item(OP_JMP);
    vm.add_item(1);
    vm.add_item(OP_PRINT);
    vm.add_item(0);
    vm.add_item(END);
    vm.execute();
    return 0;
}