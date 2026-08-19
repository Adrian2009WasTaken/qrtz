# qrtz
Super simple programming language I made to learn how programming languages work, but I also made it to learn more about CPU ISAs (therefore I technically created a virtual machine with it's own little ISA).

Several opcodes are available now:

> PUSH  
PULL  
PRNT  
PURGE  
ADD  
ADD_R  
SUB  
SUB_R  
INC  
DEC  
WAIT  
DPFB  
CMRR  
HALT  
COMP  
JPFE  

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
