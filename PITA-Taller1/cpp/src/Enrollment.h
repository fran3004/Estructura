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

    int get_enrollment_id() const;
    int get_student_id() const;
    void set_student_id(int value);
    int get_course_id() const;
    void set_course_id(int value);
    std::string get_academic_period() const;
    void set_academic_period(const std::string& value);
    double get_final_grade() const;
    void set_final_grade(double value);
    std::string get_status() const;
    void set_status(const std::string& value);
    std::string get_enrollment_date() const;
    void set_enrollment_date(const std::string& value);

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
