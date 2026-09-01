import tkinter as tk


class ProgramView(tk.Toplevel):
    """Ventana en blanco para la gestión de programas."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Programs")
        self.geometry("500x350")
