"""Validation for repository."""


from src.parser.files_to_data_structure import string_to_data_structure
from src.classes.validation_exceptions import RepositoryNotInitializedException
from src.files.contents_txt import contents_txt_exists
from src.files.files_txt import on_going_commit_exists, files_txt_exists, read_files_txt
from src.files.git_folder import git_folder_exists


def validate_repository():
    """Check if the git folder is set up corectly.

    Raises:
        RepositoryNotInitializedException: If there is any problem with the git folder.
    """

    if not git_folder_exists():
        raise RepositoryNotInitializedException("Git folder not found.")

    if not files_txt_exists():
        raise RepositoryNotInitializedException("Files.txt not found.")

    if not contents_txt_exists():
        raise RepositoryNotInitializedException("Contents.txt not found.")

    files_txt_content = read_files_txt()
    repository = string_to_data_structure(files_txt_content)
    if not on_going_commit_exists(repository):
        raise RepositoryNotInitializedException("Open commit not found.")
