#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define archivo  "usuario"
#define archivo2 "saldo"
#define archivo3 "transferencias"
///ESTRUCTURAS
typedef struct
{
    long int caja;
    long int prestamo;
    long int dni; /// el dni y el cbu es lo que nos va a ayudar a realizar las transferencias y demás...
    char cbu[10];

}sTsaldo;

typedef struct
{
    int estado; // 0 para inactivo o 1 para activo
    char nombreApellido[30];
    long int dni;
    char genero; // f si es femenino o m si es masculino
    char mail[50];
    char contrasenia[20];
    char cbu[10];
    sTsaldo saldo;
}usuario;

typedef struct
{
    long int importe;
    char referencia[10];
    char cbuReceptor[10];
}sTtransfer;

typedef struct nodoArbol
{
    usuario dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;

typedef struct nodoListaS
{
    usuario dato;
    struct nodoListaS* siguiente;
}nodoListaS;

typedef struct
{
    long int cbuEmisor;
    long int cbuReceptor;
    int tipoDeOperacion;  ///0 emite 1 recibe
    int monto;
}transferencia;

///funciones generales/utilidades:
usuario AdminCreate(usuario Admin);
void crearAdmin();
char deseaSalir();
void muestra1Usuario(usuario usu);
int chequeomail (char mail[]);

///Menu principal:
int opcionMenuPrincipal();
int menuPrincipal(int opcionElegida, usuario cuenta);
usuario crea1Usuario (usuario nuevoUsuario, char cbu[10]);
void CrearUsuario();
usuario cajaEnCero(usuario usu, char cbu[10]);
void crearSaldo(char cbu[10]);
usuario inicioSesion();
int detectaUsuario(usuario usuBuscado, char cbu[10]);

///menu de sesion iniciada:
int menuInicioSesion(char cbu[10]);
void muestraSaldo(usuario usu);
void corroborarSaldo(char pcbu[]);
void prestamo(char cbu[10]);
usuario prestamoSaldo(char cbu[10],usuario usu);
usuario deudaApagar(usuario deuda);
void pagarPrestamo(char cbu[10]);
sTtransfer carga1Transfer(sTtransfer transfer, char cbuPaga[10]);
usuario cambio1(usuario usu, sTtransfer tran);
usuario cambio2(usuario usu, sTtransfer tran);
void tranferencia(char cbuPaga[10]);
usuario newPass(usuario usu, char contrasenia[20]);
void modPass(char contrasenia[20], char cbu[10]);
int generarDigitoAleatorio();
int generarCBU(int digitos);

///ADMINISTRADOR:
int chequeoAdmin(int flag, usuario admin);
int menuAdmin();
void verUsuariosMenu();
usuario busquedaUsuXCBU(char cbu[],int *flag);
void muestraUsuarioAdmin(usuario usu);
int seguroDeseaEliminar();
usuario desactivar(usuario usu);
void desactivarCuenta(char cbu[20]);
int chequeoDNI(long int dni);
int chequeoCBU(char cbu[]);
usuario busquedaUsuXDNI(long int dni, int *flag);
void darDeBajaOAltaAdmin();
int chequeoAdmin(int flag, usuario admin);
void ordenaxDNI(usuario arrayUsu[], int validos);
int ArchiToArray(usuario arrayUsu[], int dimension);
void menuAdmin2(long int dni);
void fromArchiToTransfer();
void modificaArchivo(usuario dato);

///ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(usuario dato);
nodoArbol* cargarArbloOrdenDNI(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* fromArchiToArbol(nodoArbol* arbol);
nodoArbol* buscarDNIenArbol(nodoArbol* arbol, long int dni);
nodoArbol* modificarUsuario(nodoArbol * arbol);
nodoArbol * cambiarEstado(nodoArbol * arbol);

///LISTAS
nodoListaS* inicLista();
nodoListaS* crearNodoListaS(usuario dato);
void mostrarLista(nodoListaS* lista);
nodoListaS* agregarEnOrden(nodoListaS* lista, nodoListaS* nuevoNodo);
nodoListaS* agregarAlPpio(nodoListaS* lista, nodoListaS* nuevo);
nodoListaS* FromArchiAListaOrdenada(nodoListaS* lista);
