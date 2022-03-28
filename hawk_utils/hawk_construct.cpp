#include "../include/hawk_construct.hpp"

struct HawkOperation{
    HawkType left;
    HawkType right;
    opcode op;
    bool is_uni=false;
};