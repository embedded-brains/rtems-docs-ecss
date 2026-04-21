.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 EDISOFT
.. Copyright (C) 2020, 2023 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

Auxiliary information
*********************

.. _Service:

Service and maintenance
=======================

Software and hardware of a certain complexity needs maintenance in order to
keep and improve its quality with the experience of using it.

The pre-qualified feature set of RTEMS is thoroughly specified and validated.
It is implemented by a code base which experienced more than 30 years of
evolution and continuous improvement.  However, experience shows that there
might be still some bugs, shortcomings, and documentation issues left over to
get fixed.  If you would like to report an issue related to this package,
please have a look at: `<https://embedded-brains.de/qdp-bugs>`__.

`embedded brains <https://www.embedded-brains.de>`__ is providing ongoing
commercial maintenance services complementary to the project structured ESA
activities.  In the context of these services, the reported issues will be
reviewed, fixed (if applicable) and reported in an anonymised form to the
corresponding upstream projects such as the `RTEMS Project
<https://www.rtems.org>`__ or the `GCC <https://gcc.gnu.org/>`__.

Additionally, these services include handling of issues related to this
package as well as new chip errata, which both need workarounds swiftly.
See `<https://embedded-brains.de/qdp-support>`__.

`embedded brains <https://www.embedded-brains.de>`__ offers a wide range of
RTEMS expert support services.  This includes training, consulting, and
development services for RTEMS as well as for the entire tool suite (for
example Binutils, GDB, Newlib, GCC).  The company experts are active members in
the RTEMS community.  embedded brains is a major contributor to the RTEMS
Project and leading in the design and development of the SMP support for RTEMS.

.. _FAQ:

Frequently asked questions
==========================

${.:/push-enabled-by:pkg.feature.qual}

How can I adopt the QDP to a new BSP, for example leon2?
--------------------------------------------------------

The QDP provides you with everything to adopt it to a new
${/glossary/bsp:/term}.  The main RTEMS repositories are included in the QDP.
This gives you full access to the project history in all details.  With the
${/glossary/rsb:/term} you are able to build the RTEMS tool suite for other
targets or make updates of the tools.  RTEMS and its ecosystem is documented in
the RTEMS documentation shipped with the QDP, see :ref:`RTEMSDocs`.  The tool
chain to build a customised QDP is also available with sources and
documentation under open source licenses.  However, you should think twice
whether it is your core business to build up expert knowledge in this domain.
It is probably faster and more cost effective to contract an experienced
service provider, see also :ref:`Service`.  The QDP and its generation process
is complicated enough to require expert knowledge and training.

${.:/pop-enabled-by}

Is C++ supported?
-----------------

C++ is supported in general, however, for a more complete C++ runtime and
standard library support, more ${/glossary/posix:/term}
${/glossary/api:/plural} need to be pre-qualified.  In particular, support for
condition variables is recommended.  For a basic C++ example application, see
:ref:`Examples`.

Is OpenMP supported?
--------------------

${/glossary/openmp:/term} provided by ${/glossary/gcc:/term} is excellently
supported by mainline RTEMS.  For a pre-qualified RTEMS support for OpenMP,
more ${/glossary/posix:/term} ${/glossary/api:/plural} need to be
pre-qualified.  Also some restructuring in the Newlib C library is necessary to
avoid a dependency on the C file streams.  The major work is done, see
:ref:`Service` to get it supported.

Is Ada supported?
-----------------

For a proper Ada support, more features need to be pre-qualified.  For example,
the Ada tasking support requires parts of the ${/glossary/posix:/term} API such
as threads, mutexes, and condition variables.  Unfortunately, signals are also
used.  If Ada is used for serious applications, then the use of signals should
be eliminated.  The Ada runtime depends on C library file streams.  In general,
it should be assessed if the Ada runtime library can be reorganised to better
support static linking.  See :ref:`Service` to get it supported by the
pre-qualified feature set.
${.:/push-enabled-by:__RTEMS_ADA__}
For a basic Ada example application, see :ref:`Examples`.
${.:/pop-enabled-by}

.. _Targets:

Targets
=======

Validation tests for items provided by the package were executed on the
following targets.

${.:/targets}

.. _UserTestReports:

User test reports
=================

This section describes the steps to produce a *User Test Report*. User test
reports present test results obtained from test runs on a user-provided
${/glossary/target:/term}.

The package provides a set of Python tools located in :file:`.venv` and a
package configuration in :file:`spec` to run the tests using a user-provided
command line tool, generate user test reports, and code coverage reports.  This
build process requires the following customization inputs from you:

- proper user target descriptions (recommended)

- updates to the user test report sources (recommended)

- a command line tool to run test executables on the user target (mandatory)

- timeouts for the test executions (optional)

- runtime performance limits for the user target (optional)

Follow the steps below.  In the second step, a virtual Python environment is
activated.  The steps afterwards assume, that you activated this environment
and that your current directory is the package directory.

The following instructions use the placeholders:

- ``$${arch-component}``: It shall be one of the package
  ${/glossary/target-arch:/term} component names: ${.:/subcomponent-list:1}.

- ``$${bsp-component}``: It shall be one of the package ${/glossary/bsp:/term}
  component names: ${.:/subcomponent-list:2}.

