import tkinter as tk


class PayrollView(tk.Toplevel):
    """Ventana en blanco para la gestión de nómina."""

    def __init__(self, parent):
        super().__init__(parent)
        self.title("Payroll")
        self.geometry("500x350")
