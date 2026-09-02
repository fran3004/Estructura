// Declaration of the Student class.
// Represents a university student and their academic enrollments.

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "LinkedList.h"
#include "Enrollment.h"

class Student {
public:
    Student();
    Student(int student_id,
               const std::string& full_name,
               const std::string& document_type,
               const std::string& identity_document,
               const std::string& birth_date,
               const std::string& email,
               const std::string& phone,
               int program_id,
               int current_semester,
               const std::string& status,
               double cumulative_average,
               bool active,
               const LinkedList<Enrollment*>& enrollment_list);

    int get_student_id() const;
    std::string get_full_name() const;
    void set_full_name(const std::string& value);
    int get_program_id() const;
    void set_program_id(int value);
    std::string get_status() const;
    void set_status(const std::string& value);
    double get_cumulative_average() const;
    void set_cumulative_average(double value);
    bool is_active() const;
    void set_active(bool value);
    LinkedList<Enrollment*>& get_enrollment_list();
    const LinkedList<Enrollment*>& get_enrollment_list() const;

private:
    int student_id;
    std::string full_name;
    std::string document_type;
    std::string identity_document;
    std::string birth_date;
    std::string email;
    std::string phone;
    int program_id;
    int current_semester;
    std::string status;
    double cumulative_average;
    bool active;
    LinkedList<Enrollment*> enrollment_list;
};

#endif // STUDENT_H
