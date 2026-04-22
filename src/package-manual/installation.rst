.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2020, 2026 embedded brains GmbH & Co. KG

.. include:: ../include/abbreviations.rst

.. _GettingStarted:

Installation instructions
*************************

The getting started section gives you step by step instructions which enable
you to build a simple example application using the package.

.. _PrepareHostComputer:

Prepare the host computer
=========================

The package contains a binary distribution of tools such as the cross
${/glossary/gnu:/term} Binutils and ${/glossary/gcc:/term}.  The tools were
built on an `Ubuntu 24.04 LTS <https://releases.ubuntu.com/noble/>`__
machine.  The tools should run on any Linux distribution which provides a glibc
2.39 or later.

The package archive file :file:`${.:/input/archive/file:basename}` contains
third-party sources, Python modules, shell scripts, executables, build systems,
and other files.  Security scanners may find individual files suspicious.  For
example, the following archive files of the ${/glossary/gcc:/term} Go language
test suite contain oversized files and deeply nested file system paths:

- :file:`src/gcc/libgo/go/archive/tar/testdata/writer-big.tar`

- :file:`src/gcc/libgo/go/archive/tar/testdata/writer-big-long.tar`

- :file:`src/gcc/libgo/go/compress/bzip2/testdata/fail-issue5747.bz2`

- :file:`src/gcc/libgo/go/compress/gzip/testdata/issue6550.gz.base64`

Security software trying to recursively unpack the archives may have issues.

Debian and Ubuntu
-----------------

For normal use of the package, install the following packages:

.. code-block:: none
    :linenos:

    $$ apt-get install libncurses6 make pkg-config

If you want to build a User Test Report (see also :ref:`UserTestReports`),
install the following additional packages:

.. code-block:: none
    :linenos:

    $$ apt-get install git latexmk pipx python3 \
        texlive texlive-fonts-extra texlive-latex-extra

openSUSE
--------

On `openSUSE <https://www.opensuse.org/>`_ distributions install the *C/C++
Development* pattern.

Windows
-------

It is recommended to use the
`Windows Subsystem for Linux (WSL) <https://learn.microsoft.com/en-us/windows/wsl/install>`__
with an Ubuntu 24.04 distribution.

The package archive file :file:`${.:/input/archive/file:basename}` contains symbolic
links.  This may or may not cause issues on some Windows installations or
archive extraction programs.

${.:/push-enabled-by:pkg.feature.x86_64-w64}
As an alternative to the WSL, the package contains in the :file:`x86_64-w64`
directory tools based on `MinGW-w64 <https://www.mingw-w64.org/>`__.  They can
be used to compile RTEMS applications for the supported
${/glossary/target-arch:/plural}.  The :file:`pkg-config` tool is provided to
query the tool settings from a installed ${/glossary/bsp:/term}, see
:ref:`ToolFlags`.  The tools do not require third-party DLLs.  The package does
not contain build tools like :file:`make`.  The RTEMS Tools are not provided.
You can build them from source if needed.  You can build RTEMS BSPs and the
third-party libraries using a Python 3 installation from `python.org
<https://www.python.org/>`__ directly in a Windows command line.  There is no
`MSYS2 <https://www.msys2.org/>`__ or `Cygwin <https://www.cygwin.com/>`__
required.
${.:/pop-enabled-by}

Check the package integrity
===========================

This document may be digitally signed.  Check that the signatures are valid and
trustworthy.  This document corresponds to the package archive file
:file:`${.:/input/archive/file:basename}` which has an SHA512 digest of
``${.:/input/archive/sha512}``.  You should have obtained the archive file from
the same distribution channel as this document.  Check that the SHA512 digest
of the QDP archive file matches with the SHA512 digest documented in this
document.  If the digests do not match, then the archive file is not the right
one.

.. code-block:: none
    :linenos:

    $$ sha512sum ${.:/input/archive/file:basename}
    ${.:/input/archive/sha512}

Unpack the package archive
==========================

.. note::

    The current document uses relative links to documents of the package.
    Place the document into the top-level package directory so that the
    relative links resolve to the proper documents of the package.

It is recommended to unpack the package archive in the prefix directory
:file:`${.:/component/prefix-directory}`.  Other locations may work, but this
use case was not tested.  The documents use relative links to other documents
of the package so that browsing the documents in a relocated package works.
Let :file:`~/Downloads` be the directory containing the package archive
:file:`${.:/input/archive/file:basename}` and the current document
:file:`${.:/output-pdf:basename}`.  Use the following commands to unpack the
archive and place the current document into the intended location:

.. code-block:: none
    :linenos:

    $$ sudo mkdir -p ${.:/component/prefix-directory}
    $$ cd ${.:/component/prefix-directory}
    $$ sudo tar xf ~/Downloads/${.:/input/archive/file:basename}
    $$ sudo cp ~/Downloads/${.:/output-pdf:basename} ${.:/component/package-directory:basename}

.. _Examples:

Try out the examples
====================

It is recommended to try out the example programs.

${.:/sections:1:example}

.. _Docker:

Use the package in a Docker container
=====================================

This section explains how to set up a dockerised solution to use the package.
It allows using the package in any operating system supporting Docker.  The
Docker container presented below allows you to

- build the examples,

