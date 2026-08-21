<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# Overview

This repository contains the [ECSS](https://ecss.nl/) documentation set for the
pre-qualified feature set of the [RTEMS](https://www.rtems.org/) real-time
operating system.

The documentation is built using
[specmake](https://github.com/specthings/specmake)
tools.

A demonstration build of the documentation set is published at
<https://embedded-brains.github.io/rtems-docs-ecss/>.  It uses the dummy
project of this repository, so the documents carry placeholder names and the
links to the RTEMS documentation do not resolve.

That build includes the
[Software Development Handbook (SDH)](https://embedded-brains.github.io/rtems-docs-ecss/doc/technical-notes/sdh/index.html).
It describes the specification items, the documentation rules and the tools of
the pre-qualification.

The following documents are provided:

- [Software Configuration File (SCF, Package Manual)](src/package-manual/config.yml)

- [Software Release Document (SRelD)](src/ddf/sreld/config.yml)

- [Interface Control Document (ICD)](src/ts/icd/config.yml)

- [Software Requirements Specification (SRS)](src/ts/srs/config.yml)

- [Software Validation Specification with respect to TS (SVS)](src/djf/svs/config.yml)

- [Software Unit and Integration Test Plan (SUITP)](src/djf/suitp/config.yml)

- [Software Verification Report (SVR)](src/djf/svr/config.yml)

- [Test Report](src/djf/tr/config.yml)

- [User Test Report](src/user/tr/config.yml)

- [Software Development Handbook (SDH)](src/sdh/config.yml)

The following management and product assurance documents required for an ECSS
pre-qualification are **not provided**:

- [Software Development Plan (SDP)](src/mgt/sdp/config.yml)

- [Software Configuration Management Plan (SCMP)](src/mgt/scmp/config.yml)

- [Software Product Assurance Plan (SPAP)](src/paf/spap/config.yml)

- [Software Product Assurance Milestone Report (SPAMR)](src/paf/spamr/config.yml)

The management and product assurance documents require a project-specific
customization.

An ECSS standard tailoring is **not provided**.  See
[Policy for use of ECSS System by non-ECSS members](https://ecss.nl/license-agreement-disclaimer/).

# Package Integration

A package repository builds a package of the pre-qualified RTEMS.  It provides
the package configuration and the software under qualification.  It is not part
of this repository.  The
[RTEMS package repository](https://github.com/embedded-brains/rtems-package)
is an example.

This repository provides the documentation sources.  A package repository adds
it as a Git submodule.  The package build reads a list of package specification
directories.  Add the [spec](spec) directory of this repository to that list.
The package component `spec:/pkg/component` shall define the
`rtems-docs-ecss-directory` attribute.  It shall specify the path to the
documentation sources [src](src) relative to the package build workspace
`${.:/component/workspace-directory}`, for example:

```yaml
rtems-docs-ecss-directory: modules/rtems-docs-ecss/src
```

This repository also builds the documents on its own.  The build then uses the
dummy software in [dummy-software](dummy-software) in place of a real package.
The documents carry placeholder content.  See the
[Contributing Guidelines](CONTRIBUTING.md) for the build.

# Contributing

Please refer to our
[Contributing Guidelines](CONTRIBUTING.md).

# Origin

Content from the
[ESA GitLab rtems-smp-qualification](https://gitlab.esa.int/gitrepos/external/rtems-smp-qualification)
and
[ESA GitLab rtems-smp-qualification-qual](https://gitlab.esa.int/gitrepos/external/rtems-smp-qualification-qual)
repositories was used to populate this repository.
