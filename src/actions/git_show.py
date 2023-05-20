"""Git show command."""


from src.data_structures.commit import print_commit
from src.parser.files_to_data_structure import string_to_data_structure
from src.files.contents_txt import read_contents_txt
from src.files.files_txt import read_files_txt
from src.validations.repository_validation import validate_repository


def git_show(commit_id: str):
    """Executes git show command.

    Args:
        commit_id (str): Commit id to show.

    Raises:
        RepositoryNotInitializedException: If there is any problem with the git folder.
    """

    validate_repository()
    files_txt_content = read_files_txt()
    contents_txt_content = read_contents_txt().split("\n")
    repository = string_to_data_structure(files_txt_content)
    current_commit = repository.head_commit
    while current_commit is not None:
        if current_commit.id_ == int(commit_id):
            print_commit(current_commit, True, contents_txt_content)
            return
        current_commit = current_commit.next_
