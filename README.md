#MIPSEM (C++)  

##Assembler, disassembler, and emulator for MIPS32 assembly   
   
>Decodes and encodes all MIPS32 instructions.  MIPS32 asm programs can be mapped to a custom .mmap file which can be mapped to MIPSEM's 32-bit addressable virtual memory system.  The virtual CPU can then execute instructions from memory by leveraging a decoded instruction cache to speed up execution.  This results in little instruction decoding overhead, as well as the ability to write self modifying code.   
  
####Implements numerous data structures for optimization such as:     
	-Hash table based instruction encoding and decoding    
	-Decoded instruction cache for less interpretation overhead within the virtual CPU   
	-Lazily allocated 32-bit addressable virtual memory system and instruction cache   
   
   
##Progress:   
1. Instruction encoding	-	*stable*     
2. Instruction decoding	-	*stable*     
3. Virtual memory system	-	*stable*     
4. Object file disk serialization	-	*stable*     
5. Object file assembly from .asm sources	-	in progress
6. Instruction emulation from memory	-	  in progress    
   
###Example program:      
.text   
addi	$t1, $zero, 48   
addi	$t0, $zero, 0   
loopstart:   
addi	$t0, $t0, 8   
addi	$v0, $zero, 1   
add	$a0, $zero, $t0   
syscall	   
beq	$t0, $t1, loopend   
j	loopstart   
loopend:    
addi	$a0, $zero, 9999	   
syscall				   		   
   
###Example output:   
![Alt text](/demos/program1output.png?raw=true)