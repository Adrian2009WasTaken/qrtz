#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "include.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No file argument!\n");
    exit(1);
  }

  FILE *program = fopen(argv[1], "r");
  if (!program) {
    printf("'%s' innaccessible or not found!\n", argv[1]);
    return 1;
  }

  // Create a stack of 16 registers 
  // and a special JPNF register
  typedef struct {
    uint32_t value;
    bool is_null;
  } GRegister;
  bool equal = false;

  GRegister STACK_RR[16] = { [0 ... 15] = { .value = 0, .is_null = true } };

  // Create an emulated boolean display
  // framebuffer of variable res ONLY if vm is run
  // with --display tag.
  bool display;
  char backend[16];
  int dpresy;
  int dpresx;
  if (argc >= 5 && strcmp(argv[2], "--display") == 0) {
    dpresy = atoi(argv[3]);
    dpresx = atoi(argv[4]);
    display = true;
    if (strcmp("unicode", argv[5]) == 0) {
      memcpy(&backend, "unicode", sizeof(backend));
    } else if (strcmp("ansi", argv[5]) == 0) {
      memcpy(&backend, "ansi", sizeof(backend));
    } else { memcpy(&backend, "default", sizeof(backend)); }
  } else { display = false; }
  bool displayfb[dpresy][dpresx];
  memset(displayfb, 0, sizeof(displayfb));
  // ^ Clear garbage from framebuffer

  // Create 32 byte line buffer and instruction pointerr
  int iptr = 0;
  char line[32];

  while (fgets(line, sizeof(line), program) != NULL) {
    if (line[0] == '\n' || line[0] == '\0') continue;
    char *opcode = strtok(line, " \t\n");
    char *tok1   = strtok(NULL, " \t\n");
    char *tok2   = strtok(NULL, " \t\n");
    char *tok3   = strtok(NULL, " \t\n");

    if (strcmp(opcode, "JPEQ") == 0) {
      iptr = atoi(tok1);
      equal = false;
      if (equal) {
        set_ip(iptr, program);
      }
      continue;
    }

    if (strcmp(opcode, "PUSH") == 0) {
      int value = atoi(tok1);
      int reg   = atoi(tok2);

      if (STACK_RR[reg].is_null) {
        STACK_RR[reg].value = value;
        STACK_RR[reg].is_null = false;
      } else {
        printf("ERROR: Attempted to write to $R%d but $R%d is occupied!\n", reg, reg);
        return 1;
      }
    } else if (strcmp(opcode, "JREQ") == 0) {
      int regrr = atoi(tok1);
      int value = atoi(tok2);
      int dest  = atoi(tok3);
      if (STACK_RR[regrr].value == value) {
        iptr = dest;
        set_ip(iptr, program);
      }
      continue;
    } else if (strcmp(opcode, "PULL") == 0) {
      if (display) continue;
      int reg = atoi(tok1);
      if (STACK_RR[reg].is_null) {
        printf("[NULL]");
      } else { printf("%d\n", STACK_RR[reg].value); }
    } else if (strcmp(opcode, "PRNT") == 0) {
      if (display) continue;
      int ascii_code = atoi(tok1);
      putchar(ascii_code);
    } else if (strcmp(opcode, "PURGE") == 0) {
      int reg = atoi(tok1);
      STACK_RR[reg].value = 0;
      STACK_RR[reg].is_null = true;
    } else if (strcmp(opcode, "HALT") == 0) {
      if (tok1 != NULL) {
        int exitcode = atoi(tok1);
        printf("\nVirtual machine exited with code %d\n", exitcode);
        return exitcode;
      } else {
        printf("\nVirtual machine exited with code 0.\n");
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
        iptr++;
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
    } else if (strcmp(opcode, "COMP") == 0) {
      int val1 = atoi(tok1);
      int val2 = atoi(tok2);
      int result = val1 - val2;
      if (result == 0) {
        equal = true;
      } else { equal = false; }
    } else if (strcmp(opcode, "WAIT") == 0) {
      float seconds = atof(tok1);
      struct timespec dur;
      dur.tv_sec = (time_t)seconds;
      dur.tv_nsec = (long)((seconds - dur.tv_sec) * 1000000000L);
      nanosleep(&dur, NULL);
      continue;
    } else if (strcmp(opcode, "DPFB") == 0) {
      int y = atoi(tok1);
      int x = atoi(tok2);
      if (display) {
        if (displayfb[y][x] == true) {
          displayfb[y][x] = false;
        } else { displayfb[y][x] = true; }
        render_display(backend, dpresx, dpresy, displayfb);
      } else {
        printf("VM not initialized with display. ");
        printf("Can not use DISPLAY instruction 'DPFB'! ");
        printf("Run VM with --display to enable display.\n");
        printf("VM exited with code [1]\n");
        return 1;
      }
    } else if (strcmp(opcode, "//") == 0) {
      continue;
    }
  }
}

// Helper function to set the instruction pointerr
// after a JUMP opcode chanhes it
void set_ip(int ip, FILE *program) {
  char line[32];
  int counter = 0;
  long byte_offset = 0;
  rewind(program);
  while (fgets(line, sizeof(line), program)) {
    byte_offset += strlen(line);
    counter++;
    if (counter >= ip) break;
  }
  fseek(program, byte_offset, SEEK_SET);
}
