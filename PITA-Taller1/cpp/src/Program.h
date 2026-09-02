// Declaration of the Program class.
// Represents an academic program and stores its associated courses and students.

#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "LinkedList.h"

class Program {
public:
    Program();
    Program(int program_id,
            const std::string& name,
            int faculty_id,
            const std::string& program_director,
            const std::string& level,
            const std::string& modality,
            bool active,
            const LinkedList<int>& course_list,
            const LinkedList<int>& student_list);

    int get_program_id() const;
    std::string get_name() const;
    void set_name(const std::string& value);
    int get_faculty_id() const;
    void set_faculty_id(int value);
    std::string get_program_director() const;
    void set_program_director(const std::string& value);
    std::string get_level() const;
    void set_level(const std::string& value);
    std::string get_modality() const;
    void set_modality(const std::string& value);
    bool is_active() const;
    void set_active(bool value);
    LinkedList<int>& get_course_list();
    const LinkedList<int>& get_course_list() const;
    LinkedList<int>& get_student_list();
    const LinkedList<int>& get_student_list() const;

private:
    int program_id;
    std::string name;
    int faculty_id;
    std::string program_director;
    std::string level;
    std::string modality;
    bool active;
    LinkedList<int> course_list;
    LinkedList<int> student_list;
};

#endif // PROGRAM_H
