"""Faculty model.

Represents a university faculty and stores the related academic programs.
"""

from .linked_list import LinkedList


class Faculty:
    """Entity that represents a university faculty."""

    def __init__(
        self,
        faculty_id=0,
        name="",
        dean="",
        creation_date="",
        active=False,
        program_list=None,
    ):
        self.faculty_id = faculty_id
        self.name = name
        self.dean = dean
        self.creation_date = creation_date
        self.active = active
        self.program_list = program_list if program_list is not None else LinkedList()
