% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Set up of qualification engineering environment

## How to prepare your computer?

You should have a Linux computer with these packages installed:

- a working C, C++ and Python development environment -- see section
  [POSIX Hosts](https://docs.rtems.org/docs/main/user/hosts/posix.html#posix-hosts)
  in the [RTEMS User Manual](https://docs.rtems.org/docs/main/user/)
- the [uv](https://docs.astral.sh/uv/) Python package and project manager
- `git` -- there is usually a system package

The C, C++ and Python development environment is needed to build the RTEMS
toolchain (for example assembler, compiler, linker, debugger) for the target
architecture.

```{admonition} Ubuntu is the reference
For building packages, Ubuntu Linux containers are used. This Ubuntu is
the supported basis for all pre-qualification work. You can find the
Ubuntu version and all packages needed in this
[Dockerfile](https://github.com/embedded-brains/rtems-package/blob/main/.github/container/Dockerfile).
```

## How to create a local working tree?

This project uses the GitHub fork-and-pull-request workflow. Before
making any changes to the pre-qualified RTEMS, create a personal fork of the
[embedded brains RTEMS repository](https://github.com/embedded-brains/rtems)
on GitHub and clone it to your local development machine. This
how-to guide walks you through the process of creating a working tree
on your machine. The workflow to create a pull request is described
in another how-to.

```{note}
There is no need to build a package to extend the pre-qualified subset
of RTEMS. Indeed, this would complicate the workflow, since building and
changing a package takes a lot of time. It is sufficient to use a
dedicated branch of
[embedded brains RTEMS repository](https://github.com/embedded-brains/rtems).

This branch contains:

- The [RTEMS baseline](https://gitlab.rtems.org/rtems/rtos/rtems)
- The RTEMS specification (in the `spec/` folder)
- The [specthings](https://github.com/specthings/) tools needed for
  specification work
- A [`Makefile`](https://github.com/embedded-brains/rtems/blob/esa/v6.2/Makefile)
  for a CI job to build three versions of SPARC BSP configurations
- The infrastructure to extend the RTEMS pre-qualification feature set

Therefore, the how-tos here focus on this single repository and branch.

If you are instead interested in building packages, see the
[package repository `README`](https://github.com/embedded-brains/rtems-package).
```

Aim:

- Have a checked-out working tree on your local machine.

Prerequisites:

- A GitHub account
- SSH access configured for GitHub (recommended)
- See [How to prepare your computer](#how-to-prepare-your-computer)

Steps:

1. **Sign in to GitHub**

    Open your web browser and sign in to your GitHub account.

2. **Create a Fork**

    Navigate to the RTEMS repository:

    [https://github.com/embedded-brains/rtems](https://github.com/embedded-brains/rtems)

    Click **Fork** in the upper-right corner of the GitHub page.

    During the fork creation process:

    - Select your personal GitHub account as the owner.
    - The appropriate branch is `eb/next`
    - Create the fork.

    Let `$${your_github_user}` be the name of your GitHub user. After
    completion, GitHub will create a copy of the repository under your account:

    ```{code-block} none
    ---
    linenos:
    ---
    https://github.com/$${your_github_user}/rtems
    ```

3. **Clone Your Fork**

    Open a terminal on your Linux machine and clone your fork:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git clone git@github.com:$${your_github_user}/rtems.git
    ```

    Alternatively, if you prefer HTTPS:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git clone https://github.com/$${your_github_user}/rtems.git
    ```

4. **Enter the Repository Directory**

    ```{code-block} none
    ---
    linenos:
    ---
    $ cd rtems
    ```

5. **Add the Original Repository as an Upstream Remote**

    Configure the original embedded brains repository as an additional
    remote. This allows you to synchronize your fork with the latest
    changes from the main project.

    ```{code-block} none
    ---
    linenos:
    ---
    $ git remote add upstream https://github.com/embedded-brains/rtems.git
    ```

6. **Verify the Remote Configuration**

    Verify that both remotes are configured correctly:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git remote -v
    ```

    The output should be similar to:

    ```{code-block} none
    ---
    linenos:
    ---
    origin    git@github.com:$${your_github_user}/rtems.git (fetch)
    origin    git@github.com:$${your_github_user}/rtems.git (push)
    upstream  https://github.com/embedded-brains/rtems.git (fetch)
    upstream  https://github.com/embedded-brains/rtems.git (push)
    ```

7. **Synchronize with the Upstream Repository**

    Before starting development, fetch the latest changes from the
    upstream repository:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git fetch upstream
    ```

    To update your local `eb/next` branch:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git checkout eb/next
    $ git pull --rebase upstream eb/next
    ```

    **Alternatively**, you can visit the web page of your fork and press
    the **Sync Fork** button on the top right and then fetch the latest
    changes from your fork repository:

    ```bash
    git fetch origin
    ```

    To update your local `eb/next` branch:

    ```{code-block} none
    ---
    linenos:
    ---
    $ git checkout eb/next
    $ git pull --rebase origin eb/next
    ```

Note: The RTEMS commit history is always linear. There are no merge commits
allowed. Consider this especially when resolving Git conflicts.

As a result, you now have:

- A fork of the embedded brains RTEMS repository in your GitHub account.
- A local clone on your Linux development machine.
- An `origin` remote pointing to your fork.
- An `upstream` remote pointing to the upstream embedded brains RTEMS repository.

You are ready to create feature branches, implement changes, and
submit pull requests.

## How to build RTEMS?

1. **Change to your working tree:**

    Change to the directory with your local working tree (see
    [How to create a local working tree](#how-to-create-a-local-working-tree)):

    ```{code-block} none
    ---
    linenos:
    ---
    $ cd rtems
    ```

2. **Build the RTEMS tools:**

    The architecture is `aarch64`:

    ```{code-block} none
    ---
    linenos:
    ---
    $ make tools-zynqmp
    ```

    This will run for about an hour. It will

    - install the needed Python packages with `uv` into `.venv/`
    - build and install the RTEMS tools in `tools/`

    Once the build is completed, check whether the compiler is installed
    and working:

    ```{code-block} none
    ---
    linenos:
    ---
    $ tools/6/bin/aarch64-rtems6-gcc --version
    ```

    ```{admonition} Which BSP for pre-qualification work?
    To ease pre-qualification work, the execution and debugging of tests
    should happen on an emulator. The freely available
    [pre-qualification packages](https://rtems-qual.io.esa.int/) use Gaisler
    BSPs (currently GR712rc, GR740 and GR765). These are SPARC and RISC-V
    architectures. As emulator the SPARC Instruction set Simulator (SIS)
    is excellent but the debugging support could be improved.

    Therefore, the `aarch64/zynqmp_apu` BSP is used here. It supports four
    CPU cores (needed for some validation tests), can be emulated with QEMU
    and has good support for debugging with `gdb`. The downside is that
    this BSP supports currently only the full RTEMS while the qualified-only
    subset cannot be built. But this will not interfere with the
    pre-qualification work.
    ```

3. **Build RTEMS**

    ```{code-block} none
    ---
    linenos:
    ---
    $ make bsp-zynqmp
    ```

    This step takes only one minute and will

    - create a `config.ini` in the top-level directory
    - build and install RTEMS with `waf` in `rtems-zynqmp/`

    ```{tip}
    To remove all files produced by `make bsp-zynqmp` invoke
    `make clean-zynqmp`. If you want to get rid of every created file
    including the RTEMS tools, use `make distclean`.
    ```

4. **Look around:**

    - `rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/` -- contains the build
      of "normal" RTEMS, qualified and non-qualified together
    - `rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra-coverage/` --
      contains the build instrumented for coverage analysis
    - `rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/tests/` -- contains all
      tests. The executable unit and validation test suites are the files
      starting with `ts-*`.
    - `build-zynqmp/aarch64/zynqmp_apu-extra/testsuites/validation/`,
      `build-zynqmp/aarch64/zynqmp_apu-extra/testsuites/unit/` --
      contain the temporary build files produced by `./waf`. You can
      save the `./waf install` step by starting the executables (`*.exe`)
      directly from these directories.
    - `build-zynqmp/aarch64/zynqmp_apu-extra-coverage/testsuites/validation/`
      `build-zynqmp/aarch64/zynqmp_apu-extra-coverage/testsuites/unit/` --
      contain the temporary build files produced by `./waf` with coverage
      information.

## How to run a test on an emulator?

The following shell command executes the test suite `ts-validation-0.exe`
from the installed RTEMS with the `qemu` emulator:

```{code-block} none
---
linenos:
---
$ tools/6/bin/qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio \
  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -smp 4 \
  -kernel rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/tests/ts-validation-0.exe
```

````{note}
The command in this section has been tested with RTEMS 6 from ESA
QDP 6.2 and a `qemu-system-aarch64` version 7.0.9. Newer RTEMS versions
support newer `qemu-system-aarch64` (version 10.1.0) but the command line is
a bit different:

```{code-block} none
---
linenos:
---
$ tools/6/bin/qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio \
  -machine xlnx-zcu102 -m 4096 -smp 4 \
  -kernel rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/tests/ts-validation-0.exe
```
````

The test output format is described in the [*RTEMS Engineering Manual*
section *Test Framework* subsection *Test
Reporting*](https://docs.rtems.org/docs/main/eng/test-framework.html#test-reporting).
In short, lines starting with `F:` indicate failures. `F:<n>` in the
middle of a line states the number of failures. The number `<n>` should
be `0`. Check especially for `F:0` in the line at the end starting
with `Z:` as it contains the failure summary of the whole test suite.

Moreover, the test output should end with a line like the following one.
If this line is absent, this indicates that the test crashed:

```{code-block} none
---
linenos:
---
*** END OF TEST <test-name> ***
```

````{tip}
Once you changed a source code file, it is more efficient to just re-compile
the sources with `uv run ./waf` and then run the temporary files from the
build directory (`build-zynqmp/` instead of `rtems-zynqmp/`):

```{code-block} none
---
linenos:
---
$ tools/6/bin/qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio \
  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -smp 4 \
  -kernel build-zynqmp/aarch64/zynqmp_apu-extra/testsuites/validation/ts-validation-0.exe
```

This saves you the time to install the files with `uv run ./waf install`
and it is easier to see compiler warnings in the output.
````

## How to debug with QEMU and GDB?

1. **Prepare `gdb` invocation**

    `gdb` needs instructions during start up. Create a file named `aarch64.gdb`
    with the following content:

    ```{code-block} none
    ---
    linenos:
    ---
    target remote :1234
    set print pretty on
    set pagination off
    set confirm off
    load
    define reset
    monitor system_reset
    load
    end
    ```

2. **Start `qemu`**

    You need two terminals, in one start `qemu`. The command line is the same as
    above, just with the options `-s -S` appended:

    ```{code-block} none
    ---
    linenos:
    ---
    $ tools/6/bin/qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio \
      -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -smp 4 \
      -kernel rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/tests/ts-validation-0.exe \
      -s -S
    ```

    These options make `qemu` wait for `gdb` to connect.

3. **Start `gdb`**

    In the second terminal, change to the directory with your local working tree
    (see
    [How to create a local working tree](#how-to-create-a-local-working-tree)) and
    start `gdb` providing the very same executable as last argument as provided
    to `qemu` above:

    ```{code-block} none
    ---
    linenos:
    ---
    $ cd rtems
    $ tools/6/bin/gdb --command=aarch64.gdb \
      rtems-zynqmp/aarch64-rtems6/zynqmp_apu-extra/tests/ts-validation-0.exe
    ```

4. **Debug with `gdb`**

    This text is not an introduction to using `gdb`. Please use tutorials
    on the Internet if needed. There exists graphical front-ends to `gdb` such
    as `gdbgui`.

    The basics are to set breakpoints and then to execute the program till
    the first breakpoint is hit:

    ```{code-block} none
    ---
    linenos:
    ---
    (gdb) b Runner
    Breakpoint 1 at 0x4000bc28: file ../../../testsuites/validation/ts-default.h, line 116.
    (gdb) b RtemsMallocReqMalloc_TestVariant
    Breakpoint 2 at 0x400095ac: file ../../../testsuites/validation/tc-mem-rtems-malloc.c, line 368.
    (gdb) c
    Continuing.

    Thread 1 hit Breakpoint 1, Runner (arg=123456789)
        at ../../../testsuites/validation/ts-default.h:116
    116   test_runner_argument = arg;

    [...]

    (gdb) c
    Continuing.
    [Inferior 1 (process 1) exited normally]
    (gdb) quit
    ```

    You will see console output in the first terminal during debugging.
    The `quit` or `q` command terminates `gdb`.

```{admonition} Breakpoints in validation tests
Validation test code is generated from YAML files. Therefore, finding
the right names for setting breakpoints is sometimes difficult.

The tests use `Runner()` instead of `Main()` as entry function (see file
`testsuites/validation/ts-default.h` which is included in the test suite
files like `testsuites/validation/ts-validation-0.c` which in turn is
generated from `spec/testsuites/validation-0.yml`).

The test cases which made up the test suite are defined in
`spec/build/testsuites/validation/validation-0.yml`. The names of functions
for breakpoints can be found in those files, for example
`testsuites/validation/tc-mem-rtems-malloc.c`. This test case is controlled
by a generated table. Its test function `T_case_body_RtemsMallocReqMalloc()`
loops through all lines of that table and calls for each table entry
the function `RtemsMallocReqMalloc_TestVariant()`. This function
sets up all pre-conditions (as defined by the table entry),
calls the function under test `rtems_malloc()` through
`RtemsMallocReqMalloc_Action()` and finally calls several functions
which check for the post-conditions defined by the table entry.

Note that this test case (`tc-mem-rtems-malloc.c`) is generated from the
YAML file `spec/rtems/malloc/req/malloc.yml`.
```

## How to create coverage information?

```{admonition} How coverage data is retrieved from test runs?
Normally when you run a test instrumented for coverage for `gcov` on
your computer, files with the ending `.gcda` are created next to the
respective `.o` file during the test run. These `.gcda` files contain the
collected coverage data and are analyzed by `gcov` to produce the coverage
report.

When executing tests on hardware boards, these cannot create files on
your computer. Our tests instrumented for coverage store the data in
the machine under test and write them to the console as base64 encoded
data block once the test terminates. Try running the same test suite
once from the `zynqmp_apu-extra/` folder and once instrumented from
the `zynqmp_apu-extra-coverage/` folder. You will see the different
console output at the end of the test.

Essentially, the console output of one or several coverage tests must
be collected, the base64 data must be decoded and converted into
`.gcda` files. Afterwards, the coverage report can be produced as
usual.
```

1. **Create empty directories**

    Create two empty directories:

    ```{code-block} none
    ---
    linenos:
    ---
    $ rm -rf log coverage
    $ mkdir -p log coverage
    ```

    One will contain the console output of the test run(s), the other will
    be filled with the coverage report.

2. **Run the tests**

    If you have changed any source code, make sure to compile and link
    all the test executables with `uv run ./waf`. If you want to run the
    installed executables, use `uv run ./waf install`. Moreover, make sure
    to run the test(s) from the `zynqmp_apu-extra-coverage/` tree. Store
    the test output in a file in the `log/` directory, for example:

    ```{code-block} none
    ---
    linenos:
    ---
    $ tools/6/bin/qemu-system-aarch64 -no-reboot -nographic \
      -serial mon:stdio -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 \
      -smp 4 \
      -kernel build-zynqmp/aarch64/zynqmp_apu-extra-coverage/testsuites/validation/ts-validation-0.exe \
      | tee log/ts-validation-0.log
    ```

3. **Extract the coverage information**

    ```{code-block} none
    ---
    linenos:
    ---
    $ uv run specgcovr --destination-directory=coverage \
      --object-directory=build-zynqmp/aarch64/zynqmp_apu-extra-coverage/ \
      --gcovr=.venv/bin/gcovr --gcov=$${PWD}/tools/6/bin/aarch64-rtems6-gcov \
      --gcov-tool=tools/6/bin/aarch64-rtems6-gcov-tool log/*.log
    ```

4. **View the coverage results**

    Point a browser of your choice to the file `coverage/index.html` which
    is the entry point to the coverage report. For example:

    ```{code-block} none
    ---
    linenos:
    ---
    $ firefox coverage/index.html
    ```

    Unless otherwise noted, 100% line and branch coverage are required. This
    explicitly means all sub-conditions of a complex condition must be
    exercised. For example for `if (a > 2 && b < 7)` you need test cases
    for

    - `a <= 2, b = any value`
    - `a > 2, b < 7`
    - `a > 2, b >= 7`.

# Qualification engineering

## Overview

Usually your task is to pre-qualify a group of already existing functions –
such as all functions related to semaphores or all functions related to
events. At the very core you have to write an interface specification
for each public visible function or macro, write the requirements each such
function or macro must met, write validation tests which test that each
function/macro meets all its requirements and make sure code coverage goals
are reached. The typical workflow looks like this (the steps are described
in more detail later):

1. Create a new feature branch for your work.

2. Put all functions and macros visible in the API in Doxygen groups.

3. Add all functions and code needed to the pre-qualifed API subset.

4. Create a specification directory tree for this function group.
   In the next steps you will create YAML files in this directories.
   These YAML files will contain the function specification, the
   requirements and the validation tests.

5. Write or generate interface specifications. The result is a YAML file
   for each public visible API function or macro describing the function,
   its parameters and the result. These YAML files can often been generated
   from the already existing Doxygen information found the C header files.

6. For each API function of macro:

   6.1 Write down all requirements the function or macro must meet. The result
       is a YAML file for each public visible API function or macro containing
       all its requirements.

   6.2 Write validation tests. These tests come in two flavours:

     * **Simple Validation Tests** These consists of not further structured
       test functions and are written in a extra YAML file. These are
       appropriate for macros and functions which do a simple computation
       with a single input and output condition.

     * **Action Items** These consist of pre- and post-conditions and
       a table relating the conditions to each other. The whole and often
       extensive test logic is the automatically generated for you.

   6.3 Generate C- and doc-files from the YAML files written above.
       You must add the generated tests to an existing test suite or
       create a new test suite for them once.

   6.4 Compile and run the tests

   6.5 Debug and fix test failures

   6.6 View coverage data

7. Create a pull request once you work is completed, tests and coverage
   goals are reached.

Finally, performance and memory benchmarks may be needed.

```{admonition} Examples
Examples of already pre-qualified function groups are often helpful.

[**Base Definitions**](https://docs.rtems.org/doxygen/main/group__RTEMSAPIBaseDefs.html)
define commonly used macros. This is a good example for writing
simple requirements and simple validation tests.

* `cpukit/include/rtems/score/basedefs.h` – header file

* `spec/rtems/basedefs` – specification directory tree contain all the
  YAML files created for pre-qualification

* `spec/rtems/basedefs/if/array-size.yml` – interface specification of
  the `RTEMS_ARRAY_SIZE` macro

* `spec/rtems/basedefs/req/array-size-0.yml` – requirement of the
  `RTEMS_ARRAY_SIZE` macro, note that some macros require several
  requirements

* `spec/rtems/basedefs/val/basedefs.yml` – defines many simple validation
  tests. The one of the `RTEMS_ARRAY_SIZE` macro starts at line 231.
  Note that `$${../if/array-size:/name}` is a substitution, it substitutes
  the value of the key `name` from the file `../if/array-size.yml` which
  happens to be `RTEMS_ARRAY_SIZE`. `$${.:/step}` is substitute by a number
  counting the `T_step_*` check macros in the C file generated from this
  YAML file.

* `testsuites/validation/tc-basedefs.c`  – the corresponding generated
  validation test file

* `spec/build/testsuites/validation/validation-no-clock-0.yml` – the YAML
  file which defines the test suite to which the validation test belongs

* `testsuites/validation/ts-validation-no-clock-0.c` – main C file of the
  test suite, see also `testsuites/validation/ts-default.h`

* `spec/testsuites/validation-no-clock-0.yml` – defininition of the test
  suite file `ts-validation-no-clock-0.c` itself

* `spec/build/testsuites/validation/grp.yml` – this group defines which
  test suites exist.

[**Rate Monotonic Manager**](https://docs.rtems.org/docs/main/c-user/rate-monotonic/index.html#rate-monotonic-manager)
from the Classic API executes a job periodically. This is a good example
for action requirements.

* `cpukit/include/rtems/rtems/ratemon.h` – header file

* `cpukit/rtems/src/ratemoncreate.c`, `cpukit/rtems/src/ratemoncancel.c`,
  `cpukit/rtems/src/ratemongetstatus.c` – some of its implementation files
  (note that the validation tests must cover the code in further files
  to reach the code coverage goals)

* `spec/rtems/ratemon` – specification directory tree contain all the
  YAML files created for pre-qualification

* `spec/rtems/ratemon/req/create.yml` – one of its action requirement
  YAML files

* `testsuites/validation/tc-ratemon-create.c` – the corresponding
  generated validation test file

* `spec/build/testsuites/validation/validation-no-clock-0.yml` – the YAML
  file which defines the test suite to which the validation test belongs.
  This is the same as the one of the Base Definitions example above.
```

## How to create a feature branch?

A feature branch to accumulate all you changes is typically created like this:

```{code-block} none
---
linenos:
---
$ git branch $${my-new-branch-name} eb/next
```


## How to add Doxygen groups?

We will prepare this for you.

TODO

## How to add a function to the pre-qualifed subset?

We will prepare this for you.

TODO

## How to create a specification directory tree?

We will prepare this for you.

TODO

```{admonition} Content of spec-directory
(e.g. spec/rtems/ratemon/*)
TODO
```

## How to create interface specifications?

We will prepare this for you.

TODO

## How to write requirements?

See the [*RTEMS Software Engineering Manual* chapter *Software Requirements
Engineering*](https://docs.rtems.org/docs/main/eng/req/index.html#software-requirements-engineering).

We use the [Easy Approach to Requirements Syntax
(EARS)](https://docs.rtems.org/docs/main/eng/req/req-for-req.html#syntax)
to express requirements. This is fine for simple requirements. Yet, because
action requirements are broken into pre-conditions and post-conditions, the
requirement texts are also broken appart. The *when*, *while*, *if*, *where*
part appears at the pre-conditions while the *\<system name\> shall \<system
response\>* part appears at the post-conditions.

```{admonition} Where appears the text written in those YAML files?

The texts from the interface specifications appears in the generated
RTEMS header files, in the *RTEMS Classic API Guide* or the *RTEMS POSIX
API Guide* as well as in the *RTEMS Doxygen*. In a package it also appears
in the *Interface Control Document (ICD)*.

The texts from the requirements and the description of the tests are part
of *Test Reports (TR), Software Requirements Specification (SRS), Software
Unit and Integration Test Plan (SUITP), Software Validation Specification
(SVS)*. The also appear as comments in the generated C-files.
```

## How to write simple validation tests?

Follow the examples. Each test has an *action* part which contains the C code to
exercise the function or macro and a *check* part which should check for the
expected result(s). Each of these sections has a brief description. Moreover,
each such *check* part has a *links* part which links the check to one or
several requirement. In the end, all requirements must have at least one test.

Note that at the bottom of such a YAML file, are keys like

- `test-brief` to describe the whole test case,
- `test-includes` to define header files to be included,
- `test-support` to contain code which is put at the top of the generated
   C file, and
- `test-target` the name of the C file to be generated.

Consider also that newly generated C test case files must be added to a test
suite in a YAML file (see the examples above).

The test case base on the RTEMS test framework as described in the [*RTEMS
Software Engineering Manual* chapter*Software Test
Framework*](https://docs.rtems.org/docs/main/eng/coding.html#coding-standards).
This permit the use of test fixtures. It is helpful to have a look at the
*Test Checks* and the *Log Message* in that chapter.

The RTEMS coding rules apply, see [*RTEMS Software Engineering Manual* chapter
*Coding Standards*](https://docs.rtems.org/docs/main/eng/test-framework.html#software-test-framework).

```{admonition} Unit vs. validation tests

TODO: Code coverage, Unit vs. Validation Tests / White box vs. Black box tests

TODO: Testing happens only on API level – no units with mocks,
In some cases tests manipulate RTEMS internal data structure to stimulate tests.
```

## How to write action requirements?

TODO

## How to generate C code from the YAML files?

TODO

## How to add test cases to test suites?

TODO

```{admonition} Selecting the right Validation Test Suite
Not all test cases of a function group need to be part of the same test
suite. It depends on the requirements a particular test has on the
executable. For example, a test may require the usual clock ticks, other
required no clock to "manually" trigger the clock tick as part the test
execution, others may need exactly one CPU, others at least three.
```

## How to create a test suites?

TODO

## How to compile and run the tests?

It is usually enough to execute

```{code-block} none
---
linenos:
---
$ uv run ./waf
```

If you need to track down compiler or link errors it is advisable to add
the `-v` option for verbose output:

```{code-block} none
---
linenos:
---
$ uv run ./waf -v
```

Make sure to run the exeutables from the `build-zynqmp` folder when you
do not install them with `$ uv run ./waf install`. In doubt see the section
[How to build RTEMS?](#how-to-build-rtems)

## How to run a test suite?

See the section [How to run a test on an emulator?](#how-to-run-a-test-on-an-emulator)

## How to debug tests?

See the section [How to debug with QEMU and GDB?](#how-to-debug-with-qemu-and-gdb)

## How to generate a code coverage?

See the section [How to create coverage information?](#how-to-create-coverage-information)

## How to create a pull request?

Make sure, everything compiles and links, the tests are running without
reporting failures and the code coverage goals are reached. Moreover,
make sure you have commmited  all your changes.

1. **Push your branch**

   Push your feature branch to your personal fork of the embedded brains
   RTEMS repository:

   ```{code-block} none
   ---
   linenos:
   ---
   $ git push -u origin $${my-new-branch-name}
   ```

   This will create a copy of your feature branch at your personal repository
   fork and set your feature branch to track that branch.

2. **Create a pull request**

   Login to you GitHub account and surf to the fork of the repository. Select
   the your feature branch. GitHub will offer to create a *Push Request* for it.
   As the target branch at the embedded brains RTEMS repository select
   `eb/next`. Give your pull request a name and add a short description. It
   is advisable to set the pull request to *draft* state initially.

   The click on *Create pull request*.

3. **Check and fix errors**

   You should see your new pull request, now. If not, surf to the [embedded
   brains RTEMS repository at GitHub](https://github.com/embedded-brains/rtems)
   choose the *pull request* tab and select your pull request.

   Wait till all CI jobs are completed. If there are any errors, please,
   fix those.

   Wait till *Copilot* finishes its review (you will get an email). If
   the review does not start automatically, on right side at the top
   *Copilot* appears as possible reviewers. Click on the tiny circle
   symbol right of it.

   Check all its review comments, fix the relevant ones and close the
   review comments you have examined.

4. **Push your fixes**

   Assuming you have made fixes at you local working tree and have committed
   those fixes. Push your fixes again to your local fork of the repository.
   This will automatically update the pull request:

   ```{code-block} none
   ---
   linenos:
   ---
   $ git push
   ```

   If need be, use `--force`.

   Afterwards, repeat with step 3. till all issues are resolved.

5. **Have you pull request merged**

   Once, all issue found by CI jobs and *Copilot* are resolved, remove
   the *draft* status. embedded brains staff will review you pull request
   and merge it.
