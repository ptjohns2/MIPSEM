#include "CPU.hpp"

#include "BitManip.hpp"
#include "VirtualMemory.hpp"

#include <bitset>
#include <iostream>
#include <math.h>

#pragma warning(disable: 4100)	//Warning: unreferenced formal parameter

typedef enum {
	$zero = 0, 
	$at, 
	$v0, $v1, 
	$a0, $a1, $a2, $a3, 
	$t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7,
	$s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7,
	$t8, $t9,
	$k0, $k1,
	$gp, $sp, $fp, $ra
} registersNames;


//	Constructors
CPU::CPU()
	:	parser()
{
	for(int i=0; i<32; i++){
		GPR[i] = 0x0;
		FPR[i] = 0x0;
	}
	GPR[$gp] = MEMPTR_GP;
	GPR[$sp] = MEMPTR_SP;
	PC = MEMPTR_PC;
	HI = 0;
	LO = 0;
	exitProgram = false;
}

CPU::~CPU(){}

void CPU::run(){
	while(!exitProgram){
		executeInstructionAtPC();
	}
}
void CPU::executeInstructionAtPC(){
	Instruction* instructionFromMemory = MEM.readInstruction(PC);
	cout << "\nPC = " << parser.literals.getHexLiteralString(PC) << '\t' << instructionFromMemory->getAsmString() << "\t\t\t\t";
	executeInstruction(instructionFromMemory);
}
void CPU::executeInstruction(Instruction* instruction){
	//Get necessary data
	InstructionData* instructionData = instruction->getInstructionData();
	int instructionId = instructionData->getID();
	int32_t a0 = instruction->getTokenValue(0);
	int32_t a1 = instruction->getTokenValue(1);
	int32_t a2 = instruction->getTokenValue(2);
	int32_t a3 = instruction->getTokenValue(3);
	
	//PC incrementation
	if(!instructionData->isJump()){
		PC += 4;
	}

	//Execute the right instruction
	switch(instructionId){
		case 0 : {executeInstructionID_0(a0, a1, a2, a3);break;}
		case 1 : {executeInstructionID_1(a0, a1, a2, a3);break;}
		case 2 : {executeInstructionID_2(a0, a1, a2, a3);break;}
		case 3 : {executeInstructionID_3(a0, a1, a2, a3);break;}
		case 4 : {executeInstructionID_4(a0, a1, a2, a3);break;}
		case 5 : {executeInstructionID_5(a0, a1, a2, a3);break;}
		case 6 : {executeInstructionID_6(a0, a1, a2, a3);break;}
		case 7 : {executeInstructionID_7(a0, a1, a2, a3);break;}
		case 8 : {executeInstructionID_8(a0, a1, a2, a3);break;}
		case 9 : {executeInstructionID_9(a0, a1, a2, a3);break;}
		case 10 : {executeInstructionID_10(a0, a1, a2, a3);break;}
		case 11 : {executeInstructionID_11(a0, a1, a2, a3);break;}
		case 12 : {executeInstructionID_12(a0, a1, a2, a3);break;}
		case 13 : {executeInstructionID_13(a0, a1, a2, a3);break;}
		case 14 : {executeInstructionID_14(a0, a1, a2, a3);break;}
		case 15 : {executeInstructionID_15(a0, a1, a2, a3);break;}
		case 16 : {executeInstructionID_16(a0, a1, a2, a3);break;}
		case 17 : {executeInstructionID_17(a0, a1, a2, a3);break;}
		case 18 : {executeInstructionID_18(a0, a1, a2, a3);break;}
		case 19 : {executeInstructionID_19(a0, a1, a2, a3);break;}
		case 20 : {executeInstructionID_20(a0, a1, a2, a3);break;}
		case 21 : {executeInstructionID_21(a0, a1, a2, a3);break;}
		case 22 : {executeInstructionID_22(a0, a1, a2, a3);break;}
		case 23 : {executeInstructionID_23(a0, a1, a2, a3);break;}
		case 24 : {executeInstructionID_24(a0, a1, a2, a3);break;}
		case 25 : {executeInstructionID_25(a0, a1, a2, a3);break;}
		case 26 : {executeInstructionID_26(a0, a1, a2, a3);break;}
		case 27 : {executeInstructionID_27(a0, a1, a2, a3);break;}
		case 28 : {executeInstructionID_28(a0, a1, a2, a3);break;}
		case 29 : {executeInstructionID_29(a0, a1, a2, a3);break;}
		case 30 : {executeInstructionID_30(a0, a1, a2, a3);break;}
		case 31 : {executeInstructionID_31(a0, a1, a2, a3);break;}
		case 32 : {executeInstructionID_32(a0, a1, a2, a3);break;}
		case 33 : {executeInstructionID_33(a0, a1, a2, a3);break;}
		case 34 : {executeInstructionID_34(a0, a1, a2, a3);break;}
		case 35 : {executeInstructionID_35(a0, a1, a2, a3);break;}
		case 36 : {executeInstructionID_36(a0, a1, a2, a3);break;}
		case 37 : {executeInstructionID_37(a0, a1, a2, a3);break;}
		case 38 : {executeInstructionID_38(a0, a1, a2, a3);break;}
		case 39 : {executeInstructionID_39(a0, a1, a2, a3);break;}
		case 40 : {executeInstructionID_40(a0, a1, a2, a3);break;}
		case 41 : {executeInstructionID_41(a0, a1, a2, a3);break;}
		case 42 : {executeInstructionID_42(a0, a1, a2, a3);break;}
		case 43 : {executeInstructionID_43(a0, a1, a2, a3);break;}
		case 44 : {executeInstructionID_44(a0, a1, a2, a3);break;}
		case 45 : {executeInstructionID_45(a0, a1, a2, a3);break;}
		case 46 : {executeInstructionID_46(a0, a1, a2, a3);break;}
		case 47 : {executeInstructionID_47(a0, a1, a2, a3);break;}
		case 48 : {executeInstructionID_48(a0, a1, a2, a3);break;}
		case 49 : {executeInstructionID_49(a0, a1, a2, a3);break;}
		case 50 : {executeInstructionID_50(a0, a1, a2, a3);break;}
		case 51 : {executeInstructionID_51(a0, a1, a2, a3);break;}
		case 52 : {executeInstructionID_52(a0, a1, a2, a3);break;}
		case 53 : {executeInstructionID_53(a0, a1, a2, a3);break;}
		case 54 : {executeInstructionID_54(a0, a1, a2, a3);break;}
		case 55 : {executeInstructionID_55(a0, a1, a2, a3);break;}
		case 56 : {executeInstructionID_56(a0, a1, a2, a3);break;}
		case 57 : {executeInstructionID_57(a0, a1, a2, a3);break;}
		case 58 : {executeInstructionID_58(a0, a1, a2, a3);break;}
		case 59 : {executeInstructionID_59(a0, a1, a2, a3);break;}
		case 60 : {executeInstructionID_60(a0, a1, a2, a3);break;}
		case 61 : {executeInstructionID_61(a0, a1, a2, a3);break;}
		case 62 : {executeInstructionID_62(a0, a1, a2, a3);break;}
		case 63 : {executeInstructionID_63(a0, a1, a2, a3);break;}
		case 64 : {executeInstructionID_64(a0, a1, a2, a3);break;}
		case 65 : {executeInstructionID_65(a0, a1, a2, a3);break;}
		case 66 : {executeInstructionID_66(a0, a1, a2, a3);break;}
		case 67 : {executeInstructionID_67(a0, a1, a2, a3);break;}
		case 68 : {executeInstructionID_68(a0, a1, a2, a3);break;}
		case 69 : {executeInstructionID_69(a0, a1, a2, a3);break;}
		case 70 : {executeInstructionID_70(a0, a1, a2, a3);break;}
		case 71 : {executeInstructionID_71(a0, a1, a2, a3);break;}
		case 72 : {executeInstructionID_72(a0, a1, a2, a3);break;}
		case 73 : {executeInstructionID_73(a0, a1, a2, a3);break;}
		case 74 : {executeInstructionID_74(a0, a1, a2, a3);break;}
		case 75 : {executeInstructionID_75(a0, a1, a2, a3);break;}
		case 76 : {executeInstructionID_76(a0, a1, a2, a3);break;}
		case 77 : {executeInstructionID_77(a0, a1, a2, a3);break;}
		case 78 : {executeInstructionID_78(a0, a1, a2, a3);break;}
		case 79 : {executeInstructionID_79(a0, a1, a2, a3);break;}
		case 80 : {executeInstructionID_80(a0, a1, a2, a3);break;}
		case 81 : {executeInstructionID_81(a0, a1, a2, a3);break;}
		case 82 : {executeInstructionID_82(a0, a1, a2, a3);break;}
		case 83 : {executeInstructionID_83(a0, a1, a2, a3);break;}
		case 84 : {executeInstructionID_84(a0, a1, a2, a3);break;}
		case 85 : {executeInstructionID_85(a0, a1, a2, a3);break;}
		case 86 : {executeInstructionID_86(a0, a1, a2, a3);break;}
		case 87 : {executeInstructionID_87(a0, a1, a2, a3);break;}
		case 88 : {executeInstructionID_88(a0, a1, a2, a3);break;}
		case 89 : {executeInstructionID_89(a0, a1, a2, a3);break;}
		case 90 : {executeInstructionID_90(a0, a1, a2, a3);break;}
		case 91 : {executeInstructionID_91(a0, a1, a2, a3);break;}
		case 92 : {executeInstructionID_92(a0, a1, a2, a3);break;}
		case 93 : {executeInstructionID_93(a0, a1, a2, a3);break;}
		case 94 : {executeInstructionID_94(a0, a1, a2, a3);break;}
		case 95 : {executeInstructionID_95(a0, a1, a2, a3);break;}
		case 96 : {executeInstructionID_96(a0, a1, a2, a3);break;}
		case 97 : {executeInstructionID_97(a0, a1, a2, a3);break;}
		case 98 : {executeInstructionID_98(a0, a1, a2, a3);break;}
		case 99 : {executeInstructionID_99(a0, a1, a2, a3);break;}
		case 100 : {executeInstructionID_100(a0, a1, a2, a3);break;}
		case 101 : {executeInstructionID_101(a0, a1, a2, a3);break;}
		case 102 : {executeInstructionID_102(a0, a1, a2, a3);break;}
		case 103 : {executeInstructionID_103(a0, a1, a2, a3);break;}
		case 104 : {executeInstructionID_104(a0, a1, a2, a3);break;}
		case 105 : {executeInstructionID_105(a0, a1, a2, a3);break;}
		case 106 : {executeInstructionID_106(a0, a1, a2, a3);break;}
		case 107 : {executeInstructionID_107(a0, a1, a2, a3);break;}
		case 108 : {executeInstructionID_108(a0, a1, a2, a3);break;}
		case 109 : {executeInstructionID_109(a0, a1, a2, a3);break;}
		case 110 : {executeInstructionID_110(a0, a1, a2, a3);break;}
		case 111 : {executeInstructionID_111(a0, a1, a2, a3);break;}
		case 112 : {executeInstructionID_112(a0, a1, a2, a3);break;}
		case 113 : {executeInstructionID_113(a0, a1, a2, a3);break;}
		case 114 : {executeInstructionID_114(a0, a1, a2, a3);break;}
		case 115 : {executeInstructionID_115(a0, a1, a2, a3);break;}
		case 116 : {executeInstructionID_116(a0, a1, a2, a3);break;}
		case 117 : {executeInstructionID_117(a0, a1, a2, a3);break;}
		case 118 : {executeInstructionID_118(a0, a1, a2, a3);break;}
		case 119 : {executeInstructionID_119(a0, a1, a2, a3);break;}
		case 120 : {executeInstructionID_120(a0, a1, a2, a3);break;}
		case 121 : {executeInstructionID_121(a0, a1, a2, a3);break;}
		case 122 : {executeInstructionID_122(a0, a1, a2, a3);break;}
		case 123 : {executeInstructionID_123(a0, a1, a2, a3);break;}
		case 124 : {executeInstructionID_124(a0, a1, a2, a3);break;}
		case 125 : {executeInstructionID_125(a0, a1, a2, a3);break;}
		case 126 : {executeInstructionID_126(a0, a1, a2, a3);break;}
		case 127 : {executeInstructionID_127(a0, a1, a2, a3);break;}
		case 128 : {executeInstructionID_128(a0, a1, a2, a3);break;}
		case 129 : {executeInstructionID_129(a0, a1, a2, a3);break;}
		case 130 : {executeInstructionID_130(a0, a1, a2, a3);break;}
		case 131 : {executeInstructionID_131(a0, a1, a2, a3);break;}
		case 132 : {executeInstructionID_132(a0, a1, a2, a3);break;}
		case 133 : {executeInstructionID_133(a0, a1, a2, a3);break;}
		case 134 : {executeInstructionID_134(a0, a1, a2, a3);break;}
		case 135 : {executeInstructionID_135(a0, a1, a2, a3);break;}
		case 136 : {executeInstructionID_136(a0, a1, a2, a3);break;}
		case 137 : {executeInstructionID_137(a0, a1, a2, a3);break;}
		case 138 : {executeInstructionID_138(a0, a1, a2, a3);break;}
		case 139 : {executeInstructionID_139(a0, a1, a2, a3);break;}
		case 140 : {executeInstructionID_140(a0, a1, a2, a3);break;}
		case 141 : {executeInstructionID_141(a0, a1, a2, a3);break;}
		case 142 : {executeInstructionID_142(a0, a1, a2, a3);break;}
		case 143 : {executeInstructionID_143(a0, a1, a2, a3);break;}
		case 144 : {executeInstructionID_144(a0, a1, a2, a3);break;}
		case 145 : {executeInstructionID_145(a0, a1, a2, a3);break;}
		case 146 : {executeInstructionID_146(a0, a1, a2, a3);break;}
		case 147 : {executeInstructionID_147(a0, a1, a2, a3);break;}
		case 148 : {executeInstructionID_148(a0, a1, a2, a3);break;}
		case 149 : {executeInstructionID_149(a0, a1, a2, a3);break;}
		case 150 : {executeInstructionID_150(a0, a1, a2, a3);break;}
		case 151 : {executeInstructionID_151(a0, a1, a2, a3);break;}
		case 152 : {executeInstructionID_152(a0, a1, a2, a3);break;}
		case 153 : {executeInstructionID_153(a0, a1, a2, a3);break;}
		case 154 : {executeInstructionID_154(a0, a1, a2, a3);break;}
		case 155 : {executeInstructionID_155(a0, a1, a2, a3);break;}
		case 156 : {executeInstructionID_156(a0, a1, a2, a3);break;}
		case 157 : {executeInstructionID_157(a0, a1, a2, a3);break;}
		case 158 : {executeInstructionID_158(a0, a1, a2, a3);break;}
		case 159 : {executeInstructionID_159(a0, a1, a2, a3);break;}
		case 160 : {executeInstructionID_160(a0, a1, a2, a3);break;}
		case 161 : {executeInstructionID_161(a0, a1, a2, a3);break;}
		case 162 : {executeInstructionID_162(a0, a1, a2, a3);break;}
		case 163 : {executeInstructionID_163(a0, a1, a2, a3);break;}
		case 164 : {executeInstructionID_164(a0, a1, a2, a3);break;}
		case 165 : {executeInstructionID_165(a0, a1, a2, a3);break;}
		case 166 : {executeInstructionID_166(a0, a1, a2, a3);break;}
		case 167 : {executeInstructionID_167(a0, a1, a2, a3);break;}
		case 168 : {executeInstructionID_168(a0, a1, a2, a3);break;}
		case 169 : {executeInstructionID_169(a0, a1, a2, a3);break;}
		case 170 : {executeInstructionID_170(a0, a1, a2, a3);break;}
		case 171 : {executeInstructionID_171(a0, a1, a2, a3);break;}
		case 172 : {executeInstructionID_172(a0, a1, a2, a3);break;}
		case 173 : {executeInstructionID_173(a0, a1, a2, a3);break;}
		case 174 : {executeInstructionID_174(a0, a1, a2, a3);break;}
		case 175 : {executeInstructionID_175(a0, a1, a2, a3);break;}
		case 176 : {executeInstructionID_176(a0, a1, a2, a3);break;}
		case 177 : {executeInstructionID_177(a0, a1, a2, a3);break;}
		case 178 : {executeInstructionID_178(a0, a1, a2, a3);break;}
		case 179 : {executeInstructionID_179(a0, a1, a2, a3);break;}
		case 180 : {executeInstructionID_180(a0, a1, a2, a3);break;}
		case 181 : {executeInstructionID_181(a0, a1, a2, a3);break;}
		case 182 : {executeInstructionID_182(a0, a1, a2, a3);break;}
		case 183 : {executeInstructionID_183(a0, a1, a2, a3);break;}
		case 184 : {executeInstructionID_184(a0, a1, a2, a3);break;}
		case 185 : {executeInstructionID_185(a0, a1, a2, a3);break;}
		case 186 : {executeInstructionID_186(a0, a1, a2, a3);break;}
		case 187 : {executeInstructionID_187(a0, a1, a2, a3);break;}
		case 188 : {executeInstructionID_188(a0, a1, a2, a3);break;}
		case 189 : {executeInstructionID_189(a0, a1, a2, a3);break;}
		case 190 : {executeInstructionID_190(a0, a1, a2, a3);break;}
		case 191 : {executeInstructionID_191(a0, a1, a2, a3);break;}
		case 192 : {executeInstructionID_192(a0, a1, a2, a3);break;}
		case 193 : {executeInstructionID_193(a0, a1, a2, a3);break;}
		case 194 : {executeInstructionID_194(a0, a1, a2, a3);break;}
		case 195 : {executeInstructionID_195(a0, a1, a2, a3);break;}
		case 196 : {executeInstructionID_196(a0, a1, a2, a3);break;}
		case 197 : {executeInstructionID_197(a0, a1, a2, a3);break;}
		case 198 : {executeInstructionID_198(a0, a1, a2, a3);break;}
		case 199 : {executeInstructionID_199(a0, a1, a2, a3);break;}
		case 200 : {executeInstructionID_200(a0, a1, a2, a3);break;}
		case 201 : {executeInstructionID_201(a0, a1, a2, a3);break;}
		case 202 : {executeInstructionID_202(a0, a1, a2, a3);break;}
		case 203 : {executeInstructionID_203(a0, a1, a2, a3);break;}
		case 204 : {executeInstructionID_204(a0, a1, a2, a3);break;}
		case 205 : {executeInstructionID_205(a0, a1, a2, a3);break;}
		case 206 : {executeInstructionID_206(a0, a1, a2, a3);break;}
		case 207 : {executeInstructionID_207(a0, a1, a2, a3);break;}
		case 208 : {executeInstructionID_208(a0, a1, a2, a3);break;}
		case 209 : {executeInstructionID_209(a0, a1, a2, a3);break;}
		case 210 : {executeInstructionID_210(a0, a1, a2, a3);break;}
		case 211 : {executeInstructionID_211(a0, a1, a2, a3);break;}
		case 212 : {executeInstructionID_212(a0, a1, a2, a3);break;}
		case 213 : {executeInstructionID_213(a0, a1, a2, a3);break;}
		case 214 : {executeInstructionID_214(a0, a1, a2, a3);break;}
		case 215 : {executeInstructionID_215(a0, a1, a2, a3);break;}
		case 216 : {executeInstructionID_216(a0, a1, a2, a3);break;}
		case 217 : {executeInstructionID_217(a0, a1, a2, a3);break;}
		case 218 : {executeInstructionID_218(a0, a1, a2, a3);break;}
		case 219 : {executeInstructionID_219(a0, a1, a2, a3);break;}
		case 220 : {executeInstructionID_220(a0, a1, a2, a3);break;}
		case 221 : {executeInstructionID_221(a0, a1, a2, a3);break;}
		case 222 : {executeInstructionID_222(a0, a1, a2, a3);break;}
		case 223 : {executeInstructionID_223(a0, a1, a2, a3);break;}
		case 224 : {executeInstructionID_224(a0, a1, a2, a3);break;}
		case 225 : {executeInstructionID_225(a0, a1, a2, a3);break;}
		case 226 : {executeInstructionID_226(a0, a1, a2, a3);break;}
		case 227 : {executeInstructionID_227(a0, a1, a2, a3);break;}
		case 228 : {executeInstructionID_228(a0, a1, a2, a3);break;}
		case 229 : {executeInstructionID_229(a0, a1, a2, a3);break;}
		case 230 : {executeInstructionID_230(a0, a1, a2, a3);break;}
		case 231 : {executeInstructionID_231(a0, a1, a2, a3);break;}
		case 232 : {executeInstructionID_232(a0, a1, a2, a3);break;}
		case 233 : {executeInstructionID_233(a0, a1, a2, a3);break;}
		case 234 : {executeInstructionID_234(a0, a1, a2, a3);break;}
		case 235 : {executeInstructionID_235(a0, a1, a2, a3);break;}
		case 236 : {executeInstructionID_236(a0, a1, a2, a3);break;}
		case 237 : {executeInstructionID_237(a0, a1, a2, a3);break;}
		case 238 : {executeInstructionID_238(a0, a1, a2, a3);break;}
		case 239 : {executeInstructionID_239(a0, a1, a2, a3);break;}
		case 240 : {executeInstructionID_240(a0, a1, a2, a3);break;}
		case 241 : {executeInstructionID_241(a0, a1, a2, a3);break;}
		case 242 : {executeInstructionID_242(a0, a1, a2, a3);break;}
		case 243 : {executeInstructionID_243(a0, a1, a2, a3);break;}
		case 244 : {executeInstructionID_244(a0, a1, a2, a3);break;}
		case 245 : {executeInstructionID_245(a0, a1, a2, a3);break;}
		case 246 : {executeInstructionID_246(a0, a1, a2, a3);break;}
		case 247 : {executeInstructionID_247(a0, a1, a2, a3);break;}
		case 248 : {executeInstructionID_248(a0, a1, a2, a3);break;}
		case 249 : {executeInstructionID_249(a0, a1, a2, a3);break;}
		case 250 : {executeInstructionID_250(a0, a1, a2, a3);break;}
		case 251 : {executeInstructionID_251(a0, a1, a2, a3);break;}
		case 252 : {executeInstructionID_252(a0, a1, a2, a3);break;}
		case 253 : {executeInstructionID_253(a0, a1, a2, a3);break;}
		case 254 : {executeInstructionID_254(a0, a1, a2, a3);break;}
		case 255 : {executeInstructionID_255(a0, a1, a2, a3);break;}
		case 256 : {executeInstructionID_256(a0, a1, a2, a3);break;}
		case 257 : {executeInstructionID_257(a0, a1, a2, a3);break;}
		case 258 : {executeInstructionID_258(a0, a1, a2, a3);break;}
		case 259 : {executeInstructionID_259(a0, a1, a2, a3);break;}
		case 260 : {executeInstructionID_260(a0, a1, a2, a3);break;}
		case 261 : {executeInstructionID_261(a0, a1, a2, a3);break;}
		case 262 : {executeInstructionID_262(a0, a1, a2, a3);break;}
		case 263 : {executeInstructionID_263(a0, a1, a2, a3);break;}
		case 264 : {executeInstructionID_264(a0, a1, a2, a3);break;}
		case 265 : {executeInstructionID_265(a0, a1, a2, a3);break;}
		case 266 : {executeInstructionID_266(a0, a1, a2, a3);break;}
		case 267 : {executeInstructionID_267(a0, a1, a2, a3);break;}
		case 268 : {executeInstructionID_268(a0, a1, a2, a3);break;}
		case 269 : {executeInstructionID_269(a0, a1, a2, a3);break;}
		case 270 : {executeInstructionID_270(a0, a1, a2, a3);break;}
		case 271 : {executeInstructionID_271(a0, a1, a2, a3);break;}
		case 272 : {executeInstructionID_272(a0, a1, a2, a3);break;}
		case 273 : {executeInstructionID_273(a0, a1, a2, a3);break;}
		case 274 : {executeInstructionID_274(a0, a1, a2, a3);break;}
		case 275 : {executeInstructionID_275(a0, a1, a2, a3);break;}
		case 276 : {executeInstructionID_276(a0, a1, a2, a3);break;}
		case 277 : {executeInstructionID_277(a0, a1, a2, a3);break;}
		case 278 : {executeInstructionID_278(a0, a1, a2, a3);break;}
		case 279 : {executeInstructionID_279(a0, a1, a2, a3);break;}
		case 280 : {executeInstructionID_280(a0, a1, a2, a3);break;}
		case 281 : {executeInstructionID_281(a0, a1, a2, a3);break;}
		case 282 : {executeInstructionID_282(a0, a1, a2, a3);break;}
		case 283 : {executeInstructionID_283(a0, a1, a2, a3);break;}
		case 284 : {executeInstructionID_284(a0, a1, a2, a3);break;}
		case 285 : {executeInstructionID_285(a0, a1, a2, a3);break;}
		case 286 : {executeInstructionID_286(a0, a1, a2, a3);break;}
		case 287 : {executeInstructionID_287(a0, a1, a2, a3);break;}
		case 288 : {executeInstructionID_288(a0, a1, a2, a3);break;}
		case 289 : {executeInstructionID_289(a0, a1, a2, a3);break;}
		case 290 : {executeInstructionID_290(a0, a1, a2, a3);break;}
		case 291 : {executeInstructionID_291(a0, a1, a2, a3);break;}
		case 292 : {executeInstructionID_292(a0, a1, a2, a3);break;}
		case 293 : {executeInstructionID_293(a0, a1, a2, a3);break;}
		case 294 : {executeInstructionID_294(a0, a1, a2, a3);break;}
		case 295 : {executeInstructionID_295(a0, a1, a2, a3);break;}
		case 296 : {executeInstructionID_296(a0, a1, a2, a3);break;}
		case 297 : {executeInstructionID_297(a0, a1, a2, a3);break;}
		case 298 : {executeInstructionID_298(a0, a1, a2, a3);break;}
		case 299 : {executeInstructionID_299(a0, a1, a2, a3);break;}
		case 300 : {executeInstructionID_300(a0, a1, a2, a3);break;}
		case 301 : {executeInstructionID_301(a0, a1, a2, a3);break;}
		case 302 : {executeInstructionID_302(a0, a1, a2, a3);break;}
		case 303 : {executeInstructionID_303(a0, a1, a2, a3);break;}
		case 304 : {executeInstructionID_304(a0, a1, a2, a3);break;}
		case 305 : {executeInstructionID_305(a0, a1, a2, a3);break;}
		case 306 : {executeInstructionID_306(a0, a1, a2, a3);break;}
		case 307 : {executeInstructionID_307(a0, a1, a2, a3);break;}
		case 308 : {executeInstructionID_308(a0, a1, a2, a3);break;}
		case 309 : {executeInstructionID_309(a0, a1, a2, a3);break;}
		case 310 : {executeInstructionID_310(a0, a1, a2, a3);break;}
		case 311 : {executeInstructionID_311(a0, a1, a2, a3);break;}
		case 312 : {executeInstructionID_312(a0, a1, a2, a3);break;}
		case 313 : {executeInstructionID_313(a0, a1, a2, a3);break;}
		case 314 : {executeInstructionID_314(a0, a1, a2, a3);break;}
		case 315 : {executeInstructionID_315(a0, a1, a2, a3);break;}
		case 316 : {executeInstructionID_316(a0, a1, a2, a3);break;}
		case 317 : {executeInstructionID_317(a0, a1, a2, a3);break;}
		case 318 : {executeInstructionID_318(a0, a1, a2, a3);break;}
		case 319 : {executeInstructionID_319(a0, a1, a2, a3);break;}
		case 320 : {executeInstructionID_320(a0, a1, a2, a3);break;}
		case 321 : {executeInstructionID_321(a0, a1, a2, a3);break;}
		case 322 : {executeInstructionID_322(a0, a1, a2, a3);break;}
		case 323 : {executeInstructionID_323(a0, a1, a2, a3);break;}
		case 324 : {executeInstructionID_324(a0, a1, a2, a3);break;}
		case 325 : {executeInstructionID_325(a0, a1, a2, a3);break;}
		case 326 : {executeInstructionID_326(a0, a1, a2, a3);break;}
		case 327 : {executeInstructionID_327(a0, a1, a2, a3);break;}
		case 328 : {executeInstructionID_328(a0, a1, a2, a3);break;}
		case 329 : {executeInstructionID_329(a0, a1, a2, a3);break;}
		case 330 : {executeInstructionID_330(a0, a1, a2, a3);break;}
		case 331 : {executeInstructionID_331(a0, a1, a2, a3);break;}
		case 332 : {executeInstructionID_332(a0, a1, a2, a3);break;}
		case 333 : {executeInstructionID_333(a0, a1, a2, a3);break;}
		case 334 : {executeInstructionID_334(a0, a1, a2, a3);break;}
		case 335 : {executeInstructionID_335(a0, a1, a2, a3);break;}
		case 336 : {executeInstructionID_336(a0, a1, a2, a3);break;}
		case 337 : {executeInstructionID_337(a0, a1, a2, a3);break;}
		case 338 : {executeInstructionID_338(a0, a1, a2, a3);break;}
		case 339 : {executeInstructionID_339(a0, a1, a2, a3);break;}
		case 340 : {executeInstructionID_340(a0, a1, a2, a3);break;}
		case 341 : {executeInstructionID_341(a0, a1, a2, a3);break;}
		case 342 : {executeInstructionID_342(a0, a1, a2, a3);break;}
		case 343 : {executeInstructionID_343(a0, a1, a2, a3);break;}
		case 344 : {executeInstructionID_344(a0, a1, a2, a3);break;}
		case 345 : {executeInstructionID_345(a0, a1, a2, a3);break;}
		case 346 : {executeInstructionID_346(a0, a1, a2, a3);break;}
		case 347 : {executeInstructionID_347(a0, a1, a2, a3);break;}
		case 348 : {executeInstructionID_348(a0, a1, a2, a3);break;}
		case 349 : {executeInstructionID_349(a0, a1, a2, a3);break;}
		case 350 : {executeInstructionID_350(a0, a1, a2, a3);break;}
		case 351 : {executeInstructionID_351(a0, a1, a2, a3);break;}
		case 352 : {executeInstructionID_352(a0, a1, a2, a3);break;}
		case 353 : {executeInstructionID_353(a0, a1, a2, a3);break;}
		case 354 : {executeInstructionID_354(a0, a1, a2, a3);break;}
		case 355 : {executeInstructionID_355(a0, a1, a2, a3);break;}
		case 356 : {executeInstructionID_356(a0, a1, a2, a3);break;}
		case 357 : {executeInstructionID_357(a0, a1, a2, a3);break;}
		case 358 : {executeInstructionID_358(a0, a1, a2, a3);break;}
		case 359 : {executeInstructionID_359(a0, a1, a2, a3);break;}
		case 360 : {executeInstructionID_360(a0, a1, a2, a3);break;}
		case 361 : {executeInstructionID_361(a0, a1, a2, a3);break;}
		case 362 : {executeInstructionID_362(a0, a1, a2, a3);break;}
		case 363 : {executeInstructionID_363(a0, a1, a2, a3);break;}
		case 364 : {executeInstructionID_364(a0, a1, a2, a3);break;}
		case 365 : {executeInstructionID_365(a0, a1, a2, a3);break;}
		case 366 : {executeInstructionID_366(a0, a1, a2, a3);break;}
		case 367 : {executeInstructionID_367(a0, a1, a2, a3);break;}
		case 368 : {executeInstructionID_368(a0, a1, a2, a3);break;}
		case 369 : {executeInstructionID_369(a0, a1, a2, a3);break;}
		case 370 : {executeInstructionID_370(a0, a1, a2, a3);break;}
		case 371 : {executeInstructionID_371(a0, a1, a2, a3);break;}
		case 372 : {executeInstructionID_372(a0, a1, a2, a3);break;}
		case 373 : {executeInstructionID_373(a0, a1, a2, a3);break;}
		case 374 : {executeInstructionID_374(a0, a1, a2, a3);break;}
		case 375 : {executeInstructionID_375(a0, a1, a2, a3);break;}
		case 376 : {executeInstructionID_376(a0, a1, a2, a3);break;}
	}
	

	//make sure $zero stays 0
	GPR[$zero] = 0;
}


