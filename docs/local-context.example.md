# Private local context template

Copy and adapt this outline outside the repository. Do not put real machine
paths, runtime settings or deployment history into this tracked example.

Each checkout/worktree can have a Git-ignored `.local/AGENTS.md` containing an
absolute pointer to the shared private directory and instructions to read it
before deployment or environment-specific testing. Create that pointer when
preparing each worktree; Git does not populate ignored files in new worktrees.

## environment.md

- Source checkout(s) and role of each worktree.
- Installed executable, configuration and plugin directories.
- MSBuild, C++ toolset and SDK locations/versions.
- Windows/taskbar versions, monitor layout, DPI and representative test settings.
- How to identify the running instance without confusing it with a build output.

## deployment.md

1. Record the running version and source commit if known.
2. Exit normally and verify the process has stopped.
3. Back up the executable and any configuration that the operation can change.
4. Copy the intended build output; preserve runtime settings and plugins.
5. Start the intended installation and verify the actual executable path.
6. Check display, positioning, persistence and relevant regression cases.
7. Record results and rollback location; restore the backup if validation fails.

Document the machine's actual normal-exit mechanism, backup layout and rollback
commands here. A source checkout or successful build is not a deployment.

## current-installation.md

Keep the current installed source revision, verified EXE hash, deployment time,
backup location and selected runtime preferences in one place. Update it after
verified deployment; a newly built or pushed commit is not automatically the
installed revision. Other local documents should refer here instead of copying
this mutable state.

## validation-log.md

For each deployment, record date, commit, build configuration/overrides, executable
hash, installed location, backup reference, tests and outcomes, remaining limits,
and whether rollback was exercised. Keep current running-version information
separate from stable environment instructions.

Back up this private directory independently. Git ignore prevents accidental
tracking; it does not provide backup. Old local feature branches can remain
archived snapshots once the public fork has passed migration and deployment
validation; they do not need ongoing development.
