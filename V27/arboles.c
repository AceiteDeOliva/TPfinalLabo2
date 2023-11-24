#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"
//Inicializa nodoArbol
nodoArbol* inicArbol()
{
    return NULL;
}
// crea nodo de arbol
nodoArbol* crearNodoArbol(usuario dato)
{
    nodoArbol* aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato=dato;
    aux->izq=NULL;
    aux->der=NULL;
return aux;
}
//Carga arbol ordenado por DNI
nodoArbol* cargarArbolOrdenDNI(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    arbol=nuevo;
    else
    {
        if(nuevo->dato.dni > arbol->dato.dni){
            arbol->der=cargarArbolOrdenDNI(arbol->der, nuevo);
        }else{
            arbol->izq=cargarArbolOrdenDNI(arbol->izq, nuevo);
        }
    }
return arbol;
}
//Pasa de archivo a arbol ordenado por DNI
nodoArbol* fromArchiToArbolDNI(nodoArbol* arbol)
{
   FILE* buffer=fopen(archivo, "rb");
   usuario usu;

   if(buffer)
   {
       while(fread(&usu, sizeof(usuario), 1, buffer)>0)
       {
           nodoArbol* aux=crearNodoArbol(usu);
           arbol=cargarArbolOrdenDNI(arbol, aux);
       }
       fclose(buffer);
   }
return arbol;
}
//Busca DNI en arbol ordenado por DNI
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
//Muestra un arbol en inorden
void mostrarArbolInorden(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarArbolInorden(arbol->izq);
        muestraUsuarioAdmin(arbol->dato);
        mostrarArbolInorden(arbol->der);
    }
}

//Carga arbol en orden por cbu
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
//Pasa del archivo a un arbol ordenado por CBU
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
//Busca CBU en arbol ordenado por CBU
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

//Borra Arbol completamente para liberar memoria
void borrarArbol(nodoArbol* raiz) {

    if (raiz == NULL) {
        return;
    }

    borrarArbol(raiz->izq);
    borrarArbol(raiz->der);

    free(raiz);
}
