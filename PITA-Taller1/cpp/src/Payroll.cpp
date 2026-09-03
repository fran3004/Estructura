// Implementation of payroll calculations for professors and administrative staff.

#include "Payroll.h"

#include "Administrative.h"
#include "Professor.h"

Payroll::Payroll() : description("") {}

Payroll::Payroll(const std::string& description) : description(description) {}

std::string Payroll::get_description() const { return description; }

void Payroll::set_description(const std::string& value) { description = value; }

double Payroll::calculate_professor_salary(const Professor& professor) const {
    const double base_salary = professor.get_base_monthly_salary();
    const double health_discount = base_salary * 0.09;
    const double pension_discount = base_salary * 0.12;
    const double severance = base_salary * 0.08;
    const double bonus = base_salary * 0.15;
    const double vacation = base_salary * 0.05;
    const double net_salary = base_salary - health_discount - pension_discount + severance + bonus + vacation;
    return net_salary;
}

double Payroll::calculate_administrative_salary(const Administrative& administrative) const {
    const double base_salary = administrative.get_base_salary();
    const double health_discount = base_salary * 0.08;
    const double pension_discount = base_salary * 0.10;
    const double severance = base_salary * 0.07;
    const double holiday_bonus = base_salary * 0.10;
    const double vacation = base_salary * 0.04;
    const double net_salary = base_salary - health_discount - pension_discount + severance + holiday_bonus + vacation;
    return net_salary;
}
