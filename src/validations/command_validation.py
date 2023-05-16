"""Validation for commands."""

from src.classes.actions import Actions
from src.classes.validation_exceptions import InvalidCommandException


def validate_arguments(args: list[str]):
    """Validates arguments.

    Args:
        args (list[str]): sys.argv excluding the first element (the script name)

    Raises:
        InvalidCommandException: If the command is invalid
    """

    if len(args) == 0:
        raise InvalidCommandException("No arguments")
    try:
        Actions(args[0])
    except ValueError as exc:
        raise InvalidCommandException("Invalid operation") from exc
    if args[0] == "add" and len(args) != 2:
        raise InvalidCommandException("Add recieves one argument")
    if args[0] == "commit" and len(args) != 3:
        raise InvalidCommandException("Commit recieves three arguments")
    if args[0] == "commit" and args[1] not in ["-m", "--message"]:
        raise InvalidCommandException("Commit second argument must be -m or --message")
    if args[0] == "log" and len(args) != 1:
        raise InvalidCommandException("Log recieves no arguments")
    if args[0] == "init" and len(args) != 1:
        raise InvalidCommandException("Init recieves no arguments")
