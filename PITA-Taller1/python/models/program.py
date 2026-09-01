"""Program model.

Represents an academic program and stores the related courses and students.
"""

from .linked_list import LinkedList


class Program:
    """Entity that represents an academic program."""

    def __init__(
        self,
        program_id=0,
        name="",
        faculty_id=0,
        program_director="",
        level="",
        modality="",
        active=False,
        course_list=None,
        student_list=None,
    ):
        self.program_id = program_id
        self.name = name
        self.faculty_id = faculty_id
        self.program_director = program_director
        self.level = level
        self.modality = modality
        self.active = active
        self.course_list = course_list if course_list is not None else LinkedList()
        self.student_list = student_list if student_list is not None else LinkedList()
