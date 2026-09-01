"""Administrative model.

Represents the university administrative staff.
"""


class Administrative:
    """Entity that represents an administrative worker."""

    def __init__(
        self,
        administrative_id=0,
        full_name="",
        document_type="",
        document_number="",
        email="",
        phone="",
        position="",
        category="",
        employment_type="",
        base_salary=0.0,
        health_discount=0.0,
        pension_discount=0.0,
        severance_provision=0.0,
        holiday_bonus=0.0,
        vacation_provision=0.0,
        net_salary=0.0,
        active=False,
    ):
        self.administrative_id = administrative_id
        self.full_name = full_name
        self.document_type = document_type
        self.document_number = document_number
        self.email = email
        self.phone = phone
        self.position = position
        self.category = category
        self.employment_type = employment_type
        self.base_salary = base_salary
        self.health_discount = health_discount
        self.pension_discount = pension_discount
        self.severance_provision = severance_provision
        self.holiday_bonus = holiday_bonus
        self.vacation_provision = vacation_provision
        self.net_salary = net_salary
        self.active = active
