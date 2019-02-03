// PIC18Legacy.c
// Generated by decompiling PIC18Legacy.hex
// using Reko decompiler version 0.8.0.2.

#include "PIC18Legacy.h"

// 00000000: void fn00000000(Register byte TABLAT)
void fn00000000(byte TABLAT)
{
	globals->b0001 &= 191;
	Data19[0x01].ptr0000 = 330;
	fn00000E(TABLAT, 0x00, 0x00);
}

// 00000E: void fn00000E(Register byte TABLAT, Register Eq_15 FSR0, Register word24 TBLPTR)
void fn00000E(byte TABLAT, Eq_15 FSR0, word24 TBLPTR)
{
	__tblrd(TBLPTR, 0x01);
	0x00->b00C5 = TABLAT;
	__tblrd(TBLPTR, 0x01);
	0x00->b00C6 = TABLAT;
	byte TBLPTRL_4 = 0x06;
	byte TBLPTRH_46 = 0x00;
	byte TBLPTRU_49 = 0x00;
	bool Z_17 = SLICE(cond(TABLAT), bool, 2);
	while (true)
	{
		if (!Z_17 && 0x00->b00C5 == 0x00)
			return;
		__tblrd(TBLPTR, 0x01);
		0x00->b00C0 = TABLAT;
		__tblrd(TBLPTR, 0x01);
		0x00->b00C1 = TABLAT;
		__tblrd(TBLPTR, 0x01);
		0x00->b00C2 = TABLAT;
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		0x00->b00C3 = TABLAT;
		__tblrd(TBLPTR, 0x01);
		0x00->b00C4 = TABLAT;
		__tblrd(TBLPTR, 0x01);
		__tblrd(TBLPTR, 0x01);
		globals->b00C7 = TBLPTRL_4;
		globals->b00C8 = TBLPTRH_46;
		globals->b00C9 = TBLPTRU_49;
		0x00->b00C3 = 0x00->b00C3;
		bool Z_57 = SLICE(cond(0x00->b00C3), bool, 2);
l000080:
		if (Z_57)
			break;
		0x00->b00C4 = 0x00->b00C4;
		if (0x00->b00C4 != 0x00)
			break;
		TBLPTRL_4 = globals->b00C7;
		TBLPTRH_46 = globals->b00C8;
		TBLPTRU_49 = globals->b00C9;
		0x00->b00C5 = 0x00->b00C5 - 0x01;
		0x00->b00C6 = 0x00->b00C6 - !SLICE(cond(0x00->b00C5), bool, 0);
		Z_17 = SLICE(cond(0x00->b00C6), bool, 2);
	}
	while (true)
	{
		__tblrd(TBLPTR, 0x01);
		*FSR0 = TABLAT;
		0x00->b00C3 = 0x00->b00C3 - 0x01;
		++FSR0;
		Z_57 = SLICE(cond(0x00->b00C3), bool, 2);
		if (0x00->b00C3 < 0x00)
			break;
		0x00->b00C4 = 0x00->b00C4 - 0x01;
	}
	goto l000080;
}

// 0000D0: void fn0000D0(Register byte LATB, Register byte FSR2L, Register (ptr16 Eq_184) FSR2, Register (ptr16 Eq_185) FSR1)
void fn0000D0(byte LATB, byte FSR2L, struct Eq_184 * FSR2, struct Eq_185 * FSR1)
{
	FSR1->b0000 = FSR2L;
	while (FSR2->b00FE != 0x00)
	{
		if ((0x00->b00CA & 0x01) != 0x00)
		{
			0x00->b00CA = 0x00->b00CA & ~0x01;
			if ((LATB & 0x01) != 0x00)
				LATB |= 0x80;
			else
				LATB &= 0x7F;
		}
	}
	FSR1->b0001 = FSR1->b0001;
}

// 000128: void fn000128(Register cu8 WREG, Register cu8 FSR0L, Register cu8 FSR0H, Register cu8 PRODL, Register Eq_225 FSR0)
void fn000128(cu8 WREG, cu8 FSR0L, cu8 FSR0H, cu8 PRODL, Eq_225 FSR0)
{
	while (FSR0H < WREG)
	{
		*FSR0 = 0x00;
		FSR0 = (word32) FSR0 + 0x01;
	}
	while (FSR0L < PRODL)
	{
		*FSR0 = 0x00;
		FSR0 = (word32) FSR0 + 0x01;
	}
}

