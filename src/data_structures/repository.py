"""Repository manipulations."""

from src.data_structures.commit import print_commit
from src.classes.data_structures import Repository, Commit


def push_commit_to_repository(repository: Repository, commit: Commit) -> None:
    """Adds a commit to the end of a repository.

    Args:
        repository (Repository): repository dataclass
        commit (Commit): commit dataclass
    """

    tail = repository.tail_commit
    repository.tail_commit = commit
    commit.prev_ = tail
    if tail is None:
        repository.head_commit = commit
    else:
        tail.next_ = commit


def print_repository(repository: Repository, log_content: bool, contents_txt_content: list[str]):
    """Prints repository information.

    Args:
        repository (Repository): linked list of commits
        log_content (bool, optional): wheather it should print the content
        contents_txt_content (list[str]): contents.txt content as a list of lines
    """
    commit = repository.tail_commit
    while commit is not None:
        print_commit(commit, log_content, contents_txt_content)
        commit = commit.prev_
