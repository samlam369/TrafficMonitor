# Architecture

The fork separates taskbar placement from item layout and formatting. Keep
native taskbar detection factual: enabling an extension must not make a
StartAllBack taskbar report itself as a native Windows 11 taskbar.

## Placement implementations

| Implementation | Responsibility |
| --- | --- |
| `CClassicalTaskbarDlg` | Upstream classic placement and icon-space reservation. |
| `CWin11TaskbarDlg` | Upstream native Windows 11 placement, including Widgets and Start-relative rules. |
| `COverlayTaskbarDlg` | Optional left/top placement within the outer primary taskbar, without resizing or repositioning its icon container. |

Overlay selection requires the option, left-side placement, and the supported
structure on the resolved primary taskbar. Use the same activation decision for
window creation and settings applicability. Store the user's preference
separately from whether overlay is currently active. The icon-preserving
checkbox and its explanation belong beside the parent left-placement option;
the placement subdialog only edits row count and applicable native/offset values.
Disabling the parent disables the effect and its child control without clearing
the stored preference.

Overlay computes orientation from taskbar geometry. Horizontal placement starts
at the left edge plus the horizontal offset and centers vertically. Vertical
placement starts at the top edge plus the vertical offset and centers
horizontally. Its geometry does not depend on the Start button's dimensions or
native Windows alignment/Widgets registry preferences. It reserves no space;
overlap remains possible when other taskbar content reaches the monitor.

The native Windows 11 implementation is kept unchanged from the imported
upstream baseline. Shared drawing, tooltip and plugin behavior remains in the
existing taskbar base class.

## Layout and formatting

Three-row layout uses a dedicated geometry helper. It preserves item order,
exclusive plugin columns and the existing fallback layouts. CPU frequency
formatting and width measurement use the same formatter so the compact suffix
also reduces the reserved width. Neither feature requires changing the plugin
API or shell detection.

## Integrating upstream changes

Keep fork additions in dedicated files where that clarifies responsibility;
line count alone is not a maintenance target. Prefer narrow integration points
for settings persistence, dialog controls and implementation selection.

Fetch upstream, create an integration branch, and review changes to shared
layout, configuration and taskbar lifecycle code even when Git reports no
conflicts. Run the automated checks and relevant desktop checklist before
merging. Keep general bug fixes separate from optional fork features so they
can be reviewed or proposed upstream independently.
