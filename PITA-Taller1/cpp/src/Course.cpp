// Initial implementation of the Course class.
// TODO: define the course behavior as system logic is added.

#include "Course.h"

Course::Course()
    : course_id(0), name(""), program_id(0), credits(0), curriculum_semester(0), assigned_professor_id(0), max_capacity(0), active(false), enrollment_list() {}

Course::Course(int course_id, const std::string& name, int program_id, int credits, int curriculum_semester, int assigned_professor_id, int max_capacity, bool active, const LinkedList<int>& enrollment_list)
    : course_id(course_id), name(name), program_id(program_id), credits(credits), curriculum_semester(curriculum_semester), assigned_professor_id(assigned_professor_id), max_capacity(max_capacity), active(active), enrollment_list(enrollment_list) {}

int Course::get_course_id() const { return course_id; }
std::string Course::get_name() const { return name; }
void Course::set_name(const std::string& value) { name = value; }
int Course::get_program_id() const { return program_id; }
void Course::set_program_id(int value) { program_id = value; }
int Course::get_credits() const { return credits; }
void Course::set_credits(int value) { credits = value; }
int Course::get_curriculum_semester() const { return curriculum_semester; }
void Course::set_curriculum_semester(int value) { curriculum_semester = value; }
int Course::get_assigned_professor_id() const { return assigned_professor_id; }
void Course::set_assigned_professor_id(int value) { assigned_professor_id = value; }
int Course::get_max_capacity() const { return max_capacity; }
void Course::set_max_capacity(int value) { max_capacity = value; }
bool Course::is_active() const { return active; }
void Course::set_active(bool value) { active = value; }
LinkedList<int>& Course::get_enrollment_list() { return enrollment_list; }
const LinkedList<int>& Course::get_enrollment_list() const { return enrollment_list; }
