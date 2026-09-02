#include "Menu.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "Payroll.h"
#include "Persistence.h"

namespace {
std::string to_bool_string(bool value) {
    return value ? "Activo" : "Inactivo";
}

std::string trim(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }
    std::size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }
    return value.substr(start, end - start);
}

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream stream(text);
    std::string item;
    while (std::getline(stream, item, delimiter)) {
        parts.push_back(item);
    }
    return parts;
}

std::string format_money(double value) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
}

bool string_to_bool(const std::string& value) {
    return value == "1" || value == "true" || value == "True" || value == "s" || value == "S";
}
}

Menu::Menu() {
    initialize_demo_data();
    if (persistence::ask_load_existing_data()) {
        load_all_data();
    }
}

Menu::~Menu() = default;

void Menu::run() {
    bool exit_requested = false;

    while (!exit_requested) {
        show_banner();
        show_main_menu();

        const int option = read_int("Seleccione una opción: ", 1, 11);

        switch (option) {
            case 1: handle_faculties(); break;
            case 2: handle_programs(); break;
            case 3: handle_courses(); break;
            case 4: handle_students(); break;
            case 5: handle_professors(); break;
            case 6: handle_administrative(); break;
            case 7: handle_enrollments(); break;
            case 8: handle_payroll(); break;
            case 9: show_reports(); break;
            case 10: handle_persistence(); break;
            case 11:
                std::cout << "Gracias por usar PITA - UPC.\n";
                exit_requested = true;
                break;
            default:
                break;
        }
    }
}

void Menu::show_banner() const {
    std::cout << "\n========================================\n";
    std::cout << "        PITA - UPC\n";
    std::cout << "========================================\n";
}

void Menu::show_main_menu() const {
    std::cout << "1. Facultades\n";
    std::cout << "2. Programas\n";
    std::cout << "3. Cursos\n";
    std::cout << "4. Estudiantes\n";
    std::cout << "5. Profesores\n";
    std::cout << "6. Personal Administrativo\n";
    std::cout << "7. Inscripciones\n";
    std::cout << "8. Nomina\n";
    std::cout << "9. Reportes\n";
    std::cout << "10. Persistencia\n";
    std::cout << "11. Salir\n";
}

void Menu::show_module_menu(const std::string& title) const {
    std::cout << "\n--- " << title << " ---\n";
    std::cout << "1. Crear\n";
    std::cout << "2. Listar\n";
    std::cout << "3. Buscar\n";
    std::cout << "4. Actualizar\n";
    std::cout << "5. Eliminar\n";
    std::cout << "6. Desactivar\n";
    std::cout << "7. Volver\n";
}

void Menu::wait_for_enter() const {
    std::cout << "Presione Enter para continuar...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int Menu::read_int(const std::string& prompt, int minimum, int maximum) const {
    int value = minimum - 1;
    while (true) {
        std::cout << prompt;
        if ((std::cin >> value) && value >= minimum && value <= maximum) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Intente nuevamente.\n";
    }
}

double Menu::read_double(const std::string& prompt, double minimum, double maximum) const {
    double value = minimum - 1.0;
    while (true) {
        std::cout << prompt;
        if ((std::cin >> value) && value >= minimum && value <= maximum) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Intente nuevamente.\n";
    }
}

std::string Menu::read_string(const std::string& prompt) const {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return trim(value);
}

void Menu::initialize_demo_data() {
    Faculty faculty(1, "Facultad de Ingeniería", "Dra. Acosta", "2024-01-15", true, LinkedList<Program*>());
    manager.create_faculty(faculty);

    Program program(1, "Ingeniería de Sistemas", 1, "Ing. García", "Pregrado", "Presencial", true, LinkedList<int>(), LinkedList<int>());
    manager.create_program(program);

    Course course(1, "Estructura de Datos", 1, 4, 3, 1, 30, true, LinkedList<int>());
    manager.create_course(course);

    Student student(1, "Ana Pérez", "DNI", "12345678", "2000-05-18", "ana@upc.edu", "987654321", 1, 5, "Activo", 4.20, true, LinkedList<Enrollment*>());
    manager.create_student(student);

    Professor professor(1, "Carlos Ruiz", "DNI", "87654321", "carlos@upc.edu", "955555555", 1, "Tiempo completo", "Categoria 1", "Doctor", 7, "Completa", 12, "Director", 4.5, 4.0, 3.8, 4.2, 3.9, 120.0, 1.5, 4500.0, 4500.0, 405.0, 540.0, 360.0, 675.0, 990.0, true);
    manager.create_professor(professor);

    Administrative administrative(1, "Marta López", "DNI", "11223344", "marta@upc.edu", "944444444", "Coordinadora", "Administrativo", "Tiempo completo", 3200.0, 256.0, 320.0, 224.0, 320.0, 128.0, 0.0, true);
    manager.create_administrative(administrative);

    Enrollment enrollment(1, 1, 1, "2025-1", 4.5, "Activo", "2025-01-15");
    manager.create_enrollment(enrollment);
}

void Menu::restore_default_demo_data() {
    initialize_demo_data();
}

