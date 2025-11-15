# SmartLogger

Multithreaded logger with optional file recording. Lightweight C++20 project demonstrating a thread-safe console logger with colored output and an optional safe file recorder.

---

## Overview

SmartLogger provides:
- Thread-safe console logging with color per level.
- Formatted messages using C++20 `<format>`.
- Optional persisted logging to file via a thread-safe singleton recorder.

Core files:
- [CMakeLists.txt](CMakeLists.txt)
- [src/CMakeLists.txt](src/CMakeLists.txt)
- [src/main.cpp](src/main.cpp)
- [libraries/CMakeLists.txt](libraries/CMakeLists.txt)
- [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h)
- [libraries/smartlogger/smartlogger.cpp](libraries/smartlogger/smartlogger.cpp)
- [libraries/saferecorder/saferecorder.h](libraries/saferecorder/saferecorder.h)
- [libraries/saferecorder/saferecorder.cpp](libraries/saferecorder/saferecorder.cpp)

---

## Quick start

Requirements:
- CMake >= 3.15
- C++20-capable compiler

Build and run:
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./app
```

(CMake config from [CMakeLists.txt](CMakeLists.txt) builds `libraries` then `src`.)

---

## Usage (API)

Main logger class: [`SmartLogger`](libraries/smartlogger/smartlogger.h)

Enable/disable recording:
- [`SmartLogger::EnableRecord`](libraries/smartlogger/smartlogger.h)

Templated logging helpers:
- [`SmartLogger::Info`](libraries/smartlogger/smartlogger.h)
- [`SmartLogger::Debug`](libraries/smartlogger/smartlogger.h)
- [`SmartLogger::Warn`](libraries/smartlogger/smartlogger.h)
- [`SmartLogger::Error`](libraries/smartlogger/smartlogger.h)
- [`SmartLogger::Fatal`](libraries/smartlogger/smartlogger.h)

File recorder (singleton): [`SafeRecorder`](libraries/saferecorder/saferecorder.h)
- Acquire: [`SafeRecorder::getInstance`](libraries/saferecorder/saferecorder.h)
- Write: [`SafeRecorder::log`](libraries/saferecorder/saferecorder.h)

Example usage: [src/main.cpp](src/main.cpp)

---

## Design notes

Concurrency
- Printing is serialized by `std::mutex mLogMutex` inside [`SmartLogger::printHelper`](libraries/smartlogger/smartlogger.cpp).
- File recording delegates to a singleton [`SafeRecorder`](libraries/saferecorder/saferecorder.h) owning an `std::ofstream`.

Templates & linking
- Templated helpers are defined via inclusion of [libraries/smartlogger/smartlogger.cpp](libraries/smartlogger/smartlogger.cpp) from [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h) to ensure definitions are available.

Color control
- Color and level names live in `mLogSettings` in [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h).
- Color sequences are applied by [`SmartLogger::updatePrintColor`](libraries/smartlogger/smartlogger.cpp).

File path
- Default log file macro: `FileName "../../../app_log.txt"` in [libraries/saferecorder/saferecorder.h](libraries/saferecorder/saferecorder.h).

---

## Configuration & customization

- Change log levels/names/colors in `mLogSettings` at [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h).
- Disable file recording with [`SmartLogger::EnableRecord`](libraries/smartlogger/smartlogger.h).
- Change output path by editing `FileName` in [libraries/saferecorder/saferecorder.h](libraries/saferecorder/saferecorder.h).

---

## Caveats & recommendations

- The example in [src/main.cpp](src/main.cpp) spawns many threads; reduce the count if the environment cannot handle it.
- `SafeRecorder` uses a `static std::unique_ptr` for the singleton; watch static-lifetime ordering.
- `SafeRecorder` throws if the file fails to open (see [libraries/saferecorder/saferecorder.cpp](libraries/saferecorder/saferecorder.cpp)) — catch as needed.

---

## Troubleshooting

- `<format>` errors: ensure the compiler and standard library support C++20 `<format>` or use libfmt.
- File not opened: verify `FileName` in [libraries/saferecorder/saferecorder.h](libraries/saferecorder/saferecorder.h) and permissions.
- Template/link errors: ensure `smartlogger.cpp` is included via [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h).

---

## Files of interest

- [CMakeLists.txt](CMakeLists.txt) — top-level build
- [libraries/CMakeLists.txt](libraries/CMakeLists.txt)
- [libraries/smartlogger/CMakeLists.txt](libraries/smartlogger/CMakeLists.txt)
- [libraries/saferecorder/CMakeLists.txt](libraries/saferecorder/CMakeLists.txt)
- [libraries/smartlogger/smartlogger.h](libraries/smartlogger/smartlogger.h)
- [libraries/smartlogger/smartlogger.cpp](libraries/smartlogger/smartlogger.cpp)
- [libraries/saferecorder/saferecorder.h](libraries/saferecorder/saferecorder.h)
- [libraries/saferecorder/saferecorder.cpp](libraries/saferecorder/saferecorder.cpp)
- [src/CMakeLists.txt](src/CMakeLists.txt)
- [src/main.cpp](src/main.cpp)

---

## License

MIT.

---
