#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define duzina 1024

struct student;
typedef struct student _STUDENT;
typedef struct student *position;

struct student {
	char ime[N];
	char prezime[N];
	int godina;
	position next;

};

int odabir();
int stvori(position);
int unesi(position);
int ispis(position);
int dodajElp(position);
int dodajElk(position);
position trazi(position);
int brisi(position);

int main(void)
{
	_STUDENT head;
	int k = 0;
	int j = 0;
	position studentF = NULL;
	head.next = NULL;


	while (k != 5)
	{
		k = 0;
		k = odabir();

		if (k == 1)
		{
			dodajElp(&head);
		}
		else if (k == 2)
		{
			ispis(head.next);
		}
		else if (k == 3)
		{
			dodajElk(&head);
		}
		else if (k == 4)
		{
			studentF = trazi(head.next);
			if (studentF != NULL)
				printf("Trazeni student je: %s %s %d\n", studentF->ime, studentF->prezime, studentF->godina);
			else printf("Nije pronaden.\n");
		}
		else if (k == 5)
		{
			continue;
		}
		else
			printf("Pogresan izbor\n");
	}
	return 0;
}

int odabir()
{
	int n = 0;

	printf("Odaberite redni broj funkcije koju zelite koristiti\n");
	printf("1. Dodaj novi element na poèetak liste\n");
	printf("2. Ispis\n");
	printf("3. Dodaj novi element na kraj\n");
	printf("4. Pronadi element u listi(po prezimenu)\n");
	printf("5. Izlaz iz programa\n");

	scanf(" %d", &n);
	return n;
}

int stvori(position *head)
{
	position q = NULL;

	*head = (position)malloc(sizeof(_STUDENT));
	if (*head == NULL) return -1;

	q = *head;
	q->next = NULL;

	return 0;
}

int unesi(position p)
{
	if (p == NULL) return -1;

	printf("Unesite ime, prezime i godinu rodenja:\n");
	scanf(" %s %s %d\n", p->ime, p->prezime, &p->godina);

	return 0;
}

int dodajElp(position p)
{
	position q = NULL;
	int k = -1;

	k = stvori(&q);
	if (k == -1)
	{
		printf("Greska");
		return -1;
	}

	k = unesi(q);
	if (k == -1)
	{
		printf("Greska");
		return -1;
	}

	q->next = p->next;
	p->next = q;

	return 0;
}

int ispis(position p)
{
	if (p == NULL)
		printf("Lista je prazna\n");
	else
	{
		printf("Lista:\n");
		while (p != NULL)
		{
			printf("%s %s %d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
	return 0;
}

int dodajElk(position p)
{
	if (p == NULL) return NULL;

	while (p->next != NULL)
		p = p->next;

	return dodajElp(p);
}