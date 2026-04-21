.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2021 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

.. _VerificationActivities:

Verification Activities Reporting and Monitoring
************************************************

.. _AutomaticallyGeneratedCode:

General
=======

Automatically generated code has its origin in some specification items.
These items contain pieces of human written code. We use tools to
assemble these pieces of manual conceived code into entire files of code.
These files contain the collected pieces of hand written code, some generated
header and trailer code as well as tables which are also derived from
manually created specification items.
All other code is fully hand written.

Automatically generated code files are treated as if there were hand written:

    * The tool to generate the code is run by a programmer.
    * The generated files are inspected and tested by that programmer.
    * The generated files are sent to the developer mailing list as if
      that programmer had created them by hand.
    * The generated files are reviewed on the mailing list like any
      other files and any findings must be fixed.
    * Finally, the generated code is committed to the source code
      repository like all hand written code.
    * This means, the automatically produced code is not generated anew
      every time the operating system is built. Instead, the code is generated
      once, reviewed, committed to the other source code. The operating system
      is then built again and again from that once checked-in source code
      without generating it every time from scratch.

As automatically generated code in :term:`RTEMS` is handled like hand written
code, the verification activities performed on generated code are exactly the
same as those for hand written code.

.. _NoRB:

Software Related System Requirements Process Verification (for SRR)
===================================================================

The ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}
(${/glossary/sss:/term} and ${/glossary/ird:/term}).  The system requirements
are to be defined by the end user of the QDP.  RTEMS is designed as a reusable
software product which can be utilized by application designers to ease the
development of their applications.  The requirements of the end system (system
requirements) using RTEMS are only known to the application designer.  RTEMS
itself is developed by the RTEMS maintainers and they do not know the
requirements of a particular end system in general.  RTEMS is designed as a
real-time operating system to meet typical system requirements for a wide range
of applications.  Its suitability for a particular application must be
determined by the application designer based on the technical specification
provided by RTEMS accompanied with performance data for a particular target
platform.  See also section *No Requirements Baseline (RB)* of the
${/ref/tn/qt-109-r6:/cite-long}.

Independent of the lack of RB documents, the more than 30 years of RTEMS
development and the continuous adoption to user needs should give some evidence
that there are working processes in place.

A system model is not provided by the QDP.  See also section *No Logical and
Computational Model* of the ${/ref/tn/qt-109-r6:/cite-long}.

Software Requirements and Architecture Engineering Process Verification (for PDR)
=================================================================================

Traceability
------------

.. _SoftwareRequirementsToSystemRequirements:

Software Requirements to System Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
:ref:`NoRB`.

.. _RequirementsToSoftwareDesignComponents:

Requirements to Software Design Components
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Software architecture components are design components.  The table below lists
for each requirement the associated design components.

${.:/traceability-requirements-to-design}

.. _SoftwareDesignComponentsToRequirements:

Software Design Components to Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Software architecture components are design components.  The table below lists
for each design component the associated requirements.

${.:/traceability-design-to-requirements}

Feasibility
-----------

.. _SoftwareRequirementsVerification:

Software Requirements Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The verification activities related to the ${/glossary/ts:/term} are mandated
by clause 5.8.3.2 of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

* **Reviewer:** Frank Kühndel (embedded brains)
* **Review Date:** 2021-11-26, 2021-11-10,
  previous reviews 2021-01-12/13, 2021-10-28 opened `Issue #645`_.
* **Input Items:**

    * |E40| ${/ref/ecss/q-st-40c-r1:/cite}, clause 5.8.3.2
    * |Q80| ${/ref/ecss/q-st-80c-r1:/cite}, clause 7.2.1.3
    * |SRS| release 1 ${doc-ts-srs:/cite}
      (for review 2021-11-26 the one found in `Issue #739`_)
    * |ICD| release 1 ${doc-ts-icd:/cite}
      (for review 2021-11-26 the one found in `Issue #739`_)

1. Software requirements and interface are externally and internally
   consistent

       - **Compliant:** OK.

       - **Verification:** As random sample, these :term:`SRS` software
         requirements and :term:`ICD` interface requirements have been
         checked for consistency:

             + :term:`SRS` ``spec:/rtems/event/req/receive``
             + :term:`SRS` ``spec:/rtems/event/req/send``
             + :term:`SRS` ``spec:/rtems/event/req/send-receive``
             + :term:`SRS` ``spec:/rtems/event/req/system-receive``
             + :term:`SRS` ``spec:/rtems/event/req/system-send``
             + :term:`ICD` ``spec:/rtems/mode/req/bit-set``
             + :term:`ICD` ``spec:/rtems/mode/req/default``
             + :term:`ICD` ``spec:/rtems/mode/req/masks``
             + :term:`ICD` ``spec:/rtems/mode/req/masks-all``
             + :term:`ICD` ``spec:/rtems/mode/req/masks-unique``
             + :term:`ICD` ``spec:/rtems/mode/req/unique``

       - **Comment:** The requirements of some managers rely on a glossary,
         for example ``spec:/rtems/ratemon/req/period``.
         These glossary items are neither linked nor included in the
         :term:`SRS`.

.. _`Issue #645`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/645
.. _`Issue #739`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/739

2. This verification activity is not applicable because the
   ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
   :ref:`NoRB`.

3. This verification activity is not applicable because the
   ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
   :ref:`NoRB`.

4. This verification activity is not applicable because the
   ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
   :ref:`NoRB`.  Without a requirements baseline no verification methods can
   exist.

5. The :term:`RTEMS` software is already implemented. Hence, the software
   design is feasible.

       - **Compliant:** Yes

       - **Verification:** Source code exists, can be compiled and tests
         can be executed.

6. Operation and maintenance have apparently been feasible since :term:`RTEMS`
   public availability in 1993.
7. Not applicable because

       + :term:`SRS` section 4.12 *Safety requirements* states:
         *There are no safety requirements*.
       + :term:`SRS` section 4.7 *Security and privacy requirements* states:
         *There are no security or privacy requirements*.
       + :term:`SRS` and :term:`ICD` contain no criticality requirements.
         Moreover, a :term:`FMECA` did not lead to criticality requirements
         (see section :ref:`OtherSpecificVerificationRAMS_CDR`).

8. The hardware environment constraints are identified

       - **Compliant:** Yes

      - **Verification:** Review of :term:`SRS`

           + section 4.2 *Environmental considerations*
           + section 4.4 *Constraints*

9.  The implementation constraints are identified

       - **Compliant:** Yes

      - **Verification:** Review of :term:`SRS`

           + chapter 5 *Constraints*

10. a) Not applicable because of none existing requirements baseline, see :ref:`NoRB`.
    b) Table 1: *Validation Requirements* in section *Validation Requirements*
       of the :term:`SRS` lists the validation method per requirement.
       Table 1: *Validation Requirements* in section *Validation Requirements*
       of the :term:`ICD` lists the validation method per requirement.

       - **Compliant:** Yes

       - **Verification:** Review of :term:`SRS` and :term:`ICD` for validation
         methods per requirement.

       - **Comment:** Verification methods cannot be defined because there
         is no requirements baseline, see :ref:`NoRB`.

11. Not applicable because there is no logical model
    (see ${/ref/tn/qt-109-r6:/cite-long} section
    *9.4.7 No Logical and Computational Model*).

.. In case there are several items which need to be verified (such as different
   software documents), there may be a report on each individual item
   or one report on all items. The reports may be included in this SVR or
   this SVR will reference the documents containing the reports.

.. _HMIEvaluation:

HMI Evaluation
^^^^^^^^^^^^^^

The pre-qualified feature set of RTEMS does not include a Human Machine Interface.

Behavioural Verification of the Logical Model and Architectural Design Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not applicable because there is no logical model
(see ${/ref/tn/qt-109-r6:/cite-long} section *9.4.7 No Logical and Computational Model*).

.. _VerificationOfTheSoftwareArchitecturalAndInterfaceDesign:

Verification of the Software Architectural and Interface Design
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The verification activities related to the software architectural design are
mandated by clause 5.8.3.3.a of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2021-10-29; a previous review 2021-02-02/05 opened
`Issue #640`_ and `Issue #645`_.

**Input Items:**

* ${/ref/ecss/q-st-40c-r1:/cite-long}, clause 5.8.3.3a

* ${doc-ts-icd:/cite-long}

* ${ref-ddf-sdd:/cite-long}

* ${/ref/tn/rtems-space-profile-r6:/cite-long}

* ${doc-ts-srs:/cite-long}

**Compliant:** Yes

1.  There is no |RB|. Instead, the |SP| is used here as substitute to
    at least check consistency against the |SP| somewhere. Note that
    the |SP| does not state any requirements so that these cannot be
    checked here.

    **Verification:**

      1. All components mentioned in the |SP| chapter
         *3. Space Profile Definition* are present in the :term:`ICD`
         with interfaces.

      2. All components mentioned in the |SP| chapter
         *3. Space Profile Definition* are present at least
         in the :term:`ICD` or :term:`SRS` with requirements.

      3. All functions mentioned in the |SP| chapter
         *3. Space Profile Definition* have at least one requirement
         in the :term:`ICD` or :term:`SRS`. This has checked for
         the Barrier Manager and Message Manager as random sample.

.. _IcdAndSrsIncompleteFinding:

    **Notes:**

      + The *Extensions Manager* appears as *userext*.

      + The requirements for directives ``rtems_message_queue_flush()`` and
        ``rtems_message_queue_get_number_pending()`` are merged together in
        :term:`SRS` section *spec:/rtems/message/req/flush-pending*.

      + The requirements for directives ``rtems_message_queue_send()`` and
        ``rtems_message_queue_urgent()`` are merged together in
        :term:`SRS` section *spec:/rtems/message/req/urgent-send*.

      + The requirement for the macro ``CONFIGURE_MAXIMUM_MESSAGE_QUEUES``
        can be found in the :term:`ICD` section
        *spec:/acfg/req/max-message-queues*.

      + The requirement for the macro ``RTEMS_MESSAGE_QUEUE_BUFFER``
        can be found in the :term:`ICD` section
        *spec:/rtems/message/req/buffer*.

.. _`Issue #640`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/640

.. _SoftwareArchitecturalVerificationPoint2:

