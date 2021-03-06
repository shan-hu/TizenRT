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
 * apps/include/netutils/dhcpc.h
 *
 *   Copyright (C) 2007, 2009-2011 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * This logic was leveraged from uIP which also has a BSD-style license:
 *
 *   Copyright (c) 2005, Swedish Institute of Computer Science
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @defgroup DHCP DHCP
 * @brief Provides APIs for DHCP(Dynamic Host Configuration Protocol) Client
 * @ingroup NETWORK
 * @{
 */
/**
 * @file dhcpc.h
 * @brief APIs for DHCP client
 */

#ifndef __APPS_INCLUDE_NETUTILS_DHCPC_H
#define __APPS_INCLUDE_NETUTILS_DHCPC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <netinet/in.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct dhcpc_state {
	struct in_addr serverid;
	struct in_addr ipaddr;
	struct in_addr netmask;
	struct in_addr dnsaddr;
	struct in_addr default_router;
	uint32_t lease_time;		/* Lease expires in this number of seconds */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
// *INDENT-OFF*
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
// *INDENT-ON*
#endif

/**
 * @brief Get DHCP client handle
 *
 * @param[in] intf the name of network interface
 * @param[in] mac_addr the mac address of network interface
 * @param[in] mac_len the length of mac address
 * @return On success, handle. On failure, returns null
 * @since Tizen RT v1.0
 */
void *dhcpc_open(const char *intf);

/**
 * @brief Starts DHCP client
 *
 * @param[in] handle generic data structure that contains dhcpc information
 * @param[out] presult dhcp informations that contain ip address, netmask and gateway
 * @return On success, 0. On failure, returns negative
 * @since Tizen RT v1.0
 */
int dhcpc_request(void *handle, struct dhcpc_state *presult);

/**
 * @brief dhcpc_close() return dhcp client handle
 *
 * @param[in] handle generic data structure that contains dhcpc information
 * @return none
 * @since Tizen RT v1.0
*/
void dhcpc_close(void *handle);

#undef EXTERN
#ifdef __cplusplus
// *INDENT-OFF*
}
// *INDENT-ON*
#endif

#endif							/* __APPS_INCLUDE_NETUTILS_DHCPC_H */
/**@} */
