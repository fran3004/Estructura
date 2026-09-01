// Declaration of the Professor class.
// Represents academic staff according to the university academic statute.

#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>

class Professor {
public:
    Professor();
    Professor(int professor_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& email, const std::string& phone, int faculty_id, const std::string& employment_type, const std::string& category_rank, const std::string& academic_title, int years_of_qualified_experience, const std::string& dedication, int lecture_hours, const std::string& managerial_role, double category_score, double title_score, double experience_score, double productivity_score, double academic_management_score, double total_points, double point_value, double base_monthly_salary, double health_discount, double pension_discount, double severance_provision, double bonus_provision, double vacation_provision, double net_salary, bool active);

private:
    int professor_id;
    std::string full_name;
    std::string document_type;
    std::string identity_document;
    std::string email;
    std::string phone;
    int faculty_id;
    std::string employment_type;
    std::string category_rank;
    std::string academic_title;
    int years_of_qualified_experience;
    std::string dedication;
    int lecture_hours;
    std::string managerial_role;
    double category_score;
    double title_score;
    double experience_score;
    double productivity_score;
    double academic_management_score;
    double total_points;
    double point_value;
    double base_monthly_salary;
    double health_discount;
    double pension_discount;
    double severance_provision;
    double bonus_provision;
    double vacation_provision;
    double net_salary;
    bool active;
};

#endif // PROFESSOR_H
