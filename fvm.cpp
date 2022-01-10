#include "fvm.hpp"
#define PC_START 0x3000
#define MR_KBSR  0xFE00
#define MR_KBDR 0xFE02
inline uint32_t sign_extend(uint32_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}
uint16_t VM::check_key() {
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  return select(1, &readfds, NULL, NULL, &timeout) != 0;
}
uint16_t VM::mem_read(uint16_t address) {
  if (address == MR_KBSR) {
    if (check_key()) {
      memory[MR_KBSR] = (1 << 15);
      memory[MR_KBDR] = getchar();
    } else {
      memory[MR_KBSR] = 0;
    }
  }
  return memory[address];
}
void VM::execute(){
    reg[R_COND] = FL_ZRO;
    reg[R_PC] = PC_START;
    while (true){
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;
        switch(op){
            case OP_ADD:{}
            default:{}
        }
    }
}
int main(){
    return 0;
}