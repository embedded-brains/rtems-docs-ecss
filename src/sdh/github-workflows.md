% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(GitHubWorkflows)=

# GitHub workflows

The pre-qualified RTEMS is worth something only while its specification, its
sources and its test results agree. Every change can break that agreement, and
a break which nobody notices for weeks is expensive to repair. Automated checks
therefore examine each change before it enters the pre-qualified RTEMS, and
they report the result where you discuss the change.

The checks serve a second goal. The pre-qualified RTEMS starts from a fixed
version of the RTEMS mainline, and the mainline moves on. The closer the two
stay, the less work it takes to bring a new RTEMS release into the
pre-qualification. This chapter shows you how a change travels, which checks
it passes, and how your work can also reach the RTEMS mainline.

(GitHubWorkflowsRepositories)=

## Repositories and branches

Your change touches up to four repositories on two hosts. The pre-qualified
RTEMS lives in the eb repository on GitHub. The RTEMS mainline lives in the
rtems.org repository on GitLab. You work in a fork on each host, and you send
your change from a fork to the repository above it.

```{figure} ../images/repository-relationships.*
---
alt: The eb repository and your fork on GitHub, the rtems.org repository and
  your GitLab fork on GitLab, and the routes of a change between them
width: 100%
---
Repositories and the routes of a change
```

The eb repository has two long-lived branches, and they differ in who changes
them. `eb/main` holds the RTEMS baseline of the rtems.org repository, the fixes
which the regression test runs need, and the files which build and test RTEMS.
`eb/qual` is `eb/main` plus the specification items and the pre-qualified
RTEMS. A change of `eb/main` reaches every branch, so a maintainer makes it.
You open your pull request against `eb/qual`.

Because `eb/qual` builds on `eb/main`, it has to take each change of `eb/main`.
The workflow Harmonia does this for you: after each change of `eb/main`, it
merges `eb/main` into `eb/qual` through a pull request of its own.

(GitHubWorkflowsCategories)=

## Commit categories

