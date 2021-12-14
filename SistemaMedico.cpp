#include <iostream>
#include <ctime>
#include <cstdlib>

#include "listaUsuario.h"

using namespace std;

//prototipos
void personasRegistradas();
void registrarCuentaUsuario();
int generarCodigo();
string validarNumeroCuenta();
string solicitudContrasenia();

bool confirmarCredencialesAdmin(string,string);
bool confirmarCredencialesEstandar(string,string);

void menuAdmin();
void menuEstandar();

void limP();
void pausa();
void clean_stdin(void);

//lista de objetos Usuario
ListaUsuario *usuarios = new ListaUsuario();
int nUsuarios=1; //lleva el control de la posicion en la lista donde se colocara

//funcion principal
int main(){
	srand(time(0)); // seteando la semilla
	
	//var locales del main
	bool salir=false;
	string usuario;
	string contrasenia;
	
	int opc=0;
	
	do{
		limP();
		//menu principal
		cout<<"     ...................................."<<endl;
		cout<<"         Bienvenido al Sistema Medico"<<endl;
		cout<<"     ...................................."<<endl<<endl;	
		cout<<" *Ingrese 1 para ir al Login"<<endl<<endl;
		cout<<" *Ingrese 2 para Registrar Cuenta de Usuario"<<endl<<endl;
		cout<<" *Ingrese 3 para ir al Menu de personas registradas"<<endl<<endl;
		cout<<" *Ingrese 0 para Salir\n\n->";
		
		cin>>opc;
		
		clean_stdin();
		limP();
		
		switch(opc){ //estudio de casos
		
			case 0:{
				cout<<"Saliendo...";
				pausa();
				salir=true;
				break;
			}
			
			case 1:{
				cout<<" *Ingrese el usuario\n->";
				cin>>usuario;
				cout<<"\n *Ingrese la contrasenia\n->";
				cin>>contrasenia;
				
				clean_stdin();
				
				if(confirmarCredencialesAdmin(usuario,contrasenia)){
					menuAdmin();
				}else if(confirmarCredencialesEstandar(usuario,contrasenia)){
					menuEstandar();
					cout<<"\ndentro     \n";
					pausa();
				}
				
				break;
			}
			
			case 2:{
				registrarCuentaUsuario();
				break;
			}
			
			case 3:{
				personasRegistradas();
				break;
			}
		}
	}while(!salir);
	
	return 0;
}

//metodo que crea una cuenta usuario
void registrarCuentaUsuario(){
	
	int codigo=0;
	string nombre;
	char tipo=' ';
	string numeroCuenta;
	string contrasenia;
	int estado=0;
	
	int aux;
	
	Usuario userAux;
	
	//Codigo
	codigo=generarCodigo();
	userAux.setCodigo(codigo);
	//clean_stdin();
	
	//nombre
	cout<<"*Ingrese el NOMBRE del Usuario\n->";
	cin>>nombre;
	userAux.setNombre(nombre);
	
	//tipo
	do{
		cout<<"*Ingrese el TIPO del Usuario (A=Administrado / E=Estandar)\n->";
		cin>>tipo;
		if(tipo!='E' && tipo!='A'){
			cout<<"Error! Debe ingresar E para indicar usuario estandar, o A para indicar usuario Administrado";
			pausa();
		}
	}while(tipo!='E' && tipo!='A'); //ciclo que asegura un caracter correcto entre E o A
	
	userAux.setTipo(tipo);
	
	//numero de cuenta
	numeroCuenta=validarNumeroCuenta();
	userAux.setNumeroCuenta(numeroCuenta);
	clean_stdin();
	
	//contrasenia
	contrasenia=solicitudContrasenia();
	userAux.setContrasenia(contrasenia);
	
	//estado
	userAux.setEstado(1); //se asume activa la cuenta (ya que es aperturada como nueva)
	
	clean_stdin();
	
	limP();
	
	usuarios->insertar(nUsuarios, userAux); //se inserta el usuario auxiliar en la lista de usuarios dinamica, en la posicion de nUsuarios
	
	//verificacion de registro
	Usuario userVerificacion=usuarios->getObjetoPorCodigo(codigo);
	
	cout<<"\n          *Usuario Registrado Correctamente\n";
	//mostrar datos de la cuenta
	cout<<"\n*Codigo de la Cuenta: "<<userVerificacion.getCodigo()<<endl<<endl;
	cout<<"\n*Numero de Cuenta: "<<userVerificacion.getNumeroCuenta()<<endl<<endl;
	cout<<"\n*Contrasenia: "<<userVerificacion.getContrasenia()<<endl<<endl;
	cout<<"\n*Nombre del Usuario: "<<userVerificacion.getNombre()<<endl<<endl;
	if(userVerificacion.getTipo()=='A'){
		cout<<"\n*Tipo del Usuario: Administrador"<<endl<<endl;
	}else{
		cout<<"\n*Tipo del Usuario: Estandar"<<endl<<endl;
	}
	if(userVerificacion.getEstado()){
		cout<<"\n*Estado de la Cuenta: Activa"<<endl<<endl;
	}else{
		cout<<"\n*Estado de la Cuenta: Inactiva"<<endl<<endl;
	}
	
	nUsuarios++;
	pausa();
}

