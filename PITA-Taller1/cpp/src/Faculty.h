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

    int get_faculty_id() const;
    std::string get_name() const;
    void set_name(const std::string& value);
    std::string get_dean() const;
    void set_dean(const std::string& value);
    std::string get_creation_date() const;
    void set_creation_date(const std::string& value);
    bool is_active() const;
    void set_active(bool value);
    LinkedList<Program*>& get_program_list();
    const LinkedList<Program*>& get_program_list() const;

private:
    int faculty_id;
    std::string name;
    std::string dean;
    std::string creation_date;
    bool active;
    LinkedList<Program*> program_list;
};

#endif // FACULTY_H
