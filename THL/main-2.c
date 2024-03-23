#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int nbr_transitions;
} Automate;

typedef struct
{
    int etat;
    char etiquete;
} Etiquette;

typedef struct {
    int etats[MAX_LINES];
    int nbr_etats;
} EnsembleEtats;

// declarer les fonctions
Automate stock(FILE *file);
void alphabet(Automate automate);
void menu(Automate automate1, Automate automate2, Automate automate3);
void generate_dot(Automate automate);
bool est_engendre(Automate automate, char *mot);
void test_list(Automate automate, char *nom_fichier);
void Union_Automates(Automate A1,Automate A2);
void etoile(Automate A1);
void produit(Automate A1,Automate A2) ;
Automate intersection(Automate A1,Automate A2);
//void supprimer_epsilon_transitions(Automate automate);




int main()
{
    FILE *my_file1 = fopen("automate1.txt", "r");
    FILE *my_file2 = fopen("automate2.txt", "r");
    FILE *my_file3 = fopen("automate_transitions.txt", "r");

    if (my_file1 == NULL || my_file2 == NULL || my_file3 == NULL)
    {
        return 1;
    }
    Automate my_automate1 = stock(my_file1);
    Automate my_automate2 = stock(my_file2);
    Automate my_automate3 = stock(my_file3);
    // afficher le menu des operations
    menu(my_automate1, my_automate2, my_automate3);

    return 0;
}

