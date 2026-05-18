.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 embedded brains GmbH & Co. KG

.. _Introduction:

Introduction
************

The Interface Control Document together with the ${doc-ts-srs:/cite-long} forms
the Technical Specification as required by ${/ref/ecss/e-st-40c:/cite-long} and
${/ref/ecss/q-st-80c-r1:/cite-long}.  The document is intended to be used by
reviewers and qualification authorities.  For users of the
${/glossary/qdp:/term} and ${/glossary/rtems:/term} it is recommended to get
started by reading the ${/pkg/deployment/doc-package-manual:/cite-long}.  For
using RTEMS in general, please refer to the ${/ref/rtems/user:/cite-long} and
the ${/ref/rtems/c-user:/cite-long}.

The specification of RTEMS is done using so-called specification items.  For an
overview of the specification approach see the
`Software Requirements Engineering <${.:/component/deployment-directory:relpath %(*:/directory)}/doc/rtems/eng/req/index.html>`_
chapter in the ${/ref/rtems/eng:/cite-long}.  It is recommended to read this
chapter.  The interface requirements and interfaces presented in the current
document are specified using specification items.

RTEMS is a reusable software component whose main purpose is to provide an
Application Programming Interface (${/glossary/api:/term}) to real-time
operating system services.  The component should implement the API and nothing
more.  The mainline version of RTEMS contains a lot of features.  It would have
been impossible to cover everything within the scope of this activity.
Therefore, a survey was carried out in March 2019, and the results were discussed
on an online workshop organised by ESA/ESTEC on 27 March 2019.  The initial
set of interfaces for the pre-qualified RTEMS feature set is documented in the
${/ref/tn/rtems-space-profile-r6:/cite-long}.  Please note that the technical
note specifies only the initial set of interfaces.  For example, several object
delete directives are explicitly excluded in the technical note.  However, in
order to run the validation tests it turned out that deleting objects was
absolutely necessary to reduce the memory demands of the validation tests
(reusable objects vs. use only once objects).  Other interfaces were added to
the pre-qualified feature set to avoid new conditional code, for example
sending and catching signals.

The API header files of RTEMS are generated from specification items.  The
header files are completely generated, so in case a header file contains an
interface which is not included in the pre-qualified feature set, then it still
needs to be specified.  All specified interfaces which are not included in the
pre-qualified feature set are marked as such through constraints.  The
constraints are listed for each interface here in the ICD and also in the
${/ref/rtems/c-user:/cite-long}.
