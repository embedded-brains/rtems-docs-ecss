% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(Tools)=

# Tools

This chapter gives a brief overview of the command line tools used throughout
this handbook, what each tool is used for in this project, and where to find
more information.

(ToolsBuildDebugSimulation)=

## Build, debug, and simulation tools

(ToolMake)=

### make

[GNU Make](https://www.gnu.org/software/make/) is a build automation tool that
reads a `Makefile` describing how target files depend on other files and runs
the commands needed to bring outdated targets up to date.

In this project, the root `Makefile` builds the RTEMS tools installation, the
reference BSP installation, and the workspace application, see
{ref}`CreateWorkspace`. It also drives the day-to-day workflow around the
workspace application, for example `make run`, `make debug`, `make gdb`, and
`make distclean`.

See the [GNU Make manual](https://www.gnu.org/software/make/manual/) for more
information.

(ToolGdb)=

### gdb

@`/glossary/gdb:/term` is the GNU debugger. It lets you start a program under
its control, or attach to an already running program, and then inspect and
control its execution, for example by setting breakpoints, stepping through
code, and examining variables.

In this project, `make gdb` starts a @`/glossary/gdb:/term` client and connects
it to the workspace application started by `make debug`, see
{ref}`DebugWorkspaceApplication`.

See the [GDB website](https://www.sourceware.org/gdb/) for more information.

(ToolQemu)=

### qemu

[QEMU](https://www.qemu.org/) is a generic and open source machine emulator and
virtualizer.

In this project, `make run` and `make debug` execute the cross-compiled
workspace application under QEMU instead of on physical target hardware, see
{ref}`RunWorkspaceApplication` and {ref}`DebugWorkspaceApplication`.

See the [QEMU documentation](https://www.qemu.org/docs/master/) for more
information.

(ToolsSpecification)=

## Specification tools

The specification tools operate on the specification items in the `spec`
directory, see {ref}`SpecificationItems`. They are installed together with
`specmake` into the Python virtual environment of the RTEMS working tree, see
{ref}`CreateWorkingTree`. `uv` manages this environment from the
`pyproject.toml` of that tree. Run every tool through `uv run`, so that you get
the pinned version of each tool.

(ToolSpecverify)=

### specverify

`specverify` verifies the structural format of specification items: it checks
for well-formed YAML, resolvable links, and missing mandatory attributes. It
can also format specification items in place so that they follow this project's
YAML style, for example the list indentation convention.

In this project, `specverify` is run after every edit to a specification item,
first to format the changed files, then to validate the whole specification
tree:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ uv run specverify --format-items --do-not-indent-lists \
    --clang-format-style=default:file:_clang-format \
    spec/rtems/timer/req/create.yml
$ uv run specverify spec
```

```{raw} latex
\end{footnotesize}
```

Some specification attributes hold C language source code, for example the
pre-condition states and the test actions of an action requirement.
`specverify` formats them with the `clang-format` tool. Without the
`--clang-format-style` option, it fails on every such item.

The specification types name the style `default`. The `--clang-format-style`
option binds that name to a style file. The RTEMS working tree provides the
style file `_clang-format` in its root directory. The `file:` prefix is
mandatory, because `clang-format` reads a bare value as a style name.

The style file requires `clang-format` 22 or later. An older version rejects it
with the message `unknown enumerated scalar`. The virtual environment of the
RTEMS working tree pins a suitable version, which `uv run` selects.

The CI job runs this command on the changed items. It rejects the branch when
the command changes an item.

See {ref}`interface-items-step-8` and {ref}`ActionRequirementsStep7` for this
workflow in context.

@`.:/subprocess:args=specverify --help,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=-2`

(ToolSpecwareview)=

### specwareview

`specwareview` renders specification items into human-readable tables and
documents. The `--filter` option selects a rendering, for example
`action-compact-table` to render an action requirement's transition-map back
into a table, and `--format` selects the output format, for example `myst` or
`commonmark`.

In this project, `specwareview` is used to check the fully-resolved semantics
of a transition-map against the author's intent:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ uv run specwareview --filter=action-compact-table --format=myst /rtems/timer/req/create
```

```{raw} latex
\end{footnotesize}
```

Running `specwareview` without arguments also validates the whole specification
tree, complementary to `specverify`.

@`.:/subprocess:args=specwareview --help,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=-2`

(ToolSpecwareexport)=

### specwareexport

`specwareexport` exports the specification into generated source code
(application configuration, interface, and validation code) and documentation
source files.

In this project, `make` invokes `specwareexport` internally to generate C code
from the specification items, see {ref}`QualEngGenerateCCode`. It can also be
run directly, for example to only generate source code and skip the
documentation sources:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ uv run specwareexport --no-application-configuration-code --no-documentation
```

```{raw} latex
\end{footnotesize}
```

@`.:/subprocess:args=specwareexport --help,cwd=%(.:/component/deployment-directory),hide-cwd=1,font-size=-2`
