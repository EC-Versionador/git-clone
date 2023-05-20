"""Commit manipulations."""

from src.classes.data_structures import Commit, File


def push_file_to_commit(commit: Commit, file_: File) -> None:
    """Adds a file to the end of a commit.

    Args:
        commit (Commit): commit dataclass
        file_ (File): file dataclass
    """

    tail = commit.tail_file
    commit.tail_file = file_
    file_.prev_ = tail
    if tail is None:
        commit.head_file = file_
    else:
        tail.next_ = file_


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


def print_commit(commit: Commit, log_content: bool, contents_txt_content: list[str]):
    """Prints commit information.

    Args:
        commit (Commit): linked list of files
        log_content (bool, optional): wheather it should print the content
        contents_txt_content (list[str]): contents.txt content as a list of lines
    """
    
    print(f"Commit id: {commit.id_}")
    print(f"Commit message: {commit.message}")
    current_file = commit.tail_file
    while current_file is not None:
        print(f"File path: {current_file.path}")
        if not log_content:
            current_file = current_file.prev_
            continue
        start = current_file.start or 0
        end = current_file.end or 0
        print("\n".join(contents_txt_content[start - 1:end]))
        current_file = current_file.prev_
