# Spotifind
## Descripcion
Este programa consiste en un modulo para leer y gestionar un dataset de canciones en un archivo csv, cumple con distintas funcionalidades a traves de una serie de 7 opciones para el usuario, la primera de ellas es cargar las canciones, sigue  la busqueda de canciones en estas segun por genero, artista o tempo, tambien cuenta con la funcionalidad de crear una lista de reproduccion nombrada por el ususario, a la cual se le suman dos opciones mas para agregar canciones a la lista y la otra para mostrar las canciones que conforman la lista. 

## Requisitos Previos
- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Clonar el repositorio desde GitHub:**
    - Abre una terminal o línea de comandos.
    - Clona el repositorio usando el siguiente comando:
   ```bash
    git clone https://github.com/usuario/nombre-repositorio.git
   ```

2. **Abrir el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde clonaste el repositorio.

3. **Compilar el código**
    - Abre el archivo principal (por ejemplo, `Tarea2.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
    
    ```bash
    gcc -o Tarea2 Tarea2.c tdas/list.c tdas/map.c tdas/extra.c
    ```

4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
    
    ```bash
    ./tarea2
    ```

   git clone https://github.com/VicenteGonzalez14/Sistema-gesti-n-tickets.git

## FUNCIONALIDADES
1. Carga un conjunto de canciones desde un archivo CSV (song_dataset_.csv) y las almacena en mapas según diferentes criterios: ID, Tempo y Artista.
2. Permite buscar canciones a través de su ID en el mapa, mostrando los detalles completos de la canción si se encuentra.
3. Permite realizar una búsqueda por el tempo de las canciones, filtrando por un rango de tempo definido por el usuario (por ejemplo, lento, moderado, rápido), luego muestra las canciones que caen dentro del rango de tempo especificado.}
4. Permite realizar una búsqueda de canciones por el nombre del artista, muestra todas las canciones del artista seleccionado, presentando información detallada.
5. Permite crear una nueva lista de reproducción, asignándole un nombre que el usuario proporciona, verifica si ya existe una lista con el mismo nombre, y si es así, evita duplicados, la lista se inicializa vacia.
6. Las canciones pueden ser agregadas a las listas de reproducción, verificando que el ID de la canción exista antes de agregarla a la lista seleccionada, Las canciones se insertan en las listas de reproducción correspondientes.}
7. Muestra todas las canciones de una lista de reproducción específica, presentando información detallada de cada una (ID, título, artista, álbum, género y tempo).

## Problemas conocidos:
1. El programa funciona correctamente, pero se podria considerar la limitacion que tiene al formato de archivo csv, con la misma estructura para que no falle la funcion para leer el dataset de canciones.

## Ejemplo de uso: 

### Opción 1: El usuario carga un archivo CSV que contiene las canciones, y el programa procesa e ingresa los datos en los mapas correspondientes (por ID, tempo y artista).
1)Cargar canciones.

    Cargar canciones
  
    Ingrese su opción: 1
    Cargando canciones desde CSV...
    Canción registrada: ID 1 - Song Title
    Canción registrada: ID 2 - Another Song
    ...
    Canciones cargadas exitosamente desde el archivo CSV.
    Presione cualquier tecla para continuar...

### Opción 2: El usuario ingresa el ID de una canción, y el programa muestra la información de la canción si se encuentra en el mapa.
2)Buscar por ID

     Ingrese su opción: 2  
    Ingrese el ID de la canción a buscar: 1  
    ID: 1  
    Título canción: Song Title  
    Artista: Artist Name  
    Álbum: Album Name  
    Género: Genre  
    Tempo: 120.0  
    -------------------------------  
    Presione cualquier tecla para continuar...

### Opción 3: El usuario ingresa el nombre de una nueva lista de reproducción, y el programa crea una lista vacía para agregar canciones posteriormente.
3)Buscar por artista

    Ingrese su opción: 4  
    Ingrese el nombre del artista a buscar: Artist Name  
    ID: 1  
    Título canción: Song Title  
    Artista: Artist Name  
    Álbum: Album Name  
    Género: Genre  
    Tempo: 120.0  
    -------------------------------  
    Presione cualquier tecla para continuar...

### Opción 4: El usuario ingresa un rango de tempo (mínimo y máximo), y el programa muestra todas las canciones que caen dentro de ese rango.
3)Buscar por tempo

      Ingrese su opción: 3  
    Ingrese el tempo mínimo: 100.0  
    Ingrese el tempo máximo: 150.0  
    ID: 1  
    Título canción: Song Title  
    Artista: Artist Name  
    Álbum: Album Name  
    Género: Genre  
    Tempo: 120.0  
    -------------------------------  
    Presione cualquier tecla para continuar...

### Opción 5: El usuario ingresa el nombre de una nueva lista de reproducción, y el programa crea una lista vacía para agregar canciones posteriormente.
5)Crear lista de reproducción

    Ingrese su opción: 5  
    Ingrese el nombre de la lista de reproducción: Mi lista  
    Lista de reproducción 'Mi lista' creada exitosamente.  
    Presione cualquier tecla para continuar...

### Opción 6: El usuario ingresa el nombre de una lista de reproducción existente y el ID de una canción para agregarla a la lista.
6)Agregar canción a lista de reproducción

    Ingrese su opción: 6  
    Ingrese el nombre de la lista de reproducción: Mi lista  
    Ingrese el ID de la canción a agregar: 1  
    Canción 'Song Title' agregada a la lista 'Mi lista'.  
    Presione cualquier tecla para continuar...
### Opción 7: El usuario ingresa el nombre de una lista de reproducción, y el programa muestra todas las canciones de esa lista.
7)Mostrar canciones de una lista de reproducción

    Ingrese su opción: 7  
    Ingrese el nombre de la lista de reproducción: Mi lista  
    Canciones en la lista de reproducción 'Mi lista':  
    ID: 1  
    Título canción: Song Title  
    Artista: Artist Name  
    Álbum: Album Name  
    Género: Genre  
    Tempo: 120.0  
    -------------------------------  
    Presione cualquier tecla para continuar...  
### Opción 8: El usuario elige esta opción para salir del programa.
8)Salir

    Ingrese su opción: 8  
    Saliendo del sistema de búsqueda de canciones...  

## Contribuciones
### Mateo Moncada:
1. Desarrollo funciones para cargar canciones y guardarlas en mapas.
2. Realizo pruebas en el programa para verificar el correcto funcionamiento de este. 
3. Auto-evaluación: 3 (Aporte excelente).
### Vicente Gonzalez: 
1. Desarrollo funciones de busqueda de cancinones a traves de mapas.
2. Desarrollo funciones para implementar la lista de reproducción.
3. Auto-evaluación: 3 (Aporte excelente).

























