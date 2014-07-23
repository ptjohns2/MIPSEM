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
5. Object file assembly from .asm sources	-	*stable*   
6. Instruction emulation from memory	-	  nearly complete for most commonly used instructions    
7. Pseudoinstruction replacement	-	*stable*    
8. Macro replacement	-	*stable*       
     
###Example program:         
      
<pre style='color:#000000;background:#ffffff;'><html><body style='color:#000000; background:#ffffff; '><pre>
#Obfuscated Hello World <span style='color:#800000; font-weight:bold; '>in</span> MIPS3<span style='color:#008c00; '>2</span> assembly.  <span style='color:#004a43; '>Uses</span> self modifying <span style='color:#004a43; '>code</span>
.eqv	INSTRUCTION_ENCODING__addi_$v0_$0_<span style='color:#008c00; '>0</span>	<span style='color:#008000; '>0x20020000</span>	

.<span style='color:#004a43; '>macro</span> printString<span style='color:#808030; '>(</span><span style='color:#808030; '>%</span><span style='color:#004a43; '>label</span><span style='color:#808030; '>)</span>
	li	$t1<span style='color:#808030; '>,</span> INSTRUCTION_ENCODING__addi_$v0_$0_<span style='color:#008c00; '>0</span>
	addi	$t1<span style='color:#808030; '>,</span> $t1<span style='color:#808030; '>,</span> <span style='color:#008c00; '>4</span>
	la	$t0<span style='color:#808030; '>,</span> nopAddr1
	sw	$t1<span style='color:#808030; '>,</span> <span style='color:#008c00; '>0</span><span style='color:#808030; '>(</span>$t0<span style='color:#808030; '>)</span>
<span style='color:#e34adc; '>	nopAddr1:</span>	<span style='color:#800000; font-weight:bold; '>nop</span>
	la	$a0<span style='color:#808030; '>,</span> <span style='color:#808030; '>%</span><span style='color:#004a43; '>label</span>
	la	$t2<span style='color:#808030; '>,</span> instructionAddr	#$t2 <span style='color:#808030; '>=</span> instructionAddr
	lw	$t1<span style='color:#808030; '>,</span> <span style='color:#008c00; '>0</span><span style='color:#808030; '>(</span>$t2<span style='color:#808030; '>)</span>		#$t1 <span style='color:#808030; '>=</span> <span style='color:#808030; '>*</span>$t2 <span style='color:#808030; '>=</span> <span style='color:#808030; '>*</span>instructionAddr
	la	$t2<span style='color:#808030; '>,</span> nopAddr2		#$t2 <span style='color:#808030; '>=</span> nopAddr2
	sw	$t1<span style='color:#808030; '>,</span> <span style='color:#008c00; '>0</span><span style='color:#808030; '>(</span>$t2<span style='color:#808030; '>)</span>		#<span style='color:#808030; '>*</span>nopAddr2 <span style='color:#808030; '>=</span> $t1 <span style='color:#808030; '>=</span> <span style='color:#808030; '>*</span>$t2 <span style='color:#808030; '>=</span> <span style='color:#808030; '>*</span>instructionAddr
<span style='color:#e34adc; '>	nopAddr2:</span>	<span style='color:#800000; font-weight:bold; '>nop</span>
.end_macro

.<span style='color:#004a43; '>macro</span> exit<span style='color:#808030; '>(</span><span style='color:#808030; '>)</span>
	addi	$v0<span style='color:#808030; '>,</span> $zero<span style='color:#808030; '>,</span> <span style='color:#008000; '>0xA</span>
	<span style='color:#bb7977; font-weight:bold; '>syscall</span>
.end_macro
	


<span style='color:#004a43; '>.data</span>
<span style='color:#e34adc; '>stringAddr:</span>		.asciiz	<span style='color:#0000e6; '>"Self modifying Hello, World! program in MIPS32"</span>
<span style='color:#e34adc; '>instructionAddr:</span>	.<span style='color:#800000; font-weight:bold; '>word</span>	<span style='color:#bb7977; font-weight:bold; '>syscall</span>	#encode <span style='color:#0000e6; '>"syscall"</span> instruction to <span style='color:#004a43; '>this</span> <span style='color:#800000; font-weight:bold; '>word</span> <span style='color:#800000; font-weight:bold; '>in</span> <span style='color:#004a43; '>.data</span> <span style='color:#004a43; '>section</span>

.text
	printString<span style='color:#808030; '>(</span>stringAddr<span style='color:#808030; '>)</span>
	exit<span style='color:#808030; '>(</span><span style='color:#808030; '>)</span>
</pre></pre>
	   	   		   
      
###Example output:      
![Alt text](/demos/program1output.png?raw=true)















