#ifndef __DYNINSN_HH__
#define __DYNINSN_HH__ 

#include "../Common/Common.hh"

namespace Emulator
{

struct Exception_t
{
    bool    valid;
    xlen_t  Cause;
    xlen_t  Tval;
};

struct Prediction_t
{
    bool    Taken;
    xlen_t  Target;
};

enum funcType_t {
    ALU , MUL , DIV, BRU, CSR, LDU, STU, FPU
};


#define BRU_JAR         0
#define BRU_JALR        1
#define BRU_BEQ         2
#define BRU_BNE         3
#define BRU_BLT         4
#define BRU_BGE         5
#define BRU_BLTU        6
#define BRU_BGEU        7    

#define CSR_CSRRW       0
#define CSR_CSRRS       1
#define CSR_CSRRC       2
#define CSR_CSRR        3
#define CSR_FENCEI      4
#define CSR_ECALL       5
#define CSR_EBREAK      6
#define CSR_MRET        7
#define CSR_SRET        8
#define CSR_FENCE       9

#define LDU_LB          0
#define LDU_LH          1
#define LDU_LW          2
#define LDU_LD          3
#define LDU_LBU         4
#define LDU_LHU         5
#define LDU_LWU         6

#define STU_SB          0
#define STU_SH          1
#define STU_SW          2
#define STU_SD          3

#define ALU_ADD         0
#define ALU_SUB         1
#define ALU_SLL         2
#define ALU_SLT         3
#define ALU_SLTU        4   
#define ALU_XOR         5
#define ALU_SRL         6
#define ALU_SRA         7
#define ALU_OR          8
#define ALU_AND         9

#define ALU_ADDW        10
#define ALU_SUBW        11
#define ALU_SLLW        12
#define ALU_SRLW        13
#define ALU_SRAW        14


#define MUL_MUL         0
#define MUL_MULH        1
#define MUL_MULHSU      2
#define MUL_MULHU       3

#define MUL_MULW        4

#define DIV_DIV         0
#define DIV_DIVU        1
#define DIV_REM         2
#define DIV_REMU        3

#define DIV_DIVW        4
#define DIV_DIVUW       5
#define DIV_REMW        6
#define DIV_REMUW       7


enum InsnState_t{
    State_Fetch1, State_Fetch2, State_Decode, State_Dispatch, 
    State_Issue,State_ReadOperand,State_Execute,State_WriteBack, State_Commit, State_Done
};

enum RegType_t{
    NONE, INT
};

enum AguType_t{
    Gen_Addr,Gen_Data,Gen_Both
};

struct DynInsn
{
    InsnState_t  State;

    Addr_t       Pc;
    uint64_t     RobTag;
    uint64_t     LSQTag;

    funcType_t   Fu;
    uint8_t      SubOp;

    //bool         IsRvcInsn;
    Insn_t       CompressedInsn;
    Insn_t       UncompressedInsn;

    bool         ControlFlowInsn;
    //本身的ISA寄存器
    IsaRegId_t   IsaRs1;
    IsaRegId_t   IsaRs2;
    IsaRegId_t   IsaRd;
    //数据类型
    RegType_t    Rs1Type;
    RegType_t    Rs2Type;
    RegType_t    RdType;
    //对应的物理寄存器
    PhyRegId_t   PhyRs1;
    PhyRegId_t   PhyRs2;
    PhyRegId_t   PhyRd;
    PhyRegId_t   LPhyRd;//依赖的前面指令的rd对应的物理寄存器

    bool         Operand1Ready;
    bool         Operand2Ready;

    xReg_t       Operand1;
    xReg_t       Operand2;
    xReg_t       RdResult;

    /* AGU Information */
    Addr_t       Agu_addr;//保存load/store指令要访问的地址
    bool         Agu_addr_ready;
    xReg_t       Agu_data;//保存store指令要存入的数据
    bool         Agu_data_ready;

    bool         BruMisPred;
    Addr_t       BruTarget;//实际的应该跳转的分支预测的地址

    Imm_t        imm;

    Exception_t  Excp;
    Prediction_t Pred;//保存了预测的分支地址以及是否采用分支预测
};

} // namespace Emulator


#endif	