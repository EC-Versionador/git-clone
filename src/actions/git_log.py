"""Git log command."""


from src.data_structures.repository import print_repository
from src.files.contents_txt import read_contents_txt
from src.parser.files_to_data_structure import string_to_data_structure
from src.files.files_txt import read_files_txt
from src.validations.repository_validation import validate_repository


def git_log(log_content: bool = False):
    """Executes git log command.

    Args:
        log_content (bool, optional): wheather it should print the content
        of the files or not. Defaults to False.

    Raises:
        RepositoryNotInitializedException: If there is any problem with the git folder.
    """

    validate_repository()
    files_txt_content = read_files_txt()
    contents_txt_content = read_contents_txt().split("\n")
    repository = string_to_data_structure(files_txt_content)

    print_repository(repository, log_content, contents_txt_content)
