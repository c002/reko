// switch.c
// Generated by decompiling switch
// using Reko decompiler version 0.8.0.2.

#include "switch.h"

// 000082F0: Register word32 _init(Register word32 r4, Register ptr32 r10, Register ptr32 lr, Register ptr32 pc, Register out ptr32 r4Out, Register out ptr32 r10Out, Register out ptr32 pcOut)
word32 _init(word32 r4, ptr32 r10, ptr32 lr, ptr32 pc, ptr32 & r4Out, ptr32 & r10Out, ptr32 & pcOut)
{
	word32 lr_8;
	ptr32 pc_9;
	ptr32 r10_10 = call_gmon_start(r10, lr, pc, out lr_8, out pc_9);
	word32 r0_17 = frame_dummy(pc_9);
	ptr32 pc_25;
	r4Out = __do_global_ctors_aux(r4, lr_8, pc_9, out pc_25);
	r10Out = r10_10;
	pcOut = pc_25;
	return r0_17;
}

// 00008314: void abort()
void abort()
{
}

// 00008324: void __libc_start_main()
void __libc_start_main()
{
}

// 00008334: void _start(Stack int32 dwArg00, Stack (ptr32 Eq_38) ptrArg08, Stack (ptr32 Eq_39) ptrArg0C, Stack (ptr32 void) ptrArg10)
void _start(int32 dwArg00, void (* ptrArg08)(), void (* ptrArg0C)(), void * ptrArg10)
{
	__libc_start_main(globals->ptr8364, dwArg00, fp + 0x04, globals->ptr8368, ptrArg08, ptrArg0C, ptrArg10);
	abort();
}

// 0000836C: Register ptr32 call_gmon_start(Register ptr32 r10, Register ptr32 lr, Register ptr32 pc, Register out ptr32 lrOut, Register out ptr32 pcOut)
ptr32 call_gmon_start(ptr32 r10, ptr32 lr, ptr32 pc, ptr32 & lrOut, ptr32 & pcOut)
{
	ptr32 r10_10 = 0x8380 + globals->dw8394;
	<anonymous> * r3_11 = r10_10 + globals->dw8398;
	if (r3_11 != null)
	{
		ptr32 r10_16;
		ptr32 lr_17;
		ptr32 pc_19;
		r3_11();
		lrOut = lr_17;
		pcOut = pc_19;
		return r10_16;
	}
	else
	{
		lrOut = lr;
		pcOut = pc;
		return r10;
	}
}

// 0000839C: void __do_global_dtors_aux(Register word32 r4, Register word32 r5, Register word32 lr, Register word32 pc)
void __do_global_dtors_aux(word32 r4, word32 r5, word32 lr, word32 pc)
{
	byte * r5_10 = globals->ptr83F4;
	if ((word32) *r5_10 != 0x00)
		return;
	<anonymous> *** r4_14 = globals->ptr83F8;
	<anonymous> * r2_16 = **r4_14;
	if (r2_16 == null)
		*r5_10 = 0x01;
	else
	{
		<anonymous> ** r3_24 = *r4_14;
		*r4_14 = (<anonymous> ***) ((char *) r3_24 + 0x04);
		r2_16();
	}
}

// 000083FC: void call___do_global_dtors_aux()
void call___do_global_dtors_aux()
{
}

// 00008404: Register (ptr32 word32) frame_dummy(Register ptr32 pc)
word32 * frame_dummy(ptr32 pc)
{
	word32 * r0_4 = globals->ptr8424;
	if (*r0_4 == 0x00)
		return r0_4;
	word32 r3_8 = globals->dw8428;
	if (r3_8 == 0x00)
		return r0_4;
	word32 * r0_12;
	fn00000000();
	return r0_12;
}

// 0000842C: void call_frame_dummy()
void call_frame_dummy()
{
}

