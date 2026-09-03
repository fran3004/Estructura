#include "EntityManager.h"

#include <stdexcept>

EntityManager::EntityManager() = default;

bool EntityManager::contains_by_id(const LinkedList<Faculty>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_faculty_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Program>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_program_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Course>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_course_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Student>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_student_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Professor>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_professor_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Administrative>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_administrative_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::contains_by_id(const LinkedList<Enrollment>& items, int id) {
    for (const auto& item : items.to_vector()) {
        if (item.get_enrollment_id() == id) {
            return true;
        }
    }
    return false;
}

bool EntityManager::create_faculty(Faculty faculty) {
    if (contains_by_id(faculties, faculty.get_faculty_id())) {
        return false;
    }
    faculties.insert(faculty, faculties.count_elements());
    return true;
}

Faculty* EntityManager::get_faculty(int faculty_id) {
    for (std::size_t i = 0; i < faculties.count_elements(); ++i) {
        Faculty* item = faculties.get(i);
        if (item != nullptr && item->get_faculty_id() == faculty_id) {
            return item;
        }
    }
    return nullptr;
}

const Faculty* EntityManager::get_faculty(int faculty_id) const {
    for (std::size_t i = 0; i < faculties.count_elements(); ++i) {
        const Faculty* item = faculties.get(i);
        if (item != nullptr && item->get_faculty_id() == faculty_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Faculty>& EntityManager::list_faculties() {
    return faculties;
}

const LinkedList<Faculty>& EntityManager::list_faculties() const {
    return faculties;
}

bool EntityManager::delete_faculty(int faculty_id) {
    Faculty* faculty = get_faculty(faculty_id);
    if (faculty == nullptr) {
        return false;
    }
    if (!faculty->get_program_list().is_empty()) {
        return false;
    }
    for (std::size_t i = 0; i < faculties.count_elements(); ++i) {
        if (faculties.get(i) != nullptr && faculties.get(i)->get_faculty_id() == faculty_id) {
            faculties.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_faculty(int faculty_id) {
    Faculty* faculty = get_faculty(faculty_id);
    if (faculty == nullptr) {
        return false;
    }
    faculty->set_active(false);
    return true;
}

bool EntityManager::reactivate_faculty(int faculty_id) {
    Faculty* faculty = get_faculty(faculty_id);
    if (faculty == nullptr) {
        return false;
    }
    faculty->set_active(true);
    return true;
}

bool EntityManager::create_program(Program program) {
    if (contains_by_id(programs, program.get_program_id())) {
        return false;
    }
    if (!contains_by_id(faculties, program.get_faculty_id())) {
        return false;
    }
    Faculty* faculty = get_faculty(program.get_faculty_id());
    if (faculty == nullptr || !faculty->is_active()) {
        return false;
    }
    programs.insert(program, programs.count_elements());
    programs.insert(program, programs.count_elements());
    faculty->get_program_list().insert(get_program(program.get_program_id()), faculty->get_program_list().count_elements());
    return true;
}

Program* EntityManager::get_program(int program_id) {
    for (std::size_t i = 0; i < programs.count_elements(); ++i) {
        Program* item = programs.get(i);
        if (item != nullptr && item->get_program_id() == program_id) {
            return item;
        }
    }
    return nullptr;
}

const Program* EntityManager::get_program(int program_id) const {
    for (std::size_t i = 0; i < programs.count_elements(); ++i) {
        const Program* item = programs.get(i);
        if (item != nullptr && item->get_program_id() == program_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Program>& EntityManager::list_programs() {
    return programs;
}

const LinkedList<Program>& EntityManager::list_programs() const {
    return programs;
}

bool EntityManager::delete_program(int program_id) {
    Program* program = get_program(program_id);
    if (program == nullptr) {
        return false;
    }
    if (!program->get_course_list().is_empty() || !program->get_student_list().is_empty()) {
        return false;
    }
    for (std::size_t i = 0; i < programs.count_elements(); ++i) {
        if (programs.get(i) != nullptr && programs.get(i)->get_program_id() == program_id) {
            programs.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_program(int program_id) {
    Program* program = get_program(program_id);
    if (program == nullptr) {
        return false;
    }
    program->set_active(false);
    return true;
}

bool EntityManager::reactivate_program(int program_id) {
    Program* program = get_program(program_id);
    if (program == nullptr) {
        return false;
    }
    if (!contains_by_id(faculties, program->get_faculty_id())) {
        return false;
    }
    Program* current = get_program(program_id);
    if (current == nullptr) {
        return false;
    }
    current->set_active(true);
    return true;
}

bool EntityManager::create_course(Course course) {
    if (contains_by_id(courses, course.get_course_id())) {
        return false;
    }
    if (!contains_by_id(programs, course.get_program_id())) {
        return false;
    }
    Program* program = get_program(course.get_program_id());
    if (program == nullptr || !program->is_active()) {
        return false;
    }
    courses.insert(course, courses.count_elements());
    program->get_course_list().insert(course.get_course_id(), program->get_course_list().count_elements());
    return true;
}

Course* EntityManager::get_course(int course_id) {
    for (std::size_t i = 0; i < courses.count_elements(); ++i) {
        Course* item = courses.get(i);
        if (item != nullptr && item->get_course_id() == course_id) {
            return item;
        }
    }
    return nullptr;
}

const Course* EntityManager::get_course(int course_id) const {
    for (std::size_t i = 0; i < courses.count_elements(); ++i) {
        const Course* item = courses.get(i);
        if (item != nullptr && item->get_course_id() == course_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Course>& EntityManager::list_courses() {
    return courses;
}

const LinkedList<Course>& EntityManager::list_courses() const {
    return courses;
}

bool EntityManager::delete_course(int course_id) {
    Course* course = get_course(course_id);
    if (course == nullptr) {
        return false;
    }
    if (!course->get_enrollment_list().is_empty()) {
        return false;
    }
    for (std::size_t i = 0; i < courses.count_elements(); ++i) {
        if (courses.get(i) != nullptr && courses.get(i)->get_course_id() == course_id) {
            courses.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_course(int course_id) {
    Course* course = get_course(course_id);
    if (course == nullptr) {
        return false;
    }
    course->set_active(false);
    return true;
}

bool EntityManager::reactivate_course(int course_id) {
    Course* course = get_course(course_id);
    if (course == nullptr) {
        return false;
    }
    if (!contains_by_id(programs, course->get_program_id())) {
        return false;
    }
    Program* program = get_program(course->get_program_id());
    if (program == nullptr || !program->is_active()) {
        return false;
    }
    course->set_active(true);
    return true;
}

bool EntityManager::create_student(Student student) {
    if (contains_by_id(students, student.get_student_id())) {
        return false;
    }
    if (!contains_by_id(programs, student.get_program_id())) {
        return false;
    }
    Program* program = get_program(student.get_program_id());
    if (program == nullptr || !program->is_active()) {
        return false;
    }
    students.insert(student, students.count_elements());
    program->get_student_list().insert(student.get_student_id(), program->get_student_list().count_elements());
    return true;
}

Student* EntityManager::get_student(int student_id) {
    for (std::size_t i = 0; i < students.count_elements(); ++i) {
        Student* item = students.get(i);
        if (item != nullptr && item->get_student_id() == student_id) {
            return item;
        }
    }
    return nullptr;
}

const Student* EntityManager::get_student(int student_id) const {
    for (std::size_t i = 0; i < students.count_elements(); ++i) {
        const Student* item = students.get(i);
        if (item != nullptr && item->get_student_id() == student_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Student>& EntityManager::list_students() {
    return students;
}

const LinkedList<Student>& EntityManager::list_students() const {
    return students;
}

bool EntityManager::delete_student(int student_id) {
    Student* student = get_student(student_id);
    if (student == nullptr) {
        return false;
    }
    if (!student->get_enrollment_list().is_empty()) {
        return false;
    }
    for (std::size_t i = 0; i < students.count_elements(); ++i) {
        if (students.get(i) != nullptr && students.get(i)->get_student_id() == student_id) {
            students.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_student(int student_id) {
    Student* student = get_student(student_id);
    if (student == nullptr) {
        return false;
    }
    student->set_active(false);
    return true;
}

bool EntityManager::reactivate_student(int student_id) {
    Student* student = get_student(student_id);
    if (student == nullptr) {
        return false;
    }
    if (!contains_by_id(programs, student->get_program_id())) {
        return false;
    }
    Program* program = get_program(student->get_program_id());
    if (program == nullptr || !program->is_active()) {
        return false;
    }
    student->set_active(true);
    return true;
}

bool EntityManager::create_professor(Professor professor) {
    if (contains_by_id(professors, professor.get_professor_id())) {
        return false;
    }
    if (professor.get_faculty_id() != 0 && !contains_by_id(faculties, professor.get_faculty_id())) {
        return false;
    }
    professors.insert(professor, professors.count_elements());
    return true;
}

Professor* EntityManager::get_professor(int professor_id) {
    for (std::size_t i = 0; i < professors.count_elements(); ++i) {
        Professor* item = professors.get(i);
        if (item != nullptr && item->get_professor_id() == professor_id) {
            return item;
        }
    }
    return nullptr;
}

const Professor* EntityManager::get_professor(int professor_id) const {
    for (std::size_t i = 0; i < professors.count_elements(); ++i) {
        const Professor* item = professors.get(i);
        if (item != nullptr && item->get_professor_id() == professor_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Professor>& EntityManager::list_professors() {
    return professors;
}

const LinkedList<Professor>& EntityManager::list_professors() const {
    return professors;
}

bool EntityManager::delete_professor(int professor_id) {
    for (std::size_t i = 0; i < professors.count_elements(); ++i) {
        if (professors.get(i) != nullptr && professors.get(i)->get_professor_id() == professor_id) {
            professors.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_professor(int professor_id) {
    Professor* professor = get_professor(professor_id);
    if (professor == nullptr) {
        return false;
    }
    professor->set_active(false);
    return true;
}

bool EntityManager::reactivate_professor(int professor_id) {
    Professor* professor = get_professor(professor_id);
    if (professor == nullptr) {
        return false;
    }
    professor->set_active(true);
    return true;
}

bool EntityManager::create_administrative(Administrative administrative) {
    if (contains_by_id(administrative_staff, administrative.get_administrative_id())) {
        return false;
    }
    administrative_staff.insert(administrative, administrative_staff.count_elements());
    return true;
}

Administrative* EntityManager::get_administrative(int administrative_id) {
    for (std::size_t i = 0; i < administrative_staff.count_elements(); ++i) {
        Administrative* item = administrative_staff.get(i);
        if (item != nullptr && item->get_administrative_id() == administrative_id) {
            return item;
        }
    }
    return nullptr;
}

const Administrative* EntityManager::get_administrative(int administrative_id) const {
    for (std::size_t i = 0; i < administrative_staff.count_elements(); ++i) {
        const Administrative* item = administrative_staff.get(i);
        if (item != nullptr && item->get_administrative_id() == administrative_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Administrative>& EntityManager::list_administrative_staff() {
    return administrative_staff;
}

const LinkedList<Administrative>& EntityManager::list_administrative_staff() const {
    return administrative_staff;
}

bool EntityManager::delete_administrative(int administrative_id) {
    for (std::size_t i = 0; i < administrative_staff.count_elements(); ++i) {
        if (administrative_staff.get(i) != nullptr && administrative_staff.get(i)->get_administrative_id() == administrative_id) {
            administrative_staff.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_administrative(int administrative_id) {
    Administrative* administrative = get_administrative(administrative_id);
    if (administrative == nullptr) {
        return false;
    }
    administrative->set_active(false);
    return true;
}

bool EntityManager::reactivate_administrative(int administrative_id) {
    Administrative* administrative = get_administrative(administrative_id);
    if (administrative == nullptr) {
        return false;
    }
    administrative->set_active(true);
    return true;
}

bool EntityManager::create_enrollment(Enrollment enrollment) {
    if (contains_by_id(enrollments, enrollment.get_enrollment_id())) {
        return false;
    }
    Student* student = get_student(enrollment.get_student_id());
    if (student == nullptr || !student->is_active()) {
        return false;
    }
    Course* course = get_course(enrollment.get_course_id());
    if (course == nullptr || !course->is_active()) {
        return false;
    }
    if (student->get_program_id() != course->get_program_id()) {
        return false;
    }
    enrollments.insert(enrollment, enrollments.count_elements());
    student->get_enrollment_list().insert(get_enrollment(enrollment.get_enrollment_id()), student->get_enrollment_list().count_elements());
    course->get_enrollment_list().insert(enrollment.get_enrollment_id(), course->get_enrollment_list().count_elements());
    return true;
}

Enrollment* EntityManager::get_enrollment(int enrollment_id) {
    for (std::size_t i = 0; i < enrollments.count_elements(); ++i) {
        Enrollment* item = enrollments.get(i);
        if (item != nullptr && item->get_enrollment_id() == enrollment_id) {
            return item;
        }
    }
    return nullptr;
}

const Enrollment* EntityManager::get_enrollment(int enrollment_id) const {
    for (std::size_t i = 0; i < enrollments.count_elements(); ++i) {
        const Enrollment* item = enrollments.get(i);
        if (item != nullptr && item->get_enrollment_id() == enrollment_id) {
            return item;
        }
    }
    return nullptr;
}

LinkedList<Enrollment>& EntityManager::list_enrollments() {
    return enrollments;
}

const LinkedList<Enrollment>& EntityManager::list_enrollments() const {
    return enrollments;
}

bool EntityManager::delete_enrollment(int enrollment_id) {
    Enrollment* enrollment = get_enrollment(enrollment_id);
    if (enrollment == nullptr) {
        return false;
    }
    Student* student = get_student(enrollment->get_student_id());
    if (student != nullptr) {
        for (std::size_t i = 0; i < student->get_enrollment_list().count_elements(); ++i) {
            Enrollment** current = student->get_enrollment_list().get(i);
            if (current != nullptr && *current != nullptr && (*current)->get_enrollment_id() == enrollment_id) {
                student->get_enrollment_list().remove_at(i);
                break;
            }
        }
    }
    Course* course = get_course(enrollment->get_course_id());
    if (course != nullptr) {
        for (std::size_t i = 0; i < course->get_enrollment_list().count_elements(); ++i) {
            int* current = course->get_enrollment_list().get(i);
            if (current != nullptr && *current == enrollment_id) {
                course->get_enrollment_list().remove_at(i);
                break;
            }
        }
    }
    for (std::size_t i = 0; i < enrollments.count_elements(); ++i) {
        if (enrollments.get(i) != nullptr && enrollments.get(i)->get_enrollment_id() == enrollment_id) {
            enrollments.remove_at(i);
            return true;
        }
    }
    return false;
}

bool EntityManager::deactivate_enrollment(int enrollment_id) {
    Enrollment* enrollment = get_enrollment(enrollment_id);
    if (enrollment == nullptr) {
        return false;
    }
    enrollment->set_status("Inactive");
    return true;
}

bool EntityManager::reactivate_enrollment(int enrollment_id) {
    Enrollment* enrollment = get_enrollment(enrollment_id);
    if (enrollment == nullptr) {
        return false;
    }
    Student* student = get_student(enrollment->get_student_id());
    Course* course = get_course(enrollment->get_course_id());
    if (student == nullptr || course == nullptr) {
        return false;
    }
    enrollment->set_status("Active");
    return true;
}
