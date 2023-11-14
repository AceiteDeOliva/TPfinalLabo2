#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"
#include <unistd.h>

int main()
{
    usuario cuenta;
    usuario arregloDeUsu[100];

    int opcion;
    do
    {
        opcion = opcionMenuPrincipal();
        opcion = menuPrincipal(opcion, cuenta, arregloDeUsu);

    }
    while(opcion!=0);


    return 0;
}

///Funciones:
int opcionMenuPrincipal()
{
    int opcion;

    system("cls");

    do
    {

        imprimir_letra_por_letra("    \033[1;31mBIENVENIDO AL BANCO ESTEBANQUITO\033[0m    \n");
        printf("------------------------------------------\n");
        printf("Elija una opcion:\n\n");
        printf("1-Crear una cuenta.\n2-Iniciar sesion.\n0-Salir del programa.\n");
        printf("------------------------------------------\n");
        fflush(stdin);
        scanf("%i", &opcion);
        if((opcion<0 || opcion>3) && opcion != 123)
        {
            printf("Ha ingresado un numero incorrecto... vuelva a ingresar\n");
            system("pause");
            system("cls");
        }
        if(opcion==123)
        {
            printf("Comando especial ejecutado con exito, Abriendo ventana admin\n");
            menuAdmin();
            system("pause");
            system("cls");
        }
    }
    while(opcion<0 || opcion>2);

    return opcion;
}


int menuPrincipal(int opcionElegida, usuario cuenta, usuario arreglo[100])
{


    int x = opcionElegida;
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
                printf("Usuario incorrecto o contrase�a incorrecta.\nSi esto le ocurre varias veces, puede que su cuenta haya sido desactivada forzozamente por deudas\n");
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
        salir=deseaSalir();

        if(salir=='n')
        {
            x = 1;
        }
        break;
    default:
        system("cls");
        printf("Ha elegido una opcion que no es las que se le indica, por favor, vuelva a elegir...\n");
        system("pause");
        break;
    }
    return x;
}

int menuInicioSesion(char cbu[10], usuario arreglo[100])
{
    int x;
    char salir;
    char contrasenia[20];
    char confirmacion[20];
    int seguro;
    int flag;
    usuario miUsu;

    do
    {
        system("cls");
        printf("Bienvenido a su cuenta\n");
        printf("--------------------------------------\n");
        printf("Opciones disponibles:\n1-Corroborar saldo.\n2-Agregar saldo.\n3-Hacer transferencia.\n4-Pedir prestamo.\n5-Pagar prestamo.\n6-Cambiar tu contrasenia.\n7-Desactivar Cuenta.\n8-Corroborar datos de tu cuenta.\n0-Salir del Menu.\n");
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
        case 2:
            system("cls");
            AgregarSaldoCuenta(cbu);
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
            seguro=seguroDeseaEliminar();
            if(seguro==1){
                desactivarCuenta(cbu);
                x=0;
            }
            system("pause");
            break;
        case 8:
            system("cls");
            miUsu=busquedaUsuXCBU(cbu, &flag);
            muestraUsuarioAdmin(miUsu);
            system("pause");
            break;
        case 0:
            salir = deseaSalir();
            if(salir =='n')
            {
                x=1;
            }
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
///MENU ADMINS:

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
            system("cls");
            salir=deseaSalir();
            if(salir=='n')
            {
                x=1;
            }
            else
            {
                printf("Saliendo del menu...");
            }
            break;
        default:
            system("cls");
            printf("Ha seleccionado una opcion que no est� entre las posibles... volviendo al menu\n");
            system("pause");
            break;
        }
    }
    while(x!=0);


    return x;
}

void verUsuariosMenu(usuario arreglo[], int dimensionarray)
{
    int x;
    char salir;
    int validos;
    char cbu[10]={};
    long int dni=0;
    usuario usuBuscado;
    usuario usuBuscado2;
    int flag=0;

    do
    {
        system("cls");
        printf("/////Ver usuarios/////\n");
        printf("--------------------------------------\n");
        printf("Opciones disponibles:\n1-Ver todos los usuarios ordenados por dni\n2-Ver todos los usuarios ordenados por genero\n3-Ver todos los usuarios ordenados por nombre\n4-Buscar 1 usuario por CBU.\n5-Buscar 1 usuario por DNI.\n0-Salir del Menu.\n");
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
            muestraArregloUsuarios(arreglo, validos);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("ORDENADO POR GENERO:\n");
            validos=ArchiToArray(arreglo, dimensionarray);
            ordenaXgenero(arreglo, validos);
            muestraArregloUsuarios(arreglo, validos);
            system("pause");
            break;
        case 3:
            system("cls");
            printf("ORDENADO POR NOMBRE:\n");
            validos=ArchiToArray(arreglo, dimensionarray);
            ordenaXnombre(arreglo, validos);
            muestraArregloUsuarios(arreglo, validos);
            system("pause");
            break;
        case 4:
            system("cls");
            printf("Ingrese le CBU del usuario que desea buscar.\n");
            fflush(stdin);
            gets(cbu);
            usuBuscado=busquedaUsuXCBU(cbu, &flag);
            if(flag==1)
            {
                muestraUsuarioAdmin(usuBuscado);
            }
            else
            {
                printf("Usuario no encontrado.\n");
            }
            system("pause");
            break;
        case 5:
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
            system("cls");
            salir=deseaSalir();
            if(salir=='n')
            {
                x=1;
            }
            else
            {
                printf("Saliendo del menu...\n");
            }
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