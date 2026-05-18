.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2022 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

.. _Introduction:

Introduction
************

The Software Verification Report (${/glossary/svr:/term}) is a part of the
Design Justification File (DJF) as required by ${/ref/ecss/e-st-40c:/cite-long}
and ${/ref/ecss/q-st-80c-r1:/cite-long}.  The document is intended to be used
by reviewers and qualification authorities.  For users of the
${/glossary/qdp:/term} and ${/glossary/rtems:/term} it is recommended to get
started by reading the ${/pkg/deployment/doc-package-manual:/cite-long}.  For
using RTEMS in general, please refer to the ${/ref/rtems/user:/cite-long} and
the ${/ref/rtems/c-user:/cite-long}.

The specification of RTEMS is done using so called specification items.  For an
overview of the specification approach see the
`Software Requirements Engineering <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/index.html>`_
chapter in the ${/ref/rtems/eng:/cite-long}.  It is recommended to read this
chapter.

RTEMS is a reusable software component whose main purpose is to provide an
Application Programming Interface (${/glossary/api:/term}) to real-time
operating system services.  The component should implement the API and nothing
more.  The interfaces of RTEMS are specified in the Interface Control Document
${doc-ts-icd:/cite}.  RTEMS existed for more than 30 years before this
pre-qualification activity started, this explains why not many design and
other non-functional requirements are present.  The purpose of the activity was
not the development of a new software product.  The focus of the activity was
an accurate specification and validation of the functions implementing the API
of the *pre-qualified feature set*.  RTEMS in general provides more
functionality.  A key element of the pre-qualified feature set is the support
for Symmetric Multiprocessing (${/glossary/smp:/term}).

This document covers only RTEMS and no other software products related to the
QDP.  In particular, it does not cover the tool chain generating the QDP, see
also ${/ref/legacy/svr-r1:/cite}.  The purpose of this document is to present gathered
results of all the software verification activities that have to be executed
along the software development life cycle according to the |SVerP|. It is
organized per process, with the exception of the timing and sizing issues which
are gathered in a separate chapter.

This document follows the definition of Annex M of |E40| for chapters from 1 to
6.  As a deviation from |E40| and |Q80| the validation, unit, and integration
test reports are included in :ref:`SoftwareTestReports`.
