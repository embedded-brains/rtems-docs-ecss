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

This repository should be used in a package repository as a Git submodule.  In
the package repository, add the package specification [spec](spec)
directory of this repository to the package specification directory list used
for the package build.  The package component `spec:/pkg/component` shall
define the `rtems-docs-ecss-directory` attribute.  It shall specify the path to
the documentation sources [src](src) relative to the package build workspace
`${.:/component/workspace-directory}`, for example:

```yaml
rtems-docs-ecss-directory: modules/rtems-docs-ecss/src
```

# Contributing

Please refer to our
[Contributing Guidelines](CONTRIBUTING.md).

# Origin

Content from the
[ESA GitLab rtems-smp-qualification](https://gitlab.esa.int/gitrepos/external/rtems-smp-qualification)
and
[ESA GitLab rtems-smp-qualification-qual](https://gitlab.esa.int/gitrepos/external/rtems-smp-qualification-qual)
repositories was used to populate this repository.
