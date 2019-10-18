#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_LENGTH 1024
#define MAX_PATH 1025
#define NAME_BUFFER_LENGTH 128

typedef struct _student _STUDENT;
typedef struct _student* _pstud;


struct _student{
	char ime[NAME_BUFFER_LENGTH];
	char prezime[NAME_BUFFER_LENGTH];
	int bodovi;
};

int brojac(char *);
int citac(int, _pstud, char *);
int ispis(int, _pstud, int);

int main()
{
	char* c = NULL;
	int lineN = 0;
    _pstud popis = NULL;
    int maxpoints = 0;

    c = (char)malloc(sizeof(char)*MAX_PATH);

    printf("Unesite ime datoteke: ");
    scanf(" %s", c);

    lineN = brojac(c);

    if(lineN > 0)
    {
        printf("Broj studenata u datoteci: %d\n", lineN);
        popis = (_pstud)malloc(sizeof(_STUDENT)*lineN);
        maxpoints = citac(lineN, popis, c);
        printf("Maksimalni broj bodova: %d", maxpoints);

        ispis(lineN, popis, maxpoints);
    }
    else
        printf("Nema");

	return 0;
}

int brojac(char * fname)
{
    FILE *fp = NULL;
    char *buff = NULL;
    int n = 0;

    fp = fopen(fname, "r");
    buff = (char*)malloc(sizeof(char)BUFFER_LENGTH);

    while(!feof(fp))
    {
        fgets(buff, BUFFER_LENGTH, fp);
        n++;
    }
    fclose(fp);
    return n;
}

int citac(int n, _pstud p, char * fname)
{
    FILE *fp = NULL;
    char *buff = NULL;
    int maxP = 0;

    fp = fopen(fname, "r");
    buff = (char*)malloc(sizeof(char)BUFFER_LENGTH);
    while(!feof(fp))
        {
           fgets(buff, BUFFER_LENGTH, fp);
           fscanf(buff, " %d %s %s", &p->bodovi, p->ime, p->prezime)


        if(p->bodovi > maxP)
            maxP = p->bodovi;
        p++;
        }
        fclose(fp);
        return maxP;
}

int ispis(int n, _pstud p, int maxpoint)
{
    int i = 0;

    for(i = 0; i < n; i++)
    {
        printf("\n\t\t%15s %15s %5d %5d = %6.2f", p->ime, p->prezime, p->bodovi, p->bodovi, maxpoint);
        p++;
    }
}
