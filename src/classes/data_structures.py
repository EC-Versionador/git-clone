"""Data structures used to represent the repository and its contents."""

from dataclasses import dataclass
from typing import Optional


@dataclass
class File:
    """A file represented by its path and the start and end of its content in contents.txt."""

    path: str | None = None
    start: int | None = None
    end: int | None = None
    next_: Optional["File"] = None
    prev_: Optional["File"] = None


@dataclass
class Commit:
    """A doubly linked list of files."""

    id_: int | None = None
    message: str | None = None
    next_: Optional["Commit"] = None
    prev_: Optional["Commit"] = None
    head_file: Optional[File] = None
    tail_file: Optional[File] = None


@dataclass
class Repository:
    """A doubly linked list of commits."""

    head_commit: Optional[Commit] = None
    tail_commit: Optional[Commit] = None
