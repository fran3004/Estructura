#ifndef MENU_H
#define MENU_H

#include <string>
#include "EntityManager.h"

class Menu {
public:
    Menu();
    ~Menu();

    void run();

private:
    EntityManager manager;

    void show_banner() const;
    void show_main_menu() const;
    void show_module_menu(const std::string& title) const;
    void wait_for_enter() const;

    int read_int(const std::string& prompt, int minimum, int maximum) const;
    double read_double(const std::string& prompt, double minimum, double maximum) const;
    std::string read_string(const std::string& prompt) const;

    void initialize_demo_data();
    void restore_default_demo_data();

    void handle_faculties();
    void create_faculty();
    void list_faculties() const;
    void search_faculty() const;
    void update_faculty();
    void delete_faculty();
    void deactivate_faculty();

    void handle_programs();
    void create_program();
    void list_programs() const;
    void search_program() const;
    void update_program();
    void delete_program();
    void deactivate_program();

    void handle_courses();
    void create_course();
    void list_courses() const;
    void search_course() const;
    void update_course();
    void delete_course();
    void deactivate_course();

    void handle_students();
    void create_student();
    void list_students() const;
    void search_student() const;
    void update_student();
    void delete_student();
    void deactivate_student();

    void handle_professors();
    void create_professor();
    void list_professors() const;
    void search_professor() const;
    void update_professor();
    void delete_professor();
    void deactivate_professor();

    void handle_administrative();
    void create_administrative();
    void list_administrative_staff() const;
    void search_administrative() const;
    void update_administrative();
    void delete_administrative();
    void deactivate_administrative();

    void handle_enrollments();
    void create_enrollment();
    void list_enrollments() const;
    void search_enrollment() const;
    void update_enrollment_grade();
    void cancel_enrollment();
    void calculate_student_average() const;
    void evaluate_ebra() const;

    void handle_payroll();
    void show_professor_payroll() const;
    void show_administrative_payroll() const;

    void show_reports() const;
    void handle_persistence();
    void save_all_data() const;
    void load_all_data();
};

#endif // MENU_H
