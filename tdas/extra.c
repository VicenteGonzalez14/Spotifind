#include "map.h"
#include "list.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char **leer_linea_csv(FILE *archivo, char separador) {
    static char linea[1024];
    if (fgets(linea, sizeof(linea), archivo) == NULL) return NULL;

    // Limpiar salto de línea al final
    linea[strcspn(linea, "\r\n")] = '\0';

    // Reservar memoria para los campos
    char **campos = malloc(sizeof(char *) * 100);
    int i = 0;

    char *campo = strtok(linea, &separador);
    while (campo != NULL && i < 100) {
        campos[i++] = strdup(campo);
        campo = strtok(NULL, &separador);
    }

    // Rellenar con NULL por seguridad
    while (i < 100) campos[i++] = NULL;

    return campos;
}


// Comparación de claves para el mapa de ID
int is_equal_int(void *key1, void *key2) {
    return *(int *)key1 == *(int *)key2;
}

// Comparación de claves para el mapa de tempo
int is_equal_float(void *key1, void *key2) {
    return *(float *)key1 == *(float *)key2;
}

// Comparación de claves para el mapa de artistas
int is_equal_str(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}

// Función para cargar canciones desde un archivo CSV
void leer_canciones(Song **songs, int *total_canciones, Map *mapaID, Map *mapaTempo, Map *mapaArtista) {
    printf("Cargando canciones desde CSV...\n");
    FILE *archivo = fopen("canciones.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');  // Leer encabezados

    int k = 0;
    *total_canciones = 1000;
    *songs = (Song *)malloc(sizeof(Song) * (*total_canciones));

    // 🔁 Este bloque es el que reemplazas:
    while ((campos = leer_linea_csv(archivo, ',')) != NULL && k < *total_canciones) {
        if (campos[0] && campos[2] && campos[3] && campos[4] && campos[18] && campos[20]) {
            (*songs)[k].id = atoi(campos[0]);
            strncpy((*songs)[k].track_name, campos[4], sizeof((*songs)[k].track_name));
            strncpy((*songs)[k].artist, campos[2], sizeof((*songs)[k].artist));
            strncpy((*songs)[k].album_name, campos[3], sizeof((*songs)[k].album_name));
            strncpy((*songs)[k].track_genre, campos[20], sizeof((*songs)[k].track_genre));
            (*songs)[k].tempo = atof(campos[18]);

            map_insert(mapaID, &(*songs)[k].id, &(*songs)[k]);
            map_insert(mapaTempo, &(*songs)[k].tempo, &(*songs)[k]);
            map_insert(mapaArtista, (*songs)[k].artist, &(*songs)[k]);

            printf("Canción registrada: ID %d - %s\n", (*songs)[k].id, (*songs)[k].track_name);
            k++;
        } else {
            printf("Línea malformada o incompleta en la canción %d. Saltando.\n", k + 1);
        }
    }

    fclose(archivo);
}

// Función para buscar canciones por ID
void buscar_por_id(Map *mapaID, int id_buscar) {
    MapPair *pair = map_search(mapaID, &id_buscar);
    if (pair != NULL) {
        Song *cancion = (Song *)pair->value;
        printf("ID: %d\n", cancion->id);
        printf("Título canción: %s\n", cancion->track_name);
        printf("Artista: %s\n", cancion->artist);
        printf("Álbum: %s\n", cancion->album_name);
        printf("Género: %s\n", cancion->track_genre);
        printf("Tempo: %.2f\n", cancion->tempo);
        printf("-------------------------------\n");
    } else {
        printf("No se encontró una canción con ID: %d\n", id_buscar);
    }
}

// Función para buscar canciones por tempo
void buscar_por_tempo(Map *mapaTempo, float tempo_min, float tempo_max) {
    MapPair *pair = map_first(mapaTempo);
    int canciones_encontradas = 0;

    while (pair != NULL) {
        Song *cancion = (Song *)pair->value;
        if (cancion->tempo >= tempo_min && cancion->tempo <= tempo_max) {
            canciones_encontradas++;
            printf("ID: %d\n", cancion->id);
            printf("Título canción: %s\n", cancion->track_name);
            printf("Artista: %s\n", cancion->artist);
            printf("Álbum: %s\n", cancion->album_name);
            printf("Género: %s\n", cancion->track_genre);
            printf("Tempo: %.2f\n", cancion->tempo);
            printf("-------------------------------\n");
        }
        pair = map_next(mapaTempo);  // Avanza al siguiente par
    }

    if (canciones_encontradas == 0) {
        printf("No se encontraron canciones en el rango de tempo %.2f - %.2f\n", tempo_min, tempo_max);
    }
}

// Función para buscar canciones por artista
void buscar_por_artista(Map *mapaArtista, const char *artista_buscar) {
    MapPair *pair = map_search(mapaArtista, (char *)artista_buscar);

    if (pair != NULL) {
        Song *cancion = (Song *)pair->value;
        printf("ID: %d\n", cancion->id);
        printf("Título canción: %s\n", cancion->track_name);
        printf("Artista: %s\n", cancion->artist);
        printf("Álbum: %s\n", cancion->album_name);
        printf("Género: %s\n", cancion->track_genre);
        printf("Tempo: %.2f\n", cancion->tempo);
        printf("-------------------------------\n");
    } else {
        printf("No se encontraron canciones para el artista: %s\n", artista_buscar);
    }
}

void crear_lista_reproduccion(Map* playlistMap) {
    char nombre_lista[100];
    printf("Ingrese el nombre de la lista de reproducción: ");
    fgets(nombre_lista, sizeof(nombre_lista), stdin);
    nombre_lista[strcspn(nombre_lista, "\n")] = 0;

    if (map_search(playlistMap, nombre_lista) != NULL) {
        printf("Ya existe una lista de reproducción con ese nombre.\n");
        return;
    }

    Playlist* nueva_lista = (Playlist*)malloc(sizeof(Playlist));
    strcpy(nueva_lista->name, nombre_lista);
    nueva_lista->songs = list_create();

    map_insert(playlistMap, strdup(nombre_lista), nueva_lista);
    printf("Lista de reproducción '%s' creada exitosamente.\n", nombre_lista);
}

void agregar_cancion_a_lista(Map* playlistMap, Map* mapaID) {
    char nombre_lista[100];
    printf("Ingrese el nombre de la lista de reproducción: ");
    fgets(nombre_lista, sizeof(nombre_lista), stdin);
    nombre_lista[strcspn(nombre_lista, "\n")] = 0;  // Eliminar salto de línea

    // Buscar la lista de reproducción
    Playlist* lista = (Playlist*) map_search(playlistMap, nombre_lista);

    if (lista == NULL) {
        printf("No se encontró la lista de reproducción '%s'.\n", nombre_lista);
        return;
    }

    int id_cancion;
    printf("Ingrese el ID de la canción a agregar: ");
    scanf("%d", &id_cancion);
    limpiar_buffer();

    // Buscar la canción en el mapa de canciones
    MapPair *pair = map_search(mapaID, &id_cancion);
    if (pair == NULL) {
        printf("No se encontró una canción con el ID: %d\n", id_cancion);
        return;
    }

    Song* cancion = (Song*)pair->value;
    // Insertar la canción en la lista de reproducción
    list_push_back(lista->songs, cancion);
    printf("Canción '%s' agregada a la lista '%s'.\n", cancion->track_name, nombre_lista);

}

void mostrar_canciones_lista(Map* playlistMap) {
    char nombre_lista[100];
    printf("Ingrese el nombre de la lista de reproducción: ");
    fgets(nombre_lista, sizeof(nombre_lista), stdin);
    nombre_lista[strcspn(nombre_lista, "\n")] = 0;  // Eliminar salto de línea

    // Buscar la lista de reproducción
    Playlist* lista = (Playlist*) map_search(playlistMap, nombre_lista);

    if (lista == NULL) {
        printf("No se encontró la lista de reproducción '%s'.\n", nombre_lista);
        return;
    }

    // Mostrar las canciones en la lista
    printf("Canciones en la lista de reproducción '%s':\n", lista->name);
    Node* current = list_first(lista->songs);
    while (current != NULL) {
        Song* cancion = (Song*)current->data;
        printf("ID: %d\n", cancion->id);
        printf("Título canción: %s\n", cancion->track_name);
        printf("Artista: %s\n", cancion->artist);
        printf("Álbum: %s\n", cancion->album_name);
        printf("Género: %s\n", cancion->track_genre);
        printf("Tempo: %.2f\n", cancion->tempo);
        printf("-------------------------------\n");
        current = list_next(lista->songs);
    }
}


