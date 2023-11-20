#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

///MENU PRINCIPAL
int main()
{
    system("color A0");
    int opcion = -1;

    while(opcion != 0)
    {
        system("cls");

        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("------------------------------|");
        printf("[1]CREAR CUENTA\n");
        puts("------------------------------|");
        printf("[2]INICIAR SESION\n");
        puts("------------------------------|");
        printf("[3]INICIAR SESION COMO ADMIN\n");
        puts("------------------------------|");
        printf("[0]SALIR\n");
        puts("------------------------------|");
        fflush(stdin);
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 1:

            menuPrincipal(opcion);
            break;
        case 2:

            menuPrincipal(opcion);
            break;

        case 3:
            printf("Abriendo ventana admin\n");
            menuAdmin();
            system("pause");
            system("cls");
            break;
        case 0:
            printf("Programa finalizado...\n");
            break;
        default:
            printf("Opcion no valida\n");
            system("pause");
            break;

        }
    }

    return 0;
}


/// MENU PRINCIPAL
void menuPrincipal(int opcionElegida)
{
    funcionConBarraDeCarga();
    int x=opcionElegida;
    int chequeo = 0;
    int intentos=0;
    usuario ingreso;
    nodoArbol * raiz = NULL;
    raiz = fromArchiToArbolDNI(raiz);
    nodoArbol * cuenta = NULL;

    switch (x)
    {
    case 1: // Crear usuarios
        system("cls");
        CrearUsuario();
        system("cls");
        break;
    case 2: // Iniciar sesion
        system("cls");
        do
        {
            ingreso = inicioSesion();
            cuenta = buscarDNIenArbol(raiz, ingreso.dni);
            if(cuenta)
            {
                if (cuenta->dato.estado == 0)
                {
                    printf("Usuario desactivado hablar con administracion\n");
                }
                else
                {
                    chequeo = chequeoCredenciales(cuenta->dato, ingreso);
                    if (chequeo == 1)
                    {
                        menuInicioSesion(cuenta);
                    }

                }
            }
            printf("Usuario incorrecto o contrasenia incorrecta.\n");
            intentos++;
        }
        while (intentos < 3);
        if (intentos == 3)
        {
            printf("Demasiados intentos, volviendo al menu anterior\n");
        }
        break;
    default:
        system("cls");
        printf("Ha elegido una opcion que no es las que se le indica, por favor, vuelva a elegir...\n");
        system("pause");
        break;
    }

}


///MENU UNA VEZ INICIADA LA SESION
void menuInicioSesion(nodoArbol * cuenta)
{
    int x;
    int seguro = 0;
    fila movimientos;
    inicFila(&movimientos);
    nodoArbol * raiz = NULL;
    raiz = fromArchiToArbolCBU(raiz);

    do
    {
        system("cls");
        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("-----------------------------------|");
        printf("[1]VER MOVIMIENTOS\n");
        puts("-----------------------------------|");
        printf("[2]DEPOSITAR/EXTRAER\n");
        puts("-----------------------------------|");
        printf("[3]HACER TRANSFERENCIA\n");
        puts("-----------------------------------|");
        printf("[4]VER DATOS DE TU CUENTA\n");
        puts("-----------------------------------|");
        printf("[5]CAMBIAR CONTRASENIA\n");
        puts("-----------------------------------|");
        printf("[6]DESACTIVAR CUENTA\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            fromFileToFila(cuenta,&movimientos);
            recorrerMostrarExtraerFila(&movimientos);
            printf("Su saldo actual es:%li\n",cuenta->dato.saldo);
            puts("-----------------------------------|");
            system("pause");
            break;

        case 2:
            system("cls");
            depositarExtraer(cuenta,&movimientos);
            system("pause");
            break;
        case 3:
            system("cls");
            carga1Transfer (raiz,cuenta,&movimientos);
            system("pause");
            break;
        case 4:
            system("cls");
            muestra1Usuario(cuenta->dato);
            system("pause");
            break;
        case 5:
            system("cls");
            cuenta->dato = newPass(cuenta->dato);
            reemplazarDato(cuenta->dato);
            printf("Contrasenia cambiada con exito...\n");
            system("pause");
            break;
        case 6:
            system("cls");
            seguro=seguroDeseaEliminar();
            if(seguro==1)
            {
                cuenta->dato = desactivar(cuenta->dato);
                reemplazarDato(cuenta->dato);
                x=0;
            }
            system("pause");
            break;
        case 0:
            borrarArbol(raiz);
            x = 0;
            break;
        default:
            system("cls");
            printf("Ha elegido una opcion que no se encuentra dentro de las disponibles...\n");
            system("pause");
            break;
        }

    }
    while(x!=0);
    main();
}

