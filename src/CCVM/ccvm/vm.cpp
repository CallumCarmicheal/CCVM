#include "../stdafx.h"
#include "vm.h"
#include <stdio.h>
#include "windows.h" 

char* DisplaySpecialChar(char c);

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
    int instrCount = static_cast<int>(code.size())-1;

    // Print the sizes
    printf("len (opcodes) = %i\n",  instrCount);
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

        printf("     SP: %03.d, PC: %03.d, INSTR:    %s\n", sp, pc, instructionToString(code[pc]));
        
        switch (code[pc]) {
      // Integer:
        case IADD:
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 + v2;

            // DEBUG: printf("IADD: %i + %i = %i\n", v1, v2, v1+v2);
            break;
        case ISUB: 
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 - v2;
            break;
        case IMUL: 
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 * v2; 
            break;
        case IDIV: 
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 / v2;
            break;
        case ILT:  
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 < v2;
            break;
        case IEQ:  
            v2 = stack[sp--];
            v1 = stack[sp--];
            stack[++sp] = v1 > v2; 
            break;
        case IINC:
            stack[sp]++; 
            break;
        case IDEC: 
            stack[sp]--;
            break;

        case ICONST:
            // Store the next opcode into the stack
            // as a integer const
            stack[++sp] = code[++pc];
            break;

    // Branch:
        case BR: 
            // Jmp to addr
            pc = code[++pc];
            break;

        case BRT:
            // Jmp to addr if true
            v1 = code[++pc];
            if (stack[sp--] == 1) pc = v1;
            break;

        case BRF: 
            // Jmp to addr if false
            v1 = code[++pc];
            if (stack[sp--] == 0) pc = v1;
            break;
        case BRS:   
            // Jmp to addr on stack
            // sp = addr
            pc = stack[sp--];
            break;
        case BRST: 
            // Jmp to addr on stack, if condition == 1
            // sp = condition, sp-1 = addr
            if (stack[sp--] == 1) pc = stack[sp--];
            break;
        case BRSF: 
            // Jmp to addr on stack, if condition == 0
            // sp = condition, sp-1 = addr
            if (stack[sp--] == 0) pc = stack[sp--];
            break;

    // Memory/Stack:
        case LOAD:
            // Set top of stack to stack[ FP + ADDR ]
            stack[++sp] = stack[fp + code[++pc]];
            break;
        case LOADR: 
            stack[++sp] = stack[sp - code[++sp]];
            break; 
        case GLOAD: 
            // Load the value at memory[addr] to top of stack
            stack[++sp] = memory[code[++pc]];
            break;
        case STORE:
            // Store top of stack to STACK [ FP + ADDR ] 
            stack[fp + code[++pc]] = stack[++sp];
            break;
        case GSTORE: 
            // Push memory to top of stack
            memory[code[++pc]] = stack[++sp];
            break;
        case GSTORES: 
            // Assumes the string format is 
            // pushed in the correct format,
            // LEFT -> RIGHT = TOP -> BOTTOM
            //  
            // EG:  [sp - 2] ICONST H
            //      [sp - 1] ICONST E
            //      [sp - 0] ICONST \n
            //

            // DEBUG: this->tracePrintInstructions(4, 4);
            // DEBUG: this->tracePrintStack(1, 7);

            // V1   ADDR = 0
            // V2   LEN  = 6
            // V3   SP   = SP
            //      SP   = (SP - LEN + 1) 
            //
            // After the string has been loaded into memory
            // it is popped of the stack. SP = SP - LEN(v2)

            v1 = code[++pc];
            v2 = code[++pc];
            v3 = sp;
            sp = sp - v2 + 1;

            printf("Stack Pointer Before: %i\n", sp);
            // DEBUG: printf("V1 (ADDR) = %i, V2 (LEN) = %i, V3 = SP (%i), SP = %i\n", v1, v2, v3, sp);

            for (; sp <= v3; sp++) {
                // DEBUG: printf("SP[%03.i] = [%c]\n", sp, stack[sp]);
                memory[v1++] = stack[sp];
            }

            // TODO: Check stack pointer
            sp = sp - v2 - 1;

            // DEBUG: printf("Stack Pointer After: %i\n", sp);
            // DEBUG: this->tracePrintStack(v2 + 2, 3);

            break;

        // TODO:
        case GLOADS: break;

        case LOADP:
            // 0 = Default to noArgs
            // 1 = Arg1
            // ... etc

            v1 = code[++pc];

            //DEBUG: printf("addr = %i\n", v1);
            //DEBUG: tracePrintStack(6, 6);
            //DEBUG: printf("stack[%i] = stack[( (%i-2 = %i) + %i ) = %i] = %i\n", sp+1, fp, fp-2, v1, fp-2 - v1, stack[fp-2 - v1]);
            //DEBUG: printf("Loaded param: %i = %i, stack[%i]\n", v1, stack[fp - 2 - v1], fp - 2 - v1);

            stack[++sp] = stack[fp - 2 - v1];
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
            
        // TODO:
        case CALLV: break;

        case RET:
        case RETN:
            // Check if fp == -1
            if (fp == -1) {
                // Show error
                printf("There is no where to return to, EXECUTION EXCEPTION\n");

                printf("Registers: pc = %i, fp = %i, sp = %i\n", this->pc, this->fp, this->sp);

                // Stop execution
                this->rn = 0;

                return;
            }

            // v1 = Return value
            // v2 = Number of Args
            v1 = stack[sp--];           // Pop return address
            sp = fp;                    // Jump over locals to our frame
            pc = stack[sp--];           // Pop the return address, jmp to next instruction (pc is incremented) 
            fp = stack[sp--];           // Restore previous fp (allows recursion)
            v2 = stack[sp--];           // How many args to throw away
            sp -= v2;                   // Pop the arguments

            if (code[pc] == RET)
                stack[++sp] = v1;       // Leave the result on stack

            // DEBUG: printf("sp   = %i\npc   = %i\nfp   = %i\nargs = %i\nres  = %i\n", sp, pc, fp, v2, v1);
            // DEBUG: fflush(stdout);
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

            printf("SP = %d, v2 = %i\n", sp, v2);

            while (v1 <= sp) putchar(stack[v1++]);

            // Restore our stackpointer
            sp = v2;
            break;

        // TODO:
        case SYSPRINTSZ:    break;
        case SYSPRINTSZL:   break;

        case SYSPRINTSM:    
            // we want to print off the characters stored in memory, 
            // to do this we will be setting v1 to our starting address, 
            // and v2 the ending address. 
            // this looks like v1 = addr, v2 = addr + len then we loop until 
            // v1 == v2 while looping print off each character we have in memory[v1]
            // 
            // v1 = addr
            // v2 = len
            v1 = code[++pc];
            v2 = v1 + code[++pc];

            for (; v1 < v2; v1++) {
                printf("v1 = %i, char = [%c] int = [%i]\n", v1, memory[v1], memory[v1]);
                //putchar(memory[v1]);
            }
            
            break;
        case SYSPRINTSZM:   break;

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

        Sleep(10);
    }
    
    printf("finished execution \n");
}

// TODO: Make functions that dump registers and other information

instr_t* DisplaySpecialChar(instr_t* c) {
    if (c[0] == 10) {
        // DEBUG: printf(" == 10 ");
        // I dont know how this works, it just does.
        return new instr_t[1]{ 'n\\' };
    }

    // DEBUG: printf(" != 10 ");
    return c;
}

void CCVM::tracePrintStack(int above, int below) {
    printf("Stack Trace: sp = %i, top: %i, below: %i\n", sp, above, below);
    
    for (int x = above; x > 0; x--) 
        printf("    stack[ sp +%.2d (%03.i) ] = [%2s] %i\n", x, sp+x, DisplaySpecialChar(&stack[sp+x]), stack[sp + x]);
    
    if (sp == -1)
         printf("--> stack[ sp     (%03.i) ] = [ ] NULL\n", sp);
    else printf("--> stack[ sp     (%03.i) ] = [%2s] %i\n",  sp, DisplaySpecialChar(&stack[sp]), stack[sp]);

    for (int x = 1; (x <= below) && (sp - x >= 0); x++) 
        printf("    stack[ sp -%.2d (%03.i) ] = [%2s] %i\n", x, sp-x, DisplaySpecialChar(&stack[sp-x]), stack[sp-x]);
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