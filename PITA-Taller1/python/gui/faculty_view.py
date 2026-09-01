import tkinter as tk


class FacultyView(tk.Toplevel):
    """Ventana en blanco para la gestión de facultades."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Faculties")
        self.geometry("500x350")