2.  The software components are internal consistent.

    **Review Date:** 2021-09-22 (a preceding review 2021-02-02/05 opened
    issue `Issue #663`_).

    The findings of review 2021-02-02/05 have been resolved.
    There are still todos in the :term:`SDD` such as missing
    diagrams but these are considered minor and are tracked in `Issue #738`_.

.. _`Issue #663`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/663
.. _`Issue #738`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/738

3.  The section :ref:`RequirementsToSoftwareDesignComponents` presents the
    traceability from requirements to design components.  The section
    :ref:`SoftwareDesignComponentsToRequirements` presents the traceability
    from design components to requirements.  The completeness was verified by
    review:

    * **Reviewer:** Frank Kühndel (embedded brains)
    * **Review Date:** 2021-01-19 (Opened `Issue #660`_), 2021-05-27 (Update),
      2021-09-22 (Update), 2021-10-29 (Update), 2021-11-26 (Update),
      2021-12-08 (Update)
    * **Input Item:**

        + *Table 2: Requirement, test status* from section
          :ref:`Verification of Software Validation w.r.t. TS
          <Verification_of_software_validation>`.
        + |SRS| ${doc-ts-srs:/cite}
        + *Table 1: Requirement to Design to Code Traceability* above
        + *Table 2: Design to Requirement Traceability* above
        + *Table 3: Design to Code Traceability* above
        + *Table 4: Code to Design Traceability* above

    * **Compliant:** OK
    * **Verification:**

        + Compare the content of the above tables with the
          requirements listed in the :term:`SRS`. Random sample check that the
          requirements are implemented in the specified file.

        + The tables should only list traced elements (none "N/A" in the tables).

    * **Comments:**

        + *Table 1: Requirement to Design Traceability*
          lists these elements as traced to "N/A":

            - ``/req/api``
            - ``/req/applconfig``
            - ``/req/domains``
            - ``/req/errata``
            - ``/req/fatal-error``
            - ``/req/fine-grained-locking``
            - ``/req/mem-benchmark``
            - ``/req/perf-runtime``
            - ``/req/root``
            - ``/req/terminate``
            - ``/req/test-suites``
            - ``/req/root``

          These are top level requirements and apply to the whole product.
          Therefore, they are not traced. See also `Comment 22674`_ in `Issue #660`_
          made during AR/FR preparation meeting 2021-12-03.

        + *Table 4: Code to Design Traceability*
          still lists these elements as traced to "N/A" at the time of writing:

            - ``bsps/sparc/include/drvmgr/leon2_amba_bus.h``
            - ``cpukit/include/sys/priority.h``

          The source file ``leon2_amba_bus.h`` is going to be removed.
          The source file ``priority.h`` is going to be traced to
          ``RTEMSImplKernel`` *RTEMS Kernel Interface*.

.. _`Issue #660`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/660
.. _`Comment 22674`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/660#note_22674

.. _IcdIncompleteFinding:

4.  There is no |RB|. Instead, the |SP| is used here as substitute to
    at least check consistency against the |SP| somewhere.

    **Review Date:** 2021-11-19, 2021-10-29
    (a preceding review 2021-02-02/05 opened issue `Issue #662`_).

    **Verification:**
    Search for components or functions mentioned in the :term:`ICD`
    but not stated in the |SP| chapter *3. Space Profile Definition*.
    Check that a rational for all such components or functions is given.

    **Findings:**

     + The :term:`ICD` contains interface specifications for the following
       functions despite these are not in the |SP|:

       - ``rtems_barrier_delete()``
       - ``rtems_clock_get_boot_time()``
       - ``rtems_clock_get_boot_time_bintime()``
       - ``rtems_clock_get_boot_time_timeval()``
       - ``rtems_clock_get_monotonic()``
       - ``rtems_clock_get_monotonic_bintime()``
       - ``rtems_clock_get_monotonic_coarse()``
       - ``rtems_clock_get_monotonic_coarse_bintime()``
       - ``rtems_clock_get_monotonic_coarse_timeval()``
       - ``rtems_clock_get_monotonic_sbintime()``
       - ``rtems_clock_get_monotonic_timeval()``
       - ``rtems_clock_get_realtime()``
       - ``rtems_clock_get_realtime_bintime()``
       - ``rtems_clock_get_realtime_coarse()``
       - ``rtems_clock_get_realtime_coarse_bintime()``
       - ``rtems_clock_get_realtime_coarse_timeval()``
       - ``rtems_clock_get_realtime_timeval()``
       - ``rtems_clock_get_seconds_since_epoch()``
       - ``rtems_clock_get_tod_timeval()``
       - ``rtems_clock_get_uptime_nanoseconds()``
       - ``rtems_clock_get_uptime_seconds()``
       - ``rtems_clock_get_uptime_timeval()``
       - ``rtems_clock_tick()``
       - ``rtems_clock_tick_before()``
       - ``rtems_clock_tick_later()``
       - ``rtems_clock_tick_later_usec()``
       - ...

     + The :term:`ICD` contains interface specifications for the following
       components despite these are not in the |SP| and without providing a
       rational for it:

        - ``attr``
        - ``basedefs``
        - ``cache``
        - ``config``
        - ``cpuuse``
        - ``dpmem``
        - ``io``
        - ``mode``
        - ``mp``
        - ``option``
        - ``region``
        - ``signal``
        - ``status``
        - ``support``
        - ``type``
        - ``score``

    This is relevant as |SP| chapter *3. Space Profile Definition*
    explicitly states:

        *Anything not mentioned here is excluded from the space profile.*

    Moreover, section *4.5.2 Excluded* of the |SP|, explicitly excludes

      - IO Manager
      - Signal Manager
      - Region Manager
      - Dual Ported Memory Manager

    **Conclusion:** Request for waiver RfW-QDP-03 has been submitted
    (waivers are listed in the |SCF| ${/pkg/deployment/doc-package-manual:/cite}, see also `Issue #662`_).

.. _`Issue #662`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/662

.. Point 4 by EDISOFT

5.  "Producing a detailed design is feasible" because the detailed
    design has already been produced.

6.  "Operations and maintenance are feasible" because :term:`RTEMS`
    is in operation and maintained since decades.

7.  Not applicable.
    According to |SRS| ${doc-ts-srs:/cite} sections *5.2 Performance requirements*
    till *5.16 Adaptation and installation requirements* there are no safety
    nor other critical requirements.
    Moreover, the interface requirements have been derived from the
    existing software (see for example section *6.5.21 Specify Timer
    Manager* in the ${/ref/tn/qt-109-r6:/cite-long}). Hence, this point is not applicable.

8.  Not applicable.
    Without a |RB|, the proper sequence of events, inputs,
    outputs, interfaces, logic flow, allocation of timing and
    sizing budgets, and error handling are not available as input to
    the architecture. It should be mentioned that decades of practical
    use of :term:`RTEMS` are proof that implementation and architecture
    meet the needs of users and do properly realize interfaces, timing,
    data and logic flows.

9.  Not applicable. Because :term:`RTEMS` has not been designed "top-down"
    there are no "high level" components. The components on architecture level
    are the same as those on detailed design level.

.. _DynamicFeatures:

10. "Dynamic features" are provided and real‐time choices
    are justified.

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2021-09-22 (a preceding review 2021-02-02/05 let to findings
in `Issue #663`_)

**Input Items:**

  * |E40| ${/ref/ecss/q-st-40c-r1:/cite}, clause 5.8.3.3a
  * ${ref-ddf-sdd:/cite-long}

**Compliant:** Yes

    "Dynamic features (tasks definition and priorities,
    synchronization mechanisms, shared resources management)"
    are described in the |SDD|, for example in sections *Task Manager*,
    *Task Priority*, *Semaphore Manager* and *I/O Manager*.

    Real‐time and design choices are justified, for example
    in chapter *RTEMS Overview* of the :term:`SDD`.

11. Not applicable. This clause would only be relevant for an application
    with real-time requirements in the |RB|.

.. _ArchitecturalDesignBehavioralModelChecking:

Architectural Design Behavioral Model Checking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A system model is not provided by the QDP.  See also section *No Logical and
Computational Model* of the ${/ref/tn/qt-109-r6:/cite-long}.

.. _VerificationOfSoftwareDocumentationPDR:

Verification of Software Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

No verification activities related to the software documentation of RTEMS were
carried out at the ${/glossary/pdr:/term}.  For software verification
activities, see sections :ref:`VerificationSwDocs_CDR` and
:ref:`VerificationSwDocs_AR`.

.. _OthersSpecificInspectionsAnalysesOrReviewOfDesignReportsPDR:

Others Specific Inspections, Analyses, or Review of Design Reports
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are no other specific inspections, analyses, or review of design reports.

.. _OthersSpecificVerificationRelatedToRAMSRequirementsPDR:

Others Specific Verification Related to RAMS Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There was no specific verification done related to ${/glossary/rams:/term}
requirements at the ${/glossary/pdr:/term}, see also
:ref:`OtherSpecificVerificationRAMS_CDR`.

Software Design and Implementation Engineering Process Verification (for CDR)
=============================================================================

.. _Traceability:

Traceability
------------

.. _SoftwareDetailedDesignToSoftwareArchitecturalDesign:

Software Detailed Design to Software Architectural Design
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Both architecture and design components are documented using Doxygen groups
which form a hierarchy.  The higher level groups define the software
architecture.  Some Doxygen groups are defined by specification items to
associate requirements with architecture and design components.  See also the
${ref-ddf-sdd:/cite-long}.

.. _SoftwareDesignComponentsToSourceCode:

Software Design Components to Source Code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The table below lists for each software design component the associated source
code files.

${.:/traceability-design-to-code}

.. _SourceCodeToSoftwareDesignComponents:

Source Code to Software Design Components
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The table below lists for each source code file the associated software design
components.

${.:/traceability-code-to-design}

.. _Software_unit_test:

Software Unit Test to Requirements, Design
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A traceability from software unit tests to requirements and the software design
is not provided.  For a justification see the
`Introduction <${.:/component/documentation-directory}/djf/suitp/introduction.html>`_
of the |SUITP| ${doc-djf-suitp:/cite} and the *On Demand Unit and Integration
Testing* section of the ${/ref/tn/qt-109-r6:/cite-long}.

Feasibility
-----------

