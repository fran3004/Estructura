import tkinter as tk


class CourseView(tk.Toplevel):
    """Ventana en blanco para la gestión de cursos."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Courses")
        self.geometry("500x350")
