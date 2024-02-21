#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    ID_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    EOF_TOKEN,
    EG_TOKEN
} CODES_LEX;

// types d'identifateurs
typedef enum {
    TCONST,
    TVAR
} TSYM;

typedef struct {
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;

// strucrure du token
typedef struct {
    char NOM[20];
    TSYM TIDF;
    int VAL;
    int ADRESSE;
} T_TAB_IDF;

#endif /* TOKENS_H */