// 00008434: Register (ptr32 ptr32) frobulate(Register (ptr32 ptr32) r0, Stack (ptr32 ptr32) dwArg00, Register out ptr32 spOut)
ptr32 * frobulate(ptr32 * r0, ptr32 * dwArg00, ptr32 & spOut)
{
	__divsi3(r0 * r0, (ptr32 *) 1337);
	spOut = *dwArg00;
	return dwArg00;
}

// 00008470: Register word32 bazulate(Register (ptr32 ptr32) r0, Register (ptr32 ptr32) r1)
word32 bazulate(ptr32 * r0, ptr32 * r1)
{
	ptr32 ** sp_29;
	word32 * fp_24 = frobulate(r0, r1, out sp_29);
	word32 r0_38 = __divsi3(r0 + r1, r0);
	ptr32 * r0_46 = *(fp_24 - 0x0018);
	word32 * fp_47 = frobulate(r0_46, *sp_29, out sp_80);
	__divsi3(r0_38, r0_46);
	return *fp_47;
}

// 000084D4: Register word32 switcheroo(Register (ptr32 ptr32) r0)
word32 switcheroo(ptr32 * r0)
{
	word32 * fp_35;
	switch (r0)
	{
	case 0x00:
	case 0x01:
		goto l00008540;
	case 0x02:
	case 0x03:
	case 0x04:
		fp_35 = frobulate(r0, r0, out sp_96);
		break;
	case 0x05:
	case 0x07:
l00008540:
		fp_35 = bazulate(null, null);
		break;
	case 0x06:
		fp_35 = frobulate(r0 - 0x03, r0, out sp_97);
		break;
	case 0x08:
		bazulate(r0, r0);
		goto l00008540;
	}
	return *(fp_35 - -0x04);
}

// 0000855C: void main(Register (ptr32 ptr32) r0)
void main(ptr32 * r0)
{
	switcheroo(r0);
}

// 00008588: Register (ptr32 ptr32) __divsi3(Register (ptr32 ptr32) r0, Register (ptr32 ptr32) r1)
ptr32 * __divsi3(ptr32 * r0, ptr32 * r1)
{
	ptr32 * r1_10;
	int32 ip_5 = r0 ^ r1;
	Eq_211 r3_118 = 0x01;
	ptr32 * r2_109 = null;
	r1_10 = r1;
	if (r1 < null)
		r1_10 = 0x00 - r1;
	if (r1 == null)
	{
		__div0(r0);
		return null;
	}
	else
	{
		if (r0 < null)
			r0 = 0x00 - r0;
		if (r0 >= r1_10)
		{
			do
			{
				bool C_35 = SLICE(cond(r1_10 - (ptr32 *) 0x10000000), bool, 1);
				if (r1_10 < (ptr32 *) 0x10000000)
					C_35 = SLICE(cond(r1_10 - r0), bool, 1);
				if (!C_35)
					r1_10 <<= 0x04;
				if (!C_35)
					r3_118 <<= 0x04;
			} while (C_35);
			do
			{
				bool C_50 = SLICE(cond(r1_10 - (ptr32 *) 0x80000000), bool, 1);
				if (r1_10 < (ptr32 *) 0x80000000)
					C_50 = SLICE(cond(r1_10 - r0), bool, 1);
				if (!C_50)
					r1_10 <<= 0x01;
				if (!C_50)
					r3_118 <<= 0x01;
			} while (C_50);
			do
			{
				ptr32 * r0_67;
				r0_67 = r0;
				if (r0 >= r1_10)
					r0_67 = r0 - r1_10;
				if (r0 >= r1_10)
					r2_109 |= r3_118;
				ptr32 * r0_80;
				r0_80 = r0_67;
				if (r0_67 >= r1_10 >> 0x01)
					r0_80 = r0_67 - (r1_10 >> 0x01);
				if (r0_67 >= r1_10 >> 0x01)
					r2_109 |= r3_118 >> 0x01;
				ptr32 * r0_101;
				r0_101 = r0_80;
				if (r0_80 >= r1_10 >> 0x02)
					r0_101 = r0_80 - (r1_10 >> 0x02);
				if (r0_80 >= r1_10 >> 0x02)
					r2_109 |= r3_118 >> 0x02;
				r0 = r0_101;
				if (r0_101 >= r1_10 >> 0x03)
					r0 = r0_101 - (r1_10 >> 0x03);
				if (r0_101 >= r1_10 >> 0x03)
					r2_109 |= r3_118 >> 0x03;
				bool Z_116 = SLICE(cond(r0), bool, 2);
				if (r0 != null)
				{
					r3_118 >>= 0x04;
					Z_116 = SLICE(cond(r3_118), bool, 2);
				}
				if (!Z_116)
					r1_10 >>= 0x04;
			} while (Z_116);
		}
		ptr32 * r0_133 = r2_109;
		if (ip_5 < 0x00)
			r0_133 = 0x00 - r2_109;
		return r0_133;
	}
}