void Menu::handle_faculties() {
    show_module_menu("Facultades");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_faculty(); break;
        case 2: list_faculties(); break;
        case 3: search_faculty(); break;
        case 4: update_faculty(); break;
        case 5: delete_faculty(); break;
        case 6: deactivate_faculty(); break;
        default: break;
    }
}

void Menu::create_faculty() {
    const int faculty_id = read_int("ID de la facultad: ", 1, 100000);
    const std::string name = read_string("Nombre: ");
    const std::string dean = read_string("Decano(a): ");
    const std::string date = read_string("Fecha de creación: ");
    const bool active = read_int("Estado activo (1/0): ", 0, 1) == 1;

    Faculty faculty(faculty_id, name, dean, date, active, LinkedList<Program*>());
    if (manager.create_faculty(faculty)) {
        std::cout << "Facultad creada correctamente.\n";
    } else {
        std::cout << "No se pudo crear la facultad.\n";
    }
}

void Menu::list_faculties() const {
    auto faculties = manager.list_faculties().to_vector();
    std::cout << "\nFacultades registradas:\n";
    if (faculties.empty()) {
        std::cout << "No hay facultades registradas.\n";
        return;
    }
    for (const auto& faculty : faculties) {
        std::cout << "- ID: " << faculty.get_faculty_id() << " | Nombre: " << faculty.get_name()
                  << " | Decano: " << faculty.get_dean() << " | Estado: " << to_bool_string(faculty.is_active()) << "\n";
    }
}

void Menu::search_faculty() const {
    const int faculty_id = read_int("ID de la facultad a buscar: ", 1, 100000);
    const Faculty* faculty = manager.get_faculty(faculty_id);
    if (faculty == nullptr) {
        std::cout << "Facultad no encontrada.\n";
        return;
    }
    std::cout << "ID: " << faculty->get_faculty_id() << " | Nombre: " << faculty->get_name()
              << " | Decano: " << faculty->get_dean() << " | Estado: " << to_bool_string(faculty->is_active()) << "\n";
}

void Menu::update_faculty() {
    const int faculty_id = read_int("ID de la facultad a actualizar: ", 1, 100000);
    Faculty* faculty = manager.get_faculty(faculty_id);
    if (faculty == nullptr) {
        std::cout << "Facultad no encontrada.\n";
        return;
    }
    faculty->set_name(read_string("Nuevo nombre: "));
    faculty->set_dean(read_string("Nuevo decano: "));
    faculty->set_creation_date(read_string("Nueva fecha: "));
    faculty->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Facultad actualizada.\n";
}

void Menu::delete_faculty() {
    const int faculty_id = read_int("ID de la facultad a eliminar: ", 1, 100000);
    if (manager.delete_faculty(faculty_id)) {
        std::cout << "Facultad eliminada.\n";
    } else {
        std::cout << "No se pudo eliminar la facultad.\n";
    }
}

void Menu::deactivate_faculty() {
    const int faculty_id = read_int("ID de la facultad a desactivar: ", 1, 100000);
    if (manager.deactivate_faculty(faculty_id)) {
        std::cout << "Facultad desactivada.\n";
    } else {
        std::cout << "No se pudo desactivar la facultad.\n";
    }
}

void Menu::handle_programs() {
    show_module_menu("Programas");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_program(); break;
        case 2: list_programs(); break;
        case 3: search_program(); break;
        case 4: update_program(); break;
        case 5: delete_program(); break;
        case 6: deactivate_program(); break;
        default: break;
    }
}

void Menu::create_program() {
    const int program_id = read_int("ID del programa: ", 1, 100000);
    const std::string name = read_string("Nombre: ");
    const int faculty_id = read_int("ID de facultad: ", 1, 100000);
    const std::string director = read_string("Director: ");
    const std::string level = read_string("Nivel: ");
    const std::string modality = read_string("Modalidad: ");
    const bool active = read_int("Activo (1/0): ", 0, 1) == 1;

    Program program(program_id, name, faculty_id, director, level, modality, active, LinkedList<int>(), LinkedList<int>());
    if (manager.create_program(program)) {
        std::cout << "Programa creado correctamente.\n";
    } else {
        std::cout << "No se pudo crear el programa.\n";
    }
}

void Menu::list_programs() const {
    auto programs = manager.list_programs().to_vector();
    std::cout << "\nProgramas registrados:\n";
    for (const auto& program : programs) {
        std::cout << "- ID: " << program.get_program_id() << " | Nombre: " << program.get_name()
                  << " | Facultad: " << program.get_faculty_id() << " | Estado: " << to_bool_string(program.is_active()) << "\n";
    }
}

void Menu::search_program() const {
    const int program_id = read_int("ID del programa a buscar: ", 1, 100000);
    const Program* program = manager.get_program(program_id);
    if (program == nullptr) {
        std::cout << "Programa no encontrado.\n";
        return;
    }
    std::cout << "ID: " << program->get_program_id() << " | Nombre: " << program->get_name()
              << " | Facultad: " << program->get_faculty_id() << " | Estado: " << to_bool_string(program->is_active()) << "\n";
}

