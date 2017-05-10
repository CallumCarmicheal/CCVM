#pragma once
#include "../stdafx.h"
#include <vector>

typedef int instr_t;
typedef std::vector<instr_t> instr_a;

/**
* CAT  OPCODE      INSTR           pc+1        pc+2        DESCRIPTION
* ----------------------------------------------------------------------------------------------------------------------------
* integer:
* |    0x00000001  iadd                                    integer add (pop 2 operands, add, push result)
* |    0x00000002  isub                                    integer subtract,                 sp-1 -  sp
* |    0x00000003  imul                                    integer multiply,                 sp-1 *  sp
* |    0x00000004  idiv                                    integer divide,                   sp-1 /  sp
* |    0x00000005  ilt                                     integer less than,                sp-1 <  sp
* |    0x00000006  ilteq                                   integer less than or equal to,    sp-1 <= sp
* |    0x00000007  imt                                     integer more than,                sp-1 >  sp
* |    0x00000008  imteq                                   integer more than or equal to,    sp-1 >= sp
* |    0x00000009  ieq                                     integer equal to,                 sp-1 == sp
* /
*
* branch:
* |    0x00000010  br              addr                    branch to address
* |    0x00000011  brt             addr                    branch if true
* |    0x00000012  brf             addr                    branch if false
* /
*
* memory/data:
* |    0x00000020  load            addr                    load local variable
* |    0x00000021  gload           addr                    load global variable
* |    0x00000022  store           addr                    store local variable
* |    0x00000023  gstore          addr                    store global variable
* |    0x00000024  loadp           addr                    load a parameter from call
* /
*
* stack:
* |    0x00000030  iconst          value                   push integer constant to the top of the stack
* |    0x00000031  pop                                     pop the top of the stack
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
* |    0x00000050  sysprinti                               print the value on the top of the stack, values popped of the stack
* |    0x00000051  sysprintc                               print the value on the stack as a character, values popped of stack
* |    0x00000052  sysprints       strCnt                  print as string until \0, values popped of stack
* |    0x00000053  sysprintil                              print the value on the top of the stack, values left on the stack
* |    0x00000054  sysprintcl                              print the value on the stack as a character, values left on stack
* |    0x00000055  sysprintsl      strCnt                  print as string until \0, values left on stack
* |    0x00000056  sysprintnl                              print a newline character
* |    0x00000057  sysprintnlc     nlCount                 print multiple new line characters (nlCount)
* |    0x00000058  dbgtraces       above,      below       print the stack by above and below.
* |    0x00000059  dbgtracei       above,      below       print the instructions above and below
* |    0x0000005A  slp             amt                     sleep for amt milliseconds
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

// Floating Point: 

// Branch:
static const instr_t BR          = 0x10;
static const instr_t BRT         = 0x11;
static const instr_t BRF         = 0x12;

// Data/Memory:
static const instr_t LOAD        = 0x20;
static const instr_t GLOAD       = 0x21;
static const instr_t STORE       = 0x22;
static const instr_t GSTORE      = 0x23;
static const instr_t LOADP       = 0x24;

// Stack:
static const instr_t ICONST      = 0x30;
static const instr_t POP         = 0x31;

// Operations:
static const instr_t HALT        = 0x40;
static const instr_t CALL        = 0x41;
static const instr_t CALLV       = 0x42;
static const instr_t RET         = 0x43;
static const instr_t RETN        = 0x44;

// System:
static const instr_t SYSPRINTI   = 0x50;
static const instr_t SYSPRINTC   = 0x51;
static const instr_t SYSPRINTS   = 0x52;
static const instr_t SYSPRINTIL  = 0x53;
static const instr_t SYSPRINTCL  = 0x54;
static const instr_t SYSPRINTSL  = 0x55;
static const instr_t SYSPRINTNL  = 0x56;
static const instr_t SYSPRINTNLC = 0x57;
static const instr_t DBGTRACES   = 0x58;
static const instr_t DBGTRACEI   = 0x59;

const char* instructionToString(instr_t instruction);
int instructionReservation(instr_t instruction);