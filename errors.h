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

typedef struct {
    CODES_ERR code;
    const char *code_str;
    const char *message;
} ERROR_MESSAGE;

static inline ERROR_MESSAGE getError(CODES_ERR code) {
    ERROR_MESSAGE error;
    error.code = code;
    switch (code) {
        case ID_ERR: 
            error.code_str = "ID_ERR";
            error.message = "Un identiticateur est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PROGRAM_ERR: 
            error.code_str = "PROGRAM_ERR";
            error.message = "Le mot-cle 'program' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case CONST_ERR: 
            error.code_str = "CONST_ERR";
            error.message = "'const' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case VAR_ERR:
            error.code_str = "VAR_ERR";
            error.message = "'var' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case BEGIN_ERR: 
            error.code_str = "BEGIN_ERR";
            error.message = "'begin' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case END_ERR:  
            error.code_str = "END_ERR";
            error.message = "'end' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case IF_ERR: 
            error.code_str = "IF_ERR";
            error.message = "'if' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case THEN_ERR: 
            error.code_str = "THEN_ERR";
            error.message = "'then' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case WHILE_ERR:
            error.code_str = "WHILE_ERR";
            error.message = "'while' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case DO_ERR: 
            error.code_str = "DO_ERR";
            error.message = "'do' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case READ_ERR: 
            error.code_str = "READ_ERR";
            error.message = "'read' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case WRITE_ERR: 
            error.code_str = "WRITE_ERR";
            error.message = "'write' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PV_ERR:
            error.code_str = "PV_ERR";
            error.message = "';' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PT_ERR:
            error.code_str = "PT_ERR";
            error.message = "'.' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PLUS_ERR: 
            error.code_str = "PLUS_ERR";
            error.message = "'+' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case MOINS_ERR: 
            error.code_str = "MOINS_ERR";
            error.message = "'-' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case MULT_ERR: 
            error.code_str = "MULT_ERR";
            error.message = "'*' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case DIV_ERR: 
            error.code_str = "DIV_ERR";
            error.message = "'/' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case VIR_ERR: 
            error.code_str = "VIR_ERR";
            error.message = "',' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case AFF_ERR: 
            error.code_str = "AFF_ERR";
            error.message = "':=' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case INF_ERR: 
            error.code_str = "INF_ERR";
            error.message = "'<' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case INFEG_ERR: 
            error.code_str = "INFEG_ERR";
            error.message = "'<=' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case SUP_ERR:
            error.code_str = "SUP_ERR";
            error.message = "'>' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case SUPEG_ERR: 
            error.code_str = "SUPEG_ERR";
            error.message = "'>=' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case DIFF_ERR: 
            error.code_str = "DIFF_ERR";    
            error.message = "'<>' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PO_ERR: 
            error.code_str = "PO_ERR";
            error.message = "'(' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case PF_ERR: 
            error.code_str = "PF_ERR";
            error.message = "')' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case FIN_ERR: 
            error.code_str = "FIN_ERR";
            error.message = "'fin' attendu mais trouve '%s'\n";
            break;
        case NUM_ERR:
            error.code_str = "NUM_ERR";
            error.message = "Un nombre est attendu mais '%s' a ete trouve a la place\n";
            break;
        case ERREUR_ERR:
            error.code_str = "ERREUR_ERR";  
            error.message = "Erreur inattendue\n";
            break;
        case EOF_ERR:
            error.code_str = "EOF_ERR";
            error.message = "Fin de fichier inattendue\n";
            break;
        case EG_ERR:
            error.code_str = "EG_ERR";
            error.message = "'=' est attendu mais '%s' a ete trouve a la place\n";
            break;
        case CONST_VAR_BEGIN_ERR:
            error.code_str = "CONST_VAR_BEGIN_ERR";
            error.message = "'const', 'var', ou 'begin' attendu mais trouve '%s'\n";
            break;
        case VAR_BEGIN_ERR:
            error.code_str = "VAR_BEGIN_ERR";
            error.message = "'var' ou 'begin' attendu mais trouve '%s'\n";
            break;
        case MISS_ID_ERR:
            error.code_str = "MISS_ID_ERR";
            error.message = "L'identificateur '%s' est manquant ou non defini\n";
            break;
        case REP_ID_ERR:
            error.code_str = "REP_ID_ERR";
            error.message = "L'identificateur '%s' est deja defini\n";
            break;
        case CHANGE_CONST_ERR:
            error.code_str = "CHANGE_CONST_ERR";
            error.message = "Modification de constante '%s' interdite\n";
            break;
        case USED_PROG_ID_ERR:
            error.code_str = "USED_PROG_ID_ERR";
            error.message = "L'identificateur '%s' est deja utilise par le programme\n";
            break;
        default: 
            error.code_str = "ERREUR_ERR";
            error.message = "Erreur inattendue\n";
            break;
    }
    return error;
}

#endif /* ERRORS_H */