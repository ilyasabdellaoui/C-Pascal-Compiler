#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
  ADD,
  SUB,
  MUL,
  DIV,
  EQL,
  NEQ,
  GTR,
  LSS,
  GEQ,
  LEQ,
  PRN,
  INN,
  INT,
  LDI,
  LDA,
  LDV,
  STO,
  BRN,
  BZE,
  HLT,
  LABEL
} INSTS;

typedef struct
{
  INSTS MNE;
  int SUITE;
} INST;

#define MEM_SIZE 100
#define MAX_LINE_LENGTH 1024

int MEM[MEM_SIZE] = {0}; // Initialize memory to zeros
int SP = -1;             // Initialize stack pointer to -1 (empty stack)
int PC = 0;              // Initialize program counter to 0

FILE *fp_code;
INST PCODE[100];

void ECRIRE1(INSTS MNEM)
{
  if (SP == MEM_SIZE - 1)
  { // Check stack overflow
    printf("Erreur : débordement de pile\n");
    exit(1);
  }
  else
  {
    // PC++;
    PCODE[PC].MNE = MNEM;
  }
}

void ECRIRE2(INSTS MNEM, int SUITE)
{
  if (SP == MEM_SIZE - 1)
  { // Check stack overflow
    printf("Erreur : débordement de pile\n");
    exit(1);
  }
  else
  {
    // PC++;
    PCODE[PC].MNE = MNEM;
    PCODE[PC].SUITE = SUITE;
  }
}

void IDENTIFY_INST(char *line)
{
  // P-code instructions are separated by tabs
  char *token = strtok(line, "\t");
  // printf("%s\t", token);
  if (strcasecmp(token, "INT") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(INT, atoi(token));
  }
  else if (strcasecmp(token, "ADD\n") == 0)
  {
    ECRIRE1(ADD);
  }
  else if (strcasecmp(token, "SUB\n") == 0)
  {
    ECRIRE1(SUB);
  }
  else if (strcasecmp(token, "MUL\n") == 0)
  {
    ECRIRE1(MUL);
  }
  else if (strcasecmp(token, "DIV\n") == 0)
  {
    ECRIRE1(DIV);
  }
  else if (strcasecmp(token, "EQL\n") == 0)
  {
    ECRIRE1(EQL);
  }
  else if (strcasecmp(token, "NEQ\n") == 0)
  {
    ECRIRE1(NEQ);
  }
  else if (strcasecmp(token, "GTR\n") == 0)
  {
    ECRIRE1(GTR);
  }
  else if (strcasecmp(token, "LSS\n") == 0)
  {
    ECRIRE1(LSS);
  }
  else if (strcasecmp(token, "GEQ\n") == 0)
  {
    ECRIRE1(GEQ);
  }
  else if (strcasecmp(token, "LEQ\n") == 0)
  {
    ECRIRE1(LEQ);
  }
  else if (strcasecmp(token, "PRN\n") == 0)
  {
    ECRIRE1(PRN);
  }
  else if (strcasecmp(token, "INN\n") == 0)
  {
    ECRIRE1(INN);
  }
  else if (strcasecmp(token, "INT") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(INT, atoi(token));
  }
  else if (strcasecmp(token, "LDI") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(LDI, atoi(token));
  }
  else if (strcasecmp(token, "LDA") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(LDA, atoi(token));
  }
  else if (strcasecmp(token, "LDV\n") == 0)
  {
    ECRIRE1(LDV);
  }
  else if (strcasecmp(token, "STO\n") == 0)
  {
    ECRIRE1(STO);
  }
  else if (strcasecmp(token, "BRN") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(BRN, atoi(token));
  }
  else if (strcasecmp(token, "BZE") == 0)
  {
    token = strtok(NULL, "\t");
    ECRIRE2(BZE, atoi(token));
  }
  else if (strcasecmp(token, "HLT\n") == 0)
  {
    ECRIRE1(HLT);
  }
  else if (strcasecmp(token, "LABEL") == 0)
  {
    // Do nothing for labels, as they are just markers in the code
    return;
  }
  else
  {
    printf("Erreur : Instruction %s non reconnue\n", token);
    exit(1);
  }
  // printf("%s\tPC %d\tSP %d\n", token, PC, SP);
}

