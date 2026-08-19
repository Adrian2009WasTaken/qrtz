#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include.h"

// Creatimg a wrapper for both display bsackends
void render_display(char backend[], int dpresx, int dpresy, bool displayfb[dpresx][dpresy]) {
  if (strcmp(backend, "ansi") == 0) {
    render_display_ansi(dpresx, dpresy, displayfb);
  } else if (strcmp(backend, "unicode") == 0) {
    render_display_unicode(dpresx, dpresy, displayfb);
  } else {
    printf("No backend specified, defaulting to ANSI.");
    render_display_ansi(dpresx, dpresy, displayfb);
  }
}

void render_display_ansi(int dpresx, int dpresy, bool displayfb[dpresy][dpresx]) {
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

// an option to render display with unicodee blockss
void render_display_unicode(int dpresx, int dpresy, bool displayfb[dpresy][dpresx]) {
  for (int y = 0; y < dpresy; y++) {
    for (int x = 0; x < dpresx; x++) {
      if (displayfb[y][x]) {
        printf("██");
      } else {
        printf("  ");
      }
    } printf("\n");
  } printf("\n");
}