The eb repository mixes two kinds of content. Part of it is the RTEMS of the
rtems.org repository, and the rest exists only in the eb repository, such as
the specification items and the packaging. Each commit belongs to one category,
which the paths of the commit determine. The category tells whether the commit
can go to the rtems.org repository. Only a commit of the `source` category can.
The section
[Commit messages](https://github.com/embedded-brains/rtems/blob/eb/main/CONTRIBUTING.md#commit-messages)
of `CONTRIBUTING.md` defines the categories, their paths and the form of the
commit subject of each category.

This leads to the first rule: **keep each commit within one category.** A
commit which mixes categories cannot go to the rtems.org repository. To split it
afterwards, you have to rewrite the history of your branch. It is much cheaper
to split the work while you write the commits.

The second rule keeps the tree consistent: **leave what you touch clean.** Your
commit formats the specification items and the C language files which it
changes. It also includes the files which its specification items generate,
because a stale generated file breaks the agreement between specification and
sources.

The workflow Olympos checks both rules for each commit, not for the whole tree.
The eb repository holds a large amount of content which is older than the
rules. A check per commit cleans it up file by file, as the work touches it.

(GitHubWorkflowsRoute)=

## Route to the rtems.org repository

The eb repository took the RTEMS of the rtems.org repository at a fixed commit,
the baseline. From time to time, a maintainer rebases the eb repository onto a
new baseline, for example after an RTEMS release. A commit which the rtems.org
repository accepted in the meantime is already part of the new baseline, so it
drops out of the rebase. Each such commit shrinks the gap between the
pre-qualified RTEMS and the mainline, and the next rebase costs less.

You can help with this. When you open your pull request against `eb/qual`, also
open a merge request on gitlab.rtems.org with the commits of the `source`
category. The figure shows the two routes side by side.

```{figure} ../images/upstreaming-workflow.*
---
alt: A commit goes as a pull request to eb/qual and as a merge request to the
  rtems.org repository, and both routes meet at the rebase onto a new baseline
width: 100%
---
The parallel routes of a change
```

The two reviews are independent. The merge request follows the rules of the
rtems.org repository, and its outcome does not hold up your pull request. You
decide which commits you submit. A fix of a driver or of the kernel is a good
candidate, because the mainline benefits from it directly.

Olympos helps you judge a commit. It warns when a commit of the `source`
category does not apply to the baseline of the eb repository. The warning does
not fail the check, but it tells you that the merge request will need a rebase.
{ref}`UpstreamPullRequest` shows how to open the merge request.

(GitHubWorkflowsWorkflows)=

## Workflows

Four workflows carry a change. Olympos checks it, and Hermes reports the result
on the pull request. Harmonia keeps `eb/qual` in step with `eb/main`, and Themis
prepares a reference for the checks of Olympos.

(WorkflowOlympos)=

### Olympos

Olympos inspects, builds and tests every change of `eb/main` and `eb/qual`. It
runs for a pull request and again for the push which merges it. It splits its
work into five jobs, so a failure points to its cause.

```{figure} ../images/olympos-jobs.*
---
alt: The five jobs of Olympos, the export of Themis and the comment of Hermes
width: 100%
---
The jobs of Olympos
```

The first job, Argos, inspects each commit of a pull request against the
rules. A malformed commit cannot enter the eb repository however well it
builds, so the other jobs wait for the inspection. Argos reads its list of
exclusions from the base of the pull request. As a result, a pull request
cannot exempt its own files from the inspection.

Next, Hephaistos provides the tools of 13 architectures. Building them takes
hours, so Hephaistos publishes them as a package and later runs fetch that
package. The three remaining jobs build and test RTEMS with these tools:

- Zerberus builds, tests and packages the pre-qualified RTEMS of four BSPs.

- Sisyphos builds all BSPs of each architecture and runs the tests of the BSPs
  which have a simulator.

- Daidalos builds and tests special configurations, such as SMP with POSIX or
  the multiprocessing configuration.

These three jobs run as soon as the tools of their architecture exist. A tools
failure of an unrelated architecture therefore does not hide a test regression.

(WorkflowHermes)=

### Hermes

Hermes writes the result of Olympos into one comment on the pull request, and
each new run updates that comment. The comment holds the inspection report of
Argos and the package summaries of Zerberus.

A pull request from a fork runs with a token which cannot write a comment. Only
a workflow which the end of another workflow starts may write it, so Hermes is
a workflow of its own.

The pull request produces both reports from its own tree, so a pull request
could forge them. **A green report is not a verdict.** The result of the
Olympos run is the verdict. Hermes therefore shows the reports and says where
they come from.

(WorkflowHarmonia)=

### Harmonia

Harmonia merges each change of `eb/main` into `eb/qual`. It opens a merge pull
request, which merges by itself with a merge commit once the checks of
`eb/qual` pass. A merge commit keeps the commits of `eb/main` as they are. A
rebase or a squash would copy them, and the next merge pull request would offer
the same changes again.

The eb repository builds only a pre-qualified subset of RTEMS. A source outside
that subset sits in an `objextra` build item, which the pre-qualified build
leaves out. The rtems.org repository does not know this split, so its build
changes conflict with it. Harmonia resolves the mechanical conflicts in the
`objextra` item. **An upstream build change never enters the pre-qualified set
by itself**, because that would change what the pre-qualification covers. A
maintainer decides every other conflict, see {ref}`HandleMergePullRequest`.

Harmonia also checks that no build item lists a file which the merge deleted.
Such an item merges without a conflict, but it refers to a file which is gone.

(WorkflowThemis)=

### Themis

Themis exports all specification items of each new `eb/qual` commit and stores
the result. Argos exports only the items which a pull request changes, which is
fast. On its own, it would miss a generated file which an earlier commit left
stale. Argos therefore compares against the stored result of the base of the
pull request.

Without a stored result, Argos exports all items of the base itself, which
takes longer. Themis also fails when its export changes a generated file. A
commit of `eb/qual` then left a generated file stale.

(GitHubWorkflowsExample)=

## Worked example

Suppose you find a defect in the UART driver of the GR740 BSP while you
specify a test for it. You create a branch from `eb/qual` and write two
commits. The first commit fixes the driver in `bsps/sparc/` and has the
category `source`. The second commit adds the specification item of the test
and its generated test code. It has the category `spec`, because its item
exists only in the eb repository.

You push the branch to your fork and open a pull request against `eb/qual`.
Argos inspects both commits. Each touches one category, and each includes its
generated files, so the inspection passes. Hephaistos finds the tools package
of `sparc` and builds nothing. Zerberus builds and tests the pre-qualified
RTEMS of `sparc/gr740`, and Sisyphos runs the simulator tests of `sparc`.
Hermes then shows you one row per commit and the package summary of each BSP.

You also push the first commit to your GitLab fork and open a merge request on
gitlab.rtems.org. A maintainer merges your pull request. Months later, the
RTEMS maintainers have merged your driver fix. When a maintainer moves the eb
repository to the next RTEMS release, your fix arrives with the new baseline,
and the eb repository no longer carries it as its own change.

(GitHubWorkflowsReference)=

## Reference

The file `CONTRIBUTING.md` of the eb repository states the rules: the table of
the branches, the table of the categories, the form of a commit subject and the
local checks. Where this chapter and `CONTRIBUTING.md` differ,
`CONTRIBUTING.md` is right. The workflow files below `.github/` are right about
what a workflow does.

```{table}
---
class: longtable
widths: 13,29,29,29
---
| Workflow | Trigger                                              | Output                                             | Fails when                                              |
| -------- | ---------------------------------------------------- | -------------------------------------------------- | ------------------------------------------------------- |
| Olympos  | a push to or a pull request against `eb/main` or `eb/qual`, a manual run | the inspection report, the package summaries, the test reports | a commit breaks a rule, or a build or a test fails |
| Hermes   | the end of an Olympos run of a pull request          | one comment on the pull request                    | never. Without an open pull request, it comments nothing |
| Harmonia | a push to `eb/main`, a manual run                    | the branch `harmonia/main` and a merge pull request with auto-merge | a conflict needs a decision, or a build item lists a deleted file |
| Themis   | a push to `eb/qual`, a manual run for one commit     | the stored export result of the commit             | the export changes a generated file                     |
```

```{table}
---
class: longtable
widths: 15,85
---
| Job        | Work                                                                          |
| ---------- | ----------------------------------------------------------------------------- |
| Argos      | inspects each commit of a pull request                                        |
| Hephaistos | builds the tools of 13 architectures and publishes them as a package          |
| Zerberus   | builds, tests and packages the pre-qualified RTEMS of four BSPs               |
| Sisyphos   | builds all BSPs of an architecture and runs the tests of its simulator BSPs  |
| Daidalos   | builds and tests five special configurations                                  |
```

Olympos reuses the results of earlier runs. A pull request reads the stored
results of the branch which it targets and writes none, because no other run
could use them. A push writes the stored results of its branch.

```{table}
---
class: longtable
widths: 25,40,35
---
| Stored result               | Content                                        | Writer                              |
| --------------------------- | ---------------------------------------------- | ----------------------------------- |
| tools package               | the tools of one architecture and their source | Hephaistos, for a push to `eb/main` |
| workspace                   | the package workspace of one BSP               | Zerberus, for a push                |
| build directory, test logs  | the build and the test reports of one job      | Sisyphos and Daidalos, for a push   |
| export result               | the export of all items of an `eb/qual` commit | Themis                              |
```

The tools package lives in the GitHub container registry of the eb repository.
Its tag names the operating system of the runner, the architecture and the
recipe of the tools. All branches use the recipe of `eb/main`, so they share one
set of tools. Nothing which names a branch may enter that tag. The package
contains GPL code, so it carries the source of the tools as well.
