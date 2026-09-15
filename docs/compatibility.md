# Compatibility and desktop validation

## Scope

Overlay placement targets the resolved primary taskbar with a `Start` child
window. It is opt-in and requires left-side placement. StartAllBack is the
motivating compatibility case; this does not imply support for every StartAllBack
version or every replacement taskbar. Secondary taskbar overlay is outside the
initial scope.

The earlier local implementation was exercised with StartAllBack on Windows 11
25H2, including horizontal and vertical placement. Those observations are design
evidence, not validation of the refactored fork. No broad product/version support
matrix is claimed before repeatable desktop testing.

## Known limits

- Overlay does not reserve Widgets/weather or icon space. Review screenshots
  confirmed overlap with an enabled weather/Widgets area. This is a placement
  tradeoff, not a condition that the native Widgets-width setting corrects.
- Three-row layout needs enough height for the selected font; otherwise it
  falls back to two rows without changing the saved setting.
- Two-row item bounds can fit while a large font still clips within a row.
- Geometry tests cannot establish transparency, text rendering or plugin quality.
- Full builds, non-x64 configurations, additional taskbar replacements and
  untested Windows versions require separate verification.

## Review observations (2026-09-15)

The x64 Lite candidate has been built, deployed and restarted on the review
machine. User screenshots and read-only geometry capture confirmed horizontal
three-row edge placement. UI wording and spacing were revised during review;
these observations do not establish every version's complete UI coverage.
Build and geometry CI passed for implementation commit `9548b57`; see the
[fork review](https://github.com/samlam369/TrafficMonitor/pull/1) for current checks.

An exit failure was observed with modal settings open: the taskbar display
closed while the tray process stayed alive; further waiting and tray Exit did
not resolve it. The user terminated that instance. The root cause and whether
it is inherited from upstream remain unconfirmed.

A subsequent sequence succeeded: accept the inner placement dialog, accept
Options, then request normal exit after the main window becomes enabled again.
This is a workaround, not a fix. Finish intended edits and close settings before
routine deployment, and verify process exit rather than relying on visible UI.

The latest option dependency/spacing changes still need complete manual review.
Cancel/Apply combinations, native Windows 11 regression, vertical/resize behavior
in the refactor, Explorer recovery, secondary/mixed-DPI displays, custom plugin
rendering and rollback remain unverified unless recorded separately.

## Manual checklist

Record Windows and StartAllBack versions, monitor arrangement, DPI, font,
configuration and tested commit. Mark each case as passed, failed or not tested.
Do not infer a pass from source review or compilation.

| Area | Check |
| --- | --- |
| Baseline | With fork options disabled, compare placement, dimensions and rendering with upstream. |
| Overlay | Verify left/top offsets and cross-axis centering for horizontal and vertical taskbars. |
| Icon layout | Compare Start and task-list rectangles before/after opening the monitor and adding app windows. |
| Resize | Change taskbar height and orientation; verify centering and row fallback are recalculated. |
| Settings | Exercise Apply, Cancel, OK and reopen; toggle left placement and confirm the indented option disables with an inactive explanation while retaining its preference. Check the compact suffix under Unit Settings. |
| Mode switch | Switch left/right and overlay on/off; verify correct window recreation and restoration. |
| Layout | Check two/three rows, incomplete final columns, large fonts and extreme spacing. |
| Plugins | Check ordinary items and plugins requesting an exclusive full-height column. |
| Frequency | Compare long/compact units, reserved width and tooltips. |
| Explorer | Restart Explorer and verify reattachment. |
| Displays | Check unavailable-display fallback and secondary-display normal behavior. |
| DPI | Check different scaling factors and monitor changes, including mixed DPI. |
| Lifecycle | Exit normally, restart, check persistence, then verify deployment rollback. |

Keep screenshots and diagnostic logs private unless reviewed for publication.
A release should summarize actual automated and desktop coverage plus remaining
limitations, with no implication that unchecked cases passed.
