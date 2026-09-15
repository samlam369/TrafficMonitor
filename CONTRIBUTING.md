# Contributing

This fork focuses on flexible taskbar display while preserving upstream behavior
outside optional extensions. Read [development](docs/development.md),
[architecture](docs/architecture.md) and the relevant [settings](docs/settings.md)
before changing code.

## Changes

- Keep one logical change per commit. Use Conventional Commits with a lowercase
  scope and imperative subject, a short rationale, and implementation bullets.
- Stage explicit paths or hunks. Preserve unrelated work.
- Keep native taskbar detection separate from optional placement capabilities.
- Preserve existing INI keys and defaults unless a migration is intentional.
- Update settings and compatibility documentation when behavior changes.
- Report automated checks separately from desktop testing and untested cases.
- Do not commit runtime settings, build products, personal paths or captures.

For a bug report, include the fork commit/version, Windows build, taskbar product
and version, orientation, monitor/DPI setup, relevant non-sensitive settings,
reproduction steps, and expected versus actual behavior. State whether disabling
the optional feature changes the result.

## Upstream relationship

Retain upstream attribution and licensing. Separate general fixes from fork
features. Integrate upstream on a dedicated branch, review shared-code changes,
and validate before merging. Keep machine-specific deployment instructions in
private local context, not in a separate product branch.
