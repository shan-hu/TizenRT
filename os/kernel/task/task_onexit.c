/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * kernel/task/task_onexit.c
 *
 *   Copyright (C) 2012-2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <debug.h>
#include <errno.h>

#include <tinyara/fs/fs.h>

#include "sched/sched.h"
#include "task/task.h"
#include <ttrace.h>

#ifdef CONFIG_SCHED_ONEXIT

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Type Declarations
 ****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/****************************************************************************
 * Private Variables
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: on_exit
 *
 * Description:
 *    Registers a function to be called at program exit.
 *    The on_exit() function registers the given function to be called
 *    at normal process termination, whether via exit or via return from
 *    the program's main(). The function is passed the status argument
 *    given to the last call to exit and the arg argument from on_exit().
 *
 *    NOTE 1: This function comes from SunOS 4, but is also present in
 *    libc4, libc5 and glibc. It no longer occurs in Solaris (SunOS 5).
 *    Avoid this function, and use the standard atexit() instead.
 *
 *    NOTE 2: CONFIG_SCHED_ONEXIT must be defined to enable this function
 *
 *    Limitiations in the current implementation:
 *
 *      1. Only a single on_exit function can be registered unless
 *         CONFIG_SCHED_ONEXIT_MAX defines a larger number.
 *      2. on_exit functions are not inherited when a new task is
 *         created.
 *
 * Parameters:
 *   func - A pointer to the function to be called when the task exits.
 *   arg -  An argument that will be provided to the on_exit() function when
 *          the task exits.
 *
 * Return Value:
 *   Zero on success. Non-zero on failure.
 *
 ****************************************************************************/

int on_exit(CODE void (*func)(int, FAR void *), FAR void *arg)
{
#if defined(CONFIG_SCHED_ONEXIT_MAX) && CONFIG_SCHED_ONEXIT_MAX > 1
	FAR struct tcb_s *tcb = (FAR struct tcb_s *)g_readytorun.head;
	FAR struct task_group_s *group = tcb->group;
	int index;
	int ret = ENOSPC;

	trace_begin(TTRACE_TAG_TASK, "on_exit");
	DEBUGASSERT(group);

	/* The following must be atomic */

	if (func) {
		sched_lock();

		/* Search for the first available slot.  on_exit() functions are registered
		 * from lower to higher arry indices; they must be called in the reverse
		 * order of registration when task exists, i.e., from higher to lower
		 * indices.
		 */

		for (index = 0; index < CONFIG_SCHED_ONEXIT_MAX; index++) {
			if (!group->tg_onexitfunc[index]) {
				group->tg_onexitfunc[index] = func;
				group->tg_onexitarg[index] = arg;
				ret = OK;
				break;
			}
		}

		sched_unlock();
	}
	trace_end(TTRACE_TAG_TASK);
	return ret;
#else
	FAR struct tcb_s *tcb = (FAR struct tcb_s *)g_readytorun.head;
	FAR struct task_group_s *group = tcb->group;
	int ret = ENOSPC;

	DEBUGASSERT(group);

	/* The following must be atomic */

	sched_lock();
	if (func && !group->tg_onexitfunc) {
		group->tg_onexitfunc = func;
		group->tg_onexitarg = arg;
		ret = OK;
	}

	sched_unlock();
	trace_end(TTRACE_TAG_TASK);
	return ret;
#endif
}

#endif							/* CONFIG_SCHED_ONEXIT */