void Menu::update_program() {
    const int program_id = read_int("ID del programa a actualizar: ", 1, 100000);
    Program* program = manager.get_program(program_id);
    if (program == nullptr) {
        std::cout << "Programa no encontrado.\n";
        return;
    }
    program->set_name(read_string("Nuevo nombre: "));
    program->set_program_director(read_string("Nuevo director: "));
    program->set_level(read_string("Nuevo nivel: "));
    program->set_modality(read_string("Nueva modalidad: "));
    program->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Programa actualizado.\n";
}

void Menu::delete_program() {
    const int program_id = read_int("ID del programa a eliminar: ", 1, 100000);
    if (manager.delete_program(program_id)) {
        std::cout << "Programa eliminado.\n";
    } else {
        std::cout << "No se pudo eliminar el programa.\n";
    }
}

void Menu::deactivate_program() {
    const int program_id = read_int("ID del programa a desactivar: ", 1, 100000);
    if (manager.deactivate_program(program_id)) {
        std::cout << "Programa desactivado.\n";
    } else {
        std::cout << "No se pudo desactivar el programa.\n";
    }
}

void Menu::handle_courses() {
    show_module_menu("Cursos");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_course(); break;
        case 2: list_courses(); break;
        case 3: search_course(); break;
        case 4: update_course(); break;
        case 5: delete_course(); break;
        case 6: deactivate_course(); break;
        default: break;
    }
}

void Menu::create_course() {
    const int course_id = read_int("ID del curso: ", 1, 100000);
    const std::string name = read_string("Nombre: ");
    const int program_id = read_int("ID del programa: ", 1, 100000);
    const int credits = read_int("Créditos: ", 1, 10);
    const int semester = read_int("Semestre curricular: ", 1, 12);
    const int professor_id = read_int("ID profesor asignado: ", 0, 100000);
    const int max_capacity = read_int("Capacidad máxima: ", 1, 200);
    const bool active = read_int("Activo (1/0): ", 0, 1) == 1;

    Course course(course_id, name, program_id, credits, semester, professor_id, max_capacity, active, LinkedList<int>());
    if (manager.create_course(course)) {
        std::cout << "Curso creado correctamente.\n";
    } else {
        std::cout << "No se pudo crear el curso.\n";
    }
}

void Menu::list_courses() const {
    auto courses = manager.list_courses().to_vector();
    std::cout << "\nCursos registrados:\n";
    for (const auto& course : courses) {
        std::cout << "- ID: " << course.get_course_id() << " | Nombre: " << course.get_name()
                  << " | Programa: " << course.get_program_id() << " | Estado: " << to_bool_string(course.is_active()) << "\n";
    }
}

void Menu::search_course() const {
    const int course_id = read_int("ID del curso a buscar: ", 1, 100000);
    const Course* course = manager.get_course(course_id);
    if (course == nullptr) {
        std::cout << "Curso no encontrado.\n";
        return;
    }
    std::cout << "ID: " << course->get_course_id() << " | Nombre: " << course->get_name()
              << " | Programa: " << course->get_program_id() << " | Estado: " << to_bool_string(course->is_active()) << "\n";
}

void Menu::update_course() {
    const int course_id = read_int("ID del curso a actualizar: ", 1, 100000);
    Course* course = manager.get_course(course_id);
    if (course == nullptr) {
        std::cout << "Curso no encontrado.\n";
        return;
    }
    course->set_name(read_string("Nuevo nombre: "));
    course->set_credits(read_int("Nuevos créditos: ", 1, 10));
    course->set_curriculum_semester(read_int("Nuevo semestre: ", 1, 12));
    course->set_max_capacity(read_int("Nueva capacidad: ", 1, 200));
    course->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Curso actualizado.\n";
}

void Menu::delete_course() {
    const int course_id = read_int("ID del curso a eliminar: ", 1, 100000);
    if (manager.delete_course(course_id)) {
        std::cout << "Curso eliminado.\n";
    } else {
        std::cout << "No se pudo eliminar el curso.\n";
    }
}

void Menu::deactivate_course() {
    const int course_id = read_int("ID del curso a desactivar: ", 1, 100000);
    if (manager.deactivate_course(course_id)) {
        std::cout << "Curso desactivado.\n";
    } else {
        std::cout << "No se pudo desactivar el curso.\n";
    }
}

void Menu::handle_students() {
    show_module_menu("Estudiantes");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_student(); break;
        case 2: list_students(); break;
        case 3: search_student(); break;
        case 4: update_student(); break;
        case 5: delete_student(); break;
        case 6: deactivate_student(); break;
        default: break;
    }
}

void Menu::create_student() {
    const int student_id = read_int("ID del estudiante: ", 1, 100000);
    const std::string full_name = read_string("Nombre completo: ");
    const std::string doc_type = read_string("Tipo de documento: ");
    const std::string doc_number = read_string("Número de documento: ");
    const std::string birth_date = read_string("Fecha de nacimiento: ");
    const std::string email = read_string("Correo: ");
    const std::string phone = read_string("Teléfono: ");
    const int program_id = read_int("ID del programa: ", 1, 100000);
    const int semester = read_int("Semestre actual: ", 1, 20);
    const std::string status = read_string("Estado: ");
    const double average = read_double("Promedio acumulado: ", 0.0, 5.0);
    const bool active = read_int("Activo (1/0): ", 0, 1) == 1;

    Student student(student_id, full_name, doc_type, doc_number, birth_date, email, phone, program_id, semester, status, average, active, LinkedList<Enrollment*>());
    if (manager.create_student(student)) {
        std::cout << "Estudiante creado correctamente.\n";
    } else {
        std::cout << "No se pudo crear el estudiante.\n";
    }
}

