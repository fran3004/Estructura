// Declaration of the Program class.
// Represents an academic program and stores its associated courses and students.

#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "LinkedList.h"

class Program {
public:
    Program();
    Program(int program_id,
            const std::string& name,
            int faculty_id,
            const std::string& program_director,
            const std::string& level,
            const std::string& modality,
            bool active,
            const LinkedList<int>& course_list,
            const LinkedList<int>& student_list);

private:
    int program_id;
    std::string name;
    int faculty_id;
    std::string program_director;
    std::string level;
    std::string modality;
    bool active;
    LinkedList<int> course_list;
    LinkedList<int> student_list;
};

#endif // PROGRAM_H