.. _SoftwareDetailedDesignVerification:

Software Detailed Design Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The verification activities related to the software detailed design are
mandated by clause 5.8.3.4.a of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2021-02-04/05,
2021-09-22/29 (Update; one finding was resolved because
`Issue #663`_ was closed),
2021-10-29 (Update; three finding were resolved because
they where documented in the SDD or disappeared from RTEMS),
2021-11-19 (add waiver)

**Input Item:**

* ${/ref/ecss/q-st-40c-r1:/cite-long}, clause 5.8.3.4a

* ${doc-ts-icd:/cite-long}

* ${ref-ddf-sdd:/cite-long}

* ${doc-ts-srs:/cite-long}

* ${/ref/tn/rtems-space-profile-r6:/cite-long}

**Compliant:** OK

1.  It cannot be evaluated whether the "detailed design is externally
    consistent with the architecture".

    **Verification:**

      1. Check whether all components described in the
         architecture appear in the detailed design (:term:`SDD`) and that the
         interfaces or interactions defined in the architecture match the ones
         in the detailed design at least for random samples.

      2. Check whether all components described in the ${/ref/tn/rtems-space-profile-r6:/cite-long}
         appear in the detail design.

      3. Check whether all functions and ``#defines`` mentioned in section 3
         of the ${/ref/tn/rtems-space-profile-r6:/cite-long} appear in the detailed design.

    **Notes:**

      + The component named *Scheduler Manager* in the |SP| seems to be
        merged in the component named *Task Manager* in the :term:`SDD`.
        All *Scheduler Manager* functions are listed in the *Task Manager*
        section in the :term:`SDD`. All *Scheduler Manager* macros are described
        in different places in the  :term:`SDD`.

    **Finding:**

      + The function ``rtems_rate_monotonic_deadline()`` is required by the
        |SP| but not mentioned in the |SDD|.

    **Conclusion:** Request for waiver RfW-QDP-01 has been submitted
    (waivers are listed in the |SCF| ${/pkg/deployment/doc-package-manual:/cite}, see also `Issue #664`_).

.. _`Issue #664`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/664

2.  The term :term:`software unit` is interpreted as functions
    and macros as no other "units" exist between them and the components.
    Since the |SDD| is generated by Doxygen from the original
    code, functions and components must necessarily be consistent.

3.  That the traceability between the software architecture and the software
    detailed design is complete is ensured by using Doxygen to document the
    architecture and the detailed design, see the ${ref-ddf-sdd:/cite-long}.  Both
    architecture and design components are documented using Doxygen groups
    which form a hierarchy.  Some Doxygen groups are defined by specification
    items to associate requirements with architecture and design components,
    see :ref:`Traceability`.

4.  The project defined the term :term:`software unit` to be a
    :term:`software component`. Consequently, |E40|
    clause 5.8.3.4a point 4 becomes a meaningless tautology.

    Yet, it should be pointed out that table *Code to design traceability*
    in section :ref:`Traceability` maps all
    ${/glossary/softwareunit:plural} to design components.
    Software units neither mapped nor justified
    will give raise to findings in that section.

5.  :term:`RTEMS` has existing test suites with about 600 to 700 tests.
    Most of these tests exist since long before the start of this
    qualification project and cover most of :term:`RTEMS` core code.
    Hence testing is for sure feasible.

      a) |SRS| ${doc-ts-srs:/cite} section *5.2 Performance requirements* states:
         *There are no performance requirements*. Performance measurements
         and benchmarks are planned to be done only using the official
         externally visible API.

      b) There are no computational invariants or temporal properties
         mentioned in the design. All tests were so far possible without
         them and there is no test envisioned which require them.

      c) The design neither :term:`RTEMS` have provisions for fault injection.
         Tests using fault injection were never necessary nor are such tests
         planned. The errors typically appearing in operating systems
         can be triggered through cunning :term:`ABI` usage.
         Moreover, fault injection would mean to add code which is never
         used during normal operation -- which is not desirable -- and may
         open access to features which should not be accessible
         in critical software.

6.  Operations and maintenance are feasible because :term:`RTEMS`
    is in operation and is maintained since decades.

7.  Interfaces are described in the :term:`ICD`. Requirements towards the
    interfaces are also described in the :term:`ICD` while functional software
    requirements are described in the :term:`SRS`.

    **Verification:**

      Ensure that :term:`SDD` implements :term:`ICD` and :term:`SRS`
      utilizing random sample checks.

    **Compliant:** OK

    **Comment:** Review 2021-10-29 found that :term:`SDD`, :term:`ICD` and
    :term:`SRS` are complete with minor issues (e.g `Issue #645`_,
    `Issue #664`_) which are already tracked else where. The :term:`SDD`
    describes the functions and macros which appear in the :term:`ICD`
    and :term:`SRS`.

    According to |SRS| ${doc-ts-srs:/cite} sections *5.2 Performance requirements*
    till *5.16 Adaptation and installation requirements* there are no safety
    nor other critical requirements.

8.  Not applicable.
    Without a |RB|, the proper sequence of events, inputs,
    outputs, interfaces, logic flow, allocation of timing and
    sizing budgets, and error handling are not available as input to
    the architecture. It should be mentioned that decades of practical
    use of :term:`RTEMS` are proof that implementation and architecture
    meet the needs of users and do properly realize interfaces, timing,
    data and logic flows.

9.  Not applicable because there is no logical model
    (see ${/ref/tn/qt-109-r6:/cite-long} section
    *9.4.7 No Logical and Computational Model*).

10. The :term:`SDD` contains elements which are not
    mention in the architecture, :term:`ICD` nor :term:`SRS`
    like ``Barrier Handler``,  ``Basic Types``, ``Bootcard``, and simular
    implementation components. These are apparently needed to realize the
    components and functions defined in the :term:`ICD` and :term:`SRS`.

    No hierarchical breakdown for such components is provided.

    Yet, :term:`RTEMS` is an existing software and the pre-qualified code
    archives 100% code coverage -- that is, there are no unnecessary elements
    in the code. Moreover, since the Doxygen output is used as |SDD|, this
    "design" contains an explosion of details which would not be
    present in a hand written design.

    Under these circumstances, a hand produced break down from
    :term:`ICD` and :term:`SRS` components to each detail in the Doxygen
    output would be an unnecessary exercise
    as there is no apparent use for such a break down.

11. See section *Verification of the Software Architectural and Interface
    Design* :ref:`point 10 <DynamicFeatures>` above. Pre-qualified
    :term:`RTEMS` is small enough to discuss all "Dynamic features" and
    "real‐time choice" once in the architecture.

12. Not applicable. This clause would only be relevant for an application
    with real-time requirements in the |RB|.

.. _DesignModelChecking:

Design Model Checking
^^^^^^^^^^^^^^^^^^^^^

A system model is not provided by the QDP.  See also section *No Logical and
Computational Model* of the ${/ref/tn/qt-109-r6:/cite-long}.

.. _SoftwareCodeVerification:

Software Code Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^

The verification activities related to the software code are mandated by clause
5.8.3.5.a of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2020-12-12 -- 2020-12-22,
2021-05-27 (Update of the tables below),
2021-09-29 (Update of the tables below), 2021-11-19 (add waiver)

**Input Item:**

* Source code and binaries from pre-:term:`QR` 1 :term:`QDP`

  commit ``3723ffe79eb5cfaef247f059f4a350786406b80a``

* ${doc-ts-icd:/cite-long}

* ${ref-ddf-sdd:/cite-long}

* ${/ref/tn/rtems-space-profile-r6:/cite-long} from repository ``rtems-smp-qualification-qual``

  at ``8f80d0f63824603dd758729570f506d399b8b6ca``

* ${doc-ts-srs:/cite-long}

**Compliant:** Yes

1. Is the code externally consistent with requirements and design?

  **Verification:**

  * Extract the name of visible, public and defined linker symbols from the
    :term:`RTEMS` pre-qualified libraries. All functions listed in the |SP|
    chapter *3. Space Profile Definition* must be among them.
  * Visible, public and defined linker symbols in the
    :term:`RTEMS` pre-qualified libraries should only contain functions
    listed in the |SP|.

  **Findings:**

    + There are functions which are listed in the |SP| but which
      *are not* in the pre-qualified :term:`RTEMS` libraries.
    + There are functions in the pre-qualified :term:`RTEMS` libraries
      which *are not* listed in the |SP|.

  **Conclusion:** Request for waiver RfW-QDP-03 has been submitted
  waivers are listed in the |SCF| ${/pkg/deployment/doc-package-manual:/cite}, see also `Issue #665`_).

.. The code is externally consistent with the requirements and design of the software item;
   -> Check SRS and SDD for one component that is already finished.

.. _`Issue #665`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/665

  The following tables have been produced from these sources:

    + the |SP| source file ``modules/esa-main/docs/survey/profile.rst``
    + ``<path>/gr712rc-qual-only/lib/librtemscpu.a``
    + ``<path>/gr712rc-qual-only/lib/librtemsbsp.a``
    + running the ``gcc`` preprocessor on
      ``<path>/gr712rc-qual-only/lib/include/rtems.h``
    + include files below

        - ``<path>/gr712rc-qual-only/lib/include``
        - ``<path>/include``

      reachable through an ``#include <rtems.h>``
    + where ``<path>`` is always ``rtems-6-sparc-gr712rc-smp-2/sparc-rtems6``
      in the :term:`QDP`
    + only functions and linker symbols are considered where the name does
      not begin with an
      underscore and which are defined in a *text* section of the binaries.

