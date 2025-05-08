---
draft: false 
date: 2025-05-08 
authors:
  - mathisloge
categories:
  - General
---

# Hello world 🎉

I’m excited to introduce quite, an open‑source C++ library with python bindings designed to make end‑to‑end UI testing in Qt feel… well, not quite so painful.

For now it's just Qt but I hope that the project is ready to take on other UI frameworks as well. Time will tell.

## What does **quite** do?

At its core, **quite** lets you automate and inspect an application running on any device where you’ve installed a small “remote manager” daemon. From your test code, you can:

* **Start** and **stop** the application remotely

* Discover any object in the running app and inspect its class name, methods, and properties via the builtin meta‑object system (either registered with Qt-Meta-System or with the libraries provided one).

* Invoke methods dynamically

* Read and wait on property values, with configurable timeouts

* Capture screenshots of individual objects and compare them against reference images

* Simulate mouse actions — clicks, drags, moves — targeted at any object

* Write tests in either C++ or python, with the same API


This marks the initial release.
The project is now entering a refactoring and API refinement phase, with no new features planned during this cycle.

If you have any questions, feel free to leave a comment below. Bugs or issues can be reported via the [GitHub issue tracker](https://github.com/mathisloge/ng-quite/issues).

I hope this project proves useful and contributes to improving and stabilizing your application. 🎉
