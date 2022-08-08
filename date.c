#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "date.h"

//functie de swap

void swap(double *x, double *y)
{
    double aux = *x;
    *x = *y;
    *y = aux;
}

//functie de push(dupa last), in lista

void front_push(lista *l, int t, double r)
{
    node * newnode = malloc(sizeof(*newnode));
    newnode->next = NULL;
    newnode->data.timestamp = t;
    newnode->data.real = r;
    newnode->data.out = 0;
    if(l->first == NULL)
    {
        l->first = newnode;
        l->last = newnode;
        newnode->prev = NULL;
        return;
    }
    else
    {
        newnode->prev = l->last;
        l->last->next = newnode;
        l->last = newnode;
    }
}

//functie de rotunjit cu 2 zecimale

double round(double x)
{
    return roundf(x * 100) / 100;
}

//functie care verifica daca un numar dat este intr-un interval

int interval(double cap1, double cap2, double x)
{
    if(cap1 > x || cap2 < x) return 0;
    return 1; 
}

//check presupun ca nodul are 2 noduri inainte si 2 noduri dupa
//verific daca un nod trebuie sau nu scos
void check(lista *l, node ** nod, int k, int *n)
{
    int k2 = k/2, i;
    node *p = *nod;
    for(i = 0; i < k2; i++)
    {
        p = p->prev;
    }
    node *copie = p;

    double avg = 0;
    double deviation = 0;
    for(i = 0; i < k; i++)
    {
        avg += p->data.real;
        p = p->next;
    }
    avg = avg/k;
    for(i = 0; i < k; i++)
    {
        deviation += ( pow( ( copie->data.real )-avg, 2 ) / ( (double)(k) )  );
        copie = copie->next;
    }
    
    deviation = sqrt(deviation);

    //printf("%lf %lf %lf\n\n\n", avg, deviation, round((*nod)->data.real));

    if(!interval(avg-deviation, avg+deviation, (*nod)->data.real) )
        {
            //pop(l, nod);
            (*nod)->data.out = 1;
            *n = *n - 1;
        }

}

//goleste o lista, primeste ca parametru si numarul de elemente al ei

void clean(lista *l, int *n)
{
    node * p;
    for(p = l->first->next; p!=NULL; p = p->next)
    {
        pop(l, &(p->prev));
        //*n = *n - 1;
    }
    pop(l, &(l->last));
    //*n = *n - 1;
}

//functie care printeaza lista

void print(lista *l, int *n)
{
    printf("%d\n", *n);
    node * p;
    for(p = l->first; p!=NULL; p = p->next)
    {
        printf("%d %.2lf\n", p->data.timestamp, p->data.real);
    }
}

//task e1

void e1(lista *l, int *n)
{
    node * p;
    for(p = (l->first->next->next->next); p->next != NULL; p = p->next)
    {
        check(l, &(p->prev), 5, n);
    }
    for(p = (l->first->next->next->next); p->next != NULL; p = p->next)
    {
        if(p->prev->data.out == 1) pop(l, &(p->prev));
    }

    //print(l, n);
}

//scoate valoarea mediana din jurul lui nod

double median(node *nod){

    int i;
    node *p = nod->prev->prev;

    for(i = 0; i < 5; i++)
    {
        int k = 0;
        int egalitati = 0;
        double x = p->data.real;
        node *copie1 = p;
        node *copie2 = p;
        int j;
        for(j = 0; j < i; j++)
        {
            copie1 = copie1->prev;
            if(copie1->data.real > x) k--;
            if(copie1->data.real < x) k++;
            if(copie1->data.real == x) egalitati++;
        }

        for(j = i; j < 4 ; j++)
        {
            copie2 = copie2->next;
            if(copie2->data.real > x) k--;
            if(copie2->data.real < x) k++;
            if(copie2->data.real == x) egalitati++;
        }

        if(!k || egalitati >= 2 || (egalitati == 1 && k != 3 && k != -3)) return x;

        p = p->next;
    }

    return -1;
}

//task e2

void e2(lista *l, int *n)
{
    lista newlist;
    newlist.first = NULL;
    newlist.last = NULL;

    //int nr = 0;
    node *p;
    for(p = (l->first->next->next->next); p->next != NULL; p = p->next)
    {
        front_push(&newlist, p->prev->data.timestamp, median(p->prev));
    }


    clean(l, n);
    *n = *n - 4;


    *l = newlist;
    //print(&newlist, &nr);
    //clean(&newlist, &nr);
}

