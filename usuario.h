#include <iostream>
#include <string.h>

class Usuario{
	
	public:
		Usuario();
		~Usuario();
		Usuario(int ACodigo, std::string ANombre, char ATipo, std::string ANumeroCuenta,std::string AContrasenia, int AEstado);
		
		void CambiarEstado(int AEstado);
		
		void setCodigo(int ACodigo);
		void setNombre(std::string ANombre);
		void setContrasenia(std::string AContrasenia);
		void setTipo(char ATipo);
		void setNumeroCuenta(std::string ANumeroCuenta);
		void setEstado(int AEstado);
		
		int getCodigo();
		std::string getNombre();
		std::string getContrasenia();
		char getTipo();
		std::string getNumeroCuenta();
		int getEstado();
		
	private:
		int Codigo;
		std::string Nombre;
		char Tipo;	
		std::string NumeroCuenta;
		std::string Contrasenia;	
		int Estado;
};

Usuario::Usuario(){
	
}

//metodo constructor
Usuario::Usuario(int ACodigo, std::string ANombre, char ATipo, std::string ANumeroCuenta,std::string AContrasenia, int AEstado){
	Codigo=ACodigo;
	Nombre=ANombre;
	Tipo=ATipo;
	
	NumeroCuenta=ANumeroCuenta;
	Contrasenia=AContrasenia;
	
	if(AEstado==1)
		Estado=1;
	else
		Estado=0;
}

//metodo destructor
Usuario::~Usuario(){ 
	
}

//metodo para cambiar el estado de la cuenta
void Usuario::CambiarEstado(int AEstado){
	if(AEstado==1)
		Estado=1;
	else
		Estado=0;
}

//setters
void Usuario::setCodigo(int ACodigo){
	Codigo=ACodigo;
}

void Usuario::setNombre(std::string ANombre){
	Nombre=ANombre;
}

void Usuario::setContrasenia(std::string AContrasenia){
	Contrasenia=AContrasenia;
}

void Usuario::setTipo(char ATipo){
	Tipo=ATipo;
}

void Usuario::setNumeroCuenta(std::string ANumeroCuenta){
	NumeroCuenta=ANumeroCuenta;
}

void Usuario::setEstado(int AEstado){
	if(AEstado==1)
		Estado=true;
	else
		Estado=false;
}

//getters
int Usuario::getCodigo(){
	return Codigo;
}

std::string Usuario::getNombre(){
	return Nombre;
}

std::string Usuario::getContrasenia(){
	return Contrasenia;
}

char Usuario::getTipo(){
	return Tipo;
}

std::string Usuario::getNumeroCuenta(){
	return NumeroCuenta;
}

int Usuario::getEstado(){
	return Estado;
}

