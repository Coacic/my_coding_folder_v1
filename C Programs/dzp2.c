#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node *next;
};

struct node *vrh = NULL;

void push(int vrednost)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = vrednost;
    temp->next = vrh;
    vrh = temp;
}

void pop()
{
    struct node *temp;
    if (temp == NULL)
    {
        printf("Nema elemenata za POP\n");
    }
    else
    {
        temp = vrh;
        vrh = vrh->next;
        temp->next = NULL;
        free(temp);
    }
}

void Izracunaj(char op)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp = vrh;
    vrh = vrh->next;
    int rezultat;
    if (op == '+')
    {
        int rezultat = vrh->data + temp->data;
        printf("Zbir brojeva %d i %d iznosi: %d\n", vrh->data, temp->data, rezultat);
        vrh = temp;
        vrh = vrh->next;
        vrh->data = rezultat;
        vrh = temp;
        pop();
    }
    else if (op == '-')
    {
        int rezultat = vrh->data - temp->data;
        printf("Oduzimanje brojeva %d i %d iznosi: %d\n", vrh->data, temp->data, rezultat);
        vrh = temp;
        vrh = vrh->next;
        vrh->data = rezultat;
        vrh = temp;
        pop();
    }
    else if (op == '*')
    {
        int rezultat = vrh->data * temp->data;
        printf("Mnozenje brojeva %d i %d iznosi: %d\n", vrh->data, temp->data, rezultat);
        vrh = temp;
        vrh = vrh->next;
        vrh->data = rezultat;
        vrh = temp;
        pop();
    }
    else if (op == '/')
    {
        int rezultat = vrh->data / temp->data;
        printf("Deljenje brojeva %d i %d iznosi: %d\n", vrh->data, temp->data, rezultat);
        vrh = temp;
        vrh = vrh->next;
        vrh->data = rezultat;
        vrh = temp;
        pop();
    }
    else if (op == '^')
    {
        int rezultat = pow(vrh->data, temp->data);
        printf("Broj %d na %d iznosi: %d\n", vrh->data, temp->data, rezultat);
        vrh = temp;
        vrh = vrh->next;
        vrh->data = rezultat;
        vrh = temp;
        pop();
    }
}

void traverse()
{
    struct node *temp;
    if (vrh == NULL)
    {
        printf("Stack je prazan\n");
    }
    else
    {
        temp = vrh;
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    int i, j, broj, brojPromenljivih, brojac = 0, br = 0, counter2 = 0, counter3 = 0, inkrement = 0, isAlphabet, duzinaIzraza, izbor, inkrement2 = 0;
    int vrednost, CharacterCounter, k = 0, l = 0, counterFinal = 0, isProm = 0, isIzraz = 0, counter4 = 0;
    int niz[26];
    char Izraz[100], array[26], nizKaraktera[26];
    char karakter, zeljenaprom;
    char op;
    char privremeniChar[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    while (2 > 1)
    {
        printf("----------------------------------------------------------------------------------------\n0. Izlazak programa\n1. Unos promenljivih vrednosti\n2. Unos datog izraza u postfiksnoj notaciji\n3. Ispisivanje rezultata\n4. Promena promenljivih vrednosti\n5. Promena datog izraza u postfiksnoj notaciji\n----------------------------------------------------------------------------------------\n");
        printf("Izaberite opciju:\n");
        scanf("%d", &izbor);
        if (izbor == 1)
        {
            isProm = 1;
        }
        else if (izbor == 2)
        {
            isIzraz = 1;
        }
        if (izbor == 5)
        {
            izbor = 2;
        }

        switch (izbor)
        {
        case 0:
            return 0;
        case 1:
            printf("Koliko zelite promenljivih?\n");
            scanf("%d", &brojPromenljivih);
            for (i = 0; i < brojPromenljivih; i++)
            {
                printf("Unesite promenljivu i njenu vrednost:\n");
                scanf(" %c", &karakter);
                scanf("%d", &broj);
                printf("Prom: %c\n", karakter);
                printf("Broj: %d\n", broj);
                for (j = 0; j < 26; j++)
                {
                    if (privremeniChar[j] == karakter)
                    {
                        brojac++;
                        array[inkrement2] = karakter;
                        inkrement2++;
                        niz[inkrement] = broj;
                        inkrement++;
                        printf("%c ", privremeniChar[j]);
                        printf("%d\n", niz[j]);
                        break;
                    }
                }
            }
            isProm == 1;
            break;
        case 2:
            if (isProm == 1)
            {
                while (1)
                {
                    printf("Unesite izraz:\n");
                    scanf("%s", Izraz);
                    duzinaIzraza = strlen(Izraz);
                    counter2 = 0;
                    counter3 = 0;
                    counter4 = 0;
                    CharacterCounter = 0;
                    counterFinal = 0;
                    for (i = 0; i < duzinaIzraza; i++)
                    {
                        isAlphabet = 1;
                        br = 0;
                        for (int j = 0; j < 26; j++)
                        {
                            if (privremeniChar[j] == Izraz[i])
                            {
                                br++;
                                counter4++;
                                nizKaraktera[CharacterCounter] = Izraz[i];
                                CharacterCounter++;
                                break;
                            }
                        }
                        if (br == 0)
                        {
                            isAlphabet = 0;
                        }

                        if (isAlphabet == 1)
                        {
                            counter2++;
                        }
                        else
                        {
                            counter3++;
                        }
                    }
                    if (brojac == counter2)
                    {
                        for (k = 0; k < brojac; k++)
                        {
                            for (l = 0; l < CharacterCounter; l++)
                            {
                                if (array[k] == nizKaraktera[l])
                                {
                                    counterFinal++;
                                }
                            }
                        }
                        if (counterFinal == CharacterCounter)
                        {
                            printf("Dati izraz je ispravno unet!\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("Dati izraz je neispravno unet\n");
                    }
                }
            }
            else
            {
                printf("Morate uneti vrednosti promenljivih prvo\n");
                break;
            }
            break;
        case 3:
            if (isIzraz == 1 && isProm == 1)
            {
                if (counter2 == counter3 + 1)
                {
                    inkrement = 0;
                    for (i = 0; i < duzinaIzraza; i++)
                    {
                        isAlphabet = 1;
                        br = 0;
                        for (int j = 0; j < 26; j++)
                        {
                            if (privremeniChar[j] == Izraz[i])
                            {
                                br++;
                                break;
                            }
                        }
                        if (br == 0)
                        {
                            isAlphabet = 0;
                        }

                        if (isAlphabet == 1)
                        {
                            push(niz[inkrement]);
                            inkrement++;
                        }
                        else if (isAlphabet == 0)
                        {
                            Izracunaj(Izraz[i]);
                        }
                    }
                }
            }
            else if (isProm == 0 && isIzraz == 1)
            {
                printf("Morate prvo uneti vrednost promenljivih!\n");
            }
            else
            {
                printf("Morate prvo uneti vrednost izraza!\n");
            }
            break;
        case 4:
            if (isProm == 1)
            {
                printf("Koju promenljivu zelite da promenite?\n");
                scanf(" %c", &zeljenaprom);

                for (i = 0; i < strlen(array); i++)
                {
                    if (zeljenaprom == array[i])
                    {
                        scanf("%d", &vrednost);
                        niz[i] = vrednost;
                    }
                }
            }
            else
            {
                printf("Morate prvo uneti vrednosti promenljivih");
            }
            break;
        default:
            printf("Uneli ste pogresnu vrednost, probajte ponovo\n");
            break;
        }
    }
}