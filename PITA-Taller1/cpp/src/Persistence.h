// Declaraciones para guardar y cargar la información del sistema en JSON.

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>

namespace persistence {

bool save_faculties(const std::string& json_data,
					const std::string& file_path = "../data/faculties.json");
bool load_faculties(std::string& json_data,
					const std::string& file_path = "../data/faculties.json");

bool save_programs(const std::string& json_data,
				   const std::string& file_path = "../data/programs.json");
bool load_programs(std::string& json_data,
				   const std::string& file_path = "../data/programs.json");

bool save_courses(const std::string& json_data,
				  const std::string& file_path = "../data/courses.json");
bool load_courses(std::string& json_data,
				  const std::string& file_path = "../data/courses.json");

bool save_students(const std::string& json_data,
				   const std::string& file_path = "../data/students.json");
bool load_students(std::string& json_data,
				   const std::string& file_path = "../data/students.json");

bool save_professors(const std::string& json_data,
					 const std::string& file_path = "../data/professors.json");
bool load_professors(std::string& json_data,
					 const std::string& file_path = "../data/professors.json");

bool save_administrative_staff(const std::string& json_data,
							   const std::string& file_path = "../data/administrative_staff.json");
bool load_administrative_staff(std::string& json_data,
							   const std::string& file_path = "../data/administrative_staff.json");

bool save_payroll(const std::string& json_data,
				  const std::string& file_path = "../data/payroll.json");
bool load_payroll(std::string& json_data,
				  const std::string& file_path = "../data/payroll.json");

bool save_enrollments(const std::string& json_data,
					  const std::string& file_path = "../data/enrollments.json");
bool load_enrollments(std::string& json_data,
					  const std::string& file_path = "../data/enrollments.json");

// Pregunta si se deben cargar los archivos existentes al iniciar el programa.
bool ask_load_existing_data();

} // namespace persistence

#endif // PERSISTENCE_H
