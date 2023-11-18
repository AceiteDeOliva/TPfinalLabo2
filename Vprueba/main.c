#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

///MAIN
int main()
{
    system("color A0");
    int opcion;

    opcion = opcionMenuPrincipal();
    if(opcion==1 ||opcion==2)
    {
        menuPrincipal(opcion);
    }
    return 0;
}

///MENU PRINCIPAL
int opcionMenuPrincipal()
{
    int opcion;

    system("cls");

    do
    {
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
        if(opcion<0 || opcion>3)
        {
            printf("Ha ingresado un numero incorrecto... vuelva a ingresar\n");
            system("pause");
            system("cls");
        }
        if(opcion==3)
        {
            printf("Abriendo ventana admin\n");
            menuAdmin();
            system("pause");
            system("cls");
        }
    }
    while(opcion<0 || opcion>3);

    return opcion;
}


/// MENU PRINCIPAL
int menuPrincipal(int opcionElegida)
{
    funcionConBarraDeCarga();
    int x=opcionElegida;
    int detectaCuenta = 0;
    int intentos=0;
    int exit;
    usuario ingreso;
    nodoArbol * raiz = NULL;
    raiz = fromArchiToArbolDNI(raiz);
    nodoArbol * cuenta = NULL;

    switch(x)
    {
    case 1://crear usuarios
        system("cls");
        CrearUsuario();
        system("cls");
        main();
//       crearSaldo(cbu);
        break;
    case 2://iniciar sesion |habria que cambiar toda esta parte para que se haga con el arbol
        system("cls");
        do
        {
            ingreso = inicioSesion();
            cuenta=buscarDNIenArbol(raiz,ingreso.dni);
            if(cuenta->dato.estado == 0)
            {
                printf("Usuario desactivado hablar con administracion\n");

            }
            else
            {
                detectaCuenta = detectaUsuario(cuenta->dato,ingreso);

                if(detectaCuenta==1)
                {
                    exit=menuInicioSesion(cuenta);//devuelve 0 si elijes opcion de salir
                }
                else if(detectaCuenta==0)
                {
                    printf("Usuario incorrecto o contraseña incorrecta.\nSi esto le ocurre varias veces, puede que su cuenta haya sido desactivada forzozamente por deudas\n");
                }

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


///MENU UNA VEZ INICIADA LA SESION
int menuInicioSesion(nodoArbol * cuenta)
{
    int x;
    char contrasenia[20];
    char confirmacion[20];
    int seguro;
    fromFileToFila(cuenta);
    do
    {
        system("cls");
        printf("                                                 +-----------------+\n");
        printf("                                                 |  BANCO CENTRAL  |  \n");
        printf("                                                 +-----------------+\n");
        printf("\n\n");
        puts("-----------------------------------|");
        printf("[1]VER TU SALD0\n");
        puts("-----------------------------------|");
        printf("[2]VER MOVIMIENTOS\n");
        puts("-----------------------------------|");
        printf("[3]HACER TRANSFERENCIA\n");
        puts("-----------------------------------|");
        printf("[4]PEDIR PRESTAMO\n");
        puts("-----------------------------------|");
        printf("[5]PAGAR PRESTAMO\n");
        puts("-----------------------------------|");
        printf("[6]CAMBIAR CONTRASEÑA\n");
        puts("-----------------------------------|");
        printf("[7]DESACTIVAR CUENTA\n");
        puts("-----------------------------------|");
        printf("[8]VER DATOS DE TU CUENTA\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            printf("Su saldo actual es:%li\n",cuenta->dato.saldo);
            system("pause");
            break;
        case 2:
            system("cls");
            mostrarListaDoble(cuenta->movimiento.cabecera);
            system("pause");
            break;
        case 3:
            system("cls");
            tranferencia(cuenta);
            system("pause");
            break;
        case 4:
//            system("cls");
//            prestamo(cbu);
//            system("pause");
            break;
        case 5:
//            system("cls");
//            pagarPrestamo(cbu);
//            system("pause");
            break;
        case 6:
            system("cls");
            do
            {
                printf("Ingrese su contrasenia nueva por favor...\n");
                fflush(stdin);
                scanf("%s", contrasenia);
                printf("\nIngrese nuevamente la contrasenia:\n");
                fflush(stdin);
                scanf("%s", confirmacion);
                if(strcmp(contrasenia, confirmacion)!=0)
                {
                    printf("Las contrasenias ingresadas no son iguales, por favor, vuelva a ingresar");
                }
            }
            while(strcmp(contrasenia, confirmacion)!=0);

            modPass(contrasenia, cuenta->dato.cbu);
            printf("Contrasenia cambiada con exito...\n");

            system("pause");
            break;
        case 7:
            system("cls");
            seguro=seguroDeseaEliminar();
            if(seguro==1)
            {
                desactivarCuenta(cuenta->dato.cbu);
                x=0;
            }
            system("pause");
            break;
        case 8:
            system("cls");
            muestraUsuarioAdmin(cuenta->dato);
            system("pause");
            break;
        case 0:
            main();
            break;
        default:
            system("cls");
            printf("Ha elegido una opcion que no se encuentra dentro de las disponibles...\n");
            system("pause");
            break;
        }

    }
    while(x!=0);
    return x;
}

///MENU DE ADMIN
int menuAdmin()
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
            main();
            printf("Saliendo del menu...");
            break;
        default:
            system("cls");
            printf("Ha seleccionado una opcion que no está entre las posibles... volviendo al menu\n");
            system("pause");
            break;
        }
    }
    while(x!=0);


    return x;
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

            system("pause");
            break;
        case 3:
            system("cls");

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
        printf("[2]BUSCAR EMPLEAD0 POR DNI\n");
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
