import tkinter as tk

from .administrative_view import AdministrativeView
from .course_view import CourseView
from .faculty_view import FacultyView
from .payroll_view import PayrollView
from .professor_view import ProfessorView
from .program_view import ProgramView
from .student_view import StudentView


class MainWindow(tk.Tk):
    """Ventana principal con la navegación básica del sistema."""

    def __init__(self):
        super().__init__()
        self.title("PITA")
        self.geometry("400x450")
        self.resizable(False, False)
        self._create_navigation_buttons()

    def _create_navigation_buttons(self):
        # Cada botón abre una ventana independiente para la entidad seleccionada.
        views = (
            ("Faculties", FacultyView),
            ("Programs", ProgramView),
            ("Courses", CourseView),
            ("Students", StudentView),
            ("Professors", ProfessorView),
            ("Administrative Staff", AdministrativeView),
            ("Payroll", PayrollView),
        )

        for title, view_class in views:
            button = tk.Button(
                self,
                text=title,
                command=lambda selected_view=view_class: selected_view(self),
                width=24,
            )
            button.pack(pady=6)


def run():
    """Inicia la aplicación gráfica."""
    window = MainWindow()
    window.mainloop()
