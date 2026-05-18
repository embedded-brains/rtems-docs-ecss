.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2021 embedded brains GmbH & Co. KG

.. _InventorySCI:

Inventory of software configuration item
****************************************

This document may be digitally signed.  Check that the signatures are valid and
trustworthy.  This document corresponds to the package archive file
:file:`${.:/input/archive/file:basename}` which has an SHA512 digest of
``${.:/input/archive/sha512}``.  You should have obtained the archive file from
the same distribution channel as this document.  Check that the SHA512 digest
of the package archive file matches with the SHA512 digest documented in this
document.  If the digests do not match, then the archive file is not the right
one.

.. code-block:: none

    $$ sha512sum ${.:/input/archive/file:basename}
    ${.:/input/archive/sha512}

For an overview of the package archive content, see :ref:`Overview`.  The
package archive contains the package verification script
:file:`${.:/input/verify-package/file:relpath %(/pkg/component:/prefix-directory)}`
which has an SHA512 digest of ``${.:/input/verify-package/sha512}``.  This
script may be used to verify the files of the package after unpacking the
archive.  It may also be used to list the files of the package or to list the
files of the package with an SHA512 hash value of each file content.

${.:/subprocess:args=./%(.:/input/verify-package/file:basename) --help,cwd=%(.:/input/verify-package/file:dirname)}
