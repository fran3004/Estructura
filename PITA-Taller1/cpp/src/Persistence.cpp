// Implementación de persistencia funcional para la aplicación console en C++.

#include "Persistence.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace persistence {
namespace {

bool write_file(const std::string& file_path, const std::string& data) {
    std::filesystem::path path(file_path);
    if (path.has_parent_path()) {
        std::filesystem::create_directories(path.parent_path());
    }
    std::ofstream file(file_path, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }
    file << data;
    return file.good();
}

bool read_file(const std::string& file_path, std::string& data) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    data = buffer.str();
    return true;
}

} // namespace

bool save_faculties(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_faculties(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_programs(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_programs(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_courses(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_courses(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_students(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_students(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_professors(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_professors(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_administrative_staff(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_administrative_staff(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_payroll(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_payroll(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool save_enrollments(const std::string& json_data, const std::string& file_path) { return write_file(file_path, json_data); }
bool load_enrollments(std::string& json_data, const std::string& file_path) { return read_file(file_path, json_data); }

bool ask_load_existing_data() {
    std::string answer;
    std::cout << "¿Desea cargar los datos existentes? (s/n): ";
    std::getline(std::cin, answer);
    return answer == "s" || answer == "S" || answer == "y" || answer == "Y";
}

} // namespace persistence