inline void CPU::regStoreDouble(double val, uint32_t index){
	FPR[index] = splitToUpperHalf<float, double>(val);
	FPR[(index+1) % 32] = splitToLowerHalf<float, double>(val);
}

inline double CPU::regReadDouble(uint32_t index){
	float arr[2];
	arr[0] = FPR[index];
	arr[1] = FPR[(index+1) % 32];
	return readMemAs<double>(&arr[0]);
}




//==================================================>	
//==================================================>	INSTRUCTIONS
//==================================================>	INSTRUCTIONS
//==================================================>	INSTRUCTIONS
//==================================================>	INSTRUCTIONS
//==================================================>	INSTRUCTIONS
//==================================================>	INSTRUCTIONS
//==================================================>	

inline void CPU::executeInstructionID_0(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	0	=	ABS.S	:	$fd,	$fs,	_,	_	
	FPR[a0] = std::abs(FPR[a1]);
}
inline void CPU::executeInstructionID_1(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	1	=	ABS.D	:	$fd,	$fs,	_,	_
	double doubleVal = concatenateBitPair<float, double>(FPR[a1], FPR[(a1+1) % 32]);
	doubleVal = std::abs(doubleVal);
	regStoreDouble(doubleVal, a0);
}
inline void CPU::executeInstructionID_2(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	2	=	ABS.PS	:	$fd,	$fs,	_,	_			
	FPR[a0] = std::abs(FPR[a1]);
	FPR[(a0+1) % 32] = std::abs(FPR[(a1+1) % 32]);
}
inline void CPU::executeInstructionID_3(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	3	=	ADD	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] + GPR[a2];
}
inline void CPU::executeInstructionID_4(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	4	=	ADD.S	:	$fd,	$ft,	$fs,	_		
	FPR[a0] = FPR[a1] + FPR[a2];
}
inline void CPU::executeInstructionID_5(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	5	=	ADD.D	:	$fd,	$ft,	$fs,	_		
	double doubleVal1 = concatenateBitPair<float, double>(FPR[a1], FPR[(a1+1) % 32]);
	double doubleVal2 = concatenateBitPair<float, double>(FPR[a2], FPR[(a2+1) % 32]);
	double sum = doubleVal1 + doubleVal2;
	regStoreDouble(sum, a0);
}
inline void CPU::executeInstructionID_6(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	6	=	ADD.PS	:	$fd,	$ft,	$fs,	_	
	FPR[a0] = FPR[a1] + FPR[a2];
	FPR[(a0+1) % 32] = FPR[(a1+1) % 32] + FPR[(a2+1) % 32];
}
inline void CPU::executeInstructionID_7(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	7	=	ADDI	:	$rt,	$rs,	-.imm,	_		
	GPR[a0] = GPR[a1] + signExtend(a2, 16);
}
inline void CPU::executeInstructionID_8(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	8	=	ADDIU	:	$rt,	$rs,	+.imm,	_		
	GPR[a0] = GPR[a1] + signExtend(a2, 16);
}
inline void CPU::executeInstructionID_9(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	9	=	ADDU	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] + GPR[a2];
}
inline void CPU::executeInstructionID_10(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	10	=	ALNV.PS	:	$fd,	$fs,	$ft,	$rs		

}
inline void CPU::executeInstructionID_11(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	11	=	AND	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] & GPR[a2];
}
inline void CPU::executeInstructionID_12(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	12	=	ANDI	:	$rt,	$rs,	+.imm,	_		
	GPR[a0] = GPR[a1] & a2;
}
inline void CPU::executeInstructionID_13(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	13	=	B	:	-.imm,	_,	_,	_		
	PC += (signExtend(a0, 16) << 2);
}
inline void CPU::executeInstructionID_14(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	14	=	BAL	:	-.imm,	_,	_,	_		
	//TOD: +4 or 8?
	GPR[31] = PC + 4;
	PC += (signExtend(a0, 16) << 2);
}
inline void CPU::executeInstructionID_15(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	15	=	BC1F	:	-.imm,	_,	_,	_		

}
inline void CPU::executeInstructionID_16(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	16	=	BC1F	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_17(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	17	=	BC1FL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_18(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	18	=	BC1FL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_19(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	19	=	BC1T	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_20(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	20	=	BC1T	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_21(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	21	=	BC1TL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_22(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	22	=	BC1TL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_23(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	23	=	BC2F	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_24(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	24	=	BC2F	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_25(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	25	=	BC2FL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_26(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	26	=	BC2FL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_27(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	27	=	BC2T	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_28(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	28	=	BC2T	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_29(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	29	=	BC2TL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_30(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	30	=	BC2TL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_31(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	31	=	BEQ	:	$rs,	$rt,	-.imm,	_		
	if(GPR[a0] == GPR[a1]){
		uint32_t PCoffset = (signExtend(a2, 16) << 2);
		PC += PCoffset;
	}
}
inline void CPU::executeInstructionID_32(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	32	=	BEQL	:	$rs,	$rt,	-.imm,	_		
	if(GPR[a0] == GPR[a1]){
		PC += (signExtend(a2, 16) << 2);
	}
}
inline void CPU::executeInstructionID_33(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	33	=	BGEZ	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] >= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_34(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	34	=	BGEZAL	:	$rs,	-.imm,	_,	_		
	GPR[31] = PC;
	if((int32_t)GPR[a0] >= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_35(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	35	=	BGEZALL	:	$rs,	-.imm,	_,	_		
	GPR[31] = PC;
	if((int32_t)GPR[a0] >= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_36(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	36	=	BGEZL	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] >= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_37(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	37	=	BGTZ	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] > 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_38(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	38	=	BGTZL	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] > 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_39(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	39	=	BLEZ	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] <= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_40(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	40	=	BLEZL	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] <= 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_41(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	41	=	BLTZ	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] < 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_42(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	42	=	BLTZAL	:	$rs,	-.imm,	_,	_		
	GPR[31] = PC;
	if((int32_t)GPR[a0] < 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_43(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	43	=	BLTZALL	:	$rs,	-.imm,	_,	_		
	GPR[31] = PC;
	if((int32_t)GPR[a0] < 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_44(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	44	=	BLTZL	:	$rs,	-.imm,	_,	_		
	if((int32_t)GPR[a0] < 0){
		PC += (signExtend(a1, 16) << 2);
	}
}
inline void CPU::executeInstructionID_45(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	45	=	BNE	:	$rs,	$rt,	-.imm,	_		
	if(GPR[a0] != GPR[a1]){
		PC += (signExtend(a2, 16) << 2);
	}
}
inline void CPU::executeInstructionID_46(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	46	=	BNEL	:	$rs,	$rt,	-.imm,	_		
	if(GPR[a0] != GPR[a1]){
		PC += (signExtend(a2, 16) << 2);
	}
}
inline void CPU::executeInstructionID_47(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	47	=	BREAK	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_48(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	48	=	C.F.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_49(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	49	=	C.F.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_50(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	50	=	C.F.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_51(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	51	=	C.F.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_52(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	52	=	C.F.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_53(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	53	=	C.F.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_54(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	54	=	C.UN.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_55(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	55	=	C.UN.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_56(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	56	=	C.UN.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_57(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	57	=	C.UN.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_58(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	58	=	C.UN.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_59(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	59	=	C.UN.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_60(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	60	=	C.EQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_61(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	61	=	C.EQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_62(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	62	=	C.EQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_63(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	63	=	C.EQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_64(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	64	=	C.EQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_65(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	65	=	C.EQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_66(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	66	=	C.UEQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_67(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	67	=	C.UEQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_68(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	68	=	C.UEQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_69(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	69	=	C.UEQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_70(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	70	=	C.UEQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_71(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	71	=	C.UEQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_72(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	72	=	C.OLT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_73(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	73	=	C.OLT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_74(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	74	=	C.OLT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_75(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	75	=	C.OLT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_76(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	76	=	C.OLT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_77(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	77	=	C.OLT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_78(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	78	=	C.ULT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_79(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	79	=	C.ULT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_80(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	80	=	C.ULT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_81(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	81	=	C.ULT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_82(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	82	=	C.ULT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_83(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	83	=	C.ULT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_84(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	84	=	C.OLE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_85(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	85	=	C.OLE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_86(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	86	=	C.OLE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_87(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	87	=	C.OLE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_88(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	88	=	C.OLE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_89(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	89	=	C.OLE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_90(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	90	=	C.ULE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_91(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	91	=	C.ULE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_92(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	92	=	C.ULE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_93(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	93	=	C.ULE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_94(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	94	=	C.ULE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_95(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	95	=	C.ULE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_96(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	96	=	C.SF.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_97(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	97	=	C.SF.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_98(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	98	=	C.SF.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_99(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	99	=	C.SF.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_100(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	100	=	C.SF.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_101(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	101	=	C.SF.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_102(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	102	=	C.NGLE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_103(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	103	=	C.NGLE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_104(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	104	=	C.NGLE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_105(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	105	=	C.NGLE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_106(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	106	=	C.NGLE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_107(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	107	=	C.NGLE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_108(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	108	=	C.SEQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_109(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	109	=	C.SEQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_110(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	110	=	C.SEQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_111(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	111	=	C.SEQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_112(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	112	=	C.SEQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_113(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	113	=	C.SEQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_114(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	114	=	C.NGL.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_115(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	115	=	C.NGL.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_116(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	116	=	C.NGL.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_117(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	117	=	C.NGL.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_118(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	118	=	C.NGL.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_119(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	119	=	C.NGL.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_120(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	120	=	C.LT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_121(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	121	=	C.LT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_122(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	122	=	C.LT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_123(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	123	=	C.LT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_124(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	124	=	C.LT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_125(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	125	=	C.LT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_126(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	126	=	C.NGE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_127(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	127	=	C.NGE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_128(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	128	=	C.NGE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_129(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	129	=	C.NGE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_130(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	130	=	C.NGE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_131(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	131	=	C.NGE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_132(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	132	=	C.LE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_133(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	133	=	C.LE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_134(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	134	=	C.LE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_135(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	135	=	C.LE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_136(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	136	=	C.LE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_137(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	137	=	C.LE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_138(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	138	=	C.NGT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_139(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	139	=	C.NGT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_140(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	140	=	C.NGT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_141(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	141	=	C.NGT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_142(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	142	=	C.NGT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_143(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	143	=	C.NGT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_144(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	144	=	CACHE	:	+.[20,16],	-.imm,	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_145(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	145	=	CACHEE	:	+.[20,16],	-.[15,7],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_146(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	146	=	CEIL.L.S	:	$fd,	$fs,	_,	_		
	int64_t roundedDouble = (int64_t)FPR[a1];
	double test = (double)roundedDouble;
	if(test != FPR[a1]){roundedDouble++;}	//round up
	regStoreDouble(readMemAs<double>(&roundedDouble), a0);
}
inline void CPU::executeInstructionID_147(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	147	=	CEIL.L.D	:	$fd,	$fs,	_,	_		
	int64_t roundedDouble = (int64_t)regReadDouble(a1);
	double test = (double)roundedDouble;
	if(test != regReadDouble(a1)){roundedDouble++;}	//round up
	regStoreDouble(readMemAs<double>(&roundedDouble), a0);
}
inline void CPU::executeInstructionID_148(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	148	=	CEIL.W.S	:	$fd,	$fs,	_,	_		
	int32_t roundedDouble = (int32_t)FPR[a1];
	double test = (double)roundedDouble;
	if(test != FPR[a1]){roundedDouble++;}	//round up
	FPR[a0] = readMemAs<float>(&roundedDouble);
}
inline void CPU::executeInstructionID_149(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	149	=	CEIL.W.D	:	$fd,	$fs,	_,	_		
	int32_t roundedDouble = (int32_t)regReadDouble(a1);
	double test = (double)roundedDouble;
	if(test != regReadDouble(a1)){roundedDouble++;}	//round up
	FPR[a0] = readMemAs<float>(&roundedDouble);
}
inline void CPU::executeInstructionID_150(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	150	=	CFC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_151(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	151	=	CFC2	:	$rt,	+.[15,0],	_,	_		
	
}
inline void CPU::executeInstructionID_152(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	152	=	CLO	:	$rd,	$rs,	_,	_	
	//ABNORMAL_ENCODE/DECODE	
	int32_t val = GPR[a1];
	int num = 0;
	for(int i=0; i<32; i++){
		if(!(val < 0)){break;}
		val <<= 1;
		num++;
	}
	GPR[a0] = num;
}
inline void CPU::executeInstructionID_153(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	153	=	CLZ	:	$rd,	$rs,	_,	_	
	//ABNORMAL_ENCODE/DECODE	
	int32_t val = GPR[a1];
	int num = 0;
	for(int i=0; i<32; i++){
		if(val < 0){break;}
		val <<= 1;
		num++;
	}
	GPR[a0] = num;
}
inline void CPU::executeInstructionID_154(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	154	=	COP2	:	+.[24,0],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_155(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	155	=	CTC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_156(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	156	=	CTC2	:	$rt,	+.[15,0],	_,	_		
	
}
inline void CPU::executeInstructionID_157(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	157	=	CVT.D.S	:	$fd,	$fs,	_,	_		
	double newVal = (double)FPR[a1];
	regStoreDouble(newVal, a0);
}
inline void CPU::executeInstructionID_158(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	158	=	CVT.D.W	:	$fd,	$fs,	_,	_		
	double newVal = (double)readMemAs<int32_t>(&FPR[a1]);
	regStoreDouble(newVal, a0);
}
inline void CPU::executeInstructionID_159(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	159	=	CVT.D.L	:	$fd,	$fs,	_,	_		
	double rawDouble = regReadDouble(a1);
	int64_t rawLong = readMemAs<int64_t>(&rawDouble);
	double convertedDouble = (double)rawLong;
	regStoreDouble(convertedDouble, a0);
}
inline void CPU::executeInstructionID_160(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	160	=	CVT.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_161(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	161	=	CVT.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_162(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	162	=	CVT.PS.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_163(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	163	=	CVT.S.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_164(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	164	=	CVT.S.W	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_165(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	165	=	CVT.S.L	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_166(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	166	=	CVT.S.PL	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_167(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	167	=	CVT.S.PL	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_168(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	168	=	CVT.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_169(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	169	=	CVT.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_170(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	170	=	DERET	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_171(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	171	=	DI	:	$rt,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_172(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	172	=	DIV	:	$rs,	$rt,	_,	_		
	int32_t numerator = GPR[a0];
	int32_t denominator = GPR[a1];
	HI = numerator % denominator;
	LO = numerator / denominator;
}
inline void CPU::executeInstructionID_173(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	173	=	DIV.S	:	$fd,	$fs,	$ft,	_		
	FPR[a0] = FPR[a1] / FPR[a2];
}
inline void CPU::executeInstructionID_174(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	174	=	DIV.D	:	$fd,	$fs,	$ft,	_		
	double numerator = regReadDouble(a1);
	double denominator = regReadDouble(a2);
	regStoreDouble(numerator / denominator, a0);
}
inline void CPU::executeInstructionID_175(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	175	=	DIVU	:	$rs,	$rt,	_,	_		
	uint32_t numerator = (uint32_t)GPR[a0];
	uint32_t denominator = (uint32_t)GPR[a1];
	HI = (int32_t)(numerator % denominator);
	LO = (int32_t)(numerator / denominator);
}
inline void CPU::executeInstructionID_176(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	176	=	EHB	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_177(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	177	=	EI	:	$rt,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_178(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	178	=	ERET	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_179(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	179	=	EXT	:	$rt,	$rs,	+.[10,6],	+.[15,11]	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_180(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	180	=	FLOOR.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_181(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	181	=	FLOOR.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_182(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	182	=	FLOOR.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_183(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	183	=	FLOOR.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_184(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	184	=	INS	:	$rt,	$rs,	+.[10,6],	+.[15,11]	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_185(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	185	=	J	:	+.addr,	_,	_,	_		
	PC = (PC & 0xF0000000) | (a0 << 2);
}
inline void CPU::executeInstructionID_186(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	186	=	JAL	:	+.addr,	_,	_,	_		
	GPR[$ra] = PC + 4;
	PC = (PC & 0xF0000000) | (a0 << 2);
}
inline void CPU::executeInstructionID_187(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	187	=	JALR	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_188(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	188	=	JALR	:	$rd,	$rs,	_,	_		
	
}
inline void CPU::executeInstructionID_189(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	189	=	JALR.HB	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_190(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	190	=	JALR.HB	:	$rd,	$rs,	_,	_		
	
}
inline void CPU::executeInstructionID_191(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	191	=	JALX	:	+.addr,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_192(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	192	=	JR	:	$rs,	_,	_,	_		
	PC = GPR[a0];
}
inline void CPU::executeInstructionID_193(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	193	=	JR.HB	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_194(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	194	=	LB	:	$rt,	-.imm,	($rs),	_		
	GPR[a0] = MEM.readPOD<byte>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_195(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	195	=	LBE	:	$rt,	-.[15,7],	($rs),	_		
	GPR[a0] = MEM.readPOD<byte>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_196(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	196	=	LBU	:	$rt,	-.imm,	($rs),	_		
	byte val = MEM.readPOD<byte>(GPR[a2] + a1);
	uint32_t wordVal = (uint32_t)(val);
	int32_t signedWordVal = (int32_t)(wordVal);
	GPR[a0] = signedWordVal;
}
inline void CPU::executeInstructionID_197(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	197	=	LBUE	:	$rt,	-.[15,7],	($rs),	_		
	byte val = MEM.readPOD<byte>(GPR[a2] + a1);
	uint32_t wordVal = (uint32_t)(val);
	int32_t signedWordVal = (int32_t)(wordVal);
	GPR[a0] = signedWordVal;
}
inline void CPU::executeInstructionID_198(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	198	=	LDC1	:	$ft,	-.imm,	($fmt),	_		
	FPR[a0] = MEM.readPOD<float>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_199(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	199	=	LDC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_200(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	200	=	LDXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	regStoreDouble(MEM.readPOD<double>(GPR[a1] + GPR[a2]), a0);
}
inline void CPU::executeInstructionID_201(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	201	=	LH	:	$rt,	-.imm,	($rs),	_		
	int16_t val = MEM.readPOD<int16_t>(GPR[a2] + a1);
	GPR[a0] = (int32_t)(val);
}
inline void CPU::executeInstructionID_202(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	202	=	LHE	:	$rt,	-.[15,7],	($rs),	_		
	GPR[a0] = MEM.readPOD<int16_t>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_203(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	203	=	LHU	:	$rt,	-.imm,	($rs),	_		
	uint16_t val = MEM.readPOD<uint16_t>(GPR[a2] + a1);
	uint32_t wordVal = (uint32_t)(val);
	GPR[a0] = (int32_t)(wordVal);
}
inline void CPU::executeInstructionID_204(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	204	=	LHUE	:	$rt,	-.[15,7],	($rs),	_		
	uint16_t val = MEM.readPOD<uint16_t>(GPR[a2] + a1);
	uint32_t wordVal = (uint32_t)(val);
	GPR[a0] = (int32_t)(wordVal);
}
inline void CPU::executeInstructionID_205(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	205	=	LL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_206(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	206	=	LLE	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_207(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	207	=	LUI	:	$rt,	-.imm,	_,	_
	int32_t shiftedVal = a1 << (NUM_BITS_IN_WORD / 2);
	GPR[a0] = shiftedVal;
}
inline void CPU::executeInstructionID_208(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	208	=	LUXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	virtualAddr addr = (GPR[a1] + GPR[a2]) & 0xFFFFFFFF8;
	regStoreDouble(MEM.readPOD<double>(addr), a0);
}
inline void CPU::executeInstructionID_209(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	209	=	LW	:	$rt,	-.imm,	($rs),	_		
	GPR[a0] = MEM.readPOD<int32_t>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_210(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	210	=	LWC1	:	$ft,	-.imm,	($fmt),	_		
	FPR[a0] = MEM.readPOD<float>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_211(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	211	=	LWC2	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_212(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	212	=	LWE	:	$rt,	-.[15,7],	($rs),	_		
	GPR[a0] = MEM.readPOD<int32_t>(GPR[a2] + a1);
}
inline void CPU::executeInstructionID_213(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	213	=	LWL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_214(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	214	=	LWLE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_215(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	215	=	LWR	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_216(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	216	=	LWRE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_217(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	217	=	LWXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_218(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	218	=	MADD	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_219(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	219	=	MADD.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_220(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	220	=	MADD.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_221(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	221	=	MADD.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_222(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	222	=	MADDU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_223(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	223	=	MFC0	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_224(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	224	=	MFC0	:	$rt,	$rd,	+.[2,0],	_		
	
}
inline void CPU::executeInstructionID_225(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	225	=	MFC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_226(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	226	=	MFC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_227(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	227	=	MFC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_228(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	228	=	MFHC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_229(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	229	=	MFHC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_230(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	230	=	MFHC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_231(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	231	=	MFHI	:	$rd,	_,	_,	_		
	GPR[a0] = HI;
}
inline void CPU::executeInstructionID_232(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	232	=	MFLO	:	$rd,	_,	_,	_		
	GPR[a0] = LO;
}
inline void CPU::executeInstructionID_233(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	233	=	MOV.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_234(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	234	=	MOV.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_235(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	235	=	MOV.PS	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_236(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	236	=	MOVF	:	$rd,	$rs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_237(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	237	=	MOVF.S	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_238(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	238	=	MOVF.D	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_239(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	239	=	MOVF.PS	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_240(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	240	=	MOVN	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_241(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	241	=	MOVN.S	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_242(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	242	=	MOVN.D	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_243(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	243	=	MOVN.PS	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_244(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	244	=	MOVT	:	$rd,	$rs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_245(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	245	=	MOVT.S	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_246(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	246	=	MOVT.D	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_247(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	247	=	MOVT.PS	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_248(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	248	=	MOVZ	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_249(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	249	=	MOVZ.S	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_250(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	250	=	MOVZ.D	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_251(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	251	=	MOVZ.PS	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_252(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	252	=	MSUB	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_253(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	253	=	MSUB.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_254(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	254	=	MSUB.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_255(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	255	=	MSUB.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_256(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	256	=	MSUBU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_257(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	257	=	MTC0	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_258(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	258	=	MTC0	:	$rt,	$rd,	+.[2,0],	_		
	
}
inline void CPU::executeInstructionID_259(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	259	=	MTC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_260(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	260	=	MTC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_261(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	261	=	MTC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_262(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	262	=	MTHC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_263(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	263	=	MTHC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_264(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	264	=	MTHC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_265(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	265	=	MTHI	:	$rs,	_,	_,	_		
	HI = GPR[a0];
}
inline void CPU::executeInstructionID_266(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	266	=	MTLO	:	$rs,	_,	_,	_		
	LO = GPR[a0];
}
inline void CPU::executeInstructionID_267(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	267	=	MUL	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_268(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	268	=	MUL.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_269(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	269	=	MUL.D	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_270(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	270	=	MUL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_271(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	271	=	MULT	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_272(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	272	=	MULTU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_273(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	273	=	NEG.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_274(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	274	=	NEG.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_275(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	275	=	NEG.PS	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_276(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	276	=	NMADD.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_277(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	277	=	NMADD.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_278(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	278	=	NMADD.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_279(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	279	=	NMSUB.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_280(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	280	=	NMSUB.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_281(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	281	=	NMSUB.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_282(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	282	=	NOP	:	_,	_,	_,	_		
}
inline void CPU::executeInstructionID_283(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	283	=	NOR	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = ~(GPR[a1] | GPR[a2]);
}
inline void CPU::executeInstructionID_284(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	284	=	OR	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] | GPR[a2];
}
inline void CPU::executeInstructionID_285(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	285	=	ORI	:	$rt,	$rs,	-.imm,	_		
	GPR[a0] = GPR[a1] | a2;
}
inline void CPU::executeInstructionID_286(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	286	=	PAUSE	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_287(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	287	=	PLL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_288(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	288	=	PLU.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_289(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	289	=	PREF	:	+.[20,16],	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_290(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	290	=	PREFE	:	+.[20,16],	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_291(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	291	=	PREFX	:	+.[15,11],	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_292(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	292	=	PUL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_293(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	293	=	PUU.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_294(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	294	=	RDHWR	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_295(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	295	=	RDPGPR	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_296(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	296	=	RECIP.S	:	$fd,	$fs,	_,	_		
	FPR[a0] = 1.0 / FPR[a1];
}
inline void CPU::executeInstructionID_297(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	297	=	RECIP.D	:	$fd,	$fs,	_,	_		
	regStoreDouble(1.0 / regReadDouble(a1), a0);
}
inline void CPU::executeInstructionID_298(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	298	=	ROTR	:	$rd,	$rt,	+.shamt,	_		
	
}
inline void CPU::executeInstructionID_299(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	299	=	ROTRV	:	$rd,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_300(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	300	=	ROUND.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_301(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	301	=	ROUND.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_302(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	302	=	ROUND.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_303(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	303	=	ROUND.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_304(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	304	=	RSQRT.S	:	$fd,	$fs,	_,	_		
	FPR[a0] = 1.0 / sqrt(FPR[a1]);
}
inline void CPU::executeInstructionID_305(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	305	=	RSQRT.D	:	$fd,	$fs,	_,	_		
	regStoreDouble(1.0 / sqrt(regReadDouble(a1)), a0);
}
inline void CPU::executeInstructionID_306(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	306	=	SB	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_307(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	307	=	SBE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_308(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	308	=	SC	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_309(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	309	=	SCE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_310(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	310	=	SDBBP	:	+.[25,6],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_311(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	311	=	SDC1	:	$ft,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_312(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	312	=	SDC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_313(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	313	=	SDXC1	:	$fs,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_314(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	314	=	SEB	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_315(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	315	=	SEH	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_316(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	316	=	SH	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_317(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	317	=	SHE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_318(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	318	=	SLL	:	$rd,	$rt,	+.shamt,	_		
	GPR[a0] = GPR[a1] << a2;
}
inline void CPU::executeInstructionID_319(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	319	=	SLLV	:	$rd,	$rt,	$rs,	_		
	uint32_t shamt = (uint32_t)GPR[a2];
	shamt <<= 32 - 5;
	shamt >>= 32 - 5;
	GPR[a0] = GPR[a1] << shamt;
}
inline void CPU::executeInstructionID_320(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	320	=	SLT	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = (GPR[a1] < GPR[a2])? 1 : 0;
}
inline void CPU::executeInstructionID_321(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	321	=	SLTI	:	$rt,	$rs,	-.imm,	_		
	GPR[a0] = (GPR[a1] < signExtend(a2, 16))? 1 : 0;
}
inline void CPU::executeInstructionID_322(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	322	=	SLTIU	:	$rt,	$rs,	+.imm,	_		
	GPR[a0] = ((uint32_t)GPR[a1] < (uint32_t)signExtend(a2, 16))? 1 : 0;
}
inline void CPU::executeInstructionID_323(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	323	=	SLTU	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = ((uint32_t)GPR[a1] < (uint32_t)GPR[a2])? 1 : 0;
}
inline void CPU::executeInstructionID_324(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	324	=	SQRT.S	:	$fd,	$fs,	_,	_		
	FPR[a0] = sqrt(FPR[a1]);
}
inline void CPU::executeInstructionID_325(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	325	=	SQRT.D	:	$fd,	$fs,	_,	_		
	regStoreDouble(sqrt(regReadDouble(a1)), a0);
}
inline void CPU::executeInstructionID_326(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	326	=	SRA	:	$rd,	$rt,	+.shamt,	_		
	GPR[a0] = GPR[a1] >> a2;
}
inline void CPU::executeInstructionID_327(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	327	=	SRAV	:	$rd,	$rt,	$rs,	_		
	uint32_t shamt = (uint32_t)GPR[a2];
	shamt <<= 32 - 5;
	shamt >>= 32 - 5;
	GPR[a0] = GPR[a1] << shamt;
}
inline void CPU::executeInstructionID_328(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	328	=	SRL	:	$rd,	$rt,	+.shamt,	_		
	uint32_t val = (uint32_t)GPR[a1];
	GPR[a0] = val << a2;
}
inline void CPU::executeInstructionID_329(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	329	=	SRLV	:	$rd,	$rt,	$rs,	_		
	uint32_t val = (uint32_t)GPR[a1];
	uint32_t shamt = (uint32_t)GPR[a2];
	shamt <<= 32 - 5;
	shamt >>= 32 - 5;
	GPR[a0] = val << shamt;
}
inline void CPU::executeInstructionID_330(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	330	=	SSNOP	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_331(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	331	=	SUB	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] - GPR[a2];
}
inline void CPU::executeInstructionID_332(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	332	=	SUB.S	:	$fd,	$fs,	$ft,	_		
	FPR[a0] = FPR[a1] - FPR[a2];
}
inline void CPU::executeInstructionID_333(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	333	=	SUB.D	:	$fd,	$fs,	$ft,	_		
	regStoreDouble(regReadDouble(a1) - regReadDouble(a2), a0);
}
inline void CPU::executeInstructionID_334(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	334	=	SUB.PS	:	$fd,	$fs,	$ft,	_		
	FPR[a0] = FPR[a1] - FPR[a2];
	FPR[(a0+1) % 32] = FPR[(a1+1) % 32] - FPR[(a2+1) % 32];
}
inline void CPU::executeInstructionID_335(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	335	=	SUBU	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] - GPR[a2];
}
inline void CPU::executeInstructionID_336(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	336	=	SUXC1	:	$fs,	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_337(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	337	=	SW	:	$rt,	-.imm,	($rs),	_		
	MEM.writePOD<int32_t>(GPR[a2] + a1, GPR[a0]);
}
inline void CPU::executeInstructionID_338(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	338	=	SWC1	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_339(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	339	=	SWC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_340(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	340	=	SWE	:	$rt,	-.[15,7],	($rs),	_		
	MEM.writePOD<int32_t>(GPR[a2] + a1, GPR[a0]);
}
inline void CPU::executeInstructionID_341(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	341	=	SWL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_342(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	342	=	SWLE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_343(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	343	=	SWR	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_344(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	344	=	SWRE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_345(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	345	=	SWXC1	:	$fs,	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_346(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	346	=	SYNC	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_347(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	347	=	SYNC	:	+.[10,6],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_348(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	348	=	SYNCI	:	-.imm,	(g$[25,21]),	_,	_		
	
}
inline void CPU::executeInstructionID_349(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	349	=	SYSCALL	:	_,	_,	_,	_		
	char tmpChar;
	int tmpInt;
	float tmpFloat;
	double tmpDouble;
	string tmpString;

	switch(GPR[$v0]){
		case 1:
			//print integer	1	$a0 = integer to print	
			cout << GPR[$a0];
			break;
		case 2:
			//print float	2	$f12 = float to print
			cout << FPR[12];
			break;
		case 3:
			//print double	3	$f12 = double to print
			cout << regReadDouble(12);
			break;
		case 4:
			//print string	4	$a0 = address of null-terminated string to print		
			tmpInt = 0;
			do{
				tmpChar = MEM.readPOD<char>(GPR[$a0] + tmpInt);
				tmpInt++;
				tmpString += tmpChar;
			}while(tmpChar != '\0');
			cout << tmpString;
			break;
		case 5:
			//read integer	5		=======>	$v0 contains integer read
			cin.clear();
			cin >> tmpInt;
			GPR[$v0] = tmpInt;
			break;
		case 6:
			//read float	6		=======>	$f0 contains float read
			cin >> tmpFloat;
			FPR[0] = tmpFloat;
			break;
		case 7:
			//read double	7		=======>	$f0 contains double read
			cin >> tmpDouble;
			FPR[0] = tmpDouble;
			break;
		case 8:
			//read string	8	$a0 = address of input buffer	=======>	See note below table
			//					$a1 = maximum number of characters to read	
			getline(cin, tmpString);
			tmpString += '\0';
			MEM.writeToVirtualMemorySpace(GPR[$a0], tmpString.length(), (void*)tmpString.c_str());
			break;
		case 9:
			//sbrk (allocate heap memory)	9	$a0 = number of bytes to allocate	=======>	$v0 contains address of allocated memory


			break;
		case 10:
			//exit (terminate execution)	10		=======>	terminates execution of program
			exitProgram = true;

			break;
		case 11:
			//print character	11	$a0 = character to print	=======>	See note below table


			putchar((char)GPR[4]);
			break;
		case 12:
			//read character	12		=======>	$v0 contains character read


			tmpChar = getchar();
			GPR[4] = (int32_t)tmpChar;
			break;
		case 13:
			//open file	13	$a0 = address of null-terminated string containing filename	=======>	$v0 contains file descriptor (negative if error). See note below table
			//				$a1 = flags		
			//				$a2 = mode		


			break;
		case 14:
			//read from file	14	$a0 = file descriptor	=======>	$v0 contains number of characters read (0 if end-of-file, negative if error). See note below table
			//						$a1 = address of input buffer		
			//						$a2 = maximum number of characters to read		


			break;
		case 15:
			//write to file	15	$a0 = file descriptor	=======>	$v0 contains number of characters written (negative if error). See note below table
			//					$a1 = address of output buffer		
			//					$a2 = number of characters to write		

			
			break;
		case 16:
			//close file	16	$a0 = file descriptor		


			break;
		case 17:
			//exit2 (terminate with value)	17	$a0 = termination result	=======>	See note below table


			break;
		default:

			break;
	}
}
inline void CPU::executeInstructionID_350(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	350	=	TEQ	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_351(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	351	=	TEQI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_352(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	352	=	TGE	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_353(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	353	=	TGEI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_354(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	354	=	TGEIU	:	$rs,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_355(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	355	=	TGEU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_356(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	356	=	TLBINV	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_357(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	357	=	TLBINVF	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_358(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	358	=	TLBP	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_359(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	359	=	TLBR	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_360(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	360	=	TLBWI	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_361(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	361	=	TLBWR	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_362(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	362	=	TLT	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_363(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	363	=	TLTI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_364(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	364	=	TLTIU	:	$rs,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_365(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	365	=	TLTU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_366(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	366	=	TNE	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_367(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	367	=	TNEI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_368(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	368	=	TRUNC.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_369(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	369	=	TRUNC.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_370(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	370	=	TRUNC.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_371(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	371	=	TRUNC.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_372(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	372	=	WAIT	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_373(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	373	=	WRPGPR	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_374(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	374	=	WSBH	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_375(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	375	=	XOR	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] ^ GPR[a2];
}
inline void CPU::executeInstructionID_376(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3){
	//	376	=	XORI	:	$rt,	$rs,	-.imm,	_		
	GPR[a0] = GPR[a1] ^ a2;
}

