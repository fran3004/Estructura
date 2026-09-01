"""Course model.

Represents a university course and stores its associated enrollments.
"""

from .linked_list import LinkedList


class Course:
    """Entity that represents an academic course."""

    def __init__(
        self,
        course_id=0,
        name="",
        program_id=0,
        credits=0,
        curriculum_semester=0,
        assigned_professor_id=0,
        max_capacity=0,
        active=False,
        enrollment_list=None,
    ):
        self.course_id = course_id
        self.name = name
        self.program_id = program_id
        self.credits = credits
        self.curriculum_semester = curriculum_semester
        self.assigned_professor_id = assigned_professor_id
        self.max_capacity = max_capacity
        self.active = active
        self.enrollment_list = enrollment_list if enrollment_list is not None else LinkedList()
