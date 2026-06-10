% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Specification how-to

## How to prepare your computer?

You should have a Linux computer with these packages installed:

- a working C, C++ and Python development environment -- see section
  [POSIX Hosts](https://docs.rtems.org/docs/main/user/hosts/posix.html#posix-hosts)
  in the
  [RTEMS User Manual](https://docs.rtems.org/docs/main/user/)
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
of RTEMSs. Indeed, this would complicate the workflow as building and
changing a package takes much time. It is sufficient to only use a
dedicated branch of
[embedded brains RTEMS repository](https://github.com/embedded-brains/rtems).

This branch contains:

- The [RTEMS baseline](https://gitlab.rtems.org/rtems/rtos/rtems)
- The RTEMS specification (in the `spec/`-folder)
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
   - The appropriate branch is the default one (`esa/<something>`)
   - Create the fork.

   Let `$${your_github_user}` be the name of your GitHub user. After
   completion, GitHub will create a copy of the repository under your account:

   ```text
   https://github.com/$${your_github_user}/rtems
   ```

3. **Clone Your Fork**

   Open a terminal on your Linux machine and clone your fork:

   ```bash
   git clone git@github.com:$${your_github_user}/rtems.git
   ```

   Alternatively, if you prefer HTTPS:

   ```bash
   git clone https://github.com/$${your_github_user}/rtems.git
   ```

4. **Enter the Repository Directory**

   ```bash
   cd rtems
   ```

5. **Add the Original Repository as an Upstream Remote**

   Configure the original embedded brains repository as an additional
   remote. This allows you to synchronize your fork with the latest
   changes from the main project.

   ```bash
   git remote add upstream https://github.com/embedded-brains/rtems.git
   ```

6. **Verify the Remote Configuration**

   Verify that both remotes are configured correctly:

   ```bash
   git remote -v
   ```

   The output should be similar to:

   ```text
   origin    git@github.com:$${your_github_user}/rtems.git (fetch)
   origin    git@github.com:$${your_github_user}/rtems.git (push)
   upstream  https://github.com/embedded-brains/rtems.git (fetch)
   upstream  https://github.com/embedded-brains/rtems.git (push)
   ```

7. **Synchronize with the Upstream Repository**

   Before starting development, fetch the latest changes from the
   upstream repository:

   ```bash
   git fetch upstream
   ```

   To update your local ESA branch:

   ```bash
   git checkout esa/<something>
   git pull --rebase upstream esa/<something>
   ```

   **Alternatively**, you can visit the web page of your fork and press
   the **Sync Fork** button on the top right and then fetch the latest
   changes from your fork repository:

   ```bash
   git fetch origin
   ```

   To update your local ESA branch:

   ```bash
   git checkout esa/<something>
   git pull --rebase origin esa/<something>
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

## How to build RTEMS with the pre-qualified subset?

1. Change to the directory with your local working tree (see
   [How to create a local working tree](#how-to-create-a-local-working-tree)):

    ```bash
    cd rtems
    ```

2. Build the RTEMS tools for the `aarch64` architecture:

    ```bash
    make tools-zynqmp
    ```

    This will run for about an hour. It will

    * install the needed Python packages with `uv` into `.venv/`
    * build and install the RTEMS tools in `tools/`

    Once the build is completed, check whether the compiler is installed
    and working:

    ```bash
    tools/6/bin/aarch64-rtems6-gcc --version
    ```

3. Build RTEMS

    ```bash
    make bsp-zynqmp
    ```

    This step takes only one minute and will

    * create a `config.ini` in the `rtems/` directory
    * build and install RTEMS with `waf` in `rtems/workspace/`

    ```{tip}
    To remove all files produced by `make bsp-zynqmp` invoke `clean-zynqmp`.
    If you want to get rid of every created file including the RTEMS tools,
    use `distclean-zynqmp`.
    ```

4. Look around:

    * `workspace/aarch64-rtems6/zynqmp_apu-extra/` -- contains the build
      of "normal" RTEMS, qualified and non-qualified together
    * `workspace/aarch64-rtems6/zynqmp_apu-extra-coverage/` --
      contains the build instrumented for coverage analysis
    * `workspace/aarch64-rtems6/zynqmp_apu-extra/tests/` -- contains all
      tests. The executable unit and validation test suites are the files
      starting with `ts-*`.

Run a test "manually" on the SIS (SPARC Instruction set Simulator):

```bash
tools/6/bin/sis -gr740 -extirq 10 -dumbio -r -m 4 \
    workspace/sparc-rtems6/gr740-qual-only/tests/ts-validation-0.exe
```

The test output format is described in the [*RTEMS Engineering Manual*
section *Test Framework* subsection *Test Reporting*](
https://docs.rtems.org/docs/main/eng/test-framework.html#test-reporting).
In short, lines starting with `F:` indicate failures.  `F:<n>` in the
middle of a line states the number of failures. The number `<n>` should
be `0`.  Check especially for `F:0` in the line at the end starting
with `Z:` as it contains the failure summary of the whole test suite.

Moreover, the test output should end with a line like the following one.
If this line is absent, this indicates that the test crashed:

```bash
*** END OF TEST <test-name> ***
```

**How to debug with SIS and GDB: TODO (Sebastian?)**

Once you have made changes to the RTEMS code, you can rebuild RTEMS with

```bash
make bsp-zynqmp
```
