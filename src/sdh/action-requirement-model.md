% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(ActionRequirementModel)=

# The action requirement model

A qualified product needs requirements which a reviewer can check for gaps,
tests which follow from them in a way a reviewer can check, and a design which
shows how both reach the code. An @`/glossary/action-requirement:/term` gives
the requirements and the tests from one source, and it links them to the
design. Its text is a set of requirements in the Easy Approach to Requirements
Syntax (@`/glossary/ears:/term`). The same entries form a
@`/glossary/state-transition-table:/term`, which the tools check for gaps and
contradictions. The generator turns the table into a test which runs every
feasible entry. This chapter explains the model behind it, so that you can
judge what a specification states and what it leaves out. The next chapter,
{ref}`UnitVerification`, shows how the model reaches the software units. The
task chapter {ref}`ActionRequirements` shows how you write items of the
@`/spec/requirement-action:/spec-name`.

The model uses established methods. The tools and the review check each table
for the completeness and the consistency which the Federal Aviation
Administration (@`/glossary/faa:/term`) recommends for the requirements of
avionics software @`/ref/research/lempia-2009-remh:/cite`. The test design of
the model matches the category-partition method
@`/ref/research/ostrand-1988-cp:/cite`, and its test execution matches
model-based testing @`/ref/research/utting-2006-mbt:/cite`. The Guide to the
Software Engineering Body of Knowledge (@`/glossary/swebok:/term`) lists the
techniques of this test design as decision table testing, equivalence
partitioning and boundary value analysis
@`/ref/research/washizaki-2026-swebok:/cite`.

## A requirement in EARS form

EARS writes a requirement in a fixed order of clauses
@`/ref/research/mavin-2026-ears:/cite`. Each clause starts with a keyword. A
complex requirement combines them:

> **While** \<pre-condition>, **when** \<trigger>, the \<system> **shall**
> \<response>.

An action requirement is built from exactly these clauses. Each state of a
@`/glossary/pre-condition:/term` carries a text which starts with `While`. The
item carries the trigger as its text, which starts with `When`. Each state of a
@`/glossary/post-condition:/term` carries a text with `shall`. One entry of the
@`/glossary/transition-map:/term` therefore reads as one EARS requirement. The
figure shows the entry of the item `/score/sem/req/seize-try` for a semaphore
with a positive count.

```{figure} ../images/ar-ears-entry.*
---
alt: The EARS clauses of one transition map entry and the parts of the item 
  which give them
width: 100%
---
One transition map entry as an EARS requirement
```

The other EARS keywords have a counterpart in the item:

```{table}
---
class: longtable
widths: 25,75
---
| EARS keyword    | Counterpart in the action requirement |
| --------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `While`         | a state of a pre-condition                                                                                                                                 |
| `When`          | the trigger, the text of the item                                                                                                                          |
| `shall`         | a state of a post-condition                                                                                                                                |
| `Where`         | the `enabled-by` expression of a transition map entry, for example `RTEMS_SMP`                                                                             |
| `If` ... `then` | the state of a pre-condition which names an unwanted situation, such as an invalid object identifier, together with the post-condition states of the error |
```

The texts of the states use `While` also for an unwanted situation, since the
situation is a state before the trigger. Since every entry with post-condition
states is an EARS requirement, the rules for EARS apply to each state text. The
@`/spec/requirement-action-condition:/spec-name` and the
@`/spec/requirement-action-state:/spec-name` define the attributes of a
condition and of its states. {ref}`ActionRequirements` gives the form of these
texts.

## From EARS sentences to a state transition table

A single EARS requirement says what happens in one situation. It says nothing
about the situations which no requirement names, and a reviewer has no means to
see a missing one. An action requirement closes this gap. You list every
pre-condition which affects the outcome of the trigger and every state which it
can take. The transition map then has to give the outcome for **each
combination** of pre-condition states, and for each combination exactly once.

The Requirements Engineering Management Handbook of the FAA asks for these two
properties as well. A set of detailed requirements is complete if it assigns a
value to each output for every system state. It is consistent if it assigns
only one value for every system state. The handbook notes that a table makes
both properties easier to confirm @`/ref/research/lempia-2009-remh:/cite`.

The @`/spec/requirement-action-transition:/spec-name` defines an entry of the
map. The tools of this project apply the two checks to every transition map.
They are called @`/glossary/transition-map-coverage:/term` and
@`/glossary/transition-map-disjointness:/term`. The first check rejects a
combination of pre-condition states without an entry. The second check rejects
a combination with two entries for the same configuration.

