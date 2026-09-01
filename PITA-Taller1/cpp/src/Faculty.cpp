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
                   const LinkedList<int>& program_list)
    : faculty_id(faculty_id),
      name(name),
      dean(dean),
      creation_date(creation_date),
      active(active),
      program_list(program_list) {}
