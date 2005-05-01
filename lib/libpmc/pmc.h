/*-
 * Copyright (c) 2003,2004 Joseph Koshy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _PMC_H_
#define _PMC_H_

#include <sys/pmc.h>

/*
 * Prototypes
 */

int	pmc_allocate(const char *_ctrspec, enum pmc_mode _mode, uint32_t _flags,
    int _cpu, pmc_id_t *_pmcid);
int	pmc_attach(pmc_id_t _pmcid, pid_t _pid);
int	pmc_capabilities(pmc_id_t _pmc, uint32_t *_caps);
int	pmc_configure_logfile(int _fd);
int	pmc_detach(pmc_id_t _pmcid, pid_t _pid);
int	pmc_disable(int _cpu, int _pmc);
int	pmc_enable(int _cpu, int _pmc);
int	pmc_get_driver_stats(struct pmc_op_getdriverstats *_gms);
int	pmc_init(void);
int	pmc_read(pmc_id_t _pmc, pmc_value_t *_value);
int	pmc_release(pmc_id_t _pmc);
int	pmc_rw(pmc_id_t _pmc, pmc_value_t _newvalue, pmc_value_t *_oldvalue);
int	pmc_set(pmc_id_t _pmc, pmc_value_t _value);
int	pmc_start(pmc_id_t _pmc);
int	pmc_stop(pmc_id_t _pmc);
int	pmc_width(pmc_id_t _pmc, uint32_t *_width);
int	pmc_write(pmc_id_t _pmc, pmc_value_t _value);

int	pmc_ncpu(void);
int	pmc_npmc(int _cpu);
int	pmc_cpuinfo(const struct pmc_op_getcpuinfo **_cpu_info);
int	pmc_pmcinfo(int _cpu, struct pmc_op_getpmcinfo **_pmc_info);

const char	*pmc_name_of_capability(uint32_t _c);
const char	*pmc_name_of_class(enum pmc_class _pc);
const char	*pmc_name_of_cputype(enum pmc_cputype _cp);
const char	*pmc_name_of_disposition(enum pmc_disp _pd);
const char	*pmc_name_of_event(enum pmc_event _pe);
const char	*pmc_name_of_mode(enum pmc_mode _pm);
const char	*pmc_name_of_state(enum pmc_state _ps);

int	pmc_event_names_of_class(enum pmc_class _cl, const char ***_eventnames,
    int *_nevents);

/*
 * Architecture specific extensions
 */

#if __i386__ || __amd64__
int	pmc_x86_get_msr(pmc_id_t _pmc, uint32_t *_msr);
#endif

#endif