In case of any problems, please have a look at :ref:`Service`.

Step 1: Use Git to track changes
--------------------------------

Running the tools may result in an inconsistent package state due to
configuration errors.  It is strongly recommended to turn the package
deployment into a Git repository and import it to Git.  The tools have a mode
to use Git to track changes.  You can audit the build steps with ``git log``
and if necessary revert steps using ``git revert``.

Open a terminal window, change into package directory, and run the following
commands:

.. code-block:: none
    :linenos:

    $$ cd ${.:/component/deployment-directory}
    $$ git init
    $$ git add -f .
    $$ git commit -m "Initial import"

Step 2: Activate the virtual Python environment
-----------------------------------------------

The tools are provided by the package in a virtual Python environment located
in the :file:`.venv` directory.  Open a terminal window, change into package
directory, and active the virtual Python environment:

.. code-block:: none
    :linenos:

    $$ cd ${.:/component/deployment-directory}
    $$ source .venv/bin/activate

The following commands are only required if the virtual Python environment is
not operational on your host system.  You can reinstall the virtual Python
environment with the
`uv Python package and project manager <https://docs.astral.sh/uv/>`__
by running ``uv sync``.

.. code-block:: none
    :linenos:

    $$ cd ${.:/component/deployment-directory}
    $$ rm -rf .venv
    $$ uv sync
    $$ source .venv/bin/activate

Step 3: Check that the ``specmake`` tool works
----------------------------------------------

Check that the ``specmake`` tool works.  Run ``specmake --help``:

