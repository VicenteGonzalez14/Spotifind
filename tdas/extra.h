
#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include "list.h"
#include "map.h"

typedef struct {
    int id;
    char track_name[100];
    char artist[100];
    char album_name[100];
    float tempo;
    char track_genre[100];
} Song;

typedef struct {
    char name[100];
    List* songs;
} Playlist;

void limpiar_buffer();
char **leer_linea_csv(FILE *archivo, char separador);
void crear_lista_reproduccion(Map* playlistMap);
void agregar_cancion_a_lista(Map* playlistMap, Map* mapaID);
void mostrar_canciones_lista(Map* playlistMap);
void buscar_por_id(Map *mapaID, int id_buscar);
void buscar_por_tempo(Map *mapaTempo, float min, float max);
void buscar_por_artista(Map *mapaArtista, const char *artista);
void leer_canciones(Song **songs, int *total_canciones, Map *mapaID, Map *mapaTempo, Map *mapaArtista);


// Funciones de comparación
int is_equal_int(void *key1, void *key2);
int is_equal_float(void *key1, void *key2);
int is_equal_str(void *key1, void *key2);

#endif
