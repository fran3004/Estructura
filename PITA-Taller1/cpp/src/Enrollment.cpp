// Initial implementation of the Enrollment class.
// TODO: define additional construction and attribute initialization behavior.

#include "Enrollment.h"

Enrollment::Enrollment() : enrollment_id(0), student_id(0), course_id(0), academic_period(""), final_grade(0.0), status(""), enrollment_date("") {}

Enrollment::Enrollment(int enrollment_id, int student_id, int course_id, const std::string& academic_period, double final_grade, const std::string& status, const std::string& enrollment_date)
    : enrollment_id(enrollment_id), student_id(student_id), course_id(course_id), academic_period(academic_period), final_grade(final_grade), status(status), enrollment_date(enrollment_date) {}

int Enrollment::get_enrollment_id() const { return enrollment_id; }
int Enrollment::get_student_id() const { return student_id; }
void Enrollment::set_student_id(int value) { student_id = value; }
int Enrollment::get_course_id() const { return course_id; }
void Enrollment::set_course_id(int value) { course_id = value; }
std::string Enrollment::get_academic_period() const { return academic_period; }
void Enrollment::set_academic_period(const std::string& value) { academic_period = value; }
double Enrollment::get_final_grade() const { return final_grade; }
void Enrollment::set_final_grade(double value) { final_grade = value; }
std::string Enrollment::get_status() const { return status; }
void Enrollment::set_status(const std::string& value) { status = value; }
std::string Enrollment::get_enrollment_date() const { return enrollment_date; }
void Enrollment::set_enrollment_date(const std::string& value) { enrollment_date = value; }
