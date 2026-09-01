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
          int creditos,
            int curriculum_semester,
            int assigned_professor_id,
            int max_capacity,
            bool active,
            const LinkedList<int>& enrollment_list);

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
