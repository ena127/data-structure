#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for delay()

#define N 5757

// words of 5 letters
char word[N][5];

// adjacency matrix
char adj_mat[N][N];


// Function declarations
void print_word();
void init_data();
void init_adj_mat();



/********* For adjacency list and queue,
           we need node structure and its memory pool.
********************************************/
// record structure
struct node {
  int index;
  struct node * next;
};

#define POOL_SIZE 6*5757  // What is an appropriate size?  The average degree
			  // is about 5.  So this must be enough.

// pool of memory
struct node pool[POOL_SIZE];
struct node * top=pool;  // a pointer variable for stack top.

// Still use the same memory management.
void init_pool() // Initialize the pool.
{
  int i;
  struct node *r=pool;
  struct node *s;

  pool[POOL_SIZE-1].next=NULL;

  for(i=1;i<POOL_SIZE;i++) {
    s=r++;
    s->next=r;
  }
}

// When calling new_node(), make sure to check if it returns NULL.
struct node * new_node()
{
  struct node *r;

  if(top==NULL)
    return NULL;

  r=top;
  top=r->next;
  return r;
}

// Push a node to the pool.
void free_node(struct node *r)
{
  r->next=top;
  top=r;
}

/***************** End of Memory Mananagement *********************/






/***************** adjacency list *******************/
struct node * adj_list[N];

void init_adj_list()
{
  int i,j;
  struct node *p;

  for (i=0; i<N; i++)
    adj_list[i]=NULL;

  for (i=0; i<N; i++)
    for (j=N-1; j>=0; j--)    // a new node is put in front.  To make the
			      // list in ascending order, we check the
			      // vertices in reverse order.
      if (adj_mat[i][j]) {
	      p=new_node();
	      p->index=j;
	      p->next=adj_list[i];
	      adj_list[i]=p;
      }
  printf("Adjacency list was successfully constructed!\n");
}



void init_data()
{
  int i;
  FILE *f;

  if ((f=fopen("words.dat", "r")) == NULL)
    printf("Sorry, I can't open words.dat.\n");

  // skip the first four lines
  for (i=1; i<=4; i++) {
    while (getc(f)!='\n');
  }

  // start reading data
  for (i=0; i<N; i++) {
    fscanf(f, "%5c", word[i]);
    while (getc(f)!='\n');
  }

  printf("All the words were successfully read!\n");
  fclose(f);
}

int adjacent(char u[5], char v[5])
{
  int i, check=0;

  for (i=0; i<5; i++)
    if (u[i]!=v[i]) check++;

  if (check==1)
    return 1;
  else
    return 0;
}

void init_adj_mat()
{
  int i,j,l;

  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      adj_mat[i][j]=adjacent(word[i],word[j]);

  printf("Adjacency matrix was successfully constructed!\n");
}


void print_word(int k)
{
  int i;
  if(0<=k && k<N) {
    for (i=0; i<5; i++)
      putchar(word[k][i]);
  }
  else
    printf("ERROR: print_word() received a k=%d which is out of bound!\n", k);
}




/* u-v */
int compare(char u[5], char v[5])
{
  return strncmp(u, v, 5);
}

// Sequential search.
// Returns the index of the found record. (between 0 and N-1)
// Returns -1, if not found.
int search_index(char key[5])
{
  int m = 0; // middle
  int l=0; // lowest value
  int r = N-1; //highest value

  // binary search 
  while (l<=r){
    m = (l+r)/2;
    if (compare(key,word[m])>0){
      l= m+1;
    }
    else if (compare(key,word[m])<0){
      r = m-1;
    }
    else{
      return m; // success
    }
  }
  return -1; // unsuccess
  
}


/********** Homework 8 *****************/
void hw8()
{
  printf("Ha ha ha.  Let's do homework!!!\n" );
  // You may use this space for your homework :)
  print_word(38);

  printf("Ok!  I am doing homework!!!\n");
  char hello[5] = "hello";
  char graph[5] = "graph";
  struct node *p = adj_list[search_index(hello)];
  struct node *q = adj_list[search_index(graph)];
  int counter = 0;


  // 1 -(a)
  printf("#1\n");
  printf("(a) : The words adjacent to 'hello'\n");
  while(p!=NULL){
    counter++;
    print_word(p->index);
    printf("  ");
    p= p->next;
  }
  printf("\n");
  printf("The degree of the word 'hello' is : %d\n", counter);


  // 1 -(b)
  counter = 0; // init counter
  printf("(b) : The words adjacent to 'graph'\n");

  while(q!=NULL){
    counter++;
    print_word(q->index);
    printf("  ");
    q=q->next;
  }
  printf("\n");
  printf("(b) : The degree of the word 'graph' is : %d\n", counter);

  // 2 & 3
  printf("#2\n");
  int degree[N] = {0,};
  int degreeList[N] = {0, };
  struct node *r = NULL;

  for(int i=0; i<N; i++){
    counter = 0;
    r = adj_list[i];
    while (r!=NULL){
      counter++;
      r = r->next;
    }
    degree[i] = counter;
    degreeList[counter]++;
  }

  int max_degree = degree[0];

  for(int i=1; i<N; i++){ //degree 배열에서 max_degree 찾기
    if(max_degree<degree[i]){
      max_degree = degree[i];
    }
  }

  for(int i=0; i<max_degree+1; i++){ //max_degree까지의 각 degree별 단어 개수 출력
    printf("%d : %d\n", i, degreeList[i]);
  }
  printf("#3\n");
  printf("The maximum degree is %d.\n",max_degree);

  //4
  printf("#4\n");
  printf("The words that have the maximum degree.\n");

  for(int i=0; i<N; i++){
    counter = 0;
    r = adj_list[i];
    while (r!=NULL){
      counter++;
      r = r->next;
    }
    degree[i] = counter;

    if(max_degree == counter){
      print_word(i);
      printf("  ");
    }
  }

  //5
  printf("\n#5.\n");

  float avg_degree=0; //평균 degree 저장할 변수
  int tmp=0; // 평균 degree 계산위해 사용되는 임시변수
  int nodes_cnt = 0; //노드의 개수

  for(int i=0; i<max_degree+1; i++){
    tmp = i * degreeList[i];
    avg_degree += tmp;
  }
  avg_degree = avg_degree / N;
  printf("The average degree is %f.\n", avg_degree);

  //6
  printf("#6\n");
  for (int i=0; i<N; i++){
    nodes_cnt += degree[i];
  }
  printf("Adjacent list have %d nodes.\n", nodes_cnt);

  //7
  printf("#7\n");
  float min_pool = 0;
  min_pool = avg_degree * N;
  printf("The minimum possible size required of POOL SIZE is %f.\n", min_pool);




}


// All the initializations
void init()
{
  init_data();
  init_adj_mat();
  init_pool();
  init_adj_list();
  hw8();
}


void find_path(char start[5], char goal[5])
{
  int i,j,k,l;

  i=search_index(start);
  j=search_index(goal);

  if (i<0) printf("Sorry. %5s is not in the dictionary.", start);
  else if (j<0) printf("Sorry. %5s is not in the dictionary.", goal);
  else {
    printf("Hmm... I am trying to figure out the shortest path from ");
    print_word(i); printf(" to "); print_word(j); printf(".\n");
    for (l=0; l<150; l++) {
      for (k=0; k<N; k++) {
	printf("Considering about ");
	print_word(k);
	printf("\r"); fflush(stdout);
      }
    }
    printf("\nWell..., I don't know.  Please enlighten me ;)\n");
  }
}
