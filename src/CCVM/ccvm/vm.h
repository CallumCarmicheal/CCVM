#pragma once
#include "../stdafx.h"
#include "instructions.h"
#include <vector>

class CCVM {
private:
    // Registers
    int pc;     // Program Counter
    int sp;     // Stack Pointer
    int rn;     // State
    int fp;     // Framepointer

    // Data
    instr_a code;
    instr_a stack;
    instr_a memory;

    void tracePrintStack(int above, int below);
    void tracePrintInstructions(int above, int below);

public:
    CCVM();

    void Initialize(instr_a instructions, int start, int memory);
    void Execute();

    // Getters
    int getPC();
    int getSP();
    int getRN();
    int getFP();

    instr_a* getInstructions();
    instr_a* getStack();
    instr_a* getMemory();
};