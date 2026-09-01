// Declaration of the Student class.
// Represents a university student and their academic enrollments.

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "LinkedList.h"

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
               const LinkedList<int>& enrollment_list);

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
    LinkedList<int> enrollment_list;
};

#endif // STUDENT_H
