#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "errors.h"

TSym_Cour SYM_PRECED;
TSym_Cour SYM_COUR;

T_TAB_IDF TAB_IDFS[100]; // On stocke ici les identificateurs
int c = 0;               // (OFFSET) Compteur pour les identificateurs

FILE *fichier;
FILE *p_output;
CODES_LEX OPERATION;
char OP_STR[20];

char Car_Cour;    // caractère courant
char PROG_ID[20]; // mot courant
int ADRESSE;
int if_label_cour = 0;
int while_label_cour = 1;

// Declaration des fonctions
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void MULOP();
void ADDOP();
void RELOP();
void COND();
void Lire_Car();
void Erreur(CODES_ERR code);
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR);
void PROGRAM();
void BLOCK();
void CONSTS();
void Sym_Suiv();
void lire_mot();
void lire_nombre();
int Is_Defined(char *NOM);
void Already_Defined(char *NOM);
void Is_Const(int INDEX);
void Generer_Arg(char *INST);
void Generer_Args(char *INST, int VAL_ADR);

// Definition des fonctions

void lire_mot() {
    char mot[20];
    int indice = 0;

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour)) {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0';

    // Verifier si le mot est un mot-cle
    if (strcasecmp(mot, "program") == 0) {
        SYM_COUR.CODE = PROGRAM_TOKEN;
    } else if (strcasecmp(mot, "const") == 0) {
        SYM_COUR.CODE = CONST_TOKEN;
    } else if (strcasecmp(mot, "var") == 0) {
        SYM_COUR.CODE = VAR_TOKEN;
    } else if (strcasecmp(mot, "begin") == 0) {
        SYM_COUR.CODE = BEGIN_TOKEN;
    } else if (strcasecmp(mot, "end") == 0) {
        SYM_COUR.CODE = END_TOKEN;
    } else if (strcasecmp(mot, "if") == 0) {
        SYM_COUR.CODE = IF_TOKEN;
    } else if (strcasecmp(mot, "then") == 0) {
        SYM_COUR.CODE = THEN_TOKEN;
    } else if (strcasecmp(mot, "while") == 0) {
        SYM_COUR.CODE = WHILE_TOKEN;
    } else if (strcasecmp(mot, "do") == 0) {
        SYM_COUR.CODE = DO_TOKEN;
    } else if (strcasecmp(mot, "read") == 0) {
        SYM_COUR.CODE = READ_TOKEN;
    } else if (strcasecmp(mot, "write") == 0) {
        SYM_COUR.CODE = WRITE_TOKEN;
    } else {
        // TO DO: Specify the identifier type on the declaration phase
        // TO DO: Prevent re
        SYM_COUR.CODE = ID_TOKEN;
    }

    // Stockage du mot dans le jeton
    strcpy(SYM_COUR.NOM, mot);
}

void lire_nombre() {
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour)) {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.NOM, nombre);
}

int nbrLigne_Cour = 1;

void Sym_Suiv() {
    SYM_PRECED = SYM_COUR;
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        if (Car_Cour == '\n') {
            nbrLigne_Cour++;
        }
        Lire_Car();
    }
    if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    else if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else
    {
        switch (Car_Cour)
        {
        case ';':
            SYM_COUR.CODE = PV_TOKEN;
            Lire_Car();
            break;

        case '+':
            SYM_COUR.CODE = PLUS_TOKEN;
            Lire_Car();
            break;

        case '-':
            SYM_COUR.CODE = MOINS_TOKEN;
            Lire_Car();
            break;

        case '*':
            SYM_COUR.CODE = MULT_TOKEN;
            Lire_Car();
            break;

        case '/':
            SYM_COUR.CODE = DIV_TOKEN;
            Lire_Car();
            break;

        case ',':
            SYM_COUR.CODE = VIR_TOKEN;
            Lire_Car();
            break;

        case ':':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = AFF_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM_COUR.CODE = ERREUR_TOKEN;
            }
            break;

        case '<':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = INFEG_TOKEN;
                Lire_Car();
            }
            else if (Car_Cour == '>')
            {
                SYM_COUR.CODE = DIFF_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM_COUR.CODE = INF_TOKEN;
            }
            break;

        case '>':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = SUPEG_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM_COUR.CODE = SUP_TOKEN;
            }
            break;

        case '(':
            SYM_COUR.CODE = PO_TOKEN;
            Lire_Car();
            break;
        case '=':
            SYM_COUR.CODE = EG_TOKEN;
            Lire_Car();
            break;

        case ')':
            SYM_COUR.CODE = PF_TOKEN;
            Lire_Car();
            break;

        case '.':
            SYM_COUR.CODE = PT_TOKEN;
            Lire_Car();
            break;

        case EOF:
            SYM_COUR.CODE = FIN_TOKEN;
            break;

        default:
            SYM_COUR.CODE = ERREUR_TOKEN;
            Lire_Car();
        }
    }
}

