% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(InterfaceItems)=

# Interface specification items

This chapter assumes that you have already read {ref}`SpecificationItems`. If
you are not yet comfortable with the ideas of a specification item, a UID, and
the `$${<uid>:<attribute-path>}` substitution syntax, read that chapter first
-- everything here builds directly on it.

## What is an interface specification item?

Every public C function, macro, constant, type, or structure that RTEMS offers
to an application is documented by exactly one *interface specification item*.
See {ref}`where the generated text ends up <QualEngWhereTextAppears>` (the
Interface Control Document, the generated header files, the API guides, and
Doxygen). In other words: when you write an interface item, you are not just
writing "a comment for a function" -- you are writing the authoritative,
machine-checked interface documentation that a reviewer, a test writer, and a
document generator will all read verbatim.

An interface item lives as a single YAML file under a `spec/.../if/` directory.
Its file name (without `.yml`) becomes the last segment of its UID. For
example, the C function `rtems_timer_create()` is specified by the file
`spec/rtems/timer/if/create.yml`, which has the UID `/rtems/timer/if/create`.

This chapter walks you through writing such an item from scratch, using
`rtems_timer_create()` as the running example. Chapter
{ref}`ActionRequirements` continues the same example to build the matching
functional specification.

```{figure} ../images/interface-item-workflow.*
---
alt: Overview of an interface specification item's properties and activities
width: 70%
---
Interface item overview
```

## Before you start

You need a local checkout of the RTEMS sources and the RTEMS specification
tree, see {ref}`CreateWorkingTree`. All paths in this chapter are relative to
the root of that checkout (referred to as `rtems` below).

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ cd rtems
$ ls spec/rtems/timer/if
```

```{raw} latex
\end{footnotesize}
```

## Step 1: check whether the item already exists

Before creating anything, search for an existing item. Never blindly overwrite
an existing interface item -- it may carry carefully curated descriptions,
cross-references, and links that a fresh scaffold would destroy.

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ grep -rl "name: rtems_timer_create" spec/rtems/timer
spec/rtems/timer/if/create.yml
```

```{raw} latex
\end{footnotesize}
```

If an item already exists, read it, understand it, and only change what you
were asked to change. For the rest of this chapter we pretend the file does not
exist yet, so that you can see how each attribute is derived.

## Step 2: pick the file location and the interface kind

Interface items are grouped by component. `rtems_timer_create()` belongs to the
Timer Manager, so its file goes into `spec/rtems/timer/if/create.yml`,
alongside the other Timer Manager directives.

Every interface item has an `interface-type` attribute that says what kind of C
construct it documents:

- `function` -- an ordinary C function, or a function-like macro that is
  documented exactly like a function.
- `macro` -- an object-like or function-like macro that is *not* documented
  like a function (rare; used for macros with unusual expansion behavior).
- `define` -- a constant flag or value, such as `O_CREAT` or `EXIT_FAILURE`.
- `typedef` -- a type alias.
- `struct` (via `definition-kind: struct-only`) -- a structure type.

`rtems_timer_create()` is an ordinary function, so `interface-type: function`.
{ref}`InterfaceItemsOtherKinds` at the end of this chapter covers the other
four kinds.

## Step 3: write the brief

The `brief` attribute is a single sentence, in the **imperative mood**,
summarizing what the directive does.

- Correct: `Create a timer.`
- Incorrect: `Creates a timer.` (not imperative) or
  `This function creates a timer.` (not a brief, and redundant)

Use `the <object>` rather than `a <object>` when the object being acted upon is
one of the function's own parameters -- but keep `a/an <object>` for
constructor-style functions that create a brand new object out of system
resources (the object does not exist yet, so there is nothing to point `the`
at). `rtems_timer_create()` is exactly this constructor case: there is no timer
yet, so `Create a timer.` is correct, not `Create the timer.`. Contrast this
with an initialization function where the caller already allocated the storage,
such as a barrier initialization: `Initialize the barrier object.` is correct
there, because the object storage already exists.

### Mention significant parameters, correctly phrased

