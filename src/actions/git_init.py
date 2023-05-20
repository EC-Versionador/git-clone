"""Git init command."""

from src.parser.files_to_data_structure import string_to_data_structure
from src.files.files_txt import (
    create_files_txt,
    add_on_going_commit,
    files_txt_exists,
    on_going_commit_exists,
    read_files_txt,
)
from src.files.contents_txt import create_contents_txt, contents_txt_exists
from src.files.git_folder import create_git_folder, git_folder_exists


def git_init():
    """Executes git init command."""
    if not git_folder_exists():
        create_git_folder()

    if not files_txt_exists():
        create_files_txt()

    if not contents_txt_exists():
        create_contents_txt()

    files_txt_content = read_files_txt()
    repository = string_to_data_structure(files_txt_content)
    if not on_going_commit_exists(repository):
        add_on_going_commit()