.. list-table:: Space Profile Functions not in the pre-qualified RTEMS library
   :widths: 15 10
   :header-rows: 1

   * - Function
     - Explanation
   * - posix_memalign()
     - ?
   * - rtems_build_name()
     - #define in rtems/rtems/object.h:311
   * - rtems_clock_get_ticks_per_second()
     - #define in rtems/rtems/clock.h:298
   * - rtems_clock_get_ticks_since_boot()
     - #define in rtems/rtems/clock.h:340
   * - rtems_fatal()
     - inline function in rtems/fatal.h:153
   * - rtems_interrupt_local_disable()
     - #define in rtems/rtems/intr.h:452
   * - rtems_interrupt_local_enable()
     - #define in rtems/rtems/intr.h:493
   * - rtems_interrupt_lock_acquire()
     - #define in rtems/rtems/intr.h:631
   * - rtems_interrupt_lock_destroy()
     - #define in rtems/rtems/intr.h:574
   * - rtems_interrupt_lock_initialize()
     - #define in rtems/rtems/intr.h:542
   * - rtems_interrupt_lock_release()
     - #define in rtems/rtems/intr.h:674
   * - rtems_malloc()
     - ?
   * - rtems_message_queue_build()
     - ?
   * - rtems_rate_monotonic_deadline()
     - ?
   * - rtems_scheduler_get_processor()
     - #define in rtems/rtems/tasks.h:729
   * - rtems_scheduler_get_processor_maximum()
     - #define in rtems/rtems/tasks.h:763
   * - rtems_task_build()
     - ?

Note: The functions listed in the above table are all declared or defined
in a header file -- even those which do not appear in the libraries.
Exceptions are the function ``rtems_rate_monotonic_deadline()`` and the
POSIX functions.

.. list-table:: Functions appearing in the pre-qualified RTEMS library but not in the space profile
   :widths: 15 10
   :header-rows: 1

   * - Function
     - Explanation
   * - Clock_isr()
     - ?
   * - apbuart_inbyte_nonblocking()
     - ?
   * - apbuart_outbyte_polled()
     - ?
   * - apbuart_outbyte_wait()
     - ?
   * - boot_card()
     - ?
   * - bsp_fatal_extension()
     - ?
   * - bsp_idle_thread()
     - ?
   * - bsp_interrupt_check_and_lock()
     - ?
   * - bsp_interrupt_clear()
     - ?
   * - bsp_interrupt_entry_find()
     - ?
   * - bsp_interrupt_entry_remove()
     - ?
   * - bsp_interrupt_facility_initialize()
     - ?
   * - bsp_interrupt_get_affinity()
     - ?
   * - bsp_interrupt_get_attributes()
     - ?
   * - bsp_interrupt_handler_default()
     - ?
   * - bsp_interrupt_initialize()
     - ?
   * - bsp_interrupt_is_pending()
     - ?
   * - bsp_interrupt_is_valid_vector()
     - ?
   * - bsp_interrupt_lock()
     - ?
   * - bsp_interrupt_raise()
     - ?
   * - bsp_interrupt_raise_on()
     - ?
   * - bsp_interrupt_set_affinity()
     - ?
   * - bsp_interrupt_spurious()
     - ?
   * - bsp_interrupt_unlock()
     - ?
   * - bsp_interrupt_vector_disable()
     - ?
   * - bsp_interrupt_vector_enable()
     - ?
   * - bsp_interrupt_vector_is_enabled()
     - ?
   * - bsp_start()
     - ?
   * - bsp_start_on_secondary_processor()
     - ?
   * - clock_nanosleep()
     - ?
   * - flsl()
     - ?
   * - getchark()
     - ?
   * - leon3_ext_irq_init()
     - ?
   * - leon3_power_down_loop()
     - ?
   * - pthread_self()
     - ?
   * - rtems_barrier_delete()
     - ?
   * - rtems_cache_disable_data()
     - ?
   * - rtems_cache_disable_instruction()
     - ?
   * - rtems_cache_enable_data()
     - ?
   * - rtems_cache_enable_instruction()
     - ?
   * - rtems_cache_flush_entire_data()
     - ?
   * - rtems_cache_flush_multiple_data_lines()
     - ?
   * - rtems_cache_freeze_data()
     - ?
   * - rtems_cache_freeze_instruction()
     - ?
   * - rtems_cache_get_data_cache_size()
     - ?
   * - rtems_cache_get_data_line_size()
     - ?
   * - rtems_cache_get_instruction_cache_size()
     - ?
   * - rtems_cache_get_instruction_line_size()
     - ?
   * - rtems_cache_get_maximal_line_size()
     - ?
   * - rtems_cache_instruction_sync_after_code_change()
     - ?
   * - rtems_cache_invalidate_entire_data()
     - ?
   * - rtems_cache_invalidate_entire_instruction()
     - ?
   * - rtems_cache_invalidate_multiple_data_lines()
     - ?
   * - rtems_cache_invalidate_multiple_instruction_lines()
     - ?
   * - rtems_cache_unfreeze_data()
     - ?
   * - rtems_cache_unfreeze_instruction()
     - ?
   * - rtems_clock_get_tod()
     - ?
   * - rtems_clock_set()
     - ?
   * - rtems_configuration_get_maximum_barriers()
     - ?
   * - rtems_configuration_get_maximum_extensions()
     - ?
   * - rtems_configuration_get_maximum_message_queues()
     - ?
   * - rtems_configuration_get_maximum_partitions()
     - ?
   * - rtems_configuration_get_maximum_periods()
     - ?
   * - rtems_configuration_get_maximum_semaphores()
     - ?
   * - rtems_configuration_get_maximum_tasks()
     - ?
   * - rtems_configuration_get_maximum_timers()
     - ?
   * - rtems_extension_delete()
     - ?
   * - rtems_initialize_executive()
     - ?
   * - rtems_interrupt_clear()
     - ?
   * - rtems_interrupt_entry_install()
     - ?
   * - rtems_interrupt_entry_remove()
     - ?
   * - rtems_interrupt_get_affinity()
     - ?
   * - rtems_interrupt_get_attributes()
     - ?
   * - rtems_interrupt_handler_iterate()
     - ?
   * - rtems_interrupt_is_pending()
     - ?
   * - rtems_interrupt_raise()
     - ?
   * - rtems_interrupt_raise_on()
     - ?
   * - rtems_interrupt_set_affinity()
     - ?
   * - rtems_interrupt_vector_disable()
     - ?
   * - rtems_interrupt_vector_enable()
     - ?
   * - rtems_interrupt_vector_is_enabled()
     - ?
   * - rtems_message_queue_construct()
     - ?
   * - rtems_message_queue_delete()
     - ?
   * - rtems_partition_delete()
     - ?
   * - rtems_put_char()
     - ?
   * - rtems_putc()
     - ?
   * - rtems_rate_monotonic_delete()
     - ?
   * - rtems_scheduler_get_maximum_priority()
     - ?
   * - rtems_semaphore_delete()
     - ?
   * - rtems_semaphore_flush()
     - ?
   * - rtems_signal_catch()
     - ?
   * - rtems_signal_send()
     - ?
   * - rtems_status_text()
     - ?
   * - rtems_task_construct()
     - ?
   * - rtems_task_create()
     - ?
   * - rtems_task_delete()
     - ?
   * - rtems_task_exit()
     - ?
   * - rtems_task_mode()
     - ?
   * - rtems_task_wake_when()
     - ?
   * - rtems_timer_delete()
     - ?
   * - rtems_timer_fire_when()
     - ?
   * - rtems_timer_server_fire_when()
     - ?
   * - sparc_syscall_exit()
     - ?
   * - syscall()
     - ?
   * - syscall_irqdis()
     - ?
   * - syscall_irqdis_fp()
     - ?
   * - syscall_irqen()
     - ?
   * - window_flush_trap_handler()
     - ?
   * - window_overflow_trap_handler()
     - ?
   * - window_underflow_trap_handler()
     - ?

Note: At least most of the ``rtems_*``-functions listed in the above table
are all declared or defined in a pre-qualified only header file. That is,
the compiler will compile application code with these functions and the
linker will even link such code.

2. All software units are internally consistent. Otherwise the compiler would not
   compile their code or the linker would not link them. Any unused functions
   would be detected by code coverage analysis (see  section :ref:`Coverage`).

3. For the verification that the ${/glossary/rtems:/term} source code is
   traceable to design and requirements, testable, correct, and in conformity
   to software requirements and coding standards, see this report and the
   SPAMR.

4. The project defined the term :term:`software unit` to be a
   C function or assembler code. Since in C any executable code
   is either inside of a C function or is assembler code, all code
   is inside a unit. The case |E40| clause 5.8.3.5a point 4 addresses
   can therefore not occur in :term:`RTEMS` and hence there is no
   need to justify such code.

