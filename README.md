# PITA - Programa Integrado de Transacciones Académicas

## Descripción

PITA es un proyecto universitario de Estructura de Datos para gestionar una universidad de forma integrada. El sistema contempla entidades como facultades, programas académicos, cursos, estudiantes, profesores, administrativos y nómina, con el objetivo de organizar y administrar información académica y operativa.

Este repositorio está estructurado para desarrollar la misma solución en dos lenguajes:

- C++ para la versión de lógica y estructuras de datos
- Python para la versión con modelos y posible interfaz gráfica

## Estructura general

- `cpp/`: implementación en C++
- `python/`: implementación en Python
- `data/`: archivos de datos o ejemplos de persistencia
- `docs/`: documentación adicional del proyecto

## Cómo ejecutar

### Versión en C++

1. Abrir la carpeta `cpp/`.
2. Configurar el proyecto con CMake.
3. Compilar desde la terminal:

```bash
cmake -S . -B build
cmake --build build
./build/PITA
```

> Esta versión aún no contiene lógica funcional; solo se prepara la estructura base del proyecto.

### Versión en Python

1. Entrar a la carpeta `python/`.
2. Crear un entorno virtual si se desea.
3. Instalar dependencias:

```bash
pip install -r requirements.txt
```

4. Ejecutar la aplicación principal:

```bash
python main.py
```

> La versión en Python aún está en preparación y no implementa funcionalidades reales.

## Estado actual

Este repositorio se encuentra en la fase inicial de creación de la estructura base del proyecto. Aún no se ha desarrollado ninguna funcionalidad ni lógica del sistema.
