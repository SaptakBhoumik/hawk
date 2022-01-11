#ifndef MAIN__FVM__HPP
#define MAIN__FVM__HPP
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <unistd.h>
#include <vector>
#include <iostream>
namespace FVM{

/* Opcodes */
enum opcodes {
  OP_DEF,//default
  OP_ADD,  /* add  */
  OP_SUB,  /* subtract  */
  OP_DIV,  /* divide  */
  OP_MUL,  /* multiply  */
  OP_MOV,  /*Move a value to an register*/
  OP_EXIT,  /*exit*/
  OP_HAULT  /*hault*/
};

class VM {
    size_t len=0;
    size_t curr_index=0;
    double code[UINT16_MAX];
    double op=OP_DEF;
    public:
    void advance();
    double memory[UINT16_MAX];
    VM();
    void execute();
    void add_item(double item);
};
}
#endif