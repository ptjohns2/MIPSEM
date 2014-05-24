#include "CPU.hpp"

#include <math.h>

#pragma warning(disable: 4100)	//Warning: unreferenced formal parameter

//	Constructors
CPU::CPU(){
	for(int i=0; i<32; i++){
		GPR[i] = 0x0;
		FPR[i] = 0x0;
	}
	GPR[29] = MEMORY_SECTION_STACK;
	GPR[30] = MEMORY_SECTION_STACK;
	PC = MEMORY_SECTION_TEXT;
	HI = 0x0;
	LO = 0x0;
}

CPU::~CPU(){}

void CPU::executeInstruction(Instruction* instruction){
	//Get necessary data
	InstructionData* instructionData = instruction->getInstructionData();
	int instructionId = instructionData->getInstructionID();
	int32_t a0 = instruction->getArgumentValue(0);
	int32_t a1 = instruction->getArgumentValue(1);
	int32_t a2 = instruction->getArgumentValue(2);
	int32_t a3 = instruction->getArgumentValue(3);

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

	//PC incrementation (optional)
	if(!instructionData->changesPC()){PC += 4;}
}

//Helper functions
inline uint32_t CPU::calculateBranchTargetOffset(int32_t val){
	return (signExtend(val) << 2) + 4;
}

inline uint32_t CPU::signExtend(uint32_t val){
	int32_t signedVal = (int32_t)val;
	signedVal <<= 16;
	signedVal >>= 16;
	return (uint32_t)signedVal;
}