///MENU DE ADMIN
void menuAdmin()
{
    int x;
    do
    {
        system("cls");
        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("------------------------------|");
        printf("[1]USUARIOS\n");
        puts("------------------------------|");
        printf("[2]EMPLEADOS\n");
        puts("------------------------------|");
        printf("[0]SALIR\n");
        puts("------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            verUsuariosMenu();
            system("pause");
            break;
        case 2:
            system("cls");
            verEmpleadosMenu();
            system("pause");
            break;
        case 0:
            printf("Saliendo del menu...");
            main();
            break;
        default:
            system("cls");
            printf("Ha seleccionado una opcion que no está entre las posibles... volviendo al menu\n");
            system("pause");
            break;
        }
    }
    while(x!=0);


}

///MENU DE ADMIN PARA VER USUARIOS DE DISTINTAS FORMAS
void verUsuariosMenu()
{
    int x;
    long int dni=0;
    nodoArbol* arbol=inicArbol();
    nodoListaS* lista=inicLista();
    nodoArbol* nodoBuscado = NULL;

    do
    {
        system("cls");
        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("-----------------------------------|");
        printf("[1]VER USUARIOS ORDENADOS POR DNI\n");
        puts("-----------------------------------|");
        printf("[2]BUSCAR USUARIO POR DNI\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            printf("ORDENADO POR DNI:\n");
            nodoBuscado = fromArchiToArbolDNI(nodoBuscado);
            mostrarArbolInorden(nodoBuscado);
//            lista=FromArchiAListaOrdenada(lista);
//            mostrarLista(lista);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("                                                 +-----------------+\n");
            printf("                                                 |  BANCO CENTRAL  |  \n");
            printf("                                                 +-----------------+\n");
            printf("\n\n");
            printf("\nINGRESE DNI DEL USUARIO QUE DESEA BUSCAR: ");
            fflush(stdin);
            scanf("%ld", &dni);
            arbol=fromArchiToArbolDNI(arbol);
            nodoBuscado=buscarDNIenArbol(arbol, dni);

            if(nodoBuscado != NULL)
            {
                menuOpcionesAdminUsuario(nodoBuscado);

            }
            else
            {
                printf("Usuario no encontrado.\n");
            }
            system("pause");
            break;
        case 0:
            menuAdmin();
            break;
        default:
            system("cls");
            printf("Ha ingresado una opcion que esta fuera de las posibles... volviendo al menu");
            system("pause");
            break;
        }
    }
    while(x!=0);
}

void menuOpcionesAdminUsuario(nodoArbol* usuarioBuscado)
{
    int x;
    fila movimientos;
    inicFila(&movimientos);

    do
    {
        system("cls");
        muestra1Usuario(usuarioBuscado->dato);

        puts("-----------------------------------|");
        printf("[1]MODIFICAR USUARIO\n");
        puts("-----------------------------------|");
        printf("[2]DAR DE BAJA/ALTA\n");
        puts("-----------------------------------|");
        printf("[3]VER HISTORIAL DE TRANSACCIONES\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");

            usuarioBuscado = modificarUsuario(usuarioBuscado);
            reemplazarDato(usuarioBuscado->dato);
            system("pause");
            break;
        case 2:
            system("cls");
            usuarioBuscado->dato = altaBaja(usuarioBuscado->dato);
            reemplazarDato(usuarioBuscado->dato);
            system("pause");
            break;
        case 3:
            system("cls");
            fromFileToFila(usuarioBuscado,&movimientos);
            recorrerMostrarExtraerFila(&movimientos);
            printf("Saldo:%li\n", usuarioBuscado->dato.saldo);

            system("pause");
            break;
        case 0:
            verUsuariosMenu();
            break;
        default:
            system("cls");
            printf("Ha ingresado una opcion que esta fuera de las posibles... volviendo al menu");
            system("pause");
            break;
        }
    }
    while(x!=0);
}

void verEmpleadosMenu()
{
    int x;
    int validos=0;

    celda adlEmpleados[5];

    do
    {
        system("cls");
        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("-----------------------------------|");
        printf("[1]VER EMPLEADOS ORDENADOS POR DNI\n");
        puts("-----------------------------------|");
        printf("[2]BUSCAR EMPLEADO POR DNI\n");
        puts("-----------------------------------|");
        printf("[3]AGREGAR NUEVO EMPLEADO\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            validos=fromArchiEmpleadosToADL(adlEmpleados, 5);
            mostrarADLempleados(adlEmpleados,validos);
            system("pause");
            break;
        case 2:
            system("cls");
            mostrarArchi();
            system("pause");
            break;
        case 3:
            system("cls");
            cargarArchiEmpleados();
            system("pause");
            break;
        case 0:
            menuAdmin();
            break;
        default:
            system("cls");
            printf("Ha ingresado una opcion que esta fuera de las posibles... volviendo al menu");
            system("pause");
            break;
        }
    }
    while(x!=0);
}
