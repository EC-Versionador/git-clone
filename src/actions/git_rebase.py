"""Git rebase command."""


from src.classes.validation_exceptions import CommitNotFoundException
from src.files.contents_txt import read_contents_txt, rewrite_file
from src.files.files_txt import read_files_txt
from src.parser.files_to_data_structure import string_to_data_structure
from src.validations.repository_validation import validate_repository


def git_rebase(commit_id: str):
    """Executes git rebase command.

    Args:
        commit_id (str): Commit id to rebase.

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
            break
        current_commit = current_commit.next_
    
    if current_commit is None:
        raise CommitNotFoundException("Commit not found.")

    current_file = current_commit.tail_file
    while current_file is not None:
        rewrite_file(current_file, contents_txt_content)        
        current_file = current_file.prev_