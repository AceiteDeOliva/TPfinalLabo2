#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

typedef struct
{
    long int caja;
    long int prestamo;
} sTsaldo;

typedef struct
{
    int estado; /// 0 para inactivo o 1 para activo
    char nombreApellido[30];
    long int dni;
    char genero; ///masculino, femenino
    char mail[50];
    char contrasenia[20];
    int cbu;
    sTsaldo saldo;
} usuario;

typedef struct nodoArbol
{
    usuario dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

//11111111111111111111111111111111111111111111111111111111111111111111111
typedef struct
{
    int cbuEmisor;
    int cbuReceptor;
    int importe;
    time_t fecha;
} transferencia;

typedef struct
{
    struct nodoDoble * cabecera;
    struct nodoDoble * cola;
} fila;

typedef struct nodoDoble
{
    transferencia dato;
    struct nodoDoble * siguiente;
    struct nodoDoble * anterior;
} nodoDoble;

typedef struct{
    long int importe;
    char referencia[10];
    char cbuReceptor[10];
}sTtransfer;

void imprimirUsuario(usuario u);
nodoArbol* modificarUsuario(nodoArbol * arbol);
int generarCBU();
int generarDigitoAleatorio();
nodoArbol * cambiarEstado(nodoArbol * arbol);
nodoArbol* existePaciente(nodoArbol* pacientes, int dniPaciente);
void inicFila(fila * fila);
void agregarAFila(fila * fila,transferencia dato);
nodoDoble* crearNodoDoble(transferencia dato);
nodoDoble * buscarUltimo(nodoDoble * lista);

#endif // HEADERS_H_INCLUDED
