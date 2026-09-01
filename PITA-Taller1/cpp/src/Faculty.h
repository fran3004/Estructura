// Declaration of the Faculty class.
// Represents a university faculty and stores the associated academic programs.

#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include "LinkedList.h"
#include "Program.h"

class Faculty {
public:
    Faculty();
    Faculty(int faculty_id,
            const std::string& name,
            const std::string& dean,
            const std::string& creation_date,
            bool active,
            const LinkedList<Program*>& program_list);

private:
    int faculty_id;
    std::string name;
    std::string dean;
    std::string creation_date;
    bool active;
    LinkedList<Program*> program_list;
};

#endif // FACULTY_H