5. The code implements proper event sequences, consistent interfaces,
   correct data and control flow and completeness. Otherwise the verification
   tests would fail.

   It should be noted, that :term:`RTEMS` as small operating system kernel
   has only to cope with rather simple sequences of events and that also
   the data and control flow of the managers is less complex compared to
   typical applications. Moreover, :term:`RTEMS` has no interface to end users.
   Its only interfaces are :term:`ABI` functions and interfaces to hardware
   devices.

   The verification tests check all error conditions so that the error
   handling is completely covered.

   **Reviewer:** Frank Kühndel (embedded brains)

   **Review Date:** 2021-11-24 (update), 2021-10-29 (update)

   Note previous reviews 2020-12-12 -- 22 and 2021-05-28 led to findings
   `Issue #668`_ (closed) and `Issue #704`_ (closed). Note also that certain
   error conditions listed in the |RCA| ${/ref/rtems/c-user:/cite} do not exist in
   pre-qualified :term:`RTEMS`, especially those related to
   :term:`remote` ${/glossary/node:plural}.

   **Input Items:**

     * |RCA| ${/ref/rtems/c-user:/cite}
     * |SRS| ${doc-ts-srs:/cite}
     * :term:`QDP` from the :term:`CDR`, the validation test files:

         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tc-part-create.c``
         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tc-part-ident.c``
         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tr-object-ident.h``
         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tr-object-ident.c``
         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tc-part-get.c``
         + ``rtems/6/sparc/gr712rc/smp/src/rtems-qual-only/testsuites/validation/tc-part-return.c``

     * pre-:term:`QR` 1, commit ``3723ffe79eb5cfaef247f059f4a350786406b80a``
       the validation test files:

         + ``rtems-6-sparc-gr712rc-smp-2/src/rtems/testsuites/validation/tc-sem-obtain.c``
         + ``rtems-6-sparc-gr712rc-smp-2/src/rtems/testsuites/validation/tc-sem-delete.c``
         + ``rtems-6-sparc-gr712rc-smp-2/src/rtems/testsuites/validation/tc-sem-set-priority.c``
         + ``rtems-6-sparc-gr712rc-smp-2/src/rtems/testsuites/validation/tc-sem-create.c``
         + ``rtems-6-sparc-gr712rc-smp-2/src/rtems/testsuites/validation/tc-sem-release.c``

     * from the ``rtems-central`` git with hash
       ``65bc2ff136e61833c73dd3f2ba3e6bdc477df59e`` the specification items:

         + ``spec/rtems/part/req/create.yml``
         + ``spec/rtems/part/req/ident.yml``
         + ``spec/rtems/part/val/ident.yml``
         + ``spec/rtems/part/val/part.yml``
         + ``spec/rtems/part/req/delete.yml``
         + ``spec/rtems/part/req/get_buffer.yml``
         + ``spec/rtems/part/req/return_buffer.yml``

     * from the ``rtems-smp-qualification-qual`` git with hash
       ``ae9028c1845b49af806a36920c4affcaef028104`` the specification items:

         + ``spec/rtems/sem/req/obtain.yml``
         + ``spec/rtems/sem/req/flush.yml``
         + ``spec/score/sem/req/seize-try.yml``
         + ``modules/rtems/testsuites/validation/tx-thread-queue.c``

     * from the ``rtems-smp-qualification-qual`` git with hash
       ``c2439ce318b26070a67dcb7e9c879a269f7f5ede`` the specification items:

         + ``spec/rtems/sem/req/timeout.yml``
         + ``spec/score/tq/req/timeout.yml``
         + ``spec/score/tq/req/timeout-mrsp.yml``
         + ``spec/score/tq/req/timeout-priority-inherit.yml``
         + ``cpukit/include/rtems/score/status.h``
         + ``spec/rtems/sem/req/obtain.yml``
         + ``spec/score/mtx/req/seize-try.yml``

   **Compliant:** Yes

   **Verification:** As random sample for 2020-12-12 -- 22 the partition
   manager test code has been selected for review and 2021-05-28 the semaphore
   manager:

     * For all functions: The specification item mentions and realizes
       all error conditions listed in the |RCA|.
     * The error conditions are implemented and tested in the verification
       test.
     * The |SRS|, which is generated from specification
       items, lists all error conditions with description (compared to the
       |RCA|).

    **Comments:**

      * The :term:`SRS` contains a requirement for
        ``spec:/rtems/sem/req/delete`` despite directive
        ``rtems_semaphore_delete()`` is not in the |SP|.
      * ``rtems_semaphore_obtain()`` error condition
        ``RTEMS_NOT_DEFINED`` is specified with the
        ``rtems_semaphore_set_priority()`` directive.
      * ``rtems_semaphore_obtain()`` error condition
        ``RTEMS_OBJECT_WAS_DELETED`` is specified with the
        ``rtems_semaphore_delete()`` directive.
      * ``rtems_semaphore_obtain()`` error condition
        ``RTEMS_UNSATISFIED`` is specified with the
        ``rtems_semaphore_flush()`` directive and
        in ``spec/score/sem/req/seize-try.yml``.
      * Specification items like ``spec/rtems/sem/req/timeout.yml``
        delegate part of their work to other specification items
        such as ``spec/score/tq/req/timeout.yml``,
        ``spec/score/tq/req/timeout-mrsp.yml`` or
        ``spec/score/tq/req/timeout-priority-inherit.yml``. These may in turn
        employ further specification items. This can be imagined like a
        subroutine call. ``spec/rtems/sem/req/timeout.yml`` may test some
        requirements itself, to specify and test a bunch of other requirements
        it calls ``spec/score/tq/req/timeout-mrsp``.yml``,
        ``spec/score/tq/req/timeout-mrsp.yml``, and
        ``spec/score/tq/req/timeout-priority-inherit.yml``.
      * :term:`RTEMS` uses internally other status #defines which are
        mixed results of :term:`RTEMS` Classic :term:`API` and :term:`POSIX`
        :term:`API` together. The mapping between them can be found in file
        ``cpukit/include/rtems/score/status.h``. Relevant here are:

          + ``RTEMS_TIMEOUT == STATUS_TIMEOUT``
          + ``RTEMS_INCORRECT_STATE == STATUS_DEADLOCK`` or
            ``STATUS_INCORRECT_STATE``
          + ``RTEMS_INVALID_PRIORITY == STATUS_INVALID_PRIORITY`` or
            ``STATUS_MUTEX_CEILING_VIOLATED``

      * ``spec/rtems/sem/req/timeout.yml`` tests error condition
        ``RTEMS_TIMEOUT`` by setting
        ``ctx->tq_ctx.enqueue = TQEnqueueClassicSem`` whereby function
        ``TQEnqueueClassicSem`` calls ``rtems_semaphore_obtain()``.
        Then it employs ``spec/score/tq/req/timeout.yml``,
        ``spec/score/tq/req/timeout-mrsp.yml`` or
        ``spec/score/tq/req/timeout-priority-inherit.yml`` which test
        for return status ``STATUS_TIMEOUT`` (among other things).
      * For an example where ``RTEMS_INCORRECT_STATE`` is tested see
        ``spec/rtems/sem/req/obtain.yml`` which employs
        ``spec/score/mtx/req/seize-try.yml`` at this code:
        ``{/score/mtx/req/seize-try:/test-run}( &ctx->tq_mtx_ctx )``.
        ``spec/score/mtx/req/seize-try.yml`` then tests for
        ``STATUS_DEADLOCK`` (among other things).
      * For an example where ``RTEMS_INVALID_PRIORITY`` is tested see
        ``spec/rtems/sem/req/obtain.yml`` which employs
        ``spec/score/mtx/req/seize-try.yml`` at this code:
        ``{/score/mtx/req/seize-try:/test-run}( &ctx->tq_mtx_ctx )``.
        ``spec/score/mtx/req/seize-try.yml`` then tests for
        ``STATUS_MUTEX_CEILING_VIOLATED``.
      * The ``rtems_semaphore_flush()`` directive is not in the |SP|
        but is tested.
      * ``rtems_semaphore_set_priority()`` error condition
        ``RTEMS_ILLEGAL_ON_REMOTE_OBJECT`` cannot occur as
        pre-qualified :term:`RTEMS` does not support :term:`remote` objects.
      * Review on 2021-10-29 found no T O D Os in the :term:`SRS` anymore.

.. _`Issue #668`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/668

.. _`Issue #704`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/704

6. Not applicable because

       + :term:`SRS` section 4.12 *Safety requirements* states:
         *There are no safety requirements*.
       + :term:`SRS` section 4.7 *Security and privacy requirements* states:
         *There are no security or privacy requirements*.
       + :term:`SRS` and :term:`ICD` contain no criticality requirements.
         Moreover, a :term:`FMECA` did not lead to criticality requirements
         (see section :ref:`OtherSpecificVerificationRAMS_CDR`).

7. Run-time errors of :term:`RTEMS` are :term:`ABI` calls with illegal values
   or in illegal states. All these error conditions are detected and an error
   code is returned to the caller as specified in the :term:`SRS` and |RCA|.

8. Pre-qualified :term:`RTEMS` does not use dynamically allocated memory.
   Pre-qualified :term:`RTEMS` must be configured with a fixed maximum number of
   elements for each resource (such as threads or semaphores) at compile time.

   Normal :term:`RTEMS` provides the option to dynamically allocate
   resources but this option as been turned off for pre-qualified :term:`RTEMS`.
   Consequently, there cannot be any memory leak.

9. Numerical protection mechanisms are not applicable, because no
   floating-point operations are used in the pre-qualified
   ${/glossary/rtems:/term} source code.

.. Point 4 by EDISOFT

.. _StructuralCodeCoverageAchievementCDR:

Structural Code Coverage Achievement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: ../include/coverage-summary.rst

.. _DeactivatedCodeVerification:

Deactivated Code Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The pre-qualified feature set of RTEMS contains two blocks of
${/glossary/deactivatedcode:/term}.  The code is covered by unit tests.

Firstly, the directives to get the configured maximum of Classic API objects
support the unlimited objects configuration.  This configuration option is not
available in the pre-qualified feature set.  Its use would lead to an
unresolved reference linker error.  The deactivated code is tested by unit
tests specified by ${/rtems/config/unit/config:/spec}.

Secondly, the message queue implementation supports arbitrary message
priorities.  The message priority is expressed by an integer value.  The
Classic API does not support arbitrary message priorities.  The arbitrary
message priorities are supported by the ${/glossary/posix:/term} API which are
not included in the pre-qualified feature set.  Using a POSIX message queue
would lead to unresolved reference linker errors.  The deactivated code is
tested by unit tests specified by ${/score/msgq/unit/msgq:/spec}.

..  :ref:`ECSS-Q-ST-80C Rev.1 6.2.6.5 <DT-ECSS-Q-ST-80C-R1-QDP-125>`
    We wrote in the SPAMR plan:
    There is no deactivated code in RTEMS, since the pre-qualified RTEMS
    will achieve 100% code coverage.

.. _ConfigurableCodeVerification:

Configurable Code Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

RTEMS code is configured at two different time points.  Firstly, the RTEMS
build is configured through options of the build system.  This configuration is
defined by the QDP configuration and it is immutable for a deployed RTEMS.

Secondly, the deployed RTEMS can be configured according to application
requirements by various
`application configuration options <${.:/component/deployment-directory}/doc/rtems/c-user/config/index.html>`_.
The application-specific configuration is contained in an application-provided
object file which is linked into the application executable.  The application
link process shall ensure that the application-specific configuration is used
instead of the default configuration present in the RTEMS libraries.  All
configuration options supported by the pre-qualified feature set have
associated validation tests.  The RTEMS design includes measures to detect and
report a misconfiguration:

* The application is done through C preprocessor defines.  Some configuration
  errors are detected by the C preprocessor or static assertions.  In this
  case, the compilation process aborts with an error.

* Using features not included in the pre-qualified feature set results in
  unresolved reference linker errors.

* Some configuration errors are detected during system initialization and
  reported as fatal errors.

* Some configuration errors are detected once a directive is used and reported
  through an error status code.

* The application can query the actual value of configuration parameters to
  ensure that the application configuration is as expected.

.. See :ref:`ECSS-Q-ST-80C Rev.1 6.2.6.6 <DT-ECSS-Q-ST-80C-R1-QDP-126>`.

