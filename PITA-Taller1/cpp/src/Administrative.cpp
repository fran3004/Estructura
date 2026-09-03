// Initial implementation of the Administrative class.
// TODO: define the administrative staff behavior as system logic is added.

#include "Administrative.h"

Administrative::Administrative()
    : administrative_id(0), full_name(""), document_type(""), identity_document(""), email(""), phone(""), position(""), category(""), employment_type(""), base_salary(0.0), health_discount(0.0), pension_discount(0.0), severance_provision(0.0), holiday_bonus(0.0), vacation_provision(0.0), net_salary(0.0), active(false) {}

Administrative::Administrative(int administrative_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& email, const std::string& phone, const std::string& position, const std::string& category, const std::string& employment_type, double base_salary, double health_discount, double pension_discount, double severance_provision, double holiday_bonus, double vacation_provision, double net_salary, bool active)
    : administrative_id(administrative_id), full_name(full_name), document_type(document_type), identity_document(identity_document), email(email), phone(phone), position(position), category(category), employment_type(employment_type), base_salary(base_salary), health_discount(health_discount), pension_discount(pension_discount), severance_provision(severance_provision), holiday_bonus(holiday_bonus), vacation_provision(vacation_provision), net_salary(net_salary), active(active) {}

int Administrative::get_administrative_id() const { return administrative_id; }
std::string Administrative::get_full_name() const { return full_name; }
void Administrative::set_full_name(const std::string& value) { full_name = value; }
std::string Administrative::get_document_type() const { return document_type; }
std::string Administrative::get_identity_document() const { return identity_document; }
std::string Administrative::get_email() const { return email; }
std::string Administrative::get_phone() const { return phone; }
std::string Administrative::get_position() const { return position; }
std::string Administrative::get_category() const { return category; }
std::string Administrative::get_employment_type() const { return employment_type; }
double Administrative::get_base_salary() const { return base_salary; }
double Administrative::get_net_salary() const { return net_salary; }
bool Administrative::is_active() const { return active; }
void Administrative::set_active(bool value) { active = value; }
