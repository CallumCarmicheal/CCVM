#pragma once
#include "../stdafx.h"
#include <vector>

typedef int instr_t;
typedef std::vector<instr_t> instr_a;

/**
* CAT  OPCODE      INSTR           pc+1        pc+2        DESCRIPTION
* ----------------------------------------------------------------------------------------------------------------------------
* integer:
* |    0x00000001  iadd                                    integer add,                      sp-1 +  sp
* |    0x00000002  isub                                    integer subtract,                 sp-1 -  sp
* |    0x00000003  imul                                    integer multiply,                 sp-1 *  sp
* |    0x00000004  idiv                                    integer divide,                   sp-1 /  sp
* |    0x00000005  ilt                                     integer less than,                sp-1 <  sp
* |    0x00000006  ilteq                                   integer less than or equal to,    sp-1 <= sp
* |    0x00000007  imt                                     integer more than,                sp-1 >  sp
* |    0x00000008  imteq                                   integer more than or equal to,    sp-1 >= sp
* |    0x00000009  ieq                                     integer equal to,                 sp-1 == sp
* |    0x0000000A  iinc                                    increment integer at the top of the stack
* |    0x0000000B  idec                                    decrement integer at the top of the stack
* |    0x0000000C  iconst          value                   push integer constant to the top of the stack
* /
*
* branch:
* |    0x00000010  br              addr                    branch to address
* |    0x00000011  brt             addr                    branch if true
* |    0x00000012  brf             addr                    branch if false
* |    0x00000013  brs                                     branch to address on stack
* |    0x00000014  brts                                    branch to address on stack (sp-1) if true
* |    0x00000015  brfs                                    brnach to address on stack (sp-1) if false
* /
*
* memory/stack:
* |    0x00000020  load            addr                    load local variable, relative to framepointer
* |    0x00000021  loadr           addr                    load relative stack data,        stack[sp++] = stack[sp-addr]
* |    0x00000022  gload           addr                    load global variable, load from memory
* |    0x00000023  store           addr                    store local variable, relative to framepointer
* |    0x00000024  gstore          addr                    store global variable, store in memory
* |    0x00000025  gstores         addr        len         store string in global memory from stack
* |    0x00000026  gloads          addr        len         load string from global memory to stack
* |    0x00000027  loadp           addr                    load a parameter from call, loads parameter from frame pointer
* |    0x00000028  pop                                     pop the top of the stack
* /
*
* operations:
* |    0x00000040  halt
* |    0x00000041  call            addr        noArgs      call addr, expect noArgs, after ret params are popped
* |    0x00000042  callv           addr        noArgs      call addr, expect noArgs, do NOT pop params of stack!
* |    0x00000043  ret                                     return from a function with the top of the stack as result, return val;
* |    0x00000044  retn                                    return from a function with no result, EG: return;
* /
*
* system:
* | Print Integer:
* |    0x00000050  sysprinti                               print the value on the top of the stack, values popped of the stack
* |    0x00000051  sysprintil                              print the value on the top of the stack, values left on the stack
* |
* | Print Character:
* |    0x00000052  sysprintc                               print the value on the stack as a character, values popped of stack
* |    0x00000053  sysprintcl                              print the value on the stack as a character, values left on stack
* |
* | Print String:
* |    0x00000054  sysprints       strCnt                  print the values on the stack as a string len of strCnt, values popped of stack
* |    0x00000055  sysprintsl      strCnt                  print the values on the stack as a string len of strCnt, values left on stack
* |    0x00000056  sysprintsz                              print as string until \0, values popped of stack
* |    0x00000057  sysprintszl                             print as string until \0, values left on stack
* |    0x00000058  sysprintsm      addr        len         print string from memory at addr for len count
* |    0x00000059  sysprintszm     addr                    print string from memory at addr until null terminated \0
* |
* | Print New Line:
* |    0x0000005A  sysprintnl                              print a newline character
* |    0x0000005B  sysprintnlc     nlCount                 print multiple new line characters (nlCount)
* | 
* | Misc:
* |    0x0000005C  dbgtraces       above       below       print the stack by above and below.
* |    0x0000005D  dbgtracei       above       below       print the instructions above and below
* |    0x0000005E  slp             amt                     sleep for amt milliseconds
* |    0x0000005F  syspcs                                  store current program counter to top of stack
* /
*/

/* class Instruction {
private:
public:
}; */

// Integer:
static const instr_t IADD        = 0x01;
static const instr_t ISUB        = 0x02;
static const instr_t IMUL        = 0x03;
static const instr_t IDIV        = 0x04;
static const instr_t ILT         = 0x05;
static const instr_t ILTEQ       = 0x06;
static const instr_t IMT         = 0x07;
static const instr_t IMTEQ       = 0x08;
static const instr_t IEQ         = 0x09;
static const instr_t IINC        = 0x0A;
static const instr_t IDEC        = 0x0B;
static const instr_t ICONST      = 0x0C;

// Branch:
static const instr_t BR          = 0x10;
static const instr_t BRT         = 0x11;
static const instr_t BRF         = 0x12;
static const instr_t BRS         = 0x13;
static const instr_t BRST        = 0x14;
static const instr_t BRSF        = 0x15;

// Memory/Stack:
static const instr_t LOAD        = 0x20;
static const instr_t LOADR       = 0x21;
static const instr_t GLOAD       = 0x22;
static const instr_t STORE       = 0x23;
static const instr_t GSTORE      = 0x24;
static const instr_t GSTORES     = 0x25;
static const instr_t GLOADS      = 0x26;
static const instr_t LOADP       = 0x27;
static const instr_t POP         = 0x28;

// Operations:
static const instr_t HALT        = 0x40;
static const instr_t CALL        = 0x41;
static const instr_t CALLV       = 0x42;
static const instr_t RET         = 0x43;
static const instr_t RETN        = 0x44;

// System:
//   Print Interger:
static const instr_t SYSPRINTI   = 0x50;
static const instr_t SYSPRINTIL  = 0x51;
//   Print Characters:
static const instr_t SYSPRINTC   = 0x52;
static const instr_t SYSPRINTCL  = 0x53;
//   Print String
static const instr_t SYSPRINTS   = 0x54;
static const instr_t SYSPRINTSL  = 0x55;
static const instr_t SYSPRINTSZ  = 0x56;
static const instr_t SYSPRINTSZL = 0x57;
static const instr_t SYSPRINTSM  = 0x58;
static const instr_t SYSPRINTSZM = 0x59;
//   Print New Line
static const instr_t SYSPRINTNL  = 0x5A;
static const instr_t SYSPRINTNLC = 0x5B;
//   Misc
static const instr_t DBGTRACES   = 0x5C;
static const instr_t DBGTRACEI   = 0x5D;
static const instr_t SLP         = 0x5E;
static const instr_t SYSPCS      = 0x5F;

const char* instructionToString(instr_t instruction);
int instructionReservation(instr_t instruction);