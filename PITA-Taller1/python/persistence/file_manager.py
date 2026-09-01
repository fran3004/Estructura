"""Firmas para guardar y cargar entidades en archivos JSON."""

from pathlib import Path


DATA_DIRECTORY = Path(__file__).resolve().parents[2] / "data"


def save_faculties(faculties, file_path=DATA_DIRECTORY / "faculties.json"):
	"""Guardará las facultades en formato JSON."""
	pass


def load_faculties(file_path=DATA_DIRECTORY / "faculties.json"):
	"""Cargará las facultades desde un archivo JSON."""
	pass


def save_programs(programs, file_path=DATA_DIRECTORY / "programs.json"):
	"""Guardará los programas en formato JSON."""
	pass


def load_programs(file_path=DATA_DIRECTORY / "programs.json"):
	"""Cargará los programas desde un archivo JSON."""
	pass


def save_courses(courses, file_path=DATA_DIRECTORY / "courses.json"):
	"""Guardará los cursos en formato JSON."""
	pass


def load_courses(file_path=DATA_DIRECTORY / "courses.json"):
	"""Cargará los cursos desde un archivo JSON."""
	pass


def save_students(students, file_path=DATA_DIRECTORY / "students.json"):
	"""Guardará los estudiantes en formato JSON."""
	pass


def load_students(file_path=DATA_DIRECTORY / "students.json"):
	"""Cargará los estudiantes desde un archivo JSON."""
	pass


def save_professors(professors, file_path=DATA_DIRECTORY / "professors.json"):
	"""Guardará los profesores en formato JSON."""
	pass


def load_professors(file_path=DATA_DIRECTORY / "professors.json"):
	"""Cargará los profesores desde un archivo JSON."""
	pass


def save_administrative_staff(staff, file_path=DATA_DIRECTORY / "administrative_staff.json"):
	"""Guardará el personal administrativo en formato JSON."""
	pass


def load_administrative_staff(file_path=DATA_DIRECTORY / "administrative_staff.json"):
	"""Cargará el personal administrativo desde un archivo JSON."""
	pass


def save_payroll(payroll, file_path=DATA_DIRECTORY / "payroll.json"):
	"""Guardará la nómina en formato JSON."""
	pass


def load_payroll(file_path=DATA_DIRECTORY / "payroll.json"):
	"""Cargará la nómina desde un archivo JSON."""
	pass


def save_enrollments(enrollments, file_path=DATA_DIRECTORY / "enrollments.json"):
	"""Guardará las matrículas en formato JSON."""
	pass


def load_enrollments(file_path=DATA_DIRECTORY / "enrollments.json"):
	"""Cargará las matrículas desde un archivo JSON."""
	pass


def ask_load_existing_data():
	"""Pregunta si se deben cargar los archivos existentes al iniciar."""
	answer = input("Do you want to load existing data? (y/n): ")
	return answer.strip().lower() == "y"
