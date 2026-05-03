/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup ValDummy
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

#include <dummy.h>

#include <rtems/test.h>

/**
 * @defgroup ValDummy spec:/val/dummy
 *
 * @ingroup TestsuitesValidation0
 *
 * @brief Tests some @ref RTEMSAPI interfaces.
 *
 * This test case performs the following actions:
 *
 * - Validate dummy_add().
 *
 *   - Check that the result has the expected value.
 *
 * @{
 */

/**
 * @brief Validate dummy_add().
 */
static void ValDummy_Action_0( void )
{
  int result = dummy_add( 1, 2 );

  /*
   * Check that the result has the expected value.
   */
  T_eq_int( result, 3 );
}

/**
 * @fn void T_case_body_ValDummy( void )
 */
T_TEST_CASE( ValDummy )
{
  ValDummy_Action_0();
}

/** @} */
