"""Repository manipulations."""

from src.classes.data_structures import Repository, Commit


def push_commit_to_repository(repository: Repository, commit: Commit) -> None:
    """Adds a commit to the end of a repository.

    Args:
        repository (Repository): repository dataclass
        commit (Commit): commit dataclass
    """

    head = repository.head_commit
    repository.head_commit = commit
    commit.next_ = head
    if head is None:
        repository.tail_commit = commit
    else:
        head.prev_ = commit
