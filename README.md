MIPSEM (C++)  

Assembler, disassembler, and emulator for MIPS32 assembly   
   
Decodes and encodes all MIPS32 instructions.  MIPS32 asm programs can be mapped to a custom .mmap file which can be mapped to MIPSEM's 32-bit addressable virtual memory system.  The virtual CPU can then execute instructions from memory by leveraging a decoded instruction cache to speed up execution and to allow self modifying code.   
  
Implements numerous data structures for optimization such as:     
	-Hash table based instruction encoding and decoding    
	-Decoded instruction cache for less interpretation    overhead within the virtual CPU   
	-Lazily allocated 32-bit addressable virtual memory system and instruction cache;   
   
A work in progress.     
   
Progress:   
	Instruction encoding	-	done   
	Instruction decoding	-	done	
	Virtual memory system	-	done   
	Instruction interpretation	-	  in progress    
   
Example program:   
addi 	$t1, $zero, 48	#0   
addi	$t0, $zero, 0	#4   
addi	$t0, $t0, 8	#8   
addi	$v0, $zero, 1	#12   
add	$a0, $zero, $t0	#16   
syscall			#20   
beq	$t0, $t1, 1	#24   
b	-6			#28   
addi	$a0, $zero, 999	#32   
syscall			#36   
   
Example output:   
![Alt text](/demos/program1output.png?raw=true)