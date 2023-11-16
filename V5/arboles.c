#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(usuario dato)
{
    nodoArbol* aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato=dato;
    aux->izq=NULL;
    aux->der=NULL;
return aux;
}

nodoArbol* cargarArbloOrdenDNI(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    arbol=nuevo;
    else
    {
        if(nuevo->dato.dni > arbol->dato.dni)
            arbol->der=cargarArbloOrdenDNI(arbol->der, nuevo);
        else
            arbol->izq=cargarArbloOrdenDNI(arbol->izq, nuevo);
    }
return arbol;
}

nodoArbol* fromArchiToArbol(nodoArbol* arbol)
{
   FILE* buffer=fopen(archivo, "rb");
   usuario usu;

   if(buffer)
   {
       while(fread(&usu, sizeof(usuario), 1, buffer)>0)
       {
           nodoArbol* aux=crearNodoArbol(usu);
           arbol=cargarArbloOrdenDNI(arbol, aux);
       }
       fclose(buffer);
   }
return arbol;
}

nodoArbol* buscarDNIenArbol(nodoArbol* arbol, long int dni)
{
    nodoArbol* rta=NULL;
    if(arbol)
    {
        if (arbol->dato.dni == dni)
            rta=arbol;
        else
        {
            if( dni < arbol->dato.dni)
            {
                rta=buscarDNIenArbol(arbol->izq, dni);
            }
            else
            {
                rta=buscarDNIenArbol(arbol->der, dni);
            }
        }
    }
return rta;
}

void mostrarArbolEnOrdenDni(nodoArbol* arbol)
{
    if(arbol)
    {
        muestra1Usuario(arbol->dato);
        mostrarArbolEnOrdenDni(arbol->izq);
        mostrarArbolEnOrdenDni(arbol->der);
    }
}
