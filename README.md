# TrafficMonitor: flexible taskbar display

This fork of [TrafficMonitor](https://github.com/zhongyang219/TrafficMonitor)
adds more control over taskbar layout and placement while keeping upstream
behavior as the default. StartAllBack compatibility is one application of the
optional overlay placement mode.

## What changes?

- **Keep taskbar icons together**

  - **Problem:** Showing TrafficMonitor on the left can create a large gap
    between Task View and app icons on taskbars such as StartAllBack.
  - **New behavior:** Enable **Keep taskbar icons in place** below the left-side
    placement option. The monitor sits at the left edge (top on vertical
    taskbars) without shifting the icons. It may overlap Widgets/weather or
    icons when the taskbar fills up.

- **Fit more readings on a tall taskbar**

  - **Problem:** Two rows can leave vertical space unused while readings spread
    across more columns and take up taskbar width.
  - **New behavior:** Choose three rows in **Layout and placement...** to stack
    more readings in each column. If the taskbar is too short for the selected
    font, the display falls back to two rows automatically.

- **Use a shorter CPU frequency label**

  - **Problem:** The fixed `GHz` suffix takes up space in a compact display.
  - **New behavior:** In **Unit Settings**, choose `G` instead of `GHz` to show
    values such as `3.41G`. The display uses less width; the value still means
    3.41 GHz.

- **Keep two-row text inside the display when adding spacing**

  - **Problem:** Increasing the gap between two rows can push text beyond the
    display's top and bottom edges, cutting it off.
  - **New behavior:** The gap stays inside the display and is limited to leave
    room for the measured font height. A font too large for two rows can still
    be clipped even with no gap.

Overlay placement, three rows and compact units are opt-in. Existing INI keys
are retained. Overlay does not reserve space for Widgets/weather or app icons:
they can overlap the monitor.

## Start here

Open **Option Settings > Taskbar Window Settings**:

- **Taskbar window:** select left-side placement, then **Keep taskbar icons in
  place (e.g. StartAllBack)** directly below it to enable edge placement.
- **Unit Settings:** choose whether CPU frequency uses `G` instead of `GHz`.
- **Layout and placement...:** choose two/three rows and adjust applicable offsets.

The icon-preserving option is inactive when left-side placement is off.
Read [settings](docs/settings.md) for activation conditions and examples.

This fork is being prepared for its first reviewed release. Upstream binaries
linked in the preserved documentation do not include these changes. See
[development](docs/development.md) to build from source and
[compatibility](docs/compatibility.md) for the validation checklist and limits.

## Documentation

- [Settings and behavior](docs/settings.md)
- [Architecture and upstream integration](docs/architecture.md)
- [Build and test](docs/development.md)
- [Compatibility and desktop validation](docs/compatibility.md)
- [Contributing](CONTRIBUTING.md)
- [Private local environment template](docs/local-context.example.md)
- Original documentation: [English](README_en-us.md) / [简体中文](docs/upstream/README_zh-cn.md)

## Attribution and license

TrafficMonitor is developed by zhongyang219 and its contributors. This fork
retains the original project history, attribution and [Anti-996 License](LICENSE)
([Chinese translation](LICENSE_CN)). See the original documentation for upstream
features, screenshots and third-party acknowledgements.
