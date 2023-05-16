"""Test all validations."""

import unittest
from src.classes.validation_exceptions import InvalidCommandException
from src.validations.command_validation import validate_arguments


class ValidationTests(unittest.TestCase):
    """Test suite for validations folder."""
    
    def test_validate_arguments(self):
        """Test validate_arguments function."""
        
        validate_arguments(["init"])
        validate_arguments(["add", "file.txt"])
        validate_arguments(["commit", "-m", "message"])
        validate_arguments(["commit", "--message", "message"])
        validate_arguments(["log"])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments([])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments(["init", "file.txt"])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments(["add"])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments(["commit", "-m"])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments(["log", "file.txt"])
        
        with self.assertRaises(InvalidCommandException):
            validate_arguments(["invalid"])
        
        print("test_validate_arguments passed!")