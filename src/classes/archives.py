"""Archives that the program uses to persist its data structures."""

from enum import Enum


class Archives(Enum):
    """Archives that the program uses to persist its data structures."""

    GIT_FOLDER = ".git_clone"
    FILES_TXT = "files.txt"
    CONTENTS_TXT = "commit.txt"
