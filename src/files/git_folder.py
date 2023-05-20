"""Git folder functions."""

from pathlib import Path
from src.classes.archives import Archives


def create_git_folder():
    """Create git folder in current directory."""
    files_txt_path = Path.cwd() / Archives.GIT_FOLDER.value
    files_txt_path.mkdir(exist_ok=True, parents=True)


def git_folder_exists():
    """Check if the current folder is a git repository."""

    git_folder_path = Path.cwd() / str(Archives.GIT_FOLDER.value)
    return git_folder_path.exists()
