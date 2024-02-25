#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINES 1000
#define MAX_LENGTH 100

typedef struct
{
    int depart;
    int arrive;
    char etiquete;
} Transition;

typedef struct
{
    Transition transitions[MAX_LINES];
    int initial;
    int final;
} Automate;

// declarer les fonctions
Automate stock(FILE *file);
void alphabet(Automate automate);
void menu(Automate automate);
void generate_dot(Automate automate);

int transitions_index = 0;

int main()
{
    FILE *my_file = fopen("projet.txt", "r");
    if (my_file == NULL)
    {
        return 1;
    }
    Automate my_automate = stock(my_file);

    // afficher le menu des operations
    menu(my_automate);

    return 0;
}

Automate stock(FILE *file) //stocker l'automate
{
    Automate automate;

    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file) != 0)
    {
        if (sscanf(line, "%d %d %c", &automate.transitions[transitions_index].depart,
                   &automate.transitions[transitions_index].arrive,
                   &automate.transitions[transitions_index].etiquete) == 3)
        {
            transitions_index++;
        }
        else
        {
            sscanf(line, "%d", &automate.initial);
            fgets(line, sizeof(line), file);
            sscanf(line, "%d", &automate.final);
            break;
        }
    }
    // Close the file
    fclose(file);

    return automate;
}
void alphabet(Automate automate)
{
    printf("Alphabets:\n");
    for (int i = 0; i < transitions_index; ++i)
    {
        printf("%c ", automate.transitions[i].etiquete);
    }
    printf("\n");
    return;
}

void menu(Automate automate)
{
    int choix;
    do
    {
        char input[100];
        do
        {
            printf("entrer un nombre pour choisir votre operation: \n");
            printf("1- Afficher la liste des transitions\n2- Afficher l'etat initial\n3- Afficher l'etat final\n4- Afficher la liste des alphabets\n5- Afficher le fichier png \n6- Quitter le programme\n");

            // lire input comme chaine de caractere
            scanf("%s", input);

            // convertir input to integer avec atoi
            choix = atoi(input);

            // s'assurer si input est un integer
            if (choix < 1 || choix > 6) {
                printf("Entrer un nombre entre 1 et 6.\n");
            }
        }
        while (choix < 1 || choix > 6);

        if (choix == 1)
        {
            printf("Transitions:\n");
            for (int i = 0; i < transitions_index; i++)
            {
                printf("(%d, %c) ->  %d \n", automate.transitions[i].depart, automate.transitions[i].etiquete, automate.transitions[i].arrive);
            }
        }
        else if (choix == 2)
        {
            printf("L'etat initial: %d\n", automate.initial);
        }
        else if (choix == 3)
        {
            printf("L'etat final: %d\n", automate.final);
        }
        else if (choix == 4)
        {
            alphabet(automate);
        }
        else if (choix == 5)
        {
            generate_dot(automate);
        }

        printf("\n");
    }
    while (choix != 6);
    return;
}
void generate_dot(Automate automate) {
    FILE *file_dot = fopen("automate.dot","w");
    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph automate{\n");
    for (int i = 0; i < transitions_index; i++){
        fprintf(file_dot,  "%d -> %d [label=%c];\n", automate.transitions[i].depart, automate.transitions[i].arrive, automate.transitions[i].etiquete);
    }
    fprintf(file_dot,"%d [color=green];\n",automate.initial);
    fprintf(file_dot,"%d [color=blue];\n",automate.final);

    for(int i=0; i < transitions_index; i++)
    {
        bool trouve = false;
        for(int j=0; j < transitions_index; j++)
        {
            if (automate.transitions[i].depart == automate.transitions[j].arrive)
            {
                trouve = true;
                break;
            }
        }
        if (trouve == false && automate.transitions[i].depart != automate.initial)//etats inatteignables
        {
            fprintf(file_dot,"%d [color=grey];\n",automate.transitions[i].depart);
        }
    }
    fprintf(file_dot,"}");
    fclose(file_dot);
    system("dot -Tpng automate.dot -o automate.png");//system :fonction pour executer les commandes de cmd
    system("start automate.png");
}

bool est_engendre(Automate automate, char *mot)
{
    int etat_courant = automate.initial;

    for (int i = 0; i < strlen(mot); i++)
    {
        char lettre = mot[i];
        bool trouve = false;

        for (int j = 0; j < transition_index; j++)
        {
            if (automate.transitions[j].depart == etat_courant && automate.transitions[j].etiquete == lettre)
            {
                etat_courant = automate.transitions[j].arrive;
                trouve = true;
                break;
            }
        }
        if (trouve == false)
        {
            return false;
        }
    }
    if (etat_courant == automate.final)
    {
        return true;
    }
    return false;
}