${.:/subprocess:args=specmake --help,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

Step 4: Update the user target descriptions
-------------------------------------------

In this step, you should edit the following :file:`user.yml` target description
items:

${.:/subprocess:args=find spec/target/*/*/ -name user.yml,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

Edit the ``brief``, ``description``, ``name``, and ``target-hash`` attributes
so that they fit to your project:

.. code-block:: yaml
    :linenos:

    brief: |
      This is a board of the package user.
    description:
      This describes a board of the package user.
    name: Board of Package User
    target-hash: cpI09Ju6orF2eoJcmJi4igeIarypsRNwUxTrZSs9LMg=

The target hash can be obtained, for example, by running the
:file:`ts-userext.exe` test executable on your target.  The target hash is
reported in the line starting with ``S:TargetHash:SHA256:``.

Commit your changes to Git.  The Git status should report a clean working tree:

.. code-block:: none
    :linenos:

    $$ git status
    On branch main
    nothing to commit, working tree clean

Step 5: Update the user test report document configurations
-----------------------------------------------------------

In this step, you should edit the following :file:`doc-user-tr.yml` document
configuration items:

${.:/subprocess:args=find spec/pkg/*/*/*/ -name doc-user-tr.yml,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

Edit at least the ``document-contributors``, ``document-copyrights``, and
``document-releases`` attributes so that they fit to your project:

.. code-block:: yaml
    :linenos:

    document-contributors:
    - action: Written by
      contributors:
      - first-name: Erika
        last-name: Mustermann
        organization: Some Company
    - action: Verified by
      contributors:
      - first-name: John
        last-name: Doe
        organization: Some Company
    - action: Approved by
      contributors:
      - first-name: Jean
        last-name: Dupont
        organization: Some Company
    document-copyrights:
    - Copyright (C) 9999 Some Company
    document-releases:
    - date: '9999-12-31'
      status: Release
      changes: |
        This is a release issued for some project.

Commit the changes to Git and make sure the working tree is clean.

Step 6: Update the user test report sources
-------------------------------------------

Edit at test report documentation sources in the directory
:file:`src/doc/user/tr`.  You probably want to replace :file:`logo.pdf`.
Depending on your logo dimensions, you have to update the file
:file:`project.sty` accordingly.  Commit the changes to Git and make sure the
working tree is clean.

Step 7: Build the user test report without real test runs
----------------------------------------------------------

By default, the test runs on the user target are performed using a dummy
command which performs no real test execution.  Firstly, build the user test
report with this dummy command to make sure the document generation works.  Run
``specmake`` to build the user test report:

.. code-block:: none
    :linenos:

    $$ specmake --use-git /pkg/$${arch-component}/$${bsp-component}/doc-user-tr

To get the UIDs of available user test reports, see step 5.  Remove the
``spec`` prefix and the ``.yml`` extension to get an UID from an item file
path.

Step 8: Provide a command to run tests
--------------------------------------

Edit the ``command`` attribute of the :file:`spec/pkg/test-runner/user.yml`
test runner item.  Provide a command line tool to run individual test
executables on your target.  The ``command`` attribute expects a list of string
values.  The first value is the path to your command line tool.  The following
values are command parameters.  You can use the ``$${.:/test-executable}``
substitution to pass the test executable path to your command line tool.  The
values shall be strings, please note the implicit type conversions of the
${/glossary/yaml:/term} format.  Here is an example command line with
some parameters requiring a ``'value'`` encapsulation:

.. code-block:: yaml
    :linenos:

    command:
    - foobar
    - '42'
    - 'yes'
    - 'no'
    - 'true'
    - 'false'
    - 'null'
    - $${.:/test-executable}

The command is invoked as a subprocess by the package builder with timeout
monitoring.  If the subprocess runs longer than an executable-specific timeout,
then it is killed.  For each executable, the timeout may be provided by a test
timeout associated with the target and build configuration.  You can customise
the timeout calculation through the ``default-timeout-in-seconds``,
``min-timeout-in-seconds``, and ``timeout-scaler`` attributes of the test
runner item:

.. code-block:: yaml
    :linenos:

    default-timeout-in-seconds: 90.0
    min-timeout-in-seconds: 10.0
    timeout-scaler: 2.0

Let *E* be the executable-specific timeout or the default timeout
associated with a executable.  Let *M* be the maximum of *E* and the specified
minimum timeout.  Let *S* be *M* multiplied by the specified timeout scaler.
The value *S* is used as a timeout in seconds for the subprocess invocation.

The executable-specific timeouts are specified in :file:`test-timeouts.yml`
files:

${.:/subprocess:args=find spec/target/*/*/user -name test-timeouts.yml,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

Commit the changes to Git and make sure the working tree is clean.

Step 9: Build the user test report with real test runs
-------------------------------------------------------

Run ``specmake`` to build the user test report with the updated test runner:

.. code-block:: none
    :linenos:

    $$ specmake --use-git /pkg/$${arch-component}/$${bsp-component}/doc-user-tr

To get the UIDs of available user test reports, see step 5.  Remove the
``spec`` prefix and the ``.yml`` extension to get an UID from an item file
path.

Step 10: Review the user test report
------------------------------------

Review the generated test report located at
``doc/$${arch-component}/$${bsp-component}/user/tr/tr.pdf``.  Start with the
*List of unexpected test failures* chapter.

If some tests time out, then check if this is an actual issue with the test or
the timeout value.  For the test timeout specification, see step 8.

If some performance measurements are outside the specified limits, then this
needs to be reviewed carefully.  The performance runtime limits are specified
in :file:`perf-default.yml` and :file:`perf-smp.yml` files:

${.:/subprocess:args=find spec/target/*/*/user -name perf-*.yml,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

You can use the ``specupdateperf`` tool to update the performance runtime
limits using test result JSON files:

${.:/subprocess:args=specupdateperf --help,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=0}

See the *Introduction* chapter to get the list of test log files used to create
the document.

.. _MissionQualification:

Guidance for RTEMS qualification in user's environment
======================================================

${.:/push-enabled-by:not: pkg.feature.qual}

This section is applicable to applications which are subject to an ECSS
qualification.  This package is not intended to be used for such applications.
You can upgrade the package on request, see also :ref:`Service`.

${.:/pop-enabled-by}

${.:/push-enabled-by:pkg.feature.qual}

The following two sections describe the engineering and product assurance
activities which may be performed by the package user in a product
qualification according to ECSS standards.

In case of any problems, please have a look at :ref:`Service`.

Engineering activities
----------------------

The RTEMS software product included in this package is provided with
pre-qualification tests already performed on the documented targets, see
:ref:`Targets`.  You, the package user, may be required to run the tests again
on your targets.  See :ref:`UserTestReports` for the steps to perform this
task.

In addition to running the tests, re-generate the report and verifying that in
the user hardware execution everything is OK, the QDP users will need to make
the traceability of the project requirements to the RTEMS requirements.

Product assurance activities
----------------------------

Taking into account the specifics for the RTEMS pre-qualification project, the
EDISOFT product assurance team suggests the following activities.

Verify if there are changes in the original plans (record tracking).  Verify if
the changes are in accordance with the original plans and, if not, they are
justified. The PA should look at the following documents, considered as plans
for the RTEMS pre-qualification project:

* ${/glossary/ecss:/term} documentation (ECSS-E-ST-40C ${/ref/ecss/e-st-40c:/cite},
  ECSS-Q-ST-80C Rev.  1 ${/ref/ecss/q-st-80c-r1:/cite}, ECSS-M-ST-40C Rev.1
  ${/ref/ecss/m-st-40c-r1:/cite}) – Always applicable for ${/glossary/esa:/term}
  projects

* Software Development Plan (SDP)

  * `<${.:/component/deployment-directory}/doc/mgt/sdp/SDP-000.pdf>`_

  * `<${.:/component/deployment-directory}/doc/mgt/sdp/html/index.html>`_

* Software Configuration Management Plan (SCMP)

  * `<${.:/component/deployment-directory}/doc/mgt/scmp/SCMP-001.pdf>`_

  * `<${.:/component/deployment-directory}/doc/mgt/scmp/html/index.html>`_

* Software Product Assurance Plan (SPAP)

  * `<${.:/component/deployment-directory}/doc/paf/spap/SPAP-002.pdf>`_

  * `<${.:/component/deployment-directory}/doc/paf/spap/html/index.html>`_

* ${/ref/tn/qt-109-r6:/cite-long}

  * `<${/pkg/deployment/doc-tn-qt:/file:relpath %(/pkg/component:/prefix-directory)}>`__

  The technical note contains the tailoring of ECSS documents for the RTEMS
  pre-qualification project (chapter 4) and other relevant technical
  information that could be used by the PA:

  * Requirements, interfaces and test plans format (see chapter 6)

  * ECSS statement of compliance (see chapter 9)

Verify the affected parts of the QDP deliverables, according below:

* General verifications (transversal to all documentation):

  * Verify document correctness against ECSS and QT-109

  * Verify proper tracking update (change records)

  * Verify traceability (for example requirements to tests)

* Verifications specific to the SRS:

${.:/document-elements:2:srs}

  * Verification following the SDP, section 5.3 (for requirement specifications)

  * Verification following the SPAP, section 6.7.1

* Verifications specific to the ICD:

${.:/document-elements:2:icd}

  * Verification following SDP, section 5.3 (for interface specifications)

  * Verification following SPAP, section 6.7.1

* Verifications specific to the SDD:

${.:/document-elements:2:sdd}

  * Verification following SDP, section 5.3

  * Verification following SPAP, section 6.7.2

* Verifications specific to the SVS and SUITP:

${.:/document-elements:2:svs}

  * Verification following SDP, section 5.3 (for test specifications)

  * Verification following SDP, chapter 6 (only the parts applicable to RTEMS)

  * Verification following SPAP, section 6.7.4

* Verifications specific to the software product source code and test suite:

  * Verification following SPAP, section 6.7.3

* Verifications specific to the SVR - **the one generated for the own hardware, according to the previous section**:

${.:/document-elements:2:svr}

  * Verification following SDP, section 10 (only the parts applicable to RTEMS)

  * Verification following SPAP, section 6.7.3

  * Verification following SPAP, section 6.7.4

  * Verification of test results

* Verifications specific to the SRelD:

  * Verify if the delta closes any software problem reports.

* Verifications specific to the SPAMR:

${.:/document-elements:2:spamr}

  * Verification following SPAP, section 6.5

  * Verification following SPAP, section 5.5 (verification of software metrics)

  * Verification following SPAP, section 6.7.4.1

* Verifications regarding Independent Software Verification
  and Validation (ISVV):

  * Revisit and re-assess as needed the documentation listed within
    :ref:`ISVVDocs` regarding the ISVV performed as part of the
    RTEMS SMP pre-qualification, namely in what respects ISVV
    postponed findings that might have been addressed in the
    meanwhile (for example by the RTEMS community)

* Verifications specific to this document:

  * Follow the instructions and try to replicate the software utilization,
    specifically the PA should be able to decompress the QDP and correctly
    compile the RTEMS example application.

  * Assess the possible impacts of the listed :ref:`Problems`

* Other verifications:

  * Verify if updates on Sphinx documentation are in accordance with the SDP, section 8

  * Perform the activities as described in SPAP sections 6.2.1 and 6.4

  * Verification of Certificate of Conformance, in accordance with the SPAP, section 6.7.4.2

  * Verification of audits (functional and physical configuration verification),
    in accordance with the SCMP, section 5.8

${.:/pop-enabled-by}

.. _ExternallyProvidedItems:

Use of externally provided items
================================

${.:/push-enabled-by:not: pkg.feature.qual}
This section is applicable to applications which are subject to an ECSS
qualification.  This package is not intended to be used for such applications.
This section is provided as background information.
${.:/pop-enabled-by}

In order to build the BSP of the package and finally also the application,
various tools and reusable software components are required.  Notable tools are
the C preprocessor, the compiler, the assembler, and the linker.  The compiler
and the C library provide standard header files.  These tools and interfaces
are essential to build BSPs, third-party libraries, and applications.  However,
they are outside the responsibility scope of the activity delivering the
package and provided as is.  For QDP package version 6, an analysis was carried
out to investigate which externally provided functions are required by the
pre-qualified feature set of RTEMS and what can be done to ensure that these
components have an acceptable quality.  The analysis and the results are
presented in this section.

Since QDP package version 6, applications could use the following linker
options to link with the operating system:

* ``-nodefaultlibs``

* ``-Wl,--start-group``

* ``-lrtemscpu``

* ``-lrtemsbsp``

* ``-Wl,--end-group``

The :file:`librtemsbsp.a` and :file:`librtemscpu.a` libraries contain the
pre-qualified RTEMS feature set.  In previous QDP package versions, linking to
the :file:`libgcc.a` library provided by GCC was required.  This library is not
covered by the pre-qualification activities.  It contains runtime support for
programming languages such as C and C++.  This includes software
implementations of integer operations if the ${/glossary/target-arch:/term}
does not support them in hardware.  For example, consider the following source
code:

.. code-block:: c

    uint64_t mul( uint64_t a, uint64_t b )
    {
      return a * b;
    }

For a 32-bit target, this may get compiled into the following assembly code:

.. code-block:: none

    mul:
        save     %sp, -96, %sp
        mov      %i2, %o2
        mov      %i3, %o3
        mov      %i0, %o0
        call     __muldi3, 0
         mov     %i1, %o1
        mov      %o0, %i0
        jmp      %i7+8
         restore %g0, %o1, %o1

Here a call to ``__muldi3`` is issued.  This function is provided by
:file:`libgcc.a`.  However, for a 64-bit target, this may get compiled into the
following assembly code:

.. code-block:: none

    mul:
        mulld 3, 3, 4
        blr

So, it is target-specific if the :file:`libgcc.a` is required.  Some
programming languages have features requiring complex runtime libraries.  An
example is the C++ exception handling which may require a stack unwinder.  The
stack unwinder is a complex piece of software.

For the 32-bit SPARC target, which :file:`libgcc.a` components are required for
the pre-qualified feature set?  To figure this out, we built the validation
tests without linking to :file:`libgcc.a` and checked for undefined references:

* ``__clzsi2``

* ``__divdi3``

* ``__moddi3``

* ``__udivdi3``

* ``__umoddi3``

These are integer operations implemented in
`libgcc/libgcc2.c <https://gcc.gnu.org/git/?p=gcc.git;a=blob;f=libgcc/libgcc2.c>`__
of the GCC sources.  Due to the wide spread use of these functions on various
GCC targets, the maturity of GCC, and the competence the GCC developers
contributing to this area of GCC, it is reasonable to accept these functions as
proven in use.  However, we should not have the same level of confidence in other
components included in :file:`libgcc.a`, for example the stack unwinder.  Since
we linked to this library as a whole, there was a risk that applications may pick
up something which does not meet the quality expectations or has undesirable
dependencies, for example use of dynamic memory.

One option is to simply copy the file from GCC, strip it down to what is
needed, and then ship it with the pre-qualified RTEMS.  However, this file is
covered by a license which hinders this approach.  It could result in
applications having to meet ${/glossary/gplv3:/term} requirements, see also
`COPYING.RUNTIME <https://gcc.gnu.org/git/?p=gcc.git;a=blob;f=COPYING.RUNTIME>`__
of the GCC sources.  To overcome the license issues, we reviewed the
implementations from the `compiler-rt <https://compiler-rt.llvm.org/>`__
package of the ${/glossary/llvm:/term} Project.  The goal was to remove the
need to link against :file:`libgcc.a`.

The above option is a minimalistic solution. More useful for application
developers would be a somewhat trustworthy compiler with thoroughly tested
libraries.  A trustworthy compiler is a very hard project, however, thoroughly
tested libraries is just a bit of work.  For the parts provided by
:file:`libgcc.a` and compiler-rt, this work would be easy to integrate in GCC
and LLVM as a shared component.  LLVM has already unit tests for this
component.  Doing this work in isolation just for the ESA community would be a
questionable.  The package build process could be enhanced with a run of the
compiler test suite.

For the QDP package version 6, the budget only allowed the minimalistic
solution.  The compiler builtins using library routines for integer arithmetic,
integer comparison, and bit operations were added from the LLVM compiler-rt
component to the pre-qualified RTEMS feature set, see also the
`GCC routines for integer arithmetic <https://gcc.gnu.org/onlinedocs/gccint/Integer-library-routines.html>`__.
Unit tests were added to achieve the code and branch coverage goals.  No
functional specification and validation tests are provided.  As a result,
linking to :file:`libgcc.a` is no longer required for the pre-qualified feature
set of RTEMS.  In the linker flags exported by the BSP, the :file:`libgcc.a` is
still listed for backward compatibility.  In particular, for some floating
point operations :file:`libgcc.a` is required.  Application designers should
review the linker map file to check which functions are used from
:file:`libgcc.a`.

${.:/push-enabled-by:pkg.feature.edisoft-rtems}

.. _PerformanceComparison:

Performance comparison with EDISOFT RTEMS
=========================================

Previous ESA activities funded a customised RTEMS version provided by EDISOFT.
In contrast to the RTEMS product of this QDP, the development of the EDISOFT
RTEMS version is detached from the RTEMS Project.  It can be considered a
separate software product development line.  Significant parts of the
${/glossary/api:/term} of both products are still compatible.  If you intend to
port your application from the EDISOFT RTEMS version to the version provided by
the QDP, see :ref:`Migration`.  The runtime performance tests and the static
memory usage benchmarks of the QDP are used to compare the performance of both
products.

The version 15 (v15) of EDISOFT RTEMS is used for the performance comparison.
The source code was delivered by the :file:`09060101-039-15.SFW.zip` archive
which had an SHA512 digest of
7​a​1​9​4​0​b​7​d​4​9​7​9​f​1​7​b​d​3​7​a​6​f​4​7​1​e​9​9​3​1​d​d​c​3​6​7​8​7​b​d​6​a​5​e​3​c​e​7​7​d​7​3​c​9​5​f​1​5​d​0​a​b​7​1​c​2​9​d​b​f​0​6​f​1​1​8​4​f​1​e​c​9​3​c​5​a​9​5​4​0​4​8​f​a​4​3​c​7​c​1​3​b​0​7​9​0​7​0​8​b​3​a​8​2​0​a​d​9​a​d​6​5​e​9​6​4​a.
The EDISOFT RTEMS BSP is normally built using GCC 4.2.1 which was released at
July 18, 2007. This GCC version was patched to

* add support for RTEMS 4.8,

* add a workaround for the LEON3FT store-store errata,

* add a workaround for the GRLIB-TN-0012 errata,

* fix build issues in newer host environments (native GCC 13),

* not install the documentation files, and

* use the RTEMS-specific start file, end file, and C library specification of
  GCC 13.

The EDISOFT RTEMS version was delivered with an incomplete build system.  A
modified variant of the RTEMS build system was used to build the BSP.  Support
for the linker garbage collection was added to the linker command file.  The
build was performed with data sections, function sections, and the linker
garbage collection enabled, to reduce the code and data sizes of the memory
usage benchmarks.  This setup is used by default for the *RTEMS 6* variant.

For the performance comparison, the EDISOFT RTEMS BSP was also built using the
GCC 13 of the QDP to reduce the compiler influence on the benchmark results.
The following list provides all BSP variants used for the performance
comparison:

${.:/benchmark-variants-list}

The EDISOFT RTEMS does not provide all API elements used by the tests, for
example the Barrier Manager, Partition Manager, and Signal Manager are not
included.  Also some directives resulting from the SMP support of RTEMS are
missing.  In the tables below, missing tests are indicated by ``?`` values in
the associated row.  All numbers in the tables below are obtained from
executables generated by the QDP build process and the test logs included in
the QDP.

Comparison of static memory usage benchmarks
--------------------------------------------

See :ref:`Membench`, for an overview of the memory usage benchmarks provided by
the QDP.  For each memory usage benchmark, the section sizes of the *RTEMS 6*
variant are listed as a baseline.  The EDISOFT RTEMS variants follow with
values indicating the change of the section size relative to the baseline.

For the EDISOFT RTEMS variants, the following items were observed:

* GCC 13 seems to generate a smaller code size.

* The ``.bss`` size includes the mandatory support for error message storage.
  The related objects are ``_Error_Fatal_Message`` and
  ``_Error_Non_Fatal_Message`` needing about 14408 bytes of memory.

* The configured RTEMS Workspace size seems to be a bit high.  This could be a
  bug in ``CONFIGURE_MEMORY_FOR_TASKS()`` which adds one to the number of tasks
  for whatever reason.

By default, the Deterministic Priority Scheduler is configured with 256
priority levels, see ${/acfg/if/max-priority:/name}.  For each priority level,
a chain control structure of 12 bytes is required.  This results in 3072 bytes.
For the *RTEMS 6* variant, this number is included in the ``.bss`` section.
For the EDISOFT RTEMS variants, this number is included in the ``.noinit``
section which includes the RTEMS Workspace.

${.:/memory-benchmark-variants-table}

Comparison of runtime performance measurements
----------------------------------------------

The table below lists for each runtime performance requirement, the statistics
obtained for each runtime performance execution environment and BSP variant.
The statistics are the minimum, median, and maximum runtime of the measured
code path specified by the associated runtime performance requirement.  The
statistics of the *RTEMS 6* variant are listed as a baseline.  The EDISOFT
RTEMS variants follow with values indicating the change relative to the
baseline.

The results of the runtime performance measurements for
${/score/cpu/req/perf-nops:/spec} and ${/score/cpu/req/perf-empty:/spec} can be
used to check that the runtime measurement implementations on all variants
deliver comparable results.  For all variants, the results of these two runtime
measurements should be close together.

${.:/performance-variants-table}

Conclusion
----------

Based the results obtained from the static memory usage benchmarks and the
runtime performance measurements, we try to assess if a migration of your
application from EDISOFT RTEMS to the version provided by the QDP is an option.

With respect to the static memory usage obtained from the benchmarks, both
products are quite close.  The EDISOFT RTEMS variants have a higher use of
zero-initialised and not initialised data, however, this could be probably
reduced.  Due to the different feature sets, a comparison of the code size is
problematic.  The following aspects need to be considered:

* The EDISOFT RTEMS uses a primitive runtime device enumeration support.  In
  contrast, the QDP version uses configuration defined values for devices
  properties such as the base address of a module.  This requires less code.

* The EDISOFT RTEMS uses a first-fit heap for the RTEMS Workspace.  Operating
  system data structures are allocated from the RTEMS Workspace.  In contrast,
  the QDP version does not use the RTEMS Workspace and instead uses statically
  allocated data structures.  This requires less code and should result in
  faster system initialization times.

* The QDP version uses red-black trees for priority queues and timers.  This
  data structure performs well with a large number of items, however, it
  requires more code compared to the data structures used by EDISOFT RTEMS.

* The QDP version provides timekeeping services which support
  ${/glossary/ntp:/term} and scale well on ${/glossary/smp:/term} systems.
  This requires more code and data compared to the implementation used by
  EDISOFT RTEMS.  Not included in the pre-qualified feature set of the QDP is
  the support for ${/glossary/pps:/term} synchronization.  This could be added
  on demand.

* The QDP version protects the creation and deletion of system-provided objects
  through a priority inheritance mutex.  This mutex uses a protection from
  asynchronous thread cancellation while the mutex is owned.  The thread life
  cycle management (create, start, restart, cancellation, deletion) is much
  more capable and robust compared to the EDISOFT RTEMS implementation.
  Various bugs have been fixed in this area throughout the development of the
  SMP support.  This requires a bit of code.  The mutex was introduced to make
  the runtime of the thread dispatch disabled critical sections independent of
  the heap fragmentation (RTEMS Workspace).

* The QDP version provides a proper implementation of the priority inheritance
  protocol.  Priority changes triggered by events originating from sources such
  as the priority inheritance protocol, priority ceiling protocol, explicit
  priority changes, and scheduling policies such as ${/glossary/edf:/term}.
  are carried out immediately when they happen.  This requires more code.

Typical applications will use the Semaphore Manager and the Message Manager.
The corresponding memory usage benchmarks have the smallest footprint for the
*RTEMS 6* variant provided by the QDP.  So, in terms of static memory usage
considering also the above feature differences between the products, selecting
the version provided by the QDP for your application is a reasonable option.

How do the products compare in terms of runtime performance measurements?  The
QDP version supports processor usage statistics for threads.  Whenever an heir
thread is chosen by the scheduler, the processor usage statistic of the
executing thread is updated.  This feature requires a bit of time.  It is
probably the reason, why some measured statistics for operations which involve
a context switch are so close together especially in the *HotCache* execution
environment.

The operations involving the thread life cycle management (create, start,
restart, cancellation, deletion) require more time in the QDP version.  The
reason for this is that they also do a lot more to make the operations correct
and robust.  Normally, such operations are not performance critical.  If they
are performance critical, then a review of the application design is highly
recommended.

Two design goals of the SMP support development were:

* Fast operations for the average case.

* Proper priority handling in the complicated cases.

Important operations for the average case are obtaining and releasing an
uncontested mutex.  In this scenario, the QDP version performs quite well.
With respect to the measured runtime of core operations of the operating
system, choosing the version of the QDP should be a reasonable option.

${.:/pop-enabled-by}

.. _QDPForRTEMS:

Available and on request QDPs for RTEMS
=======================================

An RTEMS QDP is not only available for the ${/glossary/target:/term} of this
package.  A QDP can be made available for every ${/glossary/target-arch:/term}
and ${/glossary/bsp:/term} supported by RTEMS.  For the creation of an RTEMS
QDP for a particular target the following items are required:

* Support for the target architecture (for example AArch64, ARMv7-ARM, PowerPC,
  RISC-V, SPARC)

* Basic BSP with a ${/glossary/clock-driver:/term} and a character output
  device driver (to get the test reports)

* Specification and validation of the target architecture support and the basic
  BSP

* Related engineering and product assurance activities

* Qualification toolchain to run the tests, generate the documents, and package
  the artifacts; this includes a test runner to run the tests on the specific
  target (this could be an ${/glossary/obc:/term})

* A QDP configuration so that the toolchain produces the desired results

The specification and validation are the main engineering activities necessary
to deliver a QDP.  Large parts of RTEMS are architecture-independent.  For
these parts, the specification of existing QDPs can be easily reused.  An
adoption to the target architecture requires a specification of the thread
context switching and interrupt processing with the associated validation
tests.  Other components are the initialization of clock domains, IO pins,
processor modes, memory controllers, cache controllers, power management
controllers, bus systems, memory management units, memory protection units,
watchdogs, and related components.  A clock driver and a character output
device driver are mandatory.  An important work is gathering of all relevant
hardware errata, a review of the errata, and the implementation of errata
workarounds.  For the mentioned tasks, personnel with a deep understanding of
target architecture and ${/glossary/system-on-chip:/term} is required.

Once the specification and validation tasks are finished, a QDP configuration
needs to be assembled and processed by the toolchain to generate the QDP for
the target.  This configurability of the qualification toolchain was a design
goal.  Unfortunately, the toolchain delivered to ESA does not meet this design
goal.  embedded brains has an enhanced in-house version of the toolchain which
allows an easy and flexible configuration to produce QDPs for any desired RTEMS
target, see :ref:`Service`.

AMD Xilinx
----------

On request, QDPs can be made available by embedded brains for the following
product lines from
`AMD Xilinx <https://www.xilinx.com/products/silicon-devices/soc.html>`__:

* Zynq 7000 SoC

* Zynq UltraScale+ MPSoC

* Zynq UltraScale+ RFSoC

* Versal Adaptive SoC

fentISS Hypervisors
-------------------

`fentISS <https://www.fentiss.com/>`__ provides hypervisor products (XtratuM
and XNG) which can be used together with RTEMS as a guest system.  On request,
QDPs can be made available by embedded brains for the following products from
fentISS:

* ARMv7-A: Virtualization through TrustZone support, clock and timer through
  hypercalls, interrupt controller through hypercalls:

  * Xilinx Zynq 7000 SoC: 2 x ARM Cortex-A9 (SMP model)

* ARMv7-R: Para-virtualization, clock & timer through hypercalls, Interrupt
  controller through hypercalls:

  * Texas Instruments TMS570LC4357: 1 x ARM Cortex-R5

  * Xilinx UltraScale+ MPSoC: 2 x ARM Cortex-R5 (SMP model)

  * NanoXplore NG-LARGE: 1 x ARM Cortex-R5

* ARMv8-A: Virtualization through virtualization extensions, clock and timer
  through ARM Generic Timer, interrupt controller through hypercalls:

  * Xilinx UltraScale+ MPSoC: 4 x ARM Cortex-A53 (SMP model)

  * Renesas R-Car V3U: 8 x ARM Cortex-A76 (SMP model)

* ARMv8-R: Virtualization through virtualization extensions, clock and timer
  through ARM Generic Timer, interrupt controller through hypercalls:

  * NanoXplore NG-ULTRA: 4 x ARM Cortex-R52 (SMP model)

* RISC-V (64-bit): Virtualization through virtualization extensions, clock and
  timer through hypercalls, interrupt controller through hypercalls

  * Frontgrade Gaisler NOEL-XCKU: 4 x 64-bit NOEL-V (SMP model)

* SPARCv8: Para-virtualization, clock and timer through hypercalls, interrupt
  controller through hypercalls:

  * Frontgrade Gaisler GR712RC: 2 x LEON3 (SMP model)

  * Frontgrade Gaisler GR740: 4 x LEON4 (SMP model)

${/glossary/ecss:/term} criticality category B is the goal for the fentISS
hypervisor products: 

* XNG for ARMv7-A on Xilinx Zynq 7000 SoC and XNG for ARMv7R on Texas
  Instruments TMS570LC4357: qualification completed targeting ECSS criticality
  category B.

* XNG for ARMv8-R NanoXplore NG-ULTRA, XNG for Frontgrade Gaisler GR740 and XNG
  for Frontgrade Gaisler NOEL-V: qualification on-going targeting ECSS
  criticality category B.

* Any other version is considered as a prototype, being candidate for future
  delta-qualification campaigns.

Frontgrade Gaisler
------------------

On request, QDPs can be made available by embedded brains for the following
products and product lines from
`Frontgrade Gaisler <https://www.gaisler.com/index.php>`__:

* GR712RC (also available from ESA)

* GR716A and GR716B

* GR740 (also available from ESA)

* GR765

* UT699/UT699E/UT700

Microchip
---------

On request, QDPs can be made available by embedded brains for the following
products and product lines from
`Microchip <https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/32-bit-mcus>`__:

* PolarFire SoC

* SAMRH707 - Radiation Hardness

* SAMRH71 - Radiation Hardened

* SAMV71Q21RT - Radiation Tolerance

* SAM V MCUs

* SAM E MCUs

* SAM S MCUs

NanoXplore
----------

On request, QDPs can be made available by embedded brains for the following
products and product lines from
`NanoXplore <https://nanoxplore.com/>`__:

* NG-ULTRA

Teledyne e2v Semiconductors
---------------------------

On request, QDPs can be made available by embedded brains for the following products
and product lines from
`Teledyne e2v Semiconductors <https://semiconductors.teledyneimaging.com/en/home/>`__:

* LS1046-Space: Radiation Tolerant Quad ARM Cortex-A72

* Products based on NXP Layerscape

* Products based on NXP QorIQ P-Series

* Products based on NXP QorIQ T-Series

Texas Instruments
-----------------

On request, QDPs can be made available by embedded brains for the following products
from
`Texas Instruments <https://www.ti.com/microcontrollers-mcus-processors/arm-based-microcontrollers/arm-cortex-r-mcus/overview.html>`__:

* TMS570LC4357

* TMS570LS3137

VORAGO
------

On request, QDPs can be made available by embedded brains for the following
products and product lines from
`VORAGO <https://www.voragotech.com/>`__:

* VA41600

* VA41620

* VA41628

* VA41629

* VA41630

.. _LicenseInfo:

License information
===================

${.:/license-info}

.. _ISVVLicense:

ISVV documents copyrights and license
-------------------------------------

| © 2022 Airbus Defence and Space Limited
| © 2021, 2023 Critical Software SA

The copyright holders listed above grant that the
${/glossary/isvv:/term} documents

* :file:`CSW-RTEMSISVV-2021-GLS-04956_4-rtems-smp-isvv-glossary-and-acronyms.pdf`

* :file:`CSW-RTEMSISVV-2023-PLN-01130_2-rtems-smp-isvv-ive-plan.pdf`

* :file:`CSW-RTEMSISVV-2021-RPT-04960_7-rtems-smp-isvv-ive-report.pdf`

* :file:`CSW-RTEMSISVV-2021-RPT-04960_7-rtems-smp-isvv-ive-report-code-annex.pdf`

* :file:`CSW-RTEMSISVV-2021-RPT-04960_7-rtems-smp-isvv-ive-report-code-annex.xlsx`

* :file:`CSW-RTEMSISVV-2021-SVP-04961_6-rtems-smp-isvv-iva-plan.pdf`

* :file:`CSW-RTEMSISVV-2021-RPT-04962_4-rtems-smp-isvv-iva-report.pdf`

* :file:`CSW-RTEMSISVV-2022-TCS-02711_9-rtems-smp-isvv-iva-test-specification-worksheet.pdf`

* :file:`CSW-RTEMSISVV-2022-TCS-02711_9-rtems-smp-isvv-iva-test-specification-worksheet.xlsx`

* :file:`CSW-RTEMSISVV-2023-LST-01297_3-rtems-smp-isvv-all-findings-except-for-code-analysis.pdf`

* :file:`CSW-RTEMSISVV-2023-LST-01297_3-rtems-smp-isvv-all-findings-except-for-code-analysis.xlsx`

may be reproduced in whole or in part, or stored in a retrieval system,
or transmitted in any form, or by any means electronic, mechanical,
photocopying or otherwise, under the `Creative Commons
Attribution-ShareAlike 4.0 International Public License
<https://creativecommons.org/licenses/by-sa/4.0/legalcode>`_.

.. _BuildDescription:

Package build description
=========================

${.:/build-description:1:/pkg/deployment/archive}