Each pre-condition has a finite set of states. The tools therefore enumerate
every combination, and they decide both checks exactly.

The two checks rest on a property of the pre-conditions. The states of each
pre-condition have to cover every system state and to exclude each other, so
that each system state belongs to exactly one state. Only then does an entry
for each combination give one outcome for each system state. No tool can check
this property, because a state consists of its text and its prepare code. The
review of the item checks it, see {ref}`ActionRequirements`.

Glossary terms of the component support the review. The state texts of
`/score/sem/req/surrender`, for example, name the kind of a semaphore through
the glossary terms of a binary and a counting semaphore. Where all items of a
component state their conditions in the terms of its glossary, the states of
different items speak about the same entities in the same words. The tools do
not enforce such a language, but an inconsistent state becomes easier to see.

A combination which cannot occur still needs an entry. Such an infeasible entry
names a @`/glossary/skip-reason:/term` instead of post-condition states, see
the @`/spec/requirement-action-skip-reasons:/spec-name`. The reason is part of
the requirement, so a reviewer sees why the combination is missing from the
test.

## Relational model

The states of a pre-condition are classes of concrete states. The state
`Positive` of the pre-condition `Count` stands for every count from one up to
the maximum. A post-condition state need not name such a class. The state
`MinusOne` of the post-condition `Count` says how the count after the trigger
relates to the count before it. It does not say whether the count is still
positive.

The figure shows the consequence. Over the two classes `Zero` and `Positive`,
an attempt to seize a semaphore with a positive count leads to `Zero` if the
count was one and stays in `Positive` otherwise. The class of the next state
follows from the data, not from the class of the current state.

```{figure} ../images/ar-seize-try-states.*
---
alt: State diagram of the seize try operation over the classes Zero and Positive
width: 100%
---
The trigger of `/score/sem/req/seize-try` over the classes of the count
```

An action requirement is therefore a transition table with data and not a plain
finite automaton. In the terms of model-based testing, the pre-condition
classes make the model transition based, and the post-condition relations make
it a model in pre and post form @`/ref/research/utting-2006-mbt:/cite`.

## Worked example: seize a semaphore without waiting

The item `/score/sem/req/seize-try` specifies how the semaphore handler behaves
when a task tries to seize a counting semaphore and does not want to wait. The
trigger is:

> When the calling task tries to seize the semaphore.

One pre-condition `Count` affects the outcome. It has two states:

```{table}
---
class: longtable
widths: 20,80
---
| State      | Text                                                   |
| ---------- | ------------------------------------------------------ |
| `Zero`     | While the count of the semaphore is zero.              |
| `Positive` | While the count of the semaphore is greater than zero. |
```

Two post-conditions describe the effect:

```{table}
---
class: longtable
widths: 20,15,65
---
| Post-condition | State      | Text                                                                                |
| -------------- | ---------- | ----------------------------------------------------------------------------------- |
| `Status`       | `Ok`       | The return status of the directive call shall be derived from `STATUS_SUCCESSFUL`.  |
| `Status`       | `Unsat`    | The return status of the directive call shall be derived from `STATUS_UNSATISFIED`. |
| `Count`        | `Nop`      | The count of the semaphore shall not be modified.                                   |
| `Count`        | `MinusOne` | The count of the semaphore shall be decremented by one.                             |
```

The transition map has one entry for each of the two pre-condition states:

```{table}
---
class: longtable
widths: 34,33,33
---
| Pre-condition `Count` | Post-condition `Status` | Post-condition `Count` |
| --------------------- | ----------------------- | ---------------------- |
| `Zero`                | `Unsat`                 | `Nop`                  |
| `Positive`            | `Ok`                    | `MinusOne`             |
```

Read as EARS, the map states two requirements. While the count is zero, when
the task tries to seize the semaphore, the status shall be `STATUS_UNSATISFIED`
and the count shall not change. While the count is positive, when the task
tries to seize the semaphore, the status shall be `STATUS_SUCCESSFUL` and the
count shall be decremented by one. The map covers both states of `Count`, and
it covers each state once.

The code which this item specifies is the first part of
`_CORE_semaphore_Seize()` for the Classic API and `_Semaphore_Try_wait()` for
the self-contained objects. Both compare the count with zero and either
decrement it or report that the semaphore is not available. The pre-condition
`Count` has its two states because the code has exactly this one decision.
Where the code had a second decision, such as a test against a maximum, the
pre-condition would need a state on each side of it.

## The binding to the code

