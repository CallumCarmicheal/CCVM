using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using instr_t = System.Int32;

namespace Compiler.CCASM {
    class Instructions {
        enum Opcodes : instr_t {
            // Integer:
            IADD                        = 0x01,
            ISUB                        = 0x02,
            IMUL                        = 0x03,
            IDIV                        = 0x04,
            ILT                         = 0x05,
            ILTEQ                       = 0x06,
            IMT                         = 0x07,
            IMTEQ                       = 0x08,
            IEQ                         = 0x09,
            IINC                        = 0x0A,
            IDEC                        = 0x0B,
            ICONST                      = 0x0C,

            // Branch:
            BR                          = 0x10,
            BRT                         = 0x11,
            BRF                         = 0x12,
            BRS                         = 0x13,
            BRST                        = 0x14,
            BRSF                        = 0x15,

            // Memory/Stack:
            LOAD                        = 0x20,
            LOADR                       = 0x21,
            GLOAD                       = 0x22,
            STORE                       = 0x23,
            GSTORE                      = 0x24,
            GSTORES                     = 0x25,
            GLOADS                      = 0x26,
            LOADP                       = 0x27,
            POP                         = 0x28,

            // Operations:
            HALT                        = 0x40,
            CALL                        = 0x41,
            CALLV                       = 0x42,
            RET                         = 0x43,
            RETN                        = 0x44,

            // System:
            //   Print Interger:
            SYSPRINTI                   = 0x50,
            SYSPRINTIL                  = 0x51,
            //   Print Characters:
            SYSPRINTC                   = 0x52,
            SYSPRINTCL                  = 0x53,
            //   Print String
            SYSPRINTS                   = 0x54,
            SYSPRINTSL                  = 0x55,
            SYSPRINTSZ                  = 0x56,
            SYSPRINTSZL                 = 0x57,
            SYSPRINTSM                  = 0x58,
            SYSPRINTSZM                 = 0x59,
            //   Print New Line
            SYSPRINTNL                  = 0x5A,
            SYSPRINTNLC                 = 0x5B,
            //   Misc
            DBGTRACES                   = 0x5C,
            DBGTRACEI                   = 0x5D,
            SLP                         = 0x5E,
            SYSPCS                      = 0x5F
        }

        // Integer: 
        public const string IADD        = "IADD";
        public const string ISUB        = "ISUB";
        public const string IMUL        = "IMUL";
        public const string IDIV        = "IDIV";
        public const string ILT         = "ILT";
        public const string ILTEQ       = "ILTEQ";
        public const string IMT         = "IMT";
        public const string IMTEQ       = "IMTEQ";
        public const string IEQ         = "IEQ";
        public const string IINC        = "IINC";
        public const string IDEC        = "IDEC";
        public const string ICONST      = "ICONST";

        // Branch: 
        public const string BR          = "BR";
        public const string BRT         = "BRT";
        public const string BRF         = "BRF";
        public const string BRS         = "BRS";
        public const string BRST        = "BRST";
        public const string BRSF        = "BRSF";

        // Memory/Stack: 
        public const string LOAD        = "LOAD";
        public const string LOADR       = "LOADR";
        public const string GLOAD       = "GLOAD";
        public const string STORE       = "STORE";
        public const string GSTORE      = "GSTORE";
        public const string GSTORES     = "GSTORES";
        public const string GLOADS      = "GLOADS";
        public const string LOADP       = "LOADP";
        public const string POP         = "POP";

        // Operations: 
        public const string HALT        = "HALT";
        public const string CALL        = "CALL";
        public const string CALLV       = "CALLV";
        public const string RET         = "RET";
        public const string RETN        = "RETN";

        // System: 
        //   Print Interger: 
        public const string SYSPRINTI   = "SYSPRINTI";
        public const string SYSPRINTIL  = "SYSPRINTIL";
        //   Print Characters: 
        public const string SYSPRINTC   = "SYSPRINTC";
        public const string SYSPRINTCL  = "SYSPRINTCL";
        //   Print String 
        public const string SYSPRINTS   = "SYSPRINTS";
        public const string SYSPRINTSL  = "SYSPRINTSL";
        public const string SYSPRINTSZ  = "SYSPRINTSZ";
        public const string SYSPRINTSZL = "SYSPRINTSZL";
        public const string SYSPRINTSM  = "SYSPRINTSM";
        public const string SYSPRINTSZM = "SYSPRINTSZM";
        //   Print New Line 
        public const string SYSPRINTNL  = "SYSPRINTNL";
        public const string SYSPRINTNLC = "SYSPRINTNLC";
        //   Misc 
        public const string DBGTRACES   = "DBGTRACES";
        public const string DBGTRACEI   = "DBGTRACEI";
        public const string SLP         = "SLP";
        public const string SYSPCS      = "SYSPCS";

