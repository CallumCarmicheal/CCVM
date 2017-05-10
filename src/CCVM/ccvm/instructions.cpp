#include "../stdafx.h"
#include "instructions.h"

const char* instructionToString(instr_t instruction) {
    switch (instruction) {
    case IADD:          return "IADD"; break;
    case ISUB:          return "ISUB"; break;
    case IMUL:          return "IMUL"; break;
    case IDIV:          return "IDIV"; break;
    case ILT:           return "ILT"; break;
    case ILTEQ:         return "ILTEQ"; break;
    case IMT:           return "IMT"; break;
    case IMTEQ:         return "IMTEQ"; break;
    case IEQ:           return "IEQ"; break;

    case BR:            return "BR"; break;
    case BRT:           return "BRT"; break;
    case BRF:           return "BRF"; break;

    case LOAD:          return "LOAD"; break;
    case GLOAD:         return "GLOAD"; break;
    case STORE:         return "STORE"; break;
    case GSTORE:        return "GSTORE"; break;
    case LOADP:         return "LOADP"; break;

    case ICONST:        return "ICONST"; break;
    case POP:           return "POP"; break;

    case HALT:          return "HALT"; break;
    case CALL:          return "CALL"; break;
    case RET:           return "RET"; break;
    case RETN:          return "RETN"; break;

    case SYSPRINTI:     return "SYSPRINTI"; break;
    case SYSPRINTC:     return "SYSPRINTC"; break;
    case SYSPRINTS:     return "SYSPRINTS"; break;
    case SYSPRINTIL:    return "SYSPRINTIL"; break;
    case SYSPRINTCL:    return "SYSPRINTCL"; break;
    case SYSPRINTSL:    return "SYSPRINTSL"; break;
    case SYSPRINTNL:    return "SYSPRINTNL"; break;
    case SYSPRINTNLC:   return "SYSPRINTNLC"; break;
    case DBGTRACES:     return "DBGTRACES"; break;
    case DBGTRACEI:     return "DBGTRACEI"; break;

    default:            return "UNKNOWN"; break;
    }
}

/*
static const char* instructionToStringVM(instr_t instruction, CCVM vm) {
std::string instr = "";

switch (instruction) {
case IADD:          instr = "IADD";  break;
case ISUB:          instr = "ISUB";  break;
case IMUL:          instr = "IMUL";  break;
case IDIV:          instr = "IDIV";  break;
case ILT:           instr = "ILT";   break;
case ILTEQ:         instr = "ILTEQ"; break;
case IMT:           instr = "IMT";   break;
case IMTEQ:         instr = "IMTEQ"; break;
case IEQ:           instr = "IEQ";   break;

case BR:            instr = "BR   " + ;  break;
case BRT:           instr = "BRT  " + ; break;
case BRF:           instr = "BRF  " + ; break;

case LOAD:          instr = "LOAD"; break;
case GLOAD:         instr = "GLOAD"; break;
case STORE:         instr = "STORE"; break;
case GSTORE:        instr = "GSTORE"; break;
case LOADP:         instr = "LOADP"; break;

case ICONST:        instr = "ICONST"; break;
case POP:           instr = "POP"; break;

case HALT:          instr = "HALT"; break;
case CALL:          instr = "CALL"; break;
case RET:           instr = "RET"; break;
case RETN:          instr = "RETN"; break;

case SYSPRINTI:     instr = "SYSPRINTI"; break;
case SYSPRINTC:     instr = "SYSPRINTC"; break;
case SYSPRINTS:     instr = "SYSPRINTS"; break;
case SYSPRINTIL:    instr = "SYSPRINTIL"; break;
case SYSPRINTCL:    instr = "SYSPRINTCL"; break;
case SYSPRINTSL:    instr = "SYSPRINTSL"; break;
case SYSPRINTNL:    instr = "SYSPRINTNL"; break;
case SYSPRINTNLC:   instr = "SYSPRINTNLC"; break;
case DBGTRACES:     instr = "DBGTRACES"; break;
case DBGTRACEI:     instr = "DBGTRACEI"; break;

default:            instr = "UNKNOWN"; break;
}

return instr.c_str();
} //*/

//*
int instructionReservation(instr_t instruction) {
    switch (instruction) {
    case BR:            case BRT:
    case BRF:           case LOAD:
    case GLOAD:         case STORE:
    case GSTORE:        case LOADP:
    case ICONST:        case SYSPRINTS:
    case SYSPRINTSL:    case SYSPRINTNLC:
        return 1; break;

    case CALL:          case DBGTRACEI:
    case DBGTRACES:
        return 2; break;

    default:
        return 0;
    }

    return 0;
} //*/