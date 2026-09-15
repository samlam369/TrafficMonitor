# Contributor and agent guidance

- Read `docs/development.md` and the documentation relevant to the change.
- If `.local/AGENTS.md` exists, read it before deployment or environment-specific testing. Local context is untracked and must never be published.
- Inspect the branch and working tree before edits. Preserve unrelated changes.
- Keep independent changes in separate Conventional Commits, with a rationale and implementation bullets. Stage explicit paths or hunks.
- Preserve native taskbar detection and upstream behavior outside opt-in features.
- Record automated tests separately from actual desktop validation and untested limitations.
- A source change or build does not deploy an executable. Follow the local normal-exit, backup and rollback procedure for deployments.
- Never commit runtime configuration, credentials, diagnostic captures or build products.
- Use bounded independent agent tasks when useful; coordinate ownership of shared files.
