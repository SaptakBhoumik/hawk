#include "../include/hawk_construct.hpp"
namespace HAWK_VM{
struct HawkOperation{
    HawkType left;
    HawkType right;
    opcode op;
    bool is_uni=false;
};
}