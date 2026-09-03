import tkinter as tk
from tkinter import ttk

from models.program import Program
from persistence.file_manager import save_programs
from .theme import THEME, apply_theme


class ProgramView(tk.Toplevel):
    """Gestión de programas académicos."""

    def __init__(self, parent, manager):
        super().__init__(parent)
        self.title("Programas")
        self.geometry("980x560")
        self.configure(bg=THEME["background"])
        apply_theme(self)
        self.manager = manager
        self._build_ui()
        self.refresh_table()

    def _build_ui(self):
        ttk.Label(self, text="Programas", style="Title.TLabel").pack(anchor="w", padx=16, pady=(16, 12))

        form = ttk.LabelFrame(self, text="Datos del programa", padding=12)
        form.pack(fill="x", padx=16, pady=(0, 12))

        self.vars = {
            "program_id": tk.StringVar(),
            "name": tk.StringVar(),
            "faculty_id": tk.StringVar(),
            "program_director": tk.StringVar(),
            "level": tk.StringVar(),
            "modality": tk.StringVar(),
            "active": tk.BooleanVar(value=True),
        }

        fields = [
            ("ID", "program_id", "entry"),
            ("Nombre", "name", "entry"),
            ("ID facultad", "faculty_id", "entry"),
            ("Director", "program_director", "entry"),
            ("Nivel", "level", "entry"),
            ("Modalidad", "modality", "entry"),
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

        self.status = tk.StringVar(value="Listo para gestionar programas.")
        ttk.Label(form, textvariable=self.status, foreground=THEME["text_soft"]).grid(row=row + 1, column=0, columnspan=2, sticky="w", pady=(12, 0))

        table_frame = ttk.LabelFrame(self, text="Listado de programas", padding=10)
        table_frame.pack(fill="both", expand=True, padx=16, pady=(0, 16))
        self.tree = ttk.Treeview(table_frame, columns=("ID", "Nombre", "Facultad", "Director", "Nivel", "Modalidad", "Estado"), show="headings")
        for column in ("ID", "Nombre", "Facultad", "Director", "Nivel", "Modalidad", "Estado"):
            self.tree.heading(column, text=column)
            self.tree.column(column, width=130, anchor="w")
        self.tree.pack(fill="both", expand=True)

    def _save_state(self):
        save_programs(self.manager.programs)

    def refresh_table(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        current = self.manager.programs.head
        while current is not None:
            program = current.data
            self.tree.insert("", "end", values=(program.program_id, program.name, program.faculty_id, program.program_director, program.level, program.modality, "Activo" if program.active else "Inactivo"))
            current = current.next

    def save(self):
        try:
            program = Program(
                program_id=int(self.vars["program_id"].get() or 0),
                name=self.vars["name"].get(),
                faculty_id=int(self.vars["faculty_id"].get() or 0),
                program_director=self.vars["program_director"].get(),
                level=self.vars["level"].get(),
                modality=self.vars["modality"].get(),
                active=self.vars["active"].get(),
            )
            if self.manager.create_program(program):
                self._save_state(); self.refresh_table(); self.status.set("Programa guardado.")
            else:
                self.status.set("No se pudo guardar el programa.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def update(self):
        program_id = int(self.vars["program_id"].get() or 0)
        if not program_id:
            self.status.set("Debe indicar el ID del programa.")
            return
        try:
            payload = {
                "name": self.vars["name"].get(),
                "faculty_id": int(self.vars["faculty_id"].get() or 0),
                "program_director": self.vars["program_director"].get(),
                "level": self.vars["level"].get(),
                "modality": self.vars["modality"].get(),
                "active": self.vars["active"].get(),
            }
            if self.manager.update_program(program_id, **payload):
                self._save_state(); self.refresh_table(); self.status.set("Programa actualizado.")
            else:
                self.status.set("No se pudo actualizar el programa.")
        except Exception as exc:  # noqa: BLE001
            self.status.set(f"Error: {exc}")

    def deactivate(self):
        program_id = int(self.vars["program_id"].get() or 0)
        if program_id and self.manager.deactivate_program(program_id):
            self._save_state(); self.refresh_table(); self.status.set("Programa desactivado.")
        else:
            self.status.set("No se pudo desactivar el programa.")
