#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("No file argument!\n");
    exit(1);
  }

  FILE *program = fopen(argv[1], "r");
  if (!program) {
    printf("'%s' innaccessible or not found!\n", argv[1]);
    return 1;
  }

  char STACK_RE[8][32] = {"NULL", "NULL",
                          "NULL", "NULL",
                          "NULL", "NULL",
                          "NULL", "NULL"};

  char STACK_RR[8][32] = {"NULL", "NULL",
                          "NULL", "NULL",
                          "NULL", "NULL",
                          "NULL", "NULL"};

  char line[32];
  while (fgets(line, sizeof(line), program) != NULL) {
    char *opcode = strtok(line, " \t\n");
    char *tok1   = strtok(NULL, " \t\n");
    char *tok2   = strtok(NULL, " \t\n");
    char *tok3   = strtok(NULL, " \t\n");

    if (strcmp(opcode, "PUSH") == 0) {
      int value = atoi(tok1);
      int reg   = atoi(tok2);

      if (strcmp(STACK_RE[reg], "NULL") == 0) {
        char buffer[32];
        sprintf(buffer, "%d", value);
        strcpy(STACK_RE[reg], buffer);
      } else {
        printf("FATAL ERROR: Register %d is occupied!", reg);
        return 1;
      }
    } else if (strcmp(opcode, "PULL") == 0) {
      int reg = atoi(tok1);
      printf("%s\n", STACK_RE[reg]);
    } else if (strcmp(opcode, "PULL_R") == 0) {
      int reg = atoi(tok1);
      printf("%s\n", STACK_RR[reg]);
    } else if (strcmp(opcode, "PURGE") == 0) {
      int reg = atoi(tok1);
      strcpy(STACK_RE[reg], "NULL");
    } else if (strcmp(opcode, "PURGE_R") == 0) {
      int reg = atoi(tok1);
      strcpy(STACK_RR[reg], "NULL");
    }
  }
}
