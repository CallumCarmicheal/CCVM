using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Compiler.CCASM.Instruction;

namespace Compiler.CCASM {
    class Compiler {

        public Compiler() { }
        
        // Translate full application into bytecode including sections
        public CompilerState CompileSource(string code) {
            // Generate Sections
            var sections = Section.CompileList(code);   // Setting up data sections
            var labels   = Label.CompileList(sections); // Linking code to labels

            // Print our labels
            Console.WriteLine("Source Labels: ");
            Console.WriteLine("\tSection | Name {1,-15} | Data", "", "", "");
            Console.WriteLine("\t".PadRight(60, '-'));

            foreach (Label lbl in labels) {
                Console.WriteLine("\t{0,-7} | {1,-20} | {2}", lbl.Section, lbl.Name, lbl.Data);
            }

            // Compile our instructions
            var sect_data         = sections["data"];
            var lbls_data         = labels.Where((x) => x.Section == "data").ToArray();
            var sect_text         = sections["text"];
            var data_instructions = new List<Instruction>();
            var instructions      = new List<Instruction>();

            // Start the data section first
            for(int x = 0; x < lbls_data.Length; x++) {
                var lbl  = lbls_data[x];
                var data = lbl.Data;

                // Check if we have a string
                if (data.StartsWith("\'")) {
                    data = data.Replace("\'", "");

                    foreach(char chr in data) {
                        data_instructions.Add(new Instruction("ICONST " + (chr - '0')) {
                            Section    = "data",
                            SourceLine = x
                        });
                    }
                }
            }

            // Compile the text section
            
            for(int x = 0; x < sect_text.Data.Count; x++) {
                var instr       = sect_text.Data[x];
                var instruction = new Instruction(instr) {
                    Section    = "text",
                    SourceLine = x
                };
            }
            
            // Now we start linking
            foreach(Instruction instr in instructions) {
                if (instr.LinkParameter) {
                    foreach(Parameter p in instr.ArgV) {
                        if (p.Type == Parameter.ParamType.Label) {
                            // Find the label

                        }
                    }
                }
            }

            return null;
        }

        

        // Directly translate instructions into bytecode
        public CompilerState CompileInstructions(string[] Instructions) {
            return null;
        }
    }
}
