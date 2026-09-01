// Declaration of the Payroll class.
// This module calculates payroll without duplicating employee data.

#ifndef PAYROLL_H
#define PAYROLL_H

#include <string>

class Payroll {
public:
    Payroll();
    explicit Payroll(const std::string& description);

private:
    std::string description;
};

#endif // PAYROLL_H
