.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

.. _Margin_Budget_Status:

Margin and Technical Budget Status
**********************************

The question to answer is whether there is enough
CPU computing power and memory in the embedded
hardware so that a given (real-time) application
can be executed successfully even in the worst case.

    * Is there enough memory ...

        + to store the code?
        + to store all data?
        + for each thread: to store function call frames on the stack?

    * Are the CPU cores fast enough to meet all
      real time deadlines?

    * Especially, will the application operate close to some memory
      or computing power limits of the hardware or will there be a lot
      of room for safety margins?

These questions can only be answered for an application built on top
of the pre-qualified part of the :term:`RTEMS` operating system.
The sections below report on the memory use and computing power
consumption of the :term:`RTEMS` operating system and its :term:`ABI`
functions. This shall enable application developers to calculate
the technical budgets and margins for their applications.

.. _TechnicalBudgetsAndMarginsComputation:

Technical Budgets and Margins Computation
=========================================

Section  *4.6 Guidelines for the Application Build* and
subsections of the accompanying |SCF| ${/pkg/deployment/doc-package-manual:/cite} describe how a
user of this :term:`QDP` can calculate the technical budgets and margins
for her application.

Moreover, the mentioned subsections also provide the
numbers for memory consumption while the numbers for time consumption
can be found in this :term:`SVR` in subsections *Test Suite - Performance0*
of chapter :ref:`SoftwareTestReports` and following chapters.
For accurate results, the performance tests for the time figures may need to
be re-run on the users hardware while the memory consumption will
not change as long as the instruction set architecture is not completely
different.

.. _`Issue #659`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/659

.. What applications need to calculate is:
   * memory consumption
      ** static code size
      ** static data size
      ** Stack size
         per thread measured on lowest level component
   * computing power (that is, time) consumption
      ** CPU utilization (worst case)
      ** deadline fulfillment
      ** I: process interference time, the time that the
         process can be interrupted by processes of
         higher priority
      ** B: process blocking time, the time that the
         process can be blocked on a protected object
         access by a process of lower priority

.. _SoftwareBudget:

Software Budget (Sizing and Timing)
===================================

Static Memory Usage Benchmarks
------------------------------

The software budget in terms of memory consumption (sizing) and timing of
services of ${/glossary/rtems:/term} is provided by memory and runtime
performance benchmark programs.  The memory benchmarks are presented also in
the *Static Memory Usage Benchmarks* section of the |SCF| ${/pkg/deployment/doc-package-manual:/cite}.  The
results of the memory benchmarks can be used by an application designer to
estimate the static memory consumption if certain services of the operating
system (for example tasks, message queues, semaphores) are used by the
application.  All objects used by services of the pre-qualified feature set of
RTEMS are statically allocated by the linker.

${.:/memory-benchmarks:2}

Performance Measurement Results
-------------------------------

The timing of operating system services (for example obtaining an available
mutex) is measured by runtime performance benchmark programs.  The benchmarks
exercise typical usage scenarios of operating system services.  The measured
scenarios are executed in different ${/glossary/target:/term} system
environments to estimate best case and worst case timings.  The execution
environments and the runtime performance measurement approach are described in
the
`Code Runtime Measurements <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/test-framework.html#code-runtime-measurements>`_
section of the |RSE| manual ${/ref/rtems/eng:/cite}.  The table below lists
all runtime performance requirements.  For each requirement, target- and
configuration-specific margins are specified for measured timing values such as
the minimum, median, and maximum execution duration of a specified and measured
code path.  The status indicates if the actually measured timings on the target
are within the specified margins (``P``) or not (``F``).

${.:/performance-summary}

* **Reviewer:** Frank Kühndel (embedded brains)
* **Review Date:** 2021-12-08, review 2021-10-21 opened `Issue #770`_
* **Input Item:** Table *Performance Requirement Status* above for a
  GR712RC :term:`SMP` build with tests on the simulator only
  (:term:`QDP` build from commit ``dac80a461c3dfa6e5ca1eae625744da13c5f50d``).
* **Compliant:** OK
* **Verification:**

    + All test are passed ("P").
    + All test have an associated specification.

.. _`Issue #770`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/770

Schedulability Simulation and Analysis
======================================

Not applicable because schedulability analysis and simulation
can only be performed for an application.
