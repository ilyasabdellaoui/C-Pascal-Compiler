#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    ID_ERR,
    PROGRAM_ERR,
    CONST_ERR,
    VAR_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    THEN_ERR,
    WHILE_ERR,
    DO_ERR,
    READ_ERR,
    WRITE_ERR,
    PV_ERR,
    PT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    FIN_ERR,
    NUM_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    CONST_VAR_BEGIN_ERR,
    VAR_BEGIN_ERR,
    MISS_ID_ERR,
    REP_ID_ERR,
    CHANGE_CONST_ERR,
    USED_PROG_ID_ERR
} CODES_ERR;

static inline const char * getError(CODES_ERR code) {
    switch (code) {
        case ID_ERR: return "ID_ERR";
        case PROGRAM_ERR: return "PROGRAM_ERR";
        case CONST_ERR: return "CONST_ERR";
        case VAR_ERR: return "VAR_ERR";
        case BEGIN_ERR: return "BEGIN_ERR";
        case END_ERR: return "END_ERR";
        case IF_ERR: return "IF_ERR";
        case THEN_ERR: return "THEN_ERR";
        case WHILE_ERR: return "WHILE_ERR";
        case DO_ERR: return "DO_ERR";
        case READ_ERR: return "READ_ERR";
        case WRITE_ERR: return "WRITE_ERR";
        case PV_ERR: return "PV_ERR";
        case PT_ERR: return "PT_ERR";
        case PLUS_ERR: return "PLUS_ERR";
        case MOINS_ERR: return "MOINS_ERR";
        case MULT_ERR: return "MULT_ERR";
        case DIV_ERR: return "DIV_ERR";
        case VIR_ERR: return "VIR_ERR";
        case AFF_ERR: return "AFF_ERR";
        case INF_ERR: return "INF_ERR";
        case INFEG_ERR: return "INFEG_ERR";
        case SUP_ERR: return "SUP_ERR";
        case SUPEG_ERR: return "SUPEG_ERR";
        case DIFF_ERR: return "DIFF_ERR";
        case PO_ERR: return "PO_ERR";
        case PF_ERR: return "PF_ERR";
        case FIN_ERR: return "FIN_ERR";
        case NUM_ERR: return "NUM_ERR";
        case ERREUR_ERR: return "ERREUR_ERR";
        case EOF_ERR: return "EOF_ERR";
        case EG_ERR: return "EG_ERR";
        case CONST_VAR_BEGIN_ERR: return "CONST_VAR_BEGIN_ERR";
        case VAR_BEGIN_ERR: return "VAR_BEGIN_ERR";
        case MISS_ID_ERR: return "MISS_ID_ERR";
        case REP_ID_ERR: return "REP_ID_ERR";
        case CHANGE_CONST_ERR: return "CHANGE_CONST_ERR";
        case USED_PROG_ID_ERR: return "USED_PROG_ID_ERR";
        default: return "UNKNOWN_ERR";
    }
}

#endif /* ERRORS_H */