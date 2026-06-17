% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

# Qualification engineering

## Overview

Usually your task is to pre-qualify a group of already existing functions –
such as all functions related to semaphores or all functions related to events.
At the very core, you have to write an interface specification for each
publicly visible function or macro, write the requirements that each such
function or macro must meet, write validation tests that verify each function
or macro meets all its requirements and make sure code coverage goals are
reached. The typical workflow looks like this (the steps are described in more
detail later):

1. Create a new feature branch for your work.

2. Put all functions and macros visible in the API in Doxygen groups.

3. Add all functions and code needed to the pre-qualified API subset.

4. Create a specification directory tree for this function group. In the next
   steps, you will create YAML files in these directories. These YAML files
   will contain the function specification, the requirements and the validation
   tests.

5. Write or generate interface specifications. The result is a YAML file for
   each publicly visible API function or macro describing the function, its
   parameters and the result. These YAML files can often be generated from the
   existing Doxygen information found in the C header files.

6. For each API function or macro:

   6.1 Write down all requirements the function or macro must meet. The result
   is a YAML file for each publicly visible API function or macro containing
   all its requirements.

   6.2 Write validation tests. These tests come in two flavours:

   - **Simple Validation Tests** These consist of unstructured test functions
     and are written in an extra YAML file. These are appropriate for macros
     and functions that do a simple computation

   - **Action Requirements** These consist of pre- and post-conditions and a
     table relating the conditions to each other. The whole and often extensive
     test logic is automatically generated for you.

   6.3 Generate C- and doc-files from the YAML files written above. You must
   add the generated tests to an existing test suite or create a new test suite
   for them once.

   6.4 Compile and run the tests

   6.5 Debug and fix test failures

   6.6 View coverage data

7. Create a pull request once your work is completed, tests and coverage goals
   are reached.

Finally, performance and memory benchmarks may be needed.

```{admonition} Examples
Examples of already pre-qualified function groups are often helpful.

[**Base Definitions**](https://docs.rtems.org/doxygen/main/group__RTEMSAPIBaseDefs.html)
define commonly used macros. This is a good example for writing
simple requirements and simple validation tests.

* `cpukit/include/rtems/score/basedefs.h` – header file

* `spec/rtems/basedefs` – specification directory tree contains all the
  YAML files created for pre-qualification

* `spec/rtems/basedefs/if/array-size.yml` – interface specification of
  the `RTEMS_ARRAY_SIZE` macro

* `spec/rtems/basedefs/req/array-size-0.yml` – requirement of the
  `RTEMS_ARRAY_SIZE` macro, note that some macros require several
  requirements

* `spec/rtems/basedefs/val/basedefs.yml` – defines many simple validation
  tests. The one for the `RTEMS_ARRAY_SIZE` macro starts at line 231.
  Note that `$${../if/array-size:/name}` is a substitution, it substitutes
  the value of the key `name` from the file `../if/array-size.yml` which
  happens to be `RTEMS_ARRAY_SIZE`. `$${.:/step}` is substituted by a number
  counting the `T_step_*` check macros in the C file generated from this
  YAML file.

* `testsuites/validation/tc-basedefs.c`  – the corresponding generated
  validation test file

* `spec/build/testsuites/validation/validation-no-clock-0.yml` – the YAML
  file which defines the test suite to which the validation test belongs

* `testsuites/validation/ts-validation-no-clock-0.c` – main C file of the
  test suite, see also `testsuites/validation/ts-default.h`

* `spec/testsuites/validation-no-clock-0.yml` – definition of the test
  suite file `ts-validation-no-clock-0.c` itself

* `spec/build/testsuites/validation/grp.yml` – this group defines which
  test suites exist.

[**Rate Monotonic Manager**](https://docs.rtems.org/docs/main/c-user/rate-monotonic/index.html#rate-monotonic-manager)
from the Classic API executes a job periodically. This is a good example
for action requirements.

* `cpukit/include/rtems/rtems/ratemon.h` – header file

* `cpukit/rtems/src/ratemoncreate.c`, `cpukit/rtems/src/ratemoncancel.c`,
  `cpukit/rtems/src/ratemongetstatus.c` – some of its implementation files
  (note that the validation tests must cover the code in further files
  to reach the code coverage goals)

* `spec/rtems/ratemon` – specification directory tree contains all the
  YAML files created for pre-qualification

* `spec/rtems/ratemon/req/create.yml` – one of its action requirement
  YAML files

* `testsuites/validation/tc-ratemon-create.c` – the corresponding
  generated validation test file

* `spec/build/testsuites/validation/validation-no-clock-0.yml` – the YAML
  file which defines the test suite to which the validation test belongs.
  This is the same as the one of the Base Definitions example above.
```

## How to create a feature branch?

A feature branch to accumulate all your changes is typically created like this:

```{code-block} none
---
linenos:
---
$ git checkout -b $${my-new-branch-name} eb/next
```

## How to add Doxygen groups?

We will prepare this for you.

TODO

## How to add a function to the pre-qualified subset?

We will prepare this for you.

TODO

## How to create a specification directory tree?

We will prepare this for you.

TODO