//metodo que genera un numero de cuenta irrepetible
int generarCodigo(){
	int num=0;
	bool encontrado=false;
	
	do{
		num = rand() % 500 + 100;
		
		encontrado=false;
	
		if(usuarios->buscarPorCodigo(num)){ 
			encontrado=true;
		}
	
	}while(encontrado); //ciclo que asegura buscar un codigo no repetido
	
	return num;
}

//metodo que solicita y valida una contrasenia
string solicitudContrasenia(){
	//faltan validaciones...
	string contrasenia;
	
	cout<<"*Ingrese la Contrasenia del Usuario\n->";
	cin>>contrasenia;
	
	return contrasenia;
}

//metodo que genera un numero de cuenta irrepetible
string validarNumeroCuenta(){
	string num;
	bool encontrado=false;
	bool tamAceptable=false;
	
	do{
		//solicitar la cuenta de usuario
		cout<<"\n*Ingrese la cuenta de usuario (debe contener 8 caracteres)\n->";
		cin>>num;
		
		encontrado=false;
	
		if(usuarios->buscarPorNumCuenta(num) ){ //compara si el usuario  tiene el mismo numero de cuenta que el num ingresado
			encontrado=true;
			cout<<"*Error, cuenta ya en uso!\n";
		}
		
		//validacion de tamanio de 8 caracteres
		if(num.length()==8)
			tamAceptable=true;
		else{
			tamAceptable=false;
			cout<<"\nError, la cuenta ingresada no contiene 8 caracteres...\n";
		}
			
	}while(encontrado || !tamAceptable); //ciclo que asegura buscar un numero de cuenta no repetido  
	
	return num;
}

//metodo que confirma las credenciales de admin
bool confirmarCredencialesAdmin(string usuario, string contrasenia){
	//var locales
	bool pasar=false;

	
	if(usuarios->buscarPorNumCuenta(usuario)){ //busca si existe un Usuario con ese numero de usuario
		Usuario userAux=usuarios->getObjetoPorNumCuenta(usuario); //de encontrarlo, se obtiene ese usuario y se pasan los datos al usuario auxiliar para validar su contrasenia y tipo
		
		if(userAux.getContrasenia()==contrasenia && userAux.getTipo()=='A'){ //validacion de la contrasenia y el tipo
			pasar=true; //puede pasar
		}

	}

	if(pasar) //se retorna true si pasar es true, y false de lo contrario
		return true;
	else
		return false;
}

//metodo que confirma las credenciales de usuario
bool confirmarCredencialesEstandar(string usuario, string contrasenia){
	//var locales
	bool pasar=false;

	
	if(usuarios->buscarPorNumCuenta(usuario)){ //busca si existe un Usuario con ese numero de usuario
		Usuario userAux=usuarios->getObjetoPorNumCuenta(usuario); //de encontrarlo, se obtiene ese usuario y se pasan los datos al usuario auxiliar para validar su contrasenia y tipo
		
		if(userAux.getContrasenia()==contrasenia && userAux.getTipo()=='E'){ //validacion de la contrasenia y el tipo
			pasar=true; //puede pasar
		}

	}

	if(pasar) //se retorna true si pasar es true, y false de lo contrario
		return true;
	else
		return false;
}

