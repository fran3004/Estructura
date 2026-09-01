"""Punto de entrada de la versión en Python de PITA."""

from gui.main_window import run
from persistence.file_manager import ask_load_existing_data


if __name__ == "__main__":
	ask_load_existing_data()
	run()
