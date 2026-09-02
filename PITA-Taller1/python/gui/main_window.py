import tkinter as tk
from tkinter import ttk

from models.linked_list import LinkedList
from persistence.file_manager import (
    load_administrative_staff,
    load_courses,
    load_enrollments,
    load_faculties,
    load_payroll,
    load_professors,
    load_programs,
    load_students,
    save_administrative_staff,
    save_courses,
    save_enrollments,
    save_faculties,
    save_payroll,
    save_professors,
    save_programs,
    save_students,
)
from services.entity_manager import EntityManager
from .faculty_view import FacultyView
from .program_view import ProgramView
from .course_view import CourseView
from .student_view import StudentView
from .professor_view import ProfessorView
from .administrative_view import AdministrativeView
from .payroll_view import PayrollView
from .theme import THEME, apply_theme


class DashboardWindow(tk.Toplevel):
    """Panel de control resumido y reutilizable."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("UPC | PITA | Panel de control")
        self.geometry("780x420")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager

        ttk.Label(self, text="Panel de control", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        cards = [
            ("Facultades", self.manager.faculties.count_elements()),
            ("Programas", self.manager.programs.count_elements()),
            ("Cursos", self.manager.courses.count_elements()),
            ("Estudiantes", self.manager.students.count_elements()),
            ("Profesores", self.manager.professors.count_elements()),
            ("Administrativos", self.manager.administrative_staff.count_elements()),
            ("Inscripciones activas", self._active_enrollments()),
            ("Alertas EBRA", self._ebra_alerts()),
        ]

        container = ttk.Frame(self)
        container.pack(fill="both", expand=True, padx=16, pady=(0, 16))

        for idx, (label, value) in enumerate(cards):
            frame = ttk.Frame(container, padding=12)
            frame.grid(row=idx // 4, column=idx % 4, padx=8, pady=8, sticky="nsew")
            ttk.Label(frame, text=label, foreground=THEME["text_soft"]).pack(anchor="w")
            ttk.Label(frame, text=str(value), font=("Segoe UI", 18, "bold"), foreground=THEME["primary_green_dark"]).pack(anchor="w", pady=(6, 0))

    def _active_enrollments(self):
        count = 0
        current = self.manager.enrollments.head
        while current is not None:
            item = current.data
            if getattr(item, "status", "").upper() in {"ACTIVE", "COMPLETED"}:
                count += 1
            current = current.next
        return count

    def _ebra_alerts(self):
        count = 0
        current = self.manager.students.head
        while current is not None:
            student = current.data
            if self.manager.evaluate_ebra_status(student.student_id)["status"] == "EBRA":
                count += 1
            current = current.next
        return count


class MainWindow(tk.Tk):
    """Ventana principal con navegación por secciones de la aplicación."""

    def __init__(self):
        super().__init__()
        self.title("UPC | PITA | Sistema de Gestión Académica")
        self.geometry("420x640")
        self.resizable(False, False)
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = EntityManager()
        self._load_state()

        header = ttk.Label(self, text="UPC\nPITA", style="Title.TLabel", font=("Segoe UI", 24, "bold"), background=THEME["primary_green_dark"], foreground="white")
        header.pack(fill="x", pady=(0, 20))

        actions = [
            ("Panel de control", lambda: DashboardWindow(self, self.manager)),
            ("Facultades", lambda: FacultyView(self, self.manager)),
            ("Programas", lambda: ProgramView(self, self.manager)),
            ("Cursos", lambda: CourseView(self, self.manager)),
            ("Estudiantes", lambda: StudentView(self, self.manager)),
            ("Profesores", lambda: ProfessorView(self, self.manager)),
            ("Personal administrativo", lambda: AdministrativeView(self, self.manager)),
            ("Inscripciones", lambda: self.open_placeholder("Inscripciones")),
            ("Nómina", lambda: PayrollView(self, self.manager)),
            ("Persistencia", lambda: self.open_placeholder("Persistencia")),
            ("Reportes", lambda: self.open_placeholder("Reportes")),
        ]

        for label, command in actions:
            ttk.Button(self, text=label, command=command, style="Sidebar.TButton").pack(fill="x", padx=20, pady=4)

    def _load_state(self):
        self.manager.faculties = LinkedList(load_faculties())
        self.manager.programs = LinkedList(load_programs())
        self.manager.courses = LinkedList(load_courses())
        self.manager.students = LinkedList(load_students())
        self.manager.professors = LinkedList(load_professors())
        self.manager.administrative_staff = LinkedList(load_administrative_staff())
        self.manager.enrollments = LinkedList(load_enrollments())
        payroll_records = load_payroll()
        if payroll_records:
            self.manager.payroll = payroll_records[0]
        else:
            self.manager.payroll = None

    def _save_state(self):
        save_faculties(self.manager.faculties)
        save_programs(self.manager.programs)
        save_courses(self.manager.courses)
        save_students(self.manager.students)
        save_professors(self.manager.professors)
        save_administrative_staff(self.manager.administrative_staff)
        save_enrollments(self.manager.enrollments)
        if self.manager.payroll is not None:
            save_payroll([self.manager.payroll])

    def open_placeholder(self, title):
        window = tk.Toplevel(self)
        window.title(title)
        window.geometry("500x240")
        ttk.Label(window, text=f"{title}\n\nSección disponible para ampliación del módulo.", font=("Segoe UI", 12), justify="center").pack(expand=True, padx=20, pady=20)
        return window


def run():
    window = MainWindow()
    window.mainloop()
