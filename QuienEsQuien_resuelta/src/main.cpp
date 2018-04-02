#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include "../include/quienesquien.h"

using namespace std;

int main(int argc, char * argv[]){

	bool jugar = false;
	bool limpiar = false;
	QuienEsQuien quienEsQuien;
	
	if(argc == 2){
		string parametroAleatorio = "aleatorio";
		if(argv[1]== parametroAleatorio){
			cout << "Creando un QuienEsQuien aleatorio"<< endl;
			int numero_de_personajes;
		   	int numero_de_atributos;

		   	do{
		   		cout << "¿Número de personajes? ";
		   		cin >>numero_de_personajes;
		   	}while(numero_de_personajes<=0);

		   	quienEsQuien.tablero_aleatorio(numero_de_personajes);
			quienEsQuien.mostrar_estructuras_leidas();

		   	string nombreFicheroSalida = string("datos/tablero") +
		   		"-num-per="+to_string(numero_de_personajes)+".csv";

		   	cout << "Guardando tablero aleatorio en "<<nombreFicheroSalida<<endl;
		   	ofstream archivoDeSalida(nombreFicheroSalida);
		   	archivoDeSalida << quienEsQuien;

		   	cout << "Guardado"<<endl;
		   	return 0;

		}else{
			cout << "Cargando fichero para jugar'"<< argv[1] <<"'"<< endl;
			ifstream f (argv[1]);
			if (!f){
				cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
				return 1;
			}
			f>> quienEsQuien;
			jugar = true;
		}
	} else if(argc == 3 ){
		string parametroLimpiar = "limpiar";
		if(parametroLimpiar== argv[2]){
			cout << "Cargando fichero para limpiar (sin jugar) '"<< argv[1] <<"'"<< endl;
			ifstream f (argv[1]);
			if (!f){
				cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
				return 1;
			}
			f>> quienEsQuien;
			jugar = false;
		} else{
			cout << "Modo '"<<argv[2]<<"' no reconocido"<<endl;
			return 1;
		}

	} else {
		cout << "No se reconocen los argumentos. Ejemplos de uso:" << endl;
		cout << "\tJugar:               ./bin/quienesquien RUTA_FICHERO"<< endl;
		cout << "\tLimpiar sin jugar:   ./bin/quienesquien RUTA_FICHERO limpiar"<< endl;
		cout << "\tGenerar aleatorio:   ./bin/quienesquien aleatorio"<< endl;
		return 1;
	}

	quienEsQuien.mostrar_estructuras_leidas();

	bool mejor;
	string mi_respuesta;

	do{
		cout << "¿Como quieres construir el arbol? (basica o mejora): ";
		cin >> mi_respuesta;
		cout << endl;

	}while(mi_respuesta != "mejora" && mi_respuesta != "basica");

	if(mi_respuesta == "mejora")
		quienEsQuien.usar_arbol(quienEsQuien.crear_arbol(1));
	if(mi_respuesta == "basica")
		quienEsQuien.usar_arbol(quienEsQuien.crear_arbol(0));

	cout << "=========== Arbol en crudo ===========" << endl;
	quienEsQuien.escribir_arbol_completo();
	
	cout << "Profundidad promedio de las hojas del arbol: ";
	cout << quienEsQuien.profundidad_promedio_hojas() << endl; 
	cout << "======================================" << endl << endl << endl;

	bool car;
	string resp , nombre;
	vector<bool> caracteristicas(quienEsQuien.num_atributos());

	quienEsQuien.eliminar_nodos_redundantes();

	cout << "=========== Arbol ===================="<<endl;
	quienEsQuien.escribir_arbol_completo();
	cout << "Profundidad promedio de las hojas del arbol: ";
	cout << quienEsQuien.profundidad_promedio_hojas()<<endl; 
	cout << "======================================" << endl << endl << endl;


	string reiniciar;
	do{
		if(mi_respuesta == "basica"){
		//CREAR NUEVO PERSONAJE
			cout << "¿Quieres añadir nuevos personajes al juego? (si no)"<<endl;
			cin >> resp;

			while( !(resp == "no" || resp == "No" || resp == "NO"|| resp == "nO" )){	

				if(resp == "si" || resp == "Si" || resp == "SI"|| resp == "sI" ){
					cout<< "¿Cómo se llama?"<<endl;
					cin >> nombre;
					cout << "Introduce los atributos (como 0 o 1)"<<endl;
						for(int i=0; i<quienEsQuien.num_atributos(); i++) {
							cin>>car;
							caracteristicas[i]=car;
						}

					quienEsQuien.aniade_personaje(nombre, caracteristicas);

				}

				cout << "¿Quieres añadir nuevos personajes? (si no)"<<endl;
				cin >> resp;
			}

			cout << "=========== Arbol + Personajes nuevos ===================="<<endl;
			quienEsQuien.escribir_arbol_completo();
			cout << "Profundidad promedio de las hojas del arbol: ";
			cout << quienEsQuien.profundidad_promedio_hojas()<<endl; 
			cout << "======================================" << endl << endl << endl;
		}
	//ELIMINAR PERSONAJE EXISTENTE

		cout << "¿Quieres eliminar un personaje del juego? (si no)"<<endl;
		cin >> resp;

		while( !(resp == "no" || resp == "No" || resp == "NO"|| resp == "nO" )){	

			if(resp == "si" || resp == "Si" || resp == "SI"|| resp == "sI" ){
				cout<< "¿Cómo se llama?"<<endl;
				cin >> nombre;

				quienEsQuien.elimina_personaje(nombre);
			}

			cout << "¿Quieres eliminar otro personaje? (si no)"<<endl;
			cin >> resp;
		}

		//INICIAR JUEGO
		if(jugar)
			quienEsQuien.iniciar_juego();

		cout << "¿Quieres volver a jugar? (responde no, para salir)" << endl;
		cin >> reiniciar;
		
		//REINICIAR JUEGO
		if(!(reiniciar == "no" || reiniciar == "No" || reiniciar == "NO"|| reiniciar == "nO" )){
			do{
			cout << "¿Como quieres construir el arbol? (basica o mejora): ";
			cin >> mi_respuesta;
			cout << endl;

			}while(mi_respuesta != "mejora" && mi_respuesta != "basica");

			if(mi_respuesta == "mejora")
				quienEsQuien.usar_arbol(quienEsQuien.crear_arbol(1));
			if(mi_respuesta == "basica")
				quienEsQuien.usar_arbol(quienEsQuien.crear_arbol(0));
		}

	}while(!(reiniciar == "no" || reiniciar == "No" || reiniciar == "NO"|| reiniciar == "nO" ));

	return 0;
}
