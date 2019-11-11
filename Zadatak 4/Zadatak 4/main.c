//
//  main.c
//  Zadatak 4
//
//  Created by Luka Mrduljaš on 11/11/2019.
//  Copyright © 2019 Luka Mrduljaš. All rights reserved.
//

#ifndef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ERROR
#define ERROR 1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef BUFFER
#define BUFFER 1024
#endif

struct node;
typedef struct node _node;
typedef struct node* position;
struct node{
  int koeficijent, eksponent;
  position next;
};

int ReadFromFileSort(position);
int CreateNode(position *);
int AddPoly(position, position, position);
int MultiplyPoly(position);
int PrintPoly(position);

int main(int argc, char *argv[])
{
  int err = SUCCESS;
  _node p1, p2, s;
  p1.next = NULL;
  p2.next = NULL;
  s.next = NULL;

  printf("\tPolinom 1:\n");
  err = ReadFromFileSort(&p1);
  if(err) return err;
  printf("\r\n\tP1(x) = ");
  err = PrintPoly(p1.next);
  if(err) return err;

  printf("\n\n\tPolinom 2:\n");
  err = ReadFromFileSort(&p2);
  if(err) return err;
  printf("\r\n\tP2(x) = ");
  err = PrintPoly(p2.next);
  if(err) return err;
  printf("\n");

  printf("\r\n\tSuma polinoma");
  printf("\r\n\tS(x) = ");
  AddPoly(p1.next, p2.next, &s);
  if (err) return err;
  PrintPoly(s.next);
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


int ReadFromFileSort(position p)
{
  int err = SUCCESS;
  FILE *fp = NULL;
  char *filename = NULL;
  position q = NULL;
  position temp = NULL;

  filename = (char*)malloc(BUFFER * sizeof(char));
  if(filename == NULL) return ERROR;
  memset(filename, '\0', BUFFER);

  printf("Unesi ime filea za citanje: ");
  scanf(" %s", filename);
  if(strchr(filename, '.')==NULL)
    strcat(filename, ".txt");

  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("\n\tDatoteka %s nije otvorena!",filename);
    return ERROR;
  }

  while(!feof(fp)){
    err = CreateNode(&q);
    if (err)
        {
            printf("\n\tMemorija nije alocirana!");
            break;
        }

    fscanf(fp, " %d %d", &q->koeficijent, &q->eksponent);

    temp = p;

    while(temp->next!=NULL && temp->next->eksponent < q->eksponent)
      temp = temp->next;

    if(temp->next!=NULL && temp->next->eksponent == q->eksponent)
    {
      temp->next->koeficijent *= q->koeficijent;
      free(q);

      if(temp->next->koeficijent == 0)
      {
        q = temp->next;
        temp->next = q->next;

        free(q);
      }

    }
    else{
      q->next = temp->next;
      temp->next = q;
    }
  }

  fclose(fp);
  return SUCCESS;

}

int PrintPoly(position p)
{
  int first = 1;
  while(p!=NULL){
    if(first){
      printf(" %dx^%d", p->koeficijent, p->eksponent);
      first=0;
    }
    else{
      if(p->koeficijent > 0)
        printf(" + %dx^%d", p->koeficijent, p->eksponent);
      else printf(" %dx^%d", p->koeficijent, p->eksponent);
    }
    p = p->next;
  }
  return SUCCESS;
}

int AddPoly(position p1, position p2, position s)
{
  int err = SUCCESS;
  position q = NULL;
  position temp = NULL;

  while(p1!=NULL && p2!=NULL)
  {
    err = CreateNode(&q);
    if (err)
    {
      printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
      break;
    }
    if(p1->eksponent > p2->eksponent)
    {
      q->eksponent = p1->eksponent;
      q->koeficijent = p1->koeficijent;
      p1 = p1->next;
    }
    else if(p2->eksponent > p1->eksponent)
    {
      q->eksponent = p2->eksponent;
      q->koeficijent = p2->koeficijent;
      p2 = p2->next;
    }
    else
    {
      q->eksponent = p1->eksponent;
      q->koeficijent = p1->koeficijent + p2->koeficijent;
      p1 = p1->next;
      p2 = p2->next;
    }

    q->next=s->next;
    s->next=q;
    s=q;

  }
  if(p1!=NULL)
    temp = p1;
  if(p2!=NULL)
    temp = p2;
  while(temp!=NULL)
  {
    err = CreateNode(&q);
    if (err)
    {
      printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
      break;
    }
    q->eksponent = temp->eksponent;
    q->koeficijent = temp->koeficijent;

    q->next=s->next;
    s->next=q;
    s=q;
    
    temp = temp->next;
  }
  return err;
}