        public static instr_t GetOpcode(string instruction) {
            instruction = instruction.ToUpper();

            switch (instruction) {
            // Integer: 
            case IADD:        return (instr_t)Opcodes.IADD;
            case ISUB:        return (instr_t)Opcodes.ISUB;
            case IMUL:        return (instr_t)Opcodes.IMUL;
            case IDIV:        return (instr_t)Opcodes.IDIV;
            case ILT:         return (instr_t)Opcodes.ILT;
            case ILTEQ:       return (instr_t)Opcodes.ILTEQ;
            case IMT:         return (instr_t)Opcodes.IMT;
            case IMTEQ:       return (instr_t)Opcodes.IMTEQ;
            case IEQ:         return (instr_t)Opcodes.IEQ;
            case IINC:        return (instr_t)Opcodes.IINC;
            case IDEC:        return (instr_t)Opcodes.IDEC;
            case ICONST:      return (instr_t)Opcodes.ICONST;

            // Branch: 
            case BR:          return (instr_t)Opcodes.BR;
            case BRT:         return (instr_t)Opcodes.BRT;
            case BRF:         return (instr_t)Opcodes.BRF;
            case BRS:         return (instr_t)Opcodes.BRS;
            case BRST:        return (instr_t)Opcodes.BRST;
            case BRSF:        return (instr_t)Opcodes.BRSF;

            // Memory/Stack: 
            case LOAD:        return (instr_t)Opcodes.LOAD;
            case LOADR:       return (instr_t)Opcodes.LOADR;
            case GLOAD:       return (instr_t)Opcodes.GLOAD;
            case STORE:       return (instr_t)Opcodes.STORE;
            case GSTORE:      return (instr_t)Opcodes.GSTORE;
            case GSTORES:     return (instr_t)Opcodes.GSTORES;
            case GLOADS:      return (instr_t)Opcodes.GLOADS;
            case LOADP:       return (instr_t)Opcodes.LOADP;
            case POP:         return (instr_t)Opcodes.POP;

            // Operations: 
            case HALT:        return (instr_t)Opcodes.HALT;
            case CALL:        return (instr_t)Opcodes.CALL;
            case CALLV:       return (instr_t)Opcodes.CALLV;
            case RET:         return (instr_t)Opcodes.RET;
            case RETN:        return (instr_t)Opcodes.RETN;

            // System: 
            //   Print Interger: 
            case SYSPRINTI:   return (instr_t)Opcodes.SYSPRINTI;
            case SYSPRINTIL:  return (instr_t)Opcodes.SYSPRINTIL;
            //   Print Characters: 
            case SYSPRINTC:   return (instr_t)Opcodes.SYSPRINTC;
            case SYSPRINTCL:  return (instr_t)Opcodes.SYSPRINTCL;
            //   Print String 
            case SYSPRINTS:   return (instr_t)Opcodes.SYSPRINTS;
            case SYSPRINTSL:  return (instr_t)Opcodes.SYSPRINTSL;
            case SYSPRINTSZ:  return (instr_t)Opcodes.SYSPRINTSZ;
            case SYSPRINTSZL: return (instr_t)Opcodes.SYSPRINTSZL;
            case SYSPRINTSM:  return (instr_t)Opcodes.SYSPRINTSM;
            case SYSPRINTSZM: return (instr_t)Opcodes.SYSPRINTSZM;
            //   Print New Line 
            case SYSPRINTNL:  return (instr_t)Opcodes.SYSPRINTNL;
            case SYSPRINTNLC: return (instr_t)Opcodes.SYSPRINTNLC;
            //   Misc 
            case DBGTRACES:   return (instr_t)Opcodes.DBGTRACES;
            case DBGTRACEI:   return (instr_t)Opcodes.DBGTRACEI;
            case SLP:         return (instr_t)Opcodes.SLP;
            case SYSPCS:      return (instr_t)Opcodes.SYSPCS;

            default:
                throw new Exceptions.CompilerException(Exceptions.ExceptionType.InvalidInstruction, 
                    $"The instruction {instruction} is not found/is invalid!");
            }


        }

