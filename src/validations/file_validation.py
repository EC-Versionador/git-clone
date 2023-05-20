"""Validation for file."""

from pathlib import Path
from src.classes.validation_exceptions import FileNotFoundException


def validate_file(file_path: str):
    """Check if the file exists.

    Args:
        file_path (Path): Path to file.

    Raises:
        FileNotFoundException: If the file does not exist.
    """

    if not Path(file_path).exists():
        raise FileNotFoundException(f"File {file_path} not found.")
