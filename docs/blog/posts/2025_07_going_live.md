---
draft: false
date: 2025-07-27
authors:
  - mathisloge
categories:
  - General
---

# Hello world 🎉

I’m excited to introduce quite, an open‑source C++ library with python bindings designed to make end‑to‑end UI testing in Qt feel… well, not quite so painful.

Originally, I planned to release it a bit later, but I now want to test my own applications — and it’s far easier if the library is already public. 😄

For now it's just Qt but I hope that the project is ready to take on other UI frameworks as well. Time will tell.

<!-- more -->

## What does **quite** do?

At its core, **quite** lets you automate and inspect an application running on any device where you’ve installed a small “remote manager” daemon. From your test code, you can:

- Discover any object in the running app and inspect its class name, methods, and properties via the built-in meta-object system (either registered with Qt's meta-system or the one provided by the library)
- Invoke methods dynamically
- Read and wait on property values, with configurable timeouts
- Write values to objects
- Capture screenshots of individual objects and compare them against reference images
- Write tests in either C++ or Python, using the same API


This marks the initial release.

If you have any questions, feel free to leave a comment below. Bugs or issues can be reported via the [GitHub issue tracker](https://github.com/mathisloge/quite/issues).

I hope this project proves useful and contributes to improving and stabilizing your application. 🎉
