"""Custom exceptions used for validation."""


class InvalidCommandException(Exception):
    """Exception raised for invalid commands."""

    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)
