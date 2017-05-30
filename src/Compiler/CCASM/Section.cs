using Compiler.CCASM.Exceptions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler.CCASM {
    class Section {
        public string Name;
        public List<string> Arguments = new List<string>();
        public List<string> Data = new List<string>();

        public static Dictionary<string, Section> CompileList(string program) {
            Dictionary<string, Section> sections = new Dictionary<string, Section>();
            List<string> formatResponse          = new List<string>();
            string[] code                        = program.Split('\n');
            string currentSection                = "";

            // Create a index of all the sections
            for (int x = 0; x < code.Length; x++) {
                string str = code[x].Split(';')[0].Trim();

                // Skip over empty lines
                if (string.IsNullOrWhiteSpace(str))
                    continue;

                // Check if string is a section
                if (Helper.reverseStringFormat(".section {0}", str, ref formatResponse)) {
                    string[] data = formatResponse[0].Split(' ');

                    if (sections.ContainsKey(data[0])) 
                        throw new CompilerException(ExceptionType.InvalidSections,
                            $"Duplicated Section: Line={x}, Section={data[0]}");
                    

                    Section s      = new Section();
                    s.Name         = data[0];
                    s.Arguments    = Helper.strArrayToList(data.Skip(1));
                    currentSection = s.Name;
                    sections.Add(s.Name, s);
                    continue;
                }

                // We have a issue, no section has been indicated but
                // code has been placed
                else if (string.IsNullOrWhiteSpace(currentSection)) 
                    throw new CompilerException(ExceptionType.InvalidSections, 
                        $"No Section Specifed: Line={x}, Section={currentSection}, Instruction={str}");
                
                // We have data
                sections[currentSection].Data.Add(str);
            }

            return sections;
        }
    }
}
