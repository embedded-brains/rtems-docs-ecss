.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 embedded brains GmbH & Co. KG

.. _Introduction:

Introduction
************

The Software Validation Specification (with respect to the Technical
Specification) is a part of the Design Justification File (DJF) as required by
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
