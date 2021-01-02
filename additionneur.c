#include <stdio.h>
#include <stdlib.h>


int convertir_entree (char *tab, char *strhexa) { //--- Fonction de conversion d'entrée hexa
    int detecteNonHexa = 0;                                 //Variable de test pour une caractère non hexa
    int compt = 0;                                          //Compteur pour la variable de test, si hexa est de la forme "0x...."", débute le scan après 2

    if (strhexa == NULL)    {
        return 2;                                           //2e erreur : cas où il n'y a pas de valeur pour l'un des 2 hexa à rentrer dans le terminal
    }
    else    {
        if (strhexa[0] == '0' && (strhexa[1] == 'x' || strhexa[1] == 'X'))  {       
            compt = 2;                                                              //Initialise le compteur à 2, si hexa est de la forme "0x...."
        }

        for (compt = compt; strhexa[compt] != '\0'; compt++)    {                   //Detecte une caractère non hexa...     Info : je n'ai pas mis les nombres négatifs
            if ((int)strhexa[compt] >= 71 && (int)strhexa[compt] <= 90) {           //Detecte pour une lettre minuscule, change la valeur de test "detecteNonHexa" sur true et stop la boucle "for"
                detecteNonHexa = 1;
                break;
            }
            else if ((int)strhexa[compt] >= 103 && (int)strhexa[compt] <= 122)  {   //Detecte pour une lettre majuscule, ....
                detecteNonHexa = 1;
                break;
            }
        }

        if (detecteNonHexa) {
            return 3;                                       //3e erreur : cas où un caractère non hexa est detecté
        }
        else    {
            int long base10 = strtol(strhexa, NULL, 16);    //Conversion d'entrée hexa string en long : base16 --> base10 

            for (int i = 15; i >= 0; i--)   {               //Insère dans le tableau, la représentation en base 2
                tab[i] = base10%2;
                base10 = base10/2;
            }

            if (base10 >= 2)    {
            
                return 4;                                   //4e erreur : cas où on peut encore insérer des valeur dans le tableau, non représentable sur 16 bits
            }
            else    {
                return 0;                                   //Fin de la fonction, tout s'est bien déroulé sans erreur
            }
        }
    }
}

char pl_NAND (char A, char B)   { //----- Fonction porte logique NAND
    if (A == 0 && B == 0)   {
        return 1;
    }
    else if (A == 0 && B == 1)  {
        return 1;
    } 
    else if (A == 1 && B == 0)  {
        return 1;
    } 
    else if (A == 1 && B == 1)  {
        return 0;
    }
    return 2;
}

char pl_NOR (char A, char B)    { //----- Fonction porte logique NOR
    if (A == 0 && B == 0)   {
        return 1;
    }
    else if (A == 0 && B == 1)  {
        return 0;
    } 
    else if (A == 1 && B == 0)  {
        return 0;
    } 
    else if (A == 1 && B == 1)  {
        return 0;
    }
    return 2;
}

char pl_XOR (char A, char B)    { //----- Fonction porte logique XOR
    return pl_NAND(pl_NAND(pl_NAND(A, A), B), pl_NAND(pl_NAND(B, B), A));
}

char pl_AND (char A, char B)    { //----- Fonction porte logique XOR
    return pl_NAND(pl_NAND(A, B), pl_NAND(A, B));
}

char pl_OR (char A, char B)     { //------ Fonction porte logique OR
    return pl_NOR(pl_NOR(A, B), pl_NOR(A, B));
}

char pl_NOT (char A)            { //------ Fonction porte logique NOT
    return pl_NOR(A, A);
}

char add_1b (char A, char B, char Cin, char *Cout)  { //----- Function d'addition 1 bit

    Cout[0] = pl_XOR(Cin, pl_XOR(A, B));                        //Calcul de la somme avec la retenue d'entrée

    Cin = pl_OR(pl_AND(pl_XOR(A, B), Cin), pl_AND(A, B));       //Calcul de la retenue de sortie

    Cout[1] = Cin;                                              //Stockage de la retenue de sortie dans le pointeur

    return Cout[0];                                             //Fin de la fonction, retourne de le résultat de la somme
}

char add_16b (char *A, char *B, char *sum)  { //----- Fonction d'additionneur 16 bits
    char C[2];                                          //Initialise un tableau pour le résultat de la somme 1 bit et la retenue
    C[1] = 0;                                           //Initialise la retenue à 0

    for (int i = 15; i >= 0; i--)   {                   //Calcul sur 16 bits des 2 valeurs hexa
        C[0] = add_1b(A[i], B[i], C[1], C);
        sum[i] = C[0];
    }

    sum[16] = '\0';                                     //Fin de la chaîne de caractère

    if (C[1] == 1)   {                                  //Regarde si la retenue de sortie est nulle ou pas, si c'est pas le cas, il y a overflow
        return 1;                                       //Overflow
    }
    else    {
        return 0;                                       //Fin de la function
    }
}

