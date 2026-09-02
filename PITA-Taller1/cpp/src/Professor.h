// Declaration of the Professor class.
// Represents academic staff according to the university academic statute.

#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>

class Professor {
public:
    Professor();
    Professor(int professor_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& email, const std::string& phone, int faculty_id, const std::string& employment_type, const std::string& category_rank, const std::string& academic_title, int years_of_qualified_experience, const std::string& dedication, int lecture_hours, const std::string& managerial_role, double category_score, double title_score, double experience_score, double productivity_score, double academic_management_score, double total_points, double point_value, double base_monthly_salary, double health_discount, double pension_discount, double severance_provision, double bonus_provision, double vacation_provision, double net_salary, bool active);

    int get_professor_id() const;
    std::string get_full_name() const;
    void set_full_name(const std::string& value);
    int get_faculty_id() const;
    void set_faculty_id(int value);
    std::string get_document_type() const;
    std::string get_identity_document() const;
    std::string get_email() const;
    std::string get_phone() const;
    std::string get_employment_type() const;
    void set_employment_type(const std::string& value);
    std::string get_category_rank() const;
    std::string get_academic_title() const;
    int get_years_of_qualified_experience() const;
    std::string get_dedication() const;
    int get_lecture_hours() const;
    std::string get_managerial_role() const;
    double get_base_monthly_salary() const;
    double get_net_salary() const;
    bool is_active() const;
    void set_active(bool value);

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
