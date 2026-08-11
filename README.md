# semiT
Super simple programming language I made to learn how programming languages work, but I also made it to learn more about CPU ISAs (therefore I technically created a virtual machine with it's own little ISA).

Several opcodes are available now:

> PUSH  
PULL  
PULL_R  
PURGE  
PURGE_R  
ADD  
ADD_R  
SUB  
SUB_R  

The entire thing's architecture could have been done a lot better but I didn't plan any of this.

The virtual machine keeps track of 2 stacks of registers, the RE and RR stacks.
Each stack is an array of 8 strings, each string limited to 32 bytes (char STACK_RR[8][32] = {}).

STACK_RE is meant to hold only values that are currently being worked on. STACK_RR stores result values of opcodes like ADD_R and SUB_R.

Therefore you can only PUSH values to STACK_RE.

Nice cool stuff I may implement:

+ MUL and DIV opcodes.

+ Possibly a JZ and JNZ opcodes to get closer to Turing completeness. This means I will have to implement an instruction pointer which I have no idea on how to do for now.
