import datetime
import os
from typing import overload

__version__: str
__version_git_ref__: str

class Image:
    @overload
    def __init__(self) -> None:
        """__init__(*args, **kwargs)
        Overloaded function.

        1. __init__(self: quite._quite.Image) -> None

        2. __init__(self: quite._quite.Image, file_path: os.PathLike) -> None
        """

    @overload
    def __init__(self, file_path: os.PathLike) -> None:
        """__init__(*args, **kwargs)
        Overloaded function.

        1. __init__(self: quite._quite.Image) -> None

        2. __init__(self: quite._quite.Image, file_path: os.PathLike) -> None
        """

    def data(self) -> ImageView:
        """data(self: quite._quite.Image) -> quite._quite.ImageView"""

    def save_to(self, file_path: os.PathLike) -> None:
        """save_to(self: quite._quite.Image, file_path: os.PathLike) -> None"""

class ImageView:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def data(self) -> memoryview:
        """data(self: quite._quite.ImageView) -> memoryview"""

    @property
    def channels(self) -> int: ...
    @property
    def height(self) -> int: ...
    @property
    def width(self) -> int: ...

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

    def create(self) -> ObjectQuery:
        """create(self: quite._quite.ObjectQueryBuilder) -> quite._quite.ObjectQuery

        Creates a object query to be used to e.g. find an object.
        """

    def set_parent(
        self, parent_object_query_builder: ObjectQueryBuilder
    ) -> ObjectQueryBuilder:
        """set_parent(self: quite._quite.ObjectQueryBuilder, parent_object_query_builder: quite._quite.ObjectQueryBuilder) -> quite._quite.ObjectQueryBuilder

        Sets the parent.
        """

class Probe:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def exit(self) -> None:
        """exit(self: quite._quite.Probe) -> None

        Request to exit the application.
        """

    def find_object(self, object_query: ObjectQuery) -> RemoteObject:
        """find_object(self: quite._quite.Probe, object_query: quite._quite.ObjectQuery) -> quite._quite.RemoteObject

        Try to get an instance of an object by the given query. If the object might not be present directly, use try_find_object.
        """

    def try_find_object(
        self, object_query: ObjectQuery, timeout: datetime.timedelta
    ) -> RemoteObject:
        """try_find_object(self: quite._quite.Probe, object_query: quite._quite.ObjectQuery, timeout: datetime.timedelta) -> quite._quite.RemoteObject

        Try to get a object in the specified time.
        """

    def wait_for_connected(self, timeout: datetime.timedelta = ...) -> None:
        """wait_for_connected(self: quite._quite.Probe, timeout: datetime.timedelta = datetime.timedelta(seconds=5)) -> None

        Wait until the application is connected.
        """

class ProbeManager:
    def __init__(self) -> None:
        """__init__(self: quite._quite.ProbeManager) -> None"""

    def connect_to_probe(self, name: str) -> Probe:
        """connect_to_probe(self: quite._quite.ProbeManager, name: str) -> quite._quite.Probe"""

    def launch_qt_probe_application(
        self, name: str, path_to_application: str, args: list[str]
    ) -> Probe:
        """launch_qt_probe_application(self: quite._quite.ProbeManager, name: str, path_to_application: str, args: list[str]) -> quite._quite.Probe"""

class Property:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def fetch(self) -> bool | int | int | float | str | RemoteObject:
        """fetch(self: quite._quite.Property) -> Union[bool, int, int, float, str, quite._quite.RemoteObject]"""

    def value(self) -> bool | int | int | float | str | RemoteObject:
        """value(self: quite._quite.Property) -> Union[bool, int, int, float, str, quite._quite.RemoteObject]"""

    def wait_for_value(
        self,
        target_value: bool | int | int | float | str | RemoteObject,
        timeout: datetime.timedelta,
    ) -> bool | int | int | float | str | RemoteObject:
        """wait_for_value(self: quite._quite.Property, target_value: Union[bool, int, int, float, str, quite._quite.RemoteObject], timeout: datetime.timedelta) -> Union[bool, int, int, float, str, quite._quite.RemoteObject]"""

class RemoteObject:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def invoke(self, method: str) -> None:
        """invoke(self: quite._quite.RemoteObject, method: str) -> None

        Invokes the given method. Has to be the fully qualified name. If the qualified name is unknown, use the meta API to query the methods.
        """

    def mouse_action(self) -> None:
        """mouse_action(self: quite._quite.RemoteObject) -> None"""

    def property(self, name: str) -> Property:
        """property(self: quite._quite.RemoteObject, name: str) -> quite._quite.Property

        Reads a property from the object
        """

    def take_snapshot(self) -> Image:
        """take_snapshot(self: quite._quite.RemoteObject) -> quite._quite.Image"""
