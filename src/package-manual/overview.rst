.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2021 embedded brains GmbH & Co. KG

.. _Overview:

Software configuration item overview
************************************

Documents generated specifically for a package contain a package variant
identification and version, for example ``[${.:/component/ident}]``.  The
package variant may have an impact on the content of documents.  For example,
the ${/glossary/srs:/term} generated for an SMP configuration will contain
other requirements compared to the SRS generated for an uniprocessor
configuration.  Another example are the memory benchmarks and object sizes
presented in this document, see :ref:`Membench` and :ref:`Memobj`.  In addition
to the package variant identification and version, each document has a release
number which is defined in the document-specific changes information placed
after the table of contents.

.. _TestReports:

Test reports
============

The package includes the following test reports:

${.:/document-elements:1:tr}

.. _ECSSSoftwareDocumentation:

ECSS software documentation overview
====================================

${.:/push-enabled-by:not: pkg.feature.qual}
The package contains no ECSS documents.  You can upgrade the package on
request, see also :ref:`Service`.
${.:/pop-enabled-by}

${.:/push-enabled-by:pkg.feature.qual}

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

Requirements Baseline
---------------------

The Requirement Baseline (${/glossary/rb:/term}) which consists of the Software
System Specification (${/glossary/sss:/term}) and the Software Interface
Requirements Document (${/glossary/ird:/term}) is not contained in the QDP.
The system requirements are to be defined by you, the end user of the QDP.
RTEMS is designed as a reusable software product which can be utilised by
application designers to ease the development of their applications.  The
requirements of the end system (system requirements) using RTEMS are only known
to the application designer.  RTEMS itself is developed by the RTEMS
maintainers and they do not know the requirements of a particular end system in
general.  RTEMS is designed as a real-time operating system to meet typical
system requirements for a wide range of applications.  Its suitability for a
particular application must be determined by the application designer based on
the technical specification provided by the QDP accompanied with performance
data for a particular target platform.

Technical Specification (TS)
----------------------------

The package includes the following documents of the Technical Specification
(TS):

* Software Requirements Specification (SRS)

${.:/document-elements:2:srs}

* Interface Control Document (ICD)

${.:/document-elements:2:icd}

Design Definition File (DDF)
----------------------------

The package includes the following documents of the Design Definition File
(DDF):

* Software Configuration File (SCF)

  The SCF is this document.  It is an exception, since it is contained outside
  the QDP.  The reason for being not included in the QDP is that the SCF may be
  used to verify the authenticity and integrity of the QDP, see
  :ref:`InventorySCI`.

* Software Detailed Design (SDD)

${.:/document-elements:2:sdd}

* Software Release Document (SRelD)

${.:/document-elements:2:sreld}

* Software User Manual (SUM)

  The QDP does **not** provide a SUM which strictly follows the ECSS clauses.
  Please refer to the SCF (this document) and the :ref:`RTEMSDocs`.

Design Justification File (DJF)
-------------------------------

The package includes the following documents of the Design Justification File
(DJF):

* Software Reuse File (SRF)

  .. note::

      This document is not included in the package.

* Software Unit and Integration Test Plan (SUITP)

${.:/document-elements:2:suitp}

* Software Unit and Integration Test Report (SUITR) and
  Software Validation Report (SValR) with Respect to TS

${.:/document-elements:2:tr}

* Software Validation Specification (SVS) with Respect to TS

${.:/document-elements:2:svs}

* Software Verification Report (SVR)

${.:/document-elements:2:svr}

Management File (MGT)
---------------------

The package includes the following documents of the Management File (MGT):

* Software Development Plan (SDP)


  .. note::

      This document is not included in the package.

* Software Review Plan (SRevP)

  .. note::

      This document is not included in the package.

* Software Configuration Management Plan (SCMP)

  .. note::

      This document is not included in the package.

Maintenance File (MF)
---------------------

The maintenance software life cycle state is not covered by the QDP.  The RTEMS
development will continue independently.  One goal of the project which
delivered this QDP was to establish procedures in the RTEMS community so that
the quality level achieved by the activity can be maintained in the future
development of RTEMS.

Operational (OP)
----------------

The operational software life cycle state is not covered by the QDP.  You, as
an end user of the QDP, will hopefully have an operational phase if the
software product delivered by the QDP is used in your applications.

Product Assurance File (PAF)
----------------------------

The package includes the following documents of the Product Assurance File
(PAF):

* Software Product Assurance Milestone Report (SPAMR)

${.:/document-elements:2:spamr}

* Software Product Assurance Plan (SPAP)

  .. note::

      This document is not included in the package.