void Menu::list_students() const {
    auto students = manager.list_students().to_vector();
    std::cout << "\nEstudiantes registrados:\n";
    for (const auto& student : students) {
        std::cout << "- ID: " << student.get_student_id() << " | Nombre: " << student.get_full_name()
                  << " | Programa: " << student.get_program_id() << " | Promedio: " << format_money(student.get_cumulative_average())
                  << " | Estado: " << to_bool_string(student.is_active()) << "\n";
    }
}

void Menu::search_student() const {
    const int student_id = read_int("ID del estudiante a buscar: ", 1, 100000);
    const Student* student = manager.get_student(student_id);
    if (student == nullptr) {
        std::cout << "Estudiante no encontrado.\n";
        return;
    }
    std::cout << "ID: " << student->get_student_id() << " | Nombre: " << student->get_full_name()
              << " | Programa: " << student->get_program_id() << " | Promedio: " << format_money(student->get_cumulative_average())
              << " | Estado: " << to_bool_string(student->is_active()) << "\n";
}

void Menu::update_student() {
    const int student_id = read_int("ID del estudiante a actualizar: ", 1, 100000);
    Student* student = manager.get_student(student_id);
    if (student == nullptr) {
        std::cout << "Estudiante no encontrado.\n";
        return;
    }
    student->set_full_name(read_string("Nuevo nombre: "));
    student->set_program_id(read_int("Nuevo programa: ", 1, 100000));
    student->set_status(read_string("Nuevo estado: "));
    student->set_cumulative_average(read_double("Nuevo promedio: ", 0.0, 5.0));
    student->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Estudiante actualizado.\n";
}

void Menu::delete_student() {
    const int student_id = read_int("ID del estudiante a eliminar: ", 1, 100000);
    if (manager.delete_student(student_id)) {
        std::cout << "Estudiante eliminado.\n";
    } else {
        std::cout << "No se pudo eliminar el estudiante.\n";
    }
}

void Menu::deactivate_student() {
    const int student_id = read_int("ID del estudiante a desactivar: ", 1, 100000);
    if (manager.deactivate_student(student_id)) {
        std::cout << "Estudiante desactivado.\n";
    } else {
        std::cout << "No se pudo desactivar el estudiante.\n";
    }
}

void Menu::handle_professors() {
    show_module_menu("Profesores");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_professor(); break;
        case 2: list_professors(); break;
        case 3: search_professor(); break;
        case 4: update_professor(); break;
        case 5: delete_professor(); break;
        case 6: deactivate_professor(); break;
        default: break;
    }
}

void Menu::create_professor() {
    const int professor_id = read_int("ID del profesor: ", 1, 100000);
    const std::string full_name = read_string("Nombre completo: ");
    const std::string document_type = read_string("Tipo de documento: ");
    const std::string document_number = read_string("Número de documento: ");
    const std::string email = read_string("Correo: ");
    const std::string phone = read_string("Teléfono: ");
    const int faculty_id = read_int("ID de facultad: ", 0, 100000);
    const std::string employment_type = read_string("Tipo de contratación: ");
    const std::string category_rank = read_string("Rango: ");
    const std::string academic_title = read_string("Título académico: ");
    const int experience = read_int("Años de experiencia: ", 0, 80);
    const std::string dedication = read_string("Dedicación: ");
    const int lecture_hours = read_int("Horas de clase: ", 0, 80);
    const std::string managerial_role = read_string("Rol administrativo: ");
    const double category_score = read_double("Puntaje de categoría: ", 0.0, 10.0);
    const double title_score = read_double("Puntaje de título: ", 0.0, 10.0);
    const double experience_score = read_double("Puntaje de experiencia: ", 0.0, 10.0);
    const double productivity_score = read_double("Puntaje de productividad: ", 0.0, 10.0);
    const double academic_management_score = read_double("Puntaje académico: ", 0.0, 10.0);
    const double total_points = read_double("Puntaje total: ", 0.0, 1000.0);
    const double point_value = read_double("Valor por punto: ", 0.0, 1000.0);
    const double base_monthly_salary = read_double("Salario base: ", 0.0, 100000.0);
    const double health_discount = read_double("Descuento salud: ", 0.0, 100000.0);
    const double pension_discount = read_double("Descuento pensión: ", 0.0, 100000.0);
    const double severance_provision = read_double("Provisión de cesantía: ", 0.0, 100000.0);
    const double bonus_provision = read_double("Provisión de bonificación: ", 0.0, 100000.0);
    const double vacation_provision = read_double("Provisión de vacaciones: ", 0.0, 100000.0);
    const double net_salary = read_double("Salario neto: ", 0.0, 100000.0);
    const bool active = read_int("Activo (1/0): ", 0, 1) == 1;

    Professor professor(professor_id, full_name, document_type, document_number, email, phone, faculty_id, employment_type, category_rank, academic_title, experience, dedication, lecture_hours, managerial_role, category_score, title_score, experience_score, productivity_score, academic_management_score, total_points, point_value, base_monthly_salary, health_discount, pension_discount, severance_provision, bonus_provision, vacation_provision, net_salary, active);
    if (manager.create_professor(professor)) {
        std::cout << "Profesor creado correctamente.\n";
    } else {
        std::cout << "No se pudo crear el profesor.\n";
    }
}

