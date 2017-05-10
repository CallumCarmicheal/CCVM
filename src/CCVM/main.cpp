// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ccvm/instructions.h"
#include "ccvm/vm.h"

int main() {
    CCVM vm;

    auto prog_Print = instr_a {
        // New line
        SYSPRINTNLC, 3,

        ICONST, 1, // 0
        ICONST, 2, // 1
        ICONST, 3, // 2

        // Example: Bye:
        //   strCnt = 3
        //   sp     = 5
        // 
        // Stack:
        //   5 = e   <-- sp - strCnt + 3 <-- sp
        //   4 = y   <-- sp - strCnt + 2
        //   3 = B   <-- sp - strCnt + 1
        //   2 = 3   <-- sp - strCnt     <-- new sp (v2)
        //   1 = 2
        //   0 = 1

        DBGTRACEI, 3, 3,

        // sp = 2
        //       3            4             5            06
        ICONST, 'B', ICONST, 'y',  ICONST, 'e', ICONST, '\n',

        SYSPRINTS, 4, // Print 3 characters

        // 3 new lines
        //SYSPRINTNLC, 3, 

        // Add 2 + 3
        IADD,

        // Print 5
        SYSPRINTI,

        HALT
    };

    auto prog_Functions = instr_a {
    // .def ADD(2: x, 1: y), (x+1) + y
    /* 000 */ DBGTRACES, 0, 5,      // Trace the stack, print the stack
    /* 003 */ LOADP, 1,             // y
    /* 005 */ LOADP, 2,             // x

    /* 007 */ CALL, 13, 1,          // INC(x) - Add 1 to x

    /* 010 */ IADD,                 // x + y

    /* 011 */ SYSPRINTIL,           // PRINT THE RESULT AND LEAVE ON STACK
    /* 012 */ RET,                  // Return stack val

    // .def INC(1: x), Add 1 to x
    /* 013 */ DBGTRACES, 4, 4,      // Trace the stack
    /* 016 */ LOADP, 1,             // x
    /* 018 */ ICONST, 0,            // add 1 to the stack
    /* 020 */ IADD,                 // x + 1
    /* 021 */ DBGTRACES, 6, 6,      // Debug trace the stack
    /* 024 */ RET,                  // return x

    // .def MAIN
    /* 025 */ ICONST, 3,        // 3
    /* 000 */ ICONST, 5,        // 5
    /* 000 */ CALL, 0, 2,       // int r = ADD( x: 3, y: 5 )
        
    // PRINT THE ADDED VALUE 2 times, to test
    // if the values are still on stack after print
    /* 000 */ SYSPRINTIL,
    /* 000 */ SYSPRINTNL,

    /* 000 */ SYSPRINTIL,
    /* 000 */ SYSPRINTNL,

    /* 000 */ HALT
    };

    // bytes, entry point, memory section size
    vm.Initialize( prog_Functions, 25, 0);

    vm.Execute();

    _gettch();

    return 0;
}

