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

- Overlay does not reserve icon space. Dense taskbar content can overlap it.
- Three-row layout needs enough height for the selected font; otherwise it
  falls back to two rows without changing the saved setting.
- Two-row item bounds can fit while a large font still clips within a row.
- Geometry tests cannot establish transparency, text rendering or plugin quality.
- Full builds, non-x64 configurations, additional taskbar replacements and
  untested Windows versions require separate verification.

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
| Settings | Exercise Apply, Cancel, OK and reopen; confirm saved values and control applicability. |
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
