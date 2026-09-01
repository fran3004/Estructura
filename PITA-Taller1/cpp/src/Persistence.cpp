// Implementación mínima de la decisión inicial de carga.

#include "Persistence.h"

#include <iostream>

namespace persistence {

// Las operaciones JSON se implementarán cuando se definan los formatos de cada entidad.
bool save_faculties(const std::string&, const std::string&) { return false; }
bool load_faculties(std::string&, const std::string&) { return false; }
bool save_programs(const std::string&, const std::string&) { return false; }
bool load_programs(std::string&, const std::string&) { return false; }
bool save_courses(const std::string&, const std::string&) { return false; }
bool load_courses(std::string&, const std::string&) { return false; }
bool save_students(const std::string&, const std::string&) { return false; }
bool load_students(std::string&, const std::string&) { return false; }
bool save_professors(const std::string&, const std::string&) { return false; }
bool load_professors(std::string&, const std::string&) { return false; }
bool save_administrative_staff(const std::string&, const std::string&) { return false; }
bool load_administrative_staff(std::string&, const std::string&) { return false; }
bool save_payroll(const std::string&, const std::string&) { return false; }
bool load_payroll(std::string&, const std::string&) { return false; }
bool save_enrollments(const std::string&, const std::string&) { return false; }
bool load_enrollments(std::string&, const std::string&) { return false; }

bool ask_load_existing_data() {
	std::string answer;
	std::cout << "Do you want to load existing data? (y/n): ";
	std::getline(std::cin, answer);
	return answer == "y" || answer == "Y";
}

} // namespace persistence
