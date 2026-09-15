# Releases

Fork versions use `<upstream-version>-flex.<sequence>`. The first release is
`1.86-flex.1`, based on upstream 1.86. Git tags add a `v` prefix.
The Windows numeric version keeps upstream's `1.8.6` components and uses the
fourth component for the fork sequence (`1.8.6.1`). Displayed version strings
and About use `1.86-flex.1`.

## Packaging checklist

1. Commit the version strings and release documentation before building.
2. Run the layout tests and build x64 Lite from the release commit.
3. Package TrafficMonitor.exe, tracked skins and language directories, LICENSE,
   LICENSE_CN and a short installation README. Exclude PDBs, runtime settings,
   diagnostic data and locally installed plugins.
4. Verify the ZIP manifest, executable version and hash. Generate SHA256SUMS.txt.
5. Validate normal local deployment/restart of the exact packaged executable.
6. Publish the tag and GitHub pre-release with the ZIP and checksums. Record
   tested coverage and limitations; promote to a stable release separately.

Fork tags (`v*-flex.*`) run the x64 Lite checks on Windows 2022. The inherited
three-architecture Release CI is restricted to the upstream repository.
For an existing immutable release tag, dispatch Fork checks from main with
`source_ref` set to that tag. This validates the tagged source using the current
workflow; it does not replace historical checks or uploaded release assets.

The build uses dynamic MFC and requires the Microsoft Visual C++ v14 x64
Redistributable. Get it from
[Microsoft's supported downloads](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist).

Future upstream updates should be integrated on a separate branch, reviewed
against the opt-in behavior and validated before updating the version base.
