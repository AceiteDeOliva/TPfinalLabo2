#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "librerias1.h"
///inicializa la lista
nodoListaS* inicLista()
{
    return NULL;
}
///Crea un nodo de la lista
nodoListaS* crearNodoListaS(usuario dato)
{
    nodoListaS* aux=(nodoListaS*)malloc(sizeof(nodoListaS));
    aux->dato=dato;
    aux->siguiente=NULL;
return aux;
}
///Pasa del archivo a una lista los usuarios que esten en estado 0
nodoListaS* FromArchiAListaOrdenadaDesactivados(nodoListaS* lista)
{
    FILE* buffer=fopen(archivo, "rb");
    usuario usu;

    if(buffer)
    {
        while(fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(usu.estado == 0){
            nodoListaS* aux=crearNodoListaS(usu);
            lista=agregarEnOrden(lista, aux);
            }
        }

        fclose(buffer);
    }

    return lista;
}
///Agrega en orden de DNI a la lista
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
///agrega al principio de la lista
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
///Muestra la lista
void mostrarLista(nodoListaS* lista)
{
    nodoListaS* seg=lista;

    if(seg)
    {
         while(seg)
         {
             muestraUsuarioAdmin(seg->dato);
             seg=seg->siguiente;
         }
    }
}
///Borra la lista completamente
void borrarLista(nodoListaS** lista) {
    nodoListaS* aux = *lista;
    nodoListaS* seg;

    while (aux != NULL) {
        seg = aux->siguiente;
        free(aux);
        aux = seg;
    }

    *lista = NULL;
}