A brief that only says `Create a timer.` is not yet complete: it says nothing
about the parameters, so it does not actually summarize what the call does.
Every significant parameter -- and especially every output parameter -- should
be mentioned, so that the brief alone tells the reader what the directive does.
How you phrase a parameter reference depends on its kind:

- **Pointer parameter** (other than a string):
  `referenced by $${.:/params[x]/name}`.
- **Scalar parameter, or a string** (`char *` / `const char *`):
  `specified by $${.:/params[x]/name}`.
- **Function pointer parameter**: no `referenced by` -- just
  `$${.:/params[x]/name}` on its own.

Replace `x` with the parameter's zero-based index. Whichever form you use, a
noun must precede it: never write "the referenced by ...", always "the `<noun>`
referenced by ...", for example "the object referenced by ...".

For `rtems_timer_create()`: `name` is a scalar parameter, so it is
`specified by`; `id` is a pointer parameter used purely as an output (its
existing contents are never read), which is exactly the kind of parameter this
rule most wants mentioned.

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
brief: |
  Create a timer with the name specified by $${.:/params[0]/name}, and store
  its identifier in the object referenced by $${.:/params[1]/name}.
```

```{raw} latex
\end{footnotesize}
```

This is more thorough than what you would find by simply reading
`spec/rtems/timer/if/create.yml` today: that file still has the older,
un-normalized `Creates a timer.`, with no parameters mentioned at all -- a
leftover from before this rule was established, not something to imitate.
Several other Classic API constructor directives (`rtems_task_create()`,
`rtems_semaphore_create()`, `rtems_message_queue_create()`, ...) have the same
leftover, terse brief. Write new items, and any item you are asked to touch, to
the current rule; do not copy an old brief just because it is what is on disk.

## Step 4: document the parameters and their direction

`rtems_timer_create()` has this C signature. This signature, and the other
excerpts from `spec/rtems/timer/if/create.yml` throughout this chapter, are
quoted verbatim from the RTEMS sources; see the
[RTEMS license](https://www.rtems.org/license/) for the terms that apply to
them.

```{raw} latex
\begin{footnotesize}
```

```{code-block} c
---
linenos:
---
rtems_status_code rtems_timer_create( rtems_name name, rtems_id *id );
```

```{raw} latex
\end{footnotesize}
```

Each parameter becomes one entry in the `params` list, in declaration order.
Two attributes matter most: `description` and `dir`.

The `description` **must** begin with the exact word `is` (lower case, no
capitalization), because it is spliced into sentences elsewhere (for example
"is the object name of the timer."). For pointer parameters, mention what
happens to the referenced object.

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
params:
- description: |
    is the object name of the timer.
  dir: null
  name: name
- description: |
    is the pointer to an $${../../type/if/id:/name} object.  When the directive
    call is successful, the identifier of the created timer will be stored in
    this object.
  dir: out
  name: id
```

```{raw} latex
\end{footnotesize}
```

Note the `$${../../type/if/id:/name}` reference instead of the literal text
`rtems_id`: whenever you refer to another interface item (a type, a constant,
another function), reference it through its UID so that the rendered
documentation gets a real cross-reference link, and so that a future rename of
`rtems_id` does not silently make this text wrong. The path is *relative* to
the current item's directory; `../../type/if/id` climbs out of
`spec/rtems/timer/if/` up to `spec/rtems/type/if/id.yml`.

### Choosing `dir`

The `dir` attribute records how the function uses the memory a pointer
parameter refers to. Use this decision procedure:

| Parameter shape                                                               | `dir` value | Example                                                                                                                 |
| ----------------------------------------------------------------------------- | ----------- | ----------------------------------------------------------------------------------------------------------------------- |
| Passed by value, not a pointer (including opaque descriptors like `mqd_t`)    | `null`      | `int`, `size_t`, `rtems_name`                                                                                           |
| Pointer, function only *reads* through it                                     | `in`        | `const struct timespec *`                                                                                               |
| Pointer, function only *writes* through it, or initializes a brand-new object | `out`       | the `id` output parameter above, `pthread_cond_init()`'s attribute pointer                                              |
| Pointer, function *reads the existing state and then modifies it*             | `inout`     | destructors (`pthread_attr_destroy()`), synchronization primitives that block and change state (`pthread_mutex_lock()`) |