A transition table alone is a specification on paper. An action requirement
also carries code which binds each state to the system. The test code of a
pre-condition state **prepares** a concrete state which belongs to its class.
The test code of a post-condition state **checks** whether the concrete state
after the trigger belongs to the expected class or relation.

```{figure} ../images/ar-commuting-square.*
---
alt: The prepare code maps the pre-condition state to a concrete state, the 
  trigger runs, and the check code maps the result back to the post-condition 
  states
width: 100%
---
The prepare code and the check code bind the model to the code
```

The figure is a commuting square. The upper path is the transition map. The
lower path is the real call of the software. The test passes if both paths end
in the same post-condition states. Model-based testing calls the code on the
vertical arrows the adaptor. It concretises the input of a test and abstracts
the output of the system, so that a verdict can compare the output with the
model @`/ref/research/utting-2006-mbt:/cite`.

The binding gives the requirement its precision. A state text may abstract from
the implementation as far as the reader needs. The check code still decides for
every run whether the system met the state text.

## Test design

The generated test runs every feasible entry of the transition map. Decision
table testing derives its test cases in the same way, from every combination of
conditions @`/ref/research/washizaki-2026-swebok:/cite`. The design matches the
category-partition method of Ostrand and Balcer
@`/ref/research/ostrand-1988-cp:/cite`. The table gives the terms of the method
and their counterparts in an action requirement:

```{table}
---
class: longtable
widths: 50,50
---
| Category-partition method                   | Action requirement                      |
| ------------------------------------------- | --------------------------------------- |
| parameter or environment condition          | pre-condition                           |
| choice, one class of a partition            | state of a pre-condition                |
| test frame, one choice of each category     | one combination of pre-condition states |
| constraint which removes a combination      | skip reason                             |
| setup of the environment for each test case | prepare code of the states              |
```

The generated test runs the prepare code of every pre-condition for each
combination. Each test case therefore sets up its own environment just before
it runs. A test case which relied on the state of the previous one could spoil
the rest of the test run. The category-partition method sets up each test case
in the same way @`/ref/research/ostrand-1988-cp:/cite`.

A test runs one representative of each class. Choose the representative of a
numeric class at the edge of the class, because an error of a comparison shows
at the edge. Take the edges from the code, where a comparison draws the line
between two classes. The category-partition method and model-based testing
choose values at the boundaries in the same way
@`/ref/research/ostrand-1988-cp:/cite` @`/ref/research/utting-2006-mbt:/cite`.
In the example, the edge of the class `Positive` is a count of one, since the
decrement leaves the class there. The prepare code of the item sets a count of
two, so it tests the interior of the class. Do not add a state for a value
whose outcome equals the outcome of its class. The state would repeat an entry
of the map and add nothing to the specification.

(ActionRequirementLogicalModel)=

## The logical model

@`/ecss/e/40/0860055:/standard-and-clause` asks the supplier to construct a
@`/glossary/logical-model:/term` of the functional requirements. Such a model
describes what the software shall do and leaves out how the software does it.
Its purpose is that you understand the requirements as a whole, and not only
one by one @`/ref/ecss/e-st-40c-r1:/cite`. The architecture then describes how
the software meets these requirements @`/ref/ecss/e-hb-40a:/cite`. Clause
@`/ecss/e/40/0860057:/clause` requires a @`/glossary/behavioural-view:/term` in
the logical model, and clause @`/ecss/e/40/0860154:/clause` verifies the
behaviour of the software against this view.

A model consists of submodels. Each submodel is a partial description for one
purpose, and the common kinds are structural and behavioural models
@`/ref/research/washizaki-2026-swebok:/cite`. The handbook ECSS-E-HB-40A names
the object, dynamic and functional models of one method as an example of a
logical model @`/ref/ecss/e-hb-40a:/cite`. The specification items of this
project give three views of this kind, and each view has its own item types.

The items of the @`/spec/interface:/spec-name` give the
@`/glossary/structural-view:/term`. An item of the
@`/spec/interface-group:/spec-name` contains the directives, types and
constants of a manager. Each item joins its group through the
@`/spec/interface-ingroup:/spec-name`. The groups form a hierarchy from an item
of the @`/spec/interface-domain:/spec-name` down to a single directive. An item
of the @`/spec/interface-function:/spec-name` names the types of its parameters
and of its return value through references to other interface items. The
Interface Control Document (@`/glossary/icd:/term`) presents this view.

