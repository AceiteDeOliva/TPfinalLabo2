#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "librerias1.h"

nodoListaS* inicLista()
{
    return NULL;
}

nodoListaS* crearNodoListaS(usuario dato)
{
    nodoListaS* aux=(nodoListaS*)malloc(sizeof(nodoListaS));
    aux->dato=dato;
    aux->siguiente=NULL;
return aux;
}

nodoListaS* fromArregloDeEstructurasToLista(nodoListaS* lista, usuario arreglo[], int validos)
{
    int i=0;

    while(i<validos)
    {
        nodoListaS* aux=crearNodoListaS(arreglo[i]);
        lista=agregarAlFinal(lista, aux);
    }
return lista;
}

nodoListaS* buscaUlt(nodoListaS* lista)
{
    nodoListaS* seg=lista;

    if(seg)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
    }
return seg;
}

nodoListaS* agregarAlFinal(nodoListaS* lista, nodoListaS* nuevo)
{
    if(lista==NULL)
        lista=nuevo;
    else
    {
        nodoListaS* ult=buscaUlt(lista);
        ult->siguiente=nuevo;
    }
return lista;
}

void mostrarLista(nodoListaS* lista)
{
    nodoListaS* seg=lista;

    if(seg)
    {
         while(seg)
         {
             muestra1Usuario(seg->dato);
             seg=seg->siguiente;
         }
    }
}
