.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2021 embedded brains GmbH & Co. KG

.. _Introduction:

Introduction
************

The Software Unit Test Plan and the Software Integration Test Plan are parts of
the Design Justification File (DJF) as required by
${/ref/ecss/e-st-40c:/cite-long} and ${/ref/ecss/q-st-80c-r1:/cite-long}.  The
document is intended to be used by reviewers and qualification authorities.
For users of the ${/glossary/qdp:/term} and ${/glossary/rtems:/term} it is
recommended to get started by reading the
${/pkg/deployment/doc-package-manual:/cite-long}.  For using RTEMS in general,
please refer to the ${/ref/rtems/user:/cite-long} and the
${/ref/rtems/c-user:/cite-long}.

The specification of RTEMS is done using so-called specification items.  For an
overview of the specification approach see the
`Software Requirements Engineering <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/index.html>`_
chapter in the ${/ref/rtems/eng:/cite-long}.  The test suites and test cases
presented in this document are specified using specification items.  The items
contain source code fragments which are used to generate source files for test
suites and test cases.

${/glossary/ecss:/term} requires separate documents for the plans, one for the
unit tests and one for the integration tests.  The first deviation from ECSS is
that this activity provides a combined unit and integration test plan.  The
boundaries between unit and integration tests for a fully developed and mature
software product which ships in the form of two static libraries
(``librtemsbsp.a`` and ``librtemscpu.a``) are vague. To avoid the trouble of
giving a precise definition of what unit and integration tests are with respect
to each other they are combined into one set of tests.

The second deviation from ECSS is that unit and integration tests are not
provided in general.  They may be provided on demand.  The RTEMS design and
development started in the 1980s.  The software industry discovered the value
of unit tests after this decade.  The initial RTEMS test suite contained no
unit tests and currently there are only a couple of unit tests in the RTEMS
test suite.  The approach of the RTEMS Project was always to do the testing at
the ${/glossary/api:/term} level even for tests which target internal
implementation functions, see for example this discussion on the RTEMS
development mailing list: `[PATCH 3/3] smpschedsem01: New test Test to verify
task priority is inherited from a semaphore.
<https://lists.rtems.org/pipermail/devel/2014-June/035043.html>`_ The main
reason for this is to find code which is not used by an API through code
coverage analysis.  The purpose of RTEMS is to provide an API.  All code which
is not needed by an API is superfluous and should be removed or deactivated.

The spirit of the RTEMS test suite is to do unit tests of internal functions
through API level calls.  This is also the benchmark for the validation tests
developed by this activity.  The
`Action Requirement Item Type <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/items.html#spectypeactionrequirementitemtype>`_
specification items allow a very detailed specification of functions.  See also
`How-To - Action Requirements <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/howto.html#action-requirements>`_.
For directives, not only the function parameters are considered, but also
states of the system relevant to the directive call.  Examples are the state of
threads which are affected by the directive, the execution context and mode of
the caller, interrupts which happen during the directive call, activity on
other processors during the directive call, and the state of the object
accessed by the directive.  The RTEMS Test Framework which was developed for
this activity provides support for
`Interrupt Tests <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/test-framework.html#interrupt-tests>`_.

The goal of this activity is to reach 100% statement and branch coverage
through validation tests.  Once this is achieved, this will show that
everything in the implementation serves a purpose defined at API level.  One
problem with this approach is that it is not immediately clear for a given
software unit to which requirements it belongs.  It would be very labour
intensive to explicitly link each unit to a set of requirements.  It would be
also hard to maintain this information.  For a given unit, the source code and
${/glossary/sdd:/term} could be used to manually get this information.  A
verification activity could do this for a random sample set of units.

For an operating system, there are some difficulties if unit tests for all
units should be carried out.  Some units change the state of the processor at
register level.  This makes mocking difficult.  The inputs to units are not only
passed as parameters, there is a considerable amount of global state in the
system.  The test execution may be controlled by the system under test.  For an
operating system which is developed from scratch it would make sense to write a
mocking framework to do unit tests right from the beginning of the development.
However, RTEMS is a fully designed, developed, and tested software product.  In
this case, it is more efficient to avoid any mocking and instead set up the
pre-conditions for tests through the already existing API level functions.
This is what we do for the validation tests.

