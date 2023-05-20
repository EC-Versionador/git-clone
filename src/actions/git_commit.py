"""Git commit command."""

from src.classes.validation_exceptions import RepositoryNotInitializedException
from src.files.contents_txt import (
    file_exists,
    get_last_written_line_index,
    write_file_to_contents,
)
from src.parser.files_to_data_structure import string_to_data_structure
from src.parser.data_structure_to_file import data_structure_to_string
from src.files.files_txt import add_on_going_commit, read_files_txt, write_files_txt
from src.validations.repository_validation import validate_repository


def git_commit(message: str):
    """Executes git commit command.

    Args:
        message (str): Commit message.
    """

    validate_repository()
    files_txt_content = read_files_txt()
    repository = string_to_data_structure(files_txt_content)

    on_going_commit = repository.tail_commit
    if on_going_commit is None or on_going_commit.id_ is None:
        raise RepositoryNotInitializedException("Open commit not found.")

    on_going_commit.message = message
    current_file = on_going_commit.tail_file
    while current_file is not None:
        if not file_exists(current_file.path or ""):
            current_file = current_file.prev_
            continue
        start = get_last_written_line_index() + 1
        write_file_to_contents(current_file.path or "")
        end = get_last_written_line_index()
        current_file.start = start
        current_file.end = end
        current_file = current_file.prev_

    files_txt_content = data_structure_to_string(repository)
    write_files_txt(files_txt_content)
    add_on_going_commit(on_going_commit.id_ + 1)
    
