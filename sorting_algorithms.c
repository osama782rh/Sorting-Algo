#include <stdlib.h>
#include <stdio.h>

// Tri à bulles adapté pour utiliser trois paramètres avec optimisation et vérification élément déjà triée
void bubble_sort(char *str, int low, int high) {
    int size = high + 1;
    int swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = 0; // Réinitialiser swapped à 0 au début de la boucle
        for (int j = 0; j < size - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
                swapped = 1; // Mettre swapped à 1 s'il y a un échange
            }
        }
        if (swapped == 0) // Si aucun élément n'a été échangé, sortir de la boucle
            break;
    }
}

// Tri fusion
void merge(char *str, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char *L = (char *)malloc(n1 * sizeof(char));
    char *R = (char *)malloc(n2 * sizeof(char));

    for (i = 0; i < n1; i++)
        L[i] = str[l + i];
    for (j = 0; j < n2; j++)
        R[j] = str[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            str[k] = L[i];
            i++;
        } else {
            str[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        str[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        str[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(char *str, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(str, l, m);
        merge_sort(str, m + 1, r);
        merge(str, l, m, r);
    }
}

// Tri par insertion adapté pour utiliser trois paramètres
void insertion_sort(char *str, int low, int high) {
    int size = high + 1;
    for (int i = low + 1; i < size; i++) {
        char key = str[i];
        int j = i - 1;
        // Déplacer les éléments de str[low...i-1] qui sont plus grands que key
        // d'une position vers l'avant de leur position actuelle
        while (j >= low && str[j] > key) {
            str[j + 1] = str[j];
            j = j - 1;
        }
        str[j + 1] = key;
    }
}

// Tri rapide
int partition(char *str, int low, int high) {
    char pivot = str[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (str[j] < pivot) {
            i++;
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
    }
    char temp = str[i + 1];
    str[i + 1] = str[high];
    str[high] = temp;
    return (i + 1);
}

void quick_sort(char *str, int low, int high) {
    if (low < high) {
        int pivot = partition(str, low, high);
        quick_sort(str, low, pivot - 1);
        quick_sort(str, pivot + 1, high);
    }
}