void Menu::list_professors() const {
    auto professors = manager.list_professors().to_vector();
    std::cout << "\nProfesores registrados:\n";
    for (const auto& professor : professors) {
        std::cout << "- ID: " << professor.get_professor_id() << " | Nombre: " << professor.get_full_name()
                  << " | Facultad: " << professor.get_faculty_id() << " | Título: " << professor.get_academic_title()
                  << " | Salario base: " << format_money(professor.get_base_monthly_salary()) << "\n";
    }
}

void Menu::search_professor() const {
    const int professor_id = read_int("ID del profesor a buscar: ", 1, 100000);
    const Professor* professor = manager.get_professor(professor_id);
    if (professor == nullptr) {
        std::cout << "Profesor no encontrado.\n";
        return;
    }
    std::cout << "ID: " << professor->get_professor_id() << " | Nombre: " << professor->get_full_name()
              << " | Facultad: " << professor->get_faculty_id() << " | Estado: " << to_bool_string(professor->is_active()) << "\n";
}

void Menu::update_professor() {
    const int professor_id = read_int("ID del profesor a actualizar: ", 1, 100000);
    Professor* professor = manager.get_professor(professor_id);
    if (professor == nullptr) {
        std::cout << "Profesor no encontrado.\n";
        return;
    }
    professor->set_full_name(read_string("Nuevo nombre: "));
    professor->set_faculty_id(read_int("Nueva facultad: ", 0, 100000));
    professor->set_employment_type(read_string("Nuevo tipo de contratación: "));
    professor->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Profesor actualizado.\n";
}

void Menu::delete_professor() {
    const int professor_id = read_int("ID del profesor a eliminar: ", 1, 100000);
    if (manager.delete_professor(professor_id)) {
        std::cout << "Profesor eliminado.\n";
    } else {
        std::cout << "No se pudo eliminar el profesor.\n";
    }
}

void Menu::deactivate_professor() {
    const int professor_id = read_int("ID del profesor a desactivar: ", 1, 100000);
    if (manager.deactivate_professor(professor_id)) {
        std::cout << "Profesor desactivado.\n";
    } else {
        std::cout << "No se pudo desactivar el profesor.\n";
    }
}

void Menu::handle_administrative() {
    show_module_menu("Personal Administrativo");
    const int option = read_int("Seleccione una opción: ", 1, 7);
    switch (option) {
        case 1: create_administrative(); break;
        case 2: list_administrative_staff(); break;
        case 3: search_administrative(); break;
        case 4: update_administrative(); break;
        case 5: delete_administrative(); break;
        case 6: deactivate_administrative(); break;
        default: break;
    }
}

void Menu::create_administrative() {
    const int administrative_id = read_int("ID del personal: ", 1, 100000);
    const std::string full_name = read_string("Nombre completo: ");
    const std::string doc_type = read_string("Tipo de documento: ");
    const std::string doc_number = read_string("Número de documento: ");
    const std::string email = read_string("Correo: ");
    const std::string phone = read_string("Teléfono: ");
    const std::string position = read_string("Cargo: ");
    const std::string category = read_string("Categoría: ");
    const std::string employment_type = read_string("Tipo de contratación: ");
    const double base_salary = read_double("Salario base: ", 0.0, 100000.0);
    const double health_discount = read_double("Descuento salud: ", 0.0, 100000.0);
    const double pension_discount = read_double("Descuento pensión: ", 0.0, 100000.0);
    const double severance = read_double("Cesantía: ", 0.0, 100000.0);
    const double holiday_bonus = read_double("Bonificación: ", 0.0, 100000.0);
    const double vacation = read_double("Vacaciones: ", 0.0, 100000.0);
    const double net_salary = read_double("Salario neto: ", 0.0, 100000.0);
    const bool active = read_int("Activo (1/0): ", 0, 1) == 1;

    Administrative administrative(administrative_id, full_name, doc_type, doc_number, email, phone, position, category, employment_type, base_salary, health_discount, pension_discount, severance, holiday_bonus, vacation, net_salary, active);
    if (manager.create_administrative(administrative)) {
        std::cout << "Personal administrativo creado correctamente.\n";
    } else {
        std::cout << "No se pudo crear el personal administrativo.\n";
    }
}

void Menu::list_administrative_staff() const {
    auto staff = manager.list_administrative_staff().to_vector();
    std::cout << "\nPersonal administrativo registrado:\n";
    for (const auto& person : staff) {
        std::cout << "- ID: " << person.get_administrative_id() << " | Nombre: " << person.get_full_name()
                  << " | Cargo: " << person.get_position() << " | Salario base: " << format_money(person.get_base_salary()) << "\n";
    }
}

