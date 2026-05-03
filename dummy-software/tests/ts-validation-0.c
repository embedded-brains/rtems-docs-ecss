/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup TestsuitesValidation0
 */

/*
 * Copyright (C) 2026 embedded brains GmbH & Co. KG
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

/*
 * This file was automatically generated.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <dummy/options.h>
#include <rtems/bspIo.h>
#include <rtems/test-info.h>

#include <rtems/test.h>

/**
 * @defgroup TestsuitesValidation0 spec:/testsuites/validation-0
 *
 * @ingroup RTEMSTestSuitesValidation
 *
 * @brief This general purpose validation test suite provides enough resources
 *   to run basic tests for all specified managers and functions.
 *
 * @{
 */

const char rtems_test_name[] = "TestsuitesValidation0";

static char buffer[ 512 ];

static void OutputChar( char c )
{
  putchar( (char)c );
}

BSP_output_char_function_type BSP_output_char = OutputChar;

void rtems_putc( char c )
{
  BSP_output_char_function_type output_char;

  output_char = BSP_output_char;

  ( *output_char )( c );
}

void rtems_put_char( int c, void *arg )
{
  (void) arg;
  rtems_putc( (char) c );
}

static const T_action actions[] = {
  T_report_hash_sha256_output_char
};

static const T_config config = {
  .name = rtems_test_name,
  .buf = buffer,
  .buf_size = sizeof( buffer ),
  .putchar = rtems_put_char,
  .verbosity = T_NORMAL,
  .now = T_now_clock,
  .allocate = malloc,
  .deallocate = free,
  .action_count = T_ARRAY_SIZE( actions ),
  .actions = actions
};

int main(void)
{
  rtems_test_begin( rtems_test_name, RTEMS_TEST_STATE_PASS );
  T_register();

  int exit_code = T_main( &config );

  if (exit_code == 0) {
    rtems_test_end( rtems_test_name );
  }

#ifdef RTEMS_GCOV_COVERAGE
  rtems_test_gcov_dump_info();
#endif

  return exit_code;
}

/** @} */
