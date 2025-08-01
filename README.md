<div align="center">
  <img src="docs/logo.svg" alt="Quite UI Testing Framework" style="width: 100%" />
</div

quite is a new UI testing framework specifically designed for applications built on the Qt framework.
It aims to provide developers and testers with an efficient way to automate the testing of Qt application user interfaces.

I welcome any feedback, suggestions, and contributions that can help make quite a robust and reliable native UI testing framework!

> [!CAUTION]
> The project is currently in its early development phase and will be until a v2 release is done.
> There is no API stability or other guarantees at this time.
> Changes may occur without notice, and existing code may become incompatible with future versions.
> Until v2 I will not mark any change as breaking change.

# Release and branch strategy

All PRs should be target the develop branch.
Each commit with a `feat:` type, will trigger an minor version bump and a pre-release.
Each breaking change will result in a breaking change (note, that until v2 I will not mark any change as breaking).
At some point I will merge the develop into the main, which results in a new release.
