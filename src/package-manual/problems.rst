.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

.. _Problems:

Possible problems and known errors
**********************************

${.:/open-issues:0}

${.:/push-enabled-by: pkg.feature.qual}

Postponed ISVV findings
=======================

There were |ISVV| Findings that although confirmed as such, were not yet
addressed. The table below summarises the most relevant ones (for full
details, please refer to the documentation listed within
:ref:`ISVVDocs`).

While using the upcoming RTEMS SMP |QDP| release 5, one shall be aware
of these known issues, and assess the risk they impose to the
scope/mission/application on which the RTEMS SMP QDP is being used on.

.. tabularcolumns:: |>{\centering\let\\\tabularnewline}m{0.18\textwidth}
                    |m{0.29\textwidth}
                    |m{0.45\textwidth}|

.. _postponed-table:

.. table::  Most relevant postponed Findings
  :class: longtable

  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |ISVV Finding :sup:`2` |Finding Title                        |Further Details                                                              |
  +======================+=====================================+=============================================================================+
  |REQ-VER-004           |Incomplete requirements              |The requirements/specifications of "functional-type: action" have an         |
  |                      |                                     |incomplete text for these to really be understood as such and                |
  |                      |                                     |represent RTEMS implementation.                                              |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |REQ-VER-037           |Missing interfaces                   |One needs to check if interfaces within spec:/rtems/type/if/group            |
  |                      |                                     |needs to be updated not to mention interfaces not described in the           |
  |                      |                                     |ICD, or if the missing interfaces need to be added to ICD.                   |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |DESIGN-VER-004        |No SW User Manual (SUM) which        |Some typical SUM sections/information might be missing, which might          |
  |                      |follows ECSS clauses                 |be due to the generic nature of RTEMS. Further assessment is needed.         |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |DESIGN-VER-008        |Memory usage benchmarks              |Within section 4.8 of SW Configuration File (SCF)/SUM, one needs to          |
  |                      |                                     |add units for the values, and further contextualising information,           |
  |                      |                                     |otherwise one can't interpret the values.                                    |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |VAL-001               |"Timer Server" not directly usable   |For the current pre-qualified feature set of RTEMS, if one wants to          |
  |                      |                                     |use rtems_timer_initiate_server(), then it has to provide a custom           |
  |                      |                                     |stack allocator. This makes it inconvenient to use. One would need           |
  |                      |                                     |to provide a new directive to construct the timer server, e.g.,              |
  |                      |                                     |rtems_timer_server_construct().                                              |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |VAL-003               |Some functions are listed as         |One needs to improve the specification of some interfaces which are          |
  |                      |unspecified on ICD                   |currently set to unspecified interface-type.                                 |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |VAL-005               |Missing NULL pointer check for       |Although it might be considered as user responsibility, one could            |
  |                      |clock manager directives             |add logic that tests for NULL pointers within the clock manager              |
  |                      |                                     |directives, returning RTEMS_INVALID_ADDRESS where applicable.                |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |TS-VER-001            |No test cases descriptions           |Throughout all the SVS, several test cases do not have a                     |
  |                      |                                     |description. A test case description should be added for each test           |
  |                      |                                     |case.                                                                        |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |QT-QTU-SIM-008        |SPAMR - Fixed date and signature     |There is variable data on a signed document with fixed date.                 |
  |                      |for variable data                    |                                                                             |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |QT-QTU-SIM-015        |sphinxbuilder.py - bsp names         |If the BSP name contains underscores, then the document build                |
  |                      |with underscore                      |process will fail because the underscore, due to its special                 |
  |                      |                                     |meaning in latex. This is most noticeable on the document titles.            |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |QT-QTU-SIM-016        |ARM architecture's documents         |When building an ARM QDP, the ICD, SRS and SDD documents are                 |
  |                      |populated with SPARC specific        |populated with SPARC specific text. This is most noticeable                  |
  |                      |text                                 |on the document titles.                                                      |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-010          |TODO section left undone             |`#4810 - Unfinished TODO section`_                                           |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-011          |FIXME                                |`#4827 - Section left to be fixed in kern_tc.c and tls.h (FIXME)`_           |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-014 [3]_     |Macro wrongly defined                |`#4842 - Registers definitions wrongly defined when there are reserved bits`_|
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-018          |Deprecated Functions                 |`#4852 - Deprecated Functions`_                                              |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-023          |Code not in accordance with comments |`#4812 - Discrepancy between Code and Comments`_                             |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-026          |Function defined in header file      |`#4815 - Function defined in header file`_                                   |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-028          |Unused input parameter               |`#4862 - Unused input parameters`_                                           |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-029          |Input validity unchecked             |`#4855 - Input validity unchecked`_                                          |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-030          |Wrong data type                      |`#4816 - Wrong data type`_                                                   |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-032 [3]_     |Output value not assigned            |`#4830 - Output value not assigned`_                                         |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-044          |Code for test software               |`#4846 - Code for test software`_                                            |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-052          |#pragmas to ignore warnings          |`#4831 - #pragmas to ignore warnings`_                                       |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-071          |Confusing #IF 1 clause               |`#4819 - Unclear #IF 1 Clause in File: Possible Error`_                      |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-073          |Power-down workaround                |`#4875 - Power-down workaround`_                                             |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+
  |CODE-VER-078          |Bitwise operator applied to          |`#4864 - Bitwise operator applied to a signed operand`_                      |
  |                      |a signed operand                     |                                                                             |
  +----------------------+-------------------------------------+-----------------------------------------------------------------------------+

