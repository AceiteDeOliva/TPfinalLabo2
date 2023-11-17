#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include <time.h>
#include <windows.h>
int main()
{
srand((unsigned int)time(NULL));
nodoArbol * arbol = (nodoArbol*)malloc(sizeof(nodoArbol));
arbol->der = NULL;
arbol->izq = NULL;
arbol->dato.cbu  = generarCBU(8);
strcpy(arbol->dato.contrasenia ,"hola123");
arbol->dato.genero ='m';
strcpy(arbol->dato.mail,"josevl@live.com");
arbol->dato.dni = 42416416;
strcpy(arbol->dato.nombreApellido,"jose leta");
//
//printf("dbu:%i\n",arbol->dato.cbu);

imprimirUsuario(arbol->dato);
modificarUsuario(arbol);
imprimirUsuario(arbol->dato);

//
//nodoArbol* prueba = existePaciente(arbol,42416416);
//if (prueba != NULL) {
//        printf("Paciente encontrado:\n");
//        printf("CBU: %i\n", prueba->dato.cbu);
//    } else {
//        printf("Paciente no encontrado\n");
//    }


}