//media aritmetica din jurul unui nod

double aritm(node *nod)
{
    node *p = nod->prev->prev;
    double aritm = 0; 
    int i;
    for(i = 0; i < 5; i++)
    {
        aritm += p->data.real;
        p = p->next;
    }

    return aritm / 5;
}

//task e3

void e3(lista *l, int *n)
{
    lista newlist;
    newlist.first = NULL;
    newlist.last = NULL;

    //int nr = 0;
    node *p;
    for(p = (l->first->next->next->next); p->next != NULL; p = p->next)
    {
        front_push(&newlist, p->prev->data.timestamp, aritm(p->prev));
    }


    clean(l, n);
    *n = *n - 4;


    *l = newlist;
    //print(&newlist, &nr);
    //clean(&newlist, &nr);
}

//val absoluta

double abso(double x)
{
    if(x > 0) return x;
    else return -x;
}

//pentru task-ul u, verifica daca trebuie modificat timestamp si valoare reala

void check_u(node *nod)
{
    if(interval(100, 1000, abso(nod->data.timestamp - nod->prev->data.timestamp))){
        nod->data.timestamp = (nod->data.timestamp + nod->prev->data.timestamp) / 2;
        nod->data.real = (nod->data.real + nod->prev->data.real) / 2;
    }
}

//task u

void u(lista *l, int *n)
{
    node *p;
    for(p = (l->first->next); p != NULL; p = p->next)
    {
        check_u(p);
    }
}

//insereaza dupa nod intr-o lista, daca nodul e la final face front_push

void push_after(lista *l, node *nod, int t, double r)
{
    if(nod->next == NULL) {
        front_push(l, t, r);
        return;
    }

    node *newnode = malloc(sizeof(node));

    newnode->data.timestamp = t;
    newnode->data.real = r;
    newnode->prev = nod;
    newnode->next = nod->next;
    nod->next->prev = newnode;
    nod->next = newnode;
}

//calculul lui f asemenea formulelor din enunt

double f(int timestamp, D l1, D l2, D l3, D r1, D r2, D r3)
{

    double C = (double)(timestamp - l1.timestamp) / (double)(r1.timestamp - l1.timestamp);
    //printf("\n%lf %d\n", round(C), timestamp);
    double w1, w2, w3;
    double deimpartit = 0;
    int i;
    for(i = 0; i < 3; i++)
    {
        deimpartit += pow((double)(((double)(i))/2), 2) * 0.9 + 0.1;
    }

    w1 = (pow((double)(((double)(0))/2), 2) * 0.9 + 0.1) / deimpartit;
    w2 = (pow((double)(((double)(1))/2), 2) * 0.9 + 0.1) / deimpartit;
    w3 = (pow((double)(((double)(2))/2), 2) * 0.9 + 0.1) / deimpartit;

    //printf("\n%lf %lf %lf\n", w1, w2, w3);

    //double fun = 0;
    double stanga = l3.real * w1 + l2.real * w2 + l1.real * w3;
    double dreapta = r3.real * w1 + r2.real * w2 + r1.real * w3;


    return (1 - C) * stanga + C * dreapta;

} 

//completeaza datele intre nod si nod->next

void data_completion(lista *l, node *nod, int *n)
{

    node *p = nod;

    D l1, l2, l3;
    D r1, r2, r3;

    l1 = nod->data;
    l2 = nod->prev->data;
    l3 = nod->prev->prev->data;

    r1 = nod->next->data;
    r2 = nod->next->next->data;
    r3 = nod->next->next->next->data;

    int dif = nod->next->data.timestamp - nod->data.timestamp;
    int jump = dif / 200;
    int i;

    for(i = 1; (i <= jump) && (p->data.timestamp < p->next->data.timestamp - 200); i++)
    {
        int time = p->data.timestamp + 200;
        push_after(l, p, time, f(time, l1, l2, l3, r1, r2, r3));
        p = p->next;

        //test

        *n = *n + 1;
    }

}

//task c

void c(lista *l, int *n)
{
    node  *p;
    for(p = l->first->next->next; p->next->next != NULL; p = p->next)
    {
        if(abs(p->data.timestamp - p->next->data.timestamp) >= 1000)
        {
            data_completion(l, p, n);
        }
    }
}

//adauga la final, folositor doar cand coada este goala

void pushr(coada *c, double val, int delta)
{
        nodp *newnode = malloc(sizeof(nodp));
        newnode->next = NULL;
        newnode->prev = c->last;
        newnode->i.div = apartine(val, (double) delta);
        newnode->i.nr = 1;
        if(c->first == NULL) c->first = newnode;
        if(c->last != NULL) c->last->next = newnode;
        c->last = newnode;
}

