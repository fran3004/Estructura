// Declaration of the Enrollment class.
// Represents a student's enrollment in a course during an academic period.
// This class stores basic data and the relationship without business logic.

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

class Enrollment {
public:
    Enrollment();
    Enrollment(int enrollment_id,
              int student_id,
              int course_id,
              const std::string& academic_period,
              double final_grade,
              const std::string& status,
              const std::string& enrollment_date);

private:
    int enrollment_id;
    int student_id;
    int course_id;
    std::string academic_period;
    double final_grade;
    std::string status;
    std::string enrollment_date;
};

#endif // ENROLLMENT_H
