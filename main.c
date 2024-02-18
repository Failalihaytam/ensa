#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TRANSITIONS 100
#define MAX_ALPHABETS 26


typedef struct {
    int etat_depart;
    int etat_arrive;
    char etiquette;
} Transition;

typedef struct {
    Transition transitions[MAX_TRANSITIONS];
    int nb_transitions;
    int etats_initiaux[MAX_TRANSITIONS];
    int nb_etats_initiaux;
    int etats_finaux[MAX_TRANSITIONS];
    int nb_etats_finaux;
} Automate;

void count_lines(FILE *file, Automate *automate);
void last_lines(FILE *file, Automate *automate);

void lireAutomate(Automate *automate, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Initialize counts
    automate->nb_transitions = 0;
    automate->nb_etats_initiaux = 0;
    automate->nb_etats_finaux = 0;

    // Read transitions
    while (fscanf(fichier, "%d %d %c", &automate->transitions[automate->nb_transitions].etat_depart,
                                        &automate->transitions[automate->nb_transitions].etat_arrive,
                                        &automate->transitions[automate->nb_transitions].etiquette) == 3)
    {
        automate->nb_transitions++;
        if (automate->nb_transitions >= MAX_TRANSITIONS) {
            fprintf(stderr, "Trop de transitions. Ajustez la valeur de MAX_TRANSITIONS.\n");
            fclose(fichier);
            exit(EXIT_FAILURE);
        }
    }

    // Read and store initial states from the same line as transitions
    fseek(fichier, 0, SEEK_SET); // Reset file pointer to the beginning
    char buffer[100]; // Buffer to store the entire line
    fgets(buffer, sizeof(buffer), fichier); // Read the first line containing transitions
    sscanf(buffer, "%*d %*d %*s"); // Skip transitions
    int etat;
    while (fscanf(fichier, "%d", &etat) == 1) {
        automate->etats_initiaux[automate->nb_etats_initiaux++] = etat;
    }

    // Read and store final states from the next line
    while (fscanf(fichier, "%d", &etat) == 1) {
        automate->etats_finaux[automate->nb_etats_finaux++] = etat;
    }

    fclose(fichier);
}



void afficherAutomate(const Automate *automate) {
    printf("Transitions de l'automate :\n");
    for (int i = 0; i < automate->nb_transitions; ++i) {
        printf("%d -> %d : %c\n", automate->transitions[i].etat_depart,
                                   automate->transitions[i].etat_arrive,
                                   automate->transitions[i].etiquette);
    }

    printf("\nEtats initiaux de l'automate :\n");
    for (int i = 0; i < automate->nb_etats_initiaux; ++i) {
        printf("%d ", automate->etats_initiaux[i]);
    }
    printf("\n");

    printf("\nEtats finaux de l'automate :\n");
    for (int i = 0; i < automate->nb_etats_finaux; ++i) {
        printf("%d ", automate->etats_finaux[i]);
    }
    printf("\n");
}


int main() {
    Automate automate;
    lireAutomate(&automate, "file.txt");
    afficherAutomate(&automate);
}