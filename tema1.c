#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "date.h"

//functia main care apeleaza functiile din date.c

int main(int argc, char *argv[])
{
    int n;
    lista l;
    l.first = NULL;
    l.last = NULL;
    int i;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        int x;
        double y;
        scanf("%d%lf", &x, &y);
        front_push(&l, x, y);
    }

    int printeazal = 1;
    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i],"--e1")) e1(&l, &n);
        if(!strcmp(argv[i],"--e2")) e2(&l, &n);
        if(!strcmp(argv[i],"--e3")) e3(&l, &n);
        if(!strcmp(argv[i],"--u")) u(&l, &n);
        if(!strcmp(argv[i],"--c")) c(&l, &n);
        if (argv[i][2] == 's' && argv[i][3] == 't') {
            st(&l, argv[i]);
            printeazal = 0;}
    }


    if(printeazal)
    print(&l, &n);
    clean(&l, &n);
    return 0;
}

