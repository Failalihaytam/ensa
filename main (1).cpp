#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tri_rapide(int tab[], int debut, int fin);
void tri_fusion(int tab[], int debut, int fin);
int tour_hanoi(int n, int *movement_count);
void tri_sel(int tab[],int taille);
void tri_simple(int tab[], int taille);
void tri_bulle(int tab[], int taille);
void tri_insert(int tab[], int taille);
int menu(int tab[], int taille);

#define array_size 2000

int main()
{
    double time_spent = 0.0;
    int tab[array_size];
    int taille = array_size;
    srand(time(NULL));
    for(int i = 0; i < array_size; i++)
    {
        tab[i] = rand() % 1000;
    }

    int choix = menu(tab, taille);
    clock_t begin = clock();
    if (choix == 1)
    {
        int n;
        printf("donner le nombre des disk: ");
        scanf("%d",&n);
        int movement_count = 0;
        printf("le nombre de movements minimals est %d\n",tour_hanoi(n, &movement_count));
        return 0;
    }
    else if (choix == 2)
    {
        tri_simple(tab, taille);
    }
    else if (choix == 3)
    {
        tri_sel(tab, taille);
    }
    else if (choix == 4)
    {
        tri_insert(tab, taille);
    }
    else if (choix == 5)
    {
        tri_bulle(tab, taille);
    }
    else if (choix == 6)
    {
        tri_fusion(tab, 0, array_size-1);
    }
    else
    {
        tri_rapide(tab, 0, array_size-1);
    }
    clock_t end = clock();
    for (int i = 0; i < taille; ++i)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
}

int menu(int tab[], int taille)
{
    int choix;
    printf("choisissez\n1-tour de hanoi\n2-tri\n");
    scanf("%d",&choix);
    if(choix==1)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < taille; ++i)
        {
            printf("%d ", tab[i]);
        }
        printf("\n");

        printf("1-Tri simple\n2-Tri par selection\n3-Tri par insertion\n4-Tri bulle\n5-Tri rapide\n6-Tri fusion\n");
        scanf("%d",&choix);
        return choix+1;
    }
}

void tri_rapide(int tab[], int debut, int fin)
{
    if (debut < fin) {
        int pivot = tab[fin];
        int i = debut - 1;

        for (int j = debut; j < fin; j++) {
            if (tab[j] <= pivot) {
                i++;
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }

        int temp = tab[i + 1];
        tab[i + 1] = tab[fin];
        tab[fin] = temp;

        pivot = i + 1;

        tri_rapide(tab, debut, pivot - 1);
        tri_rapide(tab, pivot + 1, fin);
    }
}


void tri_fusion(int tab[], int debut, int fin) {
    if (debut < fin) {
        int milieu = (debut + fin) / 2;
        tri_fusion(tab, debut, milieu);
        tri_fusion(tab, milieu + 1, fin);

        int taille1 = milieu - debut + 1;
        int taille2 = fin - milieu;

        int tableau_gauche[taille1], tableau_droit[taille2];
        int i, j, k;

        for (i = 0; i < taille1; i++)
            tableau_gauche[i] = tab[debut + i];
        for (j = 0; j < taille2; j++)
            tableau_droit[j] = tab[milieu + 1 + j];

        i = 0;
        j = 0;
        k = debut;

        while (i < taille1 && j < taille2) {
            if (tableau_gauche[i] <= tableau_droit[j]) {
                tab[k] = tableau_gauche[i];
                i++;
            } else {
                tab[k] = tableau_droit[j];
                j++;
            }
            k++;
        }

        while (i < taille1) {
            tab[k] = tableau_gauche[i];
            i++;
            k++;
        }

        while (j < taille2) {
            tab[k] = tableau_droit[j];
            j++;
            k++;
        }
    }
}


int tour_hanoi(int n, int *movement_count) {
    if (n == 1) {
        (*movement_count)++;
        return *movement_count;
    }
    tour_hanoi(n-1, movement_count);
    (*movement_count)++;
    tour_hanoi(n-1, movement_count);
    return *movement_count;
}



void tri_simple(int tab[], int taille)
{
    for(int i = 0;i< taille; i++)
    {
        for(int j = 0; j< taille-1;j++)
        {
            if(tab[j]> tab[j+1])
            {
                int temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}

void tri_sel(int tab[], int taille) {
    int min;

    for (int i = 0; i < taille - 1; i++) {
        min = i;
        for (int j = i + 1; j < taille; j++) {
            if (tab[j] < tab[min])
                min = j;
        }
        int temp = tab[min];
        tab[min] = tab[i];
        tab[i] = temp;
    }
}

void tri_bulle(int tab[], int taille)
{
    for(int i = 0; i < taille-1; i++)
    {
        for(int j = 0; j < taille-i-1; j++)
        {
            if(tab[j] > tab[j+1])
            {
                int temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}
void tri_insert(int tab[], int taille)
{
    for (int i = 0;i < taille; i++)
    {
        int temp = tab[i];
        int j = i - 1;
        while (j >= 0 && tab[j] > temp)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}