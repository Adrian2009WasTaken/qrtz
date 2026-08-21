#include <stdio.h>

int number = 0;
int main(void) {
  while (number != 6000000) {
    printf("%d\n", number);
    number++;
  }
}
