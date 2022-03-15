#ifndef MAIN__HAWK__H
#define MAIN__HAWK__H
#if defined(__cplusplus)
extern "C" {
#endif
typedef double num;
#define MAX_LIMIT 65535
enum curr_type{
    TYPE_NONE=0,
    TYPE_NUM=1,
    TYPE_LABEL=2,
    TYPE_STR=3
};

struct _HawkType{
    enum curr_type type;
    num number;
    void* jmp_loc;
    struct _HawkType* label;
};
typedef struct _HawkType HawkType; 
typedef enum {
    OP_LOAD,
    OP_MOV,
    OP_POP,
    OP_PRINT_INT,
    OP_ADD,
    OP_SUB,
    OP_NEG,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_BIT_XOR,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_BIT_AND,
    OP_BIT_OR,
    OP_BIT_NOT,
    OP_SHL,
    OP_SHR,
    OP_JMP,
    OP_RET,
    OP_EXIT,
    OP_IF,
    OP_ELSE,
    OP_IF_NEQ,
    OP_IF_EQ,
    OP_IF_LT,
    OP_IF_GT,
    OP_IF_LE,
    OP_IF_GE,
    OP_IF_AND,
    OP_IF_OR,
}opcode;
#if defined(__cplusplus)
};
namespace HAWK_VM {
class HAWK{
    HawkType* m_code=nullptr,*m_memory=nullptr;
    public:
        HAWK();
        HAWK(HawkType* code,HawkType* memory);
        void execute();
        void execute(HawkType* code,HawkType* memory);
};
}
#endif
#endif