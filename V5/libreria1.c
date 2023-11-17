#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

//funciones de sistema
///RETORNA S-N
char deseaSalir(){
    char confirmacion;

    printf("Seguro/a que desea salir? s/n\n");
    fflush(stdin);
    scanf("%c", &confirmacion);

    return confirmacion;
}

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
                fseek(archi, -sizeof(usuario), SEEK_CUR);  // Retrocede el cursor y vuelve un paso para atras para que quede em eñ mismo lugar
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

    if(buffer!=NULL){
        while(flag==0 && fread(&usu, sizeof(usuario), 1, buffer)>0){
            if(strcmpi(usu.mail,mail)==0){
                flag=1;
            }
            else{
                flag=0;
            }
        }
        fclose(buffer);
    }
    else{
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
    else{
        printf("ERROR AL ABRIR EL ARCHIVO DE USUARIOS");
    }

}

///RETORNA UNA ESTRUCTURA USUARIO CARGADA POR EL USUARIO
usuario crea1Usuario (usuario nuevoUsuario)
{
    int flag=0;
    int flag1=0;

    printf("Ingrese su nombre y apellido:\n");
    fflush(stdin);
    gets(nuevoUsuario.nombreApellido);

    do
    {
        printf("Ingrese su Genero: (m o f)\n");
        fflush(stdin);
        scanf("%c", &nuevoUsuario.genero);
        if(nuevoUsuario.genero !='m'&& nuevoUsuario.genero!='f')
        {
            printf("\nLetra incorrecta, vuelva a ingresar..");
        }
    }
    while(nuevoUsuario.genero !='m'&& nuevoUsuario.genero!='f');

    printf("Ingrese su DNI:\n");
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


    printf("Ingrese su mail:\n");
    fflush(stdin);
    gets(nuevoUsuario.mail);
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

    printf("Ingrese su contrasenia:\n");
    fflush(stdin);
    gets(nuevoUsuario.contrasenia);

    nuevoUsuario.cbu = generarCBU(8);

    nuevoUsuario.estado=1;

    nuevoUsuario.saldo = 0;

    return nuevoUsuario;
}

///RETORNA 1 SI EL MAIL Y LA CONTRASEÑA PERTENECENEN A UNA CUENTA Y 0 SI NO
int detectaUsuario(usuario usuBuscado, usuario ingreso) //se deberia hacer por arbol
{
    int flag=0;
    if(strcmp(usuBuscado.mail, ingreso.mail)== 0 && strcmp(usuBuscado.contrasenia,ingreso.contrasenia)== 0){

        flag = 1;

    }

    return flag;
}

///CARGA EL MAIL Y LA CONTRASEÑA Y LOS RETORNA EN UNA STRUCT
usuario inicioSesion()
{
    usuario usuInicioSesion;
//
//    usuInicioSesion.cbu = 0;
//    usuInicioSesion.estado = 0;
//    usuInicioSesion.genero = 'a';
//    usuInicioSesion.saldo = 0;
//    strcpy(usuInicioSesion.nombreApellido,"a");

    printf("DNI:\n");
    fflush(stdin);
    scanf("%i",&usuInicioSesion.dni);

    printf("Ingrese su mail:\n");
    fflush(stdin);
    gets(usuInicioSesion.mail);

    printf("Ingrese su contrasenia:\n");
    fflush(stdin);
    scanf("%s", usuInicioSesion.contrasenia);

return usuInicioSesion;
}

