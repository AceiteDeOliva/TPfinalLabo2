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
    int cbu;

}sTsaldo;

typedef struct
{
    int estado; // 0 para inactivo o 1 para activo
    char nombreApellido[30];
    long int dni;
    char genero; // f si es femenino o m si es masculino
    char mail[50];
    char contrasenia[20];
    int cbu;
    sTsaldo saldo;
}usuario;

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
    int cbuEmisor;
    int cbuReceptor;
    int tipoDeOperacion;  ///0 emite 1 recibe
    int monto;
}movimiento;

typedef struct nodoDoble
{
    movimiento dato;
    struct nodoDoble * siguiente;
    struct nodoDoble * anterior;
} nodoDoble;

typedef struct
{
    struct nodoDoble * cabecera;
    struct nodoDoble * cola;
} fila;


///funciones generales/utilidades:
usuario AdminCreate(usuario Admin);
void crearAdmin();
char deseaSalir();
void muestra1Usuario(usuario usu);
int chequeomail (char mail[]);

///Menu principal:
int opcionMenuPrincipal();
int menuPrincipal(int opcionElegida, usuario cuenta);
usuario crea1Usuario (usuario nuevoUsuario, int cbu);
void CrearUsuario();
usuario cajaEnCero(usuario usu, int cbu);
void crearSaldo(int cbu);
usuario inicioSesion();
int detectaUsuario(usuario usuBuscado, int cbu);

///menu de sesion iniciada:
int menuInicioSesion(int cbu);
void muestraSaldo(usuario usu);
void corroborarSaldo(int cbu);
void prestamo(int cbu);
usuario prestamoSaldo(int cbu,usuario usu);
usuario deudaApagar(usuario deuda);
void pagarPrestamo(int cbu);
movimiento carga1Transfer(movimiento transfer, int cbu);
usuario cambio1(usuario usu, movimiento tran);
usuario cambio2(usuario usu, movimiento tran);
void tranferencia(int cbuPaga);
usuario newPass(usuario usu, char contrasenia[20]);
void modPass(char contrasenia[20], int cbu);
int generarDigitoAleatorio();
int generarCBU(int digitos);

///ADMINISTRADOR:
int chequeoAdmin(int flag, usuario admin);
int menuAdmin();
void verUsuariosMenu();
usuario busquedaUsuXCBU(int cbu,int *flag);
void muestraUsuarioAdmin(usuario usu);
int seguroDeseaEliminar();
usuario desactivar(usuario usu);
void desactivarCuenta(int cbu);
int chequeoDNI(long int dni);
int chequeoCBU(int cbu);
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

//Filas
void inicFila(fila * fila);
void agregarAFila(fila * fila,sTtransfer dato);
nodoDoble* crearNodoDoble(sTtransfer dato);
nodoDoble * buscarUltimo(nodoDoble * lista);