//INSTRUCTIONS
inline void CPU::executeInstructionID_0(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	0	=	ABS.S	:	$fd,	$fs,	_,	_		
	FPR[a0] = fabs(FPR[a1]);
}
inline void CPU::executeInstructionID_1(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	1	=	ABS.D	:	$fd,	$fs,	_,	_	
	FPR[a0] = ((uint32_t)(a1) << 1) >> 1;
}
inline void CPU::executeInstructionID_2(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	2	=	ABS.PS	:	$fd,	$fs,	_,	_			
	FPR[a0] = fabs(FPR[a1]);
	FPR[a0+1] = fabs(FPR[a1+1]);
}
inline void CPU::executeInstructionID_3(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	3	=	ADD	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] + GPR[a2];
}
inline void CPU::executeInstructionID_4(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	4	=	ADD.S	:	$fd,	$ft,	$fs,	_		
	FPR[a0] = FPR[a1] + FPR[a2];
}
inline void CPU::executeInstructionID_5(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	5	=	ADD.D	:	$fd,	$ft,	$fs,	_		
	uint64_t operand1 = FPR[a1];
	operand1 <<= 32;
	operand1 |= (uint64_t)FPR[(a1+1) % 32];	

	uint64_t operand2 = FPR[a2];
	operand2 <<= 32;
	operand2 |= (uint64_t)FPR[(a2+1) % 32];

	double tmpSum = (double)operand1 + (double)operand2;
	uint64_t sum = (uint64_t)tmpSum;
	int32_t msb = sum >> 32;
	int32_t lsb = (sum << 32) >> 32;
	FPR[a0] = msb;
	FPR[(a0+1) % 32] = lsb;
}
inline void CPU::executeInstructionID_6(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	6	=	ADD.PS	:	$fd,	$ft,	$fs,	_	
	FPR[a0] = FPR[a1] + FPR[a2];
	FPR[(a0+1) % 32] = FPR[(a1+1) % 32] + FPR[(a2+1) % 32];
}
inline void CPU::executeInstructionID_7(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	7	=	ADDI	:	$rt,	$rs,	-.imm,	_		
	GPR[a0] = GPR[a1] + a2;
}
inline void CPU::executeInstructionID_8(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	8	=	ADDIU	:	$rt,	$rs,	+.imm,	_		
	GPR[a0] = GPR[a1] + a2;	
}
inline void CPU::executeInstructionID_9(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	9	=	ADDU	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] + GPR[a2];
}
inline void CPU::executeInstructionID_10(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	10	=	ALNV.PS	:	$fd,	$fs,	$ft,	$rs		
	
}
inline void CPU::executeInstructionID_11(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	11	=	AND	:	$rd,	$rs,	$rt,	_		
	GPR[a0] = GPR[a1] & GPR[a2];
}
inline void CPU::executeInstructionID_12(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	12	=	ANDI	:	$rt,	$rs,	+.imm,	_		
	GPR[a0] = GPR[a1] & a2;
}
inline void CPU::executeInstructionID_13(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	13	=	B	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_14(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	14	=	BAL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_15(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	15	=	BC1F	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_16(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	16	=	BC1F	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_17(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	17	=	BC1FL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_18(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	18	=	BC1FL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_19(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	19	=	BC1T	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_20(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	20	=	BC1T	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_21(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	21	=	BC1TL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_22(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	22	=	BC1TL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_23(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	23	=	BC2F	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_24(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	24	=	BC2F	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_25(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	25	=	BC2FL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_26(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	26	=	BC2FL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_27(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	27	=	BC2T	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_28(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	28	=	BC2T	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_29(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	29	=	BC2TL	:	-.imm,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_30(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	30	=	BC2TL	:	+.[20,18],	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_31(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	31	=	BEQ	:	$rs,	$rt,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_32(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	32	=	BEQL	:	$rs,	$rt,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_33(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	33	=	BGEZ	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_34(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	34	=	BGEZAL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_35(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	35	=	BGEZALL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_36(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	36	=	BGEZL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_37(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	37	=	BGTZ	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_38(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	38	=	BGTZL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_39(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	39	=	BLEZ	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_40(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	40	=	BLEZL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_41(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	41	=	BLTZ	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_42(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	42	=	BLTZAL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_43(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	43	=	BLTZALL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_44(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	44	=	BLTZL	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_45(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	45	=	BNE	:	$rs,	$rt,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_46(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	46	=	BNEL	:	$rs,	$rt,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_47(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	47	=	BREAK	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_48(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	48	=	C.F.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_49(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	49	=	C.F.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_50(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	50	=	C.F.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_51(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	51	=	C.F.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_52(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	52	=	C.F.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_53(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	53	=	C.F.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_54(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	54	=	C.UN.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_55(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	55	=	C.UN.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_56(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	56	=	C.UN.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_57(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	57	=	C.UN.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_58(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	58	=	C.UN.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_59(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	59	=	C.UN.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_60(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	60	=	C.EQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_61(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	61	=	C.EQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_62(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	62	=	C.EQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_63(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	63	=	C.EQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_64(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	64	=	C.EQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_65(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	65	=	C.EQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_66(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	66	=	C.UEQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_67(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	67	=	C.UEQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_68(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	68	=	C.UEQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_69(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	69	=	C.UEQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_70(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	70	=	C.UEQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_71(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	71	=	C.UEQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_72(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	72	=	C.OLT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_73(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	73	=	C.OLT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_74(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	74	=	C.OLT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_75(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	75	=	C.OLT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_76(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	76	=	C.OLT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_77(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	77	=	C.OLT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_78(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	78	=	C.ULT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_79(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	79	=	C.ULT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_80(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	80	=	C.ULT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_81(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	81	=	C.ULT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_82(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	82	=	C.ULT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_83(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	83	=	C.ULT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_84(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	84	=	C.OLE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_85(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	85	=	C.OLE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_86(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	86	=	C.OLE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_87(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	87	=	C.OLE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_88(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	88	=	C.OLE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_89(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	89	=	C.OLE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_90(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	90	=	C.ULE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_91(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	91	=	C.ULE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_92(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	92	=	C.ULE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_93(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	93	=	C.ULE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_94(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	94	=	C.ULE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_95(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	95	=	C.ULE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_96(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	96	=	C.SF.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_97(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	97	=	C.SF.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_98(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	98	=	C.SF.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_99(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	99	=	C.SF.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_100(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	100	=	C.SF.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_101(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	101	=	C.SF.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_102(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	102	=	C.NGLE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_103(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	103	=	C.NGLE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_104(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	104	=	C.NGLE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_105(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	105	=	C.NGLE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_106(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	106	=	C.NGLE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_107(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	107	=	C.NGLE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_108(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	108	=	C.SEQ.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_109(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	109	=	C.SEQ.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_110(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	110	=	C.SEQ.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_111(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	111	=	C.SEQ.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_112(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	112	=	C.SEQ.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_113(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	113	=	C.SEQ.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_114(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	114	=	C.NGL.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_115(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	115	=	C.NGL.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_116(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	116	=	C.NGL.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_117(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	117	=	C.NGL.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_118(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	118	=	C.NGL.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_119(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	119	=	C.NGL.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_120(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	120	=	C.LT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_121(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	121	=	C.LT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_122(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	122	=	C.LT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_123(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	123	=	C.LT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_124(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	124	=	C.LT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_125(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	125	=	C.LT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_126(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	126	=	C.NGE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_127(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	127	=	C.NGE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_128(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	128	=	C.NGE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_129(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	129	=	C.NGE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_130(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	130	=	C.NGE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_131(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	131	=	C.NGE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_132(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	132	=	C.LE.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_133(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	133	=	C.LE.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_134(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	134	=	C.LE.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_135(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	135	=	C.LE.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_136(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	136	=	C.LE.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_137(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	137	=	C.LE.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_138(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	138	=	C.NGT.S	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_139(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	139	=	C.NGT.S	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_140(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	140	=	C.NGT.D	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_141(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	141	=	C.NGT.D	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_142(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	142	=	C.NGT.PS	:	$fs,	$ft,	_,	_		
	
}
inline void CPU::executeInstructionID_143(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	143	=	C.NGT.PS	:	+.[10,8],	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_144(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	144	=	CACHE	:	+.[20,16],	-.imm,	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_145(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	145	=	CACHEE	:	+.[20,16],	-.[15,7],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_146(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	146	=	CEIL.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_147(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	147	=	CEIL.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_148(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	148	=	CEIL.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_149(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	149	=	CEIL.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_150(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	150	=	CFC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_151(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	151	=	CFC2	:	$rt,	+.[15,0],	_,	_		
	
}
inline void CPU::executeInstructionID_152(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	152	=	CLO	:	$rd,	$rs,	_,	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_153(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	153	=	CLZ	:	$rd,	$rs,	_,	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_154(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	154	=	COP2	:	+.[24,0],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_155(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	155	=	CTC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_156(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	156	=	CTC2	:	$rt,	+.[15,0],	_,	_		
	
}
inline void CPU::executeInstructionID_157(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	157	=	CVT.D.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_158(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	158	=	CVT.D.W	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_159(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	159	=	CVT.D.L	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_160(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	160	=	CVT.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_161(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	161	=	CVT.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_162(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	162	=	CVT.PS.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_163(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	163	=	CVT.S.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_164(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	164	=	CVT.S.W	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_165(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	165	=	CVT.S.L	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_166(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	166	=	CVT.S.PL	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_167(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	167	=	CVT.S.PL	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_168(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	168	=	CVT.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_169(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	169	=	CVT.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_170(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	170	=	DERET	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_171(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	171	=	DI	:	$rt,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_172(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	172	=	DIV	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_173(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	173	=	DIV.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_174(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	174	=	DIV.D	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_175(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	175	=	DIVU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_176(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	176	=	EHB	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_177(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	177	=	EI	:	$rt,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_178(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	178	=	ERET	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_179(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	179	=	EXT	:	$rt,	$rs,	+.[10,6],	+.[15,11]	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_180(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	180	=	FLOOR.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_181(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	181	=	FLOOR.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_182(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	182	=	FLOOR.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_183(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	183	=	FLOOR.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_184(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	184	=	INS	:	$rt,	$rs,	+.[10,6],	+.[15,11]	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_185(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	185	=	J	:	+.addr,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_186(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	186	=	JAL	:	+.addr,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_187(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	187	=	JALR	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_188(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	188	=	JALR	:	$rd,	$rs,	_,	_		
	
}
inline void CPU::executeInstructionID_189(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	189	=	JALR.HB	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_190(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	190	=	JALR.HB	:	$rd,	$rs,	_,	_		
	
}
inline void CPU::executeInstructionID_191(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	191	=	JALX	:	+.addr,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_192(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	192	=	JR	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_193(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	193	=	JR.HB	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_194(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	194	=	LB	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_195(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	195	=	LBE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_196(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	196	=	LBU	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_197(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	197	=	LBUE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_198(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	198	=	LDC1	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_199(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	199	=	LDC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_200(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	200	=	LDXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_201(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	201	=	LH	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_202(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	202	=	LHE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_203(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	203	=	LHU	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_204(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	204	=	LHUE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_205(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	205	=	LL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_206(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	206	=	LLE	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_207(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	207	=	LUI	:	$rt,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_208(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	208	=	LUXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_209(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	209	=	LW	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_210(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	210	=	LWC1	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_211(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	211	=	LWC2	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_212(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	212	=	LWE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_213(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	213	=	LWL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_214(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	214	=	LWLE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_215(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	215	=	LWR	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_216(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	216	=	LWRE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_217(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	217	=	LWXC1	:	$fd,	g$[20,16],	(g$[25,21]),	_		
	
}
inline void CPU::executeInstructionID_218(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	218	=	MADD	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_219(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	219	=	MADD.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_220(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	220	=	MADD.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_221(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	221	=	MADD.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_222(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	222	=	MADDU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_223(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	223	=	MFC0	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_224(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	224	=	MFC0	:	$rt,	$rd,	+.[2,0],	_		
	
}
inline void CPU::executeInstructionID_225(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	225	=	MFC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_226(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	226	=	MFC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_227(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	227	=	MFC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_228(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	228	=	MFHC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_229(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	229	=	MFHC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_230(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	230	=	MFHC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_231(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	231	=	MFHI	:	$rd,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_232(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	232	=	MFLO	:	$rd,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_233(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	233	=	MOV.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_234(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	234	=	MOV.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_235(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	235	=	MOV.PS	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_236(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	236	=	MOVF	:	$rd,	$rs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_237(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	237	=	MOVF.S	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_238(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	238	=	MOVF.D	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_239(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	239	=	MOVF.PS	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_240(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	240	=	MOVN	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_241(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	241	=	MOVN.S	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_242(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	242	=	MOVN.D	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_243(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	243	=	MOVN.PS	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_244(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	244	=	MOVT	:	$rd,	$rs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_245(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	245	=	MOVT.S	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_246(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	246	=	MOVT.D	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_247(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	247	=	MOVT.PS	:	$fd,	$fs,	+.[20,18],	_		
	
}
inline void CPU::executeInstructionID_248(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	248	=	MOVZ	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_249(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	249	=	MOVZ.S	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_250(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	250	=	MOVZ.D	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_251(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	251	=	MOVZ.PS	:	$fd,	$fs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_252(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	252	=	MSUB	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_253(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	253	=	MSUB.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_254(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	254	=	MSUB.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_255(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	255	=	MSUB.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_256(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	256	=	MSUBU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_257(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	257	=	MTC0	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_258(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	258	=	MTC0	:	$rt,	$rd,	+.[2,0],	_		
	
}
inline void CPU::executeInstructionID_259(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	259	=	MTC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_260(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	260	=	MTC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_261(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	261	=	MTC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_262(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	262	=	MTHC1	:	$rt,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_263(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	263	=	MTHC2	:	$rt,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_264(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	264	=	MTHC2	:	$rt,	+.imm,	+.[2,0],	_	
	//ABNORMAL_ENCODE/DECODE	
	
}
inline void CPU::executeInstructionID_265(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	265	=	MTHI	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_266(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	266	=	MTLO	:	$rs,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_267(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	267	=	MUL	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_268(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	268	=	MUL.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_269(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	269	=	MUL.D	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_270(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	270	=	MUL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_271(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	271	=	MULT	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_272(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	272	=	MULTU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_273(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	273	=	NEG.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_274(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	274	=	NEG.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_275(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	275	=	NEG.PS	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_276(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	276	=	NMADD.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_277(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	277	=	NMADD.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_278(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	278	=	NMADD.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_279(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	279	=	NMSUB.S	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_280(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	280	=	NMSUB.D	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_281(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	281	=	NMSUB.PS	:	$fd,	$fmt,	$fs,	$ft		
	
}
inline void CPU::executeInstructionID_282(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	282	=	NOP	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_283(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	283	=	NOR	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_284(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	284	=	OR	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_285(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	285	=	ORI	:	$rt,	$rs,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_286(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	286	=	PAUSE	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_287(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	287	=	PLL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_288(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	288	=	PLU.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_289(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	289	=	PREF	:	+.[20,16],	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_290(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	290	=	PREFE	:	+.[20,16],	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_291(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	291	=	PREFX	:	+.[15,11],	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_292(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	292	=	PUL.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_293(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	293	=	PUU.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_294(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	294	=	RDHWR	:	$rt,	$rd,	_,	_		
	
}
inline void CPU::executeInstructionID_295(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	295	=	RDPGPR	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_296(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	296	=	RECIP.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_297(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	297	=	RECIP.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_298(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	298	=	ROTR	:	$rd,	$rt,	+.shamt,	_		
	
}
inline void CPU::executeInstructionID_299(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	299	=	ROTRV	:	$rd,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_300(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	300	=	ROUND.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_301(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	301	=	ROUND.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_302(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	302	=	ROUND.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_303(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	303	=	ROUND.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_304(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	304	=	RSQRT.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_305(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	305	=	RSQRT.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_306(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	306	=	SB	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_307(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	307	=	SBE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_308(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	308	=	SC	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_309(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	309	=	SCE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_310(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	310	=	SDBBP	:	+.[25,6],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_311(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	311	=	SDC1	:	$ft,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_312(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	312	=	SDC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_313(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	313	=	SDXC1	:	$fs,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_314(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	314	=	SEB	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_315(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	315	=	SEH	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_316(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	316	=	SH	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_317(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	317	=	SHE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_318(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	318	=	SLL	:	$rd,	$rt,	+.shamt,	_		
	
}
inline void CPU::executeInstructionID_319(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	319	=	SLLV	:	$rd,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_320(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	320	=	SLT	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_321(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	321	=	SLTI	:	$rt,	$rs,	-.imm,	_		
	
}
inline void CPU::executeInstructionID_322(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	322	=	SLTIU	:	$rt,	$rs,	+.imm,	_		
	
}
inline void CPU::executeInstructionID_323(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	323	=	SLTU	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_324(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	324	=	SQRT.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_325(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	325	=	SQRT.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_326(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	326	=	SRA	:	$rd,	$rt,	+.shamt,	_		
	
}
inline void CPU::executeInstructionID_327(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	327	=	SRAV	:	$rd,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_328(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	328	=	SRL	:	$rd,	$rt,	+.shamt,	_		
	
}
inline void CPU::executeInstructionID_329(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	329	=	SRLV	:	$rd,	$rt,	$rs,	_		
	
}
inline void CPU::executeInstructionID_330(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	330	=	SSNOP	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_331(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	331	=	SUB	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_332(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	332	=	SUB.S	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_333(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	333	=	SUB.D	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_334(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	334	=	SUB.PS	:	$fd,	$fs,	$ft,	_		
	
}
inline void CPU::executeInstructionID_335(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	335	=	SUBU	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_336(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	336	=	SUXC1	:	$fs,	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_337(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	337	=	SW	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_338(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	338	=	SWC1	:	$ft,	-.imm,	($fmt),	_		
	
}
inline void CPU::executeInstructionID_339(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	339	=	SWC2	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_340(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	340	=	SWE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_341(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	341	=	SWL	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_342(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	342	=	SWLE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_343(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	343	=	SWR	:	$rt,	-.imm,	($rs),	_		
	
}
inline void CPU::executeInstructionID_344(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	344	=	SWRE	:	$rt,	-.[15,7],	($rs),	_		
	
}
inline void CPU::executeInstructionID_345(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	345	=	SWXC1	:	$fs,	$rt,	($rs),	_		
	
}
inline void CPU::executeInstructionID_346(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	346	=	SYNC	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_347(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	347	=	SYNC	:	+.[10,6],	_,	_,	_		
	
}
inline void CPU::executeInstructionID_348(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	348	=	SYNCI	:	-.imm,	(g$[25,21]),	_,	_		
	
}
inline void CPU::executeInstructionID_349(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	349	=	SYSCALL	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_350(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	350	=	TEQ	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_351(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	351	=	TEQI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_352(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	352	=	TGE	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_353(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	353	=	TGEI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_354(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	354	=	TGEIU	:	$rs,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_355(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	355	=	TGEU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_356(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	356	=	TLBINV	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_357(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	357	=	TLBINVF	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_358(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	358	=	TLBP	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_359(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	359	=	TLBR	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_360(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	360	=	TLBWI	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_361(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	361	=	TLBWR	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_362(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	362	=	TLT	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_363(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	363	=	TLTI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_364(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	364	=	TLTIU	:	$rs,	+.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_365(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	365	=	TLTU	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_366(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	366	=	TNE	:	$rs,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_367(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	367	=	TNEI	:	$rs,	-.imm,	_,	_		
	
}
inline void CPU::executeInstructionID_368(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	368	=	TRUNC.L.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_369(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	369	=	TRUNC.L.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_370(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	370	=	TRUNC.W.S	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_371(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	371	=	TRUNC.W.D	:	$fd,	$fs,	_,	_		
	
}
inline void CPU::executeInstructionID_372(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	372	=	WAIT	:	_,	_,	_,	_		
	
}
inline void CPU::executeInstructionID_373(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	373	=	WRPGPR	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_374(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	374	=	WSBH	:	$rd,	$rt,	_,	_		
	
}
inline void CPU::executeInstructionID_375(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	375	=	XOR	:	$rd,	$rs,	$rt,	_		
	
}
inline void CPU::executeInstructionID_376(int32_t a0, int32_t a1, int32_t a2, int32_t a3){
	//	376	=	XORI	:	$rt,	$rs,	-.imm,	_		
	
}
