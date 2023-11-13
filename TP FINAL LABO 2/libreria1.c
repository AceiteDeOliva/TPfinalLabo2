#include "librerias1.h"
#include <unistd.h>


///retorna s o n, sirve para salir de los menues
char deseaSalir(){
    char confirmacion;

    printf("Seguro/a que desea salir? s/n\n");
    fflush(stdin);
    scanf("%c", &confirmacion);

    return confirmacion;
}
///retorna 1 si existe el mail o 0 si ya hay un mail creado con el mismo nombre que el pasado por parametro
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
///carga en un archivo el/los usuario/s cargado/s por teclado anteriormente
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
/// retorna un dato struct tipo "usuario"| cargamos por teclado los datos del usuario, algunos datos se generan sin intervencion del cliente
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

///retorna 1 si el usuario y contraseña son iguales al escrito anteriormente o 0 si no existen coincidencias
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
///retorna un tipo de dato struct|le pasamos por teclado el usuario y contraseña de la cuenta a querer ingresar
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

///Funciones del menu luego de iniciar sesion:
///retorna un tipo de dato struct|inicializamos la caja en 0
usuario cajaEnCero(usuario usu, char cbu[10]){

    usu.saldo.caja=0;
    usu.saldo.prestamo=0;
    strcpy(usu.saldo.cbu, cbu);

    return usu;
}
///creamos un saldo al usuario| este se ejecuta al usuario crearse una cuenta, inicializando la cuenta en 0 por defecto
void crearSaldo(char cbu[10]){//con esta funcion creamos saldo del usuario, se establece en 0
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
///muestra por pantalla el saldo en caja y el saldo a pagar en prestamos
void muestraSaldo(usuario usu) //mostramos saldo del usuario, mostrara en momento real lo que suceda con su cuenta.
{
   printf("CAJA:%ld\n", usu.saldo.caja);
   printf("PRESTAMO A PAGAR:%ld\n", usu.saldo.prestamo);
}
///entra al archivo, busca el cbu del usuario que este con la cuenta iniciada, y llama a la funcion anterior
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
///retorna un tipo de dato struct usuario| se le pedira al cliente que inserte por teclado el monto que desee agregar a su cuenta
///haciendo una "simulacion" de ingrgeso de saldo en caja.
usuario agregarsaldo(usuario usuiniciado)
{
    long int saldoAgregado;
    printf("Que saldo desea agregar a su cuenta? Solo tiene un intento...\n");///cambie la funcion para que intente agregar en vez de solo establecerlo en un numero
    fflush(stdin);
    scanf("%ld",&saldoAgregado);
    usuiniciado.saldo.caja= usuiniciado.saldo.caja+saldoAgregado;
    return usuiniciado;
}
///agrega saldo a un archivo "saldo" con su respectivo usuario, pasandole por parametro el cbu, para luego poder identificar ese saldo
///al cbu del usuario que tenga la sesion ya iniciada
void AgregarSaldoCuenta(char cbu[10])
{
    usuario usuiniciado;
    FILE*buffer=fopen(archivo2,"r+b");
    int posicion;

    if(buffer!=NULL)
    {
        fread(&usuiniciado,sizeof(usuario),1,buffer);
        while(!feof(buffer))
        {
            if(strcmp(cbu,usuiniciado.saldo.cbu)==0)
            {
                printf("Este es su saldo actual: %ld\n", usuiniciado.saldo.caja);
                posicion=ftell(buffer)-sizeof(usuario);
                usuiniciado=agregarsaldo(usuiniciado);
                fseek(buffer, posicion, SEEK_SET);
                fwrite(&usuiniciado,sizeof(usuario),1,buffer);
                break;
            }
            fread(&usuiniciado,sizeof(usuario),1,buffer);
        }

        fclose(buffer);
    }
    else{
        printf("ERROR AL ABRIR EL ARCHIVO");
    }
}
///usando la funcion posterior y el cbu pasado por parametro(asi usando la cuenta ya iniciada), sobreescribimos el el arhivo "saldo
///el prestamo que haya pedido el usuario
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
///retorna un tipo de dato struct usuario| pedimos al usuario que ingrese por teclado el monto del prestamo a pedir con un minimo de 50000
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
///retorna un struct usuario|pedimos por teclado, cuanto desea pagar el usuario del prestamo, se le debitara de la caja
///si supera el saldo en caja, no se le permitira pagar mas de lo que contiene en caja
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
///con el usuario con sesion iniciada a traves del cbu pasado por parametro, sobreescribrimos en el archivo "saldo" y modificamos
///el saldo en caja
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
///retorna un struct sTtransfer| le pedimos por teclado al usuario, que ingrese cuanto quiere transferir al usuario y
/// que ingrese el cbu del destino.
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
///retorna el cambio al receptor de la transferencia
usuario cambio1(usuario usu, sTtransfer tran){

    usu.saldo.caja=usu.saldo.caja+tran.importe;

    return usu;
}
///retorna el cambio al emisor de la transferencia
usuario cambio2(usuario usu, sTtransfer tran){

    usu.saldo.caja=usu.saldo.caja-tran.importe;

    return usu;
}
///Generamos la transferencia, sobreescribrimos los datos del emisor y receptor, en el archivo "saldo"
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
///retorna una struct con un dato modificado, en este caso la contraseña
usuario newPass(usuario usu, char contrasenia[20]){

    strcpy(usu.contrasenia, contrasenia);

    return usu;
}
///se modifica la contraseña sobreescribiendo el archivo "usuario"
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
///imprime un usuario desde un arreglo de estructuras, se le pasa la posicion y el arreglo mismo
void muestra1Usuario(usuario arreglo[100], int posicion)
{
    puts("---------------------------------------------");
    if(arreglo[posicion].estado==1){
        printf("Estado: ACTIVO\n");
    }
    else{
        printf("Estado: INACTIVO\n");
    }
    printf("Nombre y apellido:");
    printf("%s\n", arreglo[posicion].nombreApellido);
    printf("Genero:");
    printf("%c\n", arreglo[posicion].genero);
    printf("DNI:%ld\n", arreglo[posicion].dni);
    printf("Mail:%s\n", arreglo[posicion].mail);
    printf("CBU:%s\n", arreglo[posicion].cbu);
    puts("---------------------------------------------");
}

///pasa los registros del archivo al arreglo de archivos.
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

///ordena los datos del arreglo de estructuras por el dato DNI
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

///Muestra el arreglo de usuarios por pantalla hasta que ya no tenga mas q mostrar
void muestraArregloUsuarios (usuario usuArray[100], int validos)
{
    int i=0;
    while(i<validos)
    {
        muestra1Usuario(usuArray, i);
        i++;
    }
}
///ordenar el arreglo de estructuras por el dato nombre
void ordenaXnombre(usuario arrayUsu[], int validos)
{
    usuario usuAux;
    int i,j;

    for(i=0; i<validos; i++)
    {
        for(j=i+1; j<validos; j++)
        {
            if(strcmp(arrayUsu[i].nombreApellido, arrayUsu[j].nombreApellido)>0)
            {
                usuAux=arrayUsu[i];
                arrayUsu[i]=arrayUsu[j];
                arrayUsu[j]=usuAux;
            }
        }
    }
}
///ordena el arreglo de estructuras por el tipo de dato genero
void ordenaXgenero(usuario arrayUsu[], int validos)
{
    usuario usuAux;
    int i,j;

    for(i=0; i<validos; i++)
    {
        for(j=i+1; j<validos; j++)
        {
            if(arrayUsu[i].genero> arrayUsu[j].genero)
            {
                usuAux=arrayUsu[i];
                arrayUsu[i]=arrayUsu[j];
                arrayUsu[j]=usuAux;
            }
        }
    }
}

///esta funcion crea una animacion en el menu principal al ingresar en el banco
void imprimir_letra_por_letra(const char* texto)
{
    int i, len = strlen(texto);
    for (i = 0; i < len; i++)
        {
        printf("%c", texto[i]);
        fflush(stdout); // Limpiar el búfer de salida para mostrar la letra actual
        usleep(100000); // Pausa de 100 milisegundos (0.1 segundos)
         }
}
///busca un usuario por su cbu
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
///muestra por pantalla cada un usuario seleccionado
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
///una funcion que retorna 1 si decide eliminar la cuenta o 0 si se arrepiente de ello
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
///retorna para reescribir el estado de la cuenta en 0(desactivado)
usuario desactivar(usuario usu){

    usu.estado=0;

    return usu;
}
///desactiva la cuenta del usuario iniciado
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
///si encuentra el cbu devuelve 1 sino 0
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
///si encuentra el dni devuelve 1 sino 0
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
/// busca un usuario a travez del dni

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
///funcion que cuando el admin la ejecuta el usuario queda dado de baja y no podra iniciar mas la sesion
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
///chequea si el admin esta, devuelve 1 si esta 0 si no
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
