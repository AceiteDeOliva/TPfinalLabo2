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

//Crear nodo de lista doble
nodoDoble* crearNodoDoble(movimiento dato)
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

//agrega a la fila
void agregarAFila(fila * fila,movimiento dato)
{

    nodoDoble * nuevo = crearNodoDoble(dato);
    if (fila->cabecera == NULL)
    {
        fila->cabecera = nuevo;
        fila->cola = nuevo;
    }
    else
    {
        fila->cola->siguiente = nuevo;
        nuevo->anterior = fila->cola;
        fila->cola = nuevo;
    }

}

//muestra una variable tipo movimiento
void mostrarMovimiento(movimiento m)
{
    puts("--------------------------------------------|\n");
    if(m.tipoDeOperacion == 0)
    {
        printf("Importe:-%i\n",m.monto);

    }
    else
    {
        printf("Importe:+%i\n",m.monto);
    }


    if(m.cbuEmisor != m.cbuReceptor)
    {

        printf("CBU de emisor:%08d\n",m.cbuEmisor);
        printf("CBU de recipiente:%08d\n",m.cbuReceptor);


    }
    else if(m.tipoDeOperacion == 0)
    {

        printf("Extraccion\n");

    }
    else
    {

        printf("Deposito\n");

    }
    printf("Fecha de operacion: %s", ctime(&m.fecha));
    puts("\n--------------------------------------------|\n");
}
//Extrae el dato del primer nodo de una lista doble
movimiento extraer(fila * fila)
{
    movimiento resp;

    if(fila->cabecera)
    {

        resp = verPrimero(fila->cabecera);
        fila->cabecera = borrarPrimero(fila->cabecera);

        if(!fila->cabecera)
        {

            fila->cola = NULL;

        }

    }
    return resp;
}
// devuelve el primer miembre de una lista doble
movimiento verPrimero(nodoDoble * lista)
{
    movimiento resp;
    if(lista)
    {

        resp = lista->dato;

    }

    return resp;

}
//Borra el primer nodo de la lista y lo reemplaza con el segundo
nodoDoble * borrarPrimero(nodoDoble * lista)
{

    nodoDoble * aBorrar = lista;

    if(lista)
    {

        lista = lista->siguiente;
        if(lista)
        {
            lista->anterior = NULL;
        }
        free(aBorrar);

    }
    return lista;
}
//recorre toda la fila y la va mostrando a medida que elimina los nodos
void recorrerMostrarExtraerFila(fila * fila)
{
    movimiento aux;
    while(fila->cabecera)
    {
        aux = extraer(fila);
        mostrarMovimiento(aux);
    }

}
