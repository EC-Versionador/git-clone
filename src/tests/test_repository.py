"""Test repository.py module."""

import unittest
from src.data_structures.repository import push_commit_to_repository
from src.classes.data_structures import Repository, Commit


class RepositoryTests(unittest.TestCase):
    """Test suite for repository.py module."""
    
    def test_push_commit_to_repository(self):
        """test push_commit_to_repository function."""

        repository = Repository()
        commit1 = Commit(message="message1")
        commit2 = Commit(message="message2")
        push_commit_to_repository(repository, commit1)
        push_commit_to_repository(repository, commit2)

        self.assertEqual(repository.head_commit, commit2)
        self.assertEqual(repository.tail_commit, commit1)
        self.assertIsNone(commit1.next_)
        self.assertEqual(commit1.prev_, commit2)
        self.assertEqual(commit2.next_, commit1)
        self.assertIsNone(commit2.prev_)
        
        print("test_push_commit_to_repository passed!")