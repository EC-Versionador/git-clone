"""Run all tests."""

from src.tests.test_commit import CommitTests
from src.tests.test_repository import RepositoryTests
from src.tests.test_validation import ValidationTests
from src.tests.test_parser import ParserTests


if __name__ == "__main__":
    validation_test_suite = ValidationTests()
    validation_test_suite.test_validate_arguments()
    
    commit_test_suite = CommitTests()
    commit_test_suite.test_push_file_to_commit()
    commit_test_suite.test_file_in_commit()
    
    repository_test_suite = RepositoryTests()
    repository_test_suite.test_push_commit_to_repository()
    
    parser_tests = ParserTests()
    parser_tests.test_data_structure_to_string()
    parser_tests.test_string_to_data_structure()
    print("All tests passed!")