void Lire_Car() {
    Car_Cour = fgetc(fichier);
}

void Erreur(CODES_ERR code) {
    char *lexeme = SYM_COUR.NOM;
    ERROR_MESSAGE error = getError(code);
    printf("%s : ", error.code_str);
    printf(error.message, lexeme); 
    printf(" dans la ligne %d\n", nbrLigne_Cour);
    exit(EXIT_FAILURE);
}

void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR) {
    if (SYM_COUR.CODE == cl) {
        SYM_PRECED = SYM_COUR;
        Sym_Suiv();
    } else
        Erreur(COD_ERR);
}

void PROGRAM() {
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    strcpy(PROG_ID, SYM_PRECED.NOM);
    // Gen p-code: debut du programme
    Generer_Args("INT", c);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();
    Generer_Arg("HLT");
    // Test_Symbole(PT_TOKEN, PT_ERR);
    //  Check for the dot after BLOCK
    if (SYM_COUR.CODE == PT_TOKEN) {
        // Sym_Suiv(); // Consume the dot
        printf("Fin de l'execution du programme.\nSucces : programme correct !\n");
    }
    else {
        Erreur(PT_ERR);
        printf("ERREUR: fin de programme erronee!!!!\n");

        // Add this line to consume symbols until the end of the file
        while (SYM_COUR.CODE != FIN_TOKEN) {
            printf("Current Token: %d\n", SYM_COUR.CODE);
            printf("Current Lexeme: %s\n", SYM_COUR.NOM);
            Sym_Suiv();
        }
    }
}

void BLOCK() {
    CONSTS();
    VARS();
    INSTS();
}

void Already_Defined(char *NOM) {
    for (int i = 0; i < 100 && strcmp(TAB_IDFS[i].NOM, ""); i++) {
        if (!strcmp(TAB_IDFS[i].NOM, NOM)) {
            Erreur(REP_ID_ERR);
        }
    }
}

