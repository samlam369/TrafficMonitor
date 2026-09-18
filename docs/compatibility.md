# Compatibility and desktop validation

## Scope

Overlay placement targets the resolved primary taskbar with a `Start` child
window. It is opt-in and requires left-side placement. StartAllBack is the
motivating compatibility case; this does not imply support for every StartAllBack
version or every replacement taskbar. Secondary taskbar overlay is outside the
initial scope.

Support for specific Windows and StartAllBack versions should be established
through repeatable desktop testing. No broad product/version support matrix
is currently claimed.

## Known limits

- Overlay does not reserve Widgets/weather or icon space, so these can overlap
  the monitor. The native Widgets-width setting does not reserve space in
  overlay mode.
- Three-row layout needs enough height for the selected font; otherwise it
  falls back to two rows without changing the saved setting.
- Two-row item bounds can fit while a large font still clips within a row.
- Geometry tests cannot establish transparency, text rendering or plugin quality.
- Full builds, non-x64 configurations, additional taskbar replacements and
  untested Windows versions require separate verification.

## Validation coverage

Automated checks cover the x64 Lite build and layout geometry. They do not
verify desktop integration or rendering. See the
[fork review](https://github.com/samlam369/TrafficMonitor/pull/1) for build checks.

### 1.86-flex.1 release coverage

User-reported desktop validation covers **x64 Lite on Windows 11 25H2 with
StartAllBack**:

- Several days of daily use without reported stability issues.
- Taskbar placement along the left, bottom and right screen edges.
- Automatic fallback from three rows to two when taskbar height is reduced.
- Taskbar display reappearing after restarting Windows Explorer in Task Manager.

This validates the tested setup, not every StartAllBack version. Native Windows
taskbars, other taskbar replacements, full builds, x86/ARM64EC and
multi-monitor/mixed-DPI setups remain unverified for this release.
These observations do not establish a pass for every settings combination,
custom plugin, extreme font/spacing value or deployment rollback.

Desktop validation is still partial. The checklist below defines the coverage
needed for release review; it is not a list of passed tests. Results should
identify the tested commit and environment.

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
