

//#include "instructions.hpp"


/*
R:	[opcode_6][rs_5][rt_5][rd_5][shamt_5][funct_6]
I:	[opcode_6][rs_5][rt_5][immediate_16]
J:	[opcode_6][address_26]
FR:	[opcode_6][fmt_5][ft_5][fs_5][fd_5][funct_6]
FI:	[opcode_6][fmt_5][ft_5][immediate_16]
*/


/*===========================================================*/
/*	TYPE _R_ INSTRUCTIONS	*/
/*
void add(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] + emu->GPregs[i->rt];}
void sub(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] - emu->GPregs[i->rt];}
void div(struct instrInstance* i, struct registerFile* emu)		{
	emu->lo = emu->GPregs[i->rs] / emu->GPregs[i->rt];
	emu->hi = emu->GPregs[i->rs] % emu->GPregs[i->rs];
}
*/

/* TODO: mult	*/

/*
void mul(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] * emu->GPregs[i->rt];}

void mfhi(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rd] = emu->hi;}
void mflo(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rd] = emu->lo;}
void mthi(struct instrInstance* i, struct registerFile* emu)	{emu->hi = emu->GPregs[i->rd];}
void mtlo(struct instrInstance* i, struct registerFile* emu)	{emu->lo = emu->GPregs[i->rd];}

void and(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] & emu->GPregs[i->rt];}
void or(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] | emu->GPregs[i->rt];}
void xor(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = emu->GPregs[i->rs] ^ emu->GPregs[i->rt];}
void nor(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = ~(emu->GPregs[i->rs] | emu->GPregs[i->rt]);}

void slt(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rd] = (emu->GPregs[i->rs] < emu->GPregs[i->rt])? 1:0;}

void nop(struct instrInstance* i, struct registerFile* emu)		{}
*/

/*===========================================================*/
/*	TYPE _I_ INSTRUCTIONS	*/
/*
void addi(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rt] = emu->GPregs[i->rs] + i->immediate;}
void andi(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rt] = emu->GPregs[i->rs] & i->immediate;}
void ori(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rt] = emu->GPregs[i->rs] | i->immediate;}
void xori(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rt] = emu->GPregs[i->rt] ^ i->immediate;}

void sll(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rs] = emu->GPregs[i->rt] << i->immediate;}
void srl(struct instrInstance* i, struct registerFile* emu)		{emu->GPregs[i->rs] = emu->GPregs[i->rt] >> i->immediate;}

void slti(struct instrInstance* i, struct registerFile* emu)	{emu->GPregs[i->rt] = (emu->GPregs[i->rs] < i->immediate)? 1:0;}
*/

/*===========================================================*/
/*	TYPE _J_ INSTRUCTIONS	*/