`name` is passed by value, so `dir: null`. `id` is a pointer that the directive
only ever writes to (it stores the freshly created object's identifier there;
it never reads whatever garbage was there before), so `dir: out`.

## Step 5: document the return value

The `return` attribute is a dictionary with two keys:

- `return`: free text for *dynamic* or non-discrete return behavior (for
  example, "returns a pointer into the buffer"). Leave it `null` if every
  outcome is a discrete value.
- `return-values`: a list of `{value, description}` entries for every discrete
  return value or status code.

`rtems_timer_create()` returns an `rtems_status_code`, which is always one of a
fixed set of named status codes -- so `return` stays `null` and every outcome
goes into `return-values`:

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
return:
  return: null
  return-values:
  - description: |
      The requested operation was successful.
    value: $${../../status/if/successful:/name}
  - description: |
      The $${.:/params[0]/name} parameter was invalid.
    value: $${../../status/if/invalid-name:/name}
  - description: |
      The $${.:/params[1]/name} parameter was $${/c/if/null:/name}.
    value: $${../../status/if/invalid-address:/name}
  - description: |
      There was no inactive object available to create a timer.  The number of
      timers available to the application is configured through the
      $${/acfg/if/max-timers:/name} application configuration option.
    value: $${../../status/if/too-many:/name}
```

```{raw} latex
\end{footnotesize}
```

`$${.:/params[0]/name}` is a special case of the substitution syntax: `.` means
"the current item", so this resolves to this item's own first parameter's name
(`name`), instead of hardcoding the literal text `name` -- if a future edit
renames the parameter, this description updates itself.

### The classic POSIX zero/minus-one pattern

Not every function uses a status-code enum. Many POSIX and C functions instead
return `0` on success and `-1` on error, signalling the actual error through
`errno`. For that shape, use exactly this block:

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
return:
  return: null
  return-values:
  - description: |
      Returns zero on success.
    value: 0
  - description: |
      An error occurred. The $${/c/errno/if/errno:/name} is set to indicate the error.
    value: -1
```

```{raw} latex
\end{footnotesize}
```

A few rules that catch people out:

- Integer values (`0`, `-1`, `255`, ...) **must** be written as YAML integers,
  not quoted strings.
- Never invent an artificial placeholder value like `value: nonzero` in
  `return-values`. Describe "nonzero" in the free-text `return` key instead,
  spelling it as one word, `nonzero` (not `non-zero`). If the function can
  *also* literally return `0` as one specific outcome among several nonzero
  ones, that literal `0` still gets its own `return-values` entry.
- Small numbers in prose are spelled out (`zero`, not `0`); the numbers inside
  `value:` stay numeric.

## Step 6: notes and cross-references

The `notes` attribute must reference the governing standard: the C standard,
POSIX, or a FreeBSD man page for functions that come from there.
`rtems_timer_create()` is an RTEMS-specific directive with no external
standard, so its `notes` instead documents an RTEMS-internal implementation
detail:

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
notes: |
  The processor used to maintain the timer is the processor of the calling task
  at some point during the timer creation.

  For control and maintenance of the timer, RTEMS allocates a
  $${/glossary/tmcb:/term} from the local TMCB free pool and initializes it.
```

```{raw} latex
\end{footnotesize}
```

`$${/glossary/tmcb:/term}` links to a glossary entry (an *absolute* UID here,
since the general glossary lives outside this component). Before writing a
plain-text technical term, search the glossary for it -- `spec/glossary` for
project-wide terms, and the component's own `spec/.../glossary/` directory for
component-specific ones. Only introduce a brand new glossary term if a search
in both places turns up nothing.

### Referencing external standards

When a function *does* come from an external standard, `notes` must link to it,
using one of these three exact forms depending on where the function is
defined:

**C23** (cppreference.com):

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
See [C23, <stdlib.h>, malloc()](https://en.cppreference.com/w/c/memory/malloc).
```

```{raw} latex
\end{footnotesize}
```

