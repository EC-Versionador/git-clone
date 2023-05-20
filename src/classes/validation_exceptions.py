"""Custom exceptions used for validation."""


class InvalidCommandException(Exception):
    """Exception raised for invalid commands."""

    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)


class RepositoryNotInitializedException(Exception):
    """Exception raised when trying to make operations before initializing the repository."""

    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)


class FileNotFoundException(Exception):
    """Exception raised when a file is not found."""

    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)
        
class CommitNotFoundException(Exception):
    """Exception raised when a commit id is not found in the files.txt."""

    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)