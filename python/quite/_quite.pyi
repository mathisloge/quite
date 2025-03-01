import datetime
from typing import overload

__version__: str
__version_git_ref__: str

class Application:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def exit(self) -> None:
        """exit(self: quite._quite.Application) -> None

        Request to exit the application.
        """

    def find_object(self, object_query: ObjectQuery) -> RemoteObject:
        """find_object(self: quite._quite.Application, object_query: quite._quite.ObjectQuery) -> quite._quite.RemoteObject

        Try to get an instance of an object by the given query. If the object might not be present directly, use try_find_object.
        """

    def try_find_object(
        self, object_query: ObjectQuery, timeout: datetime.timedelta
    ) -> RemoteObject:
        """try_find_object(self: quite._quite.Application, object_query: quite._quite.ObjectQuery, timeout: datetime.timedelta) -> quite._quite.RemoteObject

        Try to get a object in the specified time.
        """

    def wait_for_connected(self, arg0: datetime.timedelta) -> None:
        """wait_for_connected(self: quite._quite.Application, arg0: datetime.timedelta) -> None

        Wait until the application is connected.
        """

class ApplicationManager:
    def __init__(self) -> None:
        """__init__(self: quite._quite.ApplicationManager) -> None"""

    def create_host_application(
        self,
        path_to_application: str,
        args: list[str] = ...,
        environment: dict[str, str] = ...,
    ) -> Application:
        """create_host_application(self: quite._quite.ApplicationManager, path_to_application: str, args: list[str] = [], environment: dict[str, str] = {}) -> quite._quite.Application"""

class ObjectQuery:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

class ObjectQueryBuilder:
    def __init__(self) -> None:
        """__init__(self: quite._quite.ObjectQueryBuilder) -> None"""

    @overload
    def add_property(self, key: str, value: int) -> ObjectQueryBuilder:
        """add_property(*args, **kwargs)
        Overloaded function.

        1. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: int) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: float) -> quite._quite.ObjectQueryBuilder

        3. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def add_property(self, key: str, value: float) -> ObjectQueryBuilder:
        """add_property(*args, **kwargs)
        Overloaded function.

        1. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: int) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: float) -> quite._quite.ObjectQueryBuilder

        3. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def add_property(self, key: str, value: bool) -> ObjectQueryBuilder:
        """add_property(*args, **kwargs)
        Overloaded function.

        1. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: int) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: float) -> quite._quite.ObjectQueryBuilder

        3. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def add_property(self, key: str, value: str) -> ObjectQueryBuilder:
        """add_property(*args, **kwargs)
        Overloaded function.

        1. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: int) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: float) -> quite._quite.ObjectQueryBuilder

        3. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. add_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    def query(self) -> ObjectQuery:
        """query(self: quite._quite.ObjectQueryBuilder) -> quite._quite.ObjectQuery

        Creates a object query to be used to e.g. find an object.
        """

    def set_parent(
        self, parent_object_query_builder: ObjectQueryBuilder
    ) -> ObjectQueryBuilder:
        """set_parent(self: quite._quite.ObjectQueryBuilder, parent_object_query_builder: quite._quite.ObjectQueryBuilder) -> quite._quite.ObjectQueryBuilder

        Sets the parent.
        """

class RemoteObject:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def mouse_action(self) -> None:
        """mouse_action(self: quite._quite.RemoteObject) -> None"""

    def take_snapshot(self) -> None:
        """take_snapshot(self: quite._quite.RemoteObject) -> None"""
