#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"



///MAIN
int main()
{
    usuario cuenta;
    usuario arregloDeUsu[100];
    int opcion;

    opcion = opcionMenuPrincipal();
        if(opcion==1)
        {
          menuPrincipal(opcion, cuenta, arregloDeUsu);
        }
        else if(opcion==2)
        {
          menuPrincipal(opcion, cuenta, arregloDeUsu);
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
        printf("BIENVENIDO AL BANCO ESTEBANQUITO\n");
        printf("------------------------------------------\n");
        printf("Elija una opcion:\n\n");
        printf("1-Crear una cuenta.\n2-Iniciar sesion.\n3-Iniciar sesion como ADMIN.\n0-Salir del programa.\n");
        printf("------------------------------------------\n");
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
    while(opcion<0 || opcion>2);

    return opcion;
}

/// MENU PRINCIPAL
int menuPrincipal(int opcionElegida, usuario cuenta, usuario arreglo[100])
{


    int x=opcionElegida;
    int detectaCuenta;
    char salir;
    int intentos=0;
    int exit;
    char cbu[10];

    switch(x)
    {
    case 1://crear usuarios
        system("cls");
        CrearUsuario(cbu);
        crearSaldo(cbu);
        break;
    case 2://iniciar sesion
        system("cls");
        do
        {
            cuenta=inicioSesion();
            detectaCuenta=detectaUsuario(cuenta, cbu);
            if(detectaCuenta!=0)
            {
                detectaCuenta=chequeoAdmin(detectaCuenta, cuenta);
                if(detectaCuenta==1)
                {
                    exit=menuInicioSesion(cbu, arreglo);//devuelve 0 si elijes opcion de salir
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

///MENU UNA VEZ INICIADA LA SESION
int menuInicioSesion(char cbu[10], usuario arreglo[100])
{
    int x;
    char salir;
    char contrasenia[20];
    char confirmacion[20];
    int matriz[4][7];
    int seguro;
    int flag;
    usuario miUsu;

    do
    {
        system("cls");
        printf("Bienvenido a su cuenta\n");
        printf("--------------------------------------\n");
        printf("Opciones disponibles:\n1-Corroborar saldo.\n3-Hacer transferencia.\n4-Pedir prestamo.\n5-Pagar prestamo.\n6-Cambiar tu contrasenia.\n7-Consulte nuestros dias y horarios de atencion.\n8-Desactivar Cuenta.\n9-Corroborar datos de tu cuenta.\n0-Salir del Menu.\n");
        printf("--------------------------------------\n");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            printf("Su saldo actual es:\n");
            corroborarSaldo(cbu);
            system("pause");
            break;
        case 3:
            system("cls");
            tranferencia(cbu);
            system("pause");
            break;
        case 4:
            system("cls");
            prestamo(cbu);
            system("pause");
            break;
        case 5:
            system("cls");
            pagarPrestamo(cbu);
            system("pause");
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

            modPass(contrasenia, cbu);
            printf("Contrasenia cambiada con exito...\n");

            system("pause");
            break;
        case 7:
            system("cls");
            printf("\033[7m");
            printf("\033[1;31mESTAMOS ABIERTOS TODOS LOS DIAS EN LOS CUALES NO FIGURA 0.\033[0m\n\n");
            printf("\033[0m");
            generaMatrizHorarios(matriz);
            muestraMatrizHorarios(matriz);
            puts("--------------------------------------------");
            printf("Horario de atencion 8:00 A.M - 18:00 P.M.\n");
            puts("--------------------------------------------");
            system("pause");
            break;
        case 8:
            system("cls");
            seguro=seguroDeseaEliminar();
            if(seguro==1){
                desactivarCuenta(cbu);
                x=0;
            }
            system("pause");
            break;
        case 9:
            system("cls");
            miUsu=busquedaUsuXCBU(cbu, &flag);
            muestraUsuarioAdmin(miUsu);
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
    char salir;
    usuario arreglo[100];
    do
    {
        system("cls");
        printf("/////Administracion de usuarios/////\n");
        printf("--------------------------------------\n");
        printf("Opciones disponibles:\n1-Ver usuarios registrados\n2-Desactivar usuario/s\n0-Salir del Menu.\n");
        printf("--------------------------------------\n");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            verUsuariosMenu(arreglo, 100);
            system("pause");
            break;
        case 2:
            system("cls");
            darDeBajaOAltaAdmin();
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
void verUsuariosMenu(usuario arreglo[], int dimensionarray)
{
    int x;
    char salir;
    char cbu[10]={};
    long int dni=0;
    usuario usuBuscado;
    usuario usuBuscado2;
    int flag=0;
    int validos=0;

    nodoArbol* arbol=inicArbol();
    nodoListaS* lista=inicLista();

    do
    {
        system("cls");
        printf("/////Ver usuarios/////\n");
        printf("--------------------------------------\n");
        printf("Opciones disponibles:\n1-Ver todos los usuarios ordenados por dni\n2-Buscar 1 usuario por DNI.\n0-Salir del Menu.\n");
        printf("--------------------------------------\n");
        fflush(stdin);
        scanf("%d", &x);

        switch(x)
        {
        case 1:
            system("cls");
            printf("ORDENADO POR DNI:\n");
            validos=ArchiToArray(arreglo, dimensionarray);
            ordenaxDNI(arreglo, validos);
            lista=fromArregloDeEstructurasToLista(lista, arreglo, validos);
            mostrarLista(lista);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Ingrese el DNI del usuario que desea buscar.\n");
            fflush(stdin);
            scanf("%ld", &dni);
            usuBuscado2=busquedaUsuXDNI(dni, &flag);
            if(flag==1)
            {
                muestraUsuarioAdmin(usuBuscado2);
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
