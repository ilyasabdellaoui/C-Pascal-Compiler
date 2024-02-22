#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Utilisation : %s <fichier_pascal>\n", argv[0]);
    return 1;
  }

  // Compile compilateur.c
  system("gcc -o compiler compilateur.c");

  // Compile interpreteur.c
  system("gcc -o interpreter interpreteur.c");

  // Run compilateur with file as input
  char command[100];
  snprintf(command, sizeof(command), "compiler .\\tests\\%s", argv[1]);
  system(command);

  printf("##############################################\n");

  // Run interpreter with pascal_output.txt as input
  char command2[100];
  char *extension = strrchr(argv[1], '.');
  char output_filename[100];
  if (extension != NULL)
  {
    // Copier le nom sans l'extension
    strncpy(output_filename, argv[1], extension - argv[1]);
    output_filename[extension - argv[1]] = '\0';
  }
  else
  {
    // Copier le nom complet si pas d'extension
    strcpy(output_filename, argv[1]);
  }
  strcat(output_filename, "_output.txt");

  snprintf(command2, sizeof(command2), "interpreter .\\tests\\%s", output_filename);
  system(command2);

  return 0;
}