Source Code Robustness Verification
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This verification of source code robustness bases on
|E40| ${/ref/ecss/q-st-40c-r1:/cite}, clause 5.8.3.5f.

The project takes a number of measures to ensure the code does not contain
flaws leading to catastrophic or unexpected behavior:

    * The static analyzer *Coverity* is used by the public :term:`RTEMS`
      project as well as by this :term:`ESA` qualification project.
      It detects typical flaws such as control flow paths which access
      uninitialized variables, dereferencing of ``NULL`` pointers,
      division by zero, automatic type casts with possible unwanted
      effects and other possible run-time errors such as the use of unsafe
      string copy functions or the use of wrong conversion specifiers
      in format strings of the ``printf()`` family of functions..

      The |SPAMR| reports and analyses the issues uncovered by *Coverity*.

    * The static analyzer *CLANG* is used by this :term:`ESA` qualification
      project. It detects the same type of flaws as *Coverity*.
      Since these tools use different methods to detect issues,
      using several distinct tools decreases the likelihood for
      a problem to pass undetected.

      The :term:`SPAMR` reports and analyses the issues uncovered by *CLANG*.

    * The static analyzer *CppCheck* is used by this :term:`ESA` qualification
      project. The same argument applies as for *Coverity* and *CLANG*
      above.

      The :term:`SPAMR` reports and analyses the issues uncovered by *CppCheck*.

    * :term:`RTEMS` most powerful defense against even difficult to spot
      run-time errors such as resource sharing conflicts, concurrency issues,
      program logic flaws, overlooked error conditions or inconsistent
      system states is the review process by which all code is public
      reviewed by the members of the :term:`RTEMS` developer mailing list.

It should also taken into account that :term:`RTEMS` code has passed the
"test of time". :term:`RTEMS` is in use in many commercial, educational and
scientific projects and products since decades. Countless programmers
have seen and worked with this code. Problems have been reported and fixed.

.. hand written content which references to the results
   of the static analyzers which will be provided in the SPAMR
   (:ref:`QDPProposalSPAMR`) and explains relevance of the output of the tools.
   See :ref:`ECSS-E-ST-40C 5.8.3.5f <DT-ECSS-E-ST-40C-QDP-139>`

.. _VerificationofSoftwareUnitTesting:

Verification of Software Unit Testing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The table below lists for each specified unit test suite or unit test case the
associated test code name and the test run status (``P`` for passed, ``F`` for
failed, ``X`` for an expected failed).  For the unit test suite and unit test
case specifications, see the |SUITP| ${doc-djf-suitp:/cite}.

${.:/unit-verification}

The test code itself is not qualified level B. Yet, the test code is
generated from specification items by a code generator and then undergoes
an internal review and a review on the public mailing list before added
as source code to the project and used for verification testing.
All test code is traceable to software units and requirements.
Therefore, it is ensured that the missing qualification does not
affect the outcome of the tests.

.. Marcel from ESA requested such a statement during CDR when discussing #83 and #84:
   "Test code is not qualified level-b. Statement in SVR: Test code is not
   qualified and this does not affect the outcome of the test."

The verification activities related to the software unit testing are mandated
by clause 5.8.3.6 of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

1. Are unit tests consistent with detailed design and requirements?

   Neither the ${ref-ddf-sdd:/cite-long} nor the |SUITP| ${doc-djf-suitp:/cite}
   contain detailed design nor requirements for unit tests.
   The small number of unit tests (not counting validation tests here)
   and their simplicity justify the lack of design and requirements.

2. Are the unit tests are traceable to software requirements, design and code?

   The unit tests are not traceable to software requirements in general, see
   also :ref:`Software_unit_test`.  They are traceable to design and code since
   they are integrated in the RTEMS source code and run by normal RTEMS
   executables.  No third-party frameworks with stubbing capabilities are used
   for the unit tests.

3. Is software integration and testing feasible?

   :term:`RTEMS` is not a new software build from individual units which
   must be integrated in a second step. Instead :term:`RTEMS` exists since
   decades and is an integrated piece of software. Moreover, automated
   regression tests have been used in :term:`RTEMS` long before this
   qualification project started. Consequently, software integration and
   testing was and is feasible.

4. Are operation and maintenance feasible?

   :term:`RTEMS` exists since decades. It and its test suites and test
   utilities is in operation and maintenance since long time.
   Hence, this is certainly feasible.

5. Have all activities defined in clause 5.5.3 been performed?

   **Reviewer:** Frank Kühndel (embedded brains)

   **Review Date:** 2021-09-29 (a preceding review 2021-02-24 opened
   `Issue #669`_)

   **Input Items:**

      * ${ref-ddf-sdd:/cite-long}
      * |RUM| ${/ref/rtems/user:/cite}
      * |RCA| ${/ref/rtems/c-user:/cite}
      * ${/ref/legacy/djf-suitp-r1:/cite-long}
      * |SUITR| part of this :term:`SVR` in chapter :ref:`SoftwareTestReports`
        and following

   **Compliant:** Yes

      * 5.5.3.1 a.1. Develop and document the coding of each software unit

        :term:`RTEMS` is existing software. It has been implemented
        long time ago. Documentation of the the coding is not possible.

      * 5.5.3.1 a.2.  Develop and document the build procedures to compile
        and link software units

        The instructions how to compile and link :term:`RTEMS` with all
        its software units can be found in the |RUM| ${/ref/rtems/user:/cite}.

      * 5.5.3.2 a. Develop and document the test procedures and data for
        testing each software unit

        That each :term:`software unit` is tested is ensured by the
        100% code coverage goal.

        The design of each test is documented in the :term:`SDD` – for
        example section *8.206 spec:/rtems/part/req/create*. The design
        of the test framework is also documented in section *8.113
        RTEMS Test Framework Implementation*.

      * 5.5.3.2 b. Test each software unit ensuring that it satisfies its
        requirements and document the test results.

        Validation tests are traced to requirements in section
        :ref:`Verification_of_software_validation`.
        Test results are reported in the same section.

      * 5.5.3.2 c.1. The unit test shall exercise
        code using boundaries at n‐1, n, n+1 including looping
        instructions, while, for and tests that use comparisons

        **Input Items:** Unit test code

          + ``src/rtems-qual-only/testsuites/unit/tc-score-msgq.c`` and
          + ``src/rtems/testsuites/unit/tc-score-kern-tc.c``

        from pre-:term:`QR`\#2 |QDP| build from commit

        ``9f6bee80d4b1f0729bc290c3d69e411f489b9386``

        The source code under test contains no boundaries. All possible cases in
        comparisons are tested. Exceptions are cases which cannot
        be exercises by unit tests due to the lack of support for mocks
        (such as involving variables ``ogen`` or ``gen``).

      * 5.5.3.2 c.2. The unit test shall exercise all the messages and
        error cases defined in the design document

        :term:`RTEMS` is an operating system and as such does not output
        messages.
        The :term:`SDD` is generated by the Doxygen tool. It does not list
        error cases if these are not accidentally mentioned in a comment.
        Hence the errors defined in the :term:`API` manual are used.

        The validation tests call all interface functions with such
        arguments and in such states as to provoke all errors defined
        in the |RCA| ${/ref/rtems/c-user:/cite}.

      * 5.5.3.2 c.3. The unit test shall exercise the access of all
        global variables as specified in the design document

        The :term:`SDD` is generated by the Doxygen tool. It lists much
        more variables and details as would hand written design documents
        do. Instead the observable system states as mentioned in the
        :term:`API` manual are tested.

        The validation test exercise all manager states and system states
        defined in the |RCA| ${/ref/rtems/c-user:/cite}.

      * 5.5.3.2 c.4. The unit test shall exercise out of range values for
        input data, including values that can cause erroneous results in
        mathematical functions

        The validation test call all interface functions with
        arguments which provoke all errors defined in the |RCA|
        ${/ref/rtems/c-user:/cite}. This document already considers all
        possible out of range values for input data and defines
        the expected results in such cases. As the points c.3. and
        c.4. above state, these error cases are tested.

      * 5.5.3.2 c.5. The unit test shall exercise the software at
        the limits of its requirements (stress testing).

        Not applicable because pre-qualified :term:`RTEMS` is no application
        and has no requirements baseline, see :ref:`NoRB`.

.. _`Issue #669`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/669

6. Are test results conform to expected results?

   Yes. The test results are defined in the |SUITP|. The tests check for these
   results and end with *passed* instead of `failure`. See the
   *Software Unit and Integration Test Report* sections
   in chapter :ref:`SoftwareTestReports` and following (the phrase
   "``execution-result passed``" in the *Test Suite* sections).

7. Is normal termination (that is, the test end criteria defined in the unit
   test plan) achieved?

   Yes. The tests terminate normal. See the
   *Software Unit and Integration Test Report* sections
   in chapter :ref:`SoftwareTestReports` and following.

8. Is abnormal termination of testing process (for example, incorrect major
   fault, out of time) reported?

   The :term:`RTEMS` Tester does report on abnormal termination, like
   crashes and timeouts. Yet, the tests for this
   project are orchestrated and conducted by the qualification tool chain
   (see ``spec:/qt/req/functional/test-manager-001`` and following in the
   qualification tool chain ${/ref/legacy/qtsrs-r2:/cite-long}).
   Therefore, the tool chain |SVR| ${/ref/legacy/qtsvr:/cite} must verify this question.

9. Are abnormal termination conditions documented in summary section of the
   unit test report, together with the unfinished testing and any
   uncorrected faults?

   The tests for this
   project are conducted and reported by the qualification tool chain
   (see section *5.5.1.4.25 rtemsspec.process_report module* in the
   qualification tool chain ${/ref/legacy/qtsdd-r1:/cite-long}).
   Therefore, the tool chain |SVR| ${/ref/legacy/qtsvr:/cite} must verify this question.

.. RTEMS calls these kind of test *validation tests* instead of *unit tests*.
   Point 2 EDISOFT ...

.. (Frank) See :ref:`QDPProposalSUITP`.
           RTEMS uses combined unit and integration tests because of
           :ref:`TailoringJustUnitTestingOnDemand`.

.. _VerificationOfSoftwareIntegration:

Verification of Software Integration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The verification activities related to the software integration are mandated by
clause 5.8.3.7 of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