- run the examples and tests on a simulator, and

- create the user test reports (including running the tests provided by the
  package on your board and producing test reports usable for
  ${/glossary/ecss:/term} conform qualification).

When the package is used directly on the host computer, it is recommended to
unpack the package archive into the intended prefix directory
:file:`${.:/component/prefix-directory}`.  In our Docker scenario here, the
package is mounted at the prefix directory inside the Docker container.
However, on your host computer it can be in any location.  Let the absolute
path to the package location on your host be ``$${workspace}`` throughout this
section.

.. topic:: User IDs inside and outside of a container

    Our suggestion is to unpack the package archive outside the container and
    bind-mount the resulting directory inside the container when it is started.
    This has the advantage that you can view and edit the package files outside
    the container with your host tools while building examples, running
    executables on a simulator, and build the test reports inside the
    container.

    In such a scenario, one must carefully consider who owns a file which is
    visible inside the container and on the host.  If you use ``podman`` as
    container engine, a file owned by ``root`` inside the container is owned by
    the (non-root) user who started ``podman`` on the host.  Therefore, an
    ordinary user can unpack the package archive on the host and inside the
    container the ``root`` user is active.

    When Docker is used as container engine, the mapping is less clear.
    Especially, when the Docker daemon is running as ``root``, a file owned by
    ``root`` inside of the container is also owned by ``root`` on the host.  In
    such a case, the ``Dockerfile`` we propose permits the creation of a
    non-root user inside the container with the same user and group ID as the
    user on the host.

Follow these steps:

1. Create a :file:`Dockerfile` with the following content as non-root user in a
   directory of your choice:

   .. code-block:: none
       :linenos:

       FROM ubuntu:24.04
       ARG username=packageuser
       ARG groupname=packagegroup
       ARG userid
       ARG groupid
       RUN apt-get update && \
           env DEBIAN_FRONTEND=noninteractive apt-get -y upgrade && \
           env DEBIAN_FRONTEND=noninteractive apt-get -y install \
               git \
               latexmk \
               libncurses6 \
               make \
               pipx \
               pkg-config \
               python3 \
               texlive \
               texlive-fonts-extra \
               texlive-latex-extra && \
           apt-get -y clean && \
           rm -rf /var/cache/apt /var/lib/apt/lists/* && \
           if [ -n "$${userid}" ] ; then \
               groupadd --gid "$${groupid}" "$${groupname}" ; \
               useradd --comment "Package User" --gid "$${groupname}" \
                   --uid "$${userid}" --no-user-group --shell "$$(which bash)" \
                   --home-dir "/home/$${username}" --create-home "$${username}" ; \
           fi
       USER $${userid:-0}
       RUN pipx install uv

2. Build the container image identified by the tag name ``package-tag``.  If
   you use ``podman`` or ``docker`` with user ``root`` in the container, use
   the first command below (you can replace ``podman`` by ``docker``).  If you
   use ``docker`` and need a non-root user inside the container, use the second
   command instead (do not forget the point at the end of the command line):

   .. code-block:: none
       :linenos:

       # With root user in the container:
       $$ podman build --file Dockerfile --tag package-tag .

       # With non-root user in the container:
       $$ docker build --file Dockerfile --tag package-tag \
           --build-arg userid="$$(id -u)" --build-arg groupid="$$(id -g)" .

3. Extract the package archive as non-root user
   to any location of your choice.   Let `$${workspace}` be the absolute
   path to the directory where you want to unpack the archive:

   .. code-block:: none
       :linenos:

       # On the host/outside the container:
       $$ cd $${workspace}
       $$ tar xf ${.:/input/archive/file:basename}

4. Start the container through the following command, mounting the package
   content in your ``$${workspace}`` directory on the host to the
   :file:`${.:/component/deployment-directory}` directory inside the container.
   If you use ``podman``, simply replace ``docker`` by ``podman``:

   .. code-block:: none
       :linenos:

       # On the host/outside the container:
       $$ docker run -it --rm \
           --volume=$${workspace}/${.:/component/package-directory:basename}:${.:/component/deployment-directory} \
           package-tag bash

5. Check the user IDs inside and outside the container by creating a file
   inside the container and check that it belongs to the correct user
   on the host:

   .. code-block:: none
       :linenos:

       # In the container
       $$ ls -la ${.:/component/deployment-directory}
       $$ touch ${.:/component/deployment-directory}/test-file

       # On the host/outside the container:
       $$ ls -la $${workspace}/${.:/component/package-directory:basename}

6. Compile and execute the example as described in the previous sections.  If
   everything runs as expected, the Docker setup is correct.

.. topic:: Running tests on your hardware board

    To produce the user test reports (see also :ref:`UserTestReports`), the
    tests coming with the package must be executed on your hardware board.  For
    this purpose, you must provide a program or script in the container.  This
    program or script must execute a test on your hardware.  It will be given
    the path to an executable and it is expected to return the console output
    of the board during the test execution as standard output.

    This requires a communication from inside the container to the outside
    world.  Network connections from inside the container to an external
    listening server work out of the box.  You can also bind-mount files and
    UNIX socket if you consider the user IDs of those files inside and outside
    the container.  Accessing USB devices from inside the container is usually
    difficult.  If nothing works for you, consider using a virtual machine
    instead.
