using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Compiler {
    class Program {

        private static void convertToInstructionSwitchCase() {
            string strInstructions = System.IO.File.ReadAllText("ccvm/Instructions.txt").Replace("static const instr_t ", "");
            string[] aInstructions = strInstructions.Split('\n');

            // Generate switch data (opcodes)
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('='))             continue;

                string code = aInstructions[x];
                var    spl  = aInstructions[x].Split('=');
                var    trim = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = "case Instructions.Opcodes." + trim[0] + ": break;";
            }

            System.IO.File.WriteAllLines("ccvm/Instructions.Switch.Opcodes.txt", aInstructions);

            // Reset the instructions
            aInstructions = strInstructions.Split('\n');

            // Generate switch (string to opcodes)
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('=')) continue;

                string code = aInstructions[x];
                var spl = aInstructions[x].Split('=');
                var trim = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = $"case {trim[0]}: return (instr_t)Opcodes.{trim[0]};";
            }

            // Save
            System.IO.File.WriteAllLines("ccvm/Instructions.Switch.StringToOpcodes.txt", aInstructions);

            // Reset the instructions
            aInstructions = strInstructions.Split('\n');

            // Generate switch (opcodes to string)
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('=')) continue;

                string code = aInstructions[x];
                var spl = aInstructions[x].Split('=');
                var trim = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = $"case Opcodes.{trim[0]}: return {trim[0]};";
            }

            // Save
            System.IO.File.WriteAllLines("ccvm/Instructions.Switch.OpcodesToString.txt", aInstructions);


            // Reset the instructions
            aInstructions = strInstructions.Split('\n');

            // Generate switch (string)
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('=')) continue;

                string code = aInstructions[x];
                var    spl  = aInstructions[x].Split('=');
                var    trim = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = "case Instructions." + trim[0] + ": break;";
            }

            // Save
            System.IO.File.WriteAllLines("ccvm/Instructions.Switch.String.txt", aInstructions);

            // Reset the instructions
            aInstructions = strInstructions.Split('\n');

            // Generate string data
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('=')) continue;

                string code = aInstructions[x];
                var    spl  = aInstructions[x].Split('=');
                var    trim = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = $"public const string {trim[0]} = \"{trim[0]}\";";
            }

            // Save
            System.IO.File.WriteAllLines("ccvm/Instructions.Strings.txt", aInstructions);

            // Reset the instructions
            aInstructions = strInstructions.Split('\n');

            // Generate Enum data
            for (int x = 0; x < aInstructions.Length; x++) {
                aInstructions[x] = aInstructions[x].Replace("\r", "\0");

                if (string.IsNullOrWhiteSpace(aInstructions[x])) continue;
                if (!aInstructions[x].Contains('=')) continue;

                string code = aInstructions[x];
                var spl     = aInstructions[x].Split('=');
                var trim    = spl.Select(y => y == null ? null : y.Trim()).ToArray();

                aInstructions[x] = $"{trim[0]} = {trim[1].Replace(';', ',')}";
            }

            // Save
            System.IO.File.WriteAllLines("ccvm/Instructions.Enum.txt", aInstructions);
        }


        static void Main(string[] args) {
            string program = System.IO.File.ReadAllText("src/test.asm");
            convertToInstructionSwitchCase();


            CCASM.Compiler compiler = new CCASM.Compiler();
            var resp = compiler.CompileSource(program);


            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("Done");
            Console.ReadKey();
        }
    }
}
