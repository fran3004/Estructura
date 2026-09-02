import tkinter as tk
from tkinter import ttk

from models.administrative import Administrative
from persistence.file_manager import save_administrative_staff
from .theme import THEME, apply_theme


class AdministrativeView(tk.Toplevel):
    """Gestión del personal administrativo."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Personal administrativo")
        self.geometry("1100x620")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Personal administrativo", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos del personal", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "administrative_id": tk.StringVar(),
            "full_name": tk.StringVar(),
            "document_type": tk.StringVar(),
            "document_number": tk.StringVar(),
            "email": tk.StringVar(),
            "phone": tk.StringVar(),
            "position": tk.StringVar(),
            "category": tk.StringVar(),
            "employment_type": tk.StringVar(),
            "base_salary": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "administrative_id", "entry"),
            ("Nombre completo", "full_name", "entry"),
            ("Tipo documento", "document_type", "entry"),
            ("Número", "document_number", "entry"),
            ("Correo", "email", "entry"),
            ("Teléfono", "phone", "entry"),
            ("Cargo", "position", "entry"),
            ("Categoría", "category", "entry"),
            ("Tipo de contratación", "employment_type", "entry"),
            ("Salario base", "base_salary", "entry"),
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

        self.status = tk.StringVar(value="Listo para gestionar personal administrativo.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado del personal administrativo", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Cargo", "Categoría", "Tipo", "Salario base", "Estado"), show="headings")
        for column in ("ID", "Nombre", "Cargo", "Categoría", "Tipo", "Salario base", "Estado"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=140, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        save_administrative_staff(self.manager.administrative_staff)

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.administrative_staff.head
        while current is not None:
            person = current.data
            self.tree.insert("", "end", values=(person.administrative_id, person.full_name, person.position, person.category, person.employment_type, round(float(person.base_salary), 2), "Activo" if person.active else "Inactivo"))
            current = current.next

    def save(self):
        try:
            person = Administrative(
                administrative_id=int(self.vars["administrative_id"].get() or 0),
                full_name=self.vars["full_name"].get(),
                document_type=self.vars["document_type"].get(),
                document_number=self.vars["document_number"].get(),
                email=self.vars["email"].get(),
                phone=self.vars["phone"].get(),
                position=self.vars["position"].get(),
                category=self.vars["category"].get(),
                employment_type=self.vars["employment_type"].get(),
                base_salary=float(self.vars["base_salary"].get() or 0.0),
                active=self.vars["active"].get(),
            )
            if self.manager.create_administrative(person):
                self._save_state(); self.refresh_table(); self.status.set("Registro guardado.")
            else:
                self.status.set("No se pudo guardar el registro.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        administrative_id = int(self.vars["administrative_id"].get() or 0)
        if not administrative_id:
            self.status.set("Debe indicar el ID del registro.")
            return
        try:
            payload = {
                "full_name": self.vars["full_name"].get(),
                "document_type": self.vars["document_type"].get(),
                "document_number": self.vars["document_number"].get(),
                "email": self.vars["email"].get(),
                "phone": self.vars["phone"].get(),
                "position": self.vars["position"].get(),
                "category": self.vars["category"].get(),
                "employment_type": self.vars["employment_type"].get(),
                "base_salary": float(self.vars["base_salary"].get() or 0.0),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_administrative(administrative_id, **payload):
                self._save_state(); self.refresh_table(); self.status.set("Registro actualizado.")
            else:
                self.status.set("No se pudo actualizar el registro.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        administrative_id = int(self.vars["administrative_id"].get() or 0)
        if administrative_id and self.manager.deactivate_administrative(administrative_id):
            self._save_state(); self.refresh_table(); self.status.set("Registro desactivado.")
        else:
            self.status.set("No se pudo desactivar el registro.")
