using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler.CCASM.Exceptions {
    enum ExceptionType {
        InvalidSections,
        InvalidSectionFormat,
        InvalidLabeledData,
        UnlabledDataSection,
        InvalidInstruction
    }

    class CompilerException : Exception {
        public ExceptionType Type;
        public int Line = -1;

        public CompilerException(ExceptionType Type, string Message) : base(Message) {
            this.Type = Type;
        }

        public CompilerException(ExceptionType Type, string Message, int Line) : base (Message) {
            this.Type = Type;
            this.Line = Line;
        }
    }
}