void MOVE_PC_LABEL(INST INST) {
    fseek(fp_code, 0, SEEK_SET);
    char *temp_line = malloc(MAX_LINE_LENGTH);
    PC = 0;
    while (fgets(temp_line, MAX_LINE_LENGTH, fp_code) != NULL && PCODE[PC].MNE != HLT)
    {
      char *token = strtok(temp_line, "\t");
      if (strcasecmp(token, "LABEL") == 0)
        if (INST.SUITE == atoi(strtok(NULL, "\t"))) return;
      PC++;
    }
    printf("%d\n", PC);
}

void INTER_INST(INST INST)
{
  int val1, adr, val2;
  switch (INST.MNE)
  {
  case ADD:
    val1 = MEM[SP--];
    val2 = MEM[SP--];
    MEM[++SP] = val1 + val2;
    PC++;
    break;
  case SUB:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    MEM[++SP] = val1 - val2;
    PC++;
    break;
  case MUL:
    val1 = MEM[SP--];
    val2 = MEM[SP--];
    MEM[++SP] = val1 * val2;
    PC++;
    break;
  case DIV:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    if (val2 == 0)
    {
      printf("Erreur : Division par zéro\n");
      exit(1);
    }
    MEM[++SP] = val1 / val2;
    PC++;
    break;
  case EQL:
    val1 = MEM[SP--];
    val2 = MEM[SP--];
    MEM[++SP] = (val1 == val2);
    PC++;
    break;
  case NEQ:
    val1 = MEM[SP--];
    val2 = MEM[SP--];
    MEM[++SP] = (val1 != val2);
    PC++;
    break;
  case GTR:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    MEM[++SP] = (val1 > val2);
    PC++;
    break;
  case LSS:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    MEM[++SP] = (val1 < val2);
    PC++;
    break;
  case GEQ:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    MEM[++SP] = (val1 >= val2);
    PC++;
    break;
  case LEQ:
    val2 = MEM[SP--];
    val1 = MEM[SP--];
    MEM[++SP] = (val1 <= val2);
    PC++;
    break;
  case PRN:
    printf("%d\n", MEM[SP--]);
    PC++;
    break;
  case INN:
    printf("Entrer une valeur : ");
    scanf("%d", &val1);
    MEM[++SP] = val1;
    PC++;
    break;
  case INT:
    // SP += INST.SUITE;
    SP++;
    PC++;
    break;
  case LDI:
    MEM[++SP] = INST.SUITE;
    PC++;
    break;
  case LDA:
    MEM[++SP] = INST.SUITE;
    PC++;
    break;
  case LDV:
    adr = MEM[SP--];
    MEM[++SP] = MEM[adr];
    PC++;
    break;
  case STO:
    val1 = MEM[SP--];
    adr = MEM[SP--];
    MEM[adr] = val1;
    PC++;
    break;
  case BRN:
    // On bouge PC à l'adresse du label
    MOVE_PC_LABEL(INST);
    // Si on donnait l'adresse comme label: PC = INST.SUITE;
    break;
  case BZE:
    if (MEM[SP--] == 0) {
      MOVE_PC_LABEL(INST);
      // PC = INST.SUITE;
    }
    else
      PC++;
    break;
  case HLT:
    PC++;
    break;
  default:
    printf("Erreur : Instruction non reconnue\n");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Utilisation : %s <fichier_p-code>\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp_code = fopen(argv[1], "r");
  if (fp_code == NULL)
  {
    fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s' en lecture.\n", argv[1]);
    return EXIT_FAILURE;
  }

  char *line = malloc(MAX_LINE_LENGTH);
  if (line == NULL)
  {
    fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire.\n");
    return EXIT_FAILURE;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp_code) != NULL && PCODE[PC].MNE != HLT)
  {
    IDENTIFY_INST(line);
    INTER_INST(PCODE[PC]);
  }
  // for (int i=0; i<14; i++) {
  //   printf("PCODE: %d\t%d\n", PCODE[i].MNE, PCODE[i].SUITE);
  // }
  for (int i=0; i<5; i++) printf("%d\n", MEM[i]);
  free(line);
  fclose(fp_code);

  return EXIT_SUCCESS;
}
// explain to me what MEM stores