${.:/pop-enabled-by}

.. _TechNotes:

Technical notes overview
========================

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

The package includes the following technical notes:

* ${/ref/tn/qt-109-r6:/cite-long}

  * `<${/pkg/deployment/doc-tn-qt:/file:relpath %(*:/directory)}>`__

* ${/ref/tn/rtems-space-profile-r6:/cite-long}

  * `<${/pkg/deployment/doc-tn-sp:/file:relpath %(*:/directory)}>`__

.. _RTEMSDocs:

RTEMS documentation overview
============================

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

The package includes the following manuals of the RTEMS documentation set:

* RTEMS User Manual ${/ref/rtems/user:/cite}

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/user.pdf>`__

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/user/index.html>`__

* RTEMS Classic API Guide ${/ref/rtems/c-user:/cite}

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/c-user.pdf>`__

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/c-user/index.html>`__

* RTEMS Software Engineering ${/ref/rtems/eng:/cite}

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/eng.pdf>`__

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/eng/index.html>`__

* RTEMS CPU Supplement ${/ref/rtems/cpu:/cite}

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/cpu-supplement.pdf>`__

  * `<${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/cpu-supplement/index.html>`__

.. _FormalMethods:

Formal methods documentation overview
=====================================

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

The package includes the following Formal Methods documentation set:

* ${/ref/tn/rtems-fvp:/cite-long}

  * `<${/pkg/deployment/doc-fm-fvp:/file:relpath %(*:/directory)}>`__

* ${/ref/tn/rtems-fva:/cite-long}

  * `<${/pkg/deployment/doc-fm-fva:/file:relpath %(*:/directory)}>`__

* ${/ref/tn/rtems-fvr:/cite-long}

  * `<${/pkg/deployment/doc-fm-fvr:/file:relpath %(*:/directory)}>`__

.. _ISVVDocs:

ISVV documentation overview
===========================

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

.. note::

    The documents are not included in this package.

For license information about ${/glossary/isvv:/term} related documents,
please, see :ref:`ISVVLicense`.

${.:/push-enabled-by:pkg.feature.qual}

.. _PackageV6Documents:

Package version 6 documents
===========================

Before trying to access the documents, please read the :ref:`GettingStarted`
section and unpack the package archive.

The package includes the following documents of package version 6 for
reference:

.. note::

    The documents are not included in the package.

${.:/pop-enabled-by}

.. _GitRepos:

Git repositories
================

The package contains the following Git repositories.  Optionally, you can fetch
the repository state with the ``git fetch origin`` command from the upstream
project.  For example, this gives you access to the complete source code
history of the RTEMS Project.  Since the source code is delivered in Git
repositories you know exactly which changes were done for the package on top of
the software baseline provided by the RTEMS Project or other open source
projects.  You can directly use the package branches to do project-specific
customisations.

${.:/repositories}

.. _ApplBuild:

Guidelines for the application build
====================================

Recommended optimisation flags
------------------------------

It is recommended to use the following optimisation flags to compile C code of
applications and libraries:

    ``-O2 -ffunction-sections -fdata-sections -g``

These flags are used to compile the production BSPs provided by the package.
To link executables, it is recommended to enable the linker garbage collection
with ``-Wl,--gc-sections``.  The test programs of the BSP were linked with this
option.  The rationale for using ``-O2`` is that this optimisation level is
commonly used.

Using function and data sections has an impact on the code generation since
locations in translation units are unknown until link time.  However, together
with the linker garbage collection, smaller statically-linked executables can
be produced.  This helps to include only code in the executable that is
actually used by the application.  It avoids shipping executables with dead (or
deactivated) code, which just wastes the typically expensive memory in the
space domain. In addition, it may reduce the bandwidth requirements when flight
software needs to be patched or uploaded in flight.

The application may use other optimisation flags if necessary.  However, the
${/glossary/abi:/term} shall be compatible to the BSP.  See also
:ref:`Examples`.

.. _ToolFlags:

Mandatory compiler/linker flags
-------------------------------

It is absolutely mandatory to adhere to the ${/glossary/abi:/term} defined by
the BSP.  It is recommended to use exactly the ABI relevant flags (machine
flags) defined by the BSP for the application.  You can query the ABI flags,
``CFLAGS``, and linker flags of the desired BSP with the ``pkg-config`` command
line tool.

Using ``pkg-config`` to query the tool flags of the BSP avoids having
hard-coded flags in the application build system.  It is recommended to place
the linker flags provided by ``pkg-config`` to the end of the linker command
line used to link the application executable.  See also :ref:`Examples`.
Linking to :file:`libgcc.a` is not strictly required to use the operating
system services, see also :ref:`ExternallyProvidedItems`.  It is strongly
recommended to review the linker map file of the application executable to
check that all dependencies have an adequate quality level.

${.:/sections:2:pkg-config}

.. _BSPOverview:

BSP and third-party library installation overview
=================================================

${.:/sections:1:bsp-overview}

.. _Membench:

Static memory usage benchmarks
==============================

${.:/sections:1:membench}

.. _Memobj:

Memory usage of objects
=======================

${.:/sections:1:object-sizes}

.. _Migration:

Migration hints for applications
================================

This section covers some topics which need to be considered when migrating an
application from a previous RTEMS versions to the RTEMS version delivered by
the package.  The focus is on a migration from RTEMS 4.8 and the EDISOFT RTEMS
Improvement.  For migration help from other versions, see also the
`RTEMS User Manual <${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/user/migration/index.html>`__.

No -specs bsp_specs GCC option
------------------------------

The ``-spec bsp_specs`` GCC Option is no longer needed to build RTEMS
applications and there is no :file:`bsp_specs` file installed.  If you use this
option, then you get an error like this:

.. code-block:: none

    ${.:/component/arch}-rtems${.:/component/rtems-version}-gcc: fatal error: cannot read spec file 'bsp_specs': No such file or directory

You can remove this GCC option from your build to fix this error.
Alternatively, you can add an empty :file:`bsp_specs` file.

No manager stubs
----------------

Older RTEMS versions provided stub files for some RTEMS Managers.  These stub
files are no longer needed and they are not installed.  Remove the support for
them in your build system.

rtems_task_create() vs. rtems_task_construct()
----------------------------------------------

The ${/rtems/task/if/create:/name} directive is pre-qualified, however, it is
only available if a custom stack allocator is configured.  It is recommended to
use ${/rtems/task/if/construct:/name} instead, for example:

.. code-block:: c

    #define MAX_TLS_SIZE RTEMS_ALIGN_UP( 64, RTEMS_TASK_STORAGE_ALIGNMENT )

    #define TASK_ATTRIBUTES RTEMS_DEFAULT_ATTRIBUTES

    RTEMS_ALIGNED( RTEMS_TASK_STORAGE_ALIGNMENT )
    static char task_storage[
      RTEMS_TASK_STORAGE_SIZE(
        MAX_TLS_SIZE + RTEMS_MINIMUM_STACK_SIZE,
        TASK_ATTRIBUTES
      )
    ];

    static const rtems_task_config task_config = {
      .name = rtems_build_name( 'T', 'A', 'S', 'K' ),
      .initial_priority = 123,
      .storage_area = task_storage,
      .storage_size = sizeof( task_storage ),
      .maximum_thread_local_storage_size = MAX_TLS_SIZE,
      .initial_modes = RTEMS_DEFAULT_MODES,
      .attributes = TASK_ATTRIBUTES
    };

    void construct( void )
    {
      rtems_status_code sc;
      rtems_id          id;

      sc = rtems_task_construct( &task_config, &id );
      if ( sc != RTEMS_SUCCESSFUL ) {
        oops();
      }
    }

Task storage area for initialization task
-----------------------------------------

Since the ${/rtems/task/if/create:/name} directive is not supported without a
custom stack allocator in the pre-qualified feature set of RTEMS, the task
storage area for the initialization task shall be provided by the application.
The application shall define the application configuration option
${/acfg/if/init-task-construct-storage-size:/name} and the related options:

.. code-block:: c

    #define MAX_TLS_SIZE RTEMS_ALIGN_UP( 64, RTEMS_TASK_STORAGE_ALIGNMENT )

    #define TASK_ATTRIBUTES RTEMS_DEFAULT_ATTRIBUTES

    #define TASK_STORAGE_SIZE \
      RTEMS_TASK_STORAGE_SIZE( \
        MAX_TLS_SIZE + RTEMS_MINIMUM_STACK_SIZE, \
        TASK_ATTRIBUTES \
      )

    #define CONFIGURE_MAXIMUM_THREAD_LOCAL_STORAGE_SIZE MAX_TLS_SIZE

    #define CONFIGURE_RTEMS_INIT_TASKS_TABLE

    #define CONFIGURE_INIT_TASK_ATTRIBUTES TASK_ATTRIBUTES

    #define CONFIGURE_INIT_TASK_CONSTRUCT_STORAGE_SIZE TASK_STORAGE_SIZE

The maximum thread-local storage size of the application and the initialization
task must be consistent.  In the example above, this is ensured by using
:c:macro:`MAX_TLS_SIZE` for all definitions.  For your application, replace the
example value of 64 with the maximum thread-local storage size required by your
application.  The task attributes of the initialization task shall be
consistent with the task attributes used to define the initialization task
storage area.  In the example above, this is ensured by using
:c:macro:`TASK_ATTRIBUTES` for all definitions.  Your application may use
different attributes.

For an example which uses these application configuration options, see
:ref:`Examples`.

rtems_message_queue_create() vs. rtems_message_queue_construct()
----------------------------------------------------------------

The ${/rtems/message/if/create:/name} directive is not pre-qualified.  As a
pre-qualified alternative use ${/rtems/message/if/construct:/name} instead, for
example:

.. code-block:: c

    #define MSG_SIZE sizeof( int )

    static RTEMS_MESSAGE_QUEUE_BUFFER( MSG_SIZE ) msg_buffers[ 13 ];

    static const rtems_message_queue_config msg_queue_config = {
      .name = rtems_build_name( 'M', 'S', 'G', 'Q' ),
      .maximum_pending_messages = RTEMS_ARRAY_SIZE( msg_buffers ),
      .maximum_message_size = MSG_SIZE,
      .storage_area = msg_buffers,
      .storage_size = sizeof( msg_buffers ),
      .attributes = RTEMS_DEFAULT_ATTRIBUTES
    };

    void construct( void )
    {
      rtems_status_code sc;
      rtems_id          id;

      sc = rtems_message_queue_construct( &msg_queue_config, &id );
      if ( sc != RTEMS_SUCCESSFUL ) {
        oops();
      }
    }

How to install interrupt handlers?
----------------------------------

Do not use :c:func:`rtems_interrupt_catch`, :c:func:`set_vector`, or
:c:func:`_CPU_ISR_install_vector` to install an interrupt handler.  Instead,
use ${/rtems/intr/if/entry-install:/name}.

No free()
---------

You can allocate memory using the :c:func:`rtems_malloc`,
:c:func:`rtems_calloc`, and :c:func:`posix_memalign` functions. However, the
:c:func:`free` function is not pre-qualified.  There is also no
:c:func:`malloc`, :c:func:`calloc`, :c:func:`realloc`, and
:c:func:`aligned_alloc` available since these functions depend on
:c:data:`errno` which is not pre-qualified.

No filesystem support
----------------------

The file systems supported by RTEMS are not pre-qualified.  Therefore, the
application configuration options ${/acfg/if/max-file-descriptors:/name} and
${/acfg/if/appl-disable-filesystem:/name} are mandatory for each application
which is restricted to only use pre-qualified interfaces of RTEMS:

.. code-block:: c

    #define CONFIGURE_MAXIMUM_FILE_DESCRIPTORS 0

    #define CONFIGURE_APPLICATION_DISABLE_FILESYSTEM

If you do not have these option defined, then you get linker errors for an
undefined reference to ``rtems_filesystem_initialize``.  For an example which
uses these application configuration options, see :ref:`Examples`.

No Newlib reentrancy support
----------------------------

The Newlib reentrancy support is not pre-qualified.  Therefore, the application
configuration option ${/acfg/if/disable-newlib-reentrancy:/name} is mandatory
for each application which is restricted to only use pre-qualified interfaces
of RTEMS:

.. code-block:: c

    #define CONFIGURE_DISABLE_NEWLIB_REENTRANCY

If you do not have this option defined, then you get linker errors for
undefined references to ``newlib_create_hook`` and ``newlib_terminate_hook``.
For an example which uses this application configuration option, see
:ref:`Examples`.

.. _LinkerCommandFileRequirements:

Linker command file requirements
--------------------------------

The RTEMS version of the package supports thread-local storage
(${/glossary/tls:/term}) and uses a
`linker set <${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/c-user/linker_sets.html>`__
based system initialization.  For this some linker output section definitions are
required to be present in the linker command file.  It is recommended to use
the linker command file installed by the BSP.  To use a custom linker command
file, use the following options: ``-qnolinkcmds -T yourlinkcmds``.

By default, RTEMS is compiled with function and data sections enabled
(``-ffunction-sections`` and ``-fdata-sections``).  Applications should be
linked with the linker garbage collection enabled (``-Wl,--gc-sections``).  For
this it is necessary that some linker input sections (for example the static
constructor and destructor sections) use the ``KEEP()`` directive.  For a
reference, see the linker command file installed by the BSP.  Previous RTEMS
versions did not use these options, so the ``KEEP()`` directive may be missing
in custom linker command files.

The linker output section definitions presented next are mandatory in linker
command files used for the RTEMS version delivered by the package and may be
missing in custom linker command files which worked with previous RTEMS
version.  There shall be the following linker output section definition in a
read-only memory area to support thread-local storage:

.. code-block:: none

    .tdata : {
      _TLS_Data_begin = .;
      *(.tdata .tdata.* .gnu.linkonce.td.*)
      _TLS_Data_end = .;
    }
    .tbss : {
      _TLS_BSS_begin = .;
      *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon)
      _TLS_BSS_end = .;
    }
    _TLS_Data_size = _TLS_Data_end - _TLS_Data_begin;
    _TLS_Data_begin = _TLS_Data_size != 0 ? _TLS_Data_begin : _TLS_BSS_begin;
    _TLS_Data_end = _TLS_Data_size != 0 ? _TLS_Data_end : _TLS_BSS_begin;
    _TLS_BSS_size = _TLS_BSS_end - _TLS_BSS_begin;
    _TLS_Size = _TLS_BSS_end - _TLS_Data_begin;
    _TLS_Alignment = MAX (ALIGNOF (.tdata), ALIGNOF (.tbss));

The section for the thread-local storage data can and should be read-only since
it contains only loadable initialization data.  This data is used to initialize
the thread-local storage area of a thread during its creation.

There shall be the following linker output section definition in a read-only
memory area to support the read-only RTEMS linker sets:

.. code-block:: none

    .rtemsroset : {
      KEEP (*(SORT(.rtemsroset.*)))
    }

There shall be the following linker output section definition in a read-write
memory area to support the read-write RTEMS linker sets:

.. code-block:: none

    .rtemsrwset : {
      KEEP (*(SORT(.rtemsrwset.*)))
    }

There shall be the following linker output section definition in an
uninitialised read-write memory area to support the statically allocated RTEMS
tasks:

.. code-block:: none

    .rtemsstack (NOLOAD) : {
      *(SORT_BY_ALIGNMENT (SORT_BY_NAME (.rtemsstack*)))
    }

The ``NOLOAD`` output section type just marks the section as not loadable.
This section is similar to the ``.bss`` section except that the content of the
``.rtemsstack`` section is not zero initialised.  It is not initialised at all
and may have arbitrary content.  This reduces the time to boot the application.
The section still uses memory space and shall not overlap with other sections.

Make sure that your MMU initialization covers the new sections.

No EDISOFT RTEMS improvement error reporting
--------------------------------------------

A unique feature of EDISOFT RTEMS Improvement is that fatal and non-fatal
errors can be reported, stored, and retrieved.  The error reporting is done by
all directives.  Applications can report errors with the
:c:func:`rtems_error_report` directive and retrieve reported errors through the
:c:func:`rtems_error_get_latest_non_fatal_by_offset` and
:c:func:`rtems_error_get_latest_fatal_by_offset` directives.  These directives
are not supported by any RTEMS version of the RTEMS Project.  They are also not
supported by the RTEMS version delivered by the package.  Applications should
do the error reporting if needed on their own.  The RTEMS Project offers
alternative tracing solutions, see also the
`RTEMS User Manual <${/pkg/deployment/doc-rtems:/directory:relpath %(*:/directory)}/user/tracing/eventrecording.html>`__.

Customise the inter-processor interrupt number
----------------------------------------------

For the SMP support of RTEMS, an inter-processor interrupt is required.  By
default, interrupt number 14 is used for the inter-processor interrupt on the
LEON3 BSPs.  You can define the interrupt number in your application
configuration with this code, for example if the default value conflicts with
one of your device drivers.  The inter-processor interrupt should have a low
priority since it performs no timing critical activities.

.. code-block:: c

    #include <bsp.h>

    const unsigned char LEON3_mp_irq = 13;

    /* Your application configuration options */

    #include <rtems/confdefs.h>

Hardware errata
---------------

The package addresses hardware errata published before the package was created.
Errata may get reported after the creation of the package.  It is recommended
to consult the documentation provided by the hardware vendor with respect to
hardware errata workarounds and limitations.

.. _PreQualifiedInterfaces:

Pre-qualified interfaces
========================

${.:/push-enabled-by:pkg.feature.qual}
The following sections list the pre-qualified functions, macros, and
application configuration options which may be directly used by applications.

${.:/sections:1:pre-qualified-interfaces}
${.:/pop-enabled-by}

${.:/push-enabled-by:not: pkg.feature.qual}
The package contains no pre-qualified components.
${.:/pop-enabled-by}

${.:/sections:0:overview}
