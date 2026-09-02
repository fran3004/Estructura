// Initial implementation of the Program class.
// TODO: define program behavior as system logic is added.

#include "Program.h"

Program::Program()
    : program_id(0),
      name(""),
      faculty_id(0),
      program_director(""),
      level(""),
      modality(""),
      active(false),
      course_list(),
      student_list() {}

Program::Program(int program_id,
                   const std::string& name,
                   int faculty_id,
                   const std::string& program_director,
                   const std::string& level,
                   const std::string& modality,
                   bool active,
                   const LinkedList<int>& course_list,
                   const LinkedList<int>& student_list)
    : program_id(program_id),
      name(name),
      faculty_id(faculty_id),
      program_director(program_director),
      level(level),
      modality(modality),
      active(active),
      course_list(course_list),
      student_list(student_list) {}

int Program::get_program_id() const { return program_id; }
std::string Program::get_name() const { return name; }
void Program::set_name(const std::string& value) { name = value; }
int Program::get_faculty_id() const { return faculty_id; }
void Program::set_faculty_id(int value) { faculty_id = value; }
std::string Program::get_program_director() const { return program_director; }
void Program::set_program_director(const std::string& value) { program_director = value; }
std::string Program::get_level() const { return level; }
void Program::set_level(const std::string& value) { level = value; }
std::string Program::get_modality() const { return modality; }
void Program::set_modality(const std::string& value) { modality = value; }
bool Program::is_active() const { return active; }
void Program::set_active(bool value) { active = value; }
LinkedList<int>& Program::get_course_list() { return course_list; }
const LinkedList<int>& Program::get_course_list() const { return course_list; }
LinkedList<int>& Program::get_student_list() { return student_list; }
const LinkedList<int>& Program::get_student_list() const { return student_list; }