u_int16_t convertir_sortie (char *bits) { //--------- Function de convertion de sortie hexa 
    char base16[4];                                     //Initialise tableau dans le résultat de la conversion
    char save[4];                                       //Tableau de sauvegarde pour la transition
    int j = 0;                                          //Compteur à part pour continuer la lecture de "bits" sans repartir de 0 dans boucle pour "while" dans "for"
    
    for (int i = 0; i < 4; i++) {                       //Récupère 4 bits par 4 bits pour les placer dans le tableau "save"
        int compt = 0;                                      //Compteur 4 bits par 4 bits
        while (compt != 4)  {                               //Insère 4 bits dans le tableau "save" à partir de "bits"
           save[compt] = bits[j];
           compt++;
           j++;
        }
                                                                                    //Converti 4 bits en hexa
        if (save[0] == 0 && save[1] == 0 && save[2] == 0 && save[3] == 0)   {
            base16[i] = '0';
        }
        if (save[0] == 0 && save[1] == 0 && save[2] == 0 && save[3] == 1)   {
            base16[i] = '1';
        }
        if (save[0] == 0 && save[1] == 0 && save[2] == 1 && save[3] == 0)   {
            base16[i] = '2';
        }
        if (save[0] == 0 && save[1] == 0 && save[2] == 1 && save[3] == 1)   {
            base16[i] = '3';
        }
        if (save[0] == 0 && save[1] == 1 && save[2] == 0 && save[3] == 0)   {
            base16[i] = '4';
        }
        if (save[0] == 0 && save[1] == 1 && save[2] == 0 && save[3] == 1)   {
            base16[i] = '5';
        }
        if (save[0] == 0 && save[1] == 1 && save[2] == 1 && save[3] == 0)   {
            base16[i] = '6';
        }
        if (save[0] == 0 && save[1] == 1 && save[2] == 1 && save[3] == 1)   {
            base16[i] = '7';
        }
        if (save[0] == 1 && save[1] == 0 && save[2] == 0 && save[3] == 0)   {
            base16[i] = '8';
        }
        if (save[0] == 1 && save[1] == 0 && save[2] == 0 && save[3] == 1)   {
            base16[i] = '9';
        }
        if (save[0] == 1 && save[1] == 0 && save[2] == 1 && save[3] == 0)   {
            base16[i] = 'A';
        }
        if (save[0] == 1 && save[1] == 0 && save[2] == 1 && save[3] == 1)   {
            base16[i] = 'B';
        }
        if (save[0] == 1 && save[1] == 1 && save[2] == 0 && save[3] == 0)   {
            base16[i] = 'C';
        }
        if (save[0] == 1 && save[1] == 1 && save[2] == 0 && save[3] == 1)   {
            base16[i] = 'D';
        }
        if (save[0] == 1 && save[1] == 1 && save[2] == 1 && save[3] == 0)   {
            base16[i] = 'E';
        }
        if (save[0] == 1 && save[1] == 1 && save[2] == 1 && save[3] == 1)   {
            base16[i] = 'F';
        }
    }
    printf("0x%s", base16);     //Affiche le resultat de la conversion base 2 vers base 16      Info : je n'ai pas réussi à printf de la même manière que sur le poly avec "%x"...
    return 0;                   //Fin de la function
}


int main(int argc, char **argv)  {

    char *val1 = argv[1];                                       //Récupère les entrées du terminal
    char *val2 = argv[2];                                       //Récupère les entrées du terminal

    char tab_val1[16];                                          //Initialise les tableaux pour les futures valeurs binaires ou hexa
    char tab_val2[16];                                          //Initialise les tableaux pour les futures valeurs binaires ou hexa
    char sum[16];                                               //Initialise les tableaux pour les futures valeurs binaires ou hexa

    int convert_val1 = convertir_entree(tab_val1, val1);        //Appelle la function pour la conversion et les potentielles erreurs
    int convert_val2 = convertir_entree(tab_val2, val2);        //Appelle la function pour la conversion et les potentielles erreurs

    if (argc > 3)   {                                           //1e erreur : cas où il y a une valeur en trop en entrée dans le terminal
        convert_val1 = 1;
        convert_val2 = 1;
    }

    if (!convert_val1 && !convert_val2) {                       //Test s'il y a d'éventuelles erreurs, s'il n'y a pas continue...

        for (int i = 0; i < 65; i++)    {                       //Affichage de sortie -----
            printf("-");
        }
        printf("\n");

        printf("1ère valeur = ");                               //Affichage de la 1ère valeur d'entrée en binaire
        for (int i = 0; i < 16; i++)    {
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", tab_val1[i]);
        }
        printf("\n");


        printf("2eme valeur = ");                               //Affichage de la 2eme valeur d'entrée en binaire
        for (int i = 0; i < 16; i++)    {
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", tab_val2[i]);
        }
        printf("\n");


        for (int i = 0; i < 65; i++)    {                       //Affichage de sortie -----
            printf("-");
        }
        printf("\n");


        char overflow = add_16b(tab_val1, tab_val2, sum);       //Valeur de l'overflow

        printf("Le résultat = ");                               //Affichage de la valeur de la somme en hexadécimal
        convertir_sortie(sum);

        printf(" (");
        for (int i = 0; i < 16; i++)    {                       //Affichage de la valeur de la somme en binaire
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", sum[i]);
        }
        printf(") ");

        printf("avec un overflow de %d\n", overflow);           //Affichage de la valeur de l'overflow


        for (int i = 0; i < 65; i++)    {                       //Affichage de sortie -----
            printf("-");
        }
        printf("\n");
    }
    else    {                                                   //Default erreur : cas où il y a eu une erreur dans la conversion d'un des 2 entrées du terminal
        printf("ERREUR : erreur de conversion entrée\n");
    }

    if (convert_val1 == 1 || convert_val2 == 1) {               //1e erreur
        printf("ERREUR : un des paramètres est en trop\n");
    }
    else if (convert_val1 == 2 || convert_val2 == 2) {          //2e erreur
        printf("ERREUR : un des paramètres est manquant\n");
    }
    else if (convert_val1 == 3 || convert_val2 == 3)    {       //3e erreur
        printf("ERREUR : un des paramètres ne représente pas une valeur héxadécimale %c0x....%c\n",'"','"');
    }
    else if (convert_val1 == 4 || convert_val2 == 4)    {       //4e erreur
        printf("ERREUR : un des paramètres n'est pas représentable sur 16 bits\n");
    }

    return 0;       //Fin du programme !
}