void Menu::search_administrative() const {
    const int administrative_id = read_int("ID del personal a buscar: ", 1, 100000);
    const Administrative* person = manager.get_administrative(administrative_id);
    if (person == nullptr) {
        std::cout << "Personal no encontrado.\n";
        return;
    }
    std::cout << "ID: " << person->get_administrative_id() << " | Nombre: " << person->get_full_name()
              << " | Cargo: " << person->get_position() << " | Estado: " << to_bool_string(person->is_active()) << "\n";
}

void Menu::update_administrative() {
    const int administrative_id = read_int("ID del personal a actualizar: ", 1, 100000);
    Administrative* person = manager.get_administrative(administrative_id);
    if (person == nullptr) {
        std::cout << "Personal no encontrado.\n";
        return;
    }
    person->set_full_name(read_string("Nuevo nombre: "));
    person->set_active(read_int("Activo (1/0): ", 0, 1) == 1);
    std::cout << "Personal actualizado.\n";
}

void Menu::delete_administrative() {
    const int administrative_id = read_int("ID del personal a eliminar: ", 1, 100000);
    if (manager.delete_administrative(administrative_id)) {
        std::cout << "Personal eliminado.\n";
    } else {
        std::cout << "No se pudo eliminar el personal.\n";
    }
}

void Menu::deactivate_administrative() {
    const int administrative_id = read_int("ID del personal a desactivar: ", 1, 100000);
    if (manager.deactivate_administrative(administrative_id)) {
        std::cout << "Personal desactivado.\n";
    } else {
        std::cout << "No se pudo desactivar el personal.\n";
    }
}

void Menu::handle_enrollments() {
    std::cout << "\n--- Inscripciones ---\n";
    std::cout << "1. Crear inscripcion\n";
    std::cout << "2. Listar inscripciones\n";
    std::cout << "3. Buscar inscripción\n";
    std::cout << "4. Registrar nota final\n";
    std::cout << "5. Cancelar inscripcion\n";
    std::cout << "6. Calcular promedio de estudiante\n";
    std::cout << "7. Evaluar EBRA\n";
    std::cout << "8. Volver\n";

    const int option = read_int("Seleccione una opción: ", 1, 8);
    switch (option) {
        case 1: create_enrollment(); break;
        case 2: list_enrollments(); break;
        case 3: search_enrollment(); break;
        case 4: update_enrollment_grade(); break;
        case 5: cancel_enrollment(); break;
        case 6: calculate_student_average(); break;
        case 7: evaluate_ebra(); break;
        default: break;
    }
}

void Menu::create_enrollment() {
    const int enrollment_id = read_int("ID de inscripción: ", 1, 100000);
    const int student_id = read_int("ID del estudiante: ", 1, 100000);
    const int course_id = read_int("ID del curso: ", 1, 100000);
    const std::string period = read_string("Periodo académico: ");
    const double final_grade = read_double("Nota final: ", 0.0, 5.0);
    const std::string status = read_string("Estado: ");
    const std::string enrollment_date = read_string("Fecha de inscripción: ");

    Enrollment enrollment(enrollment_id, student_id, course_id, period, final_grade, status, enrollment_date);
    if (manager.create_enrollment(enrollment)) {
        std::cout << "Inscripción creada correctamente.\n";
    } else {
        std::cout << "No se pudo registrar la inscripción.\n";
    }
}

void Menu::list_enrollments() const {
    auto enrollments = manager.list_enrollments().to_vector();
    std::cout << "\nInscripciones registradas:\n";
    for (const auto& enrollment : enrollments) {
        std::cout << "- ID: " << enrollment.get_enrollment_id() << " | Estudiante: " << enrollment.get_student_id()
                  << " | Curso: " << enrollment.get_course_id() << " | Nota: " << format_money(enrollment.get_final_grade())
                  << " | Estado: " << enrollment.get_status() << "\n";
    }
}

void Menu::search_enrollment() const {
    const int enrollment_id = read_int("ID de inscripción a buscar: ", 1, 100000);
    const Enrollment* enrollment = manager.get_enrollment(enrollment_id);
    if (enrollment == nullptr) {
        std::cout << "Inscripción no encontrada.\n";
        return;
    }
    std::cout << "ID: " << enrollment->get_enrollment_id() << " | Estudiante: " << enrollment->get_student_id()
              << " | Curso: " << enrollment->get_course_id() << " | Nota: " << format_money(enrollment->get_final_grade())
              << " | Estado: " << enrollment->get_status() << "\n";
}

void Menu::update_enrollment_grade() {
    const int enrollment_id = read_int("ID de inscripción: ", 1, 100000);
    Enrollment* enrollment = manager.get_enrollment(enrollment_id);
    if (enrollment == nullptr) {
        std::cout << "Inscripción no encontrada.\n";
        return;
    }
    const double grade = read_double("Nueva nota final: ", 0.0, 5.0);
    enrollment->set_final_grade(grade);
    std::cout << "Nota final actualizada.\n";
}

