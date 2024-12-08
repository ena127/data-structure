#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

enum state {DISCOVERED, UNDISCOVERED, PROCESSED};
enum state states[N] = {UNDISCOVERED,};
int parent[N] = {-1,};


int BFS(int s, int t)
{
  struct node *p;
  int queue[N] = {0,};
  int f= -1; //front
  int r = 0; //rear
  int current;

  for (int i = 0; i < N; i++) {
    states[i] = UNDISCOVERED;
    parent[i] = -1;
  }

  states[s] = DISCOVERED;//root marking as 'discovered'
  queue[r++] = s;  // push(start)

  while (f<r){ // underflow check
    current = queue[f++]; //pop()
    p = adj_list[current];
    while (p!=NULL){
      int v = p->index;
      if (states[v] == UNDISCOVERED){
        states[v] = DISCOVERED;
        queue[r++] = v;
        parent[v] = current;
        if (v == t){
          return v;
        }
      }
      p=p->next;
    }
    states[current] = PROCESSED;
  }
  return -1;
}

void print_path(int s, int t)
{
  int path[N];
  int v = t;
  int i = 0;
  while(v!=s){
    path[i++] = v;
    v = parent[v];
  }
  path[i] = s;
  int j = 0;
  while(i>=0){
    printf("          %d ", j);
    print_word(path[i--]);
    printf("\n");
    j++;
  }

}


void find_path(char start[5], char goal[5])
{
  int i,j,k,l;
  
  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else {
    k = BFS(i,j);
    if (k == -1) {
      printf("Sorry. There is no path from ");
      print_five_chars(start);
      printf(" to ");
      print_five_chars(goal);
      printf(".\n");
    }
    else {
      print_path(i,j);
    }
  }
}