///FUNCIONES LUEGO DE INICIAR SESION:
//nos quedamos con los prestamos?
/////SE INICIALIZA LA CAJA EN 0
//usuario cajaEnCero(usuario usu, int cbu){
//
//    usu.saldo.caja=0;
//    usu.saldo.prestamo=0;
//    usu.saldo.cbu = cbu;
//
//    return usu;
//}
//
/////SE ESTABLECE EL SALDO EN 0 CUANDO SE CREA UNA CUENTA NUEVA
//void crearSaldo(int cbu){
//    usuario caja;
//
//    FILE* buffer=fopen(archivo2, "ab");
//
//
//    if(buffer!=NULL){
//        caja=cajaEnCero(caja, cbu);
//        fwrite(&caja, sizeof(usuario), 1, buffer);
//
//        fclose(buffer);
//    }
//    else{
//        printf("ERROR AL ABRIR EL ARCHIVO");
//    }
//}
//
/////MUESTRA SALDO DE LA CUENTA Y SALDO A PAGAR POR PRESTAMOS
//void muestraSaldo(usuario usu)
//{
//   printf("CAJA:%ld\n", usu.saldo.caja);
//   printf("PRESTAMO A PAGAR:%ld\n", usu.saldo.prestamo);
//}
//
/////BUSCA EL CBU DE LA SESION INICIADA Y LLAMA A LA FUNCION ANTERIOR
//void corroborarSaldo(int pcbu)
//{
//    usuario usu;
//    FILE* buffer=fopen(archivo2, "rb");
//
//    if(buffer!=NULL)
//    {
//        while(fread(&usu, sizeof(usuario), 1, buffer)>0)
//        {
//            if(usu.saldo.cbu == pcbu) //encuentra el saldo del usuario a través del cbu, logrando asi mostrar el saldo del usuario correspondiente
//            {
//                muestraSaldo(usu);
//            }
//        }
//        fclose(buffer);
//    }
//    else{
//        printf("ERROR AL ENTRAR AL ARCHIVO, NO HAY SALDOS CARGADOS");
//    }
//}
//
/////SE GUARDA EN EL ARCHIVO EL NUEVO PRESTAMO
//void prestamo(int cbu){
//    usuario usu;
//    int posicion;
//    FILE*buffer=fopen(archivo2,"r+b");
//    if(buffer!=NULL)
//    {
//        fread(&usu,sizeof(usuario),1,buffer);
//
//            while(!feof(buffer)){
//                if(cbu==usu.saldo.cbu)
//                {
//                    printf("Este es su saldo actual %ld\n", usu.saldo.caja);
//                    posicion=ftell(buffer)-sizeof(usuario);
//                    usu=prestamoSaldo(cbu,usu);
//                    fseek(buffer, posicion, SEEK_SET);
//                    fwrite(&usu,sizeof(usuario),1,buffer);
//                    break;
//                }
//                fread(&usu, sizeof(usuario), 1, buffer);
//            }
//        fclose(buffer);
//    }
//    else{
//        printf("ERROR AL INGRESAR AL ARCHIVO");
//    }
//}
//
/////SE PREGUNTA CUANTO QUIERE DE PRESTAMO EL USUARIO
//usuario prestamoSaldo(int cbu,usuario usu)
//{
//    long int deuda=0;
//    do{
//    printf("Que cantidad desea pedir prestada..(minimo 50000)\n");
//    fflush(stdin);
//    scanf("%ld",&deuda);
//    if(deuda<50000){
//        printf("Ha ingresado una cifra menor a 50000... o un digito incorrecto");
//    }
//    }while(deuda<50000);
//
//    usu.saldo.caja=usu.saldo.caja+deuda;
//    deuda=deuda+((deuda*15)/100);
//
//    usu.saldo.prestamo=(usu.saldo.prestamo-deuda);
//    return usu;
//}
//
/////RETORNA UN USUARIO RESTANDO LA CANTIDAD DE DINERO QUE SE ELIGA, SI NO SE TIENE SUFICIENTE NO TE DEJA
//usuario deudaApagar(usuario deuda){
//    long int pago;
//    do{
//    printf("Que cantidad desea pedir pagar del prestamo?\n");
//    fflush(stdin);
//    scanf("%ld", &pago);
//    if(pago>deuda.saldo.caja){
//        printf("El pago es mayor a lo que tiene en caja\n");
//    }
//    }while(pago>deuda.saldo.caja);
//
//    deuda.saldo.caja=(deuda.saldo.caja)-pago;
//
//    deuda.saldo.prestamo=(deuda.saldo.prestamo)+pago;
//    printf("La deuda ha sido pagada con exito\n");
//
//    return deuda;
//}
//
/////SE SOBREESCRIBE EL ARCHIVO Y ACTUALIZA LA CANTIDAD DE DEUDA QUE SE TIENE
//void pagarPrestamo(int cbu){
//    usuario usu;
//    int posicion;
//    int flag=0;
//    FILE*buffer=fopen(archivo2,"r+b");
//    if(buffer!=NULL)
//    {
//
//            while(flag==0 && (fread(&usu,sizeof(usuario),1,buffer)>0)){
//            if(cbu ==usu.saldo.cbu)
//            {
//                printf("Esta es tu deuda actual %ld\n", usu.saldo.prestamo);
//                printf("Este es tu saldo disponible en cuenta:%ld\n", usu.saldo.caja);
//                posicion=ftell(buffer)-sizeof(usuario);
//                usu=deudaApagar(usu);
//                fseek(buffer, posicion, SEEK_SET);
//                fwrite(&usu,sizeof(usuario),1,buffer);
//                flag=1;
//            }
//        }
//        fclose(buffer);
//    }
//}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

