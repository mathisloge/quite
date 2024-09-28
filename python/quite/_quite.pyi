"""
quite - a ui testing framework. See https://github.com/mathisloge/ng-quite
"""

from __future__ import annotations

__all__ = ["Application", "RemoteObject"]

class Application:
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs): ...
    def __init__(self, application_path: str) -> None: ...
    def exit(self) -> None:
        """
        Request to exit the application.
        """

    def find_object(self, object_query: str) -> RemoteObject:
        """
        try to get an instance of an object by the given query.
        """

class RemoteObject:
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs): ...
    @property
    def id(self) -> int:
        """
        returns the id of the remote object.
        """

__version__: str = "0.0.1"
