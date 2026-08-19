#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include.h"

void render_display(int dpresx, int dpresy, bool displayfb[dpresy][dpresx]) {
  for (int y = 0; y < dpresy; y++) {
    for (int x = 0; x < dpresx; x++) {
      if (displayfb[y][x]) {
          printf("\033[47m  \033[0m");
      } else {
          printf("\033[40m  \033[0m");
      }
    }
    printf("\n");
  }
  printf("\n");
}
