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

/// @file libc_misc.c

/// @brief Test Case Example for Libc Misc API

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <crc8.h>
#include <crc16.h>
#include <crc32.h>
#include "tc_internal.h"

#define USEC_100 100
#define VAL_50 50
#define VAL_71 71
#define VAL_100 100
#define VAL_192 192
#define VAL_213 213
#define VAL_255 255
#define VAL_65380 65380
#define VAL_CRC32_1 1256170817UL
#define VAL_CRC32_2 3369554304UL
#define VAL_CRC32_3 1742555852UL

/**
 * @fn                  :tc_libc_misc_crc8
 * @brief               :Return a 8-bit CRC of the contents of the 'src_arr' buffer, length 'len' using a
 *                       CRC with the polynomial x^8+x^6+x^3+x^2+1
 * @scenario            :Return a 8-bit CRC of the contents of the 'src_arr' buffer, length 'len' using a
 *                       CRC with the polynomial x^8+x^6+x^3+x^2+1
 * @API's covered       :crc8
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc8(void)
{
	uint8_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	size_t length = 1;

	/* Return value should be 213 as calculated by crc8 */

	ret_chk = crc8(src_arr, length);
	TC_ASSERT_EQ("crc8", ret_chk, VAL_213);

	/* Return value should be 71 as calculated by crc8 */

	src_arr[0] = VAL_50;
	ret_chk = crc8(src_arr, length);
	TC_ASSERT_EQ("crc8", ret_chk, VAL_71);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_crc8part
 * @brief               :Continue CRC calculation on a part of the buffer.
 * @scenario            :Continue CRC calculation on a part of the buffer.
 * @API's covered       :crc8part
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc8part(void)
{
	uint8_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	uint8_t crc_8val = 0;
	size_t length = 1;

	/* Return value should be 213 as calculated by crc8part */

	ret_chk = crc8part(src_arr, length, crc_8val);
	TC_ASSERT_EQ("crc8part", ret_chk, VAL_213);

	/* Return value should be 192 as calculated by crc8part */

	crc_8val = VAL_255;
	ret_chk = crc8part(src_arr, length, crc_8val);
	TC_ASSERT_EQ("crc8part", ret_chk, VAL_192);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_crc16
 * @brief               :Return a 16-bit CRC of the contents of the 'src' buffer, length 'len'
 * @scenario            :Return a 16-bit CRC of the contents of the 'src' buffer, length 'len'
 * @API's covered       :crc16
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc16(void)
{
	uint16_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	size_t length = 1;

	/* Return value should be VAL_100 as calculated by crc16 */

	ret_chk = crc16(src_arr, length);
	TC_ASSERT_EQ("crc16", ret_chk, VAL_100);

	/* Return value should be 50 as calculated by crc16 */

	src_arr[0] = VAL_50;
	ret_chk = crc16(src_arr, length);
	TC_ASSERT_EQ("crc16", ret_chk, VAL_50);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_crc16part
 * @brief               :Continue CRC calculation on a part of the buffer.
 * @scenario            :Continue CRC calculation on a part of the buffer.
 * @API's covered       :crc16part
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc16part(void)
{
	uint16_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	uint16_t crc_16val = 0;
	size_t length = 1;

	/* Return value should be 100 as calculated by crc16part */

	ret_chk = crc16part(src_arr, length, crc_16val);
	TC_ASSERT_EQ("crc16part", ret_chk, VAL_100);

	/* Return value should be 65380 as calculated by crc16part */

	crc_16val = VAL_255;
	ret_chk = crc16part(src_arr, length, crc_16val);
	TC_ASSERT_EQ("crc16part", ret_chk, VAL_65380);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_crc32
 * @brief               :Return a 32-bit CRC of the contents of the 'src' buffer, length 'len'
 * @scenario            :Return a 32-bit CRC of the contents of the 'src' buffer, length 'len'
 * @API's covered       :crc32
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc32(void)
{
	uint32_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	size_t length = 1;

	/* Return value should be 0x4adfa541 as calculated by crc32 */

	ret_chk = crc32(src_arr, length);
	TC_ASSERT_EQ("crc32", ret_chk, VAL_CRC32_1);

	/* Return value should be VAL_CRC32_2 as calculated by crc32 */

	src_arr[0] = VAL_50;
	ret_chk = crc32(src_arr, length);
	TC_ASSERT_EQ("crc32", ret_chk, VAL_CRC32_2);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_crc32part
 * @brief               :Continue CRC calculation on a part of the buffer.
 * @scenario            :Continue CRC calculation on a part of the buffer.
 * @API's covered       :crc32part
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_crc32part(void)
{
	uint32_t ret_chk;
	uint8_t src_arr[1] = { VAL_100 };
	uint32_t crc_32val = 0;
	size_t length = 1;

	/* Return value should be 0x4adfa541 as calculated by crc32part */

	ret_chk = crc32part(src_arr, length, crc_32val);
	TC_ASSERT_EQ("crc32part", ret_chk, (uint32_t)VAL_CRC32_1);

	/* Return value should be 0x67dd4acc as calculated by crc32part */

	crc_32val = VAL_255;
	ret_chk = (uint32_t)crc32part(src_arr, length, crc_32val);
	TC_ASSERT_EQ("crc32part", ret_chk, (uint32_t)VAL_CRC32_3);

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_dbg
 * @brief               :Outputs messages to the console similar to printf() except that the output is not buffered.
 * @scenario            :In general, error messages and output of importance use dbg()
 * @API's covered       :dbg
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_dbg(void)
{
	int ret_chk = ERROR;
	const char *msg_output = "tc_libc_misc_dbg: Examples";
	/*
	   in debug.h file dbg is defined as :
	   # define EXTRA_FMT "%s: "
	   # define EXTRA_ARG ,__FUNCTION__
	   # define dbg(format, ...) \
	   syslog(LOG_ERR, EXTRA_FMT format EXTRA_ARG, ##__VA_ARGS__)
	 */

	/* Message displayed is:  "tc_libc_misc_dbg: Examples" */

	usleep(USEC_100);
	ret_chk = dbg("Examples");
	TC_ASSERT_EQ("dbg", ret_chk, strlen(msg_output));

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_lldbg
 * @brief               :Identical to [a-z]dbg() except this is uses special interfaces provided by architecture-specific logic to \n
 *                       talk directly to the underlying console hardware.
 * @scenario            :lldbg() is particularly useful in low-level code  For example, only lldbg() should be used in interrupt handlers.
 * @API's covered       :lldbg
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_lldbg(void)
{
	int ret_chk = -1;
	const char *msg_output = "tc_libc_misc_lldbg: Examples";
	/*
	   in debug.h file lldbg is defined as :
	   # define EXTRA_FMT "%s: "
	   # define EXTRA_ARG ,__FUNCTION__
	   #  define lldbg(format, ...) \
	   lowsyslog(LOG_ERR, EXTRA_FMT format EXTRA_ARG, ##__VA_ARGS__)
	 */

	/* Message displayed is:  "tc_libc_misc_lldbg: Examples" */

	usleep(USEC_100);
	ret_chk = lldbg("Examples");
	TC_ASSERT_EQ("lldbg", ret_chk, strlen(msg_output));

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_llvdbg
 * @brief               :This is intended for general debug output that is normally suppressed.
 * @scenario            :When debug out is required with all details
 * @API's covered       :llvdbg
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */
static void tc_libc_misc_llvdbg(void)
{
	int ret_chk = -1;
	const char *msg_output = "tc_libc_misc_llvdbg: Examples";
	/*
	   in debug.h file llvdbg is defined as :
	   # define EXTRA_FMT "%s: "
	   # define EXTRA_ARG ,__FUNCTION__
	   # define llvdbg(format, ...) \
	   lowsyslog(LOG_DEBUG, EXTRA_FMT format EXTRA_ARG, ##__VA_ARGS__)
	 */

	/* Message displayed is:  "tc_libc_misc_llvdbg: Examples" */

	usleep(USEC_100);
	ret_chk = llvdbg("Examples");
	TC_ASSERT_EQ("llvdbg", ret_chk, strlen(msg_output));

	TC_SUCCESS_RESULT();
}

/**
 * @fn                  :tc_libc_misc_vdbg
 * @brief               :This is intended for general debug output that is normally suppressed.
 * @scenario            :When debug out is required with all details
 * @API's covered       :vdbg
 * @Preconditions       :None
 * @Postconditions      :None
 * @Return              :void
 */

static void tc_libc_misc_vdbg(void)
{
	int ret_chk = -1;
	const char *msg_output = "tc_libc_misc_vdbg: Examples";
	/*
	   in debug.h file vdbg is defined as :
	   # define EXTRA_FMT "%s: "
	   # define EXTRA_ARG ,__FUNCTION__
	   #  define vdbg(format, ...) \
	   syslog(LOG_DEBUG, EXTRA_FMT format EXTRA_ARG, ##__VA_ARGS__)
	 */

	/* Message displayed is:  "tc_libc_misc_vdbg: Examples" */

	usleep(USEC_100);
	ret_chk = vdbg("Examples");
	TC_ASSERT_EQ("vdbg", ret_chk, strlen(msg_output));

	TC_SUCCESS_RESULT();
}

/****************************************************************************
 * Name: libc_misc
 ****************************************************************************/

int libc_misc_main(void)
{
	tc_libc_misc_crc8();
	tc_libc_misc_crc8part();
	tc_libc_misc_crc16();
	tc_libc_misc_crc16part();
	tc_libc_misc_crc32();
	tc_libc_misc_crc32part();
	tc_libc_misc_dbg();
	tc_libc_misc_lldbg();
	tc_libc_misc_llvdbg();
	tc_libc_misc_vdbg();

	return 0;
}
