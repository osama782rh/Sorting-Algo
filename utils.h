#ifndef UTILS_H
#define UTILS_H

#include "resource_usage.h"  // Inclure le fichier où SortResult est défini

// Déclaration de la fonction generate_random_string
char* generate_random_string(int size);

// Déclaration de la fonction find_best_algorithm
void find_best_algorithm(SortResult results[], int count);

// Déclaration de la fonction save_results_to_file
void save_results_to_file(SortResult results[], int count, const char *filename);

#endif // UTILS_H
