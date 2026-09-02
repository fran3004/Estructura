// Declaration of the Course class.
// Represents an academic course and its associated enrollments.

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "LinkedList.h"

class Course {
public:
    Course();
    Course(int course_id,
            const std::string& name,
            int program_id,
            int credits,
            int curriculum_semester,
            int assigned_professor_id,
            int max_capacity,
            bool active,
            const LinkedList<int>& enrollment_list);

    int get_course_id() const;
    std::string get_name() const;
    void set_name(const std::string& value);
    int get_program_id() const;
    void set_program_id(int value);
    int get_credits() const;
    void set_credits(int value);
    int get_curriculum_semester() const;
    void set_curriculum_semester(int value);
    int get_assigned_professor_id() const;
    void set_assigned_professor_id(int value);
    int get_max_capacity() const;
    void set_max_capacity(int value);
    bool is_active() const;
    void set_active(bool value);
    LinkedList<int>& get_enrollment_list();
    const LinkedList<int>& get_enrollment_list() const;

private:
    int course_id;
    std::string name;
    int program_id;
    int credits;
    int curriculum_semester;
    int assigned_professor_id;
    int max_capacity;
    bool active;
    LinkedList<int> enrollment_list;
};

#endif // COURSE_H
