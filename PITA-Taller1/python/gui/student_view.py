import tkinter as tk


class StudentView(tk.Toplevel):
    """Ventana en blanco para la gestión de estudiantes."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Students")
        self.geometry("500x350")
