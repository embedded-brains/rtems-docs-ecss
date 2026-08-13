% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(QualEngEnvironment)=

# Set up the qualification engineering environment

(PrepareComputer)=

## Prepare your computer

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
For building packages, Ubuntu Linux containers are used. This version
of Ubuntu is the supported basis for all pre-qualification work. You
can find the Ubuntu version and all packages needed in the
[Dockerfile](https://github.com/embedded-brains/rtems-package/blob/main/.github/container/Dockerfile).
```

(CreateWorkingTree)=

## Create a local working tree

This project uses the GitHub fork-and-pull-request workflow. Before making any
changes to the pre-qualified RTEMS, create a personal fork of the
[embedded brains RTEMS repository](https://github.com/embedded-brains/rtems) on
GitHub and clone it to your local development machine. This how-to guide walks
you through the process of creating a working tree on your machine. The
workflow to create a pull request is described in another how-to.

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
- A [`Makefile`](https://github.com/embedded-brains/rtems/blob/eb/next/Makefile)
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
- See {ref}`PrepareComputer`

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

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   https://github.com/$${your_github_user}/rtems
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

3. **Clone Your Fork**

   Open a terminal on your Linux machine and clone your fork:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git clone git@github.com:$${your_github_user}/rtems.git
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   Alternatively, if you prefer HTTPS:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git clone https://github.com/$${your_github_user}/rtems.git
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

4. **Enter the Repository Directory**

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ cd rtems
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

5. **Add the Original Repository as an Upstream Remote**

   Configure the original embedded brains repository as an additional remote.
   This allows you to synchronize your fork with the latest changes from the
   main project.

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git remote add upstream https://github.com/embedded-brains/rtems.git
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

6. **Verify the Remote Configuration**

   Verify that both remotes are configured correctly:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git remote -v
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   The output should be similar to:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   origin    git@github.com:$${your_github_user}/rtems.git (fetch)
   origin    git@github.com:$${your_github_user}/rtems.git (push)
   upstream  https://github.com/embedded-brains/rtems.git (fetch)
   upstream  https://github.com/embedded-brains/rtems.git (push)
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

7. **Synchronize with the Upstream Repository**

   Before starting development, fetch the latest changes from the upstream
   repository:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git fetch upstream
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   To update your local `eb/next` branch:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git checkout eb/next
   $ git pull --rebase upstream eb/next
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   **Alternatively**, you can visit the web page of your fork and press the
   **Sync Fork** button at the top right and then fetch the latest changes from
   your fork repository:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git fetch origin
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   To update your local `eb/next` branch:

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ git checkout eb/next
   $ git pull --rebase origin eb/next
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

Note: The RTEMS commit history is always linear. There are no merge commits
allowed. Consider this especially when resolving Git conflicts.

As a result, you now have:

- A fork of the embedded brains RTEMS repository in your GitHub account.
- A local clone on your Linux development machine.
- An `origin` remote pointing to your fork.
- An `upstream` remote pointing to the upstream embedded brains RTEMS
  repository.

You are ready to create feature branches, implement changes, and submit pull
requests.

(CreateWorkspace)=

## Set up a workspace application

For pre-qualification engineering tasks, the `eb/next` branch of RTEMS contains
a recommended working environment consisting of:

- An RTEMS tools installation for a @`/glossary/target-arch:/term`

- An installed reference @`/glossary/bsp:/term`

- A `Makefile`-based workspace application

The tools and the BSP need to be built and installed only during the initial
setup. Occasionally, an update may be required. For an overview of the `make`
tool driving this process, see {ref}`ToolMake`.

```{figure} ../images/workspace-application-components.*
---
alt: Overview of the workspace application's components and how they relate
width: 70%
---
Workspace application components
```

The root `Makefile` builds the tools installation, the reference BSP
installation, and the workspace application. The `spec/build` specification
configures how the `bsps`, `cpukit`, and `testsuites` sources are compiled into
the reference BSP installation. The workspace application itself is copied from
`src/work-template`, cross-compiled with the tools installation, and linked
against the reference BSP installation; the specific function or macro under
pre-qualification is generated from its `spec/rtems` item.

1. **Change to your working tree:**

   Change to the directory with your local working tree, see
   {ref}`CreateWorkingTree`.

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ cd rtems
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

2. **Optionally, remove an existing working environment:**

   To get rid of an existing working environment, run `make distclean`.

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ make distclean
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   You have to remove an existing workspace application manually. Please note
   that these files are supposed to be *not under version control*, so removing
   them could be irreversible.

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ rm -rf Makefile.work work
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

3. **Build the RTEMS tools, the BSP installation, and the workspace
   application:**

   Run `make`.

   ```{raw} latex
   \begin{footnotesize}
   ```

   ```{code-block} none
   ---
   linenos:
   ---
   $ make
   ```

   ```{raw} latex
   \end{footnotesize}
   ```

   This will run for about an hour. It will:

   - Install the needed Python packages with `uv` into `.venv`.

   - Build and install the RTEMS tools in `work-tools`.

   - Build and install the reference BSP in `work-rtems`.

   - If necessary, copy the `Makefile.work` file from a template directory to
     the repository root directory.

   - If necessary, copy the `work` directory from a template directory to the
     repository root directory.

   - Build the workspace application.

   The make process should complete successfully.

(RunWorkspaceApplication)=

## Run the workspace application

Make sure you performed the steps to set up the workspace application outlined
in {ref}`CreateWorkspace`. To run the workspace application, run `make run`.
This executes the workspace application under QEMU instead of on physical
target hardware, see {ref}`ToolQemu`.

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ make run
```

```{raw} latex
\end{footnotesize}
```

(DebugWorkspaceApplication)=

## Debug the workspace application

Make sure you performed the steps to set up the workspace application outlined
in {ref}`CreateWorkspace`. To debug the workspace application using
@`/glossary/gdb:/term` you need two terminals, see {ref}`ToolGdb` for an
overview of the tool. In one terminal, run `make debug`:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ make debug
```

```{raw} latex
\end{footnotesize}
```

In another terminal, run `make gdb`.

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ make gdb
```

```{raw} latex
\end{footnotesize}
```

(CreateCoverageReport)=

## Create a coverage report

Make sure you performed the steps to set up the workspace application outlined
in {ref}`CreateWorkspace`. To generate a coverage report, run `make coverage`:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ make coverage
```

```{raw} latex
\end{footnotesize}
```

The coverage report is located in `work-coverage/index.html`.
