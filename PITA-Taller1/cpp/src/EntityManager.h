#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <string>
#include "Faculty.h"
#include "Program.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Administrative.h"
#include "Enrollment.h"

class EntityManager {
public:
    EntityManager();

    bool create_faculty(Faculty faculty);
    Faculty* get_faculty(int faculty_id);
    const Faculty* get_faculty(int faculty_id) const;
    LinkedList<Faculty>& list_faculties();
    const LinkedList<Faculty>& list_faculties() const;
    bool delete_faculty(int faculty_id);
    bool deactivate_faculty(int faculty_id);
    bool reactivate_faculty(int faculty_id);

    bool create_program(Program program);
    Program* get_program(int program_id);
    const Program* get_program(int program_id) const;
    LinkedList<Program>& list_programs();
    const LinkedList<Program>& list_programs() const;
    bool delete_program(int program_id);
    bool deactivate_program(int program_id);
    bool reactivate_program(int program_id);

    bool create_course(Course course);
    Course* get_course(int course_id);
    const Course* get_course(int course_id) const;
    LinkedList<Course>& list_courses();
    const LinkedList<Course>& list_courses() const;
    bool delete_course(int course_id);
    bool deactivate_course(int course_id);
    bool reactivate_course(int course_id);

    bool create_student(Student student);
    Student* get_student(int student_id);
    const Student* get_student(int student_id) const;
    LinkedList<Student>& list_students();
    const LinkedList<Student>& list_students() const;
    bool delete_student(int student_id);
    bool deactivate_student(int student_id);
    bool reactivate_student(int student_id);

    bool create_professor(Professor professor);
    Professor* get_professor(int professor_id);
    const Professor* get_professor(int professor_id) const;
    LinkedList<Professor>& list_professors();
    const LinkedList<Professor>& list_professors() const;
    bool delete_professor(int professor_id);
    bool deactivate_professor(int professor_id);
    bool reactivate_professor(int professor_id);

    bool create_administrative(Administrative administrative);
    Administrative* get_administrative(int administrative_id);
    const Administrative* get_administrative(int administrative_id) const;
    LinkedList<Administrative>& list_administrative_staff();
    const LinkedList<Administrative>& list_administrative_staff() const;
    bool delete_administrative(int administrative_id);
    bool deactivate_administrative(int administrative_id);
    bool reactivate_administrative(int administrative_id);

    bool create_enrollment(Enrollment enrollment);
    Enrollment* get_enrollment(int enrollment_id);
    const Enrollment* get_enrollment(int enrollment_id) const;
    LinkedList<Enrollment>& list_enrollments();
    const LinkedList<Enrollment>& list_enrollments() const;
    bool delete_enrollment(int enrollment_id);
    bool deactivate_enrollment(int enrollment_id);
    bool reactivate_enrollment(int enrollment_id);

private:
    LinkedList<Faculty> faculties;
    LinkedList<Program> programs;
    LinkedList<Course> courses;
    LinkedList<Student> students;
    LinkedList<Professor> professors;
    LinkedList<Administrative> administrative_staff;
    LinkedList<Enrollment> enrollments;

    static bool contains_by_id(const LinkedList<Faculty>& items, int id);
    static bool contains_by_id(const LinkedList<Program>& items, int id);
    static bool contains_by_id(const LinkedList<Course>& items, int id);
    static bool contains_by_id(const LinkedList<Student>& items, int id);
    static bool contains_by_id(const LinkedList<Professor>& items, int id);
    static bool contains_by_id(const LinkedList<Administrative>& items, int id);
    static bool contains_by_id(const LinkedList<Enrollment>& items, int id);
};

#endif
