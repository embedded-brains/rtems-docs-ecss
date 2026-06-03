.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2026 embedded brains GmbH & Co. KG

.. _Introduction:

Introduction
************

The document is intended to be used by reviewers and qualification authorities.
For users of the package, it is recommended to get started by reading the
${/pkg/deployment/doc-package-manual:/cite-long}.  For using
${/glossary/rtems:/term} in general, please refer to the
${/ref/rtems/user:/cite-long} and the ${/ref/rtems/c-user:/cite-long}.

${.:/push-enabled-by:pkg.feature.qual}
The Software Integration Test Report, Software Unit Test Report, and Software
Validation Report with Respect to ${/glossary/ts:/term} are parts of the
Design Justification File (DJF) as required by ${/ref/ecss/e-st-40c:/cite-long}
and ${/ref/ecss/q-st-80c-r1:/cite-long}.  As a deviation from these
${/glossary/ecss:/term} standards, this document contains all test reports
specified by the ${doc-djf-suitp:/cite-long} and the ${doc-djf-svs:/cite-long}.
In addition, the results of the baseline RTEMS test suites and examples are
included.
${.:/pop-enabled-by}

For each target, the test results are presented grouped by the
${/glossary/bsp:/term} configurations.

For this test report, the following test logs and coverage data were used:

${.:/input-file-list-with-hashes:relpath=%(/pkg/component:/deployment-directory),test-aggregation,test-coverage test-log}

For this test report, specification inputs were used.  For example, the
specified runtime performance limits were used to evaluate the measured runtime
performance data.  If a test property check fails, then a matching test failure
verification is searched.  When a test failure verification is found
specifically for the failed check, the failed check results in an expected test
failure.

For this test report, the following verification checks were performed:

* For each target, all specified validation tests have test results or a
  justified exception.

* For each output of a test executable run:

  * The begin-of-test message is present.

  * The end-of-test message is present.

  * The reported RTEMS version has the expected value.

  * All expected build configuration options are listed.

  * No unexpected build configuration option is listed.

  * The reported tools version has the expected value.

* For each output of a test suite executable run:

  * The reported compiler version has the expected value.

  * The reported RTEMS Git commit has the expected value.

  * The reported BSP name has the expected value.

  * The reported build label has the expected value.

  * The reported target hash has the expected value.

  * The reported RTEMS_DEBUG build configuration option has the expected value.

  * The reported RTEMS_MULTIPROCESSING build configuration option has the
    expected value.

  * The reported RTEMS_POSIX_API build configuration option has the expected
    value.

  * The reported RTEMS_PROFILING build configuration option has the expected
    value.

  * The reported RTEMS_SMP build configuration option has the expected value.

  * The reported test step count is positive.

  * The reported failed test steps count is zero.

  * The reported test duration has the expected value.

  * The report hash has the expected value.

* For each output of a test suite executable run with runtime performance
  measurements:

  * All reported maximum runtime values are less than or equal to the expected
    limit.

  * All reported median runtime values are in the expected interval.

  * All reported minimum runtime values are greater than or equal to the
    expected limit.

* Where code coverage data is registered for the test report:

  * The code coverage data is present.

  * The overall function coverage is above the specified limit.

  * The overall line coverage is above the specified limit.

  * The overall branch coverage is above the specified limit.

  * For each file with code coverage data:

    * The function coverage is above the specified file-specific limit.

    * The line coverage is above the specified file-specific limit.

    * The branch coverage is above the specified file-specific limit.

  * For code coverage gap justifications:

    * All present code coverage justifications are used.

    * There are no unrelated code coverage justification areas specified.

    * The specified line coverage justification areas relate to the present
      source code.

    * The specified branch coverage justification areas relate to the present
      source code.
