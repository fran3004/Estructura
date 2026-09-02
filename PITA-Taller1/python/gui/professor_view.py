import tkinter as tk
from tkinter import ttk

from models.professor import Professor
from persistence.file_manager import save_professors
from .theme import THEME, apply_theme


class ProfessorView(tk.Toplevel):
    """Gestión de profesores."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Profesores")
        self.geometry("1120x660")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Profesores", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos del profesor", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "professor_id": tk.StringVar(),
            "full_name": tk.StringVar(),
            "document_type": tk.StringVar(),
            "document_number": tk.StringVar(),
            "email": tk.StringVar(),
            "phone": tk.StringVar(),
            "faculty_id": tk.StringVar(),
            "employment_type": tk.StringVar(),
            "academic_title": tk.StringVar(),
            "category_rank": tk.StringVar(),
            "base_monthly_salary": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "professor_id", "entry"),
            ("Nombre completo", "full_name", "entry"),
            ("Tipo documento", "document_type", "entry"),
            ("Número", "document_number", "entry"),
            ("Correo", "email", "entry"),
            ("Teléfono", "phone", "entry"),
            ("ID facultad", "faculty_id", "entry"),
            ("Tipo de contratación", "employment_type", "entry"),
            ("Título", "academic_title", "entry"),
            ("Rango", "category_rank", "entry"),
            ("Salario base", "base_monthly_salary", "entry"),
            ("Activo", "active", "check"),
        ]
        row = 0
        for label, key, kind in fields:
            ttk.Label(form, text=label).grid(row=row, column=0, sticky="w", padx=(0, 10), pady=6)
            if kind == "check":
                ttk.Checkbutton(form, variable=self.vars[key]).grid(row=row, column=1, sticky="w", pady=6)
            else:
                ttk.Entry(form, textvariable=self.vars[key], width=32).grid(row=row, column=1, sticky="w", pady=6)
            row += 1

        actions = ttk.Frame(form)
        actions.grid(row=row, column=0, columnspan=2, sticky="w", pady=(12, 0))
        ttk.Button(actions, text="Guardar", command=self.save, style="Primary.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Actualizar", command=self.update, style="Secondary.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Desactivar", command=self.deactivate, style="Danger.TButton").pack(side="left")

        self.status = tk.StringVar(value="Listo para gestionar profesores.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado de profesores", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Facultad", "Título", "Tipo", "Salario", "Estado"), show="headings")
        for column in ("ID", "Nombre", "Facultad", "Título", "Tipo", "Salario", "Estado"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=145, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        save_professors(self.manager.professors)

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.professors.head
        while current is not None:
            professor = current.data
            self.tree.insert("", "end", values=(professor.professor_id, professor.full_name, professor.faculty_id, professor.academic_title, professor.employment_type, round(float(professor.base_monthly_salary), 2), "Activo" if professor.active else "Inactivo"))
            current = current.next

    def save(self):
        try:
            professor = Professor(
                professor_id=int(self.vars["professor_id"].get() or 0),
                full_name=self.vars["full_name"].get(),
                document_type=self.vars["document_type"].get(),
                document_number=self.vars["document_number"].get(),
                email=self.vars["email"].get(),
                phone=self.vars["phone"].get(),
                faculty_id=int(self.vars["faculty_id"].get() or 0),
                employment_type=self.vars["employment_type"].get(),
                academic_title=self.vars["academic_title"].get(),
                category_rank=self.vars["category_rank"].get(),
                base_monthly_salary=float(self.vars["base_monthly_salary"].get() or 0.0),
                active=self.vars["active"].get(),
            )
            if self.manager.create_professor(professor):
                self._save_state(); self.refresh_table(); self.status.set("Profesor guardado.")
            else:
                self.status.set("No se pudo guardar el profesor.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        professor_id = int(self.vars["professor_id"].get() or 0)
        if not professor_id:
            self.status.set("Debe indicar el ID del profesor.")
            return
        try:
            payload = {
                "full_name": self.vars["full_name"].get(),
                "document_type": self.vars["document_type"].get(),
                "document_number": self.vars["document_number"].get(),
                "email": self.vars["email"].get(),
                "phone": self.vars["phone"].get(),
                "faculty_id": int(self.vars["faculty_id"].get() or 0),
                "employment_type": self.vars["employment_type"].get(),
                "academic_title": self.vars["academic_title"].get(),
                "category_rank": self.vars["category_rank"].get(),
                "base_monthly_salary": float(self.vars["base_monthly_salary"].get() or 0.0),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_professor(professor_id, **payload):
                self._save_state(); self.refresh_table(); self.status.set("Profesor actualizado.")
            else:
                self.status.set("No se pudo actualizar el profesor.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        professor_id = int(self.vars["professor_id"].get() or 0)
        if professor_id and self.manager.deactivate_professor(professor_id):
            self._save_state(); self.refresh_table(); self.status.set("Profesor desactivado.")
        else:
            self.status.set("No se pudo desactivar el profesor.")
