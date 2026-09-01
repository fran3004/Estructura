// Initial implementation of the Student class.
// TODO: define the student behavior as system logic is added.

#include "Student.h"

Student::Student()
    : student_id(0), full_name(""), document_type(""), identity_document(""), birth_date(""), email(""), phone(""), program_id(0), current_semester(0), status(""), cumulative_average(0.0), active(false), enrollment_list() {}

Student::Student(int student_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& birth_date, const std::string& email, const std::string& phone, int program_id, int current_semester, const std::string& status, double cumulative_average, bool active, const LinkedList<int>& enrollment_list)
    : student_id(student_id), full_name(full_name), document_type(document_type), identity_document(identity_document), birth_date(birth_date), email(email), phone(phone), program_id(program_id), current_semester(current_semester), status(status), cumulative_average(cumulative_average), active(active), enrollment_list(enrollment_list) {}
