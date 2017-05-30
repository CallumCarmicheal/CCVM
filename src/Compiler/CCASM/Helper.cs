using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Compiler.CCASM {
    class Helper {
        public static bool reverseStringFormat(string template, string str, ref List<string> ret) {
            string pattern = "^" + Regex.Replace(template, @"\{[0-9]+\}", "(.*?)") + "$";
            Regex r = new Regex(pattern);
            Match m = r.Match(str);
            ret = new List<string>();

            if (m.Length == 0)
                return false;

            for (int i = 1; i < m.Groups.Count; i++) {
                ret.Add(m.Groups[i].Value);
            }

            return true;
        }

        public static List<string> strArrayToList(IEnumerable<string> a) {
            var b = new List<string>();
            b.AddRange(a);
            return b;
        }

        public static List<string> strArrayToList(string[] a) {
            var b = new List<string>();
            b.AddRange(a);
            return b;
        }

        public static IEnumerable<String> SplitDelimiter(String line, Char delimiter, Char textQualifier, bool leaveInQualifier = true) {
            if (line == null)
                yield break;

            else {
                Char prevChar = '\0';
                Char nextChar = '\0';
                Char currentChar = '\0';
                Boolean inString = false;
                StringBuilder token = new StringBuilder();

                for (int i = 0; i < line.Length; i++) {
                    currentChar = line[i];

                    if (i > 0)
                         prevChar = line[i - 1];
                    else prevChar = '\0';

                    if (i + 1 < line.Length)
                         nextChar = line[i + 1];
                    else nextChar = '\0';

                    if (currentChar == textQualifier && (prevChar == '\0' || prevChar == delimiter) && !inString) {
                        inString = true;

                        if (leaveInQualifier)
                            token = token.Append(textQualifier);
                        continue;
                    }

                    if (currentChar == textQualifier && (nextChar == '\0' || nextChar == delimiter) && inString) {
                        inString = false;

                        if (leaveInQualifier)
                            token = token.Append(textQualifier);
                        continue;
                    }

                    if (currentChar == delimiter && !inString) {
                        yield return token.ToString();
                        token = token.Remove(0, token.Length);
                        continue;
                    }

                    token = token.Append(currentChar);

                }

                yield return token.ToString();
            }
        }
    }
}
