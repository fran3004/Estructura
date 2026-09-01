// Initial implementation of the Professor class.
// TODO: define professor behavior as system logic is added.

#include "Professor.h"

Professor::Professor()
    : professor_id(0), full_name(""), document_type(""), identity_document(""), email(""), phone(""), faculty_id(0), employment_type(""), category_rank(""), academic_title(""), years_of_qualified_experience(0),
      dedication(""),
      lecture_hours(0), managerial_role(""), category_score(0.0), title_score(0.0), experience_score(0.0), productivity_score(0.0), academic_management_score(0.0), total_points(0.0), point_value(0.0), base_monthly_salary(0.0), health_discount(0.0), pension_discount(0.0), severance_provision(0.0), bonus_provision(0.0), vacation_provision(0.0), net_salary(0.0), active(false) {}

Professor::Professor(int professor_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& email, const std::string& phone, int faculty_id, const std::string& employment_type, const std::string& category_rank, const std::string& academic_title, int years_of_qualified_experience,
                   const std::string& dedication,
                   int lecture_hours, const std::string& managerial_role,
                   double category_score, double title_score, double experience_score, double productivity_score, double academic_management_score, double total_points, double point_value, double base_monthly_salary, double health_discount, double pension_discount, double severance_provision, double bonus_provision, double vacation_provision, double net_salary, bool active)
    : professor_id(professor_id), full_name(full_name), document_type(document_type), identity_document(identity_document), email(email), phone(phone), faculty_id(faculty_id), employment_type(employment_type), category_rank(category_rank), academic_title(academic_title), years_of_qualified_experience(years_of_qualified_experience),
      dedication(dedication),
      lecture_hours(lecture_hours), managerial_role(managerial_role), category_score(category_score), title_score(title_score), experience_score(experience_score), productivity_score(productivity_score), academic_management_score(academic_management_score), total_points(total_points), point_value(point_value), base_monthly_salary(base_monthly_salary), health_discount(health_discount), pension_discount(pension_discount), severance_provision(severance_provision), bonus_provision(bonus_provision), vacation_provision(vacation_provision), net_salary(net_salary), active(active) {}
