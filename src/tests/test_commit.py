"""Test commit.py module."""

import unittest
from src.data_structures.commit import push_file_to_commit, file_in_commit
from src.classes.data_structures import Commit, File


class CommitTests(unittest.TestCase):
    """Test suite for commit.py module."""

    def test_push_file_to_commit(self):
        """Test push_file_to_commit function."""

        commit = Commit(message="test")
        file1 = File(path="test.txt")
        file2 = File(path="test2.txt")
        push_file_to_commit(commit, file1)
        push_file_to_commit(commit, file2)

        self.assertEqual(commit.head_file, file2)
        self.assertEqual(commit.tail_file, file1)
        self.assertIsNone(file1.next_)
        self.assertEqual(file1.prev_, file2)
        self.assertEqual(file2.next_, file1)
        self.assertIsNone(file2.prev_)

        print("test_push_file_to_commit passed!")

    def test_file_in_commit(self):
        """Test file_in_commit function."""

        commit = Commit(message="test")
        file1 = File(path="test.txt")
        file2 = File(path="test2.txt")
        push_file_to_commit(commit, file1)
        push_file_to_commit(commit, file2)

        self.assertTrue(file_in_commit(commit, "test.txt"))
        self.assertTrue(file_in_commit(commit, "test2.txt"))
        self.assertFalse(file_in_commit(commit, "test3.txt"))

        print("test_file_in_commit passed!")
