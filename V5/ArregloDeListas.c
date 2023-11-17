#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "librerias1.h"

void mostrarArchi()
{
    FILE* buffer=fopen(archivo4, "rb");
    stRegistroEmpleado registro;

    if(buffer)
    {
        while(fread(&registro, sizeof(stRegistroEmpleado), 1, buffer)>0)
        {
           mostrar1Registro(registro);
        }
        fclose(buffer);
    }
}

void mostrar1Registro(stRegistroEmpleado registro)
{
    puts("-----------------------------");
    printf("DNI: %d\n", registro.dni);
    printf("Fecha de nacimiento: %s\n", registro.fechaDeNacimiento);
    printf("Trabajo: %s\n", registro.nombreTrabajo);
    printf("Nombre y apellido: %s\n", registro.nombreYapellido);
    printf("Num telefono: %d\n", registro.NumeroTelefono);
    puts("-----------------------------");
}

void cargarArchiEmpleados()
{
    FILE* buffer=fopen(archivo4, "ab");
    char cont='s';
    stRegistroEmpleado dato;

    if(buffer)
    {
        while(cont=='s')
        {
         dato=cargarDatosEmpleado();
         fwrite(&dato, sizeof(stRegistroEmpleado), 1, buffer);

         printf("Desea continuar cargando?\n");
         fflush(stdin);
         scanf("%c", &cont);
        }
     fclose(buffer);
    }
}

stRegistroEmpleado cargarDatosEmpleado()///faltan todas las validaciones y chequeos.
{
    stRegistroEmpleado e;
    printf("                                 |");
    printf("\n    INGRESE LOS SIGUIENTES DATOS |\n");
    puts("---------------------------------");

    printf("\nNOMBRE DEL TRABAJO: ");
    fflush(stdin);
    gets(e.nombreTrabajo);

    printf("\nNOMBRE Y APELLIDO DEL EMPLEADO: ");
    fflush(stdin);
    gets(e.nombreYapellido);

    printf("\nDNI: ");
    scanf("%i", &e.dni);

    printf("\nFECHA DE NACIMIENTO(formato xx/xx/xxxx): ");
    fflush(stdin);
    gets(e.fechaDeNacimiento);

    printf("\nNUMERO DE TELEFONO: ");
    scanf("%d", &e.NumeroTelefono);

    e.estado=1;
return e;
}

nodoEmpleado* crearNodoEmplado(empleado dato)
{
    nodoEmpleado* aux=(nodoEmpleado*)malloc(sizeof(nodoEmpleado));
    aux->dato=dato;
    aux->siguiente=NULL;

    return aux;
}

int cargaADL(celda adl[], int dimension, empleado emple, char nombreTrabajo[])
{
    int validos=0;

    while(validos<dimension)
    {
        validos=alta(adl, validos, emple, nombreTrabajo);
    }
return validos;
}

int alta(celda adl[], int validos, empleado emple, char nombreTrabajo[])
{
    nodoEmpleado* aux=crearNodoEmplado(emple);
    int pos=buscaPosCelda(adl, validos, nombreTrabajo);

    if(pos==-1)
    {
        validos=agregarCelda(adl, validos, nombreTrabajo);
        pos=validos-1;
    }
    adl[pos].listaEmpleados=agregarEmpleadoEnOrdenPorDni(adl[pos].listaEmpleados, aux);

return validos;
}

int buscaPosCelda(celda adl[], int validos, char nombreTrabajo[])
{
    int rta=-1;
    int i=0;

    while(i<validos && rta==-1)
    {
        if(strcmpi(adl[i].nombreTrabajo, nombreTrabajo)==0)
        {
            rta=i;
        }
    i++;
    }
return rta;
}

int agregarCelda(celda adl[], int validos, char nombreTrabajo[])
{
    strcpy(adl[validos].nombreTrabajo, nombreTrabajo);
    adl[validos].listaEmpleados=inicLista();
    validos++;
return validos;
}

nodoEmpleado* agregarEmpleadoEnOrdenPorDni(nodoEmpleado* lista, nodoEmpleado* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if((nuevoNodo->dato.dni) < (lista->dato.dni))
        {
            lista=agregarAlPpioEmpleado(lista, nuevoNodo);
        }
        else
        {
            nodoEmpleado* ante=lista;
            nodoEmpleado* seg = lista->siguiente;
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

nodoEmpleado* agregarAlPpioEmpleado(nodoEmpleado* lista, nodoEmpleado* nuevo)
{
    if(lista==NULL)
        lista=nuevo;
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
return lista;
}

int fromArchiEmpleadosToADL(celda adlEmpleados[], int dimension)
{
    FILE* buffer=fopen(archivo4, "rb");
    stRegistroEmpleado r;
    char nombreTrabajo[30];
    empleado e;
    int validos=0;

    if(buffer)
    {
        while(fread(&r, sizeof(stRegistroEmpleado), 1, buffer)>0 && validos<dimension)
        {
           strcpy(nombreTrabajo, r.nombreTrabajo);
           e=fromArchiToEmpleado(r);
           validos=alta(adlEmpleados, validos, e, nombreTrabajo);
        }
        fclose(buffer);
    }
return validos;
}

empleado fromArchiToEmpleado(stRegistroEmpleado r)
{
    empleado e;

    e.dni=r.dni;
    e.estado=r.estado;
    strcpy(e.fechaDeNacimiento, r.fechaDeNacimiento);
    strcpy(e.nombreYapellido, r.nombreYapellido);
    e.NumeroTelefono=e.NumeroTelefono;
return e;
}

void mostrarADLempleados(celda adl[], int validos)
{
    int i=0;

    while(i<validos)
    {

        puts("-------------------");
        printf("TRABAJO: %s |\n", adl[i].nombreTrabajo);
        puts("-------------------\n");
        mostrarListaEmpleados(adl[i].listaEmpleados);
        i++;
    }
}

void mostrarListaEmpleados(nodoEmpleado* lista)
{
    nodoEmpleado* seg=lista;

    if(seg)
    {
         while(seg)
         {
             mostrarDatosListaEmpleados(seg);
             seg=seg->siguiente;
         }
    }
}

void mostrarDatosListaEmpleados(nodoEmpleado* lista)
{
    printf("ESTADO: %d\n", lista->dato.estado);
    printf("NOMBRE Y APELLIDO: %s\n", lista->dato.nombreYapellido);
    printf("DNI: %i\n", lista->dato.dni);
    printf("FECHA DE NACIMIENTO: %s\n", lista->dato.fechaDeNacimiento);
    printf("NUMERO DE TELEFONO: %d\n",lista->dato.NumeroTelefono);
}


