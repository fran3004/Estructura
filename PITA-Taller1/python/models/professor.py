"""Professor model.

Represents the academic staff and associated salary variables.
"""


class Professor:
    """Entity that represents a university professor."""

    def __init__(
        self,
        professor_id=0,
        full_name="",
        document_type="",
        document_number="",
        email="",
        phone="",
        faculty_id=0,
        employment_type="",
        category_rank="",
        academic_title="",
        years_of_qualified_experience=0,
        dedication="",
        lecture_hours=0,
        managerial_role="",
        category_score=0.0,
        title_score=0.0,
        experience_score=0.0,
        productivity_score=0.0,
        academic_management_score=0.0,
        total_points=0.0,
        point_value=0.0,
        base_monthly_salary=0.0,
        health_discount=0.0,
        pension_discount=0.0,
        severance_provision=0.0,
        bonus_provision=0.0,
        vacation_provision=0.0,
        net_salary=0.0,
        active=False,
    ):
        self.professor_id = professor_id
        self.full_name = full_name
        self.document_type = document_type
        self.document_number = document_number
        self.email = email
        self.phone = phone
        self.faculty_id = faculty_id
        self.employment_type = employment_type
        self.category_rank = category_rank
        self.academic_title = academic_title
        self.years_of_qualified_experience = years_of_qualified_experience
        self.dedication = dedication
        self.lecture_hours = lecture_hours
        self.managerial_role = managerial_role
        self.category_score = category_score
        self.title_score = title_score
        self.experience_score = experience_score
        self.productivity_score = productivity_score
        self.academic_management_score = academic_management_score
        self.total_points = total_points
        self.point_value = point_value
        self.base_monthly_salary = base_monthly_salary
        self.health_discount = health_discount
        self.pension_discount = pension_discount
        self.severance_provision = severance_provision
        self.bonus_provision = bonus_provision
        self.vacation_provision = vacation_provision
        self.net_salary = net_salary
        self.active = active
