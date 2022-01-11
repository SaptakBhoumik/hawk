#ifndef MAIN__FVM__HPP
#define MAIN__FVM__HPP
#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>
namespace FVM{
typedef long double num;
/* Opcodes */
enum opcodes {
  OP_DEF,//default
  //Operations with number//
  OP_NEG,
  OP_ADD,  /* add  */
  OP_SUB,  /* subtract  */
  OP_DIV,  /* divide  */
  OP_MUL,  /* multiply  */
  //********************//
  OP_MOV,  /*Move a value to an register*/
  OP_POP,  //Assign the register to 0
  OP_EXIT,  /*exit*/
  OP_HAULT  /*hault*/
};

class VM {
    size_t curr_index=0;
    std::vector<num> code;
    num op=OP_DEF;
    public:
    VM();
    void write(std::string filename);
    void input(std::string filename);
    void advance();
    num memory[UINT16_MAX];
    void execute();
    void add_item(num item);
};
}
#endif