// 00008638: void __div0(Register (ptr32 ptr32) r0)
void __div0(ptr32 * r0)
{
	__syscall(0x00900014);
	if (r0 >= (ptr32 *) 1000)
		return;
	__syscall(0x00900025);
}

// 00008654: void __libc_csu_init(Register word32 r4, Register word32 r5, Register word32 r6, Register word32 r10, Register ptr32 lr, Register ptr32 pc)
void __libc_csu_init(word32 r4, word32 r5, word32 r6, word32 r10, ptr32 lr, ptr32 pc)
{
	word32 pc_19;
	ptr32 r10_21;
	Eq_331 r4_24;
	word32 r0_20 = _init(0x00, 0x8668 + globals->dw86A4, lr, pc, out r4_24, out r10_21, out pc_19);
	int32 r2_30 = globals->dw86AC;
	<anonymous> * r1_31[] = r10_21 + globals->dw86A8;
	int32 r3_33 = r10_21 + r2_30 - r1_31;
	if (r4_24 >= r3_33 >> 0x02)
		return;
	r1_31[r4_24]();
}

// 000086B0: void __libc_csu_fini(Register word32 r4, Register word32 r5, Register word32 r10, Register word32 lr, Register word32 pc)
void __libc_csu_fini(word32 r4, word32 r5, word32 r10, word32 lr, word32 pc)
{
	ptr32 r10_15 = 0x86C8 + globals->dw8700;
	int32 r2_14 = globals->dw8708;
	<anonymous> * r1_16[] = r10_15 + globals->dw8704;
	int32 r3_18 = r10_15 + r2_14 - r1_16;
	int32 r4_21 = (r3_18 >> 0x02) - 0x01;
	if (r3_18 >> 0x02 == 0x00)
		_fini(r4, r5, lr, pc);
	else
		r1_16[r4_21]();
}

// 0000870C: Register word32 __do_global_ctors_aux(Register word32 r4, Register word32 lr, Register ptr32 pc, Register out ptr32 pcOut)
word32 __do_global_ctors_aux(word32 r4, word32 lr, ptr32 pc, ptr32 & pcOut)
{
	ptr32 r3_8 = globals->ptr8740;
	<anonymous> * r2_9 = *(r3_8 - 0x04);
	if (r2_9 != (<anonymous> *) 0x01)
	{
		word32 r4_16;
		ptr32 pc_20;
		r2_9();
		pcOut = pc_20;
		return r4_16;
	}
	else
	{
		pcOut = pc;
		return r4;
	}
}

// 00008744: void call___do_global_ctors_aux()
void call___do_global_ctors_aux()
{
}

// 0000874C: void _fini(Register word32 r4, Register word32 r5, Register word32 lr, Register word32 pc)
void _fini(word32 r4, word32 r5, word32 lr, word32 pc)
{
	__do_global_dtors_aux(r4, r5, lr, pc);
}

