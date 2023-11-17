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
    inicFila(&aux->movimiento);
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
        if(nuevo->dato.dni > arbol->dato.dni){
            arbol->der=cargarArbloOrdenDNI(arbol->der, nuevo);
        }else{
            arbol->izq=cargarArbloOrdenDNI(arbol->izq, nuevo);
        }
    }
return arbol;
}

nodoArbol* fromArchiToArbolDNI(nodoArbol* arbol)
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

nodoArbol* buscarDNIenArbol(nodoArbol* arbol,int dni)
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

void mostrarArbolInordenDni(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarArbolInordenDni(arbol->izq);
        muestra1Usuario(arbol->dato);
        mostrarArbolInordenDni(arbol->der);
    }
}

nodoArbol* cargarArbolOrdenCBU(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    arbol=nuevo;
    else
    {
        if(nuevo->dato.cbu > arbol->dato.cbu){
            arbol->der=cargarArbolOrdenCBU(arbol->der, nuevo);
        }else{
            arbol->izq=cargarArbolOrdenCBU(arbol->izq, nuevo);
        }
    }
return arbol;
}
nodoArbol* fromArchiToArbolCBU(nodoArbol* arbol)
{
   FILE* buffer=fopen(archivo, "rb");
   usuario usu;

   if(buffer)
   {
       while(fread(&usu, sizeof(usuario), 1, buffer)>0)
       {
           nodoArbol* aux=crearNodoArbol(usu);
           arbol=cargarArbolOrdenCBU(arbol, aux);
       }
       fclose(buffer);
   }
return arbol;
}


nodoArbol* buscarCBUenArbol(nodoArbol* arbol,int cbu)
{
    nodoArbol* rta=NULL;
    if(arbol)
    {
        if (arbol->dato.cbu == cbu)
            rta=arbol;
        else
        {
            if( cbu < arbol->dato.cbu)
            {
                rta=buscarCBUenArbol(arbol->izq, cbu);
            }
            else
            {
                rta=buscarCBUenArbol(arbol->der, cbu);
            }
        }
    }
return rta;
}


void mostrarArbolInordenCBU(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarArbolInordenCBU(arbol->izq);
        muestra1Usuario(arbol->dato);
        mostrarArbolInordenCBU(arbol->der);
    }
}

