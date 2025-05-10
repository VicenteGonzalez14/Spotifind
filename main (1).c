#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/map.h"
#include "tdas/list.h"
#include "tdas/extra.h"

int main() {
    char opcion;
    Song *canciones = NULL;
    int total_canciones = 0;
    Map *mapaID = map_create(is_equal_int);
    Map *mapaTempo = map_create(is_equal_float);
    Map *mapaArtista = map_create(is_equal_str);
    Map *playlistMap = map_create(is_equal_str);

    do {
        puts("========================================");
        puts("     Base de Datos de Canciones");
        puts("========================================");
        puts("1) Cargar Canciones");
        puts("2) Buscar por ID");
        puts("3) Buscar por Tempo");
        puts("4) Buscar por Artista");
        puts("5) Crear lista de reproducción");
        puts("6) Agregar canción a lista");
        puts("7) Mostrar lista de reproducción");
        puts("8) Salir");

        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        limpiar_buffer();
        

        switch (opcion) {
            case '1':
                leer_canciones(&canciones, &total_canciones, mapaID, mapaTempo, mapaArtista);
                break;
            case '2': {
                int id;
                printf("Ingrese ID: ");
                scanf("%d", &id);
                limpiar_buffer();
                buscar_por_id(mapaID, id);
                break;
            }
            case '3': {
                float min, max;
                printf("Tempo mínimo: "); scanf("%f", &min);
                printf("Tempo máximo: "); scanf("%f", &max);
                limpiar_buffer();
                buscar_por_tempo(mapaTempo, min, max);
                break;
            }
            case '4': {
                char artista[100];
                printf("Artista: ");
                fgets(artista, 100, stdin);
                artista[strcspn(artista, "\n")] = 0;
                buscar_por_artista(mapaArtista, artista);
                break;
            }
            case '5':
                crear_lista_reproduccion(playlistMap);
                break;
            case '6':
                agregar_cancion_a_lista(playlistMap, mapaID);
                
                break;
            case '7':
                mostrar_canciones_lista(playlistMap);
                
                break;
            case '8':
                puts("Saliendo...");
                break;
            default:
                puts("Opción no válida.");
        }
    } while (opcion != '8');

    map_clean(mapaID);
    map_clean(mapaTempo);
    map_clean(mapaArtista);
    map_clean(playlistMap);
    free(canciones);

    return 0;
}