Unit and integration tests will only be performed on a subset of units in case
validation tests are difficult to carry out or insufficient.  For example, unit
tests may be done for the chain and red-black tree data structures.

The systematic specification and validation approach through
`Action Requirement Item Type <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/items.html#spectypeactionrequirementitemtype>`_
specification items has proven by example that it is capable to find
shortcomings in the RTEMS code base which were not surfaced by the existing
RTEMS test suite, for example:

* `#4230: Timeout for automatic barriers is broken <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4230>`_

* `#4244: Possible infinite recursion in Classic API Signal handling <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4244>`_

* `#4270: A failing task extension produces zombie objects and resource leaks <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4270>`_

* `#4338: rtems_clock_set(): Cannot set future dates later than approximately 2105 <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4338>`_

* `#4390: Make zero size allocation result consistent across directives <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4390>`_

* `#4401: rtems: Change rtems_scheduler_get_processor_set() status <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4401>`_

* `#4403: rtems_timer_fire_when() returns wrong status code when wall_time argument is NULL <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4403>`_

* `#4410: rtems_task_start() does not check that the entry point is not equal to NULL <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4410>`_

* `#4411: rtems_task_restart() should set the real priority to the initial priority <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4411>`_

* `#4412: Unexpected rtems_task_restart() behaviour if called from within interrupt context <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4412>`_

* `#4414: Return RTEMS_CALLED_FROM_ISR in rtems_task_delete() <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4414>`_

* `#4426: clock_nanosleep() may use wrong clock for relative times <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4426>`_

* `#4435: Thread cancellation may produce ready threads with an active thread timer <https://gitlab.rtems.org/rtems/rtos/rtems/-/issues/4435>`_

This list is not complete and may grow if more managers are specified and
validated.  Some of these issues may also exist in previous pre-qualified RTEMS
versions.

As an example of how the specification and validation work, please have a look
at the action requirement item for the :c:func:`rtems_task_set_scheduler`
directive:

.. code-block:: c

    rtems_status_code rtems_task_set_scheduler(
      rtems_id            task_id,
      rtems_id            scheduler_id,
      rtems_task_priority priority
    );

This directive has only three parameters which are obviously covered by the
pre-conditions of the item.  The return status is a post-condition.  In
addition to these obvious conditions, the item also covers internal states of
the associated task and scheduler.  This results in a transition map which has
1535 transition entries:

.. raw:: latex

    {\fontsize{4}{6}\selectfont

.. table::
    :class: longtable

    ===== ======= ========= =============== =========== ======== ============ ================== ====== ========= ================= ======= ========= ========
    Entry TaskId  Scheduler SchedulerHasCPU SchedulerId Priority HomePriority EligiblePriorities Pinned TaskState AffinitySupported Status  Scheduler Priority
    ===== ======= ========= =============== =========== ======== ============ ================== ====== ========= ================= ======= ========= ========
    0     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Ready     Yes               InUse   Nop       Nop
    1     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Ready     No                N/A     N/A       N/A
    2     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Blocked   Yes               InUse   Nop       Nop
    3     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Blocked   No                N/A     N/A       N/A
    4     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Enqueued  Yes               InUse   Nop       Nop
    5     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            Yes    Enqueued  No                N/A     N/A       N/A
    6     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            No     Ready     Yes               Ok      Set       Set
    7     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            No     Ready     No                N/A     N/A       N/A
    8     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            No     Blocked   Yes               Ok      Set       Set
    9     Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            No     Blocked   No                N/A     N/A       N/A
    10    Task    Home      Yes             Scheduler   Valid    Real         OnlyOne            No     Enqueued  Yes               InUse   Nop       Nop
    ...   ...     ...       ...             ...         ...      ...          ...                ...    ...       ...               ...     ...       ...
    1535  Invalid N/A       N/A             Invalid     N/A      N/A          N/A                N/A    N/A       N/A               InvId   Nop       Nop
    ===== ======= ========= =============== =========== ======== ============ ================== ====== ========= ================= ======= ========= ========

.. raw:: latex

    }

This approach provides path and MC/DC coverage of the internal
:c:func:`_Scheduler_Set` function which is called by the
:c:func:`rtems_task_set_scheduler` directive.  Adding unit tests for
:c:func:`_Scheduler_Set` on top of such a validation test is just a waste of
time and budget.
