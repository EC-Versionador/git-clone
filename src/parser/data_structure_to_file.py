"""Convert repository data structure to string."""

from src.classes.data_structures import Repository


def data_structure_to_string(repository: Repository):
    """Converts repository data structure to string.

    Args:
        repository (Repository): repository data structure

    Returns:
        _type_: string representation of repository data structure
    """

    current = repository.head_commit
    text = ""
    while current is not None:
        text += f"id:{current.id_}\n"
        text += f"message:{current.message}\n"
        file_ = current.head_file
        while file_ is not None:
            text += f"path:{file_.path}\n"
            text += f"start:{file_.start}\n"
            text += f"end:{file_.end}\n"
            file_ = file_.next_
        current = current.next_

    return text
