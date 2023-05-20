"""Converts string to repository data structure."""

from src.data_structures.commit import Commit, File, push_file_to_commit
from src.data_structures.repository import Repository, push_commit_to_repository


def string_to_data_structure(files_txt_content: str) -> Repository:
    """Parses files.txt file into a Repository data structure.

    Args:
        files_txt_content (str): Contents read from files.txt.

    Returns:
        Repository: Linked list of commits that are a linked list of files.
    """

    lines = files_txt_content.split("\n")
    repository = Repository()
    last_commit_seen = Commit()
    last_seen_file = File()

    for line in lines:
        if line.startswith("id:") and last_commit_seen.id_ is not None:
            push_commit_to_repository(repository, last_commit_seen)
            last_commit_seen = Commit()
            last_commit_seen.id_ = int(line.split(":")[1])
        elif line.startswith("id:"):
            last_commit_seen.id_ = int(line.split(":")[1])
        elif line.startswith("message:"):
            last_commit_seen.message = line.split(":")[1]
        elif line.startswith("path:"):
            last_seen_file.path = line.split(":")[1]
        elif line.startswith("start:"):
            last_seen_file.start = int(line.split(":")[1])
        elif line.startswith("end:"):
            last_seen_file.end = int(line.split(":")[1])
            push_file_to_commit(last_commit_seen, last_seen_file)
            last_seen_file = File()

    push_commit_to_repository(repository, last_commit_seen)
    return repository
