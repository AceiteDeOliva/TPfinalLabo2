#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

//inicializar fila
void inicFila(fila * fila)
{
    fila->cabecera= NULL;
    fila->cola = NULL;
}

//Crear nodo
nodoDoble* crearNodoDoble(sTtransfer dato)
{
    nodoDoble* nuevoNodo = (struct nodoDoble*)malloc(sizeof(struct nodoDoble));

    if (nuevoNodo != NULL)
    {
        nuevoNodo->dato = dato;
        nuevoNodo->siguiente = NULL;
        nuevoNodo->anterior = NULL;
    }

    return nuevoNodo;
}

//agrega al final de la lista
nodoDoble * agregarAlFinal(nodoDoble * lista,nodoDoble * nuevoNodo)
{

    if(lista == NULL)
    {

        lista = nuevoNodo;

    }
    else
    {

        nodoDoble * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;

    }

    return lista;
}

// busca el ultimo de la lista
nodoDoble * buscarUltimo(nodoDoble * lista)
{
    nodoDoble * ultimo  = lista;
    while(ultimo->siguiente!= NULL)
    {

        ultimo = ultimo->siguiente;

    }

    return ultimo;
}

//agrega a la fila
void agregarAFila(fila * fila,sTtransfer dato)
{

    nodoDoble * nuevo = crearNodoDoble(dato);
    if(fila->cabecera == NULL)
    {

        fila->cabecera = nuevo;
        fila->cola = nuevo;
    }
    else
    {
        fila->cabecera = agregarAlFinal(fila->cabecera,nuevo);
        fila->cola = nuevo;

    }

}
