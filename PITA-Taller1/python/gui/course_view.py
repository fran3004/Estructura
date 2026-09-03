import tkinter as tk
from tkinter import ttk

from models.course import Course
from persistence.file_manager import save_courses
from .theme import THEME, apply_theme


class CourseView(tk.Toplevel):
    """Gestión de cursos."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Cursos")
        self.geometry("1050x620")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Cursos", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos del curso", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "course_id": tk.StringVar(),
            "name": tk.StringVar(),
            "program_id": tk.StringVar(),
            "credits": tk.StringVar(),
            "curriculum_semester": tk.StringVar(),
            "assigned_professor_id": tk.StringVar(),
            "max_capacity": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "course_id", "entry"),
            ("Nombre", "name", "entry"),
            ("ID programa", "program_id", "entry"),
            ("Créditos", "credits", "entry"),
            ("Semestre", "curriculum_semester", "entry"),
            ("Docente asignado", "assigned_professor_id", "entry"),
            ("Capacidad máxima", "max_capacity", "entry"),
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

        self.status = tk.StringVar(value="Listo para gestionar cursos.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado de cursos", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Programa", "Créditos", "Semestre", "Docente", "Capacidad", "Estado"), show="headings")
        for column in ("ID", "Nombre", "Programa", "Créditos", "Semestre", "Docente", "Capacidad", "Estado"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=110, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        save_courses(self.manager.courses)

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.courses.head
        while current is not None:
            course = current.data
            self.tree.insert("", "end", values=(course.course_id, course.name, course.program_id, course.credits, course.curriculum_semester, course.assigned_professor_id, course.max_capacity, "Activo" if course.active else "Inactivo"))
            current = current.next

    def save(self):
        try:
            course = Course(
                course_id=int(self.vars["course_id"].get() or 0),
                name=self.vars["name"].get(),
                program_id=int(self.vars["program_id"].get() or 0),
                credits=int(self.vars["credits"].get() or 0),
                curriculum_semester=int(self.vars["curriculum_semester"].get() or 0),
                assigned_professor_id=int(self.vars["assigned_professor_id"].get() or 0),
                max_capacity=int(self.vars["max_capacity"].get() or 0),
                active=self.vars["active"].get(),
            )
            if self.manager.create_course(course):
                self._save_state(); self.refresh_table(); self.status.set("Curso creado.")
            else:
                self.status.set("No se pudo guardar el curso.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        course_id = int(self.vars["course_id"].get() or 0)
        if not course_id:
            self.status.set("Debe indicar el ID del curso.")
            return
        try:
            payload = {
                "name": self.vars["name"].get(),
                "program_id": int(self.vars["program_id"].get() or 0),
                "credits": int(self.vars["credits"].get() or 0),
                "curriculum_semester": int(self.vars["curriculum_semester"].get() or 0),
                "assigned_professor_id": int(self.vars["assigned_professor_id"].get() or 0),
                "max_capacity": int(self.vars["max_capacity"].get() or 0),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_course(course_id, **payload):
                self._save_state(); self.refresh_table(); self.status.set("Curso actualizado.")
            else:
                self.status.set("No se pudo actualizar el curso.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        course_id = int(self.vars["course_id"].get() or 0)
        if course_id and self.manager.deactivate_course(course_id):
            self._save_state(); self.refresh_table(); self.status.set("Curso desactivado.")
        else:
            self.status.set("No se pudo desactivar el curso.")
