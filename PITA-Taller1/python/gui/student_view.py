import tkinter as tk
from tkinter import ttk

from models.student import Student
from persistence.file_manager import save_students
from .theme import THEME, apply_theme


class StudentView(tk.Toplevel):
    """Gestión de estudiantes."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Estudiantes")
        self.geometry("1180x660")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Estudiantes", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos del estudiante", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "student_id": tk.StringVar(),
            "full_name": tk.StringVar(),
            "document_type": tk.StringVar(),
            "document_number": tk.StringVar(),
            "birth_date": tk.StringVar(),
            "email": tk.StringVar(),
            "phone": tk.StringVar(),
            "program_id": tk.StringVar(),
            "current_semester": tk.StringVar(),
            "status": tk.StringVar(value="Activo"),
            "cumulative_average": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "student_id", "entry"),
            ("Nombre completo", "full_name", "entry"),
            ("Tipo de documento", "document_type", "entry"),
            ("Número", "document_number", "entry"),
            ("Fecha de nacimiento", "birth_date", "entry"),
            ("Correo", "email", "entry"),
            ("Teléfono", "phone", "entry"),
            ("ID programa", "program_id", "entry"),
            ("Semestre actual", "current_semester", "entry"),
            ("Estado", "status", "entry"),
            ("Promedio acumulado", "cumulative_average", "entry"),
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

        self.status = tk.StringVar(value="Listo para gestionar estudiantes.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado de estudiantes", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Programa", "Semestre", "Estado", "Promedio"), show="headings")
        for column in ("ID", "Nombre", "Programa", "Semestre", "Estado", "Promedio"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=160, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        save_students(self.manager.students)

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.students.head
        while current is not None:
            student = current.data
            self.tree.insert("", "end", values=(student.student_id, student.full_name, student.program_id, student.current_semester, student.status, round(float(student.cumulative_average), 2)))
            current = current.next

    def save(self):
        try:
            student = Student(
                student_id=int(self.vars["student_id"].get() or 0),
                full_name=self.vars["full_name"].get(),
                document_type=self.vars["document_type"].get(),
                document_number=self.vars["document_number"].get(),
                birth_date=self.vars["birth_date"].get(),
                email=self.vars["email"].get(),
                phone=self.vars["phone"].get(),
                program_id=int(self.vars["program_id"].get() or 0),
                current_semester=int(self.vars["current_semester"].get() or 0),
                status=self.vars["status"].get(),
                cumulative_average=float(self.vars["cumulative_average"].get() or 0.0),
                active=self.vars["active"].get(),
            )
            if self.manager.create_student(student):
                self._save_state(); self.refresh_table(); self.status.set("Estudiante creado.")
            else:
                self.status.set("No se pudo guardar el estudiante.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        student_id = int(self.vars["student_id"].get() or 0)
        if not student_id:
            self.status.set("Debe indicar el ID del estudiante.")
            return
        try:
            payload = {
                "full_name": self.vars["full_name"].get(),
                "document_type": self.vars["document_type"].get(),
                "document_number": self.vars["document_number"].get(),
                "birth_date": self.vars["birth_date"].get(),
                "email": self.vars["email"].get(),
                "phone": self.vars["phone"].get(),
                "program_id": int(self.vars["program_id"].get() or 0),
                "current_semester": int(self.vars["current_semester"].get() or 0),
                "status": self.vars["status"].get(),
                "cumulative_average": float(self.vars["cumulative_average"].get() or 0.0),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_student(student_id, **payload):
                self._save_state(); self.refresh_table(); self.status.set("Estudiante actualizado.")
            else:
                self.status.set("No se pudo actualizar el estudiante.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        student_id = int(self.vars["student_id"].get() or 0)
        if student_id and self.manager.deactivate_student(student_id):
            self._save_state(); self.refresh_table(); self.status.set("Estudiante desactivado.")
        else:
            self.status.set("No se pudo desactivar el estudiante.")
