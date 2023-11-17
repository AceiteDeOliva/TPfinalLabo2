#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include <time.h>
#include <windows.h>
int main()
{
nodoArbol * arbol = (nodoArbol*)malloc(sizeof(nodoArbol));
arbol->der = NULL;
arbol->izq = NULL;
arbol->dato.cbu  = 12345678;
strcpy(arbol->dato.contrasenia ,"hola123");
arbol->dato.genero ='m';
strcpy(arbol->dato.mail,"josevl@live.com");
arbol->dato.dni = 42416416;
strcpy(arbol->dato.nombreApellido,"jose leta");


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

menuPrincipal(2);
}

int menuPrincipal(int opcionElegida)
{

    int x=opcionElegida;
    int detectaCuenta = -1;
    char salir;
    int intentos=0;
    int exit;
    usuario ingreso;
    nodoArbol * raiz = fromArchiToArbolDNI(raiz);
    nodoArbol * cuenta = NULL;

    switch(x)
    {
    case 1://crear usuarios
        system("cls");
        CrearUsuario();
//       crearSaldo(cbu);
        break;
    case 2://iniciar sesion |habria que cambiar toda esta parte para que se haga con el arbol
        system("cls");
            printf("e");
        do
        {
            ingreso = inicioSesion();
            printf("a\n");
            cuenta=buscarDNIenArbol(raiz,ingreso.dni);
            printf("b\n");
            detectaCuenta = detectaUsuario(cuenta->dato,ingreso);
            printf("c\n");
            if(detectaCuenta!=0)
            {
//                detectaCuenta=chequeoAdmin(detectaCuenta, cuenta);
                if(detectaCuenta==1)
                {
                    exit=menuInicioSesion(cuenta->dato.cbu);//devuelve 0 si elijes opcion de salir
                }
                else
                {
                    exit=menuAdmin();
                }
            }
            else if(detectaCuenta==0)
            {
                printf("Usuario incorrecto o contraseña incorrecta.\nSi esto le ocurre varias veces, puede que su cuenta haya sido desactivada forzozamente por deudas\n");
            }
            intentos++;
        }
        while(intentos < 3 && exit!=0);
        if(intentos==3)
        {
            printf("Demasiados intentos, volviendo al menu anterior\n");//meti todo esto dentro de un do while para que pueda volver a ingresar los datos en caso de error.
            system("pause");
        }
        break;
    case 0:
        main();
        break;
    default:
        system("cls");
        printf("Ha elegido una opcion que no es las que se le indica, por favor, vuelva a elegir...\n");
        system("pause");
        break;
    }
    return x;
}

