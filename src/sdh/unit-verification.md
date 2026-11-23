% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(UnitVerification)=

# Verification of software units

@`/glossary/verification:/term` answers the question whether the product is
built right. It checks that the product implements its specification.
@`/glossary/validation:/term` answers the question whether the right product is
built. It checks that the product fits its intended use. The two activities
differ in their reference. They can share their means, such as a test.

The tests which the action requirements generate check the software against the
requirements of its technical specification. This project calls them validation
tests, since ECSS-E-ST-40C Rev.1 calls this activity the validation against the
technical specification @`/ref/ecss/e-st-40c-r1:/cite`. The same test runs also
give evidence for the verification of the software units below the API.

The verification of a unit gives evidence that the unit implements the
requirements which apply to it. The requirements are the reference. The
specification states them at the level where the behaviour is observable, which
is often a layer above the unit. The evidence comes from two sources. Tests
derived from the requirements run the unit and check its outcome. Structural
coverage shows that the tests reached every part of the unit, or a coverage gap
item justifies a part which they did not reach. This chapter explains how the
action requirements of {ref}`ActionRequirementModel` carry the requirements and
their tests down to the units, and which rules you follow so that they do.

## Software units

The glossary of the pre-qualified software defines a
@`/glossary/softwareunit:/term` as a C function or a function in assembler
language, with external or with internal linkage. Most units have no behaviour
of their own which a user could observe. `_CORE_semaphore_Seize()` decides
whether a task gets a semaphore, but no user calls it. The user calls
`rtems_semaphore_obtain()`.

The specification does not need a requirement for every unit. It needs one for
every behaviour, at the level where a reader can state it without describing
the code. The layers of a specification give that level.

## Layers down to the unit

The interface items state the functions of the @`/glossary/api:/term`. The
action requirement of an API function forms the API layer. Below it, the
requirements form the implementation layers. Each implementation layer is an
action requirement whose trigger is an event of the implementation, such as
"When the calling task tries to seize the semaphore." A layer which hands work
to a layer below it links that layer with the role `function-implementation`,
see the @`/spec/function-implementation-role:/spec-name`. An implementation
layer refines the @`/glossary/design-group:/term` of its module with the role
`requirement-refinement`, see the @`/spec/requirement-refinement:/spec-name`.
The @`/spec/requirement-design-group:/spec-name` defines a design group. It
names the Doxygen group of the module, and each source file of the module joins
that group with `@ingroup`. This chain reaches the units.

```{figure} ../images/ar-layers.*
---
alt: The layers from the requirement of rtems_semaphore_obtain down to the 
  design groups and the software units
width: 100%
---
The layers of `rtems_semaphore_obtain()` down to the software units
```

The figure shows the chain for `rtems_semaphore_obtain()`. The requirement of
the directive hands the seize operation to `/score/sem/req/seize-try` and to
`/score/sem/req/seize-wait`. The second one hands the enqueue of the task to
the thread queue in `/score/tq/req/enqueue-fifo`. Each layer of the
implementation refines the design group of its module. The design group
`RTEMSScoreSemaphore` contains `_CORE_semaphore_Seize()`, and the design group
`RTEMSScoreThreadQueue` contains `_Thread_queue_Enqueue()`.

The chain allocates every requirement of an implementation layer to a module,
and the Doxygen group of the module lists its units. A reviewer follows the
chain in both directions: from a requirement to the units which implement it,
and from a unit to the requirements of its module.

## Decide when a behaviour gets a layer of its own

A layer costs an item, a test and a review. Give a behaviour a layer of its own
if one of these conditions holds:

- The behaviour depends on a state which persists between calls, such as the
  count of a semaphore or the wait state of a thread. The layer then names the
  classes of that state as pre-condition states.

- Several callers use the behaviour. `/score/sem/req/seize-try` serves
  `rtems_semaphore_obtain()` and the self-contained semaphores of the C
  library. One layer states the behaviour once for all of them.

- The caller would have to multiply its transition map with the states of the
  behaviour. A layer keeps both maps small.

Otherwise, state the behaviour in the map of the caller. A unit which only
forwards a call or converts a value is covered by the requirement of its
caller.

## Tests along the layers

Each action requirement generates its own test code. The test of a layer checks
that the layer hands the work to the layer below it. A post-condition state of
the upper layer states the hand-off, such as "The calling task shall try to
seize the semaphore as specified by `/score/sem/req/seize-try`." The lower
layer can generate a test runner instead of a test case, if it has a
@`/spec/test-header:/spec-name`. The test of the upper layer then runs all
variants of the lower layer each time one of its entries reaches the hand-off.

```{figure} ../images/ar-layer-tests.*
---
alt: The requirement of rtems_semaphore_obtain generates a test case which runs 
  the test runner of seize-try
width: 100%
---
The test of the API layer runs the test of the lower layer
```

The test of the upper layer runs the units of both layers together, and the
test of the lower layer checks the outcome of the hand-off for every state of
the lower layer. In this way the tests exercise the integration of the units
along the layers. Each test executable links the units which it needs from the
static libraries of the product, as an application does.

The tests reach the units through the API, with few exceptions. The reasons
come from the product:

- The RTEMS project tests at the API level by tradition, also where a test
  targets an internal function.

- RTEMS has no mocks for tests. Some units change the state of the processor at
  the register level, which makes a mock hard to write.

- RTEMS has no deep call hierarchies, and most internal states are independent
  of each other. Most code can therefore be reached through the API alone.

