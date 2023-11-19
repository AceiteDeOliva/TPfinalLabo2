#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define archivo  "usuario"
#define archivo2 "saldo"
#define archivo3 "movimientos"
#define archivo4 "empleados"

///ESTRUCTURAS

typedef struct
{
    int estado; // 0 para inactivo o 1 para activo
    char nombreApellido[30];
    int dni;
    char genero; // f si es femenino o m si es masculino
    char mail[50];
    char contrasenia[20];
    int cbu;
    long int saldo;
}usuario;

typedef struct
{
    time_t fecha;
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

typedef struct nodoArbol
{
    usuario dato;
    fila movimiento;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;

typedef struct nodoListaS
{
    usuario dato;
    struct nodoListaS* siguiente;
}nodoListaS;


//arreglo de listas
///NUEVAS ESTRUCTURAS
typedef struct
{
    char nombreTrabajo[30];
    int estado;  ///1 activo 0 inactivo
    char nombreYapellido[30];
    int dni;
    char fechaDeNacimiento[30]; ///asi xx/xx/xxxx
    int NumeroTelefono;
}stRegistroEmpleado;

typedef struct
{
    int estado;  ///1 activo 0 inactivo
    char nombreYapellido[30];
    int dni;
    char fechaDeNacimiento[30]; ///asi xx/xx/xxxx
    int NumeroTelefono;
}empleado;

typedef struct nodoEmpleado
{
    empleado dato;
    struct nodoEmpleado* siguiente;
}nodoEmpleado;

typedef struct
{
    char nombreTrabajo[30];
    nodoEmpleado* listaEmpleados;
}celda;


///funciones generales/utilidades:
usuario AdminCreate(usuario Admin);
void crearAdmin();
void muestra1Usuario(usuario usu);
int chequeomail (char mail[]);
void funcionConBarraDeCarga();
void reemplazarDato(usuario usu);
void menuOpcionesAdminUsuario(nodoArbol* usuarioBuscado);
void movimientoAArchivo(movimiento aux);

///Menu principal:
int opcionMenuPrincipal();
void menuPrincipal(int opcionElegida);
usuario crea1Usuario (usuario nuevoUsuario);
void CrearUsuario();
usuario inicioSesion();
int chequeoCredenciales(usuario usuBuscado, usuario ingreso);

///menu de sesion iniciada:
void menuInicioSesion(nodoArbol * cuenta);
void muestraSaldo(usuario usu);
void prestamo(int cbu);
usuario prestamoSaldo(int cbu,usuario usu);
usuario deudaApagar(usuario deuda);
void pagarPrestamo(int cbu);
void carga1Transfer (nodoArbol * raiz,nodoArbol * cuenta);
usuario cambio1(usuario usu, movimiento tran);
usuario cambio2(usuario usu, movimiento tran);
void tranferencia(nodoArbol * cuenta);
usuario newPass(usuario usu);
void modPass(char contrasenia[20], int cbu);
int generarDigitoAleatorio();
int generarCBU(int digitos);


///ADMINISTRADOR:
int chequeoAdmin(int flag, usuario admin);
void menuAdmin();
void verUsuariosMenu();
usuario busquedaUsuXCBU(int cbu,int *flag);
void muestraUsuarioAdmin(usuario usu);
int seguroDeseaEliminar();
usuario desactivar(usuario usu);
void desactivarCuenta(int cbu);
int chequeoDNI(int dni);
int chequeoCBU(int cbu);
usuario busquedaUsuXDNI(int dni, int *flag);
void darDeBajaOAltaAdmin();
int chequeoAdmin(int flag, usuario admin);
void ordenaxDNI(usuario arrayUsu[], int validos);
int ArchiToArray(usuario arrayUsu[], int dimension);
void menuAdmin2(long int dni);
void fromArchiToTransfer();
void modificaArchivo(usuario dato);

//Filas
void inicFila(fila * fila);
void agregarAFila(fila * fila,movimiento dato);
nodoDoble* crearNodoDoble(movimiento dato);
nodoDoble * buscarUltimo(nodoDoble * lista);
void mostrarMovimiento(movimiento m);
void mostrarListaDoble(nodoDoble * lista);
void fromFileToFila(nodoArbol * cuenta);
movimiento generarDeposito(nodoArbol * cuenta);
void depositarExtraer(nodoArbol * cuenta);

///ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(usuario dato);
nodoArbol* cargarArbolOrdenDNI(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* fromArchiToArbolDNI(nodoArbol* arbol);
nodoArbol* buscarDNIenArbol(nodoArbol* arbol,int dni);
nodoArbol* modificarUsuario(nodoArbol * arbol);
nodoArbol * cambiarEstado(nodoArbol * arbol);
void mostrarArbolInorden(nodoArbol* arbol);
nodoArbol* buscarCBUenArbol(nodoArbol* arbol,int cbu);
nodoArbol* fromArchiToArbolCBU(nodoArbol* arbol);
void borrarArbol(nodoArbol* raiz) ;

///LISTAS
nodoListaS* inicLista();
nodoListaS* crearNodoListaS(usuario dato);
void mostrarLista(nodoListaS* lista);
nodoListaS* agregarEnOrden(nodoListaS* lista, nodoListaS* nuevoNodo);
nodoListaS* agregarAlPpio(nodoListaS* lista, nodoListaS* nuevo);
nodoListaS* FromArchiAListaOrdenada(nodoListaS* lista);

//arreglo de listas
void funcionConBarraDeCarga();
void verEmpleadosMenu();
void cargarArchiEmpleados();
stRegistroEmpleado cargarDatosEmpleado();
nodoEmpleado* crearNodoEmplado(empleado dato);
nodoEmpleado* agregarAlPpioEmpleado(nodoEmpleado* lista, nodoEmpleado* nuevo);
void mostrarArchi();
void mostrar1Registro(stRegistroEmpleado registro);
int cargaADL(celda adl[], int dimension, empleado emple, char nombreTrabajo[]);
int alta(celda adl[], int validos, empleado emple, char nombreTrabajo[]);
int buscaPosCelda(celda adl[], int validos, char nombreTrabajo[]);
int agregarCelda(celda adl[], int validos, char nombreTrabajo[]);
nodoEmpleado* agregarEmpleadoEnOrdenPorDni(nodoEmpleado* lista, nodoEmpleado* nuevoNodo);
int fromArchiEmpleadosToADL(celda adlEmpleados[], int dimension);
empleado fromArchiToEmpleado(stRegistroEmpleado r);
void mostrarADLempleados(celda adl[], int validos);
void mostrarListaEmpleados(nodoEmpleado* lista);
void mostrarDatosListaEmpleados(nodoEmpleado* lista);
