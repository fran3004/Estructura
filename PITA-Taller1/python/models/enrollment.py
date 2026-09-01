"""Enrollment model.

Represents a student's enrollment in a course during an academic period.
It contains no business logic or calculations and only stores basic information.
"""


class Enrollment:
    """Entity that records a student's enrollment in a course."""

    def __init__(
        self,
        enrollment_id=0,
        student_id=0,
        course_id=0,
        academic_period="",
        final_grade=0.0,
        status="",
        enrollment_date="",
    ):
        self.enrollment_id = enrollment_id
        self.student_id = student_id
        self.course_id = course_id
        self.academic_period = academic_period
        self.final_grade = final_grade
        self.status = status
        self.enrollment_date = enrollment_date
