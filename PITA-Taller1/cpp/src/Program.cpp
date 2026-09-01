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
