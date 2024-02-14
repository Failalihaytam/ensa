#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LINES 1000
#define MAX_LENGTH 100

typedef struct
{
    int depart;      // État de départ de la transaction
    int arrive;      // État d'arrivée de la transaction
    char etiquete;   // Étiquette de la transaction
} Transaction;

typedef struct
{
    Transaction transactions[MAX_LINES]; // Tableau de transactions
    int first;                           // État initial
    int last;                            // État final
} Automate; // Structure représentant un automate

// Déclaration des prototypes de fonctions
Automate stocker(FILE *file); // Fonction pour stocker les données de transaction
void alphabet(Automate automate); // Fonction pour afficher les alphabets
void menu(Automate automate); // Fonction pour afficher le menu
void generer_fichier_dot(Automate automate); // Fonction pour générer le fichier DOT et le fichier PNG associé

int transactions_index = 0;

int main()
{
    FILE *my_file = fopen("projet.txt", "r"); // Ouvre le fichier "projet.txt" en mode lecture
    if (my_file == NULL)
    {
        return 1; // Quitte le programme si le fichier n'a pas pu être ouvert
    }
    Automate my_automate = stocker(my_file); // Stocke les données du fichier dans un automate
    fclose(my_file); // Ferme le fichier

    // Affiche le menu des opérations
    menu(my_automate);

    return 0;
}

Automate stocker(FILE *file)
{
    Automate automate; // Déclare une variable de type Automate pour stocker les données
    char line[MAX_LENGTH]; // Déclare un tableau de caractères pour stocker chaque ligne lue du fichier

    while (fgets(line, sizeof(line), file) != 0) // Lit chaque ligne du fichier
    {
        if (sscanf(line, "%d %d %c", &automate.transactions[transactions_index].depart,
                   &automate.transactions[transactions_index].arrive,
                   &automate.transactions[transactions_index].etiquete) == 3) // Si la lecture est réussie pour une transaction
        {
            transactions_index++; // Incrémente l'index des transactions
        }
        else // Sinon, cela signifie qu'on a atteint la ligne contenant les états initial et final
        {
            sscanf(line, "%d", &automate.first); // Lit l'état initial
            fgets(line, sizeof(line), file);     // Passe à la ligne suivante pour lire l'état final
            sscanf(line, "%d", &automate.last);  // Lit l'état final
            break; // Sort de la boucle
        }
    }

    return automate; // Retourne la structure Automate avec les données lues
}

void alphabet(Automate automate)
{
    printf("Alphabets:\n");
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%c ", automate.transactions[i].etiquete); // Affiche l'étiquette de chaque transaction
    }
    printf("\n");
    return;
}

void menu(Automate automate)
{
    int answer;
    do
    {
        char input[100];
        do
        {
            printf("Entrez un nombre pour choisir votre opération :\n");
            printf("1- Afficher la liste des transactions\n2- Afficher l'état initial\n3- Afficher l'état final\n4- Afficher la liste des alphabets\n5- Générer le fichier PNG\n6- Quitter le programme\n");

            // Lit l'entrée de l'utilisateur sous forme de chaîne de caractères
            scanf("%s", input);

            // Convertit l'entrée en entier à l'aide de atoi
            answer = atoi(input);

            // Vérifie si l'entrée est un entier valide
            if (answer < 1 || answer > 6)
            {
                printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 6.\n");
            }
        } while (answer < 1 || answer > 6);

        if (answer == 1)
        {
            printf("Transactions:\n");
            for (int i = 0; i < transactions_index; ++i)
            {
                printf("(%d, %c) -> %d\n", automate.transactions[i].depart, automate.transactions[i].etiquete, automate.transactions[i].arrive); // Affiche chaque transaction
            }
        }
        else if (answer == 2)
        {
            printf("État initial : %d\n", automate.first); // Affiche l'état initial
        }
        else if (answer == 3)
        {
            printf("État final : %d\n", automate.last); // Affiche l'état final
        }
        else if (answer == 4)
        {
            alphabet(automate); // Affiche les alphabets
        }
        else if (answer == 5)
        {
            generer_fichier_dot(automate); // Génère le fichier DOT et le fichier PNG associé
        }

        printf("\n");
    } while (answer != 6); // Continue tant que l'utilisateur ne choisit pas de quitter
    return;
}

void generer_fichier_dot(Automate automate)
{
    FILE *fichier_dot = fopen("automate.dot", "w"); // Ouvre un fichier DOT en écriture
    if (fichier_dot == NULL)
    {
        printf("Impossible d'ouvrir le fichier DOT.\n");
        return;
    }

    // Début du fichier DOT
    fprintf(fichier_dot, "digraph automate {\n");

    // Écriture des transitions
    for (int i = 0; i < transactions_index; ++i)
    {
        fprintf(fichier_dot, "  %d -> %d [label=\"%c\"];\n", automate.transactions[i].depart, automate.transactions[i].arrive, automate.transactions[i].etiquete);
    }

    // Coloration des états initiaux, finaux et autres états
    fprintf(fichier_dot, "  node [style=filled];\n");
    fprintf(fichier_dot, "  %d [fillcolor=green];\n", automate.first); // État initial en vert
    fprintf(fichier_dot, "  %d [fillcolor=blue];\n", automate.last);   // État final en bleu
    for (int i = 0; i < transactions_index; ++i)
    {
        if (automate.transactions[i].depart != automate.first && automate.transactions[i].depart != automate.last)
        {
            fprintf(fichier_dot, "  %d [fillcolor=black];\n", automate.transactions[i].depart); // Autres états en noir
        }
        if (automate.transactions[i].arrive != automate.first && automate.transactions[i].arrive != automate.last)
        {
            fprintf(fichier_dot, "  %d [fillcolor=black];\n", automate.transactions[i].arrive); // Autres états en noir
        }
    }

    // Fin du fichier DOT
    fprintf(fichier_dot, "}\n");

    fclose(fichier_dot); // Ferme le fichier DOT

    // Générer le fichier PNG à partir du fichier DOT
    system("dot -Tpng automate.dot -o automate.png");
}
