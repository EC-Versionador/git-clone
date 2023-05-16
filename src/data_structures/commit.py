"""Commit manipulations."""

from src.classes.data_structures import Commit, File


def push_file_to_commit(commit: Commit, file: File) -> None:
    """Adds a file to the end of a commit.

    Args:
        commit (Commit): commit dataclass
        file (File): file dataclass
    """

    head = commit.head_file
    commit.head_file = file
    file.next_ = head
    if head is None:
        commit.tail_file = file
    else:
        head.prev_ = file


def file_in_commit(commit: Commit, path: str) -> bool:
    """Checks if file exists in commit.

    Args:
        commit (Commit): commit dataclass
        path (str): path to a file

    Returns:
        bool: whether file exists in commit or not
    """

    current = commit.head_file
    while current is not None:
        if current.path == path:
            return True
        current = current.next_
    return False
