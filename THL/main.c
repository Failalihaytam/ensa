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

Data stocker(FILE file);

int transactions_index = 0;

int main(void)
{

    FILE *my_file = fopen("projet.txt", "r");
    if (my_file == NULL)
    {
        return 1;
    }

    Data my_data = stocker(my_file);

    // Print the struct
    printf("Transactions:\n");
    for (int i = 0; i < transactions_index; ++i)
    {
        printf("%d %d %c\n", my_data.transactions[i].depart, my_data.transactions[i].arrive, my_data.transactions[i].etiquete);
    }
    printf("first: %d\n", my_data.first);
    printf("last: %d\n", my_data.last);

    return 0;
}

Data stocker(FILE file)
{
    Data data;

    char line[MAX_LENGTH];

    while(fgets(line, sizeof(line), file) !=0)
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
