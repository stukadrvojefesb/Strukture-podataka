//11. Zadatak

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#ifndef BUFFER
#define BUFFER_LENGTH 1024
#endif

#ifndef N
#define N_LENGTH 1024
#endif

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

typedef struct Student* Pozicija;
typedef struct Student* Lista;
typedef struct hashTablica* hashTab;

struct Student {
    int maticniBroj;
    char ime[N_LENGTH];
    char prezime[N_LENGTH];
    Pozicija Next;
};

struct hashTablica {
    int velicinaTablice;
    Lista* hashLista;
};

int CitajIzDat(Pozicija);
Pozicija StvoriNovogS(void);
int IzracunajHashKljuc(char*, int);
hashTab InicijalizacijaTablice(int);
int UpisuHashTablicu(Pozicija, hashTab);
int IspisHashTablice(hashTab);
int IspisPojedinacnogStudenta(hashTab);
Pozicija TraziStudentaPoMatBr(hashTab, int);

int main()
{
    struct Student HeadS;
    hashTab HeadT;
    int velicinaTablice = 11;

    HeadS.Next = NULL;

    if (CitajIzDat(&HeadS) == -1) {
        return ERROR;
    }

    HeadT = InicijalizacijaTablice(velicinaTablice);
    UpisuHashTablicu(HeadS.Next, HeadT);
    IspisHashTablice(HeadT);
    IspisPojedinacnogStudenta(HeadT);

    return 0;
}

Pozicija StvoriNovogS()
{
    Pozicija P = NULL;
    P = (Pozicija)malloc(sizeof(struct Student));
    return P;
}

hashTab InicijalizacijaTablice(int velicinaTablice)
{
    hashTab H = NULL;
    int i = 0;

    H = (hashTab)malloc(sizeof(struct hashTablica));
    if (!H) return NULL;

    H->velicinaTablice = velicinaTablice;

    H->hashLista = (Lista*)malloc(sizeof(Lista) * velicinaTablice);
    if (!H->hashLista) return NULL;

    for (i = 0; i < velicinaTablice; i++)
    {
        H->hashLista[i] = NULL;
    }

    return H;
}


int IzracunajHashKljuc(char* rijec, int velicinaTab)
{
    int hashZbroj = 0;
    int i = 0;

    for (i = 0; i < 5; i++)
        hashZbroj += rijec[i];

    return hashZbroj % velicinaTab;
}


int CitajIzDat(Pozicija P) {

    Pozicija q = NULL, temp = P;
    char* fileName = NULL;
    FILE* fp = NULL;

    fileName = (char*)malloc(sizeof(char) * BUFFER_LENGTH);

    if (!fileName) {
        printf("Greska prilikom alokacije!\n");
        return ERROR;
    }

    printf("\nUnesite datoteku za citanje: ");
    scanf(" %s", fileName);
    
    if(strchr(fileName, '.')==NULL)
        strcat(fileName,".txt");

    fp = fopen(fileName, "r");
    if (!fp) {
        printf("\nDatoteka nije otvorena!\n");
        return ERROR;
    }
    
    while (!feof(fp)) {
        q = StvoriNovogS();
        fscanf(fp, " %d %s %s", &q->maticniBroj, q->ime, q->prezime);
        q->Next = temp->Next;
        temp->Next = q;

        temp = temp->Next;

    }
    fclose(fp);

    return 0;
}

int UpisuHashTablicu(Pozicija P, hashTab H)
{
    int kljuc = 0;
    int velTab = H->velicinaTablice;
    Pozicija temp = NULL;

    while (P != NULL) {

        kljuc = IzracunajHashKljuc(P->prezime, velTab);
        
        if (H->hashLista[kljuc] != NULL)
            H->hashLista[kljuc]->Next = P;
        else
            H->hashLista[kljuc] = P;

        temp = StvoriNovogS();
        temp = P;
        P = P->Next;
        temp->Next = NULL;
    }
    return SUCCESS;
}

int IspisHashTablice(hashTab H)
{
    int i = 0;
    int velTab = H->velicinaTablice;
    Pozicija P = NULL;
    P = StvoriNovogS();

    if (!H) return ERROR;

    printf("\n\n\t%10s %10s %10s %10s\n", "Br. kljuca", "Maticni br.", "Prezime", "Ime");

    for (i = 0; i < velTab; i++)
    {
        if (H->hashLista[i] == NULL) continue;
        else {
            P = H->hashLista[i];
            while (P != NULL) {
                printf("\t%10d %10d %10s %10s\n", i, P->maticniBroj, P->prezime, P->ime);
                P = P->Next;
            }
        }
    }

    printf("\n\n");

    return SUCCESS;
}

int IspisPojedinacnogStudenta(hashTab H)
{
    char unos[64];
    int unosINT = 0;
    Pozicija P = StvoriNovogS();

    while (1) {
        printf("Unesite maticni broj trazenog studenta ili 0 za izlaz: ");
        scanf("%s", unos);

        if (isdigit(unos[0]) == 0) continue;

        unosINT = atoi(unos);
        if (unosINT == 0) break;

        P = TraziStudentaPoMatBr(H, unosINT);

        if (!P) {
            printf("Nismo nasli studenta s tim maticnim brojem!\n");
            continue;
        }
        printf("Trazeni student s maticnim brojem [%s] je: %s %s\n\n", unos, P->prezime, P->ime);
    }
    printf("\n\n");
    
    return SUCCESS;
}

Pozicija TraziStudentaPoMatBr(hashTab H, int unos)
{
    int velTab = H->velicinaTablice;
    int i = 0;
    Pozicija P = NULL;

    P = StvoriNovogS();

    for (i = 0; i < velTab; i++)
    {
        if (H->hashLista[i] == NULL) continue;
        else {
            P = H->hashLista[i];
            while (P != NULL) {
                if (P->maticniBroj == unos) {
                    return P;
                }
                P = P->Next;
            }
        }
    }

    return NULL;
}
