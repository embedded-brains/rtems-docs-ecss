% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Specification how-to

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
