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
    long int dni;
    char fechaDeNacimiento[30]; ///asi xx/xx/xxxx
    char NumeroTelefono[20];
}stRegistroEmpleado;

typedef struct
{
    int estado;  ///1 activo 0 inactivo
    char nombreYapellido[30];
    long int dni;
    char fechaDeNacimiento[30]; ///asi xx/xx/xxxx
    char NumeroTelefono[20];
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
void muestra1Usuario(usuario usu);
int chequeomail (char mail[]);
void funcionConBarraDeCarga();
void reemplazarDato(usuario usu);
void menuOpcionesAdminUsuario(nodoArbol* usuarioBuscado);
void movimientoAArchivo(movimiento aux);
void dibujoBancoCentral();

///Menu principal:
void menuPrincipal(int opcionElegida);
usuario crea1Usuario (usuario nuevoUsuario);
void CrearUsuario();
usuario inicioSesion();
int chequeoCredenciales(usuario usuBuscado, usuario ingreso);

///menu de sesion iniciada:
void menuInicioSesion(nodoArbol * cuenta);
void carga1Transfer (nodoArbol * raiz,nodoArbol * cuenta);
void tranferencia(nodoArbol * cuenta);
usuario newPass(usuario usu);
void modPass(char contrasenia[20], int cbu);
int generarDigitoAleatorio();
int generarCBU(int digitos);


///ADMINISTRADOR:
void menuAdmin();
void verUsuariosMenu();
void muestraUsuarioAdmin(usuario usu);
void menuOpcionesAdminEmpleado(celda trabajo[],int posTrabajo,nodoEmpleado*empleadoBuscado,int validos);
int seguroDeseaEliminar();
usuario desactivar(usuario usu);
usuario activar(usuario usu);
usuario altaBaja (usuario usu, nodoArbol* arbol);
int chequeoDNI(int dni);


//Filas
void inicFila(fila * fila);
void agregarAFila(fila * fila,movimiento dato);
nodoDoble* crearNodoDoble(movimiento dato);
nodoDoble * buscarUltimo(nodoDoble * lista);
void mostrarMovimiento(movimiento m);
void fromFileToFila(nodoArbol * cuenta,fila * filita);
movimiento generarDeposito(nodoArbol * cuenta);
void depositarExtraer(nodoArbol * cuenta);
movimiento verPrimero(nodoDoble * lista);
nodoDoble * borrarPrimero(nodoDoble * lista);
void recorrerMostrarExtraerFila(fila * fila);

///ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(usuario dato);
nodoArbol* cargarArbolOrdenDNI(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* fromArchiToArbolDNI(nodoArbol* arbol);
nodoArbol* buscarDNIenArbol(nodoArbol* arbol,int dni);
nodoArbol* modificarUsuario(nodoArbol * arbol);
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
nodoListaS* FromArchiAListaOrdenadaDesactivados(nodoListaS* lista);
void borrarLista(nodoListaS** lista);
//arreglo de listas
void funcionConBarraDeCarga();
void funcionConBarraDeCargaLento();
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
void mostrarDatosListaEmpleados(nodoEmpleado*nodo);
nodoEmpleado* buscarEmpleadoXdni(celda trabajos[], int validos, long int dniBuscado,int*i);
void AltaYbajaEmpleado(celda trabajos[],int posTrabajo,nodoEmpleado*emplead, int validos);
void reemplazarDatoEmpleado(celda trabajos[], int posTrabajo, empleado dato);
int modificarEmpleado(celda trabajo[],int posTrabajo,nodoEmpleado**empleadoBuscado,int*validos);
int verificarTrabajoRepetido(celda trabajos[],int validos,char nombreTrabajo[]);
int alta2(celda adl[], int validos,nodoEmpleado*emple, char nombreTrabajo[]);
nodoEmpleado* borrarNodoEmpleado(nodoEmpleado*lista,nodoEmpleado*nodoABorrar);
int RetornarPosTrabajo(celda trabajos[],char nombreTrabajo[],int validos);
void mostrarEmpleado(celda trabajo[],int posTrabajo,empleado dato);
int esFechaValida(char fechaDeNacimiento[11]);
