% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2024, 2026 embedded brains GmbH & Co. KG

(CodingGuidelines)=

# Coding guidelines

## Python

Follow the
[PEP 8 - Style Guide for Python Code](https://www.python.org/dev/peps/pep-0008/)
and the
[Google Python Style Guide](https://google.github.io/styleguide/pyguide.html).
If the Google and PEP 8 guidelines disagree with each other, the PEP 8
guidelines have precedence.

To document Python code, use the
[Google Python documentation style](https://google.github.io/styleguide/pyguide.html#38-comments-and-docstrings)
in the imperative form.

Use the [yapf](https://github.com/google/yapf) Python code formatter with its
default settings. These settings produce PEP 8 formatting. Use the `flake8` and
`pylint` static analysis tools for Python with their default settings. Use type
annotations and the `mypy` static type checker. Use `pytest` for tests. Use
[uv](https://docs.astral.sh/uv/) to organize your Python package.

Test code needs no type annotations and no analysis tools.

The listed tools ensure proper formatting and check the coding style
thoroughly. A review should focus on what the tools do not cover. In
particular, the tools may not enforce type annotations.

## C and C++

By default, use the

- [Zephyr Coding Guidelines](https://docs.zephyrproject.org/latest/contribute/coding_guidelines/index.html),
  and the

- [Zephyr C Code and General Style Guidelines](https://docs.zephyrproject.org/latest/contribute/style/code.html).

Advanced recommended reading:

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

If the Google and Zephyr guidelines disagree with each other, the Zephyr
guidelines have precedence.

Code written for an upstream project follows the guidelines of that project.
Changes and extensions of @`/glossary/rtems:/term` source code therefore follow
the RTEMS
[coding standards](https://docs.rtems.org/branches/main/eng/coding.html). Use
the Zephyr style if the upstream project is unlikely to integrate the code, or
if you are in doubt.

The default C standard version is C17. For a project which uses GCC 15 or
later, the C standard version is C23. Check the required C standard version of
upstream projects.

Before you write C++ code, consult the team to determine a suitable C++
standard version.

Do not use [Yoda conditions](https://en.wikipedia.org/wiki/Yoda_conditions).

When the coding style lets you declare variables anywhere in a function,
declare them in a scope as local as possible. Declare them as close to the
first use as possible. See also
[Local Variables in the Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Local_Variables).

Use the `clang-format` tool to format your code. By default, use the Zephyr
style. Copy `.clang-format` from Zephyr to the top-level project directory,
where `clang-format` finds it by default:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ curl -o top/of/project/.clang-format https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/refs/heads/main/.clang-format
```

```{raw} latex
\end{footnotesize}
```

Put the format configuration under version control.
