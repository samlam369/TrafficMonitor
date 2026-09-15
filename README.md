# TrafficMonitor: flexible taskbar display

This fork of [TrafficMonitor](https://github.com/zhongyang219/TrafficMonitor)
adds more control over taskbar layout and placement while keeping upstream
behavior as the default. StartAllBack compatibility is one application of the
optional overlay placement mode.

## What changes?

- **Overlay placement:** anchor the monitor at the left or top of a supported
  primary taskbar without moving or shrinking its app-icon container.
- **Three-row layout:** fit items into columns of three on horizontal taskbars,
  with an automatic two-row fallback when the font does not fit.
- **Compact CPU frequency units:** display `3.41G` instead of `3.41GHz`.
- **Two-row spacing:** keep item rectangles inside the taskbar window when
  adding positive vertical spacing.
- **Layout settings:** expose these options and applicable placement offsets
  in the taskbar settings dialog.

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
