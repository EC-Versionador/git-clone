"""Test suite for parser.py module."""

import unittest
from src.parser.data_structure_to_file import data_structure_to_string
from src.parser.files_to_data_structure import string_to_data_structure
from src.data_structures.commit import push_file_to_commit
from src.data_structures.repository import push_commit_to_repository

from src.classes.data_structures import Repository, Commit, File


class ParserTests(unittest.TestCase):
    """Test suite for parser.py module."""

    def test_data_structure_to_string(self):
        """Test data_structure_to_string function."""

        test_repository = Repository()
        test_commit1 = Commit(id_=1, message="test1")
        push_file_to_commit(test_commit1, File(path="test1.txt", start=1, end=1))
        push_file_to_commit(test_commit1, File(path="test2.txt", start=2, end=2))
        push_commit_to_repository(test_repository, test_commit1)
        test_commit_2 = Commit(id_=2, message="test2")
        push_file_to_commit(test_commit_2, File(path="test3.txt", start=3, end=3))
        push_file_to_commit(test_commit_2, File(path="test4.txt", start=4, end=4))
        push_commit_to_repository(test_repository, test_commit_2)

        expected = """id:1
message:test1
path:test1.txt
start:1
end:1
path:test2.txt
start:2
end:2
id:2
message:test2
path:test3.txt
start:3
end:3
path:test4.txt
start:4
end:4
"""
        self.assertEqual(data_structure_to_string(test_repository), expected)

        print("test_data_structure_to_string passed!")

    def test_string_to_data_structure(self):
        """Test string_to_data_structure function."""

        test = """id:1
message:test1
path:test1.txt
start:1
end:1
path:test2.txt
start:2
end:2
id:2
message:test2
path:test3.txt
start:3
end:3
path:test4.txt
start:4
end:4
"""

        repository = string_to_data_structure(test)
        res = data_structure_to_string(repository)
        self.assertEqual(res, test)

        print("test_string_to_data_structure passed!")