```{admonition} Content of spec-directory
(for example `spec/rtems/ratemon/*`)
TODO
```

## How to create interface specifications?

We will prepare this for you.

TODO

## How to write requirements?

See the
[*RTEMS Software Engineering Manual* chapter *Software Requirements Engineering*](https://docs.rtems.org/docs/main/eng/req/index.html#software-requirements-engineering).

We use the
[Easy Approach to Requirements Syntax (EARS)](https://docs.rtems.org/docs/main/eng/req/req-for-req.html#syntax)
to express requirements. This is fine for simple requirements. Yet, because
action requirements are broken into pre-conditions and post-conditions, the
requirement texts are also broken apart. The *when*, *while*, *if*, *where*
parts appear in the pre-conditions while the *\<system name> shall \<system
response>* parts appear in the post-conditions.

```{admonition} Where does the text written in those YAML files appear?

The texts from the interface specifications appear in the generated
RTEMS header files, in the *RTEMS Classic API Guide* or the *RTEMS POSIX
API Guide*, as well as in the *RTEMS Doxygen*. In a package, they also appear
in the *Interface Control Document (ICD)*.

The texts from the requirements and the description of the tests are part
of *Test Reports (TR), Software Requirements Specification (SRS), Software
Unit and Integration Test Plan (SUITP), Software Validation Specification
(SVS)*. They also appear as comments in the generated C files.
```

## How to write simple validation tests?

Follow the examples. Each test has an *action* part which contains the C code
to exercise the function or macro and a *check* part which should check for the
expected result(s). Each of these sections has a brief description. Moreover,
each such *check* part has a *links* part which links the check to one or
several requirements. In the end, all requirements must have at least one test.

Note that at the bottom of such a YAML file, are keys like

- `test-brief` to describe the whole test case,
- `test-includes` to define header files to be included,
- `test-support` to contain code which is put at the top of the generated C
  file, and
- `test-target` the name of the C file to be generated.

Consider also that newly generated C test case files must be added to a test
suite in a YAML file (see the examples above).

The test cases are based on the RTEMS test framework as described in the
[*RTEMS Software Engineering Manual* chapter *Software Test Framework*](https://docs.rtems.org/docs/main/eng/test-framework.html#software-test-framework).
This permits the use of test fixtures. It is helpful to have a look at the
*Test Checks* and the *Log Message* in that chapter.

The RTEMS coding rules apply, see
[*RTEMS Software Engineering Manual* chapter *Coding Standards*](https://docs.rtems.org/docs/main/eng/coding.html#coding-standards).

```{admonition} Unit vs. validation tests

TODO: Code coverage, Unit vs. Validation Tests / White box vs. Black box tests

TODO: Testing happens only on API level – no units with mocks,
In some cases tests manipulate RTEMS internal data structures to stimulate
tests.
```

## How to write action requirements?

TODO

## How to generate C code from the YAML files?

See the description of the `Makefile.work` in chapter
[*Set up the qualification engineering environment*](specification-how-to.md#set-up-the-qualification-engineering-environment).

## How to add test cases to test suites?

TODO

```{admonition} Selecting the right Validation Test Suite
Not all test cases of a function group need to be part of the same test
suite. It depends on the requirements a particular test has on the
executable. For example, a test may require the usual clock ticks, others
may require no clock to "manually" trigger the clock tick as part of the test
execution, others may need exactly one CPU, others at least three.
```

## How to create a test suite?

TODO

## How to compile and run the tests?

See section
[*How to set up a workspace application*](specification-how-to.md#how-to-set-up-a-workspace-application).

## How to run a test suite?

See section
[*How to run the workspace application*](specification-how-to.md#how-to-run-the-workspace-application).

## How to debug tests?

See section
[*How to debug the workspace application*](specification-how-to.md#how-to-debug-the-workspace-application).

## How to generate and view code coverage?

See section
[*How to create a coverage report*](specification-how-to.md#how-to-create-a-coverage-report).

## How to create a pull request?

Make sure everything compiles and links, the tests are running without
reporting failures and the code coverage goals are reached. Moreover, make sure
you have committed all your changes.

1. **Push your branch**

   Push your feature branch to your personal fork of the embedded brains RTEMS
   repository:

   ```{code-block} none
   ---
   linenos:
   ---
   $ git push -u origin $${my-new-branch-name}
   ```

   This will create a copy of your feature branch at your personal repository
   fork and set your feature branch to track that branch.

2. **Create a pull request**

   Log in to your GitHub account and go to your fork of the repository. Select
   your feature branch. GitHub will offer to create a *pull request* for it. As
   the target branch in the embedded brains RTEMS repository, select `eb/next`.
   Give your pull request a name and add a short description. It is advisable
   to set the pull request to *draft* state initially. Then click on *Create
   pull request*.

3. **Check and fix errors**

   You should see your new pull request now. If not, navigate to the
   [embedded brains RTEMS repository on GitHub](https://github.com/embedded-brains/rtems),
   choose the *Pull requests* tab, and select your pull request.

   Wait until all CI jobs are completed. If there are any errors, please fix
   them.

   Wait until *GitHub Copilot* finishes its review (you will get an email). If
   the review does not start automatically, *GitHub Copilot* appears in the
   list of possible reviewers on the right side. Click the small circle icon
   next to it.

   Check all its review comments, fix the relevant ones and close the review
   comments you have examined.

4. **Push your fixes**

   Assuming you have made fixes in your local working tree and have committed
   them, push your fixes again to your local fork of the repository. This will
   automatically update the pull request:

   ```{code-block} none
   ---
   linenos:
   ---
   $ git push
   ```

   If needed, use the `--force` option.

   Afterwards, repeat step 3 until all issues are resolved.

5. **Have your pull request merged**

   Once all issues found by the CI jobs and *GitHub Copilot* are resolved,
   remove the *draft* status. The embedded brains staff will review your pull
   request and merge it.
