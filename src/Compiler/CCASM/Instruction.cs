using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using instr_t = System.Int32;

namespace Compiler.CCASM {
    
    
    class Instruction {
        public class Parameter {
            public enum ParamType {
                Label,
                LabelLinked,
                Integer
            }

            public ParamType Type;
            public string    Label;
            public int       Integer;
            public int       LinkerResult;
        }

        // Section the instruction originated from
        public string           Section;

        // The instruction to encode
        public string           Code;

        // The encoded instruction
        public instr_t          Opcode;

        // The amount of parameters after this instruction
        public int              ArgC;

        // The arguments of the instruciton
        public List<Parameter>  ArgV = new List<Parameter>();

        // The line of source code 
        // Used for linking
        public int              SourceLine;

        // State that we need to link a parameter
        public bool             LinkParameter = false;

        public Instruction(string instr, int SourceLine = -1) {
            var    splInstruction  = instr.Trim().Split(' ');
            string instruction     = splInstruction[0];
            this.  Code            = instr;
            this.  SourceLine      = SourceLine;
            this.  Opcode          = Instructions.GetOpcode(instruction);
            this.  ArgC            = Instructions.GetArgumentCount(instruction);
            
            if (splInstruction.Length-1 != ArgC)
                throw new Exceptions.CompilerException(Exceptions.ExceptionType.InvalidInstruction,
                    $"The instruction {instr} is not in the valid format, Expecting {ArgC} arguments, " + 
                    $"got {splInstruction.Length}!");

            var skipped            = splInstruction.Skip(1).ToArray();

            foreach (string param in skipped) {
                int iOut;
                if (int.TryParse(param, out iOut)) {
                    ArgV.Add(new Parameter {
                        Type      = Parameter.ParamType.Integer,
                        Integer   = iOut
                    });

                    continue;
                } else {
                    // Assume we have a label
                    LinkParameter = true;

                    ArgV.Add(new Parameter {
                        Type      = Parameter.ParamType.Label,
                        Label     = param
                    });
                }
            }
        }
    }
}
