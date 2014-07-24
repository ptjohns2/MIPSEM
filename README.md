#MIPSEM (C++)  

##Assembler and emulator for MIPS32 assembly   
   
>Decodes and encodes all MIPS32 instructions.  MIPS32 asm programs can be mapped to a custom .mmap file which can be mapped to MIPSEM's 32-bit addressable virtual memory system.  The virtual CPU can then execute instructions from memory by using a decoded instruction cache to speed up execution.  This results in no additional instruction decoding overhead within loops or function calls, as well as the ability to write self modifying code.   
   
   
##Progress:   
1. Instruction encoding	-	*stable*     
2. Instruction decoding	-	*stable*     
3. Virtual memory system	-	*stable*     
4. Object file disk serialization	-	*stable*     
5. Object file assembly from .asm sources	-	*stable*   
6. Instruction emulation from memory	-	  nearly complete for most commonly used instructions    
7. Pseudoinstruction replacement	-	*stable*    
8. Macro replacement	-	*stable*       
     
###Example MIPS32 program:               
      
 ```Assembly
#Obfuscated Hello World in MIPS32 assembly.  Uses self modifying code

####### MACROS

.eqv	INSTRUCTION_ENCODING__addi_$v0_$0_0	0x20020000	

.macro printString(%label)
	li	$t1, INSTRUCTION_ENCODING__addi_$v0_$0_0
	addi	$t1, $t1, 4
	la	$t0, nopAddr1
	sw	$t1, 0($t0)
	nopAddr1:	nop
	la	$a0, %label
	la	$t2, instructionAddr	#$t2 = instructionAddr
	lw	$t1, 0($t2)		#$t1 = *$t2 = *instructionAddr
	la	$t2, nopAddr2		#$t2 = nopAddr2
	sw	$t1, 0($t2)		#*nopAddr2 = $t1 = *$t2 = *instructionAddr
	nopAddr2:	nop
.end_macro

.macro exit()
	addi	$v0, $zero, 0xA
	syscall
.end_macro
	
####### .DATA SECTION
.data
stringAddr:		.asciiz	"Hello, World!"
instructionAddr:	.word	syscall	#encode "syscall" instruction to this word in .data section

####### .TEXT SECTION
.text
	printString(stringAddr)
	exit						
```    
      

###MIPSEM output:      
![Screenshot](/demos/selfModifyingHelloWorld_output.png?raw=true)















