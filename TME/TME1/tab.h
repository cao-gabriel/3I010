#define NMAX 10

/*Initialise le tableau tab de taille size précédemment allouée.
Chaque élément du tableau contient une valeur aléatoire entre 0 et 9*/
void InitTab(int *tab, int size);

/*Affiche les valeurs du tableau*/
void PrintTab(int *tab, int size);

/*Retourne la somme des éléments du tableau*/
int SumTab(int *tab, int size);

/*Retourne la somme des éléments du tableau et met dans
la variable min l'élément minimum du tableau*/
int MinSumTab(int *min, int *tab, int size);
