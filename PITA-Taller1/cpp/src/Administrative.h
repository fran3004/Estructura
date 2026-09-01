// Declaration of the Administrative class.
// Represents a university administrative worker.

#ifndef ADMINISTRATIVE_H
#define ADMINISTRATIVE_H

#include <string>

class Administrative {
public:
    Administrative();
    Administrative(int administrative_id,
                   const std::string& full_name,
                   const std::string& document_type,
                   const std::string& identity_document,
                   const std::string& email,
                   const std::string& phone,
                   const std::string& position,
                   const std::string& category,
                   const std::string& employment_type,
                   double base_salary,
                   double health_discount,
                   double pension_discount,
                   double severance_provision,
                   double holiday_bonus,
                   double vacation_provision,
                   double net_salary,
                   bool active);

private:
    int administrative_id;
    std::string full_name;
    std::string document_type;
    std::string identity_document;
    std::string email;
    std::string phone;
    std::string position;
    std::string category;
    std::string employment_type;
    double base_salary;
    double health_discount;
    double pension_discount;
    double severance_provision;
    double holiday_bonus;
    double vacation_provision;
    double net_salary;
    bool active;
};

#endif // ADMINISTRATIVE_H
