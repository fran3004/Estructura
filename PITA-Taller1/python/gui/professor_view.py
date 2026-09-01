import tkinter as tk


class ProfessorView(tk.Toplevel):
    """Ventana en blanco para la gestión de profesores."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Professors")
        self.geometry("500x350")