void Menu::cancel_enrollment() {
    const int enrollment_id = read_int("ID de inscripción a cancelar: ", 1, 100000);
    if (manager.delete_enrollment(enrollment_id)) {
        std::cout << "Inscripción cancelada.\n";
    } else {
        std::cout << "No se pudo cancelar la inscripción.\n";
    }
}

void Menu::calculate_student_average() const {
    const int student_id = read_int("ID del estudiante: ", 1, 100000);
    const Student* student = manager.get_student(student_id);
    if (student == nullptr) {
        std::cout << "Estudiante no encontrado.\n";
        return;
    }
    double total = 0.0;
    int count = 0;
    for (std::size_t i = 0; i < student->get_enrollment_list().count_elements(); ++i) {
        const Enrollment* const* enrollment = student->get_enrollment_list().get(i);
        if (enrollment != nullptr && *enrollment != nullptr) {
            total += (*enrollment)->get_final_grade();
            ++count;
        }
    }
    const double average = count == 0 ? 0.0 : total / count;
    std::cout << "Promedio de " << student->get_full_name() << ": " << format_money(average) << "\n";
}

void Menu::evaluate_ebra() const {
    const int student_id = read_int("ID del estudiante: ", 1, 100000);
    const Student* student = manager.get_student(student_id);
    if (student == nullptr) {
        std::cout << "Estudiante no encontrado.\n";
        return;
    }
    const double average = student->get_cumulative_average();
    std::cout << "EBRA para " << student->get_full_name() << ": ";
    if (average >= 4.0) {
        std::cout << "Aprobado por excelencia académica\n";
    } else if (average >= 3.0) {
        std::cout << "En seguimiento académico\n";
    } else {
        std::cout << "Requiere apoyo académico\n";
    }
}

void Menu::handle_payroll() {
    std::cout << "\n--- Nómina ---\n";
    std::cout << "1. Nómina de profesores\n";
    std::cout << "2. Nómina de administrativos\n";
    std::cout << "3. Volver\n";

    const int option = read_int("Seleccione una opción: ", 1, 3);
    switch (option) {
        case 1: show_professor_payroll(); break;
        case 2: show_administrative_payroll(); break;
        default: break;
    }
}

void Menu::show_professor_payroll() const {
    Payroll payroll("Nómina de profesores");
    auto professors = manager.list_professors().to_vector();
    std::cout << "\nNómina de profesores:\n";
    for (const auto& professor : professors) {
        const double salary = payroll.calculate_professor_salary(professor);
        std::cout << "- " << professor.get_full_name() << " | Salario neto: S/. " << format_money(salary) << "\n";
    }
}

void Menu::show_administrative_payroll() const {
    Payroll payroll("Nómina administrativa");
    auto staff = manager.list_administrative_staff().to_vector();
    std::cout << "\nNómina administrativa:\n";
    for (const auto& person : staff) {
        const double salary = payroll.calculate_administrative_salary(person);
        std::cout << "- " << person.get_full_name() << " | Salario neto: S/. " << format_money(salary) << "\n";
    }
}

void Menu::show_reports() const {
    std::cout << "\n--- Reportes ---\n";
    std::cout << "Facultades: " << manager.list_faculties().count_elements() << "\n";
    std::cout << "Programas: " << manager.list_programs().count_elements() << "\n";
    std::cout << "Cursos: " << manager.list_courses().count_elements() << "\n";
    std::cout << "Estudiantes: " << manager.list_students().count_elements() << "\n";
    std::cout << "Profesores: " << manager.list_professors().count_elements() << "\n";
    std::cout << "Personal administrativo: " << manager.list_administrative_staff().count_elements() << "\n";
    std::cout << "Inscripciones: " << manager.list_enrollments().count_elements() << "\n";
}

void Menu::handle_persistence() {
    std::cout << "\n--- Persistencia ---\n";
    std::cout << "1. Guardar todos los datos\n";
    std::cout << "2. Cargar todos los datos\n";
    std::cout << "3. Volver\n";
    const int option = read_int("Seleccione una opción: ", 1, 3);
    if (option == 1) {
        save_all_data();
    } else if (option == 2) {
        load_all_data();
    }
}