void CONSTS() {
    switch (SYM_COUR.CODE) {
    case CONST_TOKEN:
        Sym_Suiv();
        do {
            if (strcmp(SYM_COUR.NOM, PROG_ID) == 0) {
                Erreur(USED_PROG_ID_ERR);
            }
            Already_Defined(SYM_COUR.NOM);
            TAB_IDFS[c].TIDF = TCONST;
            strcpy(TAB_IDFS[c].NOM, SYM_COUR.NOM);
            Sym_Suiv();
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            TAB_IDFS[c].VAL = atoi(SYM_PRECED.NOM);
            Test_Symbole(PV_TOKEN, PV_ERR);
            // Generation du p-code pour l'affectation
            Generer_Args("LDA", c);
            Generer_Args("LDI", TAB_IDFS[c].VAL);
            Generer_Arg("STO");
            c++;
        } while (SYM_COUR.CODE == ID_TOKEN);
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
}

void VARS() {
    switch (SYM_COUR.CODE) {
    case VAR_TOKEN:
        TAB_IDFS[c].TIDF = TVAR;
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
        if (strcmp(SYM_COUR.NOM, PROG_ID) == 0) {
            Erreur(USED_PROG_ID_ERR);
        }
        Already_Defined(SYM_PRECED.NOM);
        strcpy(TAB_IDFS[c].NOM, SYM_PRECED.NOM);
        // Reservation implicite de l'espace memoire
        c++;
        while (SYM_COUR.CODE == VIR_TOKEN) {
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
            if (strcmp(SYM_COUR.NOM, PROG_ID) == 0) {
                Erreur(USED_PROG_ID_ERR);
            }
            TAB_IDFS[c].TIDF = TVAR;
            Already_Defined(SYM_PRECED.NOM);
            strcpy(TAB_IDFS[c].NOM, SYM_PRECED.NOM);
            c++;
        }

        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(VAR_BEGIN_ERR);
        break;
    }
}

void INSTS() {
    // begin INST { ; INST } end
    if (SYM_COUR.CODE == BEGIN_TOKEN) {
        Sym_Suiv();
        INST();

        while (SYM_COUR.CODE == PV_TOKEN) {
            Sym_Suiv();
            INST();
        }

        if (SYM_COUR.CODE == END_TOKEN) {
            Sym_Suiv();
        } else {
            Erreur(FIN_ERR);
        }
    } else {
        Erreur(BEGIN_ERR);
    }
}

void INST() {
    // INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM_COUR.CODE) {
        case BEGIN_TOKEN:
            INSTS();
            break;
        case ID_TOKEN:
            AFFEC();
            break;
        case IF_TOKEN:
            SI();
            break;
        case WHILE_TOKEN:
            TANTQUE();
            break;
        case WRITE_TOKEN:
            ECRIRE();
            break;
        case READ_TOKEN:
            LIRE();
            break;
        default:
            break;
    }
}

void Is_Const(int INDEX) {
    if (TAB_IDFS[INDEX].TIDF == TCONST) {
        Erreur(CHANGE_CONST_ERR);
    }
}

void AFFEC() {
    // ID := EXPR
    Test_Symbole(ID_TOKEN, ID_ERR);
    ADRESSE = Is_Defined(SYM_PRECED.NOM);
    Is_Const(ADRESSE);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    // Gen p-code: recuperation de l'adresse
    Generer_Args("LDA", ADRESSE);
    EXPR();
    Generer_Arg("STO");
}

void SI() {
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND();
    Generer_Args("BZE", if_label_cour);
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST();
    Generer_Args("LABEL", if_label_cour);
    if_label_cour += 3;
}

void TANTQUE() {
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    Generer_Args("LABEL", while_label_cour);
    COND();
    Generer_Args("BZE", while_label_cour + 1);
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
    Generer_Args("BRN", while_label_cour);
    Generer_Args("BZE", while_label_cour + 1);
    while_label_cour += 3;
}

