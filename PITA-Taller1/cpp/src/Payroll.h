// Declaration of the Payroll class.
// This module calculates payroll without duplicating employee data.

#ifndef PAYROLL_H
#define PAYROLL_H

#include <string>

class Professor;
class Administrative;

class Payroll {
public:
    Payroll();
    explicit Payroll(const std::string& description);

    std::string get_description() const;
    void set_description(const std::string& value);

    double calculate_professor_salary(const Professor& professor) const;
    double calculate_administrative_salary(const Administrative& administrative) const;

private:
    std::string description;
};

#endif // PAYROLL_H
