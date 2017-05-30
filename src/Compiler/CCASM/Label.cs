using Compiler.CCASM.Exceptions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler.CCASM {
    class Label {
        public string   Section;
        public string   Data;
        public int      DataIndex;
        public string   Name;
        public int      NameIndex;
        public bool     SameLineAsLabel;

        // If this is false, the data
        // will be ignored when compiling
        //
        // When label has been found in code
        // we will want to set this flag to
        // true to automatically setup the data
        // when the application has started
        public bool     Referenced = false;

        public static bool LabelExists(string section, string lblName, List<Label> labels) {
            return labels.Any((x) => x.Section == section && x.Name == lblName);
        }

        public static Label GetLabel(string section, string lblName, List<Label> labels) {
            return labels.Find((x) => x.Name == lblName);
        }

        public static Label GetLabelSection(string section, string lblName, List<Label> labels) {
            return labels.Find((x) => x.Section == section && x.Name == lblName);
        }

        public static List<Label> CompileList(Dictionary<string, Section> sections) {
            List<Label> labels = new List<Label>();
            List<string> sectionKeys = new List<string>(sections.Keys.ToArray());
            List<string> formatResponse = new List<string>();

            foreach (string sectionKey in sectionKeys) {
                var section = sections[sectionKey];

                // text == code
                // data == data segments
                if (section.Name == "text" || section.Name == "data") {
                    for (int x  = 0; x < section.Data.Count; x++) {
                        var str = Helper.SplitDelimiter(section.Data[x], ' ', '\'').ToArray()[0];

                        // Make sure we have a colon (label)
                        if (!str.Contains(':'))
                            continue;

                        var spl = Helper.SplitDelimiter(str, ':', '\'').ToArray<string>();
                        var lbl = new Label() {
                            NameIndex = x,
                            Section   = section.Name,
                            Name      = spl[0].Trim()
                        };

                        // Check if the data is not on this line
                        // EG:
                        // ------
                        //
                        // Data = 
                        //     strTestString:
                        //         'Hello World\n'
                        //
                        // Code = 
                        //     _start:
                        //         jmp _end
                        //
                        // A label can allow data on the next line
                        // ONLY on the next line, anymore lines this is viewed
                        // as invalid and will throw a error
                        //
                        // HACK: Fix this so there can be any amount of
                        // whitespace!!!
                        if (spl.Length == 1 || string.IsNullOrWhiteSpace(spl[1])) {
                            string nlData       = Helper.SplitDelimiter(section.Data[x + 1], ' ', '\'').ToArray()[0];
                            var    nlSpl        = Helper.SplitDelimiter(nlData, ':', '\'').ToArray();
                            bool   nlHasLabel   = nlSpl[0].EndsWith(":");
                            bool   nlIsInvalid  = string.IsNullOrWhiteSpace(nlData);
                            
                            if (nlIsInvalid)
                                throw new CompilerException(ExceptionType.InvalidLabeledData, 
                                    $"Labeliser: Label with no data found at {x}@{section.Name}");

                            else if (nlHasLabel)
                                throw new CompilerException(ExceptionType.InvalidLabeledData, 
                                    $"Labeliser: New label found when expecting data/instruction {x}@{section.Name}");
                            
                            lbl.Data            = nlData;
                            lbl.DataIndex       = x+1;
                            lbl.SameLineAsLabel = false;
                            labels.Add(lbl);

                            // Goto the next element (x+2)
                            x++;
                            
                            continue;
                        }

                        if (spl.Length > 2) 
                            throw new CompilerException(ExceptionType.InvalidLabeledData, 
                                $"Labeliser: Label with invalid syntax {x}@{section.Name}, {str}");
                        
                        lbl.Data            = str;
                        lbl.DataIndex       = x;
                        lbl.SameLineAsLabel = true;
                        labels.Add(lbl);
                    }
                }

                else {
                    throw new CompilerException(ExceptionType.InvalidSections, $"Labeliser: Unexpected Section {section.Name}");
                }
            }
            
            return labels; 
        }
    }
}
