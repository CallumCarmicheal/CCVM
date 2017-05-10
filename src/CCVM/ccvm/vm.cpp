#include "../stdafx.h"
#include "vm.h"
#include <stdio.h>
#include "windows.h" 

CCVM::CCVM() {}

// Setup the VM
void CCVM::Initialize(instr_a instructions, int start, int memorySize) {
    this->stack  .resize(100); // By default our stack holds 100 items
    this->memory .resize(memorySize);
    this->code = instructions;

    // Setup our registers
    this->pc = start;
    this->sp = -1;
    this->rn = 0;
    this->fp = -1;
}

// Loop the CPU
void CCVM::Execute() {
    // Set our running register to 1 
    this->rn = 1;

    instr_t v1 = 0; // Tmp 1 - int
    instr_t v2 = 0; // Tmp 2 - int
    instr_t v3 = 0; // Tmp 3 - int

    int x = 0;
    int instrCount = static_cast<int>(code.size());

    // Print the sizes
    printf("len (opcodes) = %i\n",  code.size());
    printf("len (stack)   = %i\n",  stack.size());
    printf("len (memory)  = %i\n",  memory.size());
    printf("pc = %i\n|- opcode: %i\n|- asm: %s\n\n", this->pc, code[pc], instructionToString(code[pc]));
    fflush(stdout);

    // Loop while we are running
    // and we have instructions to run
    // todo: check if there is a next instruction
    while (this->rn == 1) {

       //printf("pc = %i, sp = %i\n", pc, sp);

        if (pc > instrCount) {
            printf("pc > instrCount, %i > %i\n", pc, instrCount);
            break;
        }

        printf("     PC: %03.i, INSTR:    %s\n", pc, instructionToString(code[pc]));
        
        switch (code[pc]) {
      // Integer:
        case IADD:
            // stack = 32
            // stack[31] = stack[32] + stack[31];
            // 
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 + v2;

            printf("IADD: %i + %i = %i\n", v1, v2, v1+v2);

            // print the stack
            tracePrintStack(3, 5);
            break;

        case ISUB: 
            // 
            // 
            // 
            break;
        case IMUL: break;
        case IDIV: break;
        case ILT:  break;
        case IEQ:  break;

    // Floating Point: 
        // No functions yet

    // Branch:
        case BR: 
            pc = code[++pc];
            break;

        case BRT:
            v1 = code[++pc];
            if (stack[sp] == 1) pc = v1;
            break;

        case BRF: 
            v1 = code[++pc];
            if (stack[sp] == 0) pc = v1;
            break;

    // Data/Memory:

        case LOAD:
            // Set top of stack to stack[ FP + ADDR ]
            stack[++sp] = stack[fp + code[++pc]];
            break;
        case LOADP:
            // 0 = Default to noArgs
            // 1 = Arg1
            // ... etc

            v1 = code[++pc];
            //printf("addr = %i\n", v1);
            //tracePrintStack(6, 6);
            //printf("stack[%i] = stack[( (%i-2 = %i) + %i ) = %i] = %i\n", sp+1, fp, fp-2, v1, fp-2 - v1, stack[fp-2 - v1]);
            printf("Loaded param: %i = %i, stack[%i]\n", v1, stack[fp -2 -v1], fp -2 -v1);

            stack[++sp] = stack[fp -2 -v1];
            break;
        case GLOAD: 
            // Load the value at memory[addr] to top of stack
            stack[++sp] = memory[code[++pc]];
            break;
        case STORE:
            // Store top of stack to STACK [ FP + ADDR ] 
            stack[fp + code[++pc]] = stack[sp];
            break;
        case GSTORE: 
            // Set memory to top of stack
            memory[code[++pc]] = stack[sp];
            break;

    // Stack:
        case ICONST:
            // Store the next opcode into the stack
            // as a integer const
            stack[++sp] = code[++pc];
            break;

        case POP:
            // Decrement the sp counter
            sp--;
            break;
            
    // Operations:
        case CALL:
            // v1 = addr
            // v2 = noArgs

            v1 = code[++pc];  // Target function address
            v2 = code[++pc];  // How many args got pushed

            // Store the frameData
            //  
            //   SP+      <-- Locals
            // 
            //   pc       <-- SP    , FP
            //   fp       <-- SP -1 , FP-1
            //   noArgs   <-- SP -2 , FP-2
            //  
            //   SP -3 and UNDER  <-- ARGUMENTS    
            
            stack[++sp] = v2;   // Save number of args
            stack[++sp] = fp;   // Save frame pointer
            stack[++sp] = pc;   // Push return address

            fp = sp;            // Fp points at ret addr on stack
            pc = v1-1;          // Jump to function (note that pc is incremented)

            printf("call %i, %i. fp = %i\n", v1, v2, fp);

            break;

        case RET: 
            // Check if fp == -1

            if (fp == -1) {
                // Show error
                printf("There is no where to return to, EXECUTION EXCEPTION\n");

                printf("Registers: pc = %i, fp = %i, sp = %i\n", this->pc, this->fp, this->sp);

                // Stop execution
                this->rn = 0;

                return;
            }

            // v1 = return value
            // v2 = noargs
            v1 = stack[sp--];   // Pop return address

            sp = fp;            // Jump over locals to our frame
            pc = stack[sp--];   // Pop the return address, jmp to next instruction (pc is incremented) 
            fp = stack[sp--];   // Restore previous fp (allows recursion)
            v2 = stack[sp--];   // How many args to throw away

            sp -= v2;           // Pop the arguments

            stack[++sp] = v1;   // Leave the result on stack

            printf("sp   = %i\npc   = %i\nfp   = %i\nargs = %i\nres  = %i\n", sp, pc, fp, v2, v1);
            fflush(stdout);


            break;

        case RETN:
            break;

        case HALT:
            printf("halt\n");
            this->rn = 0;
            break;
    // System:
        case SYSPRINTI:  printf("%i", stack[sp--]); break;
        case SYSPRINTIL: printf("%i", stack[sp]);   break;
        case SYSPRINTC:  putchar(stack[sp--]);      break;
        case SYSPRINTCL: putchar(stack[sp]);        break;

        case SYSPRINTS:
        case SYSPRINTSL:
            printf("sysprints: \n");

            // v3 = Amount of chars
            v3 = code[++pc];

            // Example "Bye":
            //   strCnt, v3 = 3
            //   sp         = 5
            // 
            // Stack:
            //   5 = e   <-- sp - strCnt + 3 <-- sp
            //   4 = y   <-- sp - strCnt + 2
            //   3 = B   <-- sp - strCnt + 1
            //   2 = --  <-- sp - strCnt     <-- new sp (v2)
            //   1 = --
            //   0 = --

            // v1 = sp - strCnt+1     (3 in example)
            // v2 = New stack pointer (2 in example)
            v1 = sp - v3 + 1;
            v2 = (code[pc-1] == SYSPRINTSL) ? sp : sp - v3;

            while (v1 <= sp) putchar(stack[v1++]);
            sp = v2;

            break;

        case SYSPRINTNL:  putchar('\n'); break;
        case SYSPRINTNLC: 
            v1 = code[++pc];
            
            for (int x = 1; x <= v1; x++) 
                putchar('\n');
            break;

        case DBGTRACES:
            v1 = code[++pc]; // above
            v2 = code[++pc]; // below
            tracePrintStack(v1, v2);
            break;

        case DBGTRACEI:
            v1 = code[++pc]; // above
            v2 = code[++pc]; // below
            tracePrintInstructions(v1, v2);
            break;

        default:
            printf("unknown instruction: %i\n", code[pc]);
            break;
        }

        /* if (sp != -1)
             printf("stack[%i] = %i\n", sp, stack[sp]);
        else printf("stack = EMPTY\n"); //*/
        
        pc++;

        Sleep(1000);
    }
    
    printf("finished execution \n");
}