void Menu::save_all_data() const {
    std::filesystem::path data_dir("../data");
    std::filesystem::create_directories(data_dir);

    std::ofstream faculty_file("../data/faculties.txt", std::ios::trunc);
    for (const auto& faculty : manager.list_faculties().to_vector()) {
        faculty_file << faculty.get_faculty_id() << "|" << faculty.get_name() << "|" << faculty.get_dean() << "|" << faculty.get_creation_date() << "|" << (faculty.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream program_file("../data/programs.txt", std::ios::trunc);
    for (const auto& program : manager.list_programs().to_vector()) {
        program_file << program.get_program_id() << "|" << program.get_name() << "|" << program.get_faculty_id() << "|" << program.get_program_director() << "|" << program.get_level() << "|" << program.get_modality() << "|" << (program.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream course_file("../data/courses.txt", std::ios::trunc);
    for (const auto& course : manager.list_courses().to_vector()) {
        course_file << course.get_course_id() << "|" << course.get_name() << "|" << course.get_program_id() << "|" << course.get_credits() << "|" << course.get_curriculum_semester() << "|" << course.get_assigned_professor_id() << "|" << course.get_max_capacity() << "|" << (course.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream student_file("../data/students.txt", std::ios::trunc);
    for (const auto& student : manager.list_students().to_vector()) {
        student_file << student.get_student_id() << "|" << student.get_full_name() << "|" << student.get_program_id() << "|" << format_money(student.get_cumulative_average()) << "|" << (student.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream professor_file("../data/professors.txt", std::ios::trunc);
    for (const auto& professor : manager.list_professors().to_vector()) {
        professor_file << professor.get_professor_id() << "|" << professor.get_full_name() << "|" << professor.get_faculty_id() << "|" << professor.get_academic_title() << "|" << format_money(professor.get_base_monthly_salary()) << "|" << (professor.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream admin_file("../data/administrative.txt", std::ios::trunc);
    for (const auto& person : manager.list_administrative_staff().to_vector()) {
        admin_file << person.get_administrative_id() << "|" << person.get_full_name() << "|" << person.get_position() << "|" << format_money(person.get_base_salary()) << "|" << (person.is_active() ? 1 : 0) << "\n";
    }

    std::ofstream enrollment_file("../data/enrollments.txt", std::ios::trunc);
    for (const auto& enrollment : manager.list_enrollments().to_vector()) {
        enrollment_file << enrollment.get_enrollment_id() << "|" << enrollment.get_student_id() << "|" << enrollment.get_course_id() << "|" << enrollment.get_final_grade() << "|" << enrollment.get_status() << "\n";
    }

    std::cout << "Datos guardados correctamente en la carpeta data.\n";
}

void Menu::load_all_data() {
    std::cout << "Cargando datos desde la carpeta data...\n";

    manager = EntityManager();

    std::ifstream faculty_file("../data/faculties.txt");
    if (faculty_file.is_open()) {
        std::string line;
        while (std::getline(faculty_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 5) {
                Faculty faculty(std::stoi(parts[0]), parts[1], parts[2], parts[3], string_to_bool(parts[4]), LinkedList<Program*>());
                manager.create_faculty(faculty);
            }
        }
    }

    std::ifstream program_file("../data/programs.txt");
    if (program_file.is_open()) {
        std::string line;
        while (std::getline(program_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 7) {
                Program program(std::stoi(parts[0]), parts[1], std::stoi(parts[2]), parts[3], parts[4], parts[5], string_to_bool(parts[6]), LinkedList<int>(), LinkedList<int>());
                manager.create_program(program);
            }
        }
    }

    std::ifstream course_file("../data/courses.txt");
    if (course_file.is_open()) {
        std::string line;
        while (std::getline(course_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 8) {
                Course course(std::stoi(parts[0]), parts[1], std::stoi(parts[2]), std::stoi(parts[3]), std::stoi(parts[4]), std::stoi(parts[5]), std::stoi(parts[6]), string_to_bool(parts[7]), LinkedList<int>());
                manager.create_course(course);
            }
        }
    }

    std::ifstream student_file("../data/students.txt");
    if (student_file.is_open()) {
        std::string line;
        while (std::getline(student_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 5) {
                Student student(std::stoi(parts[0]), parts[1], "DNI", "00000000", "2000-01-01", "@upc.edu", "000000000", std::stoi(parts[2]), 1, "Activo", std::stod(parts[3]), string_to_bool(parts[4]), LinkedList<Enrollment*>());
                manager.create_student(student);
            }
        }
    }

    std::ifstream professor_file("../data/professors.txt");
    if (professor_file.is_open()) {
        std::string line;
        while (std::getline(professor_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 6) {
                Professor professor(std::stoi(parts[0]), parts[1], "DNI", "00000000", "@upc.edu", "000000000", std::stoi(parts[2]), "Tiempo completo", "Categoria 1", parts[3], 0, "Completa", 0, "Director", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, std::stod(parts[4]), 0.0, 0.0, 0.0, 0.0, 0.0, std::stod(parts[4]), string_to_bool(parts[5]));
                manager.create_professor(professor);
            }
        }
    }

    std::ifstream admin_file("../data/administrative.txt");
    if (admin_file.is_open()) {
        std::string line;
        while (std::getline(admin_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 5) {
                Administrative admin(std::stoi(parts[0]), parts[1], "DNI", "00000000", "@upc.edu", "000000000", parts[2], "Categoria", "Tiempo completo", std::stod(parts[3]), 0.0, 0.0, 0.0, 0.0, 0.0, std::stod(parts[3]), string_to_bool(parts[4]));
                manager.create_administrative(admin);
            }
        }
    }

    std::ifstream enrollment_file("../data/enrollments.txt");
    if (enrollment_file.is_open()) {
        std::string line;
        while (std::getline(enrollment_file, line)) {
            if (line.empty()) continue;
            const auto parts = split(line, '|');
            if (parts.size() >= 5) {
                Enrollment enrollment(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), "2025-1", std::stod(parts[3]), parts[4], "2025-01-01");
                manager.create_enrollment(enrollment);
            }
        }
    }

    std::cout << "Datos cargados correctamente.\n";
}

