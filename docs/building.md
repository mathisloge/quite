# Building

## Build against system packages

By default, most dependencies are fetched with [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake).

If you prefer to use **system-installed packages** instead of downloading them directly, configure CPM with one of these options:

- `CPM_USE_LOCAL_PACKAGES=ON`
- `CPM_LOCAL_PACKAGES_ONLY=ON`

See the [CPM reference](https://github.com/cpm-cmake/CPM.cmake?tab=readme-ov-file#cpm_use_local_packages) for details.

!!! tip
    Use `CPM_LOCAL_PACKAGES_ONLY=ON` when integrating with package managers such as **Conan** or **vcpkg**.
    This ensures CPM won’t try to fetch sources remotely.

---

## General dependencies

* [Boost](https://www.boost.org/) >= `1.83.0`
* [gRPC](https://grpc.io/) >= `1.51.1`
* [fmt](https://fmt.dev) >= `11.0.0`
* [Quill](https://github.com/odygrd/quill) >= `10.0.0`
* [EnTT](https://github.com/skypjack/entt) >= `3.15.0`
* [stdexec](https://github.com/NVIDIA/stdexec) >= `daf12bcc46438f88b3c78212363f7b6531338780`
* [asio-grpc](https://github.com/Tradias/asio-grpc) >= `3.3.0`
* [JSON for Modern C++](https://json.nlohmann.me/) >= `3.11.0`
* [stb](https://github.com/nothings/stb) >= `f0569113c93ad095470c54bf34a17b36646bbbb5`

---

## CMake options

The build can be customized with several **CMake options**:

### `QUITE_BUILD_REMOTE_MANAGER`

- **Default:** `ON`
- **Description:** Builds the remote-manager application.
- **Introduced dependencies:**
    - [CLI11](https://cliutils.github.io/CLI11/book/) ≥ `2.4.0`

---

### `QUITE_BUILD_TEST_API`

- **Default:** `ON`
- **Description:** Builds the C++ testing API.

---

### `QUITE_BUILD_PYTHON_TEST_API`

- **Default:** `ON`
- **Description:** Builds the Python testing API module.
- **Dependencies:** Requires `QUITE_BUILD_TEST_API=ON`.
- **Introduced dependencies:**
    - [pybind11](https://pybind11.readthedocs.io/en/stable/) ≥ `3.0.0`

See [Python Usage](python-usage.md) for details.

---

### `QUITE_BUILD_PROBE_QT`

- **Default:** `ON`
- **Description:** Builds the Qt probe.
- **Introduced dependencies:**
    - [Qt](https://www.qt.io/) ≥ `6.5.0`

---

### `QUITE_INSTALL`

- **Default:**: `ON`
- **Description:**: Adds cmake install steps to targets.

---
