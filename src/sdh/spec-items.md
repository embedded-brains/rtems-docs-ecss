% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(SpecificationItems)=

# Specification items

## Overview

The document generation, the software specification, the build of software
components, and the package building is defined by specification items.
Specification items may contain dictionaries, lists, integers, floating-point
numbers, and strings. The format of these items is extensible, human readable,
machine readable, Git friendly, and can be customized according to
domain-specific needs. Each item is identified by an @{/glossary/uid:/term}.
The items are connected through {ref}`links <SpecTypeLink>` which may contain
role-specific extra information. This enables different views to a
specification item graph depending on the use case. All items are refinements
of the {ref}`root item type <SpecTypeRootItemType>`. The type hierarchy is
presented in the {ref}`SpecificationItemHierarchy`.

The [specthings](https://github.com/specthings) project provides Python
packages to work with specification items. The specification item types for
software, documentation, and package building provided by
[specware](https://github.com/specthings/specware) and
[specmake](https://github.com/specthings/specmake) enable you to:

- specify a software product
- write validation tests
- run software tests
- gather, evaluate and present test results
- gather, evaluate and present code and branch coverage information
- gather, evaluate and present software performance measurements
- produce a Technical Specification (TS) as defined by
  @{/ref/ecss/e-st-40c-r1:/cite-long} and @{/ref/ecss/q-st-80c-r2:/cite-long}
  consisting of:
  - Interface Control Document (ICD)
  - Software Requirements Specification (SRS)
- produce software design and architecture documents
- produce software product assurance documents
- produce user manuals
- produce test plan documents
- produce test report documents
- provide traceability from the specification, to the software design, to the
  source code, to test plans, to test results, and vice versa
- run static code analysers, present the results, provide links to results in
  other documents
- build the tools used to build the software product
- build the software product
- package everything as an archive file
- produce a Software Configuration File (SCF) describing the package

```{figure} ../images/traceability.*
---
alt: Traceability graph between the ICD, SDD, SRS, SUITP, SVS, and Test Report
---
Document traceability
```

## Specification items as files

Specification items can be stored in files in any file format which supports
dictionaries, lists, integers, floating-point numbers, and strings. The
*specthings* tooling supports the @{/glossary/yaml:/term},
@{/glossary/json:/term}, and Python
[pickle](https://docs.python.org/3/library/pickle.html) formats.

The developer-facing items are stored in YAML format since this format is human
readable, machine readable, and Git friendly. Each item is stored in a separate
file. Items with a common scope are stored in specification item directories.
By convention, the specification item directory names are `spec` or match with
the `spec-*` pattern. The item UID is defined by the file system path from the
specification item directory to the item file. For example, let us assume we
have a specification item directory `spec` and an item file `spec/a/b/c.yml`,
then the UID is `/a/b/c`. UIDs can be absolute or relative to an item.

## Using content defined by specification items

A flexible `$${<variable-pattern>}` or variable `` @@`<variable-pattern>` ``
substitution is used to provide data associated with specification items. For
MyST text, the `` @@`<variable-pattern>` `` style is preferred to avoid
formatting issues with the `mdformat` tool. All of the following patterns are
subject to a variable substitution:

- `$${<variable-pattern>}`

- `` $${<variable-pattern>` ``

- `` $$`<variable-pattern>} ``

- `` $$`<variable-pattern>` ``

- `@@{<variable-pattern>}`

- `` @@{<variable-pattern>` ``

- `` @@`<variable-pattern>} ``

- `` @@`<variable-pattern>` ``

The `<variable-pattern>` is defined by the following Python regular expression:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
^[$@][{`]([a-zA-Z0-9._/-]+|\*):([\[\]a-zA-Z0-9._/-]+)(:[^$$`{}]*)?[}`]$
```

```{raw} latex
\end{footnotesize}
```

You have to escape `$${`, `` $$` ``, `@@{`, and `` @@` `` sequences using
`$$$${`, `` $$$$` ``, `@@@@{`, and `` @@@@` `` respectively. There is no need
to escape a stray `$$` or `@@`.

The variable substitution pattern contains three groups:

1. The first group defines the identifier to get the associated specification
   item. The identifier can be an absolute item UID or a UID relative to the
   current item. The identifier `.` denotes the current item. The identifier
   `*` denotes the item of the mapper object used to perform the substitution.

2. The second group defines the attribute path. The attribute path may
   reference the item data directly or invoke a software-defined method
   registered through `ItemMapper.add_get_value()`. Such methods compute a
   value on the fly instead of reading it from the item's stored data, so not
   every attribute path corresponds to a literal key in the item's data file.
   For example, `/cite`, `/cite-group`, and `/document-releases` are computed
   attributes, not stored data.

3. The optional third group defines arguments or a value transformer name. The
   built-in value transformers are:

   - `basename`: the last path component of the value.
   - `dirname`: the value with its last path component removed.
   - `dash`: the value prefixed with a dash (`-`), or the empty string if the
     value is empty.
   - `join`: joins a list value's enabled elements with a separator (comma by
     default, or the value of the `separator` keyword argument).
   - `relpath`: the value expressed relative to the path given as argument.
   - `slash`: the value prefixed with a slash (`/`), or the empty string if the
     value is empty.

   Arguments passed may be comma-separated and may go through their own
   character escaping since they may need to contain characters such as `','`,
   `' '`, or a nested substitution:

   - `'%'`, `'('`, `')'` escape to `'$'`, `'{'`, `'}'` respectively, which
     allows a nested substitution to be passed as an argument. For example,
     `'%(*:/directory)'` unpacks to `'$${*:/directory}'`, meaning "the
     `/directory` attribute of the item associated with the item mapper
     performing the substitution" (`*` denotes the item of the mapper object
     used to perform the substitution).

   - `'\,'` escapes to a literal comma, and `'\s'` escapes to a literal space,
     since those characters would otherwise separate arguments or the
     transformer name from its arguments.

   - `'\g'` escapes to a literal backtick.

   - `'\\'` escapes to a literal backslash.

For example, consider the specification item with UID `/u`:

```{raw} latex
\begin{footnotesize}
```

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

```{raw} latex
\end{footnotesize}
```

In addition, the specification item with UID `/v`:

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
g: h
i: $${.:/g}
# the value of $${.:/g} is provided by item /v itself and substitutes to: h
j: $${/u:/a/b}
# the value of $${/u:/a/b} is provided by item /u and substitutes to: c
k: $${/u:/d[1]}
# the value of $${/u:/d[1]} is provided by item /u and substitutes to: f
```

```{raw} latex
\end{footnotesize}
```
