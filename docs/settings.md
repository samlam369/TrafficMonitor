# Taskbar settings

Open **Option Settings > Taskbar Window Settings > Layout and placement...**.
The dialog exposes layout options independently of whether Windows reports a
native Windows 11 taskbar. Native-only placement controls remain conditional. The compact CPU frequency
checkbox is in **Taskbar Window Settings > Unit Settings**.

## Options and persisted keys

All keys below belong to the existing `[task_bar]` INI section.

| Key | Default | Behavior |
| --- | --- | --- |
| `taskbar_left_overlay` | `false` | Request overlay placement without moving taskbar icons. Requires left-side placement and a supported primary taskbar with a `Start` child window. |
| `task_bar_wnd_on_left` | `false` | Existing left-side option; means top placement on a vertical overlay taskbar. Turning it off restores the normal placement implementation. |
| `window_offset_left` | `0` | In horizontal overlay mode, offset from the taskbar's left edge. Ignored on the centered cross axis of a vertical overlay. |
| `window_offset_top` | `0` | In vertical overlay mode, offset from the taskbar's top edge. Ignored on the centered cross axis of a horizontal overlay. |
| `taskbar_rows` | `2` | Choose two or three rows on horizontal taskbars with Horizontal arrange disabled. Values other than `3` load as `2`. |
| `cpu_freq_short_unit` | `false` | Use `G` instead of `GHz` in taskbar CPU frequency values and related tooltips. The numeric unit remains GHz; main-window formatting is unchanged. |
| `vertical_margin` | `0` | Existing row spacing, from -10 to 10. Three-row layout treats negative spacing as zero and limits positive spacing to available height. |

Offsets scale with taskbar DPI. Negative horizontal values intentionally move
the monitor left; in edge-overlay mode this can put part of it outside the
taskbar and clip it. Use zero or a positive value for left-edge padding. Overlay is centered across the taskbar's short
axis when it fits (otherwise that coordinate is zero); its active offset moves it along the long axis. The native Windows 11
Widgets reservation and snap-near-Start controls do not apply to overlay mode.
If the requested taskbar is unavailable and selection resolves to the primary
taskbar, activation is evaluated against that resolved taskbar.

## Three rows

Items retain their configured order: top to bottom, then into the next column.
The last column may contain fewer than three items. Plugins that request an
exclusive column keep their existing full-height drawing behavior.

If three text rows cannot fit at the current font size, the monitor uses the
existing two-row layout while retaining the selected three-row setting. Resizing
the taskbar causes the available space to be evaluated again. Horizontal arrange
and vertical taskbars keep their existing layouts.

The two-row spacing correction keeps item rectangles within the window for
positive spacing, and caps the gap to leave room for the measured font. Fonts
taller than half the fixed two-row window can still clip even with no gap; use
a smaller font in that case. **Reset offsets** resets only the enabled horizontal
or vertical offset; it preserves inactive offsets and other settings.

## Example

For a supported primary taskbar, left/top overlay placement with three rows and
compact frequency units:

```ini
[task_bar]
taskbar_left_overlay = true
task_bar_wnd_on_left = true
window_offset_left = 8
window_offset_top = 8
horizontal_arrange = false
taskbar_rows = 3
cpu_freq_short_unit = true
```

When editing INI manually, exit TrafficMonitor normally first, update the
existing section without duplicating keys, then restart. The program saves
settings on exit and may overwrite edits made while it is running.

Disable overlay, select two rows and disable compact units to restore the
corresponding upstream behavior. A stored overlay preference does not guarantee
that the current taskbar meets its activation conditions.
