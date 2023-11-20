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

nodoListaS* FromArchiAListaOrdenada(nodoListaS* lista)
{
    FILE* buffer=fopen(archivo, "rb");
    usuario usu;

    if(buffer)
    {
        while(fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            nodoListaS* aux=crearNodoListaS(usu);
            lista=agregarEnOrden(lista, aux);
        }

        fclose(buffer);
    }

    return lista;
}

nodoListaS* agregarEnOrden(nodoListaS* lista, nodoListaS* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if((nuevoNodo->dato.dni) < (lista->dato.dni))
        {
            lista=agregarAlPpio(lista, nuevoNodo);
        }
        else
        {
            nodoListaS* ante=lista;
            nodoListaS* seg = lista->siguiente;
            while((seg!=NULL)&& ((nuevoNodo->dato.dni)> (seg->dato.dni)))
            {
                ante=seg;
                seg=seg->siguiente;
            }
            nuevoNodo->siguiente=seg;
            ante->siguiente=nuevoNodo;
        }
    }

    return lista;
}

nodoListaS* agregarAlPpio(nodoListaS* lista, nodoListaS* nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
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