// TODO: Make functions that dump registers and other information

void CCVM::tracePrintStack(int above, int below) {
    printf("Stack Trace: sp = %i, top: %i, below: %i\n", sp, above, below);
    
    for (int x = above; x > 0; x--) 
        printf("    stack[ sp +%.2d (%03.i) ] = %i\n", x, sp+x, stack[sp+x]);
    
    if (sp == -1)
         printf("--> stack[ sp     (%03.i) ] = NULL\n", sp);
    else printf("--> stack[ sp     (%03.i) ] = %i\n",   sp, stack[sp]);

    for (int x = 1; (x <= below) && (sp - x >= 0); x++) 
        printf("    stack[ sp -%.2d (%03.i) ] = %i\n", x, sp-x, stack[sp-x]);
}

void CCVM::tracePrintInstructions(int above, int below) {
    printf("Instruction Trace: pc = %i, top: %i, below: %i\n", pc, above, below);

    for (int x = above; x > 0; x--) {
        printf("    instr[ pc +%.2d (%03.i) ] = %06.i, (asm: %s)\n", x, pc + x, code[pc + x], instructionToString(code[pc + x]));
        x -= instructionReservation(code[pc - x]);
    }

    printf("--> instr[ pc     (%03.i) ] = %06.i, (asm: %s)\n", pc, code[pc], instructionToString(code[pc]));
    
    for (int x = 1; (x <= below) && (pc - x >= 0); x++) {
        printf("    instr[ pc -%.2d (%03.i) ] = %06.i, (asm: %s)\n", x, pc - x, code[pc - x], instructionToString(code[pc-x]));
        x += instructionReservation(code[pc - x]);
    }
}

int CCVM::getSP() { return this->sp; }
int CCVM::getPC() { return this->pc; }
int CCVM::getRN() { return this->rn; }
int CCVM::getFP() { return this->fp; }

instr_a* CCVM::getInstructions() { return &this->code;   }
instr_a* CCVM::getMemory()       { return &this->memory; }
instr_a* CCVM::getStack()        { return &this->stack;  }