        public static string ToString(instr_t instruction) {
            switch((Opcodes)instruction) {
            // Integer: 
            case Opcodes.IADD:        return IADD;
            case Opcodes.ISUB:        return ISUB;
            case Opcodes.IMUL:        return IMUL;
            case Opcodes.IDIV:        return IDIV;
            case Opcodes.ILT:         return ILT;
            case Opcodes.ILTEQ:       return ILTEQ;
            case Opcodes.IMT:         return IMT;
            case Opcodes.IMTEQ:       return IMTEQ;
            case Opcodes.IEQ:         return IEQ;
            case Opcodes.IINC:        return IINC;
            case Opcodes.IDEC:        return IDEC;
            case Opcodes.ICONST:      return ICONST;

            // Branch: 
            case Opcodes.BR:          return BR;
            case Opcodes.BRT:         return BRT;
            case Opcodes.BRF:         return BRF;
            case Opcodes.BRS:         return BRS;
            case Opcodes.BRST:        return BRST;
            case Opcodes.BRSF:        return BRSF;

            // Memory/Stack: 
            case Opcodes.LOAD:        return LOAD;
            case Opcodes.LOADR:       return LOADR;
            case Opcodes.GLOAD:       return GLOAD;
            case Opcodes.STORE:       return STORE;
            case Opcodes.GSTORE:      return GSTORE;
            case Opcodes.GSTORES:     return GSTORES;
            case Opcodes.GLOADS:      return GLOADS;
            case Opcodes.LOADP:       return LOADP;
            case Opcodes.POP:         return POP;

            // Operations: 
            case Opcodes.HALT:        return HALT;
            case Opcodes.CALL:        return CALL;
            case Opcodes.CALLV:       return CALLV;
            case Opcodes.RET:         return RET;
            case Opcodes.RETN:        return RETN;

            // System: 
            //   Print Interger: 
            case Opcodes.SYSPRINTI:   return SYSPRINTI;
            case Opcodes.SYSPRINTIL:  return SYSPRINTIL;
            //   Print Characters: 
            case Opcodes.SYSPRINTC:   return SYSPRINTC;
            case Opcodes.SYSPRINTCL:  return SYSPRINTCL;
            //   Print String 
            case Opcodes.SYSPRINTS:   return SYSPRINTS;
            case Opcodes.SYSPRINTSL:  return SYSPRINTSL;
            case Opcodes.SYSPRINTSZ:  return SYSPRINTSZ;
            case Opcodes.SYSPRINTSZL: return SYSPRINTSZL;
            case Opcodes.SYSPRINTSM:  return SYSPRINTSM;
            case Opcodes.SYSPRINTSZM: return SYSPRINTSZM;
            //   Print New Line 
            case Opcodes.SYSPRINTNL:  return SYSPRINTNL;
            case Opcodes.SYSPRINTNLC: return SYSPRINTNLC;
            //   Misc 
            case Opcodes.DBGTRACES:   return DBGTRACES;
            case Opcodes.DBGTRACEI:   return DBGTRACEI;
            case Opcodes.SLP:         return SLP;
            case Opcodes.SYSPCS:      return SYSPCS;
            }

            throw new Exceptions.CompilerException(Exceptions.ExceptionType.InvalidInstruction,
                    $"The opcode {instruction} is not found/is invalid!");
        }

        public static int GetArgumentCount(string instruction) {
            instruction = instruction.ToUpper();

            switch (instruction) {
            case BR:
            case BRT:
            case BRF:
            case LOAD:
            case LOADR:
            case GLOAD:
            case STORE:
            case GSTORE:
            case LOADP:
            case ICONST:

            case SYSPRINTS:
            case SYSPRINTSZM:
            case SYSPRINTSL:
            case SYSPRINTNLC:
            case SLP:
                return 1; 

            case CALL:
            case DBGTRACEI:
            case DBGTRACES:
            case GSTORES:
            case GLOADS:
            case CALLV:
            case SYSPRINTSM:
                return 2; 

            default:
                return 0;
            }
        }
    }
}