//adauga la inceput, cand coada nu este goala

void pushl(coada *c, double val, int delta)
{
    nodp *newnode = malloc(sizeof(nodp));
    newnode->prev = NULL;
    newnode->next = c->first;
    newnode->i.div = apartine(val, (double)delta);
    newnode->i.nr = 1;
    c->first->prev = newnode;
    c->first = newnode;

}

//functia de push parcurge coada pana cand gaseste elementele intre care sa adauge un nou interval
//in cazul in care val este deja intr-un interval existent, i.nr de la nodul respectiv va creste


void push(coada *c, double val, int delta)
{
    nodp *p = c->first;
    int divcurenta = apartine(val, (double)delta);
    //if(divcurenta == 1) printf("%lf\n", val);
    if(p == NULL){
        pushr(c, val, delta);
        return;
    }
    if(divcurenta < p->i.div) {
        pushl(c, val, delta);
        return;}
    if(divcurenta > c->last->i.div) {
        pushr(c, val, delta);
        return;}
    if(divcurenta == p->i.div) {
        (p->i.nr)++;
        return;}
    if(divcurenta == c->last->i.div) {
        (c->last->i.nr)++;
        return;}

    for(p = c->first; p->next != NULL; p = p->next)
    {
        if(p->i.div == divcurenta) {
            (p->i.nr)++;
            }
        //daca divcurenta este intre diviziuni, adaug diviziune noua
        if(divcurenta > p->i.div && divcurenta < p->next->i.div)
        {
            nodp *newnode = malloc(sizeof(nodp));
            newnode->next = p->next;
            newnode->prev = p;
            newnode->i.div = divcurenta;
            newnode->i.nr = 1;
            p->next->prev = newnode;
            p->next = newnode;
            return;
        }
    }
}

//elimina nodul dat ca parametru in lista

void pop(lista *l, node ** nod)
{
    if(l->first == l->last)
    {
        free(*nod);
        l->first = NULL;
        l->last = NULL;
        return;
    }
    node * p = *nod;
    if(p == l->first)
    {
        l->first->next->prev = NULL;
        l->first = l->first->next;
        free(p);
        return;
    }
    if(p == l->last)
    {
        l->last->prev->next = NULL;
        l->last = l->first->prev;
        free(p);
        return;
    }

    node *prec = p->prev;
    node *urm = p->next;

    prec->next = urm;
    urm->prev = prec;
    free(p);

}

//ca pop dar pentru coada

void popc(coada *c, nodp ** nod){
    if(c->first == c->last)
    {
        free(*nod);
        c->first = NULL;
        c->last = NULL;
        return;
    }

    if(*nod == c->first)
    {
        nodp *p = c->first;
        c->first->next->prev = NULL;
        c->first = c->first->next;
        free(p);
        return;
    }

    if(*nod == c->last)
    {
        nodp *p = c->last;
        c->last->prev->next = NULL;
        c->last = c->last->prev;
        free(p);
        return;
    }

    nodp *p = *nod;
    nodp *prec = p->prev;
    nodp *urm = p->next;

    prec->next = urm;
    urm->prev = prec;
    free(*nod);
}

//ca si clean dar pentru coada

void cleanc(coada *c)
{
    while(c->first->next != NULL)
        popc(c, &(c->first));
    free(c->first);
}

//task st

void st(lista *l, char *arg)
{
    char s[10];
    char *ptr = arg + 4;
    int i = 0;
    while(*ptr)
    {
        s[i] = *ptr;
        i++;
        ptr = ptr + 1;
    }
    s[i] = '\0';
    int delta = atoi(s);

    coada c;
    c.first = NULL;
    c.last = NULL;
    node * p;
    for(p = l->first; p != NULL; p = p->next)
    {
        push(&c, p->data.real, delta);
        //if(p->data.real >= 10 && p->data.real <= 20) printf("\n%lf\n", p->data.real);

    }
    nodp * p1;

    for(p1 = c.first; p1 != NULL; p1 = p1->next)
    {
        printf("[%d, %d] %d\n",  (p1->i.div) * delta, (p1->i.div + 1) * delta, p1->i.nr);

    }
    cleanc(&c);
}

//intoarce diviziunea lui R in care se afla delta

int apartine(double val, double delta)
{
    return floorf(val/delta);
    //return ceilf(val/delta);
}