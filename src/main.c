#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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

  // Create a stack of 16 registers
  typedef struct {
    uint32_t value;
    bool is_null;
  } GRegister;

  GRegister STACK_RR[16] = {0};

  char line[32];
  while (fgets(line, sizeof(line), program) != NULL) {
    char *opcode = strtok(line, " \t\n");
    char *tok1   = strtok(NULL, " \t\n");
    char *tok2   = strtok(NULL, " \t\n");
    char *tok3   = strtok(NULL, " \t\n");

    if (strcmp(opcode, "PUSH") == 0) {
      int value = atoi(tok1);
      int reg   = atoi(tok2);

      if (!STACK_RR[reg].is_null) {
        STACK_RR[reg].value = value;
        STACK_RR[reg].is_null = false;
      } else {
        printf("FATAL ERROR: Attempted to write to $R%d but $R%d is occupied!\n", reg, reg);
        return 1;
      }
    } else if (strcmp(opcode, "PULL") == 0) {
      int reg = atoi(tok1);
      if (STACK_RR[reg].is_null) {
        printf("[NULL]");
      } else { printf("%d\n", STACK_RR[reg].value); }
    } else if (strcmp(opcode, "PRNT") == 0) {
      int ascii_code = atoi(tok1);
      putchar(ascii_code);
    } else if (strcmp(opcode, "PURGE") == 0) {
      int reg = atoi(tok1);
      STACK_RR[reg].value = 0;
      STACK_RR[reg].is_null = true;
    } else if (strcmp(opcode, "HALT") == 0) {
      if (tok1 != NULL) {
        int exitcode = atoi(tok1);
        printf("Virtual machine exited with code %d\n", exitcode);
        return exitcode;
      } else {
        printf("Virtual machine exited with code 0.\n");
        return 0;
      }
    } else if (strcmp(opcode, "ADD") == 0) {
      int regrr = atoi(tok3);
      int a     = atoi(tok1);
      int b     = atoi(tok2);
      int res = a + b;
      STACK_RR[regrr].value = res;
      STACK_RR[regrr].is_null = false;
    } else if (strcmp(opcode, "SUB") == 0) {
      int regrr = atoi(tok3);
      int a     = atoi(tok1);
      int b     = atoi(tok2);
      int res = a - b;
      STACK_RR[regrr].value = res;
      STACK_RR[regrr].is_null = false;
    } else if (strcmp(opcode, "ADD_R") == 0) {
      int regrr = atoi(tok3);
      int reg1 = atoi(tok1);
      int reg2 = atoi(tok2);
      int val1 = STACK_RR[reg1].value;
      int val2 = STACK_RR[reg2].value;
      int res = val1 + val2;
      STACK_RR[regrr].value = res;
      STACK_RR[regrr].is_null = false;
    } else if (strcmp(opcode, "SUB_R") == 0) {
      int regrr = atoi(tok3);
      int reg1 = atoi(tok1);
      int reg2 = atoi(tok2);
      int val1 = STACK_RR[reg1].value;
      int val2 = STACK_RR[reg2].value;
      int res = val1 - val2;
      STACK_RR[regrr].value = res;
      STACK_RR[regrr].is_null = false;
    } else if (strcmp(opcode, "INC") == 0) {
      int dreg = atoi(tok1);
      if (tok2 != NULL) {
        int increment = atoi(tok2);
        STACK_RR[dreg].value += increment;
        STACK_RR[dreg].is_null = false;
      } else {
        STACK_RR[dreg].value++;
      }
    } else if (strcmp(opcode, "DEC") == 0) {
      int dreg = atoi(tok1);
      if (tok2 != NULL && !STACK_RR[dreg].is_null) {
        int decrement = atoi(tok2);
        STACK_RR[dreg].value -= decrement;
      } else if (tok2 == NULL && !STACK_RR[dreg].is_null) {
        STACK_RR[dreg].value -= 1;
      } else if (STACK_RR[dreg].is_null) {
        printf("FATAL ERROR: Attempted to decrement $R%d but $R%d is NULL!\n", dreg, dreg);
        return 1;
      }
    } else if (strcmp(opcode, "CMRR") == 0) {
      int srcreg  = atoi(tok1);
      int destreg = atoi(tok2);
      if (!STACK_RR[srcreg].is_null) {
        STACK_RR[destreg].value = STACK_RR[srcreg].value;
        if (STACK_RR[destreg].is_null) {
          STACK_RR[destreg].is_null = false;
        }
      }
    }
  }
}
