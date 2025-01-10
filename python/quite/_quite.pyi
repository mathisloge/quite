__version__: str
__version_git_ref__: str

class Application:
    def __init__(self, application_path: str) -> None:
        """__init__(self: quite._quite.Application, application_path: str) -> None"""
    def exit(self) -> None:
        """exit(self: quite._quite.Application) -> None

        Request to exit the application.
        """
    def find_object(self, object_query: str) -> RemoteObject:
        """find_object(self: quite._quite.Application, object_query: str) -> quite._quite.RemoteObject

        try to get an instance of an object by the given query.
        """

class RemoteObject:
    def __init__(self, *args, **kwargs) -> None:
        """Initialize self.  See help(type(self)) for accurate signature."""
    @property
    def id(self) -> int: ...
