from __future__ import annotations

__all__ = ["Application", "RemoteObject"]

class Application:
    def __init__(self, arg0: str) -> None: ...
    def exit(self) -> None: ...
    def find_object(self, arg0: str) -> ...: ...

class RemoteObject:
    @property
    def id(self) -> int: ...

__version__: str = "0.0.1"
