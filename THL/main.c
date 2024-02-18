#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINES 1000
#define MAX_LENGTH 100

typedef struct
{
    int depart;
    int arrive;
    char etiquete;
} Transaction;

typedef struct
{
    Transaction transactions[MAX_LINES];
    int first;
    int last;
} Automate;

// declarer les prototypes des fonctions
Automate stock(FILE *file);
void alphabet(Automate automate);
void menu(Automate automate);
void generate_dot(Automate automate);

int transactions_index = 0;

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

    generate_dot(my_automate);

    return 0;
}

Automate stock(FILE *file)
{
    Automate automate;

    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file) != 0)
    {
        if (sscanf(line, "%d %d %c", &automate.transactions[transactions_index].depart,
                   &automate.transactions[transactions_index].arrive,
                   &automate.transactions[transactions_index].etiquete) == 3)
        {
            transactions_index++;
        }
        else
        {
            sscanf(line, "%d", &automate.first);
            fgets(line, sizeof(line), file);
            sscanf(line, "%d", &automate.last);
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
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%c ", automate.transactions[i].etiquete);
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
            printf("entrer un nombre pour choisir votre operation: \n");
            printf("1- Afficher la liste des transaction\n2- Afficher l'etat initial\n3- Afficher l'etat final\n4- Afficher la liste des alphabets\n5-Generer le fichier PNG\n6- Quitter le programme\n");

            // Read user input as string
            scanf("%s", input);

            // Convert input to integer using atoi
            answer = atoi(input);

            // Check if input is a valid integer
            if (answer < 1 || answer > 5) {
                printf("Invalid input. Please enter a number between 1 and 5.\n");
            }
        }
        while (answer < 1 || answer > 6);

        if (answer == 1)
        {
            printf("Transactions:\n");
            for (int i = 0; i < transactions_index; i++)
            {
                printf("(%d, %c) ->  %d \n", automate.transactions[i].depart, automate.transactions[i].etiquete, automate.transactions[i].arrive);
            }
        }
        else if (answer == 2)
        {
            printf("L'etat initial: %d\n", automate.first);
        }
        else if (answer == 3)
        {
            printf("L'etat final: %d\n", automate.last);
        }
        else if (answer == 4)
        {
            alphabet(automate);
        }
        else if (answer == 5)

        printf("\n");
    }
    while ( answer != 6);
    return;
}
void generate_dot(Automate automate) {
    FILE *file_dot = fopen("automate.dot","w");
    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph automate{\n");
    for (int i = 0; i < transactions_index; i++){
        fprintf(file_dot,  "%d -> %d [label=%c];\n", automate.transactions[i].depart, automate.transactions[i].arrive, automate.transactions[i].etiquete);
    }
    fprintf(file_dot,"%d [color=green];\n",automate.first);
    fprintf(file_dot,"%d [color=blue];\n",automate.last);

    for(int i=0; i < transactions_index; i++)
    {
        bool trouve = false;
        for(int j=0; j < transactions_index; j++)
        {
            if (automate.transactions[i].depart == automate.transactions[j].arrive)
            {
                trouve = true;
                break;
            }
        }
        if (trouve == false && automate.transactions[i].depart != automate.first)
        {
            fprintf(file_dot,"%d [color=grey];\n",automate.transactions[i].depart);
        }
    }
    fprintf(file_dot,"}");
    fclose(file_dot);
    system("dot -Tpng automate.dot -o automate.png");
}
