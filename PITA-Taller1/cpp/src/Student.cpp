// Initial implementation of the Student class.
// TODO: define the student behavior as system logic is added.

#include "Student.h"

Student::Student()
    : student_id(0), full_name(""), document_type(""), identity_document(""), birth_date(""), email(""), phone(""), program_id(0), current_semester(0), status(""), cumulative_average(0.0), active(false), enrollment_list() {}

Student::Student(int student_id, const std::string& full_name, const std::string& document_type, const std::string& identity_document, const std::string& birth_date, const std::string& email, const std::string& phone, int program_id, int current_semester, const std::string& status, double cumulative_average, bool active, const LinkedList<Enrollment*>& enrollment_list)
    : student_id(student_id), full_name(full_name), document_type(document_type), identity_document(identity_document), birth_date(birth_date), email(email), phone(phone), program_id(program_id), current_semester(current_semester), status(status), cumulative_average(cumulative_average), active(active), enrollment_list(enrollment_list) {}

int Student::get_student_id() const { return student_id; }
std::string Student::get_full_name() const { return full_name; }
void Student::set_full_name(const std::string& value) { full_name = value; }
int Student::get_program_id() const { return program_id; }
void Student::set_program_id(int value) { program_id = value; }
std::string Student::get_status() const { return status; }
void Student::set_status(const std::string& value) { status = value; }
double Student::get_cumulative_average() const { return cumulative_average; }
void Student::set_cumulative_average(double value) { cumulative_average = value; }
bool Student::is_active() const { return active; }
void Student::set_active(bool value) { active = value; }
LinkedList<Enrollment*>& Student::get_enrollment_list() { return enrollment_list; }
const LinkedList<Enrollment*>& Student::get_enrollment_list() const { return enrollment_list; }
