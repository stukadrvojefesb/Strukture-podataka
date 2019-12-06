#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 1024
#endif

struct Node;
typedef struct Node Node;
typedef struct Node* Position;
struct Node
{
	int Element;
	Position Next;
};

int CreateNew(Position *);
int PrintMenu();
int RandomBroj(int, int);
int PushS(Position, int);
int PushR(Position, int);
int Pop(Position);
int Print(Position);
int Postoji(Position, int);

int main(int argc, char *argv[])
{
	int x = 0;
	char *izbor = NULL;
	struct Node S, R;

	srand((unsigned)time(NULL));
	S.Next = NULL;
	R.Next = NULL;

	izbor = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (izbor == NULL) return ERROR;
	memset(izbor, '\0', BUFFER_LENGTH);

	while (strcmp(izbor, "EXIT") != 0 && strcmp(izbor, "exit") != 0)
	{
		memset(izbor, 0, BUFFER_LENGTH);
		PrintMenu();
		printf("\r\n\tIzbor : ");

		scanf(" %s", izbor);

		if (strcmp(izbor, "1") == 0)
		{
			while (x == 0 || Postoji(S.Next, x))
				x = RandomBroj(10, 10000);
			PushS(&S, x);
			x = 0;
			Print(S.Next);
		}
		else if (strcmp(izbor, "2") == 0)
		{
			Pop(&S);
			Print(S.Next);
		}
		else if (strcmp(izbor, "3") == 0)
		{
			while (x == 0 || Postoji(R.Next, x))
			{
				x = RandomBroj(10, 100);
			}
			PushR(&R, x);
			x = 0;
			Print(R.Next);
		}
		else if (strcmp(izbor, "4") == 0)
		{
			Pop(&R);
			Print(R.Next);
		}
		else if (strcmp(izbor, "EXIT") == 0 || strcmp(izbor, "exit") == 0)
		{
			printf("\r\n\r\nKRAJ\r\n\r\n");
		}
		else
		{
			printf("\r\nPogresan unos\r\n\r\n\r\n");
		}
	}
	free(izbor);

	return SUCCESS;
}

int PrintMenu()
{
	printf("\r\n\t1.\tPush stog");
	printf("\r\n\t2.\tPop stog");
	printf("\r\n\t3.\tPush red");
	printf("\r\n\t4.\tPop red");
	printf("\r\n\texit.\tIzlaz iz programa");

	return SUCCESS;
}

int CreateNew(Position *head)
{
	Position q = NULL;

	*head = (Position)malloc(sizeof(Node));
	if (*head == NULL) return ERROR;

	q = *head;
	q->Next = NULL;

	return SUCCESS;
}

int RandomBroj(int min, int max)
{
	return rand() % (max - min) + min;
}

int Postoji(Position P, int x)
{
	int i = 0;
	while (P != NULL &&  P->Element != x)
		P = P->Next;
	if (P)
		return 1;
	else
		return 0;
}

int PushS(Position P, int x)
{
	int err = SUCCESS;
	Position q = NULL;

	err = CreateNew(&q);
	if (err) return err;

	q->Element = x;

	q->Next = P->Next;
	P->Next = q;

	return err;
}

int PushR(Position P, int x)
{
	int err = SUCCESS;
	static Position last;
	Position q = NULL;

	if (P->Next == NULL)
		last = P;

	err = CreateNew(&q);
	if (err) return err;

	q->Element = x;

	q->Next = last->Next;
	last->Next = q;

	last = q;

	return err;
}

int Pop(Position P)
{
	Position tmp = NULL;

	tmp = P->Next;

	if (tmp == NULL) return ERROR;

	P->Next = tmp->Next;
	printf("\r\nBrise se : %d\r\n", tmp->Element);
	free(tmp);

	return SUCCESS;
}

int Print(Position P)
{
	if (P == NULL)
	{
		printf("\r\nLista je prazna.");
		return SUCCESS;
	}

	printf("\r\nU listi se nalaze :");
	while (P)
	{
		printf(" %d", P->Element);
		P = P->Next;
	}
	printf("\r\n\r\n\r\n");

	return SUCCESS;
}
