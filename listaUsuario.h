#include <iostream>
#include "usuario.h"

using namespace std;

class ListaUsuario {
private:
    class Nodo {
    public:
        Usuario user;
        Nodo *sig;
    };

    Nodo *raiz;
public:
    ListaUsuario();
    ~ListaUsuario();
    int cantidad();
    void insertar(int pos, Usuario x);
    void borrar(int pos);
    bool vacia();
    void imprimirUsuarios();
    bool buscarPorCodigo(int codigo);
    bool buscarPorNumCuenta(string nCuenta);
    int getPosicionPorCodigo(int codigo);
    Usuario getObjetoPorCodigo(int codigo);
    Usuario getObjetoPorNumCuenta(string nCuenta);
};

ListaUsuario::ListaUsuario()
{
    raiz = NULL;
}

ListaUsuario::~ListaUsuario()
{
    Nodo *reco = raiz;
    Nodo *bor;
    while (reco != NULL)
    {
        bor = reco;
        reco = reco->sig;
        delete bor;
    }
}

int ListaUsuario::cantidad()
{
    Nodo *reco = raiz;
    int cant = 0;
    while (reco != NULL)
    {
        cant++;
        reco = reco->sig;
    }
    return cant;
}

void ListaUsuario::insertar(int pos, Usuario x)
{
    if (pos <= cantidad() + 1)    
    {
        Nodo *nuevo = new Nodo();
        nuevo->user = x;
        if (pos == 1)
        {
            nuevo->sig = raiz;
            raiz = nuevo;
        }
        else
            if (pos == cantidad() + 1)    
            {
                Nodo *reco = raiz;
                while (reco->sig != NULL) 
                {
                    reco = reco->sig;
                }
                reco->sig = nuevo;
                nuevo->sig = NULL;
            }
            else 
            {
                Nodo *reco = raiz;
                for (int f = 1; f <= pos - 2; f++)
                {
                    reco = reco->sig;
                }
                Nodo *siguiente = reco->sig;
                reco->sig = nuevo;
                nuevo->sig = siguiente;
            }
    }
}

void ListaUsuario::borrar(int pos)
{
    if (pos <= cantidad())    
    {
        Nodo *bor;
        if (pos == 1) 
        {
            bor = raiz;
            raiz = raiz->sig;
        }
        else {
            Nodo *reco;
            reco = raiz;
            for (int f = 1; f <= pos - 2; f++)
            {
                reco = reco->sig;
            }
            Nodo *prox = reco->sig;
            reco->sig = prox->sig;
            bor = prox;
        }
        delete bor;
    }
}

bool ListaUsuario::vacia()
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

void ListaUsuario::imprimirUsuarios()
{
    Nodo *reco = raiz;
    cout << "     *Listado completo de Usuarios.\n\n\n";
    while (reco != NULL)
    {
    	cout << "Codigo: " << reco->user.getCodigo() << "\n";
        cout << "Nombre: " << reco->user.getNombre() << "\n";
        cout << "nCuenta: " << reco->user.getNumeroCuenta() << "\n";
        cout << "Contrasenia: " << reco->user.getContrasenia() << "\n";
        reco = reco->sig;
        cout << "\n";
        cout << "\n";
    }
    cout << "\n";
}

int ListaUsuario::getPosicionPorCodigo(int codigo) 
{
	int posicion=0;
	
    Nodo *reco = raiz;
    while (reco != NULL) 
    {
    	posicion++;
        if (reco->user.getCodigo() == codigo)
            return posicion;
            
        reco = reco->sig;
    }
    return posicion;
}

bool ListaUsuario::buscarPorCodigo(int codigo) 
{
    Nodo *reco = raiz;
    while (reco != NULL) 
    {
        if (reco->user.getCodigo() == codigo)
            return true;
        reco = reco->sig;
    }
    return false;
}

bool ListaUsuario::buscarPorNumCuenta(string nCuenta) 
{
    Nodo *reco = raiz;
    while (reco != NULL) 
    {
        if (reco->user.getNumeroCuenta() == nCuenta)
            return true;
        reco = reco->sig;
    }
    return false;
}

Usuario ListaUsuario::getObjetoPorCodigo(int codigo){
	Nodo *reco = raiz;
	Usuario salir;
    while (reco != NULL) 
    {
        if (reco->user.getCodigo() == codigo)
            return reco->user;
        reco = reco->sig;
    }
    
	salir.setCodigo(0);
	return salir;
}

Usuario ListaUsuario::getObjetoPorNumCuenta(string nCuenta){
	Nodo *reco = raiz;
	Usuario salir;
    while (reco != NULL) 
    {
        if (reco->user.getNumeroCuenta() == nCuenta)
            return reco->user;
        reco = reco->sig;
    }
    
	salir.setNumeroCuenta("vacio");
	return salir;
}