.. [3] Findings RTEMS-SMP-CODE-VER-014 and RTEMS-SMP-CODE-VER-032 are partially
   addressed.
   Please refer to section 3 of the RTEMS SMP ISVV Verification Report
   ${/ref/legacy/isvvver:/cite} for details.

All of the Postponed ISVV Findings have already been fully discussed with ESA
and the actions to address these are already fully defined within the Excel
files where these are listed. For further details, one can refer to the
documentation listed within :ref:`ISVVDocs`.

${.:/pop-enabled-by}

${.:/push-enabled-by: pkg.feature.qual}

Waiver
======

The following requests for waivers were issued and accepted.

.. figure:: waivers/RfW-QDP-01_1.pdf
   :figwidth: 100%
   :align: center

.. figure:: waivers/RfW-QDP-02_1.pdf
   :figwidth: 100%
   :align: center

.. figure:: waivers/RfW-QDP-03_1.pdf
   :figwidth: 100%
   :align: center

${.:/pop-enabled-by}

.. _`#4805 - SPDX Licenses and Header File Formatting`:                           https://devel.rtems.org/ticket/4805
.. _`#4806 - Header Source files format "extern C" missing`:                      https://devel.rtems.org/ticket/4806
.. _`#4807 - Two consecutive paragraphs`:                                         https://devel.rtems.org/ticket/4807
.. _`#4808 - Incorrect Formatting of "if", "while", or "for" Statements`:         https://devel.rtems.org/ticket/4808
.. _`#4809 - Incorrect Formatting of "!" Statements`:                             https://devel.rtems.org/ticket/4809
.. _`#4810 - Unfinished TODO section`:                                            https://devel.rtems.org/ticket/4810
.. _`#4827 - Section left to be fixed in kern_tc.c and tls.h (FIXME)`:            https://devel.rtems.org/ticket/4827
.. _`#4828 - Macro defined but magic number used instead`:                        https://devel.rtems.org/ticket/4828
.. _`#4842 - Registers definitions wrongly defined when there are reserved bits`: https://devel.rtems.org/ticket/4842
.. _`#4852 - Deprecated Functions`:                                               https://devel.rtems.org/ticket/4852
.. _`#4829 - Unclear comments`:                                                   https://devel.rtems.org/ticket/4829
.. _`#4811 - Non-compliant Comments with Templates`:                              https://devel.rtems.org/ticket/4811
.. _`#4812 - Discrepancy between Code and Comments`:                              https://devel.rtems.org/ticket/4812
.. _`#4813 - Inaccurate comments at the beginning of file`:                       https://devel.rtems.org/ticket/4813
.. _`#4814 - Incorrect Copyright License Information`:                            https://devel.rtems.org/ticket/4814
.. _`#4815 - Function defined in header file`:                                    https://devel.rtems.org/ticket/4815
.. _`#4862 - Unused input parameters`:                                            https://devel.rtems.org/ticket/4862
.. _`#4855 - Input validity unchecked`:                                           https://devel.rtems.org/ticket/4855
.. _`#4816 - Wrong data type`:                                                    https://devel.rtems.org/ticket/4816
.. _`#4830 - Output value not assigned`:                                          https://devel.rtems.org/ticket/4830
.. _`#4843 - Output value not assigned`:                                          https://devel.rtems.org/ticket/4843
.. _`#4817 - Wrong output type`:                                                  https://devel.rtems.org/ticket/4817
.. _`#4844 - Unchecked boundaries`:                                               https://devel.rtems.org/ticket/4844
.. _`#4850 - Variable not initialized in any file / missing #ifdefs`:             https://devel.rtems.org/ticket/4850
.. _`#4845 - Global variable declared/defined in the wrong file`:                 https://devel.rtems.org/ticket/4845
.. _`#4846 - Code for test software`:                                             https://devel.rtems.org/ticket/4846
.. _`#4831 - #pragmas to ignore warnings`:                                        https://devel.rtems.org/ticket/4831
.. _`#4822 - Function returning unchanged function input`:                        https://devel.rtems.org/ticket/4822
.. _`#4818 - Incomplete Statement`:                                               https://devel.rtems.org/ticket/4818
.. _`#4832 - CLANG flagged error`:                                                https://devel.rtems.org/ticket/4832
.. _`#4819 - Unclear #IF 1 Clause in File: Possible Error`:                       https://devel.rtems.org/ticket/4819
.. _`#4875 - Power-down workaround`:                                              https://devel.rtems.org/ticket/4875
.. _`#4847 - Goto statements`:                                                    https://devel.rtems.org/ticket/4847
.. _`#4863 - Operations evaluation order`:                                        https://devel.rtems.org/ticket/4863
.. _`#4864 - Bitwise operator applied to a signed operand`:                       https://devel.rtems.org/ticket/4864
.. _`#4820 - Hazardous cast`:                                                     https://devel.rtems.org/ticket/4820
.. _`#4849 - "Timer Server" is not directly usable`:                              https://devel.rtems.org/ticket/4849
.. _`#4918 - Some functions are listed as unspecified on ICD`:                    https://devel.rtems.org/ticket/4918
.. _`#4874 - Undefined behaviour`:                                                https://devel.rtems.org/ticket/4874
