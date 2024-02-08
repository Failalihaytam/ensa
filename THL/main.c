#include <stdio.h>
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
<<<<<<< HEAD
}Data;
=======
} Data;

// declarer les prototypes des fonctions
Data stocker(FILE *file);
void alphabet(Data data);
void menu(Data data);

int transactions_index = 0;
>>>>>>> change1

int main(void)
{
    FILE *my_file = fopen("projet.txt", "r");
    if (my_file == NULL)
    {
        return 1;
    }
    Data my_data = stocker(my_file);

    // afficher le contenu de my_data
    menu(my_data);

    return 0;
}

Data stocker(FILE *file)
{
    Data data;

    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file) != 0)
    {
        if (sscanf(line, "%d %d %c", &data.transactions[transactions_index].depart,
                &data.transactions[transactions_index].arrive,
                &data.transactions[transactions_index].etiquete) == 3)
        {
            transactions_index++;
        }
        else
        {
            sscanf(line, "%d", &data.first);
            fgets(line, sizeof(line), file);
            sscanf(line, "%d", &data.last);
            break;
        }
    }
    fclose(file);

    return data;
}

void alphabet(Data data)
{
    printf("Alphabets:\n");
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%c\n", data.transactions[i].etiquete);
    }
    return;
}

void menu(Data data)
{
    int answer;
    do
    {
        do
        {
            printf("entrer un nombre pour choisir votre operation: \n");
            printf("1- Afficher la liste des transaction\n2- Afficher l'etat initial\n3- Afficher l'etat final\n4- Afficher la liste des alphabets\n5- Quitter le programme\n");
            scanf("%i", &answer);
        }
        while (answer < 1 || answer > 5);

        if (answer == 1)
        {
            printf("Transactions:\n");
            for (int i = 0; i < transactions_index; ++i)
            {
                printf("%d %d %c\n", data.transactions[i].depart, data.transactions[i].arrive, data.transactions[i].etiquete);
            }
        }
        else if (answer == 2)
        {
            printf("L'etat initial: %d\n", data.first);
        }
        else if (answer == 3)
        {
            printf("L'etat final: %d\n", data.last);
        }
        else if (answer == 4)
        {
            alphabet(data);
        }
        printf("\n");
    }
    while (answer != 5);
    return;
}
