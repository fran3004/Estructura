// Initial implementation of the Enrollment class.
// TODO: define additional construction and attribute initialization behavior.

#include "Enrollment.h"

Enrollment::Enrollment() : enrollment_id(0), student_id(0), course_id(0), academic_period(""), final_grade(0.0), status(""), enrollment_date("") {}

Enrollment::Enrollment(int enrollment_id, int student_id, int course_id, const std::string& academic_period, double final_grade, const std::string& status, const std::string& enrollment_date)
    : enrollment_id(enrollment_id), student_id(student_id), course_id(course_id), academic_period(academic_period), final_grade(final_grade), status(status), enrollment_date(enrollment_date) {}
