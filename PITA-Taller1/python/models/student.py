"""Student model.

Represents a university student and stores their academic enrollments.
"""

from .linked_list import LinkedList


class Student:
    """Entity that represents a student."""

    def __init__(
        self,
        student_id=0,
        full_name="",
        document_type="",
        document_number="",
        birth_date="",
        email="",
        phone="",
        program_id=0,
        current_semester=0,
        status="",
        cumulative_average=0.0,
        active=False,
        enrollment_list=None,
    ):
        self.student_id = student_id
        self.full_name = full_name
        self.document_type = document_type
        self.document_number = document_number
        self.birth_date = birth_date
        self.email = email
        self.phone = phone
        self.program_id = program_id
        self.current_semester = current_semester
        self.status = status
        self.cumulative_average = cumulative_average
        self.active = active
        self.enrollment_list = enrollment_list if enrollment_list is not None else LinkedList()
