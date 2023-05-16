"""Run all tests."""

from src.tests.test_commit import CommitTests
from src.tests.test_repository import RepositoryTests
from src.tests.test_validation import ValidationTests


if __name__ == "__main__":
    validation_test_suite = ValidationTests()
    validation_test_suite.test_validate_arguments()
    commit_test_suite = CommitTests()
    commit_test_suite.test_push_file_to_commit()
    commit_test_suite.test_file_in_commit()
    repository_test_suite = RepositoryTests()
    repository_test_suite.test_push_commit_to_repository()
    print("All tests passed!")
