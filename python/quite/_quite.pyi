# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

import collections.abc
import datetime
import os
import typing
from typing import overload

__version__: str
__version_git_ref__: str

class IExpectBuilder:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def screenshot(self, name: str) -> bool:
        """screenshot(self: quite._quite.IExpectBuilder, name: str) -> bool"""

class Image:
    """Holds the data of an image in the format of RGBA. Use .data() with other libraries for more complex use cases"""

    @overload
    def __init__(self) -> None:
        """__init__(*args, **kwargs)
        Overloaded function.

        1. __init__(self: quite._quite.Image) -> None

        2. __init__(self: quite._quite.Image, file_path: os.PathLike | str | bytes) -> None
        """

    @overload
    def __init__(self, file_path: os.PathLike | str | bytes) -> None:
        """__init__(*args, **kwargs)
        Overloaded function.

        1. __init__(self: quite._quite.Image) -> None

        2. __init__(self: quite._quite.Image, file_path: os.PathLike | str | bytes) -> None
        """

    def data(self) -> ImageView:
        """data(self: quite._quite.Image) -> quite._quite.ImageView"""

    def save_to(self, file_path: os.PathLike | str | bytes) -> None:
        """save_to(self: quite._quite.Image, file_path: os.PathLike | str | bytes) -> None"""

class ImageView:
    """A non owning reference to the data of an Image."""

    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def data(self) -> memoryview:
        """data(self: quite._quite.ImageView) -> memoryview"""

    @property
    def channels(self) -> int:
        """(self: quite._quite.ImageView) -> int"""

    @property
    def height(self) -> int:
        """(self: quite._quite.ImageView) -> int"""

    @property
    def width(self) -> int:
        """(self: quite._quite.ImageView) -> int"""

class ObjectQuery:
    def __init__(self, arg0) -> None:
        """__init__(self: quite._quite.ObjectQuery, arg0: quite::ObjectQueryBuilder) -> None"""

class ObjectQueryBuilder:
    def __init__(self) -> None:
        """__init__(self: quite._quite.ObjectQueryBuilder) -> None"""

    def with_parent(self, parent: ObjectQuery) -> ObjectQueryBuilder:
        """with_parent(self: quite._quite.ObjectQueryBuilder, parent: quite._quite.ObjectQuery) -> quite._quite.ObjectQueryBuilder"""

    @overload
    def with_property(self, key: str, value: typing.SupportsInt) -> ObjectQueryBuilder:
        """with_property(*args, **kwargs)
        Overloaded function.

        1. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsInt) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsFloat) -> quite._quite.ObjectQueryBuilder

        3. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def with_property(
        self, key: str, value: typing.SupportsFloat
    ) -> ObjectQueryBuilder:
        """with_property(*args, **kwargs)
        Overloaded function.

        1. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsInt) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsFloat) -> quite._quite.ObjectQueryBuilder

        3. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def with_property(self, key: str, value: bool) -> ObjectQueryBuilder:
        """with_property(*args, **kwargs)
        Overloaded function.

        1. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsInt) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsFloat) -> quite._quite.ObjectQueryBuilder

        3. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    @overload
    def with_property(self, key: str, value: str) -> ObjectQueryBuilder:
        """with_property(*args, **kwargs)
        Overloaded function.

        1. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsInt) -> quite._quite.ObjectQueryBuilder

        Adds the property to the search requirements

        2. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: typing.SupportsFloat) -> quite._quite.ObjectQueryBuilder

        3. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: bool) -> quite._quite.ObjectQueryBuilder

        4. with_property(self: quite._quite.ObjectQueryBuilder, key: str, value: str) -> quite._quite.ObjectQueryBuilder
        """

    def with_type(self, type_name: str) -> ObjectQueryBuilder:
        """with_type(self: quite._quite.ObjectQueryBuilder, type_name: str) -> quite._quite.ObjectQueryBuilder"""

class Probe:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def exit(self) -> None:
        """exit(self: quite._quite.Probe) -> None

        Request to exit the application.
        """

    def find_object(self, object_query) -> RemoteObject:
        """find_object(self: quite._quite.Probe, object_query: quite::ObjectQuery) -> quite._quite.RemoteObject

        Try to get an instance of an object by the given query. If the object might not be present directly, use try_find_object.
        """

    def try_find_object(
        self, object_query, timeout: datetime.timedelta
    ) -> RemoteObject:
        """try_find_object(self: quite._quite.Probe, object_query: quite::ObjectQuery, timeout: datetime.timedelta) -> quite._quite.RemoteObject

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
        self,
        name: str,
        path_to_application: str,
        args: collections.abc.Sequence[str] = ...,
    ) -> Probe:
        """launch_qt_probe_application(self: quite._quite.ProbeManager, name: str, path_to_application: str, args: collections.abc.Sequence[str] = []) -> quite._quite.Probe"""

class Property:
    """Represents a property which is tied to a remote objects property"""

    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def fetch(self) -> bool | int | int | float | str | RemoteObject:
        """fetch(self: quite._quite.Property) -> bool | int | int | float | str | quite._quite.RemoteObject"""

    def value(self) -> bool | int | int | float | str | RemoteObject:
        """value(self: quite._quite.Property) -> bool | int | int | float | str | quite._quite.RemoteObject"""

    def wait_for_value(
        self,
        target_value: (
            bool
            | typing.SupportsInt
            | typing.SupportsInt
            | typing.SupportsFloat
            | str
            | RemoteObject
        ),
        timeout: datetime.timedelta,
    ) -> bool | int | int | float | str | RemoteObject:
        """wait_for_value(self: quite._quite.Property, target_value: bool | typing.SupportsInt | typing.SupportsInt | typing.SupportsFloat | str | quite._quite.RemoteObject, timeout: datetime.timedelta) -> bool | int | int | float | str | quite._quite.RemoteObject"""

    def write(
        self,
        value: (
            bool
            | typing.SupportsInt
            | typing.SupportsInt
            | typing.SupportsFloat
            | str
            | RemoteObject
        ),
    ) -> None:
        """write(self: quite._quite.Property, value: bool | typing.SupportsInt | typing.SupportsInt | typing.SupportsFloat | str | quite._quite.RemoteObject) -> None"""

class RemoteObject:
    """Represents an object from the test application."""

    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""

    def invoke(
        self,
        method: str,
        parameters: collections.abc.Sequence[
            bool
            | typing.SupportsInt
            | typing.SupportsInt
            | typing.SupportsFloat
            | str
            | RemoteObject
        ],
    ) -> bool | int | int | float | str | RemoteObject:
        """invoke(self: quite._quite.RemoteObject, method: str, parameters: collections.abc.Sequence[bool | typing.SupportsInt | typing.SupportsInt | typing.SupportsFloat | str | quite._quite.RemoteObject]) -> bool | int | int | float | str | quite._quite.RemoteObject

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

def expect(object: RemoteObject) -> IExpectBuilder:
    """expect(object: quite._quite.RemoteObject) -> quite._quite.IExpectBuilder"""

def make_query() -> ObjectQueryBuilder:
    """make_query() -> quite._quite.ObjectQueryBuilder

    Create a new ObjectQuery
    """
