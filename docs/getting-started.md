# Getting Started

## Introduction

**quite** is an end-to-end testing framework for Qt applications.

It provides a simple API that you can use from **C++** or **Python**, while still letting you choose your preferred test framework (e.g. GoogleTest, pytest, Catch2, etc.).

With quite, you can:

- Stimulate your application (e.g. trigger UI actions).
- Capture screenshots of controls.
- Query properties from your application.

To use quite, you’ll need to install two parts:

1. **The Probe** – code injected into your Application Under Test (AUT).
2. **The Test API** – the library you use in your test code to talk to the AUT.

[:material-arrow-right: Probe Installation](#probe)
[:material-arrow-right: Test API Installation](#test-api)

!!! info "Minimum language and Qt version"
    * Only **Qt 6.5** and onward is supported.
    * **C++23** required to compile the project.
    * **C++17** required to consume the testing API.
    * **gcc-13** required to compile the project.
    * currently only tested with gcc and linux.

---

## Installation

### Probe

The probe runs **inside your AUT** and sets up a gRPC server that quite uses to communicate with your application.

You’ll need to add the probe to your application during build time.

#### Install with vcpkg

```bash
vcpkg install quite[probeqt]
```

### Install with CPM.cmake

```cmake
cpmaddpackage(
  NAME quite
  URI "gh:mathisloge/quite@1.3.0"
  OPTIONS "QUITE_BUILD_PROBE_QT ON"
)
```

## Test API

The test API is what your test code uses to talk to the AUT’s probe.

You can install it for C++ or Python.

### vcpkg

```bash
vcpkg install quite[testapi]
```

### CPM.cmake

```cmake
cpmaddpackage(
  NAME quite
  URI "gh:mathisloge/quite@1.3.0"
  OPTIONS "QUITE_BUILD_TEST_API ON"
)

```

### Python

```bash
pip3 install https://github.com/mathisloge/quite/archive/refs/tags/v1.3.0.zip
```