**POSIX.1-2024** (The Open Group):

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
See [POSIX.1-2024, System Interfaces, mq_getattr()](https://pubs.opengroup.org/onlinepubs/9799919799/functions/mq_getattr.html).
```

```{raw} latex
\end{footnotesize}
```

**FreeBSD manual pages** (for BSD extensions not in C23 or POSIX, such as
`strlcpy()` or `arc4random()`):

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
See [FreeBSD Manual Pages, strlcpy()](https://man.freebsd.org/cgi/man.cgi?query=strlcpy&sektion=3).
```

```{raw} latex
\end{footnotesize}
```

Append `()` to the link text only for functions and function-like macros --
never for object-like macros or type names. Do not guess the standard from the
header file alone: a single header such as `<stdlib.h>` mixes C23 functions
(`malloc()`), POSIX functions (`setenv()`), and FreeBSD extensions
(`arc4random()`) -- check each function's actual origin.

## Step 7: errno conditions

`rtems_timer_create()` does not set `errno` (it uses the status-code mechanism
instead), so this step does not apply to our running example. Many
POSIX-flavored interfaces do set `errno`, though, so it is worth walking
through a small real example: `mq_getattr()` (`spec/c/mqueue/if/getattr.yml`).
The excerpts below are quoted verbatim from that file; see the
[RTEMS license](https://www.rtems.org/license/) for the terms that apply to
them.

Errno conditions are recorded as `role: errno` links, each pointing at the
errno constant's own interface item, with a `description` explaining the
specific condition:

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
links:
- description: |
    The $${../glossary/mqdes:/term} specified by $${.:/params[0]/name} is invalid.
  role: errno
  uid: /c/errno/if/ebadf
- description: |
    The $${/c/if/mq_attr:/definition[0]/default/name} field in
    $${.:/params[1]/name} contained set bits other than
    $${../../fcntl/if/o-nonblock:/name}.
  role: errno
  uid: /c/errno/if/einval
```

```{raw} latex
\end{footnotesize}
```

Rules for these descriptions:

- Never hardcode a parameter's name as literal text; always substitute it with
  `$${.:/params[<index>]/name}`.

- If one errno value can occur for several independent reasons, do not cram
  them into one sentence. Instead, use this exact structure -- a fixed
  introductory sentence followed by a Markdown bullet list:

  ```{raw} latex
  \begin{footnotesize}
  ```

  ```{code-block} yaml
  ---
  linenos:
  ---
  return-values:
  - description: |
      This error number indicates the following error conditions:

      - The new value specified for $${.:/params[1]/name} is not one of the
        legal values $${/c/if/process-shared:/name} or $${/c/if/process-
        private:/name}.
      - The value specified by $${.:/params[0]/name} is invalid.
    value: $${/c/errno/if/einval:/name}
  ```

  ```{raw} latex
  \end{footnotesize}
  ```

- Wrap every `brief`, `description`, and errno text block at 79 characters,
  same as any other MyST or YAML text in this project.

(interface-items-step-8)=

## Step 8: format and validate

Once the item's content is in place, two things remain: mechanical formatting,
and structural validation. Do this every time you touch a `.yml` file, no
exceptions. For an overview of the `specverify` and `specwareview` tools used
in this step, see {ref}`ToolsSpecification`.

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ uv run specverify --format-items --do-not-indent-lists \
    --clang-format-style=default:file:_clang-format \
    spec/rtems/timer/if/create.yml
```

```{raw} latex
\end{footnotesize}
```

`--do-not-indent-lists` is required: this project's convention is that list
items align with their parent key rather than being indented under it. Omitting
the flag produces a large, unrelated reformatting diff. Pass only the exact
files you touched -- passing a whole directory can raise spurious errors about
unrelated files that link elsewhere.

`--clang-format-style` binds the style name of the specification types to the
style file of the RTEMS working tree, see {ref}`ToolSpecverify`. An interface
item holds no C language source code, so the option changes nothing here. Use
the same command everywhere, because an action requirement needs it.

Then validate the whole specification tree, to catch broken UID references,
missing mandatory attributes, or accidental cycles:

```{raw} latex
\begin{footnotesize}
```

```{code-block} none
---
linenos:
---
$ uv run specverify spec
$ uv run specwareview
```

```{raw} latex
\end{footnotesize}
```

If either command reports a pre-existing error in a component you did not
touch, do not try to fix it as part of your change -- only your own item needs
to be clean.

(InterfaceItemsOtherKinds)=

## Other interface kinds

Everything above focused on `interface-type: function`, the most common and
most involved case. The other four kinds share the same `brief`, `notes`, and
cross-referencing rules, but differ in a few places:

**`macro`**

Used for macros that are not simply documented like a function (most
function-like macros just use `interface-type: function` and are documented
exactly as shown above). When you do need `interface-type: macro`:

- `definition.default` must be a nested dictionary with `attributes`, `body`,
  `params`, and `return` keys, not a flat string.
- `params` must mirror the macro's arguments and must not be empty; use
  substitution variables such as `$${.:/params[0]/name}`.
- `return` must be `null` if the macro expands to no value, or a reference to a
  concrete type otherwise. It is never itself "implementation-defined".
- A root-level `return` dictionary (with `return` and `return-values`) is still
  required, even for a macro that just expands to an integer constant.

```{raw} latex
\begin{footnotesize}
```

```{code-block} yaml
---
linenos:
---
definition:
  default:
    attributes: null
    body: _ImplementationDefined
    params:
    - $${.:/params[0]/name}
    return: null
  variants: []
```

```{raw} latex
\end{footnotesize}
```

**`define`**

Used for constant flags, such as `O_CREAT` or `EXIT_FAILURE`.

- `definition.default` is simply `_ImplementationDefined`.
- There is **no** `params` array at all for a `define` (unlike `macro`, where
  an empty `params` is not allowed either -- a `define` has none to begin
  with).

**`typedef`**

Used for type aliases.

- Must be placed directly in `spec/c/if/`, never in a subdirectory, even if the
  type conceptually belongs to a specific component.
- `params: []` and `return: null` are both mandatory, even though a typedef has
  neither.
- `definition.default` (or `definition.default.body`) is
  `_ImplementationDefined`, written literally -- do not append the type's own
  name or an asterisk to it.
- For POSIX types whose C name ends in `_t` (`clock_t`, `timer_t`, ...), keep
  the underscore in the file name too: `clock_t.yml`, not `clock-t.yml`.
- Because the file lives in the flat `spec/c/if/` directory but may
  conceptually belong to a specific component (say, `time`), its
  `interface-placement` and `interface-ingroup` links must use *absolute* UIDs
  (`uid: /c/time/if/header`), not relative ones -- a relative UID would wrongly
  resolve against `spec/c/if/` itself.

**`struct`**

Used for structure types.

- Set `definition-kind: struct-only`.
- `definition` is a **list** of member descriptions, not the default/variants
  dictionary used by the other kinds.
- Give each member its own glossary term where it represents a distinct concept
  (for example, a scheduling parameter such as "scheduling priority" or
  "initial budget" each get their own term), rather than one generic term
  covering the whole structure.

In every case, after editing or creating the item, repeat
{ref}`Step 8 <interface-items-step-8>` above: format with
`specverify --format-items ...`, then validate with `specverify spec` and
`specwareview`.

## Checklist

Before you consider an interface item finished:

- [ ] Searched for an existing item with the same `name` first.
- [ ] `brief` is one imperative sentence, using `the <object>` or
  `a/an <object>` correctly for the constructor-vs-mutator distinction.
- [ ] Every parameter has a `description` starting with `is `, and a correctly
  reasoned `dir`.
- [ ] `return` uses `return-values` for every discrete outcome, and reserves
  the free-text `return` key for genuinely dynamic behavior only.
- [ ] `notes` links to the governing standard (C23 / POSIX.1-2024 / FreeBSD),
  if any, in the exact required link format.
- [ ] Every technical term is either an existing glossary reference or was
  confirmed, by searching first, to need a new one.
- [ ] Every `errno` condition is a `role: errno` link with a substituted,
  79-character-wrapped description.
- [ ] The format command of {ref}`Step 8 <interface-items-step-8>`,
  `specverify spec`, and `specwareview` all ran clean on your changed files.

Once the interface item is in good shape, move on to {ref}`ActionRequirements`
to specify *how* the function behaves for every combination of inputs.
