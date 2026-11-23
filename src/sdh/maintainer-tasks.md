% SPDX-License-Identifier: CC-BY-SA-4.0

% Copyright (C) 2026 embedded brains GmbH & Co. KG

(MaintainerTasks)=

# Maintainer tasks

Contributors change the pre-qualified RTEMS, and a maintainer keeps it
consistent while they do. The maintainer decides which changes enter, keeps the
two long-lived branches in step and brings new RTEMS releases into the
pre-qualification. Each task in this chapter keeps the specification, the
sources and the test results in agreement.

{ref}`GitHubWorkflows` explains the repositories, the branches and the
workflows which these tasks use. Read it first.

(ReviewPullRequest)=

## Review a pull request

A pull request of a contributor enters `eb/qual`. Your review decides whether
its commits keep the pre-qualified RTEMS consistent.

Before you start, wait until the Olympos run of the pull request has ended.

1. Read the comment which Hermes leaves on the pull request. It holds one row
   per commit.

2. Ask the contributor to fix each failed row. A row fails for one of two
   reasons:

   - The commit mixes categories. The contributor splits it.

   - The commit leaves a touched file unformatted or a generated file stale.
     The contributor amends it.

   Both fixes rewrite the commits of the contributor, so you cannot make them
   yourself without taking over the branch.

3. Check the target branch. A pull request of a contributor targets
   `eb/qual`. A pull request against `eb/main` needs a reason which concerns
   all branches, see {ref}`WorkMain`.

4. Ask whether a merge request on gitlab.rtems.org exists for the commits of
   the `source` category. It is welcome but not a condition of the merge, see
   {ref}`GitHubWorkflowsRoute`.

5. Merge the pull request once the checks pass and your review is done.

The change is then part of `eb/qual`. Olympos runs again for the push of the
merge.

(WorkMain)=

## Change eb/main

A change of `eb/main` reaches every branch of the eb repository, so it needs
more care than a change of `eb/qual`. Change `eb/main` only for content which
all branches need. These are the typical cases:

- a fix which the regression test runs of `eb/main` need,

- a change of the continuous integration or of the tools,

- a change of the files which build and test RTEMS.

A fix in a pull request against `eb/qual` usually stays on `eb/qual`. Its route
to the RTEMS mainline is the merge request on gitlab.rtems.org, and it returns
to `eb/main` with the next baseline. Move such a fix to `eb/main` only where
`eb/main` needs it.

1. Create a branch from `eb/main` and commit the change.

2. Open a pull request against `eb/main` and review it as described in
   {ref}`ReviewPullRequest`.

3. Merge the pull request.

Harmonia then opens a merge pull request which brings the change into
`eb/qual`, see {ref}`HandleMergePullRequest`.

(HandleMergePullRequest)=

## Handle the merge pull request

Harmonia brings each change of `eb/main` into `eb/qual` through a merge pull
request. Most merge pull requests merge by themselves once the checks of
`eb/qual` pass. Your part is to read them, and to resolve a merge which
Harmonia cannot decide.

To read a merge pull request, start with its body. It lists each build item
whose conflict Harmonia resolved in the `objextra` sibling. The diff does not
show such an item, because the item itself is unchanged. The title and the body
become the message of the merge commit, so edit them like a commit message or
leave them as they are.

Harmonia fails when the merge needs your decision. This happens for a conflict
which is not a plain addition or removal of a source, and for a build item
which lists a file which the merge deleted. To resolve such a merge:

1. Merge `eb/main` into a new branch from `eb/qual`:

   ```{code-block} none
   ---
   linenos:
   ---
   $ git fetch eb
   $ git switch -c harmonia/main eb/eb/qual
   $ git merge eb/eb/main
   ```

2. For each conflict, decide whether the change belongs in the pre-qualified
   subset. Keep a new source of the rtems.org repository outside the subset.
   Its addition changes what the pre-qualification covers, so it needs a pull
   request of its own.

3. Push the branch and open a pull request against `eb/qual`.

4. Merge the pull request with a merge commit. A rebase or a squash copies the
   commits of `eb/main`, and the next merge pull request offers them again.

Do not let a merge pull request wait. The build items of the eb repository
conflict with most changes of `eb/main`, and the effort of a merge grows with
the gap.

(MoveBaseline)=

## Move to a new RTEMS baseline

The eb repository took the RTEMS of the rtems.org repository at a fixed commit,
the baseline. Each move to a newer baseline brings in the work which the
rtems.org repository accepted since, including the merge requests of
contributors, see {ref}`GitHubWorkflowsRoute`. A good moment for a move is an
RTEMS release.

A move changes what the pre-qualification covers. Plan it with the owners of
the deliveries, and make sure that no pull request against `eb/main` or
`eb/qual` is open.

1. Merge all changes of `eb/main` into `eb/qual`, and linearize `eb/qual` as
   `CONTRIBUTING.md` describes.

2. Rebase the commits of `eb/main` since the old baseline onto the new
   baseline. Skip each commit which the new baseline already contains.

3. Rebase the commits of `eb/qual` since the old `eb/main` onto the new
   `eb/main`. Again, skip each commit which the new baseline already contains.

4. Run the package build of each BSP and compare the results with those of the
   old baseline.

5. Push both branches with a lease on their old tips.

6. Tell the owners of branches and worktrees on `eb/main` and `eb/qual` to
   rebase them.

Both branches then start from the new baseline. Record the old and the new
baseline in the change log of the package, because the next delivery has to
explain the move.