///SE PIDE QUE INGRESE EL CBU DE LA PERSONA A LA QUE SE QUIERE TRANSFERIR Y CUANTO SE LE QUIERE TRANSFERIR
movimiento carga1Transfer (nodoArbol * raiz,int cbuPaga)
{
    movimiento transfer;
    transfer.cbuEmisor = cbuPaga;
    transfer.tipoDeOperacion = 0;

    printf("Ingrese el monto:\n ");
    fflush(stdin);
    scanf("%i", &transfer.monto);

    printf("Ingrese el cbu del destinatario:\n");
    fflush(stdin);
    scanf("%i", &transfer.cbuReceptor);

    if (cbuPaga == transfer.cbuReceptor)
    {
        printf("No se puede transferir a usted mismo, porfavor intente denuevo.\n");
    }
    else
    {
//      nodoArbol * receptor = buscarCBUenArbol(transfer.cbuReceptor);

        if (NULL)
        {
            printf("Usuario encontrado correctamente, transferencia exitosa.\n");
        }
        else
        {
            printf("Usuario no encontrado, porfavor intente con otro CBU.\n");
        }
     }
    return transfer;
}

///SOBREESCRIBIMOS EL ARCHIVO Y MODIFICAMOS EL SALDO DE AMBOS PARTICIPANTES DE LA TRANSFERENCIA
void tranferencia(nodoArbol * arbol)
{

//    movimiento transf = carga1Transfer(,arbol->dato.cbu);
//    arbol->dato.saldo = arbol->dato.saldo - transf.monto;
//    reemplazarDato(arbol->dato);

}



///RETORNA UN USUARIO CON LA NUEVA CONTRASEÑA
usuario newPass(usuario usu, char contrasenia[20]){

    strcpy(usu.contrasenia, contrasenia);

    return usu;
}

///SOBREESCRIBIMOS EL ARCHIVO CON LA NUEVA CONTRASEÑA
void modPass(char contrasenia[20], int cbu){

    usuario usu;
    FILE*buffer=fopen(archivo, "r+b");
    int posicion;

    if(buffer!=NULL){
        fread(&usu,sizeof(usuario),1,buffer);
        while(!feof(buffer)){
            if(cbu == usu.cbu){
                posicion=ftell(buffer)-sizeof(usuario);
                usu=newPass(usu, contrasenia);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                break;
            }
        fread(&usu,sizeof(usuario),1,buffer);
        }
        fclose(buffer);
    }
    else{
        printf("ERROR AL INGRESAR AL ARCHIVO");
    }
}

///BUSCA UN USUARIO EN EL ARCHIVO POR SU CBU
usuario busquedaUsuXCBU(int cbu,int *flag)
{
    *flag=0;
    usuario usu;
    FILE*buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(*flag==0 &&  (fread(&usu, sizeof(usuario), 1, buffer)>0))
        {
            if(cbu == usu.cbu)
            {
                *flag=1;
            }
        }
        fclose(buffer);
    }
    return usu;
}

///MUESTRA DATOS DE UN USUARIO
void muestraUsuarioAdmin(usuario usu)
{
   puts("---------------------------------------------");
    printf("Nombre y apellido:");
    puts(usu.nombreApellido);
    printf("Genero:%c\n", usu.genero);
    printf("DNI:%i\n", usu.dni);
    printf("Mail:%s\n", usu.mail);
    printf("CBU:%i\n", usu.cbu);
    puts("---------------------------------------------");
}

///PREGUNTA SI ESTAS SEGURO DE ELIMINAR LA CUENTA RETORNA 1-0
int seguroDeseaEliminar(){
    int desicion=0;
    char seguro;
    printf("Seguro que usted desea desactivar su cuenta? \n(No la podra volver a activar por este campo, debera ir personalmente)\ns o n:    ");
    fflush(stdin);
    scanf("%c", &seguro);
    if(seguro=='s'){
        desicion=1;
    }
    return desicion;
}

///RETORNO 0 PARA DESCATIVAR LA CUENTA
usuario desactivar(usuario usu){

    usu.estado=0;

    return usu;
}

