% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Specification how-to

## How to prepare your computer

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

## How to create a local working tree

This project uses the GitHub fork-and-pull-request workflow. Before
making any changes to the pre-qualified RTEMS, create a personal fork of the
[embedded brains RTEMS repository](https://github.com/embedded-brains/rtems)
on GitHub and clone it to your local development machine. This
how-to guide walks you through the process of creating a working tree
on your machine. The workflow to create a pull request is described
in another how-to.

Aim:

- Have a checked-out working tree on your local machine.

Prerequisites:

- A GitHub account
- SSH access configured for GitHub (recommended)
- See [How to prepare your computer](#how-to-prepare-your-computer)

Steps:

1. **Sign in to GitHub**

   Open your web browser and sign in to your GitHub account.

1. **Create a Fork**

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

1. **Clone Your Fork**

   Open a terminal on your Linux machine and clone your fork:

   ```bash
   git clone git@github.com:$${your_github_user}/rtems.git
   ```

   Alternatively, if you prefer HTTPS:

   ```bash
   git clone https://github.com/$${your_github_user}/rtems.git
   ```

1. **Enter the Repository Directory**

   ```bash
   cd rtems
   ```

1. **Add the Original Repository as an Upstream Remote**

   Configure the original embedded brains repository as an additional
   remote. This allows you to synchronize your fork with the latest
   changes from the main project.

   ```bash
   git remote add upstream https://github.com/embedded-brains/rtems.git
   ```

1. **Verify the Remote Configuration**

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

1. **Synchronize with the Upstream Repository**

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
