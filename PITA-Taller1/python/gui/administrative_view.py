import tkinter as tk


class AdministrativeView(tk.Toplevel):
    """Ventana en blanco para la gestión de administrativos."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Administrative Staff")
        self.geometry("500x350")
