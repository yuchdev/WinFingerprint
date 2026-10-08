# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Windows Fingerprint Spoofer (`antios`): generates plausible random Windows OS fingerprints (registry values such as ProductName, ProductId, DigitalProductId, BuildLab, install dates) to defeat browser fingerprinting. The project is **Windows-only** (root CMake hard-fails on non-WIN32; it targets MSVC/`/EHa`), so it cannot be built or run on the macOS dev machine. There are no lint tooling or CI configs.

## Build

- CMake (≥3.0), C++17, Boost ≥1.61 (static) required. Pass the Boost location with `-DWINDOWS_BOOST_DIR=<path>`.
- Root `CMakeLists.txt` adds `winfp`, `winapi_helpers`, and a GUI subdirectory. Tests use CTest (`ctest`); the only test is `winapi_helpers/test/functional_test`.
- `winfp_gui/antios.pro` is the alternative Qt/qmake build for the GUI (QML + C++ models).
- Linking needs advapi32, rpcrt4, shell32, kernel32 (`winfp` links Secur32). A `dic` directory with dictionaries must sit next to the executable.
- `.vc140.props` holds Visual Studio 2015 property settings.

## Architecture

- `winfp/` — static library, namespace `antios`. `IFingerprintData` (`generate()`) → `FingerprintDataBase` → `WindowsFingerprint`, which randomly generates a self-consistent fingerprint (edition → build info → product ID, BuildLab/BuildLabEx, install date no earlier than the release date, version-specific keys such as `CSDVersion` or `ReleaseId`). `windows_fpdata.*` holds the static tables of known editions/builds that generation draws from. Consistency between fields is the point; don't randomize fields independently.
- `winapi_helpers/` — header-heavy RAII wrapper library over WinAPI (registry, services, process/elevation, system/user/BIOS info, special paths, single-instance). `winfp` includes it via `winapi_helpers/include`.
- `winfp_gui/` — Qt GUI (`mainwindow`, `settings`, `windowsids`, `infotablemodel`, QML pages). Headers live in `include/antios_gui/`.
- `webrtc/` — WebRTC-leak mitigation tools (Resolver, Pinger, Firewall via WFP, Ethernet), qmake `.pro` files plus a CMake wrapper.
- `prototype/winfp/` — older Qt prototype (gui, `reg-file-wrapper` for parsing `.reg` files, installer, tests). Treat as legacy/reference.
- `plog/` (also copied under `prototype/.../reg-file-wrapper/plog`) — vendored logging library; don't edit.
- `doc/` — architecture diagrams and sample `.reg` exports (`Windows10CurrentVersion.reg`, `Windows81CurrentVersion.reg`) that show the real registry values the generator imitates.

## Gotchas

- The root `CMakeLists.txt` calls `add_subdirectory(antios_gui)`, but the directory was renamed to `winfp_gui` ("Rename dirs" commit). Fix that line before expecting the top-level CMake configure to succeed.
- `winfp/src/CMakeLists.txt` collects sources with `file(GLOB)`, so re-run CMake after adding files.