void ECRIRE() {
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPR();
    Generer_Arg("PRN");
    while (SYM_COUR.CODE == VIR_TOKEN) {
        Sym_Suiv();
        EXPR();
        Generer_Arg("PRN");
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

void LIRE() {
    Test_Symbole(READ_TOKEN, READ_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    ADRESSE = Is_Defined(SYM_PRECED.NOM);
    Generer_Args("LDA", ADRESSE);
    Generer_Arg("INN");
    while (SYM_COUR.CODE == VIR_TOKEN) {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
        ADRESSE = Is_Defined(SYM_PRECED.NOM);
        Generer_Args("LDA", ADRESSE);
        Generer_Arg("INN");
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

void COND() {
    EXPR();
    RELOP();
    EXPR();
    Generer_Arg(OP_STR);
}

// load the value of the expression in stack
void EXPR() {
    // TERM { ADDOP TERM }
    TERM();

    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN) {
        OPERATION = SYM_COUR.CODE;
        ADDOP();
        TERM();
        if (OPERATION = PLUS_TOKEN) {
            Generer_Arg("ADD");
        } else {
            Generer_Arg("SUB");
        }
    }
}

void TERM() {
    FACT();
    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN) {
        OPERATION = SYM_COUR.CODE;
        MULOP();
        FACT();
        if (OPERATION = MULT_TOKEN) {
            Generer_Arg("MUL");
        } else {
            Generer_Arg("DIV");
        }
    }
}

int Is_Defined(char *NOM) {
    for (int i = 0; i < 100 && strcmp(TAB_IDFS[i].NOM, ""); i++) {
        if (!strcmp(TAB_IDFS[i].NOM, NOM)) {
            return i;
        }
    }
    Erreur(MISS_ID_ERR);
    return -1;
}

void FACT() {
    switch (SYM_COUR.CODE) {
    case ID_TOKEN:
        Test_Symbole(ID_TOKEN, ID_ERR);
        ADRESSE = Is_Defined(SYM_PRECED.NOM);
        // Gen p-code: recuperation de la valeur
        Generer_Args("LDA", ADRESSE);
        Generer_Arg("LDV");
        break;
    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        Generer_Args("LDI", atoi(SYM_PRECED.NOM));
        break;
    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR();
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void RELOP() {
    Sym_Suiv();
    switch (SYM_PRECED.CODE)
    {
    case EG_TOKEN:
        strcpy(OP_STR, "EQL");
        break;
    case DIFF_TOKEN:
        strcpy(OP_STR, "NEQ");
        break;
    case INF_TOKEN:
        strcpy(OP_STR, "LSS");
        break;
    case SUP_TOKEN:
        strcpy(OP_STR, "GTR");
        break;
    case INFEG_TOKEN:
        strcpy(OP_STR, "LEQ");
        break;
    case SUPEG_TOKEN:
        strcpy(OP_STR, "GEQ");
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void ADDOP() {
    switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN:
        Test_Symbole(SYM_COUR.CODE, PLUS_ERR);
        break;
    case MOINS_TOKEN:
        Test_Symbole(SYM_COUR.CODE, MOINS_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void MULOP() {
    switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN:
        Test_Symbole(SYM_COUR.CODE, MULT_ERR);
        break;
    case DIV_TOKEN:
        Test_Symbole(SYM_COUR.CODE, DIV_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void Generer_Arg(char *INST) {
    fprintf(p_output, "%s\n", INST);
}

void Generer_Args(char *INST, int VAL_ADR) {
    fprintf(p_output, "%s\t%d\n", INST, VAL_ADR);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Utilisation : %s <fichier_pascal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s' en lecture.\n", argv[1]);
        return EXIT_FAILURE;
    }

    // L'extension du fichier pascal va etre remplacee par _output.txt
    char *extension = strrchr(argv[1], '.');
    char output_filename[100];
    if (extension != NULL) {
        // Copier le nom sans l'extension
        strncpy(output_filename, argv[1], extension - argv[1]);
        output_filename[extension - argv[1]] = '\0';
    } else {
        // Copier le nom complet si pas d'extension
        strcpy(output_filename, argv[1]);
    }
    strcat(output_filename, "_output.txt");

    // Ouvrir le fichier de sortie en ecriture
    p_output = fopen(output_filename, "w");
    if (p_output == NULL) {
        fprintf(stderr, "Erreur : Impossible de creer le fichier de sortie.\n");
        fclose(fichier);
        return EXIT_FAILURE;
    }

    // PREMIER_SYM();
    Lire_Car();
    Sym_Suiv();

    PROGRAM();
    // printf("Program execution completed.2\n");

    // if (SYM_COUR.CODE == EOF_TOKEN)
    // {
    //     printf("BRAVO: le programme est correcte!!!\n");
    // }
    // else
    // {
    //     printf("PAS BRAVO: fin de programme erronee!!!!\n");
    //     printf("Current Token: %d\n", SYM_COUR.CODE);
    //     printf("Current Lexeme: %s\n", SYM_COUR.NOM);
    //     Sym_Suiv(); // Move this line inside the else block
    // }

    // if in 2nd arhument we have the word "print" then we print the table of identifiers
    if (argc > 2 && strcmp(argv[2], "print") == 0) {
        printf("TABLE DES IDENTIFICATEURS\n");
        for (int i = 0; i < 100 && strcmp(TAB_IDFS[i].NOM, ""); i++) {
            printf("%s \n", TAB_IDFS[i].NOM);
        }
    }
    fclose(fichier);

    return 0;
}