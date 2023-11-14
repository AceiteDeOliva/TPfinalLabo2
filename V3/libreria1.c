#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "librerias1.h"

///RETORNA S-N
char deseaSalir(){
    char confirmacion;

    printf("Seguro/a que desea salir? s/n\n");
    fflush(stdin);
    scanf("%c", &confirmacion);

    return confirmacion;
}

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
void CrearUsuario(char cbu[10])
{
    usuario nuevoUsuario;

    FILE* buffer;
    buffer=fopen(archivo, "ab");
    if(buffer!=NULL)
    {
        nuevoUsuario=crea1Usuario(nuevoUsuario, cbu);
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
usuario crea1Usuario (usuario nuevoUsuario, char pcbu[10])
{
    int cbu;
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
    scanf("%ld", &nuevoUsuario.dni);
    flag1=chequeoDNI(nuevoUsuario.dni);
    do
    {
        if (flag1==1)
        {
            printf("Este DNI ya existe, ingrese otro por favor: ");
            fflush(stdin);
            scanf("%ld", &nuevoUsuario.dni);
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

    srand(time(NULL));
    cbu= rand()%99+99;
    sprintf(nuevoUsuario.cbu, "%d", cbu);///lo cambie a 3 digitos, pueden ser reducidos para menor complejidad

    strcpy(pcbu, nuevoUsuario.cbu);//pasamos el cbu creado a la cuenta del usuario

    nuevoUsuario.estado=1;

    return nuevoUsuario;
}

///RETORNA 1 SI EL MAIL Y LA CONTRASEÑA PERTENECENEN A UNA CUENTA Y 0 SI NO
int detectaUsuario(usuario usuBuscado, char cbu[10])
{
    usuario usu;
    int flag=0;

    FILE* buffer=fopen(archivo, "rb");

    if(buffer)
    {
        while(fread(&usu, sizeof(usuario), 1, buffer)>0 && flag==0)
        {
            if(strcmp(usu.contrasenia, usuBuscado.contrasenia)==0 && strcmp(usu.mail, usuBuscado.mail)==0 && usu.estado==1)
            {
                flag=1;
                strcpy(cbu, usu.cbu);
                break;//agrego break para que corte el ciclo una vez encontrado el usuario y contraseña correctos.
            }
        }
        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
    return flag;
}

///CARGA EL MAIL Y LA CONTRASEÑA Y LOS RETORNA EN UNA STRUCT
usuario inicioSesion()
{
    usuario usuInicioSesion;

    printf("Ingrese su mail:\n");
    fflush(stdin);
    gets(usuInicioSesion.mail);

    printf("Ingrese su contrasenia:\n");
    fflush(stdin);
    scanf("%s", usuInicioSesion.contrasenia);

return usuInicioSesion;
}

///FUNCIONES LUEGO DE INICIAR SESION:

///SE INICIALIZA LA CAJA EN 0
usuario cajaEnCero(usuario usu, char cbu[10]){

    usu.saldo.caja=0;
    usu.saldo.prestamo=0;
    strcpy(usu.saldo.cbu, cbu);

    return usu;
}

///SE ESTABLECE EL SALDO EN 0 CUANDO SE CREA UNA CUENTA NUEVA
void crearSaldo(char cbu[10]){
    usuario caja;

    FILE* buffer=fopen(archivo2, "ab");


    if(buffer!=NULL){
        caja=cajaEnCero(caja, cbu);
        fwrite(&caja, sizeof(usuario), 1, buffer);

        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
}

///MUESTRA SALDO DE LA CUENTA Y SALDO A PAGAR POR PRESTAMOS
void muestraSaldo(usuario usu)
{
   printf("CAJA:%ld\n", usu.saldo.caja);
   printf("PRESTAMO A PAGAR:%ld\n", usu.saldo.prestamo);
}

///BUSCA EL CBU DE LA SESION INICIADA Y LLAMA A LA FUNCION ANTERIOR
void corroborarSaldo(char pcbu[])
{
    usuario usu;
    FILE* buffer=fopen(archivo2, "rb");

    if(buffer!=NULL)
    {
        while(fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(strcmp(usu.saldo.cbu, pcbu)==0) //encuentra el saldo del usuario a través del cbu, logrando asi mostrar el saldo del usuario correspondiente
            {
                muestraSaldo(usu);
            }
        }
        fclose(buffer);
    }
    else{
        printf("ERROR AL ENTRAR AL ARCHIVO, NO HAY SALDOS CARGADOS");
    }
}

///SE GUARDA EN EL ARCHIVO EL NUEVO PRESTAMO
void prestamo(char cbu[10]){
    usuario usu;
    int posicion;
    FILE*buffer=fopen(archivo2,"r+b");
    if(buffer!=NULL)
    {
        fread(&usu,sizeof(usuario),1,buffer);

            while(!feof(buffer)){
                if(strcmp(cbu,usu.saldo.cbu)==0)
                {
                    printf("Este es su saldo actual %ld\n", usu.saldo.caja);
                    posicion=ftell(buffer)-sizeof(usuario);
                    usu=prestamoSaldo(cbu,usu);
                    fseek(buffer, posicion, SEEK_SET);
                    fwrite(&usu,sizeof(usuario),1,buffer);
                    break;
                }
                fread(&usu, sizeof(usuario), 1, buffer);
            }
        fclose(buffer);
    }
    else{
        printf("ERROR AL INGRESAR AL ARCHIVO");
    }
}

///SE PREGUNTA CUANTO QUIERE DE PRESTAMO EL USUARIO
usuario prestamoSaldo(char cbu[10],usuario usu)
{
    long int deuda=0;
    do{
    printf("Que cantidad desea pedir prestada..(minimo 50000)\n");
    fflush(stdin);
    scanf("%ld",&deuda);
    if(deuda<50000){
        printf("Ha ingresado una cifra menor a 50000... o un digito incorrecto");
    }
    }while(deuda<50000);

    usu.saldo.caja=usu.saldo.caja+deuda;
    deuda=deuda+((deuda*15)/100);

    usu.saldo.prestamo=(usu.saldo.prestamo-deuda);
    return usu;
}

///RETORNA UN USUARIO RESTANDO LA CANTIDAD DE DINERO QUE SE ELIGA, SI NO SE TIENE SUFICIENTE NO TE DEJA
usuario deudaApagar(usuario deuda){
    long int pago;
    do{
    printf("Que cantidad desea pedir pagar del prestamo?\n");
    fflush(stdin);
    scanf("%ld", &pago);
    if(pago>deuda.saldo.caja){
        printf("El pago es mayor a lo que tiene en caja\n");
    }
    }while(pago>deuda.saldo.caja);

    deuda.saldo.caja=(deuda.saldo.caja)-pago;

    deuda.saldo.prestamo=(deuda.saldo.prestamo)+pago;
    printf("La deuda ha sido pagada con exito\n");

    return deuda;
}

///SE SOBREESCRIBE EL ARCHIVO Y ACTUALIZA LA CANTIDAD DE DEUDA QUE SE TIENE
void pagarPrestamo(char cbu[10]){
    usuario usu;
    int posicion;
    int flag=0;
    FILE*buffer=fopen(archivo2,"r+b");
    if(buffer!=NULL)
    {

            while(flag==0 && (fread(&usu,sizeof(usuario),1,buffer)>0)){
            if(strcmp(cbu,usu.saldo.cbu)==0)
            {
                printf("Esta es tu deuda actual %ld\n", usu.saldo.prestamo);
                printf("Este es tu saldo disponible en cuenta:%ld\n", usu.saldo.caja);
                posicion=ftell(buffer)-sizeof(usuario);
                usu=deudaApagar(usu);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                flag=1;
            }
        }
        fclose(buffer);
    }
}

///SE PIDE QUE INGRESE EL CBU DE LA PERSONA A LA QUE SE QUIERE TRANSFERIR Y CUANDO SE LE QUIERE TRANSFERIR
sTtransfer carga1Transfer (sTtransfer transfer, char cbuPaga[10])
{
    int flag=0;
    printf("Ingrese el importe:\n ");
    scanf("%ld", &transfer.importe);

    printf("Ingrese el cbu del destinatario:\n");
    fflush(stdin);
    gets(transfer.cbuReceptor);
    if (strcasecmp(cbuPaga, transfer.cbuReceptor)==0)
    {
        printf("No se puede transferir a usted mismo, porfavor intente denuevo.\n");
    }
    else
    {
      flag=chequeoCBU(transfer.cbuReceptor);

        if (flag==1)
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

///SE LE ACERDITA EL DINERO DE LA TRANSFERENCIA A LA CUENTA ELEGIDA
usuario cambio1(usuario usu, sTtransfer tran){

    usu.saldo.caja=usu.saldo.caja+tran.importe;

    return usu;
}

///SE LE DEBITA EL DINERO DE LA TRANSFERENCIA A LA CUENTRA EMITENTE
usuario cambio2(usuario usu, sTtransfer tran){

    usu.saldo.caja=usu.saldo.caja-tran.importe;

    return usu;
}

///SOBREESCRIBIMOS EL ARCHIVO Y MODIFICAMOS EL SALDO DE AMBOS PARTICIPANTES DE LA TRANSFERENCIA
void tranferencia(char cbuPaga[10])
{
    usuario usu;
    sTtransfer tran;
    FILE*buffer=fopen(archivo2,"r+b");
    int posicion;

    if(buffer!=NULL)
    {
            do{
            tran=carga1Transfer(tran, cbuPaga);
            if(tran.importe > usu.saldo.caja){
                printf("El importe ingresado es menor al que tiene usted en caja...\n Ingrese otro monto\n");
            }
            }while(tran.importe > usu.saldo.caja);
            fread(&usu, sizeof(usuario),1,buffer);
        while(!feof(buffer))
        {
            if(strcmp(tran.cbuReceptor,usu.saldo.cbu)==0){
                posicion=ftell(buffer)-sizeof(usuario);
                usu=cambio1(usu, tran);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                break;
            }
            fread(&usu, sizeof(usuario),1,buffer);
        }
        fseek(buffer, 0, SEEK_SET);
        fread(&usu, sizeof(usuario),1,buffer);
        while(!feof(buffer)){
            if(strcmp(tran.referencia,usu.saldo.cbu)==0){
                posicion=ftell(buffer)-sizeof(usuario);
                usu=cambio2(usu, tran);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usu,sizeof(usuario),1,buffer);
                break;
            }
            fread(&usu, sizeof(usuario),1,buffer);
        }

        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
}

///RETORNA UN USUARIO CON LA NUEVA CONTRASEÑA
usuario newPass(usuario usu, char contrasenia[20]){

    strcpy(usu.contrasenia, contrasenia);

    return usu;
}

///SOBREESCRIBIMOS EL ARCHIVO CON LA NUEVA CONTRASEÑA
void modPass(char contrasenia[20], char cbu[10]){

    usuario usu;
    FILE*buffer=fopen(archivo, "r+b");
    int posicion;

    if(buffer!=NULL){
        fread(&usu,sizeof(usuario),1,buffer);
        while(!feof(buffer)){
            if(strcmp(cbu,usu.cbu)==0){
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


///GENERA UNA MATRIZ CON LOS DIAS Y HORARIOS DE ATENCION
void generaMatrizHorarios(int matriz[][7])
{
    int i, j;
    int numero = 1;

    for (i = 0; i < 4; i++)
        {
        for (j = 0; j < 7; j++)
           {
            matriz[i][j] = numero;
            numero = numero + 1;
           }
        }
    matriz[0][0] = 0;
    matriz[1][0] = 0;
    matriz[2][0] = 0;
    matriz[3][0] = 0;
}

///MUESTRA MATRIZ CON LOS DIAS Y HORARIOS DE ATENCION
void muestraMatrizHorarios(int matriz[][7])
{
    int i, j;
    printf("-------------------------------------------\n");

    printf("  Dom   Lun   Mar   Mie  Jue   Vie   Sab\n");
    printf("-------------------------------------------\n");

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            printf("  %2d  ", matriz[i][j]);
        }
        printf("\n");
    }
}

///BUSCA UN USUARIO EN EL ARCHIVO POR SU CBU
usuario busquedaUsuXCBU(char cbu[],int *flag)
{
    *flag=0;
    usuario usu;
    FILE*buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(*flag==0 &&  (fread(&usu, sizeof(usuario), 1, buffer)>0))
        {
            if(strcmp(cbu,usu.cbu)==0)
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
    printf("DNI:%ld\n", usu.dni);
    printf("Mail:%s\n", usu.mail);
    printf("CBU:%s\n", usu.cbu);
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
void desactivarCuenta(char cbu[20]){
    usuario usu;
    FILE*buffer=fopen(archivo, "r+b");
    int posicion;

    if(buffer!=NULL){
     fread(&usu,sizeof(usuario),1,buffer);
        while(!feof(buffer)){
            if(strcmp(cbu,usu.cbu)==0){
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
int chequeoCBU(char cbu[])
{
    usuario usu;
    int flag=0;
    FILE* buffer;
    buffer=fopen(archivo,"rb");

    if(buffer!=NULL)
    {
        while(flag==0 && fread(&usu, sizeof(usuario), 1, buffer)>0)
        {
            if(strcmp(usu.cbu,cbu)==0)
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
int chequeoDNI(long int dni)
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
usuario busquedaUsuXDNI(long int dni, int *flag)
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
    char cbu[10];
    int validar;

    do{
    printf("Que usuario desea dar de baja?(ingrese el cbu del mismo)\n");
    fflush(stdin);
    scanf("%s", cbu);
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
            if(strcmp(cbu,usu.cbu)==0)
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
    printf("DNI:%ld\n", usu.dni);
    printf("Mail:%s\n", usu.mail);
    printf("CBU:%s\n", usu.cbu);
    puts("---------------------------------------------");
}


