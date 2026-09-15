# Development

## Build

Use Windows with Visual Studio 2022 or its Build Tools, the v143 C++ toolset,
MFC for the target architecture, and a Windows SDK. Run commands from a developer
PowerShell where MSBuild and the C++ compiler are available.

The initial fork validation target is x64 Lite:

```powershell
msbuild TrafficMonitor_Lite.sln '-p:Configuration=Release (lite)' -p:Platform=x64 -p:PlatformToolset=v143 -nr:false
```

The output is `Bin/x64/Release (lite)/TrafficMonitor.exe`. If SDK selection fails,
append `-p:WindowsTargetPlatformVersion=<installed-sdk-version>` using an SDK
actually installed on the machine. The full solution and other configurations
remain in the repository but require their own dependency setup and validation.

The pre-build timestamp script is resolved relative to the project and writes
beside itself, so building from the repository root works without bypassing it.
Build timestamps mean rebuilding the same commit can produce a different hash.

## Automated checks

Run the standalone layout checks from a developer PowerShell:

```powershell
./tools/test-layout.ps1
```

These checks validate geometry and layout decisions. They do not exercise
Explorer, taskbar embedding, MFC dialog behavior, font rendering or plugin
painting. Record the exact commit, configuration and results alongside any
[desktop validation](compatibility.md).

## Local deployment

A build does not update an installed executable. Read `.local/AGENTS.md`, if
present, before machine-specific deployment or debugging. Use the
[local context template](local-context.example.md) to establish installation
paths, normal-exit and backup procedures, rollback and validation records.

Never commit runtime INI files, executables, credentials, captures or personal
machine paths. Keep public documentation reproducible without private files.

## Validation status

The review candidate has passed local x64 Lite builds and Windows CI geometry
checks; review builds have also been deployed. See [compatibility](compatibility.md)
for observed desktop behavior and the unresolved settings-open exit failure.
Successful builds, geometry tests and individual screenshots do not replace the
remaining manual checklist. Attach results to the tested commit or release.
