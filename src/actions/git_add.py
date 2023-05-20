"""Git add command."""

from src.classes.validation_exceptions import RepositoryNotInitializedException
from src.data_structures.commit import file_in_commit
from src.files.files_txt import (
    add_file_to_on_going_commit,
    read_files_txt,
)
from src.validations.repository_validation import validate_repository
from src.validations.file_validation import validate_file
from src.parser.files_to_data_structure import string_to_data_structure


def git_add(file_path: str):
    """Executes git add command.

    Args:
        file_path (str): Path to file to add.

    Raises:
        RepositoryNotInitializedException: If there is any problem with the git folder.
        FileNotFoundException: If the file does not exist.
    """

    validate_repository()
    validate_file(file_path)

    files_txt_content = read_files_txt()
    
    repository = string_to_data_structure(files_txt_content)
    on_going_commit = repository.tail_commit
    if on_going_commit is None:
        raise RepositoryNotInitializedException("Open commit not found.")
    if file_in_commit(on_going_commit, file_path):
        return
    add_file_to_on_going_commit(file_path)
