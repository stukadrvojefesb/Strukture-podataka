/*
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

struct _Cvor;
typedef struct _Cvor _CVOR;
typedef struct _Cvor* Pozicija;
struct _Cvor
{
	float Element;
	Pozicija Next;
};

int Stvori(Pozicija *);
int Push(Pozicija, float);
int Pop(Pozicija, float*);
int Izracun(float, float, char *, float *);
int ProvjeraOperanda(char*, float *);
int ProvjeraStoga(Pozicija);
int IzracunPosfixa(char *, Pozicija);
int Kontejner(Pozicija);

int main(int argc, char *argv[])
{
	int error = SUCCESS;
	char *fileName = NULL;
	_CVOR _Stog;
	_Stog.Next = NULL;

	fileName = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (fileName == NULL) return ERROR;
	memset(fileName, '\0', BUFFER_LENGTH);

	while (strlen(fileName) == 0)
	{
		printf("\r\n\tUnesite naziv datoteke s posfix izrazom <max %d znakova>: ", BUFFER_LENGTH);
		scanf(" %s", fileName);
	}

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	error = IzracunPosfixa(fileName, &_Stog);
	if (error)
		return error;

	error = ProvjeraStoga(&_Stog);

	if (error)
		printf("\r\ngreska");
	else
	{
		printf("\r\n\tRezultat: %.2f", _Stog.Next->Element);
	}

	Kontejner(_Stog.Next);
	free(fileName);

	printf("\r\n");
	return error;
}


int Stvori(Pozicija *head)
{
	Pozicija q = NULL;

	*head = (Pozicija)malloc(sizeof(_CVOR));
	if (*head == NULL) return ERROR;

	q = *head;
	q->Next = NULL;

	return SUCCESS;
}

int Push(Pozicija P, float x)
{
	int err = SUCCESS;
	Pozicija q = NULL;

	err = Stvori(&q);
	if (err) return err;

	q->Element = x;

	q->Next = P->Next;
	P->Next = q;

	return err;
}

int Pop(Pozicija P, float *x)
{
	Pozicija tmp = NULL;

	tmp = P->Next;
	if (tmp == NULL) return ERROR;

	P->Next = tmp->Next;
	*x = tmp->Element;
	free(tmp);

	return SUCCESS;
}

int Izracun(float x, float y, char *operation, float *rez)
{
	int error = SUCCESS;
	if (operation == NULL || strlen(operation) == 0)
		return ERROR;

	if (strcmp(operation, "+") == 0)
	{
		*rez = x + y;
	}
	else if (strcmp(operation, "-") == 0)
	{
		*rez = x - y;
	}
	else if (strcmp(operation, "*") == 0)
	{
		*rez = x * y;
	}
	else if (strcmp(operation, "/") == 0)
	{
		if (y < 0)
		{
			*rez = 0;
			printf("\r\n\t\tNe mozemo dijelit s nulom");
			error = ERROR;
		}
		else
		{
			*rez = x / y;
		}
	}
	else
	{
		*rez = 0;
		printf("\r\n\t\tNe valja operacija");
		error = ERROR;
	}

	return error;
}

int ProvjeraOperanda(char *buff, float *number)
{
	int rez = SUCCESS;

	rez = sscanf(buff, " %f", number);
	if (rez == EOF || rez == 0 || rez != 1) return ERROR;

	return SUCCESS;
}

int IzracunPosfixa(char *fileName, Pozicija S)
{
	int error = SUCCESS;
	float number = 0;
	float operand1 = 0;
	float operand2 = 0;
	char *buff = NULL;
	FILE *fp = NULL;

	buff = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (buff == NULL) return ERROR;
	memset(buff, '\0', BUFFER_LENGTH);

	fp = fopen(fileName, "r");
	if (fp == NULL) return ERROR;

	while (!feof(fp))
	{
		memset(buff, 0, BUFFER_LENGTH);
		fscanf(fp, " %s", buff);
		if (strlen(buff) == 0) continue;

		if (SUCCESS != ProvjeraOperanda(buff, &number))
		{
			error = Pop(S, &operand2);
			if (error) break;

			error = Pop(S, &operand1);
			if (error) break;

			error = Izracun(operand1, operand2, buff, &number);
			if (error) break;

		}
		error = Push(S, number);
		if (error) break;
	}

	fclose(fp);

	if (error)
		printf("\r\nPOSTFIX greska!");

	return error;
}

int ProvjeraStoga(Pozicija S)
{
	if (S == NULL) return ERROR;

	if (S->Next == NULL) return ERROR;

	if (S->Next->Next != NULL) return ERROR;

	return SUCCESS;
}

int Kontejner(Pozicija S)
{
	if (S == NULL) return SUCCESS;

	Kontejner(S->Next);
	free(S);
	return SUCCESS;
}
