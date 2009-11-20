/*-
 * Copyright (C) 2002-2003 NetGroup, Politecnico di Torino (Italy)
 * Copyright (C) 2005-2009 Jung-uk Kim <jkim@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Politecnico di Torino nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#ifdef _KERNEL
#include "opt_bpf.h"
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/socket.h>
#include <sys/malloc.h>
#include <net/if.h>
#else
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/param.h>
#endif

#include <sys/types.h>

#include <net/bpf.h>
#include <net/bpf_jitter.h>

#include <amd64/amd64/bpf_jit_machdep.h>

bpf_filter_func	bpf_jit_compile(struct bpf_insn *, u_int, size_t *);

/*
 * emit routine to update the jump table
 */
static void
emit_length(bpf_bin_stream *stream, __unused u_int value, u_int len)
{

	(stream->refs)[stream->bpf_pc] += len;
	stream->cur_ip += len;
}

/*
 * emit routine to output the actual binary code
 */
static void
emit_code(bpf_bin_stream *stream, u_int value, u_int len)
{

	switch (len) {
	case 1:
		stream->ibuf[stream->cur_ip] = (u_char)value;
		stream->cur_ip++;
		break;

	case 2:
		*((u_short *)(stream->ibuf + stream->cur_ip)) = (u_short)value;
		stream->cur_ip += 2;
		break;

	case 4:
		*((u_int *)(stream->ibuf + stream->cur_ip)) = value;
		stream->cur_ip += 4;
		break;
	}

	return;
}

/*
 * Function that does the real stuff
 */
