#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);

// data
struct record * data = NULL; // Initially NULL.


void init()
{
  init_pool();
}


void add(char *name, char *number)
{
  struct record * q; //curr
  q = new_node();
  if(q==NULL){
    printf("Can't add.  The address book is full!\n");
  }
  else{
    for(int i=0;i<3;i++){
      q->name[i]=name[i];
    }
    for(int j=0;j<4;j++){
      q->number[j]=number[j];
    }
  }
  q->next = data;
	data = q;
   // Error Message for overflow:
  // printf("Can't add.  The address book is full!\n");
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)
    return -1;
  else
    return strncmp(key, r->name, 3);
}


void search(char name[3])
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
  if(r==NULL)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
  struct record *p=NULL;  // previous node pointer
  struct record *q=data; //current node pointer

  if(q==NULL){
    printf("Couldn't find the name.\n");
    return;
  }

  while(q != NULL){
    int cmp_result = compare(name, q);
    if(cmp_result ==0){
      p->next=q->next;
      free_node(q);
      printf("The name was deleted.\n");
    }
    p=q;
    q=q->next;
  }
}


// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
  struct record *r = data;
  while(r!=NULL){
    print_name(r);
    printf(" : ");
    print_number(r);
    printf("\n");
    r=r->next;
  }
}
