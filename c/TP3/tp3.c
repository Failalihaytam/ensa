#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//1
typedef struct
{
    long numero;
    double solde;
    char nom[50];
    char prenom[50];
} compte;

char menu();
char sous_menu();
compte *saisir ();
void afficher(char *fichier, long num_compte);
void ajouter(char *fichier, compte c);
int position(char *fichier, long num);
void operation(char *fichier, long num_compte);
void verser(char *fichier, long num_compte, double solde);
void retirer(char *fichier, long num_compte, double solde);

void lister_comptes(char *fichier);

int main()
{
    lister_comptes("comptes.bin");
}

//2
//a
char menu()
{
    char choix;
    printf("_______Ajouter un compte ______ A\n");
    printf("_______Supprimer un compte ______S\n");
    printf("_______Op�rations sur un compte ______ O\n");
    printf("     ** Affichage **      A\n");
    printf("     ** virement **     V\n");
    printf("     ** Retrait **     R\n");
    printf("_______lister les d�biteurs ______D\n");
    printf("_______Lister les comptes ______L\n");
    printf("_______Quitter ______Q\n");
    printf("Entrer votre choix : ");
    scanf("%c", &choix);
    return choix;
}

//b
char sous_menu()
{
    char choix;
    printf("     ** Affichage **      A\n");
    printf("     ** virement **     V\n");
    printf("     ** Retrait **     R\n");
    printf(" ** pour quitter taper ** Q\n");
    printf("Entrer votre choix : ");
    scanf(" %c", &choix);
    return choix;
}

//c
compte *saisir ()
{
    compte *c = malloc(sizeof(compte));
    printf("Entrez les informations de votre compte(numero, solde, nom, prenom):  ");
    scanf("%ld %lf %s %s", &c->numero, &c->solde, c->nom, c->prenom);
    return c;
}

//d
void afficher(char *fichier, long num_compte)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    if (file == NULL)
    {
        return;
    }

    while(feof(file) == 0)
    {
      fscanf(file, "%ld %lf %s %s", &c.numero, &c.solde, c.nom, c.prenom);
      if(c.numero == num_compte)
      {
          printf("numero: %ld\nsolde: %lf\nnom: %s\nprenom: %s\n", c.numero, c.solde, c.nom, c.prenom);
          return;
      }
    }
}

//e
void ajouter(char *fichier, compte c)
{
    FILE *file = fopen(fichier, "ab");
    if (file == NULL)
    {
        return;
    }

    fprintf(file, "%ld %lf %s %s\n", c.numero, c.solde, c.nom, c.prenom);
}

//f
int position(char *fichier, long num)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    if (file == NULL)
    {
        return -1;
    }

    int i = 1;
    while(feof(file) == 0)
    {
      fscanf(file, "%ld %lf %s %s", &c.numero, &c.solde, c.nom, c.prenom);
      if(c.numero == num)
      {
          return i;
      }
      i++;
    }
    return -1;
}

//g

void operation(char *fichier, long num_compte)
{
    double solde;

    char choix;
    do
    {
        choix = toupper(sous_menu());
        if(choix == 'A')
        {
            afficher(fichier, num_compte);
        }
        else if(choix == 'V')
        {
            printf("combien voudrez vous verser?: ");
            scanf("%lf", &solde);
            verser(fichier, num_compte, solde);
        }
        else if(choix == 'R')
        {
            printf("combien voudrez vous retirer?: ");
            scanf("%lf", &solde);
            retirer(fichier, num_compte, solde);
        }
    }while(choix != 'Q');
}

//h
void verser(char *fichier, long num_compte, double solde)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    FILE *tmp = fopen("tmp.bin", "wb");
    if (file == NULL || tmp == NULL)
    {
        return;
    }

    while(feof(file) == 0)
    {
        fscanf(file, "%ld %lf %s %s", &c.numero, &c.solde, c.nom, c.prenom);
        if (c.numero == num_compte)
        {
            fprintf(tmp, "%ld %lf %s %s\n", c.numero, c.solde + solde, c.nom, c.prenom);
        }
        else
        {
            fprintf(tmp, "%ld %lf %s %s\n", c.numero, c.solde, c.nom, c.prenom);
        }
    }
    fclose(file);
    fclose(tmp);
    remove(fichier);
    rename("tmp.bin", fichier);
}

//i
void retirer(char *fichier, long num_compte, double solde)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    FILE *tmp = fopen("tmp.bin", "wb");
    if (file == NULL || tmp == NULL)
    {
        return;
    }

    while(feof(file) == 0)
    {
        fscanf(file, "%ld %lf %s %s", &c.numero, &c.solde, c.nom, c.prenom);
        if (c.numero == num_compte)
        {
            fprintf(tmp, "%ld %lf %s %s\n", c.numero, c.solde - solde, c.nom, c.prenom);
        }
        else
        {
            fprintf(tmp, "%ld %lf %s %s\n", c.numero, c.solde, c.nom, c.prenom);
        }
    }
    fclose(file);
    fclose(tmp);
    remove(fichier);
    rename("tmp.bin", fichier);
}

//j
void lister_debiteurs(char *fichier)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    if (file == NULL)
    {
        return;
    }
}
//k
void lister_comptes(char *fichier)
{
    compte c;
    FILE *file = fopen(fichier, "rb");
    if (file == NULL)
    {
        return;
    }

    int i = 1;
    //cette nouvelle boucle est utilisee pour eviter l'affichage de la derniere ligne deux fois
    while (fscanf(file, "%ld %lf %s %s", &c.numero, &c.solde, c.nom, c.prenom) == 4)
    {
        printf("%d.\nnumero: %ld\nsolde: %lf\nnom: %s\nprenom: %s\n\n", i, c.numero, c.solde, c.nom, c.prenom);
        i++;
    }

    fclose(file);
}

