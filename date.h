#ifndef _date_
#define _date_

//structurile: D este tipul de data, node este nodul din lista si lista este o structura ce 
//retine inceputul si sfarsitul listei
typedef struct D{
    int timestamp;
    double real;
    unsigned char out;
} D;

typedef struct node{
    D data;
    struct node *next;
    struct node *prev;
} node;

typedef struct lista{
    node * first;
    node * last;
} lista;

//pentru statistici voi tine o lista(un priority queue implementat ca lista); ea retine numarul diviziunii in functie
//de delta, si numarul de elemente din acel interval

typedef struct inter{
    int div;
    int nr;
} inter;

typedef struct nodp{
    inter i;
    struct nodp * next;
    struct nodp * prev;
} nodp;

typedef struct coada{
    nodp *first;
    nodp *last;
} coada;

//headere la functiile folosite
void pushr(coada *c, double val, int delta);
void pushl(coada *c, double val, int delta);
void push(coada *c, double val, int delta);
void front_push(lista *l, int t, double r);
void pop(lista *l, node ** nod);
double round(double x);
void check(lista *l, node ** nod, int k, int *n);
void clean(lista *l, int *n);
void cleanc(coada *c);
void popc(coada *c, nodp ** nod);
void print(lista *l, int *n);
void e1(lista *l, int *n);
void e2(lista *l, int *n);
void e3(lista *l, int *n);
void u(lista *l, int *n);
void c(lista *l, int *n);
void st(lista *l, char *arg);
double median(node *nod);
double aritm(node *nod);
void check_u(node *nod);
double abso(double x);
void push_after(lista *l, node *nod, int t, double r);
void data_completion(lista *l, node *nod, int *n);
double f(int timestamp, D l1, D l2, D l3, D r1, D r2, D r3);
int apartine(double val, double delta);

#endif