cmake_minimum_required(VERSION 3.16)
project(PITA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main executable and the project's source files.
# The class structure and logic will be completed later.
add_executable(PITA
    src/main.cpp
    src/LinkedList.cpp
    src/Enrollment.cpp
    src/Faculty.cpp
    src/Program.cpp
    src/Course.cpp
    src/Student.cpp
    src/Professor.cpp
    src/Administrative.cpp
    src/Payroll.cpp
    src/Persistence.cpp
    src/Menu.cpp
    src/EntityManager.cpp
)

# Include the project headers.
target_include_directories(PITA PRIVATE src)
