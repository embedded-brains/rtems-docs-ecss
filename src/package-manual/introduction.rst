.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020 embedded brains GmbH & Co. KG

.. _Introduction:

Introduction
************

The *${.:/component/package-long}* or shorter ${.:/component/package-short}
provides you with a comprehensive set of tools, libraries, header files,
sources, and documentation to build applications using the :term:`RTEMS`
real-time operating system.
${.:/push-enabled-by:pkg.feature.qual}
Some components are pre-qualified for use in criticality category B systems
according to ${/glossary/ecss:/term} standards for software products
(${/ref/ecss/e-st-40c:/cite-long} and ${/ref/ecss/q-st-80c-r1:/cite-long}).
${.:/pop-enabled-by}

The package is shipped in the separate archive file
:file:`${.:/input/archive/file:basename}` [#f1]_.  Please read the
:ref:`GettingStarted` section before you unpack this archive.
${.:/push-enabled-by:and: [pkg.feature.qual, pkg.arch.sparc]}
You may obtain this document and the package from the following ESA web site:
`https://rtems-qual.io.esa.int/ <https://rtems-qual.io.esa.int/>`_.
${.:/pop-enabled-by}

The :ref:`ECSSSoftwareDocumentation`, :ref:`TechNotes`, :ref:`RTEMSDocs` and
:ref:`FormalMethods` sections give you a structured overview and quick access
to all documents of the package.

For help to migrate existing applications from a previous RTEMS version to the
RTEMS version delivered by the package, see the :ref:`Migration`.
${.:/push-enabled-by:pkg.feature.qual}
Migrating applications and a qualification according to ECSS standards is a complex task,
especially if you migrate also from a uniprocessor system to an
${/glossary/smp:/term} system.  For ${/glossary/qdp:/plural} and related
activities, service and maintenance is provided by embedded brains, see also
:ref:`Service`.
${.:/pop-enabled-by}
${.:/push-enabled-by:not: pkg.feature.qual}
For service and maintenance by embedded brains, see :ref:`Service`.
${.:/pop-enabled-by}

${.:/push-enabled-by:pkg.feature.qual}
:ref:`MissionQualification` is provided in a dedicated section, describing the
necessary steps to qualify components of the package for the hardware platform
of the package user.
${.:/pop-enabled-by}
For ${/glossary/target:/term} systems used to execute the validation tests of
the package, see :ref:`Targets`.

.. topic:: Important Notice

    The package contains several open source software products which are
    covered by various open source licenses.  You find all sources and licenses
    in the
    :file:`${.:/component/deployment-directory:relpath %(/pkg/component:/prefix-directory)}/src`
    directory in case the package was unpacked in
    :file:`${.:/component/prefix-directory}`.  See also the :ref:`LicenseInfo`.
    The package is provided by the copyright holders and contributors "as is"
    and any express or implied warranties, including, but not limited to, the
    implied warranties of merchantability and fitness for a particular purpose
    are disclaimed. In no event shall the copyright owner or contributors be
    liable for any direct, indirect, incidental, special, exemplary, or
    consequential damages (including, but not limited to, procurement of
    substitute goods or services; loss of use, data, or profits; or business
    interruption) however caused and on any theory of liability, whether in
    contract, strict liability, or tort (including negligence or otherwise)
    arising in any way out of the use of this software, even if advised of the
    possibility of such damage.

.. rubric:: Footnotes

.. [#f1] The archive file :file:`${.:/input/archive/file:basename}` has an SHA512
         digest of ``${.:/input/archive/sha512}``.
