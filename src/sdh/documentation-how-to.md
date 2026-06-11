% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Documentation how-to

This document describes how to write and format documentation within the RTEMS
ECSS documentation project. It covers formatting, style, licensing, custom
markup extensions, and building the documentation locally.

## File formats

The project uses two markup formats:

- **MyST (Markdown)**: Used for all new documentation files.

- **reStructuredText (reST)**: Maintained for existing documentation files.

All new documentation files shall use MyST Markdown.

## File templates and headers

Every documentation file shall start with a license and copyright header. The
preferred license for documentation is `CC-BY-SA-4.0`.

### MyST header template

For MyST Markdown (`*.md`) files, the header shall be written as Markdown
comments starting with `%` on a line by itself:

```{code-block} none
---
linenos:
---
% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) <YEARS> <COPYRIGHT HOLDER>
```

### reST header template

For reStructuredText (`*.rst`) files, the header shall be written as reST
comments starting with `..`:

```{code-block} rst
---
linenos:
---
.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) <YEARS> <COPYRIGHT HOLDER>
```

Replace `<YEARS>` with the first year of substantial contribution to the file,
and optionally the last year of modification if they differ (for example
`2020, 2026`). Replace `<COPYRIGHT HOLDER>` with the name of the copyright
holder.

## Style and formatting guidelines

Adhering to style guidelines is critical to ensure readability, consistent
rendering, and clean version control diffs.

### Line length

To maintain readability and clean version control, limit the line length of
text and code:

- **MyST (Markdown)**: Text in `*.md` files shall wrap at 79 characters, which
  is automatically enforced by `mdformat`.

- **reStructuredText (reST)**: Text in `*.rst` files shall wrap at 79
  characters.

- **Exceptions**: Long URLs or specific code blocks where wrapping breaks the
  syntax.

### Heading hierarchy and casing

