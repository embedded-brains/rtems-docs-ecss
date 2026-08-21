<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# Submitting issues

Please submit issues related to this documentation project through
[ESA GitLab issues](https://gitlab.esa.int/gitrepos/external/rtems-smp-qualification/-/issues).

# Contributing to the project

## Sign your work

We use the
[Developer Certificate of Origin (DCO)](DCO.txt)
which is included in the repository.  Please read this text.  If you can
certify it, then add a line like this to every Git commit message of your
contributions:

```
Signed-off-by: Erika Mustermann <erika.mustermann@example.com>
```

Use your real name for contributions to this project.

## Building the documentation

The build needs Python with [uv](https://docs.astral.sh/uv/), a C compiler,
Doxygen and TeX Live.  The Ubuntu package archive does not provide the required
Doxygen release, so the build environment builds it from source.  Some
documents use analysis tools such as Cppcheck on the software under
qualification.  The [Dockerfile](.github/container/Dockerfile) used by the
GitHub workflows lists every package and every version.

Install these packages on an Ubuntu host.  Then run:

```
make
```

The build writes the documents into the `build` directory.

`make` removes the results of the previous build first.  To rebuild after a
change, run:

```
make documentation
```

The CI job passes `GIT_OPTIONS=--do-not-use-git`.  Do not use this option
locally.  It leaves `build` as a Git repository without commits, and the next
`make` fails.  Run `make documentation-remove` to recover.

You can also build without an installation of the tools.  Build the image which
the CI job uses:

```
docker build -f .github/container/Dockerfile -t rtems-docs-ecss .
docker run --rm -it -v "$PWD":/work -w /work rtems-docs-ecss bash
```

In the container, run:

```
git config --global --add safe.directory /work
make
```

Use a separate clone for the container.  The container and the host must not
share the `.venv` directory, because `make` builds it for one Python
interpreter.

## Documentation rules

The
[Software Development Handbook](https://embedded-brains.github.io/rtems-docs-ecss/doc/technical-notes/sdh.pdf)
describes how to write and format the documentation sources.  Its sources are
in [src/sdh](src/sdh).  Format every changed file in [src](src) with `mdformat`
before you submit it.
