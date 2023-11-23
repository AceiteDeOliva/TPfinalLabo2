#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "librerias1.h"
///Recorre el archivo de registros de empleados y los muestra
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
///Muestra un registro de empleado
void mostrar1Registro(stRegistroEmpleado registro)
{
    puts("-----------------------------");
    printf("DNI: %ld\n", registro.dni);
    printf("Fecha de nacimiento: %s\n", registro.fechaDeNacimiento);
    printf("Trabajo: %s\n", registro.nombreTrabajo);
    printf("Nombre y apellido: %s\n", registro.nombreYapellido);
    printf("Num telefono: %s\n", registro.NumeroTelefono);
    puts("-----------------------------");
}
///Busca si existe el DNI en el archivo
int buscarDniArchi4(int dni){

int flag=0;
stRegistroEmpleado aux;
FILE*buffer=fopen(archivo4,"rb");

if(buffer){

    while(fread(&aux,sizeof(stRegistroEmpleado),1,buffer)>0){

        if(aux.dni==dni){

            flag=1;
        }


    }
    fclose(buffer);

}
return flag;
}
///Carga datos de empleado en un registro
stRegistroEmpleado cargarDatosEmpleado()///faltan todas las validaciones y chequeos.
{
    stRegistroEmpleado e;
    puts("-----------------------------");
    printf("INGRESE LOS SIGUIENTES DATOS |\n");
    puts("-----------------------------");

    printf("\nNOMBRE DEL TRABAJO: ");
    fflush(stdin);
    gets(e.nombreTrabajo);

    printf("\nNOMBRE Y APELLIDO DEL EMPLEADO: ");
    fflush(stdin);
    gets(e.nombreYapellido);

    printf("\nDNI: ");
    fflush(stdin);
    scanf("%ld", &e.dni);

    int flag2=buscarDniArchi4(e.dni);

    while((e.dni > 100000000 || e.dni <= 0)||(flag2==1))
    {

        puts("ERROR: ingrese un DNI valido");
        fflush(stdin);
        scanf("%ld", &e.dni);
        flag2=buscarDniArchi4(e.dni);
    }

    printf("\nFECHA DE NACIMIENTO(formato xx/xx/xxxx): ");
    fflush(stdin);
    gets(e.fechaDeNacimiento);

    int flag=esFechaValida(e.fechaDeNacimiento);

    while(flag!=1)
    {

        printf("\nERROR: ingrese fecha Valida(formato xx/xx/xxxx): ");
        fflush(stdin);
        gets(e.fechaDeNacimiento);
        flag=esFechaValida(e.fechaDeNacimiento);
    }


    printf("\nNUMERO DE TELEFONO: ");
    scanf("%s", e.NumeroTelefono);

    printf("\n");
    e.estado=1;
    return e;
}
///Chequea si la fechad de nacimiento es valida
int esFechaValida(char fechaDeNacimiento[11])
{
    // Devuelve 1 si es válida, 0 si no

    int dia, mes, anio;

    if (sscanf(fechaDeNacimiento, "%d/%d/%d", &dia, &mes, &anio) != 3) // si pudo leer no  y almacernar los 3 valores
    {
        printf("Formato de fecha incorrecto.\n");
        return 0;
    }
   printf("Dia: %d, Mes: %d, Anio: %d\n", dia, mes, anio);
    // Verifica si los valores no son negativos
    if (dia <= 0 || mes <= 0 || anio <= 0)
    {
        printf("Los valores de dia, mes y año deben ser mayores que cero.\n");
        return 0;
    }

    // Verifica límites de mes y día
    if (mes < 1 || mes > 12 || dia < 1 || dia > 31||anio>=2024)
    {
        printf("Valores fuera de rango para mes o dia.\n");
        return 0;
    }

    // Verifica el número de días en el mes (no maneja años bisiestos)
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
    {
        printf("El mes %d solo tiene 30 dias.\n", mes);
        return 0;
    }
    else if (mes == 2)
    {
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
        {
            // Año bisiesto
            if (dia > 29)
            {
                printf("Febrero en anio bisiesto solo tiene 29 dias.\n");
                return 0;
            }
        }
        else
        {
            // Año no bisiesto
            if (dia > 28)
            {
                printf("Febrero en anio no bisiesto solo tiene 28 dias.\n");
                return 0;
            }
        }
    }

    return 1; // siempre va a retornar 1 si no entra a algun if
}
///Carga el archivo de empleados con un registro
void cargarArchiEmpleados()
{
    FILE* buffer=fopen(archivo4, "ab");
    char cont='s';
    stRegistroEmpleado dato;
    if(buffer){
        while(cont=='s')
        {
         dato=cargarDatosEmpleado();
         fwrite(&dato, sizeof(stRegistroEmpleado), 1, buffer);

         printf("Desea continuar cargando?\n");
         fflush(stdin);
         scanf("%c", &cont);
         system("pause");
         system("cls");
         dibujoBancoCentral();
        }
     fclose(buffer);
    }
}
///Crea un nodo con dato tipo empleado para lista simple
nodoEmpleado* crearNodoEmplado(empleado dato)
{
    nodoEmpleado* aux=(nodoEmpleado*)malloc(sizeof(nodoEmpleado));
    aux->dato=dato;
    aux->siguiente=NULL;

    return aux;
}
///Agrega al principio de la lista de empleados
nodoEmpleado*agregarAlPpioEmpleado(nodoEmpleado* lista, nodoEmpleado* nuevo)
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
///Agrega a la lista de empleados en orden
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
///Busca la posicion de la celda por nombre del trabajo
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
///Agrega un trabajo al arreglo
int agregarCelda(celda adl[], int validos, char nombreTrabajo[])
{
    strcpy(adl[validos].nombreTrabajo, nombreTrabajo);
    adl[validos].listaEmpleados=NULL;
    validos++;
return validos;
}
///Funcion de alta de arreglo de listas que recibe una variable empleado
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
///Funcion de alta de arreglo de listas que recibe una nodo empleado
int alta2(celda adl[], int validos,nodoEmpleado*emple, char nombreTrabajo[])
{
    int pos=buscaPosCelda(adl, validos, nombreTrabajo);

    if(pos==-1)
    {
        validos=agregarCelda(adl, validos, nombreTrabajo);
        pos=validos-1;
    }
    adl[pos].listaEmpleados=agregarEmpleadoEnOrdenPorDni(adl[pos].listaEmpleados, emple);

return validos;
}
///carga el arreglo de listas
int cargaADL(celda adl[], int dimension, empleado emple, char nombreTrabajo[])
{
    int validos=0;

    while(validos<dimension)
    {
        validos=alta(adl, validos, emple, nombreTrabajo);
    }
return validos;
}
///Crea una variable empleado a partir de un registro
empleado fromArchiToEmpleado(stRegistroEmpleado r)
{
    empleado e;

    e.dni=r.dni;
    e.estado=r.estado;
    strcpy(e.fechaDeNacimiento, r.fechaDeNacimiento);
    strcpy(e.nombreYapellido, r.nombreYapellido);
    strcpy(e.NumeroTelefono,r.NumeroTelefono);

return e;
}
///Pasa del archivo a arreglo de listas
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
///Muestra 1 empleado
void mostrarEmpleado(celda trabajo[],int posTrabajo,empleado dato)
{
    char estado[10];

    if(dato.estado==1)
    {
        strcpy(estado, "ACTIVO");
    }
    else
    {
        strcpy(estado, "INACTIVO");
    }

    puts("                                     --------------------------------------------");
    printf("                                    | DNI: %-8li                              |\n", dato.dni);
    printf("                                      NOMBRE Y APELLIDO: %s\n", dato.nombreYapellido);
    printf("                                    | FECHA DE NACIMIENTO: %-8s             |\n", dato.fechaDeNacimiento);
    printf("                                      TRABAJO: %s\n", trabajo[posTrabajo].nombreTrabajo);
    printf("                                    | NUM TELEFONO: %8s                    |\n", dato.NumeroTelefono);
    printf("                                      ESTADO: %s\n", estado);
    puts("                                     --------------------------------------------\n\n");
}
///Muestra todo el adl de empleados
void mostrarADLempleados(celda adl[], int validos)
{
    int i=0;

    while(i<validos)
    {

        puts("-------------------");
        printf("TRABAJO: %s |\n", adl[i].nombreTrabajo);
        puts("-------------------\n\n");
        puts("              ---------------------------------------------------------------------------------------------");
        printf("             |   %-10s%-25s%-15s%-25s%-15s\n", "ESTADO", "NOMBRE Y APELLIDO", "DNI", "FECHA DE NACIMIENTO", "NUM TELEFONO   |");
        puts("              ---------------------------------------------------------------------------------------------");
        mostrarListaEmpleados(adl[i].listaEmpleados);
        i++;
    }
}
///Muestra empleados de un sector
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
///Muestra lista
void mostrarDatosListaEmpleados(nodoEmpleado* lista)
{
     char estado[10];
     if(lista->dato.estado==1)
        strcpy(estado, "ACTIVO");
     else
        strcpy(estado, "INACTIVO");
     printf("             |   %-10s%-25s%-15ld%-25s%-15s| \n\n", estado, lista->dato.nombreYapellido, lista->dato.dni, lista->dato.fechaDeNacimiento, lista->dato.NumeroTelefono);
}
///Busca empleado en un sector
nodoEmpleado* buscarEmpleadoXdni(celda trabajos[], int validos, long int dniBuscado,int*i) {///i siempre tiene que estar en 0.
    for ((*i)=0;(*i)<validos;(*i)++) {
        nodoEmpleado*actual=trabajos[(*i)].listaEmpleados;
        while (actual!=NULL) {
            if (actual->dato.dni == dniBuscado) {
                return actual;
            }
            actual = actual->siguiente;
        }
    }
    return NULL;
}
///Borra nodo empleado de lista
nodoEmpleado* borrarNodoEmpleado(nodoEmpleado*lista,nodoEmpleado*nodoABorrar)
{
    if(lista!=NULL&&lista->dato.dni!=nodoABorrar->dato.dni){
        nodoEmpleado*borr=lista;
        lista=lista->siguiente;
        free(borr);
    }
    else{
        nodoEmpleado*ante=lista;
        nodoEmpleado*seg=lista->siguiente;
        while(seg!=NULL&&seg->dato.dni!=nodoABorrar->dato.dni){
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg!=NULL){
            ante->siguiente=seg->siguiente;
            free(seg);
        }
    }
    return lista;
}
///Busca si el trabajo existe
int verificarTrabajoRepetido(celda trabajos[],int validos,char nombreTrabajo[])
{
    int i=0;
    for(i=0;i<validos;i++){
        if(strcmp(trabajos[i].nombreTrabajo,nombreTrabajo)==0){
            return 1;
        }
    }
    return 0;
}
///Busca la posicion del trabajo en el arreglo
int RetornarPosTrabajo(celda trabajos[],char nombreTrabajo[],int validos)
{
    int i=0;
    int flag=0;
    while(i<validos&&flag==0){
        if(strcmp(trabajos[i].nombreTrabajo,nombreTrabajo)==0){
            flag=1;
            return i;
        }
        i++;
    }
    return -1;
}
///Carga empleado
empleado cargarEmpleado()
{
    empleado e;
    printf("\nNOMBRE Y APELLIDO DEL EMPLEADO: ");
    fflush(stdin);
    gets(e.nombreYapellido);

    printf("\nDNI: ");
    scanf("%ld", &e.dni);

    printf("\nFECHA DE NACIMIENTO(formato xx/xx/xxxx): ");
    fflush(stdin);
    gets(e.fechaDeNacimiento);

    printf("\nNUMERO DE TELEFONO: ");
    scanf("%s", e.NumeroTelefono);

    e.estado=1;
    return e;
}
///Reemplaza empleado en el archivo
void reemplazarDatoEmpleado(celda trabajos[], int posTrabajo, empleado dato)
{
    FILE* archi = fopen(archivo4, "r+b");
    if (archi){
        stRegistroEmpleado aux;
        int encontrado = 0;
        while (fread(&aux, sizeof(stRegistroEmpleado), 1, archi) > 0) {
            if (dato.dni == aux.dni) {
                encontrado = 1;

                fseek(archi, -sizeof(stRegistroEmpleado), SEEK_CUR);

                aux.dni = dato.dni;
                aux.estado = dato.estado;
                strcpy(aux.NumeroTelefono,dato.NumeroTelefono);
                strcpy(aux.nombreYapellido, dato.nombreYapellido);
                strcpy(aux.fechaDeNacimiento, dato.fechaDeNacimiento);
                strcpy(aux.nombreTrabajo, trabajos[posTrabajo].nombreTrabajo);

                fwrite(&aux, sizeof(stRegistroEmpleado), 1, archi);
                break;
            }
        }

        fclose(archi);

        if (!encontrado) {
            printf("No se encontro  un empleado con el DNI proporcionado.\n");
    }
    }
}
///Da de alta o baja a un empleado
void AltaYbajaEmpleado(celda trabajos[],int posTrabajo,nodoEmpleado*emplead, int validos)
{
    int x=-1;

    do
    {
        system("cls");
        dibujoBancoCentral();
        mostrarEmpleado(trabajos,posTrabajo,emplead->dato);
        puts("-----------------------------------|");
        printf("[1]DAR DE ALTA EMPLEADO\n");
        puts("-----------------------------------|");
        printf("[2]DAR DE BAJA EMPLEADO\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d",&x);
        switch(x)
        {
        case 1:
            emplead->dato.estado=1;
            reemplazarDatoEmpleado(trabajos,posTrabajo,emplead->dato);
            break;
        case 2:
            emplead->dato.estado=0;
            reemplazarDatoEmpleado(trabajos,posTrabajo,emplead->dato);
            break;
        case 0:
            menuOpcionesAdminEmpleado(trabajos, posTrabajo,emplead, validos);
            break;
        default:
            printf("Elija una opcion correcta.\n");
            break;
        }
    x=0;
    }
while(x!=-1);
}
