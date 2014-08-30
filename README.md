#MIPSEM (C++)  

##Assembler and emulator for MIPS32 assembly   
   
>Decodes and encodes all MIPS32 instructions.  MIPS32 asm programs can be mapped to a custom file format which can be mapped to MIPSEM's 32-bit addressable virtual memory system.  The virtual CPU can then execute instructions from memory by using a decoded instruction cache to speed up execution.  This results in no additional instruction decoding overhead within loops or consecutively called function calls.  Cache coherency is also implemented in the instruction decoder cache to make sure that self modifying MIPS32 code can be written.   
   
>The GUI written using the Qt framework allows editing of multiple MIPS32 assembly files at once via tabs.  Includes a syntax highlighter which can be customized to the user's liking.  Using the F5 hotkey attempts to assemble the object file, and if successful this also executes it using the MIPSEM_CORE executable, the cross platform MIPS32 assembly emulator.  

>MIPSEMobj programs can be run by hand using its CLI by passing it one argument: the directory of the MIPSEMobj file you want to execute.

>The assembler has helpful error messages to aid in debugging with an output console allowing you to click on the error and be brought to the file and line where the error occurs.  
   
Uses only Qt and the C++ standard library.  Distributed under the MIT license.  
   
      
![Screenshot](/demos/GUI.png?raw=true)   
   
   
#####Example MIPS32 program ran above:               
      
 ```Assembly
#Obfuscated Hello World in MIPS32 assembly.  Uses self modifying code

####### MACROS

.eqv	INSTRUCTION_ENCODING__addi_$v0_$0_0	0x20020000	

.macro printString(%label)	
	li	$t1, INSTRUCTION_ENCODING__addi_$v0_$0_0
	addi	$t1, $t1, 0b0100	#binary literals supported
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
	
.data	####### .DATA SECTION

stringAddr:		.asciiz	"Self modifying Hello, World! program in MIPS32"

#encode "syscall" instruction to this word in .data section
instructionAddr:	.word	syscall	

.text	####### .TEXT SECTION
main:
	printString(stringAddr)
	exit	# syscall #10
```    











