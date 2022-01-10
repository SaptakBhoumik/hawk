#ifndef MAIN__FVM__HPP
#define MAIN__FVM__HPP
#include <stdint.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

enum resister {
  R_R0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC, /* program counter */
  R_COND,
  R_COUNT
};
/* Opcodes */
enum opcodes {
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
  OP_EXIT  /*exit*/
};
enum condition {
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};
class VM {
  uint32_t memory[UINT32_MAX];
  uint16_t reg[R_COUNT];
  uint16_t mem_read(uint16_t address);
  uint16_t check_key();

public:
  void execute();
};
#endif