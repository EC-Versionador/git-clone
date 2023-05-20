"""Functions related to the files.txt file."""

from pathlib import Path
from src.classes.data_structures import Repository
from src.classes.archives import Archives


def create_files_txt():
    """Create files.txt file in git folder."""

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    files_txt_path.touch(exist_ok=True)


def add_on_going_commit(commit_id: int = 0):
    """Adds an open commit to the end of the files.txt file.

    Args:
        commit_id (int, optional): commit id.
        Should be zero when it is the first commit in the repository.
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    with open(files_txt_path, "a", encoding="utf-8") as files_txt:
        files_txt.write(f"id:{commit_id}\n")


def on_going_commit_exists(repository: Repository) -> bool:
    """Check if there is an open commit.
    Args:
        repository (Repository): linked list of commits

    Returns:
        bool: whether there is an open commit or not
    """

    if repository.tail_commit is None:
        return False
    if repository.tail_commit.id_ is None:
        return False
    if repository.tail_commit.message is not None:
        return False
    return True


def files_txt_exists() -> bool:
    """Check if the git folder has a files.txt file.

    Returns:
         bool: whether files.txt exists or not
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    return files_txt_path.exists()


def read_files_txt() -> str:
    """Reads the files.txt file.

    Returns:
        str: string containing content read from files.txt
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    with open(files_txt_path, "r", encoding="utf-8") as files_txt:
        return files_txt.read()


def add_file_to_on_going_commit(file_path: str):
    """Adds a file to the end of the files.txt file.

    Args:
        file_path (str): path to file
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    with open(files_txt_path, "a", encoding="utf-8") as files_txt:
        files_txt.write(f"path:{file_path}\nstart:0\nend:0\n")


def write_files_txt(files_txt_content: str):
    """Rewrites the files.txt file.

    Args:
        files_txt_content (str): string containing content to write to files.txt
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.FILES_TXT.value
    with open(files_txt_path, "w", encoding="utf-8") as files_txt:
        files_txt.write(files_txt_content)
