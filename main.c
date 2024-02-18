#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSITIONS 100
#define MAX_ALPHABET_SIZE 26
#define MAX_ETAT 100

typedef struct {
    int etat_initial;
    int etat_final;
    char etiquette;
} Transition;

typedef struct {
    Transition transitions[MAX_TRANSITIONS];
    int nombre_transitions;
    int etat_initiaux[MAX_TRANSITIONS];
    int nombre_etats_initiaux;
    int etats_finaux[MAX_TRANSITIONS];
    int nombre_etats_finaux;
} Automate;

Automate lireAutomateDepuisFichier(const char* nom_fichier) {
    Automate automate;
    FILE* fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    automate.nombre_transitions = 0;
    automate.nombre_etats_initiaux = 0;
    automate.nombre_etats_finaux = 0;

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strlen(ligne) < 3) {
            continue;
        }
        sscanf(ligne, "%d %d %c", &automate.transitions[automate.nombre_transitions].etat_initial,
               &automate.transitions[automate.nombre_transitions].etat_final,
               &automate.transitions[automate.nombre_transitions].etiquette);
        automate.nombre_transitions++;
    }

    fgets(ligne, sizeof(ligne), fichier);
    automate.nombre_etats_initiaux = sscanf(ligne, "%d %d %d", &automate.etat_initiaux[0], &automate.etat_initiaux[1], &automate.etat_initiaux[2]);

    fgets(ligne, sizeof(ligne), fichier);
    automate.nombre_etats_finaux = sscanf(ligne, "%d %d %d", &automate.etats_finaux[0], &automate.etats_finaux[1], &automate.etats_finaux[2]);

    fclose(fichier);
    return automate;
}

void afficherAlphabet(const Automate automate) {
    int alphabet[MAX_ALPHABET_SIZE] = {0};
    for (int i = 0; i < automate.nombre_transitions; ++i) {
        alphabet[automate.transitions[i].etiquette - 'a'] = 1;
    }
    printf("Alphabet de l'automate :\n");
    for (int i = 0; i < MAX_ALPHABET_SIZE; ++i) {
        if (alphabet[i] == 1) {
            printf("%c ", i + 'a');
        }
    }
    printf("\n");
}

void genererDotAutomate(const Automate automate) {
    FILE* fichier_dot = fopen("automate.dot", "w");
    if (fichier_dot == NULL) {
        printf("Erreur lors de la création du fichier DOT.\n");
        return;
    }

    fprintf(fichier_dot, "digraph Automate {\n");
    for (int i = 0; i < automate.nombre_transitions; ++i) {
        fprintf(fichier_dot, "    %d -> %d [label=\"%c\"];\n", automate.transitions[i].etat_initial,
                automate.transitions[i].etat_final, automate.transitions[i].etiquette);
    }

    for (int i = 0; i < automate.nombre_etats_initiaux; ++i) {
        fprintf(fichier_dot, "    %d [color=green];\n", automate.etat_initiaux[i]);
    }
    for (int i = 0; i < automate.nombre_etats_finaux; ++i) {
        fprintf(fichier_dot, "    %d [color=blue];\n", automate.etats_finaux[i]);
    }

    fprintf(fichier_dot, "}\n");
    fclose(fichier_dot);
}

void afficherAutomatePNG() {
    system("dot -Tpng automate.dot -o automate.png");
    system("start automate.png");
}

void afficherMenu(const Automate automate) {
    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Afficher l'alphabet\n");
        printf("2. Générer et afficher l'automate en image PNG\n");
        printf("0. Quitter\n");

        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherAlphabet(automate);
                break;
            case 2:
                genererDotAutomate(automate);
                afficherAutomatePNG();
                break;
            case 0:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    } while (choix != 0);
}

int main() {
    Automate automate = lireAutomateDepuisFichier("file.txt");
    printf("Automate lu depuis le fichier.\n");
    afficherMenu(automate);
    return 0;
}
