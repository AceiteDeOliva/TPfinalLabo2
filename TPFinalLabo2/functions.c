#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include <time.h>
#include <windows.h>
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




//void cargarFila(fila* fila){
//
//
//transferencia dato = cargarTransferecia();
//agregarAFila(fila,dato);
//
//
//}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//Genera un numero aleatorio del 0 al 9
int generarDigitoAleatorio()
{
    return rand() % 10;
}
//funcion para generar el cbu se le pasa la cantidad de digitos (8)
int generarCBU(int digitos)
{
    if (digitos == 0)
    {
        return 0;
    }
    else
    {
        int digito = generarDigitoAleatorio();
        return generarCBU(digitos - 1) * 10 + digito;
    }
}

//eliminar usuario (cambiar estado a 0)
nodoArbol * cambiarEstado(nodoArbol * arbol)
{

    arbol->dato.estado = 0;

    return arbol;
}

//Modifica un usuario dependiendo de la opcion que elija
nodoArbol* modificarUsuario(nodoArbol * arbol)
{
    int eleccion = -1;

    printf("Ingrese la opcion que desea modificar\n");
    printf("1- Nombre y apellido\n");
    printf("2- DNI\n");
    printf("3- Genero\n");
    printf("4- Mail\n");
    printf("5- contraseña\n");
    printf("6- CBU\n");
    fflush(stdin);
    scanf("%i",&eleccion);

    switch(eleccion)
    {

    case 1:
        printf("Nuevo nombre y apellido:\n");
        fflush(stdin);
        gets(arbol->dato.nombreApellido);
        break;

    case 2:
        printf("Nuevo DNI:\n");
        fflush(stdin);
        scanf("%ld",&arbol->dato.dni);
        break;
    case 3:
        printf("Nuevo genero:\n");
        fflush(stdin);
        scanf("%c",&arbol->dato.genero);
        break;
    case 4:
        printf("Nuevo mail:\n");
        fflush(stdin);
        gets(arbol->dato.mail);
        break;
    case 5:
        printf("Nueva contrasenia:\n");
        fflush(stdin);
        gets(arbol->dato.contrasenia);
        break;
    case 6:
        srand((unsigned int)time(NULL));
        arbol->dato.cbu = generarCBU(8);

        break;
    default:

        printf("opcion no valida\n");

        break;

    }

    return arbol;
}

void imprimirUsuario(usuario u)
{
    printf("Estado: %d\n", u.estado);
    printf("Nombre y Apellido: %s\n", u.nombreApellido);
    printf("DNI: %ld\n", u.dni);
    printf("Genero: %c\n", u.genero);
    printf("Correo Electronico: %s\n", u.mail);
    printf("Contrasenia: %s\n", u.contrasenia);
    printf("CBU: %08d\n", u.cbu);
}


nodoArbol* existePaciente(nodoArbol* pacientes, int dniPaciente)
{
    if (pacientes == NULL)
    {
        return NULL;
    }

    if (dniPaciente == pacientes->dato.dni)
    {
        return pacientes;

    }
    else if (dniPaciente < pacientes->dato.dni)
    {
        return existePaciente(pacientes->izq, dniPaciente);
    }
    else
    {
        return existePaciente(pacientes->der,dniPaciente);
    }

}


nodoArbol*crearNodoArbol(usuario dato)///crea un nodo con una struct tipo usuario
{
    nodoArbol*nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato.cbu=dato.cbu;
    strcpy(nuevo->dato.contrasenia,dato.contrasenia);
    nuevo->dato.dni=dato.dni;
    nuevo->dato.estado=dato.dni;
    nuevo->dato.genero=dato.genero;
    strcpy(nuevo->dato.mail,dato.mail);
    strcpy(nuevo->dato.nombreApellido,dato.nombreApellido);
    nuevo->dato.saldo.caja=dato.saldo.caja;
    nuevo->dato.saldo.prestamo=dato.saldo.prestamo;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
}
nodoArbol*InsertarEnArbol(nodoArbol*arbol,nodoArbol*nuevo)///inserta un nuevo nodo en el arbol de forma ordenada segun su dni
{
    if(arbol==NULL){
        arbol=nuevo;
    }
    else{
        if(nuevo->dato.dni<arbol->dato.dni){
            arbol->izq=InsertarEnArbol(arbol->izq,nuevo);
        }
        else{
            arbol->der=InsertarEnArbol(arbol->der,nuevo);
        }
    }
    return arbol;
}
nodoArbol*archivoToArbolBB(char archivo[],nodoArbol*arbol)///pasa los datos de un archivo a un arbol binario de busqueda
{
    FILE*arch=fopen(archivo,"rb");
    usuario dato;
    if(arch){
        while(fread(&dato,sizeof(usuario),1,arch)>0){
            nodoArbol*nuevo=crearNodoArbol(dato);
            arbol=InsertarEnArbol(arbol,nuevo);
        }
    }
    fclose(arch);
    return arbol;
}

long int DniBuscado()///pregunta por el dni buscado
{
    long int dni=0;
    printf("\nIngrese dni buscado:");
    scanf("%ld",&dni);
    return dni;
}

nodoArbol*BuscarDniEnArbol(nodoArbol*arbol,long int dni)///busca un dni en el arbol y retorna su nodo
{
    nodoArbol*res=NULL;
    if(arbol!=NULL){
        if(arbol->dato.dni==dni){
            res=arbol;
        }
        else{
            if(dni<arbol->dato.dni){
                res=BuscarDniEnArbol(arbol->izq,dni);
            }
            else{
                res=BuscarDniEnArbol(arbol->der,dni);
            }
        }
    }
    return res;
}
void MenuUsuario()///muestra menu del usuario
{
    printf("\n---------------------------------------");
    printf("\n1-Eliminar usuario.");
    printf("\n2-Modificar usuario.");
    printf("\n3-Corroborar transacciones.");
    printf("\n0-Volver al menu.");
    printf("\n---------------------------------------");
}
void mostrar1Usuario(usuario dato)///muestra un usuario
{
    printf("\n---------------------------------------");
    printf("\nNombre Apellido:%s",dato.nombreApellido);
    printf("\nDNI:%ld",dato.dni);
    printf("\nCBU:%08d\n",dato.cbu);
    printf("---------------------------------------\n");
}

void buscarUsuarioPorDni(nodoArbol*arbol)///busca un usuario por su dni
{
    long int dni=DniBuscado();
    nodoArbol*res=BuscarDniEnArbol(arbol,dni);
    while(res==NULL){
        printf("\nDNI no encontrado intente otra vez...\n");
        printf("\n");
        system ("pause");
        system ("cls");
        dni=DniBuscado();
        res=BuscarDniEnArbol(arbol,dni);
    }
    mostrar1Usuario(res->dato);
    system ("pause");
    system ("cls");
}
