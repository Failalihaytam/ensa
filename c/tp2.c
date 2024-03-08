#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1
typedef struct
{
    int annee;
    int mois;
    int jour;
}Date;

typedef struct
{
    char adresse[100];
    char sujet[100];
    Date date;
    char contenu[500];
    int etat;
}Courrier;

//Declarer les prototypes des fonctions utilisees
Courrier saisir_courrier();
void ajouter_corrier(char *nom_fichier, Courrier c);
void numeroter_enrg(char *nom_fichier);
void parite(char *nom_fichier);
int chercher_mail_exped(char *nom_fich, char *adr_exp);
void afficher_mail_exped(char *nom_fich, char *adr_exp);
int MenuPrincipal();

int main()
{
    Courrier c;
    char adr_exp[100];
    int choix = MenuPrincipal();
    switch(choix)
    {
        case 1:
            c = saisir_courrier();
            ajouter_corrier("Mail.txt", c);
            break;
        case 2:
            numeroter_enrg("Mail.txt");
        case 3:
            parite("Mail.txt");
        case 4:
            printf("entrer l'adresse que vous voullez chercher: ");
            scanf("%s", adr_exp);
            int i = chercher_mail_exped("Mail.txt", adr_exp);
            if (i == -1)
            {
                printf("l'adresse n'existe pas\n");
            }
            else
            {
                printf("C'est l'adresse numero %d\n", i);
            }
        case 5:
            printf("entrer l'adresse que vous voullez afficher ses courriers non lus: ");
            scanf("%s", adr_exp);
            afficher_mail_exped("Mail.txt", adr_exp);
    }
    return 0;
}




//2
Courrier saisir_courrier()
{
    Courrier c;
    printf("entrer les infos du courrier (adresse sujet jour/mois/annne contenu etat): ");
    scanf("%s %s %d/%d/%d %s %d", c.adresse, c.sujet, &c.date.jour, &c.date.mois, &c.date.annee, c.contenu, &c.etat);
    return c;

}

void ajouter_corrier(char *nom_fichier, Courrier c)
{
    FILE *f = fopen(nom_fichier, "a");
    if (f == NULL)
    {
        printf("impossible d'ouvrir le fichier");
        return;
    }

    fprintf(f, "%s %s %d/%d/%d %s %d\n", c.adresse, c.sujet, c.date.jour, c.date.mois, c.date.annee, c.contenu, c.etat);

    fclose(f);
    return;
}

//3
void numeroter_enrg(char *nom_fichier)
{
    Courrier c;
    FILE *f = fopen(nom_fichier, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL)
    {
        printf("impossible d'ouvrir le fichier");
        return;
    }

    int i = 1;
    while(feof(f) == 0)
    {
        fscanf(f, "%s %s %d/%d/%d %s %d", c.adresse, c.sujet, &c.date.jour, &c.date.mois, &c.date.annee, c.contenu, &c.etat);
        fprintf(temp, "%d. %s %s %d/%d/%d %s %d\n", i, c.adresse, c.sujet, c.date.jour, c.date.mois, c.date.annee, c.contenu, c.etat);
        i++;
    }

    fclose(f);
    fclose(temp);
    remove(nom_fichier);
    rename("temp.txt", nom_fichier);
}

//4
void parite(char *nom_fichier)
{
    Courrier c;
    FILE *f = fopen(nom_fichier, "r");
    FILE *f_pair = fopen("Mail_pair.txt", "w");
    FILE *f_impair = fopen("Mail_impair.txt", "w");

    if(f == NULL || f_pair == NULL || f_impair == NULL)
    {
        printf("impossible d'ouvrir le fichier");
        return;
    }

    int i;
    while (feof(f) == 0)
    {
        if (fscanf(f, "%d. %s %s %d/%d/%d %s %d", &i, c.adresse, c.sujet, &c.date.jour, &c.date.mois, &c.date.annee, c.contenu, &c.etat) != -1)
        {
            if (i % 2 == 0)
            {
                fprintf(f_pair, "%s %s %d/%d/%d %s %d\n", c.adresse, c.sujet, c.date.jour, c.date.mois, c.date.annee, c.contenu, c.etat);
            }
            else
            {
                fprintf(f_impair, "%s %s %d/%d/%d %s %d\n", c.adresse, c.sujet, c.date.jour, c.date.mois, c.date.annee, c.contenu, c.etat);
            }
        }
    }
    fclose(f);
    fclose(f_pair);
    fclose(f_impair);
}

//5
int chercher_mail_exped(char *nom_fich, char *adr_exp)
{
    FILE *f = fopen(nom_fich,"r");
    Courrier c;
    if (f == NULL)
    {
        printf("impossible d'ouvrir le fichier");
        return -1;
    }

    int i;
    while (feof(f) == 0)
    {
        if (fscanf(f, "%d. %s %s %d/%d/%d %s %d", &i, c.adresse, c.sujet, &c.date.jour, &c.date.mois, &c.date.annee, c.contenu, &c.etat) != -1)
        {
            if (strcmp(adr_exp, c.adresse) == 0)
            {
                fclose(f);
                return i;
            }
        }
    }
    fclose(f);
    //retourner -1 si l'adresse n'est pas trouvee
    return -1;
}

//6
void afficher_mail_exped(char *nom_fich, char *adr_exp)
{
    FILE *f = fopen(nom_fich,"r");
    Courrier c;
    if (f == NULL)
    {
        printf("impossible d'ouvrir le fichier");
        return;
    }

    int i;
    while (feof(f) == 0)
    {
        if (fscanf(f, "%d. %s %s %d/%d/%d %s %d", &i, c.adresse, c.sujet, &c.date.jour, &c.date.mois, &c.date.annee, c.contenu, &c.etat) != -1)
        {
            if (strcmp(adr_exp, c.adresse) == 0 && c.etat == 0)
            {
                printf("%s %s %d/%d/%d %s %d\n", c.adresse, c.sujet, c.date.jour, c.date.mois, c.date.annee, c.contenu, c.etat);
            }
        }
    }
    fclose(f);
}

//7
int MenuPrincipal()
{
    int choix;
    do
    {
        printf("entrer un nombre pour choisir votre operation: \n");
        printf("1- ajouter un courrier au fichier Mail.txt\n");
        printf("2- Numeroter le fichier Mail.txt\n");
        printf("3- Copier les enregistrements impaires du fichier Mail.text dans le fichier Mail_Impairs.txt et ceux paires dans le fichier Mail_Pairs.txt\n");
        printf("4- Rechercher un mail dans le fichier Mail.txt à base de l'adresse de son expéditeur\n");
        printf("5- Afficher tous les courriers non lus de l'expéditeur\n");
        scanf("%i", &choix);
        printf("\n");
    }while(choix < 1 || choix >5);

    return choix;
}


