"""Git folder functions."""

from pathlib import Path
from src.classes.archives import Archives


def git_folder_exists():
    """Check if the current folder is a git repository."""

    git_folder_path = Path.cwd() / str(Archives.GIT_FOLDER)
    return git_folder_path.exists()


def files_txt_exists():
    """Check if the current folder has a files.txt file."""

    files_txt_path = Path.cwd() / str(Archives.GIT_FOLDER) / str(Archives.FILES_TXT)
    return files_txt_path.exists()