1. There are no integration tests, so no traceability from integration tests to
   the software architectural design is present.  For a traceability from
   validation tests to requirements, see
   :ref:`Verification_of_software_validation`.

2. :term:`RTEMS` is not a new software build from individual units which
   must be integrated in a second step. Instead :term:`RTEMS` exists since
   decades and is an integrated piece of software. Because it is used since
   many years, its pieces have long been proved to be internally consistent.

   The validation tests probe :term:`RTEMS` as a whole piece of integrated
   software. If the software would be internally inconsistent, these tests
   would fail.

3. The validation tests exercise all external interfaces otherwise the
   code coverage goal could not be reached.

4. Section :ref:`Verification_of_software_validation` reports whether
   all validation tests have reached their expected results.

   Section :ref:`Coverage` reports whether
   validation tests have reached their expected code coverage results.

.. Point 1 is from EDISOFT

.. _VerificationSwDocs_CDR:

Verification of Software Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Outdated:** This section represents the state at ${/glossary/cdr:/term} and
${/glossary/qr:/term}/1.  This section is outdated and superseded by
:ref:`VerificationSwDocs_AR`.

The verification activities related to the software architectural design are
mandated by clause 5.8.3.10 of |E40| ${/ref/ecss/q-st-40c-r1:/cite}:

* **Reviewer:** Frank Kühndel (embedded brains)
* **Review Date:** 2021-02-23/24, updated 2021-05-28
* **Input Item:**

    * ${/ref/tn/qt-109-r6:/cite-long}
    * ${/ref/legacy/scmp-r5:/cite-long}
    * ${/ref/legacy/sdp-r6:/cite-long} (only table 5.1)
    * |QDP| ${/ref/legacy/gr712rc-cdr:/cite}

1. Is the documentation is adequate, complete, and consistent?

.. list-table:: Documentation in the :term:`QDP` according to QT-109 -- part 1.
   :widths: 15 10 5
   :header-rows: 1

   * - Document
     - Path in :term:`QDP`
     - Present in QDP?
   * - Software Requirements Specification (SRS)
     - ``doc/ts/srs/srs.pdf``
     - Yes
   * - Software Interface Control Document (ICD)
     - ``doc/ts/icd/icd.pdf``
     - Yes
   * - Software Design Document (SDD)
     - ``doc/ddf/sdd/sdd.pdf``
     - Yes
   * - Software Configuration File (SCF)
     - ``doc/ddf/scf/scf.pdf``
     - Yes, but as ``rtems-6- sparc- gr712rc- smp-2- scf.pdf``
   * - Software Release Document (SRelD)
     - ``doc/ddf/sreld/sreld.pdf``
     - *No*
   * - Software User Manual (SUM)
     - ``doc/ddf/sum/sum.pdf``
     - Yes, |RUM| is considered :term:`SUM`
   * - Software Unit and Integration Test Plan (SUITP)
     - ``doc/djf/suitp/suitp.pdf``
     - *No*

.. list-table:: Documentation in the :term:`QDP` according to QT-109 -- part 2.
   :widths: 15 10 5
   :header-rows: 1

   * - Document
     - Path in :term:`QDP`
     - Present in QDP?
   * - Software Validation Specification (SVS) with Respect to TS
     - ``doc/djf/svsts/svsts.pdf``
     - Yes, as ``svs.pdf``
   * - Software Unit and Integration Test Report (SUITR)
     - ``doc/djf/suitr/suitr.pdf``
     - *No*
   * - Software Validation Report with Respect to TS
     - ``doc/djf/svalrts/svalrts.pdf``
     - Yes, but identical to ``svr.pdf``
   * -  Software Verification Report (SVR)
     - ``doc/djf/svr/svr.pdf``
     - Yes
   * - Software Reuse File (SRF)
     - ``doc/djf/srf/srf.pdf``
     -  Yes, as ``SRF-024.pdf``
   * - Software Development Plan (SDP)
     - ``doc/mgt/sdp/sdp.pdf``
     - Yes, as ``SDP-000.pdf``
   * - Software Review Plan (SRevP)
     - ``doc/mgt/srevp/srevp.pdf``
     - Yes, as ``SRevP-018.pdf``
   * - Software Configuration Management Plan (SCMP)
     - ``doc/mgt/scmp/scmp.pdf``
     - Yes, as ``SCMP-001.pdf``
   * - Software Product Assurance Plan (SPAP)
     - ``doc/paf/spap/spap.pdf``
     - Yes, as ``SPAP-002.pdf``
   * - Software Product Assurance Milestone Report (SPAMR)
     - ``doc/paf/spamr/spamr.pdf``
     -  Yes
   * - |QT109|
     - ``doc/technical-notes/QT-109.pdf``
     - Yes, as ``QT-109.pdf``
   * -  EDISOFT. Tools Identification
     - ``doc/technical-notes/tn-ti.pdf.pdf``
     - Yes, as ``TI-003.pdf``
   * - RTEMS User Manual
     - ``doc/rtems/user/user.pdf``
     - Yes
   * - RTEMS Classic API Manual
     - ``doc/rtems/c-user.pdf``
     - Yes
   * - RTEMS Software Engineering
     - ``doc/rtems/eng.pdf``
     - Yes
   * - RTEMS CPU Architecture Supplement
     - ``doc/rtems/cpu-supplement/cpu-supplement.pdf``
     - Yes

2. Is documentation preparation is timely?

   **Outdated:** This section represents the state at :term:`CDR` and
   :term:`QR`\#1 as required by |E40| ${/ref/ecss/q-st-40c-r1:/cite}, clause 5.8.3.10.
   This section is outdated and superseded by :ref:`VerificationSwDocs_AR`.

   As already stated above and elsewhere in this :term:`SVR`,
   several documents are still missing or not complete
   (:term:`ICD`, :term:`SRS` and :term:`SDD`) at :term:`CDR`.
   Moreover, this :term:`SVR` was not completed at the time of the :term:`CDR`.

3. Does configuration management of documents follows specified procedures?

   **Outdated:** This section represents the state at :term:`CDR` and
   :term:`QR`\#1 as required by |E40| ${/ref/ecss/q-st-40c-r1:/cite}, clause 5.8.3.10.
   This section is outdated and superseded by :ref:`VerificationSwDocs_AR`.

   Configuration Management is defined in the |SCMP|
   section *6 Information/documentation management*. The document
   identification is in table 5.1 of the |SDP|.

   **Verification:**

     * Are documents correctly identified according to :term:`SCMP`
       section *6.1 Information identification*?

     * Is document identification and configuration management
       consistent between :term:`SCMP` and QT-109
       chapter *5 Qualification Data Package*?

     * Are documents build, available in formats, contain the information and
       made available as defined in :term:`SCMP` section *6.2 Data formats*?

     * Is the :term:`QDP` made available as described in :term:`SCMP`
       section *6.5 Delivery methods*?

     * Are the non-draft documents signed as described in :term:`SCMP`
       section *6.6 Digital signature*?

.. _OtherSpecificInspectionDesign_CDR:

Others Specific Inspections, Analyses, or Review of Design Reports
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are no other specific inspections, analyses, or review of design reports.

.. _OtherSpecificVerificationRAMS_CDR:

Other Specific Verification Related to RAMS Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A ${/glossary/hsia:/term} and ${/glossary/sfta:/term} was not carried out for
the pre-qualified feature set of RTEMS, see also section *No Software
Dependability and Safety Analysis* of the ${/ref/tn/qt-109-r6:/cite-long}.  The RTEMS
Improvement ${/glossary/scar:/term} was used as an input for the activity, see
section *Software Dependability and safety* of the |SPAP| ${/ref/legacy/spap-r7:/cite}.  The
${/glossary/sfmeca:/term} results of the report are presented in the SPAP.  The
SPAP lists recommendations issued by the RTEMS Improvement RAMS Team and
associated actions for the RTEMS Improvement upgrade.  These recommendations
were analysed with respect to the activity.  It was concluded that none of the
recommendations are applicable.  In conclusion, there are no RAMS requirements
and thus no related verification activities.

Software Delivery and Acceptance Process Verification (for QR and AR)
=====================================================================

Traceability
------------

.. _SoftwareAcceptanceTestingToRequirementBaseline:

Software Acceptance Testing to Requirement Baseline
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
:ref:`NoRB`.  It is recommended that the end user of the QDP writes acceptance
tests.

Feasibility
-----------

.. _Coverage:

Structural Code Coverage Achievement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: ../include/coverage-summary.rst

.. _VerificationSwDocs_AR:

Verification of Software Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This section covers the state at ${/glossary/qr:/term}/2 and
${/glossary/ar:/term}.  The verification activities related to the software
architectural design are mandated by clause 5.8.3.10 of |E40|
${/ref/ecss/q-st-40c-r1:/cite}:

* **Reviewer:** Frank Kühndel (embedded brains)
* **Review Date:** 2021-11-26, 2021-11-18, 2021-10-29

  Earlier reviews 2021-09-21/22 and 2021-10-21 opened findings
  `Issue #671`_, `Issue #645`_, `Issue #734`_, `Issue #736`_ and `Issue #737`_.

* **Input Item:**

    * Previous review in section :ref:`VerificationSwDocs_CDR`
      for :term:`CDR` and :term:`QR`\#1
    * ${/ref/tn/qt-109-r6:/cite-long}
    * ${/ref/legacy/scmp-r7:/cite-long}
    * ${/ref/legacy/sdp-r7:/cite-long} (only table 5.1)
    * Pre-:term:`AR`/:term:`FR` |QDP| build from commit

      ``dd6e686138ff83ac604d84f999c498412540ffb7``

      The following documents contained in this :term:`QDP` have been reviewed:
      :term:`SUITP`, :term:`SRelD`, :term:`ICD` and :term:`SVS`.

    * For review 2021-11-26 the :term:`SRS` and :term:`ICD`
      found in `Issue #739`_ have been used.

   **Compliant:** Yes

1. Is the documentation adequate, complete, and consistent?

