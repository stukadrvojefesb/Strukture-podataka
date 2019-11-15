#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 1024
#endif

struct node;
typedef struct node _node;
typedef struct node* position;
struct node{
    int koeficijent;
    position next;
};

int ReadFromFile(position);
int CreateNode(position *);
int Union(position, position, position);
int Presijek(position, position, position);
int PrintList(position);

int main(int argc, char *argv[])
{
	int err = SUCCESS;
	_node x1, x2, P, U;

	x1.next = NULL;
	x2.next = NULL;
	P.next = NULL;
	U.next = NULL;

	printf("\r\n\tLista 1.");
	err = ReadFromFile(&x1);
	if (err)return err;
	printf("\r\n\t\tL1 : ");
	PrintList(x1.next);

	printf("\r\n\tLista 2.");
	ReadFromFile(&x2);
	if (err)return err;
	printf("\r\n\t\tL2 : ");
	PrintList(x2.next);

	err = Presijek(x1.next, x2.next, &P);
	if (err) return err;
	printf("\r\n\t\tPresijek : ");
	PrintList(P.next);

	err = Union(x1.next, x2.next, &U);
	if (err) return err;
	printf("\r\n\t\tUnija : ");
	PrintList(U.next);


	return err;
}


int CreateNode(position *head)
{
  position q = NULL;

  *head = (position)malloc(sizeof(_node));
  if(*head == NULL) return ERROR;

  q = *head;
  q->next = NULL;

  return SUCCESS;
}


int ReadFromFile(position P)
{
	int err = SUCCESS;
	position q = NULL;
	position tmp = NULL;
	char *fileName = NULL;
	FILE *fp = NULL;

	fileName = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (fileName == NULL) return ERROR;
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\r\n\tUnesite ime dadoteke za citanje : ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\r\nGRESKA!\r\n%s datoteka nije otvorena.", fileName);
		return ERROR;
	}

	while (!feof(fp))
	{
		err = CreateNode(&q);
		if (err)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}

		fscanf(fp, " %d", &q->koeficijent);

		tmp = P;
		while (tmp->next != NULL && tmp->next->koeficijent >= q->koeficijent)
			tmp = tmp->next;

		q->next = tmp->next;
		tmp->next = q;
	}
	fclose(fp);

	return err;
}

int PrintList(position P)
{
	while (P != NULL)
	{
		printf(" %d", P->koeficijent);
		P = P->next;
	}

	return SUCCESS;
}

int Union(position x1, position x2, position U)
{
	int err = SUCCESS;
	position q, tmp;

	while (x1 && x2)
	{
		err = CreateNode(&q);
		if (err)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}
		else
		{
			if (x1->koeficijent > x2->koeficijent)
			{
				q->koeficijent = x1->koeficijent;
				x1 = x1->next;
			}
			else if (x1->koeficijent < x2->koeficijent)
			{
				q->koeficijent = x2->koeficijent;
				x2 = x2->next;
			}
			else
			{
				q->koeficijent = x1->koeficijent;
				x1 = x1->next;
				x2 = x2->next;
			}

			if (U->koeficijent == q->koeficijent)
				free(q);
			else
			{
				q->next = U->next;
				U->next = q;
				U = q;
			}
		}
	}

	if (err) return err;

	if (x1)
		tmp = x1;
	else
		tmp = x2;

	while (tmp)
	{
		err = CreateNode(&q);
		if (err)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}

		q->koeficijent = tmp->koeficijent;

		if (U->koeficijent == q->koeficijent)
		{
			free(q);
		}
		else
		{
			q->next = U->next;
			U->next = q;
			U = q;
		}

		tmp = tmp->next;
	}

	return err;
}

int Presijek(position x1, position x2, position P)
{
	int err = SUCCESS;
	position q = NULL;

	while (x1 && x2)
	{
		if (x1->koeficijent > x2->koeficijent)
			x1 = x1->next;
		else if (x1->koeficijent < x2->koeficijent)
			x2 = x2->next;
		else
		{
			err = CreateNode(&q);
			if (err)
			{
				printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
				break;
			}

			q->koeficijent = x1->koeficijent;
			q->next = P->next;
			P->next = q;
			P = q;

			x1 = x1->next;
			x2 = x2->next;
		}
	}

	return err;
}