- **Casing**: All section headers and titles shall use **sentence case**. Do
  not use [title case](https://en.wikipedia.org/wiki/Title_case).

  - Correct: `# Documentation how-to`

  - Incorrect: `# Documentation How-To`

- **MyST headings**: Use the standard Markdown heading markers:

  - Level 1: `# Heading`

  - Level 2: `## Heading`

  - Level 3: `### Heading`

  - Level 4: `#### Heading`

- **reST headings**: Use the following decorators for headings:

  - Level 1 (Title): Asterisks (`*`) under the text.

    ```{code-block} rst
    ---
    linenos:
    ---
    Title text
    **********
    ```

  - Level 2 (Section): Equal signs (`=`) under the text.

    ```{code-block} rst
    ---
    linenos:
    ---
    Section text
    ============
    ```

  - Level 3 (Subsection): Dashes (`-`) under the text.

    ```{code-block} rst
    ---
    linenos:
    ---
    Subsection text
    ---------------
    ```

  - Level 4 (Sub-subsection): Tildes (`~`) under the text.

    ```{code-block} rst
    ---
    linenos:
    ---
    Sub-subsection text
    ~~~~~~~~~~~~~~~~~~~
    ```

Ensure the decorator line is exactly the same length as the heading text.

### Indentation and whitespace

- Use spaces only. Do not use tab characters.

- Use 2 spaces for one indentation level.

- Avoid trailing whitespace at the end of lines.

- Do not use more than one blank line in a row.

- Separate list items by one blank line.

- Separate code blocks by one blank line from the surrounding text.

### reST substitutions

Do not use the
[reST substitutions](https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html#substitutions).
In particular, do not add new items to `src/common/include/abbreviations.rst`.

## Document generation and specification items

Documents are generated using
[specmake](https://github.com/specthings/specmake) tools. The documentation
build system employs a custom variable expansion.

The document generation is defined by specification items. The format of
specification items is defined by a hierarchical type system, see
{ref}`SpecificationItemHierarchy`. The documentation generator verifies the
specification item format before specification items are used to build
documents. Specification items may contain text values in reStructuredText or
MyST format.

For the document generation, a flexible `@@{<variable-pattern>}` or
`$${<variable-pattern>}` variable substitution is used. For MyST text, the
`@@{<variable-pattern>}` style is preferred to avoid formatting issues with the
`mdformat` tool. The `<variable-pattern>` is defined by the following Python
regular expression:

```{code-block} none
---
linenos:
---
^\$\{([a-zA-Z0-9._/-]+|\*)(:[\[\]a-zA-Z0-9._/-]+)(:[^$${}]*)?\}$
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

```{code-block} yaml
---
linenos:
---
a:
  b: c
d:
  - e
  - f
```

In addition, the specification item with UID `B`:

```{code-block} yaml
---
linenos:
---
g: h
i: $${.:/g}
j: $${/A:/a/b}
k: $${/A:/d[1]}
```

The substituted value of item `B` of key `i` is `h`, of key `j` is `c`, and of
key `k` is `f`.

### Documentation variables and placeholders

In general, for documentation variables and placeholders use the
`<my-placeholder>` notation.

For command-line examples, use the `$${my_placeholder}` notation. Please note
that a `$${` sequence is subject to the variable substitution by the
documentation build system. For documentation variables and placeholders, you
have to escape the `$`. For example, in the documentation sources write
`$$$${my_placeholder}` so that it gets displayed as `$${my_placeholder}`.

### Glossary references

To reference a glossary term, use the following syntax:

- Singular term: `$${/glossary/<term-id>:/term}`

- Plural term: `$${/glossary/<term-id>:/plural}`

Examples:

- `... using the $${/glossary/rtems:/term} operating system.`

- `... for various $${/glossary/api:/plural}.`

Glossary terms are defined by {ref}`SpecTypeGlossaryTermItemType` items.
Glossary terms shall be a member of a {ref}`SpecTypeGlossaryGroupItemType` item
through a {ref}`SpecTypeGlossaryMembershipLinkRole` link. The general glossary
of terms is represented by the `/glossary/group` item.

### Document citations

To cite other documents:

- Long citation (full title and reference):

  `$${/pkg/<doc-id>:/cite-long}` or

  `$${<doc-id>:/cite-long}`

- Short citation (reference code):

  `$${/pkg/<doc-id>:/cite-short}` or

  `$${<doc-id>:/cite-short}`

- Group citations:

  `$${/pkg/component:/cite-group:<citation-group-key>}`

  The `<citation-group-key>` is defined by the
  {ref}`SpecTypeCitationGroupMemberLinkRole` links used to populate a citation
  group. Group citations may be presented as a list by setting the `flat=0`
  option, for example
  `$${/pkg/component:/cite-group:<citation-group-key>,flat=0}`. Group citations
  to {ref}`SpecTypeSphinxDocumentItemType` support `label`, `name`, and `path`
  options.

Examples:

- `... as defined in the $${/ref/ecss/e-st-40c:/cite-long}.`

- `... in the $${/pkg/component:/cite-group:svr}.`

{ref}`SpecTypeReference` and {ref}`SpecTypeSphinxDocumentItemType` items can be
cited.

### Component paths and inputs

To resolve build-time paths or inputs, use the relative component syntax:

- Path relative to the target directory of the document currently generated:
  `$${.:/component/documentation-directory:relpath %(*:/directory)}`

- Archive name: `$${.:/input/archive/file:basename}`

### Conditional blocks

You can conditionally include documentation blocks using the
push/pop-enabled-by syntax:

Example in MyST:

```{code-block} none
---
linenos:
---
@@{.:/push-enabled-by:pkg.feature.qual}
This text is only included if qualification features are enabled.
@@{.:/pop-enabled-by}
```

## Code blocks and command examples

### Code blocks formatting

- In MyST, use `{code-block} <language>` syntax with the `linenos:` option for
  code blocks.

- In reST, use the `.. code-block:: <language>` directive with the `:linenos:`
  option.

Example in MyST:

````{code-block} none
---
linenos:
---
```{code-block} c
---
linenos:
---
int main( void )
{
  return 0;
}
```
````

### Command-line examples

For commands executed in a shell:

- Use MyST `{code-block} none` (or reST `.. code-block:: none`) with the
  `linenos:` option.

- Prefix command lines with `$` to distinguish them from the command output.

- For documentation variables or placeholders used in command-line examples,
  use the `$${my_placeholder}` notation. In case copy and paste is blindly
  used, this still gives a valid shell syntax with hopefully undefined
  variables.

Example in MyST:

````{code-block} none
---
linenos:
---
Let `$$$${foobar_directory}` be the foobar directory. Execute the following
command in a shell:

```{code-block} none
---
linenos:
---
$ cd $$$${foobar_directory}/some/more
$ command with args
output of command
```
````

## Local validation and formatting

Before submitting your documentation changes, perform formatting checks and
verify the documentation build locally.

### Auto-formatting

Format all `*.md` files using the `mdformat` tool to ensure it adheres to the
wrapping and layout rules configured in `.mdformat.toml`. Run the following
command:

```{code-block} none
---
linenos:
---
$ mdformat src/sdh/documentation-how-to.md
```

To only check the formatting without modifying the file:

```{code-block} none
---
linenos:
---
$ mdformat --check src/sdh/documentation-how-to.md
```

### Verification build

To verify that the documentation builds correctly and all references are
resolved, run `make`.
