#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#endif
#include "sorting_algorithms.h"
#include "resource_usage.h"
#include "hybrid_sort.h"
#include "utils.h"  

// Fonction pour supprimer le fichier CSV existant
void remove_existing_csv(const char *filename) {
    if (remove(filename) == 0) {
        printf("Le fichier %s a été supprimé.\n", filename);
    } else {
        printf("Le fichier %s n'existe pas ou ne peut pas être supprimé.\n", filename);
    }
}

// Fonction pour créer un nouveau dossier pour chaque test
char* create_new_test_directory() {
    int test_num = 1;
    char *dir_name = malloc(20 * sizeof(char));
    if (dir_name == NULL) {
        printf("Échec de l'allocation mémoire\n");
        return NULL;
    }
    
    while (1) {
        sprintf(dir_name, "Test_results_%d", test_num);
#ifdef _WIN32
        if (_mkdir(dir_name) == 0) break;
#else
        if (mkdir(dir_name, 0777) == 0) break;
#endif
        test_num++;
    }
    return dir_name;
}

int main() {
    const char *csv_filename = "sort_results.csv";

    // Supprimer le fichier CSV existant
    remove_existing_csv(csv_filename);

    // Créer un nouveau dossier pour ce test
    char *test_dir = create_new_test_directory();
    if (test_dir == NULL) {
        return 1;  // Retourne une erreur si le dossier n'a pas pu être créé
    }

    int size = 200000; // Augmenter la taille des chaînes à 200 000 caractères
    char *random_string = generate_random_string(size);
    if (random_string == NULL) {
        free(test_dir);
        return 1;  // Retourne une erreur si la chaîne n'a pas pu être générée
    }

    SortResult results[5];

    printf("Testing sorting algorithms with string size of %d characters...\n", size);
    test_sort_performance(bubble_sort, "Bubble Sort", random_string, size, &results[0]);
    test_sort_performance(insertion_sort, "Insertion Sort", random_string, size, &results[1]);
    test_sort_performance(quick_sort, "Quick Sort", random_string, size, &results[2]);
    test_sort_performance(merge_sort, "Merge Sort", random_string, size, &results[3]);
    test_sort_performance(esiee_it_sort, "Esiee-it Sort", random_string, size, &results[4]);

    print_results(results, 5);
    find_best_algorithm(results, 5);

    // Sauvegarder les résultats dans un fichier CSV
    save_results_to_file(results, 5, csv_filename);

    // Déplacer le fichier CSV dans le nouveau dossier
    char new_csv_path[100];
    snprintf(new_csv_path, sizeof(new_csv_path), "%s/%s", test_dir, csv_filename);
    rename(csv_filename, new_csv_path);

    free(random_string);  // Libérer la mémoire allouée
    free(test_dir);
    return 0;
}
