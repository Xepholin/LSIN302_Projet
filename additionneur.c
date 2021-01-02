#include <stdio.h>
#include <stdlib.h>


int convertir_entree (char *tab, char *strhexa) {
    int detecteNonHexa = 0;
    int compt = 0;

    if (strhexa == NULL)    {
        return 2;
    }
    else    {
        if (strhexa[0] == '0' && (strhexa[1] == 'x' || strhexa[1] == 'X'))  {
            compt = 2;
        }

        for (compt = compt; strhexa[compt] != '\0'; compt++)    {
            if ((int)strhexa[compt] >= 71 && (int)strhexa[compt] <= 90) { 
                detecteNonHexa = 1;
                break;
            }
            else if ((int)strhexa[compt] >= 103 && (int)strhexa[compt] <= 122)  {
                detecteNonHexa = 1;
                break;
            }
        }

        int long base10 = strtol(strhexa, NULL, 16);

        if (detecteNonHexa) {
            return 3;
        }
        else    {
            for (int i = 15; i >= 0; i--)   {
                tab[i] = base10%2;
                base10 = base10/2;
            }

            if (base10 >= 2)    {
                
                return 4;
            }
            else    {
                return 0;
            }
        }
    }
}

char pl_NAND (char A, char B)   {
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

char pl_NOR (char A, char B)    {
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

char pl_XOR (char A, char B)    {
    return pl_NAND(pl_NAND(pl_NAND(A, A), B), pl_NAND(pl_NAND(B, B), A));
}

char pl_AND (char A, char B)    {
    return pl_NAND(pl_NAND(A, B), pl_NAND(A, B));
}

char pl_OR (char A, char B) {
    return pl_NOR(pl_NOR(A, B), pl_NOR(A, B));
}

char pl_NOT (char A)    {
    return pl_NOR(A, A);
}

char add_1b (char A, char B, char Cin, char *Cout)  {

    Cout[0] = pl_XOR(Cin, pl_XOR(A, B));

    Cin = pl_OR(pl_AND(pl_XOR(A, B), Cin), pl_AND(A, B));

    Cout[1] = Cin;

    return Cout[0];
}

char add_16b (char *A, char *B, char *sum)  {
    char Cout[2];
    Cout[1] = 0;

    for (int i = 15; i >= 0; i--)   {
        Cout[0] = add_1b(A[i], B[i], Cout[1], Cout);
        sum[i] = Cout[0];
    }

    sum[16] = '\0';

    if (Cout[1] == 1)   {
        return 1;
    }
    else    {
        return 0;
    }
    return 2;
}

u_int16_t convertir_sortie (char *bits) {
    char base16[4];
    char save[4];
    int j = 0;
    
    for (int i = 0; i < 4; i++) {
        int compt = 0;
        while (compt != 4)  {
           save[compt] = bits[j];
           compt++;
           j++;
        }
        
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
    printf("0x%s", base16);
    return 0;
}


int main(int argc, char **argv)  {

    char *val1 = argv[1];
    char *val2 = argv[2];

    char tab_val1[16];
    char tab_val2[16];
    char sum[16];

    int convert_val1 = convertir_entree(tab_val1, val1);
    int convert_val2 = convertir_entree(tab_val2, val2);

    if (!convert_val1 && !convert_val2) {

        for (int i = 0; i < 65; i++)    {
            printf("-");
        }
        printf("\n");

        printf("1ère valeur = ");
        for (int i = 0; i < 16; i++)    {
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", tab_val1[i]);
        }
        printf("\n");


        printf("2eme valeur = ");
        for (int i = 0; i < 16; i++)    {
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", tab_val2[i]);
        }
        printf("\n");


        for (int i = 0; i < 65; i++)    {
            printf("-");
        }
        printf("\n");


        char overflow = add_16b(tab_val1, tab_val2, sum);

        printf("Le résultat = ");
        convertir_sortie(sum);

        printf(" (");
        for (int i = 0; i < 16; i++)    {
            if (i%4 == 0 && i != 0) {
                printf(" ");
            }
            printf("%d", sum[i]);
        }
        printf(") ");

        printf("avec un overflow de %d\n", overflow);


        for (int i = 0; i < 65; i++)    {
            printf("-");
        }
        printf("\n");
    }
    else    {
        printf("ERREUR : erreur de conversion entrée\n");
    }

    if (convert_val1 == 2 || convert_val2 == 2) {
        printf("ERREUR : un des paramètres est manquant\n");
    }
    else if (convert_val1 == 3 || convert_val2 == 3)    {
        printf("ERREUR : un des paramètres ne représente pas une valeur héxadécimale %c0x....%c\n",'"','"');
    }
    else if (convert_val1 == 4 || convert_val2 == 4)    {
        printf("ERREUR : un des paramètres n'est pas représentable sur 16 bits\n");
    }

    return 0;
}