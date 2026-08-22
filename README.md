# qrtz
Super simple programming language I made to learn how programming languages work, but I also made it to learn more about CPU ISAs (therefore I technically created a virtual machine with it's own little ISA).

Several opcodes are available now:

```
PUSH VAL REG - Sets a non-null register to a value 
PULL REG - Reads from a register and prints its value to the console
PRNT CHAR- Prints an ascii byte to the console
PURGE REG - Sets a register to NULL
ADD A B RESULT_REGISTER - Adds A and B and stores the result in RESULT_REGISTER
ADD_R REGA REGB RESULT_REGISTER - Adds register a (REGA) and register b (REGB) and stores the result in RESULT_REGISTER
SUB A B RESULT_REGISTER - Subtracts B from A and stores the result in RESULT_REGISTER
SUB_R REGA REGB RESULT_REGISTER - Subtracts register b (REGB) from register a (REGA) and stores the result in RESULT_REGISTER
INC REG (AMOUNT) - Increments the register by either 1 (if amount is not specified) or the amount given
DEC REG (AMOUNT) - Decrements the register by either 1 (if amount is not specified) or the amount given
WAIT SECONDS - Delays execution by a specified number of seconds
DPFB X Y - Flips the pixel on the display at the coordinates given
CMRR SRC DEST - Copies register SRC to register DEST
HALT EXITCODE - Stops execution and prints the exitcode given
COMP A B - Compares values A and B to each other, if they are equal it sets the equal flag to true
JREQ REG VAL DEST - Jumps to line DEST if the register is equal to VAL
JPEQ DEST - Jumps to line DEST if the equal flag is true, then clears the equal flag
```

I recently added an emulated display, enabled by running the vm using `qrtz program.qz --display x y`. x & y are the display resolutions. When running with --display, console instructions like PRNT and PULL will not work. Pixels in the display are either on or off. To toggle a pixel, you'd use the `DPFB x y` instruction, toggling the pixel at that xy position.

TODO:
  Make the display behave like how a text
  editor displays text, instead of
  printing to stdout like you'd 
  print `hello world`.

  MULL & DIV opcodes.

  Memory Management Unit + Variables

  Add labels.

  Add clear display instruction (CLDP)
  that toggles all pixels in the display
  off.

  Improve the PRNT function or optionally    merge PULL with PRNT.

  Basic conditional jumps have been added,   however more conditional jump options      must be added: JPFN, JFZ, JFNZ and a few   others. Loops work already, but the        entire instruction pointer system should   be improved. Currently POC.

  Migrate display functions into display.c

## If you want to help/contribute, you can either do so by helping to implement something from the TODO above, or simply improving this README.
