#ifndef MAIN__FVM__HPP
#define MAIN__FVM__HPP
#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <iostream>
namespace FVM{

/* Opcodes */
enum opcodes {
  OP_DEF,//default
  OP_BR,   /* branch */
  OP_ADD,  /* add  */
  OP_LD,   /* load */
  OP_ST,   /* store */
  OP_JSR,  /* jump register */
  OP_AND,  /* bitwise and */
  OP_LDR,  /* load register */
  OP_STR,  /* store register */
  OP_RTI,  /* unused */
  OP_NOT,  /* bitwise not */
  OP_LDI,  /* load indirect */
  OP_STI,  /* store indirect */
  OP_JMP,  /* jump */
  OP_RES,  /* reserved (unused) */
  OP_LEA,  /* load effective address */
  OP_TRAP, /* execute trap */
  OP_MOV,  /*Move a value to an register*/
  OP_EXIT  /*exit*/
};

class VM {
    size_t len=0;
    size_t curr_index=0;
    double code[UINT16_MAX];
    double op=OP_DEF;
    void advance();
    public:
    double memory[UINT16_MAX];
    VM();
    void execute();
    void add_item(double item);
};
}
#endif