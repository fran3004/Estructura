import tkinter as tk
from tkinter import ttk

from models.payroll import Payroll
from persistence.file_manager import save_payroll
from .theme import THEME, apply_theme


class PayrollView(tk.Toplevel):
    """Gestión de nómina."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Nómina")
        self.geometry("830x520")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Nómina", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Cálculo y desglose", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))
        self.vars = {"employee_id": tk.StringVar(), "employee_type": tk.StringVar(value="profesor")}

        ttk.Label(form, text="ID empleado").grid(row=0, column=0, sticky="w", padx=(0, 10), pady=6)
        ttk.Entry(form, textvariable=self.vars["employee_id"], width=20).grid(row=0, column=1, sticky="w", pady=6)
        ttk.Label(form, text="Tipo").grid(row=1, column=0, sticky="w", padx=(0, 10), pady=6)
        ttk.Combobox(form, textvariable=self.vars["employee_type"], values=["profesor", "administrativo"], state="readonly", width=18).grid(row=1, column=1, sticky="w", pady=6)

        actions = ttk.Frame(form)
        actions.grid(row=2, column=0, columnspan=2, sticky="w", pady=(12, 0))
        ttk.Button(actions, text="Calcular nómina", command=self.calculate, style="Primary.TButton").pack(side="left", padx=(0, 8))

        self.status = tk.StringVar(value="Listo para calcular la nómina.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=3, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Resumen de nómina", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Tipo", "Base", "Deducciones", "Provisiones", "Neto"), show="headings")
        for column in ("ID", "Tipo", "Base", "Deducciones", "Provisiones", "Neto"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=130, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        if self.manager.payroll is not None:
            save_payroll([self.manager.payroll])

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        for professor in self.manager.professors:
            report = Payroll(description="Nómina").generate_payroll_report(professor)
            self.tree.insert("", "end", values=(professor.professor_id, "Profesor", round(float(report["base_salary"]), 2), round(float(report["deductions"]), 2), round(float(report["benefits"]), 2), round(float(report["net_salary"]), 2)))
        for employee in self.manager.administrative_staff:
            report = Payroll(description="Nómina").generate_payroll_report(employee)
            self.tree.insert("", "end", values=(employee.administrative_id, "Administrativo", round(float(report["base_salary"]), 2), round(float(report["deductions"]), 2), round(float(report["benefits"]), 2), round(float(report["net_salary"]), 2)))

    def calculate(self):
        employee_id = int(self.vars["employee_id"].get() or 0)
        employee_type = self.vars["employee_type"].get()
        if employee_type == "profesor":
            employee = self.manager.get_professor(employee_id)
        else:
            employee = self.manager.get_administrative(employee_id)
        if employee is None:
            self.status.set("No se encontró el empleado solicitado.")
            return
        report = Payroll(description="Nómina").generate_payroll_report(employee)
        self.manager.payroll = Payroll(description="Nómina")
        self._save_state()
        self.status.set(f"Empleado {employee_id}: base {report['base_salary']:.2f}, deducciones {report['deductions']:.2f}, provisiones {report['benefits']:.2f}, neto {report['net_salary']:.2f}")
        self.refresh_table()
