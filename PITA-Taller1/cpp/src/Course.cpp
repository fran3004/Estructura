// Initial implementation of the Course class.
// TODO: define the course behavior as system logic is added.

#include "Course.h"

Course::Course()
    : course_id(0), name(""), program_id(0), credits(0), curriculum_semester(0), assigned_professor_id(0), max_capacity(0), active(false), enrollment_list() {}

Course::Course(int course_id, const std::string& name, int program_id, int credits, int curriculum_semester, int assigned_professor_id, int max_capacity, bool active, const LinkedList<int>& enrollment_list)
    : course_id(course_id), name(name), program_id(program_id), credits(credits), curriculum_semester(curriculum_semester), assigned_professor_id(assigned_professor_id), max_capacity(max_capacity), active(active), enrollment_list(enrollment_list) {}
