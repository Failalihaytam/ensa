#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TRANSITIONS 100
#define MAX_STATES 100

typedef struct {
    int etat_depart;
    int etat_arrive;
    char etiquette;
} Transition;

typedef struct {
    Transition transitions[MAX_TRANSITIONS];
    int nb_transitions;
    int etats_initiaux[MAX_STATES];
    int nb_etats_initiaux;
    int etats_finaux[MAX_STATES];
    int nb_etats_finaux;
} Automate;

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

    // Read last two lines separately
    char buffer[100];
    fgets(buffer, sizeof(buffer), fichier); // Read the first line
    fgets(buffer, sizeof(buffer), fichier); // Read the second line

    // Split the line into tokens and store initial states
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        automate->etats_initiaux[automate->nb_etats_initiaux++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // Read the third line
    fgets(buffer, sizeof(buffer), fichier);

    // Split the line into tokens and store final states
    token = strtok(buffer, " ");
    while (token != NULL) {
        automate->etats_finaux[automate->nb_etats_finaux++] = atoi(token);
        token = strtok(NULL, " ");
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
    return 0;
}
