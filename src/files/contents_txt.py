"""Functions related to the contents.txt file."""

from pathlib import Path
from src.classes.data_structures import File
from src.classes.archives import Archives


def create_contents_txt():
    """Create contents.txt file in git folder."""
    files_txt_path = (
        Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    )
    files_txt_path.touch(exist_ok=True)


def contents_txt_exists():
    """Check if the git folder has a contents.txt file."""

    contents_txt_path = (
        Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    )

    return contents_txt_path.exists()


def get_last_written_line_index() -> int:
    """Get the index of last line of the contents.txt file.

    Returns:
        int: index of last line of the contents.txt file
    """

    contents_txt_path = (
        Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    )

    with open(contents_txt_path, "r", encoding="utf-8") as contents_txt:
        lines = contents_txt.readlines()

    return len(lines)


def read_file(file_path: str) -> str:
    """Reads the file.

    Args:
        file_path (str): path to file

    Returns:
        str: content of the file
    """

    with open(file_path, "r", encoding="utf-8") as file:
        return file.read()


def write_to_contents_txt(file_contents: str):
    """Writes to the contents.txt file.

    Args:
        file_contents (str): content to be written to the file
    """

    contents_txt_path = (
        Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    )

    with open(contents_txt_path, "a", encoding="utf-8") as contents_txt:
        contents_txt.write(file_contents)


def file_exists(file_path: str) -> bool:
    """Check if the file exists.

    Args:
        file_path (str): path to file

    Returns:
        bool: whether the file exists or not
    """

    return Path(file_path).exists()


def write_file_to_contents(file_path: str):
    """Writes a file to the contents.txt file.

    Args:
        file_path (str): path to file
    """

    contents_txt_path = (
        Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    )

    with (
        open(file_path, "r", encoding="utf-8") as file,
        open(contents_txt_path, "a", encoding="utf-8") as contents_txt,
    ):
        contents_txt.write(f"{file.read()}\n")


def read_contents_txt():
    """Reads the contents.txt file.

    Returns:
        str: string containing content read from contents.txt
    """

    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value / Archives.CONTENTS_TXT.value
    with open(files_txt_path, "r", encoding="utf-8") as files_txt:
        return files_txt.read()


def rewrite_file(file_: File, contents_txt_content: list[str]):
    """Deletes all text from file and writes it again based on the information on the contents.txt file.

    Args:
        file_ (File): information about the file
        contents_txt_content (list[str]): contents.txt content as a list of lines
    """
    
    path = file_.path or ""
    start = file_.start or 0
    end = file_.end or 0
    
    with open(path, "w", encoding="utf-8") as file:
        file.write("\n".join(contents_txt_content[start - 1:end]))