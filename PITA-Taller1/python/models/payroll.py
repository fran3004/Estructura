"""Payroll model.

The payroll acts as a calculator that receives a Professor or an Administrative
and computes their salary without duplicating all of the same fields in both entities.
"""


class Payroll:
    """Base class for handling payroll calculations."""

    def __init__(self, description=""):
        self.description = description
