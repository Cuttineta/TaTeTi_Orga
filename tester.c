#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    tLista l;
    crear_lista(&l);
    int a=3;
    l_insertar(l,l_primera(l),&a);
    int *k= l_recuperar(l,l_primera(l));
    printf("%d",*k);

    return 0;
}
