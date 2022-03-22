#ifndef MAIN__HAWK__H
#define MAIN__HAWK__H
#if defined(__cplusplus)
extern "C" {
#endif
typedef double num;
#define MAX_LIMIT 65535
enum curr_type{
    TYPE_NONE,
    TYPE_NUM,
    TYPE_LABEL,
    TYPE_ARRAY,
    TYPE_PTR,
    TYPE_OP
};

struct HawkType{
    enum curr_type type;
    union{
        num number;
        void *so;
        struct HawkType* PTR;
        struct{ 
            struct HawkType* array;
            num size;
        };
    };
};
typedef enum {
    OP_LOAD,
    OP_MOV,
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
    OP_EQ_ARRAY,
    OP_INSERT,
    OP_APPEND,
    OP_MALLOC,
    OP_FREE,
    OP_REALOC,
    OP_LEN,
    OP_GETPTR,
    OP_LDPTR_VAL,
    OP_ASPTR_VAL,
    OP_AT,
    OP_CMALLOC,
    OP_CREALOC,
    OP_DL_OPEN,
    OP_DL_CLOSE,
    OP_DL_CALL,
}opcode;
#if defined(__cplusplus)
};
namespace HAWK_VM {
class HAWK{
    HawkType* m_code=nullptr,*m_memory=nullptr;
    public:
        HAWK() noexcept;
        HAWK(HawkType* code,HawkType* memory) noexcept;
        void execute() noexcept;
        void execute(HawkType* code,HawkType* memory) noexcept;
};
}
#endif
#endif