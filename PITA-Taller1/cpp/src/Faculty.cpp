// Initial implementation of the Faculty class.
// TODO: define faculty behavior as system logic is added.

#include "Faculty.h"

Faculty::Faculty()
    : faculty_id(0),
      name(""),
      dean(""),
      creation_date(""),
      active(false),
      program_list() {}

Faculty::Faculty(int faculty_id,
                   const std::string& name,
                   const std::string& dean,
                   const std::string& creation_date,
                   bool active,
                   const LinkedList<Program*>& program_list)
    : faculty_id(faculty_id),
      name(name),
      dean(dean),
      creation_date(creation_date),
      active(active),
      program_list(program_list) {}

int Faculty::get_faculty_id() const { return faculty_id; }
std::string Faculty::get_name() const { return name; }
void Faculty::set_name(const std::string& value) { name = value; }
std::string Faculty::get_dean() const { return dean; }
void Faculty::set_dean(const std::string& value) { dean = value; }
std::string Faculty::get_creation_date() const { return creation_date; }
void Faculty::set_creation_date(const std::string& value) { creation_date = value; }
bool Faculty::is_active() const { return active; }
void Faculty::set_active(bool value) { active = value; }
LinkedList<Program*>& Faculty::get_program_list() { return program_list; }
const LinkedList<Program*>& Faculty::get_program_list() const { return program_list; }