Some tests set internal data structures directly to prepare the state which a
requirement names. The check still runs against the requirement.

## Write the map for the tests of a unit

The transition map decides what the generated test runs. Write the map so that
the test exercises each of these aspects:

- **Outcomes and error cases.** Give a post-condition state to each outcome
  which the design names, including every error status. Give a pre-condition
  state to each unwanted situation which leads to an error, such as an invalid
  identifier.

- **State of the design.** Give a post-condition to each state variable which
  the module changes and which its design group documents, such as the count of
  a semaphore.

- **Range of an input.** Give a numeric input a state for each class of equal
  behaviour and a state for a value out of range, where the unit rejects such a
  value.

- **Boundaries.** Choose the representative of a numeric class at the edge of
  the class. A state for a value whose outcome equals the outcome of its class
  adds nothing to the map.

- **Limits.** Give a configured limit, such as the maximum number of objects,
  the states on both sides of the limit.

The limits of the model in {ref}`ActionRequirementModel` apply to these tests.
A test checks one representative of each class. It does not check the
interleaving of a trigger with an interrupt or with another processor, unless a
pre-condition state names the situation which the interleaving leaves behind.

## Traceability and coverage of a unit

The verification of a unit answers three questions. The first is which
requirements apply to the unit. These are the requirements which refine the
design group of its module, and the requirements above them in the chain.

The second question is which tests run the unit. Each test report carries the
coverage data of its test executable, so the test executables which run a unit
follow from the reports.

The third question is whether the tests reach all of its code. The coverage
report names each function, line and branch which no test reaches and which no
coverage gap item justifies. The limits of the
@`/spec/pkg-test-coverage:/spec-name` items decide whether such a spot is a
defect.

A coverage gap item justifies a part of the code which no test reaches, for
example code which only a hardware fault can reach. Its type is the
@`/spec/verification-code-coverage-gap:/spec-name`. The coverage section of the
test report lists the files with justified gaps and the files with unjustified
gaps.

The coverage measurement uses `gcov`. It counts the branches of the object
code, not the decisions of the source code. A decision with several conditions
results in several branches, so branch coverage of the object code usually
demands more than decision coverage of the source code. The compiler can also
turn a decision into code without a branch. Such a decision has no branch to
count, so only the transition map makes sure that the tests take both of its
outcomes.

## Review the verification of a unit

The review of the verification of a unit checks its evidence: the tests and
their coverage. The generator derives the test of an action requirement from
the item. The review of the item therefore also covers the design of this test.
It checks that the pre-conditions name every input and every state which
affects the outcome, that the map covers each combination once, that the state
texts follow EARS, and that the prepare code and the check code match the state
texts. {ref}`ActionRequirements` contains the checklist. The tools check the
map for transition map coverage and transition map disjointness, so the review
concentrates on the choice of the classes and on the binding to the code.

### Find the action requirements of a unit

To review the verification of a unit, start at the unit in the Software Design
Document (SDD), the Doxygen documentation of the sources. The SDD and the
Software Requirements Specification (SRS) link each other, so you follow links
and do not search. The figure shows the path for `_CORE_semaphore_Seize()`.

```{figure} ../images/ar-trace-path.*
---
alt: The path from a function in the SDD through the design group and the action
  requirement in the SRS to the test case specification in the SVS
width: 100%
---
The path from a software unit to its action requirements and its test
```

1. Find the function in the SDD. Doxygen documents it on the page of its group.
   Its paragraph "Traceability" names the specification items of the unit. An
   internal unit relates to the design group of its module, here
   `score/sem/if/group`. An API function relates to its interface item.

2. Follow the link to the entry of the design group in the SRS. Its section
   "Refined by" lists the requirements of the module, among them
   `/score/sem/req/seize-try`.

3. Open the action requirement. Its section "Function implementation" names the
   layers which use it and the layers which it uses. For `seize-try`, these are
   `/rtems/sem/req/obtain` and `/newlib/req/sys-lock-semaphore-try-wait`. The
   SRS writes the name of a section in the plural if the section lists several
   items.

4. Follow the section "Validation" to the test case specification in the
   Software Validation Specification (SVS). The test report holds the results
   of this test case.

The SRS entry of a design group links back to its Doxygen group in the section
"Software design". You can therefore walk the path in both directions.

### Tooling behind the traceability links

The package build creates these links. Nobody maintains them by hand, so they
follow every change of the sources and of the specification.

```{figure} ../images/ar-trace-tooling.*
---
alt: The sources pass through a first Doxygen run, the link hub, the SDD linker 
  and the Doxygen run of the SDD, and the link hub also feeds the SRS builder
width: 100%
---
The tools which create the traceability links
```

1. A first Doxygen run over the sources writes a tag file. The tag file lists
   each design element, such as a function, a file or a group, with its file,
   its groups and its location in the SDD.

2. The link hub reads the tag file and the specification items. It maps each
   design element to items. An element whose name matches an interface item
   maps to that item. A Doxygen group maps to the design group item whose
   identifier names it. Any other element takes the items of its groups, or of
   the groups of its file. A source file without a group stops the build.

3. The SDD linker writes a header file. For each design element, the header
   holds a Doxygen block with the paragraph "Traceability" and the links to the
   documents of its items.

4. The Doxygen run of the SDD reads the sources and this header. Each page of
   the SDD therefore shows its paragraph "Traceability".

5. The SRS builder takes the location of each design element from the link hub.
   It adds the section "Software design" to an item with a design element. It
   adds the sections "Refined by", "Function implementation" and "Validation"
   from the links between the items.
