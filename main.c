//10. ZADATAK

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

struct Stablo;
typedef struct Stablo Stablo;
typedef struct Stablo* StabloP;

struct Stog;
typedef struct Stog Stog;
typedef struct Stog* Pozicija;

struct Stablo
{
    char* El;
    StabloP Left;
    StabloP Right;
};

struct Stog
{
    StabloP Cvor;
    Pozicija Next;
};

Pozicija StvoriNoviStog(void);
StabloP ReadFromFile(char*, StabloP, Pozicija);
StabloP StvoriNovoStablo(void);
int Push(Pozicija, StabloP);
StabloP Pop(Pozicija);
int Print(StabloP);

int main()
{
    StabloP S = NULL;
    Pozicija P = NULL;
    char *filename;
    
    filename = (char*)malloc(sizeof(char) * 50);

    P = StvoriNoviStog();
    printf("Unesite ime datoteke iz koje zelite citati postfix izraz:\r\n");
    scanf(" %s", filename);
    
    if(strchr(filename, '.')==NULL)
        strcat(filename, ".txt");

    S = ReadFromFile(filename, S, P);
    
    Print(S);

    return 0;
}

Pozicija StvoriNoviStog()
{
    Pozicija q = NULL;
    q = (Pozicija)malloc(sizeof(Stog));

    if (q == NULL)
    {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }

    q->Cvor = NULL;
    q->Next = NULL;

    return q;
}

StabloP StvoriNovoStablo()
{
    StabloP q = NULL;
    q = (StabloP)malloc(sizeof(Stablo));

    if (q == NULL)
    {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }

    q->El = (char*)malloc(5 * sizeof(char));
    q->Left = NULL;
    q->Right = NULL;

    return q;
}

StabloP ReadFromFile(char* filename, StabloP S, Pozicija P)
{
    FILE* fp = NULL;
    char* buffer;
    buffer = (char*)malloc(sizeof(char) * 50);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Greska");
        return NULL;
    }

    while (!feof(fp))
    {
        memset(buffer, 0, 50);
        fscanf(fp, " %s", buffer);
        if (buffer[0] != '\n' && buffer[0] != '\0')
        {
            S = StvoriNovoStablo();
            sscanf(buffer, " %s", S->El);
            if (atoi(S->El) || isalpha(S->El[0]))
            {
                Push(P, S);
            }
            else
            {
                S->Right = Pop(P);
                S->Left = Pop(P);
                Push(P, S);
            }
        }
        else continue;
    }

    fclose(fp);
    free(buffer);

    return S;
}

StabloP Pop(Pozicija P)
{
    Pozicija temp = NULL;
    StabloP q = NULL;

    if (P->Next == NULL)
    {
        printf("Greska!");
        return NULL;
    }
    
    temp = P->Next;
    
    P->Next = temp->Next;
    q = temp->Cvor;
    free(temp);
    
    return q;
}

int Push(Pozicija P, StabloP S)
{
    Pozicija q = NULL;
    q = StvoriNoviStog();
    
    if(q==NULL)
        return ERROR;

    q->Cvor = S;
    q->Next = P->Next;
    P->Next = q;

    return SUCCESS;
}

int Print(StabloP S)
{
    if (S != NULL)
    {
        if (!atoi(S->El) || isalpha(S->El[0]))
            printf("(");

        Print(S->Left);
        printf(" %s ", S->El);
        Print(S->Right);

        if (!atoi(S->El) || isalpha(S->El[0]))
            printf(")");
    }
    return SUCCESS;
}