///REESCRIBE EN EL ARCHIVO Y DESACTIVA LA CUENTA
void desactivarCuenta(int cbu){
    usuario usu;
    FILE*buffer=fopen(archivo, "r+b");
    int posicion;

    if(buffer!=NULL){
     fread(&usu,sizeof(usuario),1,buffer);
        while(!feof(buffer)){
            if(cbu == usu.cbu){
                posicion=ftell(buffer)-sizeof(usuario);
                usu=desactivar(usu);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                break;
            }
        fread(&usu,sizeof(usuario),1,buffer);
        }
        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
}

///SI ENCUENTRA EL CBU RETORNA 1 SINO 0
int chequeoCBU(int cbu)
{
    usuario usu;
    int flag=0;
    FILE* buffer;
    buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(flag==0 && fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(usu.cbu == cbu)
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

///BUSCA UN USUARIO POR SU DNI
usuario busquedaUsuXDNI(int dni, int *flag)
{
    *flag=0;
    usuario usu;
    FILE*buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(*flag==0 && (fread(&usu, sizeof(usuario), 1, buffer)>0))
        {
            if(dni==usu.dni)
            {
                *flag=1;
            }
        }
        fclose(buffer);
    }
    return usu;
}

///FUNCION EN LA QUE EL ADMIN DA DE BAJA A UN USUARIO
void darDeBajaOAltaAdmin(){
    usuario usu;
    int cbu;
    int validar;

    do{
    printf("Que usuario desea dar de baja?(ingrese el cbu del mismo)\n");
    fflush(stdin);
    scanf("%i", &cbu);
    validar=chequeoCBU(cbu);
    if(validar!=1){
        printf("CBU No fue encontrado, ingrese otro\n");
    }
    }while(validar!=1);

    int posicion;
    FILE*buffer=fopen(archivo, "r+b");
    if(buffer!=NULL)
    {
        while((fread(&usu, sizeof(usuario), 1, buffer)>0))
        {
            if(cbu == usu.cbu)
            {
                posicion=ftell(buffer)-sizeof(usuario);
                usu=desactivar(usu);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                printf("ELIMINADO CORRECTAMENTE\n");
                break;
            }
        }
        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
        system("pause");
    }

}

///SIRVE PARA INICIAR SESION COMO ADMIN
int chequeoAdmin(int flag, usuario admin)
{
    char usu[10]="admin";
    usuario usua;
    char contrasenia[10]="123";
    int x=flag;
    FILE*buffer=fopen(archivo, "rb");

    if(buffer!=NULL)
    {
        while(fread(&usua, sizeof(usuario), 1, buffer)>0)
        {
            if(strcmp(admin.mail, usua.mail)==0 && strcmp(admin.contrasenia, usua.contrasenia)==0)
            {
                if(strcmp(admin.mail, usu)==0&&strcmp(admin.contrasenia, contrasenia)==0)
                {
                    x=2;//devuelve 2 para diferenciarse de la funcion "detectaUsuario"
                    break;//agrego break para que corte el ciclo una vez encontrado el usuario y contraseña correctos.
                }
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
    return x;
}

///ORDENA UN ARREGLO DE ESTRUCTURAS POR DNI
void ordenaxDNI(usuario arrayUsu[], int validos)
{
    usuario usuAux;
    int i, j;

    for (i=1; i<validos; i++)
    {
        usuAux=arrayUsu[i];
        j=i-1;

        while (j >= 0 && arrayUsu[j].dni> usuAux.dni)
        {
            arrayUsu[j + 1]=arrayUsu[j];
            j--;
        }

        arrayUsu[j + 1]=usuAux;
    }
}

///PASA LOS REGISTROS DEL ARCHIVO A UN ARREGLO DE ESTRUCTURAS
int ArchiToArray(usuario arrayUsu[], int dimension)
{
    int i=0;
    usuario usu;
    FILE* buffer=fopen(archivo, "rb");
    if(buffer)
    {
        fread(&usu, sizeof(usuario), 1, buffer);
        while(!feof(buffer) && i<dimension)
        {
            arrayUsu[i]=usu;
            i++;
            fread(&usu, sizeof(usuario), 1, buffer);
        }
        fclose(buffer);
    }
    return i;
}

///IMPRIME UN USUARIO POR PANTALLA
void muestra1Usuario(usuario usu)
{
    puts("---------------------------------------------");
    if(usu.estado==1){
        printf("Estado: ACTIVO\n");
    }
    else{
        printf("Estado: INACTIVO\n");
    }
    printf("Nombre y apellido:");
    printf("%s\n", usu.nombreApellido);
    printf("Genero:");
    printf("%c\n", usu.genero);
    printf("DNI:%i\n", usu.dni);
    printf("Mail:%s\n", usu.mail);
    printf("CBU:%i\n", usu.cbu);
    puts("---------------------------------------------");
}

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
    printf("2- Genero\n");
    printf("3- Mail\n");
    printf("4- contraseña\n");
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
        printf("Nuevo genero:\n");
        fflush(stdin);
        scanf("%c",&arbol->dato.genero);
        break;
    case 3:
        printf("Nuevo mail:\n");
        fflush(stdin);
        gets(arbol->dato.mail);
        break;
    case 4:
        printf("Nueva contrasenia:\n");
        fflush(stdin);
        gets(arbol->dato.contrasenia);
        break;
    default:

        printf("opcion no valida\n");

        break;

    }
    //llamada a funcion de modificar dato

return arbol;
}

