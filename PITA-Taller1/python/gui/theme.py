"""Theme configuration for the UPC PITA academic management interface."""

import tkinter as tk
from tkinter import ttk

THEME = {
    "primary_green": "#1F7A4D",
    "primary_green_dark": "#15573A",
    "secondary_green": "#CFE9DE",
    "background": "#F3F5F4",
    "panel": "#FFFFFF",
    "muted": "#DADFE3",
    "text": "#1B1F1D",
    "text_soft": "#5B6862",
    "danger": "#C63A2E",
    "warning": "#D98B1F",
    "success": "#2B8C5A",
    "shadow": "#E2E8E5",
}

FONT_FAMILY = "Segoe UI"


def apply_theme(root):
    """Applies the central UPC-inspired visual theme to the Tk root."""
    if root is None:
        return

    style = ttk.Style(root)
    try:
        style.theme_use("clam")
    except tk.TclError:
        pass

    style.configure("Main.TFrame", background=THEME["background"])
    style.configure("Sidebar.TFrame", background=THEME["primary_green_dark"])
    style.configure("Panel.TFrame", background=THEME["panel"])
    style.configure("Title.TLabel", background=THEME["panel"], foreground=THEME["primary_green_dark"], font=(FONT_FAMILY, 18, "bold"))
    style.configure("Section.TLabel", background=THEME["panel"], foreground=THEME["text"], font=(FONT_FAMILY, 11, "bold"))
    style.configure("Metric.TLabel", background=THEME["panel"], foreground=THEME["text"], font=(FONT_FAMILY, 10, "bold"))
    style.configure("Sidebar.TButton", background=THEME["primary_green_dark"], foreground="white", font=(FONT_FAMILY, 10, "bold"))
    style.map("Sidebar.TButton", background=[("active", THEME["primary_green"])])
    style.configure("Primary.TButton", background=THEME["primary_green"], foreground="white", font=(FONT_FAMILY, 10, "bold"))
    style.map("Primary.TButton", background=[("active", THEME["primary_green_dark"])])
    style.configure("Secondary.TButton", background=THEME["secondary_green"], foreground=THEME["primary_green_dark"], font=(FONT_FAMILY, 10, "bold"))
    style.configure("Danger.TButton", background=THEME["danger"], foreground="white", font=(FONT_FAMILY, 10, "bold"))
    style.configure("Treeview", background=THEME["panel"], foreground=THEME["text"], fieldbackground=THEME["panel"], rowheight=28)
    style.configure("Treeview.Heading", background=THEME["primary_green"], foreground="white", font=(FONT_FAMILY, 10, "bold"))
    style.map("Treeview", background=[("selected", THEME["secondary_green"])])
    style.configure("TEntry", padding=6)
    style.configure("TCombobox", padding=6)
    style.configure("TNotebook", background=THEME["background"])
    style.configure("TLabel", foreground=THEME["text"])
    style.configure("TFrame", background=THEME["background"])
