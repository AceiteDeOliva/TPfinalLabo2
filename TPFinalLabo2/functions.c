#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include <time.h>

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


