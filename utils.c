#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "sorting_algorithms.h"
#include "resource_usage.h"
#include "utils.h"

// Définition de la fonction generate_random_string
char* generate_random_string(int size) {
    static int random_seed_initialized = 0;
    if (!random_seed_initialized) {
#ifdef _WIN32
        srand(GetCurrentProcessId());
#else
        srand(getpid());
#endif
        random_seed_initialized = 1;
    }

    char *str = malloc(size + 1);
    if (str == NULL) {
        printf("Échec de l'allocation mémoire\n");
        return NULL;
    }

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?! ";
    int charset_size = sizeof(charset) - 1;

    for (int i = 0; i < size; i++) {
        int key = rand() % charset_size;
        str[i] = charset[key];
    }
    str[size] = '\0';

    return str;
}

// Définition de la fonction find_best_algorithm
void find_best_algorithm(SortResult results[], int count) {
    int fastest_index = 0;
    int most_efficient_index = 0;

    for (int i = 1; i < count; i++) {
        if (results[i].time_spent < results[fastest_index].time_spent) {
            fastest_index = i;
        }
        if (results[i].ram_usage < results[most_efficient_index].ram_usage) {
            most_efficient_index = i;
        }
    }

    printf("\nLe tri le plus rapide est : %s\n", results[fastest_index].name);
    printf("Le tri le plus économe en RAM est : %s\n", results[most_efficient_index].name);
}

// Fonction pour sauvegarder les résultats dans un fichier CSV
void save_results_to_file(SortResult results[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Échec de l'ouverture du fichier pour écrire les résultats.\n");
        return;
    }

    fprintf(file, "Algorithm,Time Spent (s),User CPU (s),Sys CPU (s),RAM Usage (KB),Invol CS,Vol CS\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%.6f,%.6f,%.6f,%zu,%ld,%ld\n", 
                results[i].name, results[i].time_spent, results[i].user_cpu_time, 
                results[i].sys_cpu_time, results[i].ram_usage, results[i].invol_context_switches, 
                results[i].vol_context_switches);
    }

    fclose(file);
}
