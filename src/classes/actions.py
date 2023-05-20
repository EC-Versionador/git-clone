"""Actions that the program can execute."""

from enum import Enum


class Actions(Enum):
    """Actions that the program can execute."""

    INIT = "init"
    ADD = "add"
    COMMIT = "commit"
    LOG = "log"
    SHOW = "show"
    REBASE = "rebase"
