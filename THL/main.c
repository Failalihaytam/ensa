#include <stdio.h>

#define MAX_LINES 1000
#define MAX_LENGTH 100

typedef struct
{
    int depart;
    int arrive;
    char etiquete;
}Transaction;

typedef struct
{
    Transaction transactions[MAX_LINES];
    int first;
    int last;
}Data;

int main(void)
{
    Data my_data;

    FILE *file = fopen("projet.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    int transactions_index = 0;
    char line[MAX_LENGTH];

    while(fgets(line, sizeof(line), file) !=0)
    {
        if (sscanf(line, "%d %d %s", &my_data.transactions[transactions_index].depart,
            &my_data.transactions[transactions_index].arrive,
            my_data.transactions[transactions_index].etiquete) == 3)
        {
            transactions_index++;
        }
        else
        {
            sscanf(line, "%d", &my_data.first);
            fgets(line, sizeof(line), file);
            sscanf(line, "%d", &my_data.last);
            break;
        }
    }
    fclose(file);

    // Print the struct
    printf("Transactions:\n");
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%d %d %s\n", my_data.transactions[i].depart, my_data.transactions[i].arrive, my_data.transactions[i].etiquete);
    }
    printf("first: %d\n", my_data.first);
    printf("last: %d\n", my_data.last);

    return 0;
}