.. list-table:: Documentation in the :term:`QDP` according to QT-109 -- part 1.
   :widths: 15 10 5
   :header-rows: 1

   * - Document
     - Path in :term:`QDP`
     - Present in QDP?
   * - Formal Verification Plan
     - ``doc/fm/fvp/FV1-200.pdf``
     - Yes
   * - Formal Verification Artefacts
     - ``doc/fm/fva/FV2-201.pdf``
     - Yes
   * - Formal Verification Report
     - ``doc/fm/fvr/FV3-202.pdf``
     - Yes
   * - Software Release Document (SRelD)
     - ``doc/ddf/sreld/sreld.pdf``
     - Yes
   * - Software Unit and Integration Test Plan (SUITP)
     - ``doc/djf/suitp/suitp.pdf``
     - Yes

.. list-table:: Documentation in the :term:`QDP` according to QT-109 -- part 2.
   :widths: 15 10 5
   :header-rows: 1

   * - Document
     - Path in :term:`QDP`
     - Present in QDP?
   * - Software Requirements Specification (SRS)
     - ``doc/ts/srs/srs.pdf``
     - Yes
   * - Software Interface Control Document (ICD)
     - ``doc/ts/icd/icd.pdf``
     - Yes
   * - Software Design Document (SDD)
     - ``doc/ddf/sdd/sdd.pdf``
     - Yes
   * - Software Validation Specification (SVS) with Respect to TS
     - ``doc/djf/svsts/svsts.pdf``
     - Yes, as ``svs.pdf``
   * -  Software Verification Report (SVR)
     - ``doc/djf/svr/svr.pdf``
     - Yes
   * - Software Reuse File (SRF)
     - ``doc/djf/srf/srf.pdf``
     -  Yes, as ``SRF-024.pdf``
   * - Software Development Plan (SDP)
     - ``doc/mgt/sdp/sdp.pdf``
     - Yes, as ``SDP-000.pdf``
   * - Software Review Plan (SRevP)
     - ``doc/mgt/srevp/srevp.pdf``
     - Yes, as ``SRevP-018.pdf``
   * - Software Configuration Management Plan (SCMP)
     - ``doc/mgt/scmp/scmp.pdf``
     - Yes, as ``SCMP-001.pdf``
   * - Software Product Assurance Plan (SPAP)
     - ``doc/paf/spap/spap.pdf``
     - Yes, as ``SPAP-002.pdf``
   * - Software Product Assurance Milestone Report (SPAMR)
     - ``doc/paf/spamr/spamr.pdf``
     -  Yes
   * - |QT109|
     - ``doc/technical-notes/QT-109.pdf``
     - Yes, as ``QT-109.pdf``
   * - EDISOFT. Tools Identification
     - ``doc/technical-notes/tn-ti.pdf.pdf``
     - Yes, as ``TI-003.pdf``
   * - RTEMS User Manual
     - ``doc/rtems/user/user.pdf``
     - Yes
   * - RTEMS Classic API Manual
     - ``doc/rtems/c-user.pdf``
     - Yes
   * - RTEMS Software Engineering
     - ``doc/rtems/eng.pdf``
     - Yes
   * - RTEMS CPU Architecture Supplement
     - ``doc/rtems/cpu-supplement/cpu-supplement.pdf``
     - Yes

Documents not listed in the QT-109 but present:

.. list-table:: Documents not listed in the QT-109 but present
   :widths: 15 10 5
   :header-rows: 1

   * - Document
     - File name
     - Place
   * - |SCF|
     - ``rtems-6-sparc-gr712rc- smp-2-scf.pdf``
       ``rtems-6-sparc-gr712rc- uni-2.pdf``
       ``rtems-6-sparc-gr740- smp-2.pdf``
       ``rtems-6-sparc-gr740- uni-2.pdf``
     - At same place as the QDP
   * - |SP|
     - ``doc/technical-notes/tn-space-profile.pdf``
     - In the QDP

Documents found elsewhere:

|SUM|:
     The |RUM| acts as :term:`SUM`

|SUITR|:
     The :term:`SUITR` is part of this |SVR| and can be found in form of
     subsections of chapter :ref:`SoftwareTestReports` and following chapters.

|SValR|:
     The :term:`SValR` is part of this |SVR| and can be found
     in chapters :ref:`SoftwareTestReports` and following chapters.

.. _VerificationOfSwDocsFindings:

**Comments:**

    The review 2021-10-21 confirms that all *T B D* and *T O D O*
    found by earlier reviews in :term:`SUITP`, :term:`SRelD`, :term:`ICD`
    and :term:`SVS` have been resolved.

    The review 2021-10-29 confirms that the |FVR| is present in a draft version.

    The review 2021-11-26 confirms that the |ICD| and |SRS| are completed.

.. _`Issue #670`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/670
.. _`Issue #735`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/735
.. _`Issue #734`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/735
.. _`Issue #736`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/736
.. _`Issue #737`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/737

2. Is documentation preparation timely?

   There have been delays in the past. At :term:`AR`/:term:`FR`
   documentation is complete.

3. Does configuration management of documents follow specified procedures?

   Configuration Management is defined in the |SCMP|
   section *6 Information/documentation management*. The document
   identification is in table 5.1 of the |SDP|.

   **Verification:**

     * Are documents correctly identified according to :term:`SCMP`
       section *6.1 Information identification*?

     * Is document identification and configuration management
       consistent between :term:`SCMP` and QT-109
       chapter *5 Qualification Data Package*?

     * Are documents build, available in formats, contain the information and
       made available as defined in :term:`SCMP` section *6.2 Data formats*?

     * Is the :term:`QDP` made available as described in :term:`SCMP`
       section *6.5 Delivery methods*?

     * Are the non-draft documents signed as described in :term:`SCMP`
       section *6.6 Digital signature*?

.. _`Issue #671`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/671

.. _OtherSpecificVerificationRAMS_AR:

Other Specific Verification Related to RAMS Design
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There was no specific verification done related to ${/glossary/rams:/term}
requirements at the ${/glossary/qr:/term} and ${/glossary/ar:/term}, see also
:ref:`OtherSpecificVerificationRAMS_CDR`.

Software Validation Process Verification (for CDR, QR, AR)
==========================================================

Traceability
------------

.. _SoftwareValidationSpecificationsToTS:

Software Validation Specifications to TS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

${.:/validation-verification}

.. _SoftwareValidationSpecificationsToRB:

Software Validation Specifications to RB
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
:ref:`NoRB`.  It is recommended that the end user of the QDP writes validation
tests with respect to its RB.

Feasibility
-----------

.. _Verification_of_software_validation:

Verification of Software Validation w.r.t. TS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Tests belonging to test suite Model-0 stem from formal verification.
For example:

  * RtemsModelSystemEventsMgr *N*
  * RtemsModelEventsMgr *N*
  * RtemsModelChainAPI *N*

The specifications of these tests can be found in the *Promela* models
in sub-folder ``doc/djf/svr/formal/``. They consist of Promela model
(``*.pml``) and refinement files (``*-rfn.yml``).

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2021-11-24/26, review 2021-11-19 opened `Issue #776`_,
2021-11-10, review 2021-09-29 opened `Issue #733`_ (closed in favor
of `Issue #753`_).

  * |QDP| for gr712rc-smp build from commit:
    ``d2cecd5c47be3c1f6b3072496dffbbb8be2a6ba6``

  * |SVR| from the above :term:`QDP`

**Compliant:** Yes

**Verification:**

  * There are no failed test.

  * All test have specifications and test requirements.

.. _`Issue #733`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/733
.. _`Issue #753`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/753
.. _`Issue #773`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/773
.. _`Issue #776`: https://gitrepos.estec.esa.int/external/rtems-smp-qualification/-/issues/776

.. _VerificationOfSoftwareValidationRB:

Verification of Software Validation w.r.t. RB
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ${/glossary/qdp:/term} does not provide a ${/glossary/rb:/term}, see also
:ref:`NoRB`.  It is recommended that the end user of the QDP writes validation
tests with respect to its RB.

.. _VerificationOfSoftwareDocumentation:

Verification of Software Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Verification activities with respect to the software documentation are reported
in sections :ref:`VerificationSwDocs_CDR` and :ref:`VerificationSwDocs_AR`.

Software Validation Analysis, Inspection, Review of Design Reports
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The reports for validations by analysis, inspection, or review of design are
presented in the ${doc-djf-svs:/cite-long}.

Software Quality Requirements Verification
==========================================

The software quality verifications are done according to section 10.3.3.1 of
the |SVP| which is integral part of the ${/ref/legacy/sdp-r6:/cite-long}:

Collection and analysis of metrics as defined by :term:`SPAP` ${/ref/legacy/spap-r6:/cite}
    The metrics are reported and justified in a dedicated chapter in
    the |SPAMR|.

Quality review of the deliverables on each formal review
    All performed reviews -- including inspections -- are reported in
    dedicated sections in the |SPAMR|.

Measures to handle automatically generated code
    Generated code is treated like manually written code. See also section
    :ref:`AutomaticallyGeneratedCode`.

      * Generated code is reviewed on the mailing list like manual written code.
      * Generated code is subject to testing (in order to achieve the code
        coverage threshold)
      * Generated code undergoes the same static analyzing and metering as
        the manual generated code

**Reviewer:** Frank Kühndel (embedded brains)

**Review Date:** 2021-02-24

**Verification:** Personal experience and observation of activities in the
project and on the mailing list throughout the last four months. Currently,
verification tests and header files are partially generated. Examples are

    * `[PATCH 2/2] validation: Tests for barrier manager <Mailinglist064256>`_
    * `[PATCH v2] rtems: Rework object services API <Mailinglist064177>`_ -- file ``object.h``
    * `[PATCH 02/13] validation: Add signal manager tests <Mailinglist064639>`_
    * `[PATCH] basedefs: Add stringification of argument lists <Mailinglist063765>`_

.. _`Mailinglist064256`: https://lists.rtems.org/pipermail/devel/2021-February/064256.html
.. _`Mailinglist064177`: https://lists.rtems.org/pipermail/devel/2021-February/064177.html
.. _`Mailinglist064639`: https://lists.rtems.org/pipermail/devel/2021-February/064639.html
.. _`Mailinglist063765`: https://lists.rtems.org/pipermail/devel/2020-December/063765.html

**Compliant:** Yes


.. See long task description and to do in <4.7>.a
   rtems-smp-qualification/deliverables/QT-109/source/qdp-djf-svr.rst