The same groups carry the top of the @`/glossary/functional-view:/term`. Each
group states a requirement, such as "The Classic API shall provide an interface
to the Semaphore Manager". An item of the
@`/spec/requirement-functional-generic:/spec-name` refines a group through the
@`/spec/requirement-refinement:/spec-name`. It may name the directive which it
specifies through the @`/spec/interface-function-role:/spec-name` instead.
Items of the @`/spec/constraint:/spec-name` state the conditions under which a
directive may be called, and a directive links them through the
@`/spec/constraint-role:/spec-name`. The Software Requirements Specification
(@`/glossary/srs:/term`) presents the functional requirements and the
constraints. The ICD presents the groups together with their requirements.

The action requirements give the behavioural view. An action requirement names
the directive which it specifies through the Interface Function Link Role as
well. It names the lower layers which do the work through the
@`/spec/function-implementation-role:/spec-name`, as {ref}`UnitVerification`
describes. The SRS presents the conditions and the transition map of each item.
The Software Validation Specification (@`/glossary/svs:/term`) presents the
test which the generator derives from it.

The three views refer to the same interface items. The links name them by their
identifiers, and the texts of the items name them through references. For
example, a state text names a parameter through a reference to the function
item and does not write the name itself. The build fails on a reference to an
item which does not exist, so a view cannot refer to an entity which the
structural view lacks.

```{figure} ../images/ar-logical-model.*
---
alt: The structural, functional and behavioural views of the directive 
  rtems_semaphore_obtain and the documents which present them
width: 100%
---
Three views of `rtems_semaphore_obtain()` and the documents which present them
```

The directive `rtems_semaphore_obtain()` shows all three views. In the
structural view, the item `/rtems/sem/if/obtain` is a member of the group
`/rtems/sem/if/group` of the Semaphore Manager. That group belongs to the
Classic API group `/rtems/if/group`. The function item takes an object
identifier of the type `rtems_id` and returns a status of the type
`rtems_status_code`. Both types are interface items of their own. In the
functional view, the group of the Semaphore Manager states that the Classic API
shall provide an interface to the manager. The functional requirement
`/rtems/sem/req/mrsp-prio-change-while-waiting` refines this group, and the
constraint `/rtems/sem/constraint/obtain-isr` states when the directive may be
called from within an interrupt. In the behavioural view, the action
requirement `/rtems/sem/req/obtain` specifies the directive. It hands the work
to the lower layers, among them `/score/sem/req/seize-try` of the worked
example above.

The model is semi-formal. The structure is formal: the states, the entries, the
two checks of the transition map and the generated test. The meaning of a state
is given by its EARS text and by its test code, not by a formula. The model
does not replace a formal model of the software.

## Limits of the model

A model is useful when its reader knows what it leaves out. The views of the
model share their entities, but the behavioural views do not share their
states. Each action requirement defines the states of its own pre-conditions.
The items `/score/sem/req/seize-try` and `/score/sem/req/seize-wait` divide the
count of a semaphore into `Zero` and `Positive`. The item
`/score/sem/req/surrender` divides the same count into `LessMax`, `Max` and
`Blocked`, and its post-condition states are not states of the seize items. The
tools do not check that two items use the same states for the same object.

An action requirement therefore gives the behavioural view of one trigger. The
action requirements of an object do not combine into one state machine of the
object, and no document shows the behaviour of an object across its triggers.
You read the behaviour of an object from the items of its directives, one item
at a time.

Three further limits apply to every action requirement. The first concerns the
trigger. Each entry treats the trigger as one atomic step from the state before
to the state after, so a transition has exactly one event.

The second limit follows from the first. Concurrent calls on other processors
and interrupts during the trigger are not part of the transition. A state of a
pre-condition may name the situation which such an interleaving leaves behind.

The third limit comes from the classes. A test checks one representative of
each class. The claim for the other members of the class rests on the choice of
the classes, which the review of the item checks.

The item `/score/tq/req/timeout` shows the second limit. A thread which waits
for a thread queue passes through wait states. A timeout can arrive in each of
them, also in an interrupt or from another processor.

```{figure} ../images/ar-timeout.*
---
alt: The wait states of a thread and the outcome of a timeout in each of them
width: 100%
---
The outcome of a timeout for each wait state of `/score/tq/req/timeout`
```

The requirement names three wait states as the states of its pre-condition
`WaitState`: `IntendToBlock`, `Blocked` and `ReadyAgain`. For each of them it
states the outcome of the timeout. The state `IntendToBlock` exists because of
an interleaving: the timeout arrives after the thread started to wait and
before it completed the block. The model does not describe this interleaving.
It describes the state which the interleaving leaves behind, and the test
forces the thread into that state with a scheduler event handler. The steps
between two wait states remain outside the model.