//sub menu admin
void menuAdmin(){
	//var locales
	
	int opc;
	
	do{
		limP(); //borrar pantalla
		//sub menu admin
		cout<<"     ...................................."<<endl;
		cout<<"         Sub Menu Administrador"<<endl;
		cout<<"     ...................................."<<endl<<endl;
		cout<<" *Ingrese 1 para Crear/Eliminar cuentas de usuario\n\n";
		cout<<" *Ingrese 2 para Activar/Desactivar cuentas de usuario\n\n";
		cout<<" *Ingrese 3 para Ingresar cuenta de un doctor\n\n";
		cout<<" *Ingrese 4 para Eliminar informacion de un doctor\n\n";
		cout<<" *Ingrese 5 para Modificar informacion de un doctor\n\n";
		cout<<" *Ingrese 6 para Realizar el Ingrese de un paciente\n\n";
		cout<<" *Ingrese 7 para Eliminar un paciente\n\n";
		cout<<" *Ingrese 8 para Modificar informacion de un paciente\n\n";
		cout<<" *Ingrese 9 para Volver al menu principal\n\n->";
		cin>>opc;
		
		clean_stdin();
		limP();
		
		switch(opc){ //estudio de casos
			
			//crear o eliminar cuentas de usuario
			case 1:{
				//var de tiempo de uso del caso 1
				int opc2=0;
				int codigo=0;
				
				do{
					cout<<"*Ingrese 1 para CREAR cuenta de usuario\n\n";
					cout<<"*Ingrese 2 para ELIMINAR cuenta de usuario\n\n->";
					cin>>opc2;
					limP();
					
				}while(opc2<1 || opc>2);
				
				clean_stdin();
				
				if(opc2==1){
					registrarCuentaUsuario(); //invocacion de la funcion crear cuenta usuario
				}else{
					bool encontrado=false;
					Usuario userAux;
					int posicion=0;
					
					cout<<"*Ingrese el codigo del usuario a Eliminar\n\n->";
					cin>>codigo;
					
					clean_stdin();
					
					if(usuarios->buscarPorCodigo(codigo)){ 
					
						encontrado=true;
						
						posicion=usuarios->getPosicionPorCodigo(codigo);
						
						usuarios->borrar(posicion); //se llama a la funcion borrar
						
						cout<<"\n*Usuario de codigo: "<<codigo<<" Ha sido eliminado correctamente"<<endl;
						pausa();
						
						nUsuarios--; //se decrementa la cantidad de usuarios
						break; //se detiene el bucle si ya se encontro coincidencia de los credenciales
					}
		
					if(!encontrado){
						cout<<"\n*Usuario de codigo: "<<codigo<<" no ha sido encontrado en la lista"<<endl;
						pausa();
					}

				}
				
				break;
			}
		
			case 9:{
				cout<<"\n*Saliendo al menu principal...";
				pausa();
				break;
			}
			
			default:{
				cout<<"\nParametro ingresado no valido...\n";
				pausa();
				break;
			}
			
		}
		
	}while(opc!=9); //ciclo del sub menu admin
}

//submenu estandar
void menuEstandar(){
	
}

//submenu de personas registradas
void personasRegistradas(){
	int opc=0;
	
	do{
		limP();
		cout<<"     ...................................."<<endl;
		cout<<"         Sub Menu Mostrar Personas"<<endl;
		cout<<"     ...................................."<<endl<<endl;
		cout<<" *Ingrese 1 para ver todos los usuarios registrados"<<endl<<endl;
		cout<<" *Ingrese 2 para ver todos los doctores registrados"<<endl<<endl;
		cout<<" *Ingrese 3 para ver todos los pacientes registrados"<<endl<<endl;
		cout<<" *Ingrese 0 para Salir\n\n->";
		cin>>opc;
		
		clean_stdin();
		limP();
		
		switch(opc){
			
			case 0:{
				break;
			}
			
			case 1:{
				usuarios->imprimirUsuarios();
				pausa();
				break;
			}
			
			default:{
				cout<<"*Parametro no valido";
				pausa();
				break;
			}
		}
		
	}while(opc!=0);
}

//metodo que borra la pantalla
void limP()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

//metodo que pausa el sistema y espera a una accion de teclado para continuar
void pausa()
{
	cout << "\n\nPresione una tecla para continuar...\n";
	cin.get();
}

//metodo que limpia el buffer
void clean_stdin(void)
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}