Automate stock(FILE *file) //stocker l'automate
{
    Automate automate;
    automate.nbr_transitions=0;
    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file) != 0)
    {
        if (sscanf(line, "%d %d %c", &automate.transitions[automate.nbr_transitions].depart,
                   &automate.transitions[automate.nbr_transitions].arrive,
                   &automate.transitions[automate.nbr_transitions].etiquete) == 3)
        {
            automate.nbr_transitions++;
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
    for (int i = 0; i < automate.nbr_transitions; ++i)
    {
        printf("%c ", automate.transitions[i].etiquete);
    }
    printf("\n");
    return;
}

void menu(Automate automate1, Automate automate2, Automate automate3)
{
    int choix;
    do
    {
        char input[100];
        do
        {
            printf("entrer un nombre pour choisir votre operation: \n");
            printf("1- Afficher la liste des transitions\n2- Afficher l'etat initial\n3- Afficher l'etat final\n4- Afficher la liste des alphabets\n5- Afficher le fichier png \n6- Voir si un mot est engendre par cet automate\n7- voir la liste des mots engendres\n8- Afficher l'union de deux automates\n9- Afficher L'etoile de produit\n10- le produit de deux automates\n11- Afficher l'intersection de deux automates\n12- Supprimer les epsilons transitions\n13- Quitter le programme\n");

            // lire input comme chaine de caractere
            scanf("%s", input);

            // convertir input to integer avec atoi
            choix = atoi(input);

            // s'assurer si input est un integer
            if (choix < 1 || choix > 13) {
                printf("Entrer un nombre entre 1 et 11.\n");
            }
        }
        while (choix < 1 || choix > 13);

        if (choix == 1)
        {
            printf("Transitions:\n");
            for (int i = 0; i < automate1.nbr_transitions; i++)
            {
                printf("(%d, %c) ->  %d \n", automate1.transitions[i].depart, automate1.transitions[i].etiquete, automate1.transitions[i].arrive);
            }
        }
        else if (choix == 2)
        {
            printf("L'etat initial: %d\n", automate1.initial);
        }
        else if (choix == 3)
        {
            printf("L'etat final: %d\n", automate1.final);
        }
        else if (choix == 4)
        {
            alphabet(automate1);
        }
        else if (choix == 5)
        {
            generate_dot(automate1);
        }
        else if (choix == 6)
        {
            char *mot = NULL; // Initialisation avec null

            printf("entrer le mot: ");
            mot = (char *)malloc(sizeof(char) * MAX_LENGTH); // Allocatation de la memoire
            if (mot == NULL)
            {
                return;
            }

            scanf("%s", mot);

            if (est_engendre(automate1, mot))
            {
                printf("ce mot est engendre par cet automate\n");
            }
            else
            {
                printf("ce mot n'est pas engendre par cet automate\n");
            }
        }
        else if (choix == 7)
        {
            test_list(automate1, "Mots.txt");
        }
        else if (choix == 8)
        {
            Union_Automates(automate1,automate2);
        }
        else if (choix == 9)
        {
            etoile(automate1);
        }
        else if (choix == 10)
        {
            produit(automate1,automate2);
        }
        else if (choix == 11)
        {
            intersection(automate1,automate2);
        }
        else if (choix == 12)
        {
            //supprimer_epsilon_transitions(automate3);
        }
        printf("\n");
    }
    while (choix != 13);
    return;
}
void generate_dot(Automate automate) {
    FILE *file_dot = fopen("automate.dot","w");
    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph automate{\n");
    for (int i = 0; i < automate.nbr_transitions; i++){
        fprintf(file_dot,  "%d -> %d [label=%c];\n", automate.transitions[i].depart, automate.transitions[i].arrive, automate.transitions[i].etiquete);
    }
    fprintf(file_dot,"%d [color=green];\n",automate.initial);
    fprintf(file_dot,"%d [color=blue];\n",automate.final);

    for(int i=0; i < automate.nbr_transitions; i++)
    {
        bool trouve = false;
        for(int j=0; j < automate.nbr_transitions; j++)
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

    for (int i = 0, n = strlen(mot); i < n; i++)
    {
        char caractere = mot[i];
        bool transition_trouvee = false;

        for (int j = 0; j < automate.nbr_transitions; j++)
        {
            if (automate.transitions[j].depart == etat_courant && automate.transitions[j].etiquete == caractere)
            {
                etat_courant = automate.transitions[j].arrive;
                transition_trouvee = true;
                break;
            }
        }

        if (!transition_trouvee)
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

void test_list(Automate automate, char *nom_fichier)
{
    FILE *fichier = fopen(nom_fichier,"r");
    if (fichier == NULL)
    {
        return;
    }
    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), fichier) != 0)
    {
        char *mot = NULL; //initialisation avec null

        mot = (char *)malloc(sizeof(char) * MAX_LENGTH); // Allocation de la memoire
        if (mot == NULL)
        {
            return;
        }
        sscanf(line, "%s", mot);

        if (est_engendre(automate, mot))
        {
            printf("%s\n", mot);
        }
    }
    fclose(fichier);
    return;
}

void Union_Automates(Automate A1,Automate A2)
{
    FILE *file_dot = fopen("union.dot","w");

    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph union {\nsubgraph A1{\n");
    for (int i = 0; i < A1.nbr_transitions; i++){
        fprintf(file_dot,  "a%d -> a%d [label=%c];\n", A1.transitions[i].depart, A1.transitions[i].arrive, A1.transitions[i].etiquete);
    }
    fprintf(file_dot,"}\n");

    fprintf(file_dot,"subgraph A2{\n");
    for (int j = 0; j < A2.nbr_transitions; j++){
        fprintf(file_dot,  "b%d -> b%d [label=%c];\n", A2.transitions[j].depart, A2.transitions[j].arrive, A2.transitions[j].etiquete);
    }
    fprintf(file_dot,"}\n");
    fprintf(file_dot,"start -> a%d [label=ε]; \n", A1.initial);
    fprintf(file_dot,"start -> b%d [label=ε]; \n", A2.initial);
    fprintf(file_dot,"a%d -> end [label=ε]; \n", A1.final);
    fprintf(file_dot,"b%d -> end [label=ε]; \n", A2.final);
    fprintf(file_dot,"}");

    fclose(file_dot);
    system("dot -Tpng union.dot -o union.png");
    system("start union.png");
}

void etoile(Automate A){
    FILE *file_dot = fopen("etoile.dot","w");

    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph union {\n");
    for (int i = 0; i < A.nbr_transitions; i++){
        fprintf(file_dot,  "a%d -> a%d [label=%c];\n", A.transitions[i].depart, A.transitions[i].arrive, A.transitions[i].etiquete);
    }
    fprintf(file_dot,"start -> a%d [label=ε]; \n", A.initial);
    fprintf(file_dot,"a%d -> end [label=ε]; \n", A.final);
    fprintf(file_dot,"start -> end [label=ε]; \n", A.initial);
    fprintf(file_dot,"end -> a%d [label=ε]; \n", A.initial);


    fprintf(file_dot,"}\n");

    fclose(file_dot);
    system("dot -Tpng etoile.dot -o etoile.png");
    system("start etoile.png");
}



void produit(Automate A1,Automate A2) {
    FILE *file_dot = fopen("produit.dot", "w");

    if (file_dot == NULL) {
        return;
    }
    fprintf(file_dot, "digraph produit {\n");
    for (int i = 0; i < A1.nbr_transitions; i++) {
        fprintf(file_dot, "a%d -> a%d [label=%c];\n", A1.transitions[i].depart, A1.transitions[i].arrive,
                A1.transitions[i].etiquete);
    }
    fprintf(file_dot,"a%d -> b%d [label=ε];", A1.final, A2.initial);
    for (int j = 0; j < A2.nbr_transitions; j++) {
        fprintf(file_dot, "b%d -> b%d [label=%c];\n", A2.transitions[j].depart, A2.transitions[j].arrive,
                A2.transitions[j].etiquete);
    }
    fprintf(file_dot, "}\n");

    fclose(file_dot);
    system("dot -Tpng produit.dot -o produit.png");
    system("start produit.png");
}

Automate intersection(Automate A1, Automate A2) {
    Automate product_automaton;
    product_automaton.nbr_transitions = 0;

    // Parcourir tous les états de l'automate 1
    for (int i = 0; i < A1.nbr_transitions; i++) {
        // Parcourir tous les états de l'automate 2
        for (int j = 0; j < A2.nbr_transitions; j++) {
            // Ajouter une transition pour chaque combinaison d'états
            Transition transition;
            transition.depart = A1.transitions[i].depart * (A2.final + 1) + A2.transitions[j].depart;
            transition.arrive = A1.transitions[i].arrive * (A2.final + 1) + A2.transitions[j].arrive;
            transition.etiquete = A1.transitions[i].etiquete; // Vous pouvez également utiliser l'étiquette de l'automate 2 ici si nécessaire

            // Ajouter la transition à l'automate produit
            product_automaton.transitions[product_automaton.nbr_transitions] = transition;
            product_automaton.nbr_transitions++;
        }
    }

    // Définir l'état initial du produit comme la paire d'états initiaux
    product_automaton.initial = A1.initial * (A2.final + 1) + A2.initial;

    // Définir l'état final du produit comme la paire d'états finaux
    product_automaton.final = A1.final * (A2.final + 1) + A2.final;



    FILE *file_dot = fopen("intersection.dot", "w");


    fprintf(file_dot, "digraph intersection {\n");

    // Parcourir toutes les transitions de l'automate produit
    for (int i = 0; i < product_automaton.nbr_transitions; i++) {
        fprintf(file_dot, "%d -> %d [label=\"%c\"];\n", product_automaton.transitions[i].depart, product_automaton.transitions[i].arrive, product_automaton.transitions[i].etiquete);
    }

    // Marquer l'état initial
    fprintf(file_dot, "start -> %d [label=\"start\"];\n", product_automaton.initial);
    // Marquer l'état final
    fprintf(file_dot, "%d [shape=doublecircle];\n", product_automaton.final);

    fprintf(file_dot, "}\n");
    fclose(file_dot);

    // Générer le fichier PNG à partir du fichier DOT
    system("dot -Tpng intersection.dot -o intersection.png");
    // Ouvrir le fichier PNG généré
    system("start intersection.png");
    return product_automaton;
}

void supprimer_epsilon_transitions(Automate automate)
{
    int etat_final[MAX_LENGTH];
    int n=0;

    for (int i = 0; i < automate.nbr_transitions; i++)
    {
        if (automate.transitions[i].etiquete == '$')
        {
            // Récupérer l'état de départ
            int etat_depart = automate.transitions[i].depart;
            // Récupérer l'état d'arrivée
            int etat_arrivee = automate.transitions[i].arrive;

            if (etat_arrivee==automate.final)
            {
                etat_final[n]=etat_depart;
                n++;
            }

            // Parcourir à nouveau toutes les transitions pour trouver celles qui mènent à etat_arrivee
            for (int j = 0; j < automate.nbr_transitions; j++)
            {
                // Vérifier si l'état de départ de la transition est égal à etat_arrivee
                if (automate.transitions[j].depart == etat_arrivee)
                {
                    // Ajouter une nouvelle transition de etat_depart à etat_arrivee avec l'étiquette de la transition j
                    automate.transitions[automate.nbr_transitions].depart = etat_depart;
                    automate.transitions[automate.nbr_transitions].arrive = automate.transitions[j].arrive;
                    automate.transitions[automate.nbr_transitions].etiquete = automate.transitions[j].etiquete;
                    automate.nbr_transitions++; // Incrémenter le nombre de transitions de l'automate
                }
            }

            // Décaler toutes les transitions suivant la ε-transition vers la gauche pour la supprimer
            for (int k = i; k < automate.nbr_transitions - 1; k++)
            {
                automate.transitions[k] = automate.transitions[k + 1];
            }
            // Décrémenter le nombre de transitions car une transition ε a été supprimée
            automate.nbr_transitions--;
            // Décrémenter i pour rester au même index dans la boucle après le décalage
            i--;

        }
    }

    FILE *file_dot = fopen("automate_transitions.dot","w");
    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph automate{\n");
    for (int i = 0; i < automate.nbr_transitions; i++)
    {
        fprintf(file_dot,  "%d -> %d [label=%c];\n", automate.transitions[i].depart, automate.transitions[i].arrive, automate.transitions[i].etiquete);
    }
    fprintf(file_dot,"%d [color=green];\n",automate.initial);
    fprintf(file_dot,"%d [color=blue];\n",automate.final);

    for(int i=0; i < automate.nbr_transitions; i++)
    {
        bool trouve = false;
        for(int j=0; j < automate.nbr_transitions; j++)
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
    for (int i=0;i<n+1;i++)
    {
        if(etat_final[i]==automate.initial)
        {
            fprintf(file_dot,"%d [style=filled,color=blue];\n", etat_final[i], etat_final[i]);
        }
        else
        {
            fprintf(file_dot,"%d [color=blue];\n",etat_final[i]);
        }
    }
    fprintf(file_dot,"}");
    fclose(file_dot);
    system("dot -Tpng automate_transitions.dot -o automate_transitions.png");//system :fonction pour executer les commandes de cmd
    system("start automate_transitions.png");
}

EnsembleEtats calculer_etats_atteignables(Automate automate, EnsembleEtats ensemble, char symbole) {
    EnsembleEtats etats_atteignables;
    etats_atteignables.nbr_etats = 0;

    // Parcourir toutes les transitions de l'automate
    for (int i = 0; i < automate.nbr_transitions; i++) {
        Transition transition = automate.transitions[i];
        // Vérifier si la transition part d'un état de l'ensemble actuel avec le symbole donné
        for (int j = 0; j < ensemble.nbr_etats; j++) {
            if (transition.depart == ensemble.etats[j] && transition.etiquete == symbole) {
                // Ajouter l'état d'arrivée à l'ensemble des états atteignables
                etats_atteignables.etats[etats_atteignables.nbr_etats] = transition.arrive;
                etats_atteignables.nbr_etats++;
            }
        }
    }
    return etats_atteignables;
}

// Fonction pour vérifier si un ensemble existe déjà dans la liste des ensembles
bool ensemble_existe_deja(EnsembleEtats ensemble, EnsembleEtats ensembles[], int nbr_ensembles) {
    for (int i = 0; i < nbr_ensembles; i++) {
        // Comparer les ensembles élément par élément
        if (ensemble.nbr_etats == ensembles[i].nbr_etats) {
            bool meme_ensemble = true;
            for (int j = 0; j < ensemble.nbr_etats; j++) {
                if (ensemble.etats[j] != ensembles[i].etats[j]) {
                    meme_ensemble = false;
                    break;
                }
            }
            if (meme_ensemble) {
                return true;
            }
        }
    }
    return false;
}

// Fonction pour convertir un automate non déterministe en un automate déterministe
void convertir_automate(Automate automate_nd) {
    Automate automate_d;
    automate_d.nbr_transitions = 0;

    // Initialiser l'ensemble initial avec l'état initial de l'automate non déterministe
    EnsembleEtats ensemble_initial;
    ensemble_initial.etats[0] = automate_nd.initial;
    ensemble_initial.nbr_etats = 1;

    // Initialiser la liste des ensembles avec l'ensemble initial
    EnsembleEtats ensembles[MAX_LINES];
    ensembles[0] = ensemble_initial;
    int nbr_ensembles = 1;

    // Marquer l'ensemble initial comme non traité
    bool ensembles_traites[MAX_LINES] = {false};
    ensembles_traites[0] = true;

    // Traitement des ensembles jusqu'à ce qu'ils soient tous traités
    for (int i = 0; i < nbr_ensembles; i++) {
        // Pour chaque symbole de l'alphabet
        for (int sym = 'a'; sym <= 'z'; sym++) {
            // Calculer les états atteignables à partir de l'ensemble actuel avec le symbole actuel
            EnsembleEtats etats_atteignables = calculer_etats_atteignables(automate_nd, ensembles[i], sym);
            // Si l'ensemble d'états atteignables est non vide
            if (etats_atteignables.nbr_etats > 0) {
                // Si cet ensemble n'existe pas déjà dans la liste des ensembles
                if (!ensemble_existe_deja(etats_atteignables, ensembles, nbr_ensembles)) {
                    // Ajouter cet ensemble à la liste des ensembles et marquer comme non traité
                    ensembles[nbr_ensembles] = etats_atteignables;
                    ensembles_traites[nbr_ensembles] = false;
                    nbr_ensembles++;
                }
                // Ajouter une transition de l'ensemble actuel vers l'ensemble atteignable avec le symbole actuel
                automate_d.transitions[automate_d.nbr_transitions].depart = i;
                automate_d.transitions[automate_d.nbr_transitions].arrive = nbr_ensembles - 1;
                automate_d.transitions[automate_d.nbr_transitions].etiquete = sym;
                automate_d.nbr_transitions++;
            }
        }
    }

    // Déterminer les états finaux de l'automate déterministe
    for (int i = 0; i < nbr_ensembles; i++)
    {
        for (int j = 0; j < ensembles[i].nbr_etats; j++)
        {
            if (ensembles[i].etats[j] == automate_nd.final)
            {
                automate_d.final = i;
                break;
            }
        }
    }

    // Déterminer l'état initial de l'automate déterministe
    automate_d.initial = 0;

    FILE *file_dot = fopen("automate_deterministe.dot","w");
    if (file_dot == NULL)
    {
        return;
    }
    fprintf(file_dot,"digraph automate{\n");
    for (int i = 0; i < automate.nbr_transitions; i++)
    {
        fprintf(file_dot,  "%d -> %d [label=%c];\n", automate.transitions[i].depart, automate.transitions[i].arrive, automate.transitions[i].etiquete);
    }
    fprintf(file_dot,"%d [color=green];\n",automate.initial);
    fprintf(file_dot,"%d [color=blue];\n",automate.final);

    for(int i=0; i < automate.nbr_transitions; i++)
    {
        bool trouve = false;
        for(int j=0; j < automate.nbr_transitions; j++)
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
    system("dot -Tpng automate_deterministe.dot -o automate_deterministe.png");//system :fonction pour executer les commandes de cmd
    system("start automate_deterministe.png");
}