bpf_filter_func
bpf_jit_compile(struct bpf_insn *prog, u_int nins, size_t *size)
{
	bpf_bin_stream stream;
	struct bpf_insn *ins;
	u_int i, pass;

	/*
	 * NOTE: Do not modify the name of this variable, as it's used by
	 * the macros to emit code.
	 */
	emit_func emitm;

	/* Allocate the reference table for the jumps. */
#ifdef _KERNEL
	stream.refs = malloc((nins + 1) * sizeof(u_int), M_BPFJIT,
	    M_NOWAIT | M_ZERO);
#else
	stream.refs = malloc((nins + 1) * sizeof(u_int));
#endif
	if (stream.refs == NULL)
		return (NULL);
#ifndef _KERNEL
	memset(stream.refs, 0, (nins + 1) * sizeof(u_int));
#endif

	stream.cur_ip = 0;
	stream.bpf_pc = 0;
	stream.ibuf = NULL;

	/*
	 * The first pass will emit the lengths of the instructions
	 * to create the reference table.
	 */
	emitm = emit_length;

	for (pass = 0; pass < 2; pass++) {
		ins = prog;

		/* Create the procedure header. */
		PUSH(RBP);
		MOVrq(RSP, RBP);
		SUBib(BPF_MEMWORDS * sizeof(uint32_t), RSP);
		MOVrq2(RDI, R8);
		MOVrd2(ESI, R9D);
		MOVrd(EDX, EDI);

		for (i = 0; i < nins; i++) {
			stream.bpf_pc++;

			switch (ins->code) {
			default:
#ifdef _KERNEL
				return (NULL);
#else
				abort();
#endif

			case BPF_RET|BPF_K:
				MOVid(ins->k, EAX);
				LEAVE_RET();
				break;

			case BPF_RET|BPF_A:
				LEAVE_RET();
				break;

			case BPF_LD|BPF_W|BPF_ABS:
				MOVid(ins->k, ESI);
				CMPrd(EDI, ESI);
				JAb(12);
				MOVrd(EDI, ECX);
				SUBrd(ESI, ECX);
				CMPid(sizeof(int32_t), ECX);
				JAEb(4);
				ZEROrd(EAX);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				MOVobd(RCX, RSI, EAX);
				BSWAP(EAX);
				break;

			case BPF_LD|BPF_H|BPF_ABS:
				ZEROrd(EAX);
				MOVid(ins->k, ESI);
				CMPrd(EDI, ESI);
				JAb(12);
				MOVrd(EDI, ECX);
				SUBrd(ESI, ECX);
				CMPid(sizeof(int16_t), ECX);
				JAEb(2);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				MOVobw(RCX, RSI, AX);
				SWAP_AX();
				break;

			case BPF_LD|BPF_B|BPF_ABS:
				ZEROrd(EAX);
				MOVid(ins->k, ESI);
				CMPrd(EDI, ESI);
				JBb(2);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				MOVobb(RCX, RSI, AL);
				break;

			case BPF_LD|BPF_W|BPF_LEN:
				MOVrd3(R9D, EAX);
				break;

			case BPF_LDX|BPF_W|BPF_LEN:
				MOVrd3(R9D, EDX);
				break;

			case BPF_LD|BPF_W|BPF_IND:
				CMPrd(EDI, EDX);
				JAb(27);
				MOVid(ins->k, ESI);
				MOVrd(EDI, ECX);
				SUBrd(EDX, ECX);
				CMPrd(ESI, ECX);
				JBb(14);
				ADDrd(EDX, ESI);
				MOVrd(EDI, ECX);
				SUBrd(ESI, ECX);
				CMPid(sizeof(int32_t), ECX);
				JAEb(4);
				ZEROrd(EAX);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				MOVobd(RCX, RSI, EAX);
				BSWAP(EAX);
				break;

			case BPF_LD|BPF_H|BPF_IND:
				ZEROrd(EAX);
				CMPrd(EDI, EDX);
				JAb(27);
				MOVid(ins->k, ESI);
				MOVrd(EDI, ECX);
				SUBrd(EDX, ECX);
				CMPrd(ESI, ECX);
				JBb(14);
				ADDrd(EDX, ESI);
				MOVrd(EDI, ECX);
				SUBrd(ESI, ECX);
				CMPid(sizeof(int16_t), ECX);
				JAEb(2);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				MOVobw(RCX, RSI, AX);
				SWAP_AX();
				break;

			case BPF_LD|BPF_B|BPF_IND:
				ZEROrd(EAX);
				CMPrd(EDI, EDX);
				JAEb(13);
				MOVid(ins->k, ESI);
				MOVrd(EDI, ECX);
				SUBrd(EDX, ECX);
				CMPrd(ESI, ECX);
				JAb(2);
				LEAVE_RET();
				MOVrq3(R8, RCX);
				ADDrd(EDX, ESI);
				MOVobb(RCX, RSI, AL);
				break;

			case BPF_LDX|BPF_MSH|BPF_B:
				MOVid(ins->k, ESI);
				CMPrd(EDI, ESI);
				JBb(4);
				ZEROrd(EAX);
				LEAVE_RET();
				ZEROrd(EDX);
				MOVrq3(R8, RCX);
				MOVobb(RCX, RSI, DL);
				ANDib(0x0f, DL);
				SHLib(2, EDX);
				break;

			case BPF_LD|BPF_IMM:
				MOVid(ins->k, EAX);
				break;

			case BPF_LDX|BPF_IMM:
				MOVid(ins->k, EDX);
				break;

			case BPF_LD|BPF_MEM:
				MOVid(ins->k * sizeof(uint32_t), ESI);
				MOVobd(RSP, RSI, EAX);
				break;

			case BPF_LDX|BPF_MEM:
				MOVid(ins->k * sizeof(uint32_t), ESI);
				MOVobd(RSP, RSI, EDX);
				break;

			case BPF_ST:
				/*
				 * XXX this command and the following could
				 * be optimized if the previous instruction
				 * was already of this type
				 */
				MOVid(ins->k * sizeof(uint32_t), ESI);
				MOVomd(EAX, RSP, RSI);
				break;

			case BPF_STX:
				MOVid(ins->k * sizeof(uint32_t), ESI);
				MOVomd(EDX, RSP, RSI);
				break;

			case BPF_JMP|BPF_JA:
				JMP(stream.refs[stream.bpf_pc + ins->k] -
				    stream.refs[stream.bpf_pc]);
				break;

			case BPF_JMP|BPF_JGT|BPF_K:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPid(ins->k, EAX);
				JCC(JA, JBE);
				break;

			case BPF_JMP|BPF_JGE|BPF_K:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPid(ins->k, EAX);
				JCC(JAE, JB);
				break;

			case BPF_JMP|BPF_JEQ|BPF_K:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPid(ins->k, EAX);
				JCC(JE, JNE);
				break;

			case BPF_JMP|BPF_JSET|BPF_K:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				TESTid(ins->k, EAX);
				JCC(JNE, JE);
				break;

			case BPF_JMP|BPF_JGT|BPF_X:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPrd(EDX, EAX);
				JCC(JA, JBE);
				break;

			case BPF_JMP|BPF_JGE|BPF_X:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPrd(EDX, EAX);
				JCC(JAE, JB);
				break;

			case BPF_JMP|BPF_JEQ|BPF_X:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				CMPrd(EDX, EAX);
				JCC(JE, JNE);
				break;

			case BPF_JMP|BPF_JSET|BPF_X:
				if (ins->jt == 0 && ins->jf == 0)
					break;
				TESTrd(EDX, EAX);
				JCC(JNE, JE);
				break;

			case BPF_ALU|BPF_ADD|BPF_X:
				ADDrd(EDX, EAX);
				break;

			case BPF_ALU|BPF_SUB|BPF_X:
				SUBrd(EDX, EAX);
				break;

			case BPF_ALU|BPF_MUL|BPF_X:
				MOVrd(EDX, ECX);
				MULrd(EDX);
				MOVrd(ECX, EDX);
				break;

			case BPF_ALU|BPF_DIV|BPF_X:
				TESTrd(EDX, EDX);
				JNEb(4);
				ZEROrd(EAX);
				LEAVE_RET();
				MOVrd(EDX, ECX);
				ZEROrd(EDX);
				DIVrd(ECX);
				MOVrd(ECX, EDX);
				break;

			case BPF_ALU|BPF_AND|BPF_X:
				ANDrd(EDX, EAX);
				break;

			case BPF_ALU|BPF_OR|BPF_X:
				ORrd(EDX, EAX);
				break;

			case BPF_ALU|BPF_LSH|BPF_X:
				MOVrd(EDX, ECX);
				SHL_CLrb(EAX);
				break;

			case BPF_ALU|BPF_RSH|BPF_X:
				MOVrd(EDX, ECX);
				SHR_CLrb(EAX);
				break;

			case BPF_ALU|BPF_ADD|BPF_K:
				ADD_EAXi(ins->k);
				break;

			case BPF_ALU|BPF_SUB|BPF_K:
				SUB_EAXi(ins->k);
				break;

			case BPF_ALU|BPF_MUL|BPF_K:
				MOVrd(EDX, ECX);
				MOVid(ins->k, EDX);
				MULrd(EDX);
				MOVrd(ECX, EDX);
				break;

			case BPF_ALU|BPF_DIV|BPF_K:
				MOVrd(EDX, ECX);
				ZEROrd(EDX);
				MOVid(ins->k, ESI);
				DIVrd(ESI);
				MOVrd(ECX, EDX);
				break;

			case BPF_ALU|BPF_AND|BPF_K:
				ANDid(ins->k, EAX);
				break;

			case BPF_ALU|BPF_OR|BPF_K:
				ORid(ins->k, EAX);
				break;

			case BPF_ALU|BPF_LSH|BPF_K:
				SHLib((ins->k) & 0xff, EAX);
				break;

			case BPF_ALU|BPF_RSH|BPF_K:
				SHRib((ins->k) & 0xff, EAX);
				break;

			case BPF_ALU|BPF_NEG:
				NEGd(EAX);
				break;

			case BPF_MISC|BPF_TAX:
				MOVrd(EAX, EDX);
				break;

			case BPF_MISC|BPF_TXA:
				MOVrd(EDX, EAX);
				break;
			}
			ins++;
		}

		if (pass > 0)
			continue;

		*size = stream.cur_ip;
#ifdef _KERNEL
		stream.ibuf = malloc(*size, M_BPFJIT, M_NOWAIT);
		if (stream.ibuf == NULL)
			break;
#else
		stream.ibuf = mmap(NULL, *size, PROT_READ | PROT_WRITE,
		    MAP_ANON, -1, 0);
		if (stream.ibuf == MAP_FAILED) {
			stream.ibuf = NULL;
			break;
		}
#endif

		/*
		 * Modify the reference table to contain the offsets and
		 * not the lengths of the instructions.
		 */
		for (i = 1; i < nins + 1; i++)
			stream.refs[i] += stream.refs[i - 1];

		/* Reset the counters. */
		stream.cur_ip = 0;
		stream.bpf_pc = 0;

		/* The second pass creates the actual code. */
		emitm = emit_code;
	}

	/*
	 * The reference table is needed only during compilation,
	 * now we can free it.
	 */
#ifdef _KERNEL
	free(stream.refs, M_BPFJIT);
#else
	free(stream.refs);
	if (stream.ibuf != NULL &&
	    mprotect(stream.ibuf, *size, PROT_READ | PROT_EXEC) != 0) {
		munmap(stream.ibuf, *size);
		stream.ibuf = NULL;
	}
#endif

	return ((bpf_filter_func)stream.ibuf);
}
