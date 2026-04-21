<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# Repository overview

This repository contains documentation sources in the `src` directory and
specification items stored in `*.yml` files.

Specification items are identified by a UID which is defined by the file path
relative to a base directory without the `.yml` extension.  The base
directories are all `spec` directories and the direct subdirectories of
`config`.  The specification items are connected through links which may
contain role-specific extra information.

# Document generation

Documents are generated using
[specmake](https://github.com/specthings/specmake) tools.

The specification items may contain text values in reStructuredText or MyST
Markdown format.

The document generation is defined by specification items. The format of
specification items is defined by a hierarchical type system. The documentation
generator verifies the specification item format before specification items are
used to build documents.

For the document generation, a flexible variable substitution is used defined
by the following Python regular expression:

```
^\$\{([a-zA-Z0-9._/-]+|\*)(:[\[\]a-zA-Z0-9._/-]+)(:[^${}]*)?\}$
```

The variable substitution pattern contains three groups:

1. The first group defines the identifier to get the associated specification
   item. The identifier can be an absolute item UID or a UID relative to the
   current item. The identifier `.` denotes the current item. The identifier
   `*` denotes the item of the mapper object used to perform the substitution.

2. The second group defines the attribute path. The attribute path may
   reference the item data directly or invoke a software-defined method.

3. The optional third group defines arguments or value transformers.

For example, consider the specification item with UID `A`:

```yaml
a:
  b: c
d:
  - e
  - f
```

In addition, the specification item with UID `B`:

```yaml
g: h
i: ${.:/g}
j: ${/A:/a/b}
k: ${/A:/d[1]}
```

The substituted value of item `B` of key `i` is `h`, of key `j` is `c`, and of
key `k` is `f`.

# General Code Review Standards

## License and Copyright Compliance

- Every file shall have an SPDX-License-Identifier at the beginning of the
  file.

- Every file shall have a copyright statement at the beginning of the file.

## Content Guidelines

- Use British English, but prefer -ize/-ization spellings and allow "license".

- In `*.md` files, the MyST Markdown format shall be used.

- In `*.rst` files, the
  [reStructuredText format compatible with the Sphinx documentation framework](https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html#rst-primer)
  shall be used.

- In `*.pdf` files, embedded fonts shall have an open source licence.

- In `*.yml` files:

  - Where the `glossary-type` key has the value `term` and the value of the
    `term` key is an acronym (for example FB for "Foo Bar"), the value of the
    `text` key shall use the following phrase pattern:

    This term is an acronym for Foo Bar.

  - Where `text` keys are present, the value shall be in MyST Markdown format.

- In `*.md`, `*.rst`, and `*.yml` files, except
  `.github/copilot-instructions.md`, the following terms shall not be used:

  - and/or

  - e.g.

  - etc.

  - i.e.

- In requirement specification items in `*.yml` files, normative requirements
  shall be written in the Easy Approach to Requirements Syntax
  ([EARS](https://alistairmavin.com/ears/)).

## File and Directory Naming Conventions

- The following file and directory names and name patterns are exceptions:

  - `*.patch`
  - `CODE_OF_CONDUCT.md`
  - `CONTRIBUTING.md`
  - `DCO.txt`
  - `LICENSES`
  - `Makefile`
  - `README.md`

- For all other file and directory names the following rules shall apply:

  - File and directory names shall use lower case
    [ASCII](https://en.wikipedia.org/wiki/ASCII) characters.

  - File and directory name parts shall be separated by dashes.
