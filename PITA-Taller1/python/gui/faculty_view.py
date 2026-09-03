import tkinter as tk
from tkinter import ttk

from models.faculty import Faculty
from persistence.file_manager import save_faculties
from .theme import THEME, apply_theme


class FacultyView(tk.Toplevel):
    """Gestión de facultades."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Facultades")
        self.geometry("920x560")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Facultades", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos de la facultad", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "faculty_id": tk.StringVar(),
            "name": tk.StringVar(),
            "dean": tk.StringVar(),
            "creation_date": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "faculty_id", "entry"),
            ("Nombre", "name", "entry"),
            ("Decano", "dean", "entry"),
            ("Fecha de creación", "creation_date", "entry"),
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
        ttk.Button(actions, text="Buscar", command=self.search, style="Secondary.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Guardar", command=self.save, style="Primary.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Actualizar", command=self.update, style="Secondary.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Desactivar", command=self.deactivate, style="Danger.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(actions, text="Reactivar", command=self.reactivate, style="Secondary.TButton").pack(side="left")

        self.status = tk.StringVar(value="Listo para gestionar facultades.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado de facultades", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))

        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Decano", "Fecha de creación", "Estado"), show="headings")
        for column in ("ID", "Nombre", "Decano", "Fecha de creación", "Estado"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=150, anchor="w")
        self.tree.pack(fill="both", expand=True)
        self.tree.bind("<<TreeviewSelect>>", self._tree_select)

    def _save_state(self):
        save_faculties(self.manager.faculties)

    def _tree_select(self, _event=None):
        selected = self.tree.selection()
        if not selected:
            return
        item = self.tree.item(selected[0], "values")
        self.vars["faculty_id"].set(item[0])
        self.vars["name"].set(item[1])
        self.vars["dean"].set(item[2])
        self.vars["creation_date"].set(item[3])
        self.vars["active"].set(item[4] == "Activo")

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.faculties.head
        while current is not None:
            faculty = current.data
            self.tree.insert("", "end", values=(faculty.faculty_id, faculty.name, faculty.dean, faculty.creation_date, "Activo" if faculty.active else "Inactivo"))
            current = current.next

    def search(self):
        value = self.vars["name"].get().strip()
        faculty = self.manager.search_faculty(value)
        if faculty is None:
            self.status.set("No se encontró la facultad.")
            return
        self.vars["faculty_id"].set(str(faculty.faculty_id))
        self.vars["name"].set(faculty.name)
        self.vars["dean"].set(faculty.dean)
        self.vars["creation_date"].set(faculty.creation_date)
        self.vars["active"].set(faculty.active)
        self.status.set("Facultad localizada.")

    def save(self):
        try:
            faculty = Faculty(
                faculty_id=int(self.vars["faculty_id"].get() or 0),
                name=self.vars["name"].get(),
                dean=self.vars["dean"].get(),
                creation_date=self.vars["creation_date"].get(),
                active=self.vars["active"].get(),
            )
            if self.manager.create_faculty(faculty):
                self._save_state(); self.refresh_table(); self.status.set("Facultad creada correctamente.")
            else:
                self.status.set("La facultad ya existe o la información es inválida.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        faculty_id = self.vars["faculty_id"].get().strip()
        if not faculty_id:
            self.status.set("Debe ingresar un ID de facultad para actualizar.")
            return
        try:
            payload = {
                "name": self.vars["name"].get(),
                "dean": self.vars["dean"].get(),
                "creation_date": self.vars["creation_date"].get(),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_faculty(int(faculty_id), **payload):
                self._save_state(); self.refresh_table(); self.status.set("Facultad actualizada.")
            else:
                self.status.set("No se pudo actualizar la facultad.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        faculty_id = int(self.vars["faculty_id"].get() or 0)
        if faculty_id and self.manager.deactivate_faculty(faculty_id):
            self._save_state(); self.refresh_table(); self.status.set("Facultad desactivada.")
        else:
            self.status.set("No se pudo desactivar la facultad.")

    def reactivate(self):
        faculty_id = int(self.vars["faculty_id"].get() or 0)
        if faculty_id and self.manager.reactivate_faculty(faculty_id):
            self._save_state(); self.refresh_table(); self.status.set("Facultad reactivada.")
        else:
            self.status.set("No se pudo reactivar la facultad.")
