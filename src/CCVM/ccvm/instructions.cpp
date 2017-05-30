#include "../stdafx.h"
#include "instructions.h"

const char* instructionToString(instr_t instruction) {
    switch (instruction) {
        // Integer
    case ICONST:        return "ICONST"; break;
    case IADD:          return "IADD"; break;
    case ISUB:          return "ISUB"; break;
    case IMUL:          return "IMUL"; break;
    case IDIV:          return "IDIV"; break;
    case ILT:           return "ILT"; break;
    case ILTEQ:         return "ILTEQ"; break;
    case IMT:           return "IMT"; break;
    case IMTEQ:         return "IMTEQ"; break;
    case IEQ:           return "IEQ"; break;

        // Branch
    case BR:            return "BR"; break;
    case BRT:           return "BRT"; break;
    case BRF:           return "BRF"; break;
    case BRS:           return "BRS"; break;
    case BRST:          return "BRST"; break;
    case BRSF:          return "BRSF"; break;

        // Memory/Stack
    case LOAD:          return "LOAD"; break;
    case LOADR:         return "LOADR"; break;
    case GLOAD:         return "GLOAD"; break;
    case STORE:         return "STORE"; break;
    case GSTORE:        return "GSTORE"; break;
    case GSTORES:       return "GSTORES"; break;
    case GLOADS:        return "GLOADS"; break;
    case LOADP:         return "LOADP"; break;
    case POP:           return "POP"; break;

        // Operations
    case HALT:          return "HALT"; break;
    case CALL:          return "CALL"; break;
    case CALLV:         return "CALLV"; break;
    case RET:           return "RET"; break;
    case RETN:          return "RETN"; break;

        // System
    case SYSPRINTI:     return "SYSPRINTI"; break;
    case SYSPRINTC:     return "SYSPRINTC"; break;
    case SYSPRINTS:     return "SYSPRINTS"; break;
    case SYSPRINTSZ:    return "SYSPRINTSZ"; break;
    case SYSPRINTSM:    return "SYSPRINTSM"; break;
    case SYSPRINTSZM:   return "SYSPRINTSZM"; break;
    case SYSPRINTIL:    return "SYSPRINTIL"; break;
    case SYSPRINTCL:    return "SYSPRINTCL"; break;
    case SYSPRINTSL:    return "SYSPRINTSL"; break;
    case SYSPRINTSZL:   return "SYSPRINTSZL"; break;
    case SYSPRINTNL:    return "SYSPRINTNL"; break;
    case SYSPRINTNLC:   return "SYSPRINTNLC"; break;
    case DBGTRACES:     return "DBGTRACES"; break;
    case DBGTRACEI:     return "DBGTRACEI"; break;
    case SLP:           return "SLP"; break;
    case SYSPCS:        return "SYSPCS"; break;

    default:            return "UNKNOWN"; break;
    }
}

//*
int instructionReservation(instr_t instruction) {
    switch (instruction) {
    case BR:            case BRT:
    case BRF:           case LOAD:  case LOADR:
    case GLOAD:         case STORE:
    case GSTORE:        case LOADP:
    case ICONST:        
    

    case SYSPRINTS:     case SYSPRINTSZM:
    case SYSPRINTSL:    case SYSPRINTNLC:
    case SLP:
        return 1; 

    case CALL:          case DBGTRACEI:
    case DBGTRACES:     case GSTORES:
    case GLOADS:        case CALLV:

    case SYSPRINTSM:
        return 2;

    default:
        return 0;
    }
} //*/