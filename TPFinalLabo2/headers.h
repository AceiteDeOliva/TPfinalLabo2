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

typedef struct
{

    struct nodoDoble * cabecera;
    struct nodoDoble * cola;
} fila;

typedef struct nodoDoble
{
    int dato;
    struct nodoDoble * siguiente;
    struct nodoDoble * anterior;
} nodoDoble;



void imprimirUsuario(usuario u);
nodoArbol* modificarUsuario(nodoArbol * arbol);
int generarCBU();
int generarDigitoAleatorio();
nodoArbol * cambiarEstado(nodoArbol * arbol);
nodoArbol* existePaciente(nodoArbol* pacientes, int dniPaciente);
void inicFila(fila * fila);


#endif // HEADERS_H_INCLUDED
