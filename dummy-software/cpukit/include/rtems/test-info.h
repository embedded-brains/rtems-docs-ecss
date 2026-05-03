/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup RTEMSTest
 *
 * @brief This header file provides interfaces of the RTEMS Test Support.
 */

/*
 * Copyright (C) 2014, 2018 embedded brains GmbH & Co. KG
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _RTEMS_TEST_INFO_H
#define _RTEMS_TEST_INFO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup RTEMSTest Test Support
 *
 * @ingroup RTEMSAPI
 *
 * @brief Test support functions.
 *
 * @{
 */

/**
 * @brief Each test must define a test name string.
 */
extern const char rtems_test_name[];

/**
 * @brief Test states.
 */
typedef enum
{
  RTEMS_TEST_STATE_PASS,
  RTEMS_TEST_STATE_FAIL,
  RTEMS_TEST_STATE_USER_INPUT,
  RTEMS_TEST_STATE_INDETERMINATE,
  RTEMS_TEST_STATE_BENCHMARK
} RTEMS_TEST_STATE;

#if (TEST_STATE_EXPECTED_FAIL && TEST_STATE_USER_INPUT) || \
    (TEST_STATE_EXPECTED_FAIL && TEST_STATE_INDETERMINATE) || \
    (TEST_STATE_EXPECTED_FAIL && TEST_STATE_BENCHMARK) || \
    (TEST_STATE_USER_INPUT    && TEST_STATE_INDETERMINATE) || \
    (TEST_STATE_USER_INPUT    && TEST_STATE_BENCHMARK) || \
    (TEST_STATE_INDETERMINATE && TEST_STATE_BENCHMARK)
  #error Test states must be unique
#endif

#if TEST_STATE_EXPECTED_FAIL
  #define TEST_STATE RTEMS_TEST_STATE_FAIL
#elif TEST_STATE_USER_INPUT
  #define TEST_STATE RTEMS_TEST_STATE_USER_INPUT
#elif TEST_STATE_INDETERMINATE
  #define TEST_STATE RTEMS_TEST_STATE_INDETERMINATE
#elif TEST_STATE_BENCHMARK
  #define TEST_STATE RTEMS_TEST_STATE_BENCHMARK
#else
  #define TEST_STATE RTEMS_TEST_STATE_PASS
#endif

/**
 * @brief Prints a begin of test message using printf().
 *
 * @return As specified by printf().
 */
int rtems_test_begin(const char* name, const RTEMS_TEST_STATE state);

/**
 * @brief Prints an end of test message using printf().
 *
 * @return As specified by printf().
 */
int rtems_test_end(const char* name);

/**
 * @brief Dumps the gcov information as a base64 encoded gcfn and gcda data
 *   stream using rtems_put_char().
 */
void rtems_test_gcov_dump_info( void );

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RTEMS_TEST_INFO_H */
