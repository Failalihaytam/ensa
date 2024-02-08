#include <stdio.h>

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
} Data;

// declarer les prototypes des fonctions
Data stocker(FILE *file);
void afficher(Data data);

int transactions_index = 0;

int main(void)
{
    FILE *my_file = fopen("projet.txt", "r");
    if (my_file == NULL)
    {
        return 1;
    }
    Data my_data = stocker(my_file);

    // afficher le contenu de my_data
    afficher(my_data);

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

void afficher(Data data)
{
    printf("Transactions:\n");
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%d %d %c\n", data.transactions[i].depart, data.transactions[i].arrive, data.transactions[i].etiquete);
    }
    printf("first: %d\n", data.first);
    printf("last: %d\n", data.last);
    return;
}

void menu(void)
{
    int answer;
    do
    {
        do
        {
            printf("entrer un nombre pour choisir votre operation: \n");
            printf("1- afficher la liste des transaction\n2- afficher l'etat initial\n3- afficher l'etat final\n4- afficher la liste des alphabets");

        }
        while (answer < 1 || answer > 4);
    }
    while (answer != 0);
}
