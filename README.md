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

Nice cool stuff I may implement:

+ MUL and DIV opcodes.

+ Possibly a JZ and JNZ opcodes to get closer to Turing completeness. This means I will have to implement an instruction pointer which I have no idea on how to do for now.

I recently added an emulated display, enabled by running the vm using `qrtz program.qz --display x y`. x & y are the display resolutions. When running with --display, console instructions like PRNT and PULL will not work. Pixels in the display are either on or off. To toggle a pixel, you'd use the `DPFB x y` instruction, toggling the pixel at that xy position.

TODO:
  Make the display behave like how a text
  editor displays text, instead of
  printing to stdout like you'd 
  print `hello world`.

  Add instruction pointer, CMP register,
  and JE/JNE instructions.

  Add labels.

  Add clear display instruction (CLDP)
  that toggles all pixels in the display
  off.

## If you want to help/contribute, you can either do so by helping to implement something from the TODO above, or simply improving this README.
