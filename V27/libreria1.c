#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"
#include <conio.h>
#include <unistd.h>


///Funciones de sistema
///sobreescribe un dato usuario en el archivo
void reemplazarDato(usuario usu)
{

    FILE*archi=fopen(archivo,"r+b");

    usuario aux; // es necesario ya que se necesita almacenar el dato leido del archivo
    if(archi)
    {

        while(fread(&aux,sizeof(usuario),1,archi)>0)
        {

            if(usu.dni==aux.dni)
            {
                fseek(archi, -sizeof(usuario), SEEK_CUR);  // Retrocede el cursor y vuelve un paso para atras para que quede em e� mismo lugar
                fwrite(&usu, sizeof(usuario), 1, archi);
                break;


            }

        }
        fclose(archi);

    }

}

//funciones de creacion de usuario
///RETORNA 1 SI EXISTE EL MAIL Y 0 SI NO EXISTE
int chequeomail (char mail[])
{

    usuario usu;
    int flag=0;
    FILE* buffer;
    buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(flag==0 && fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(strcmpi(usu.mail,mail)==0)
            {
                flag=1;
            }
            else
            {
                flag=0;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        system("pause");
    }
    return flag;
}

///CARGA A UN ARCHIVO LOS DATOS DE UN USUARIO NUEVO
void CrearUsuario()
{
    usuario nuevoUsuario;

    FILE* buffer;
    buffer=fopen(archivo, "ab");
    if(buffer!=NULL)
    {
        nuevoUsuario=crea1Usuario(nuevoUsuario);
        fwrite(&nuevoUsuario, sizeof(usuario), 1, buffer);

        fclose(buffer);
        printf("\nUsuario creado con exito!!\n");
        system("pause");
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO DE USUARIOS");
    }

}

///RETORNA UNA ESTRUCTURA USUARIO CARGADA POR EL USUARIO
usuario crea1Usuario (usuario nuevoUsuario)
{
    int flag=0;
    int flag1=0;
    dibujoBancoCentral();

    printf("PORFAVOR INGRESE LOS SIGUIENTES DATOS.\n");

    printf("\nNOMBRE Y APELLIDO: ");
    fflush(stdin);
    gets(nuevoUsuario.nombreApellido);

    do
    {
        printf("\nGENERO (m/f): ");
        fflush(stdin);
        scanf("%c", &nuevoUsuario.genero);
        if(nuevoUsuario.genero !='m'&& nuevoUsuario.genero!='f')
        {
            printf("\nLetra incorrecta, vuelva a ingresar..");
        }
    }
    while(nuevoUsuario.genero !='m'&& nuevoUsuario.genero!='f');

    printf("\nDNI: ");
    fflush(stdin);
    scanf("%i", &nuevoUsuario.dni);
    flag1=chequeoDNI(nuevoUsuario.dni);
    do
    {
        if (flag1==1)
        {
            printf("Este DNI ya existe, ingrese otro por favor: ");
            fflush(stdin);
            scanf("%i", &nuevoUsuario.dni);
            flag1=chequeoDNI(nuevoUsuario.dni);
        }
    }
    while(flag1==1);


    int tieneArroba;

    do
    {
        // Solicitar al usuario que ingrese el email
        printf("\nMAIL: ");
        fflush(stdin);
        gets(nuevoUsuario.mail);
        nuevoUsuario.mail[strcspn(nuevoUsuario.mail, "\n")] = '\0'; // Eliminar el salto de linea al final

        // Verificar si el email contiene '@'
        tieneArroba = strchr(nuevoUsuario.mail, '@') != NULL;

        // Si no contiene '@', mostrar un mensaje de error
        if (!tieneArroba)
        {
            printf("El email debe contener '@'. Por favor, intentelo de nuevo.\n");
        }



        flag=chequeomail(nuevoUsuario.mail);
        do
        {
            if (flag==1)
            {
                printf("Este mail ya existe, ingrese otro por favor: ");
                gets(nuevoUsuario.mail);
                flag=chequeomail(nuevoUsuario.mail);
            }
        }
        while(flag==1);
    }
    while (!tieneArroba && flag !=1);

    char contrasenia[20];

    printf("\nPASSWORD: ");
    int i = 0;

    while (1)
    {
        char ch = _getch();

        if (ch == 13)
        {
            break;  // Si el caracter es 'Enter', rompe el bucle
        }
        else if (ch == 8 && i > 0)
        {
            // Si el caracter es Backspace y hay caracteres para borrar
            printf("\b \b");  // Borra el ultimo caracter en la pantalla
            i--;
        }
        else if (i < sizeof(contrasenia) - 1)
        {
            // Si hay espacio para mas caracteres
            contrasenia[i++] = ch;
            printf("*");  // Muestra un asterisco en lugar del caracter
        }
    }

    contrasenia[i] = '\0';

    strcpy(nuevoUsuario.contrasenia,contrasenia);
    //printf("la contrsenia es %s ",nuevoUsuario.contrasenia);

    srand((unsigned int)time(NULL));
    nuevoUsuario.cbu = generarCBU(8);

    nuevoUsuario.estado=1;

    nuevoUsuario.saldo = 0;

    return nuevoUsuario;
}

///RETORNA 1 SI EL MAIL Y LA CONTRASE�A PERTENECENEN A UNA CUENTA Y 0 SI NO
int chequeoCredenciales(usuario usuBuscado, usuario ingreso) //se deberia hacer por arbol
{
    int flag=0;
    if(strcmp(usuBuscado.mail, ingreso.mail)== 0 && strcmp(usuBuscado.contrasenia,ingreso.contrasenia)== 0)
    {

        flag = 1;

    }

    return flag;
}

//Genera un numero aleatorio del 0 al 9
int generarDigitoAleatorio()
{
    return rand() % 10;
}

//funcion para generar el cbu, se le pasa la cantidad de digitos (8)
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
///Carga una variable usuario para luego comparar con el arbol y validar el inicio de sesion
usuario inicioSesion()
{
    dibujoBancoCentral();
    usuario usuInicioSesion;
    printf("\nDNI: ");
    fflush(stdin);
    scanf("%i",&usuInicioSesion.dni);

    printf("\nMAIL: ");
    fflush(stdin);
    gets(usuInicioSesion.mail);

    printf("\nPASSWORD: ");

    char contrasenia[20];
    int i=0;
    while (1)
    {
        char ch = _getch();

        if (ch == 13)
        {
            break;  // Si el caracter es 'Enter', rompe el bucle
        }
        else if (ch == 8 && i > 0)
        {
            // Si el caracter es Backspace y hay caracteres para borrar
            printf("\b \b");  // Borra el ultimo caracter en la pantalla
            i--;
        }
        else if (i < sizeof(contrasenia) - 1)
        {
            // Si hay espacio para mas caracteres
            contrasenia[i++] = ch;
            printf("*");  // Muestra un asterisco en lugar del caracter
        }
    }

    contrasenia[i] = '\0';

    strcpy(usuInicioSesion.contrasenia, contrasenia);

    return usuInicioSesion;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///FUNCIONES LUEGO DE INICIAR SESION:
///Agrega/resta saldo a la cuenta
void depositarExtraer(nodoArbol * cuenta)
{
    int opcion = -1;
    movimiento efectivo;
    system("cls");
    dibujoBancoCentral();
    puts("-----------------------------------|");
    printf("[1]DEPOSITAR\n");
    puts("-----------------------------------|");
    printf("[2]EXTRAER\n");
    puts("-----------------------------------|");
    printf("[0]SALIR\n");
    puts("-----------------------------------|");
    fflush(stdin);
    scanf("%i",&opcion);
    efectivo = generarDeposito(cuenta);
    switch(opcion)
    {

    case 1:

        efectivo.tipoDeOperacion = 1;
        cuenta->dato.saldo += efectivo.monto;
        reemplazarDato(cuenta->dato);
        movimientoAArchivo(efectivo);
        break;

    case 2:
        efectivo.tipoDeOperacion = 0;
        if(cuenta->dato.saldo >= efectivo.monto)
        {

            cuenta->dato.saldo -= efectivo.monto;
            reemplazarDato(cuenta->dato);
            movimientoAArchivo(efectivo);

        }
        else
        {

            printf("Saldo insuficiente\n");

        }

        break;

    case 0:
        menuInicioSesion(cuenta);
        break;

    default:

        printf("Opcion no valida\n");
        break;

    }

}
///MOVIMIENTOS
/// genera una variable movimiento de un deposito o extraccino para luego guardar en el archivo
movimiento generarDeposito(nodoArbol * cuenta)
{

    movimiento nuevoDeposito;

    nuevoDeposito.fecha = time(NULL);

    nuevoDeposito.cbuEmisor = cuenta->dato.cbu;

    nuevoDeposito.cbuReceptor = cuenta->dato.cbu;

    nuevoDeposito.tipoDeOperacion = -1;

    printf("Ingrese el monto:\n");
    fflush(stdin);
    scanf("%d", &nuevoDeposito.monto);

    return nuevoDeposito;
}

//Carga datos de la transferencia
///genera la varible movimiento de una transferencia que luego se guarda en el archivo y se agrega a la lista
void carga1Transfer (nodoArbol * raiz,nodoArbol * cuenta)
{
    movimiento transfer;
    transfer.fecha = time(NULL);
    transfer.cbuEmisor = cuenta->dato.cbu;
    transfer.tipoDeOperacion = 0;

    printf("Ingrese el monto:\n ");
    fflush(stdin);
    scanf("%i", &transfer.monto);

    if (transfer.monto <= cuenta->dato.saldo)
    {

        do
        {
            printf("Ingrese el cbu del destinatario (-1 para cancelar):\n");
            fflush(stdin);
            scanf("%i", &transfer.cbuReceptor);

            if (transfer.cbuReceptor == -1)
            {
                printf("Operaci�n cancelada.\n");
                break;
            }

            if (cuenta->dato.cbu == transfer.cbuReceptor)
            {
                printf("No se puede transferir a usted mismo, por favor intente de nuevo.\n");
                transfer.monto = 0;
            }
            else
            {
                nodoArbol* receptor = buscarCBUenArbol(raiz, transfer.cbuReceptor);

                if (receptor != NULL)
                {
                    cuenta->dato.saldo -= transfer.monto;
                    reemplazarDato(cuenta->dato);
                    movimientoAArchivo(transfer);

                    receptor->dato.saldo += transfer.monto;
                    reemplazarDato(receptor->dato);
                    transfer.tipoDeOperacion = 1;
                    movimientoAArchivo(transfer);

                    printf("Usuario encontrado correctamente, transferencia exitosa.\n");
                    break;
                }
                else
                {
                    printf("Usuario no encontrado, por favor intente con otro CBU.\n");
                }
            }
        }
        while (1);
    }
    else
    {
        printf("Saldo insuficiente\n");
    }
}

//carga el archivo de movimientos
void movimientoAArchivo(movimiento aux)
{
    FILE* file = fopen(archivo3, "ab");

    if (file == NULL)
    {
        perror("Error abriendo archivo\n");
        return;
    }

    fwrite(&aux, sizeof(movimiento), 1, file);

    fclose(file);
}

//Pasa del archivo de movimientos a la fila
void fromFileToFila(nodoArbol * cuenta,fila * filita)
{
    movimiento aux;
    FILE* file = fopen(archivo3, "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while(fread(&aux, sizeof(movimiento), 1, file)== 1)
    {
        if(cuenta->dato.cbu == aux.cbuEmisor && aux.tipoDeOperacion ==0)
        {

            agregarAFila(filita,aux);

        }
        else if(cuenta->dato.cbu == aux.cbuReceptor && aux.tipoDeOperacion == 1)
        {

            agregarAFila(filita,aux);

        }


    }

    fclose(file);
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//Modificacion de usuario
///RETORNA UN USUARIO CON LA NUEVA CONTRASENIA
usuario newPass(usuario usu)
{
    char contrasenia[20];
    char confirmacion[20];
    do
    {
        dibujoBancoCentral();
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
    strcpy(usu.contrasenia,confirmacion);
    return usu;
}

///Da de baja o alta el usuario(cambia su estado a 1 o 0) y devuelve el usuario modificado
usuario altaBaja (usuario usu)
{
    muestraUsuarioAdmin(usu);

    int eleccion = -1;

    while(eleccion!=0)
    {
        system("cls");
        dibujoBancoCentral();
        muestra1Usuario(usu);
        puts("\n-----------------------------------|");
        printf("[1]DAR DE BAJA\n");
        puts("-----------------------------------|");
        printf("[2]DAR DE ALTA\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%i",&eleccion);

        switch(eleccion)
        {
        case 1:
            usu.estado=0;
            break;
        case 2:
            usu.estado=1;
            break;
        case 0:
            break;
        default:
            printf("opcion no valida.\n");
            break;
        }
    }
    return usu;
}

///PREGUNTA SI ESTAS SEGURO DE ELIMINAR LA CUENTA RETORNA 1-0
int seguroDeseaEliminar()
{
    int desicion=0;
    char seguro;
    printf("Seguro que usted desea desactivar su cuenta? \n(No la podra volver a activar por este campo, debera ir personalmente)\ns o n:    ");
    fflush(stdin);
    scanf("%c", &seguro);
    if(seguro=='s')
    {
        desicion=1;
    }
    return desicion;
}

///MUESTRA DATOS DE UN USUARIO
void muestra1Usuario(usuario usu)
{
    char genero[10];
    char estado[10];
    if(usu.genero=='f')
    {
        strcpy(genero, "FEMENINO");
    }
    else if(usu.genero=='m')
    {
        strcpy(genero, "MASCULINO");
    }

    if(usu.estado==1)
    {
        strcpy(estado, "ACTIVO");
    }
    else
    {
        strcpy(estado, "INACTIVO");
    }


    puts("                                     --------------------------------------------");
    printf("                                    | DNI: %-8i                             |\n", usu.dni);
    printf("                                      NOMBRE Y APELLIDO: %s\n", usu.nombreApellido);
    printf("                                    | GENERO: %-8s                           |\n", genero);
    printf("                                      MAIL: %s\n", usu.mail);
    printf("                                    | CBU: %08d                              |\n", usu.cbu);
    printf("                                      ESTADO: %s\n", estado);
    puts("                                     --------------------------------------------");
}

///IMPRIME UN USUARIO POR PANTALLA
void muestraUsuarioAdmin(usuario usu)
{
    char estado[9];
    char genero[10];

    if(usu.estado==1)
    {
     strcpy(estado, "ACTIVO");
    }
    else if(usu.estado==0)
    {
        strcpy(estado, "INACTIVO");
    }

    if(usu.genero=='f')
    {
         strcpy(genero, "FEMENINO");
    }
    else if(usu.genero=='m')
    {
         strcpy(genero, "MASCULINO");
    }
    printf("      | %-15s%-23s%-13s%-15d%-30s%-9d|\n", estado, usu.nombreApellido, genero, usu.dni, usu.mail, usu.cbu);

}

///SI ENCUENTRA EL DNI RETORNA 1 SINO 0
int chequeoDNI(int dni)
{
    usuario usu;
    int flag=0;
    FILE* buffer;
    buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(flag==0 && fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(usu.dni==dni)
            {
                flag=1;
            }
            else
            {
                flag=0;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        system("pause");
    }
    return flag;
}

//Modifica un usuario dependiendo de la opcion que elija
usuario modificarUsuario(usuario dato)
{
    int eleccion = -1;
    int tieneArroba;
    int flag;

    while (eleccion != 0)
    {

        system("cls");
        dibujoBancoCentral();
        muestra1Usuario(dato);

        printf("[MODIFICAR]\n");
        puts("-----------------------------------|");
        printf("[1]NOMBRE Y APELLIDO\n");
        puts("-----------------------------------|");
        printf("[2]GENERO\n");
        puts("-----------------------------------|");
        printf("[3]MAIL\n");
        puts("-----------------------------------|");
        printf("[4]CONTRASENIA\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%i", &eleccion);

        switch (eleccion)
        {
        case 1:
            printf("Nuevo nombre y apellido:\n");
            fflush(stdin);
            gets(dato.nombreApellido);
            break;
        case 2:
            printf("Nuevo genero (m-f): \n");
            fflush(stdin);
            scanf("%c", &dato.genero);
            while(dato.genero!='m' && dato.genero!='f')
            {
                printf("Ese genero no existe. Porfavor ingrese m (masculino) f (femenino).\n");
                fflush(stdin);
                scanf("%c", &dato.genero);
            }
            break;
        case 3:
    do {
        printf("Ingrese el nuevo Mail: \n");
        fflush(stdin);

        fgets(dato.mail, sizeof(dato.mail), stdin);
        dato.mail[strcspn(dato.mail, "\n")] = '\0'; // Remove newline character

        tieneArroba = strchr(dato.mail, '@') != NULL;

        if (!tieneArroba) {
            printf("El email debe contener '@'. Por favor, intentelo de nuevo.\n");
        } else {
            flag = chequeomail(dato.mail);
            if (flag == 1) {
                printf("Este mail ya existe, ingrese otro por favor: \n");
            }
        }
    } while (!tieneArroba || flag == 1);
            break;
        case 4:
            printf("Nueva contrasenia:\n");
            fflush(stdin);
            gets(dato.contrasenia);
            break;
        case 0:

            break;
        default:
            printf("Opcion no valida\n");
            break;

        }
    }
    return dato;
}

///funcion para grafico de barra de carga
void funcionConBarraDeCarga()
{
    const int totalIteraciones = 100; // N�mero total de iteraciones de tu funci�n
    int progreso;

    printf("\n\n\n\n\n\n\n\n");
    for (progreso = 0; progreso <= totalIteraciones; ++progreso)
    {
        // Simula la ejecuci�n de tu funci�n
        // ...

        // Imprime la barra de carga
        printf("\r                        Progreso: [");
        for (int i = 0; i < progreso * 50 / totalIteraciones; ++i)
        {
            printf("=");
        }
        for (int i = progreso * 50 / totalIteraciones; i < 50; ++i)
        {
            printf(" ");
        }
        printf("] %3d%%", progreso * 100 / totalIteraciones);

        // Simula un retardo para ajustar la velocidad de la barra de carga
        usleep(100);  // Retardo de 50,000 microsegundos (0.05 segundos)
    }

    printf("\n");
}

///funcion para grafico de barra de carga igual a la anterior pero con carga mas lenta, asi permite leer el mensaje antes de volver al main
void funcionConBarraDeCargaLento()
{
    const int totalIteraciones = 100; // N�mero total de iteraciones de tu funci�n
    int progreso;

    printf("\n\n\n\n\n\n\n\n\n");
    for (progreso = 0; progreso <= totalIteraciones; ++progreso)
    {
        // Simula la ejecuci�n de tu funci�n
        // ...

        // Imprime la barra de carga
        printf("\r                        Progreso: [");
        for (int i = 0; i < progreso * 50 / totalIteraciones; ++i)
        {
            printf("=");
        }
        for (int i = progreso * 50 / totalIteraciones; i < 50; ++i)
        {
            printf(" ");
        }
        printf("] %3d%%", progreso * 100 / totalIteraciones);

        // Simula un retardo para ajustar la velocidad de la barra de carga
        usleep(50000);  // Retardo de 50,000 microsegundos (0.05 segundos)
    }

    printf("\n");
}
///funcion de prints para mostrar el logo del banco
void dibujoBancoCentral()
{
    printf("\n");
    printf("                                           $-----------------------------$\n");
    printf("                                           |  B A N C O   C E N T R A L  |\n");
    printf("                                           $-----------------------------$\n");
    printf("\n\n\n\n\n");
}

///Funcion que modifica el empleado dependiendo de la eleccion
int modificarEmpleado(celda trabajo[],int posTrabajo,nodoEmpleado**empleadoBuscado,int*validos)///inicializar i en 0
{
    int i2=-1;
    int eleccion=-1;

    while(eleccion != 0)
    {
        dibujoBancoCentral();
        mostrarEmpleado(trabajo,posTrabajo,(*empleadoBuscado)->dato);
        printf("[MODIFICAR]\n");
        puts("-----------------------------------|");
        printf("[1]NOMBRE Y APELLIDO\n");
        puts("-----------------------------------|");
        printf("[2]FECHA DE NACIMIENTO\n");
        puts("-----------------------------------|");
        printf("[3]TRABAJO\n");
        puts("-----------------------------------|");
        printf("[4]NUMERO DE TELEFONO\n");
        puts("-----------------------------------|");
        printf("[0]SALIR\n");
        puts("-----------------------------------|");
        fflush(stdin);
        scanf("%i",&eleccion);

        switch(eleccion)
        {
        case 1:
            printf("Nuevo nombre y apellido:\n");
            fflush(stdin);
            gets((*empleadoBuscado)->dato.nombreYapellido);
            break;
        case 2:
            printf("Nueva fecha(xx/xx/xxxx):\n");
            fflush(stdin);
            gets((*empleadoBuscado)->dato.fechaDeNacimiento);
            break;
        case 3:

            printf("Nuevo trabajo:\n");
            fflush(stdin);
            char trabajoNom[20];
            scanf("%s",trabajoNom);

            if(verificarTrabajoRepetido(trabajo,*validos,trabajoNom)==1)
            {
                i2=posTrabajo;
                posTrabajo=RetornarPosTrabajo(trabajo,trabajoNom,*validos);
                trabajo[posTrabajo].listaEmpleados=agregarEmpleadoEnOrdenPorDni(trabajo[posTrabajo].listaEmpleados,*empleadoBuscado);
                trabajo[i2].listaEmpleados=borrarNodoEmpleado(trabajo[i2].listaEmpleados,*empleadoBuscado);
            }
            else
            {
                char control='s';
                char nuevoTrabajo[30];
                printf("El trabajo elegido no existe. Desea crear uno nuevo y cargar a este empleado?s/n\n");
                fflush(stdin);
                scanf("%c",&control);
                if(control=='s')
                {
                    system("cls");
                    dibujoBancoCentral();
                    i2=posTrabajo;
                    printf("Ingrese nombre del trabajo nuevo:\n");
                    fflush(stdin);
                    scanf("%s",nuevoTrabajo);
                    alta2(trabajo,*validos,(*empleadoBuscado),nuevoTrabajo);
                    trabajo[i2].listaEmpleados=borrarNodoEmpleado(trabajo[i2].listaEmpleados,*empleadoBuscado);
                    posTrabajo=*validos;
                }
                else
                {
                    system("pause");
                }
            }
            break;
        case 4:
            printf("Nuevo numero de telefono:\n");
            fflush(stdin);
            scanf("%s",(*empleadoBuscado)->dato.NumeroTelefono);
            break;
        case 0:

            break;
        default:
            printf("opcion no valida\n");
            break;
          }
    }
    return posTrabajo;
}

void guiaDeUsuario()
{
    printf("                             Bienvenido al Sistema de Cuentas Bancarias. A continuacion  dispondra\n");
    printf("                              de una breve sintaxis de todo lo que este sistema es capaz de hacer.\n\n\n");
    printf("[USUARIOS]\n");
    printf("- Crear una Cuenta\n");
    printf("- Iniciar Sesion\n");
    printf("- Ver Tus Movimientos\n");
    printf("- Depositar y Extraer Dinero\n");
    printf("- Hacer Transferencia a Otro Usuario\n");
    printf("- Ver Todos los Datos de Tu Cuenta\n");
    printf("- Cambiar Contrasenia\n");
    printf("- Desactivar Cuenta (puedes reactivarla contactando con soporte)\n\n\n");

    printf("[ADMINISTRADOR]\n");
    printf(" Gestion de Usuarios y Empleados:\n");
    printf("- Ver Usuarios Ordenados por DNI\n");
    printf("- Mostrar Usuarios Dados de Baja\n");
    printf("- Buscar Usuario por DNI\n");
    printf("- Modificar Usuario\n");
    printf("- Dar de Alta o Dar de Baja Usuario\n");
    printf("- Ver Historial de Transacciones de Usuario\n");
    printf("- Ver Empleados Ordenados por Trabajo y DNI\n");
    printf("- Agregar Nuevo Empleado\n");
    printf("- Buscar Empleado por DNI\n");
    printf("- Modificar Empleado\n");
    printf("- Dar de Alta o Dar de Baja Empleado\n");

    printf("\nDisfruta utilizando el Sistema de Cuentas Bancarias! Si necesitas asistencia, contacta al soporte;\n\n\n");
}



