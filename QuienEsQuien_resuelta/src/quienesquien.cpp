#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <ctype.h>
#include <algorithm>

QuienEsQuien::QuienEsQuien(){
	//TODO :)
}
QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	//TODO :)
	personajes = quienEsQuien.personajes;
	atributos = quienEsQuien.atributos;
	tablero = quienEsQuien.tablero;
	arbol = quienEsQuien.arbol;
	jugada_actual = quienEsQuien.jugada_actual;
}
QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	//TODO :)
	if (this != &quienEsQuien)
		this->personajes = quienEsQuien.personajes;
		this->atributos = quienEsQuien.atributos;
		this->tablero = quienEsQuien.tablero;
		this->arbol = quienEsQuien.arbol;
		this->jugada_actual = quienEsQuien.jugada_actual;
	return *this;
}
QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	//TODO :)
  personajes.erase (personajes.begin(),personajes.end());
  atributos.erase (atributos.begin(),atributos.end());
  tablero.clear();

  arbol.clear();
  jugada_actual = bintree<Pregunta>::node();

}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  * 
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();
	
  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");
    	
    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}
	
    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;
	    	
	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));
	    		
	    		assert(valor == "0" || valor == "1");
	    		
	    		bool valor_atributo = valor == "1";
	    		
	    		atributos_personaje.push_back(valor_atributo);
				
	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}
			
			string nombre_personaje = linea;
	    	
	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}
  	
	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada l�nea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un n�mero a un vector de bool que corresponde 
  *        con su representaci�n en binario con un numero de digitos
  *        fijo.
  *
  * @param n N�mero a convertir en binario.
  * @param digitos N�mero de d�gitos de la representaci�n binaria.
  *
  * @return Vector de booleanos con la representaci�n en binario de @e n 
  *      con el n�mero de elementos especificado por @e digitos. 

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;  
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

void QuienEsQuien::construccion_basica(vector<int> descartes, bintree<Pregunta>::node n, int nivel)
{
	vector<int> descartes_izda;
	vector<int> descartes_dcha;

	// RAMA IZQUIERDA

	for(unsigned int i = 0; i < descartes.size(); i++){
		if(tablero[descartes[i]][nivel] == 1)
			descartes_izda.push_back(descartes[i]);
	}
	
	
	if(descartes_izda.size() == 0){

	}
	else if(descartes_izda.size() == 1){
		Pregunta p1(personajes[descartes_izda[0]],descartes_izda.size());
		arbol.insert_left(n,p1);
	}
	else if(descartes_izda.size() > 1){

		Pregunta p1(atributos[nivel+1],descartes_izda.size());
		arbol.insert_left(n,p1);
		construccion_basica(descartes_izda,n.left(),nivel+1);
	}

	// RAMA DERECHA

	for(unsigned int i = 0; i < descartes.size(); i++){
		if(tablero[descartes[i]][nivel] == 0)
			descartes_dcha.push_back(descartes[i]);
	}
	
	
	if(descartes_dcha.size() == 0){

	}
	else if(descartes_dcha.size() == 1){
		Pregunta p1(personajes[descartes_dcha[0]],descartes_dcha.size());
		arbol.insert_right(n,p1);
	}
	else if(descartes_dcha.size() > 1){

		Pregunta p1(atributos[nivel+1],descartes_dcha.size());
		arbol.insert_right(n,p1);
		construccion_basica(descartes_dcha,n.right(),nivel+1);
	}


}
bintree<Pregunta> QuienEsQuien::crear_arbol(bool mejora)
{	

	vector<int> descartes;
	for(unsigned int i = 0; i < personajes.size(); i++)
			descartes.push_back(i);


	if(mejora){

		vector<int> atrib;
		
		for(unsigned int i = 0; i < atributos.size(); i++)
			atrib.push_back(i);

		int indice = mejor_atributo(atrib);
		

		// Borramos el atributo de la raiz que será la primera pregunta
		atrib.erase(atrib.begin()+indice);

		Pregunta pregunta(atributos[indice],personajes.size());
		bintree<Pregunta> arbol(pregunta);
		ID3(descartes,atrib,arbol.root(),indice);


		return arbol;

	}
	else{

		Pregunta p(atributos[0],personajes.size());
		bintree<Pregunta> arbol(p);
		construccion_basica(descartes,arbol.root(),0);

		return arbol;

	}
}


void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
		
		//aqui empieza el juego!!!
		
		jugada_actual = arbol.root();
		string respuesta;
		set<string>::iterator it;
		set<string> personajes_levantados(informacion_jugada(jugada_actual));
		vector<string> preguntas;

		int num_preguntas =0;

		cout << "*********PREGUNTAS HASTA AHORA*********" << endl;
		preguntas_formuladas(jugada_actual);
		cout << "***************************************" << endl << endl;

		cout<<"Los personajes que hay en el tablero son: ";

		for(it = personajes_levantados.begin(); it != personajes_levantados.end(); ++it)
			cout<< *it << " ";
		cout << endl << endl;

		while((*jugada_actual).obtener_num_personajes() != 1){

			do{	
				cout << "¿Es " << (*jugada_actual).obtener_pregunta() <<" ? "<< endl;
				cin >> respuesta;
				cout << endl;

				if(respuesta == "si" || respuesta == "Si" || respuesta == "SI"|| respuesta == "sI" ){
					jugada_actual= jugada_actual.left();
					num_preguntas++;
				}
				else if(respuesta == "no" || respuesta == "No" || respuesta == "NO"|| respuesta == "nO" ){
					jugada_actual= jugada_actual.right();
					num_preguntas++;
				}
				

			}while( !(respuesta == "si" || respuesta == "Si" || respuesta == "SI"|| 
				    respuesta == "sI" ||respuesta == "no" || respuesta == "No" || 
				    respuesta == "NO"|| respuesta == "nO" ));


			personajes_levantados = informacion_jugada(jugada_actual);

			cout << "*********PREGUNTAS HASTA AHORA*********" << endl;
			preguntas_formuladas(jugada_actual);
			cout << "***************************************" << endl << endl;

			cout<<"Los personajes que quedan en el tablero son: ";

			for(it = personajes_levantados.begin(); it != personajes_levantados.end(); ++it)
				cout<< *it << " ";
			cout << endl << endl;

		}

		cout<<"¡Ya lo se! tu personaje es: ¡" << (*jugada_actual).obtener_personaje() <<"!"<< endl;
		cout<< "Has hecho: "<<num_preguntas <<" preguntas."<<endl;

}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	
	set<string> personajes_levantados;
	vector<bool> cam = camino(jugada_actual);
	bool iguales = true;


	for(unsigned int i = 0; i < tablero.size(); i++){
		iguales = true;
		for(unsigned int j = 0; j < cam.size() && iguales; j++){
			if(tablero[i][j] != cam[j])
				iguales = false;
		}

		if(iguales)
			personajes_levantados.insert(personajes[i]);

	}

	return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a, 
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);    
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
	
	bintree<Pregunta>::level_iterator it;
	bintree<Pregunta> aux;
	int num_nodos_red = 0;
	//calculo el numero de nodos redundantes
	for(it=arbol.begin_level(); it!=arbol.end_level(); ++it)
	{
		if((*it).left().null() && !(*it).right().null())
			num_nodos_red++;
		if((*it).right().null() && !(*it).left().null())
			num_nodos_red++;
	}

	//elimino los redundantes
	for(it=arbol.begin_level(); it!=arbol.end_level(); ++it){
		if((*it).left().null() && !(*it).right().null()){
			
			arbol.prune_right((*it),aux);

			if((*it).parent().left() == (*it))
				arbol.insert_left((*it).parent(),aux);
			else
				arbol.insert_right((*it).parent(),aux);
			num_nodos_red--;
		}
		if((*it).right().null() && !(*it).left().null()){
			
			arbol.prune_left((*it),aux);
			
			if((*it).parent().left() == (*it))
				arbol.insert_left((*it).parent(),aux);
			else
				arbol.insert_right((*it).parent(),aux);
			num_nodos_red--;
		}
	}
	//si queda algun nodo aún, vuelvo a borrar redundantes
	if(num_nodos_red>0)
		eliminar_nodos_redundantes();

}

float QuienEsQuien::profundidad_promedio_hojas(){
	
	bintree<Pregunta>::level_iterator it;
	float suma = 0;
	float num_hojas = 0;

	for(it = arbol.begin_level(); it != arbol.end_level(); ++it){
		if((*it).left().null() && (*it).right().null()){
			suma = suma + profundidad_nodo(*it);
			num_hojas++;
		}
	}

	return suma/num_hojas;
}


float QuienEsQuien::profundidad_nodo(bintree<Pregunta>::node n){

	bintree<Pregunta>::node aux = n;
	float profundidad = 0;

	while(!aux.parent().null()){

		aux = aux.parent();
		profundidad++;
		
	}

	return profundidad;
}

void QuienEsQuien::preguntas_formuladas ( bintree<Pregunta>::node jugada){

	vector<bool> cam = camino(jugada);
	vector<bool>::const_iterator it;
	bintree<Pregunta>::node aux = arbol.root();

	for(it = cam.cbegin(); it != cam.cend(); ++it){

		cout << (*aux).obtener_pregunta() << ": ";

		if(*it == 0){
			cout << "No" << endl;
			aux = aux.right();
		}
		else{
			cout << "Si" << endl;
			aux = aux.left();
		}

	}
}


vector<bool> QuienEsQuien::camino (bintree<Pregunta>::node nodo){

	bintree<Pregunta>::node nodo_camino;
	vector<bool> camino;

	nodo_camino = nodo;

    while(!nodo_camino.parent().null()){
    
		if(nodo_camino.parent().left() == nodo_camino) // Entonces se cumple el atributo
		camino.push_back(1);
		if(nodo_camino.parent().right() == nodo_camino) // No cumple el camino
		camino.push_back(0);

		nodo_camino = nodo_camino.parent(); // Vamos al nodo padre

    }

    // Invertimos vector
    reverse(camino.begin(),camino.end());

	return camino;

}


void QuienEsQuien::aniade_personaje(string nombre, vector<bool> caracteristicas){

// Primero insertamos el personaje en los vectores
	personajes.push_back(nombre);
	tablero.push_back(caracteristicas);

	vector<bool>::const_iterator it;
	bintree<Pregunta>::node nodo = arbol.root();
	bintree<Pregunta> aux;
	bool insertado = false;

	
	
	//actualizo el numero de personajes de los nodos por los que voy pasando.
	(*arbol.root()).set_num_personajes((*arbol.root()).obtener_num_personajes()+1);
	//cout<<"la raiz es"<<(*nodo)<<endl;
	
	//busco el camino que coincide con las características de mi personaje para ver donde insertarlo
	for(it = caracteristicas.cbegin(); it != caracteristicas.end() && !insertado; ++it){

		if(*it == 0)
			if (!nodo.right().null()){	
				nodo = nodo.right();
				if((*nodo).obtener_num_personajes() !=1)
					(*nodo).set_num_personajes((*nodo).obtener_num_personajes()+1);
			}
		if(*it == 1)
			if (!nodo.left().null()){
				nodo = nodo.left();
				if((*nodo).obtener_num_personajes() !=1)
					(*nodo).set_num_personajes((*nodo).obtener_num_personajes()+1);
			}
		if(nodo.right().null() && nodo.left().null())
			insertado =true;
		//cout<<"¿esta ya insertado?"<<insertado<<endl;
	}
	if(!insertado){
		if((*nodo).obtener_num_personajes() == 1){ // Si es una hoja

			vector<bool> cam = camino(nodo);
			bintree<Pregunta>::node papa;
			bool rama;
			int pos = -1;

			papa = nodo.parent();

			if(nodo.parent().left() ==  nodo){ // Es hijo a la izquierda
				//cout<<(*nodo.parent().left())<<"hoja hasta aqui funciona hijo izda"<<endl;
				arbol.prune_left(nodo.parent(),aux);
				rama = 1;
			}
			if(nodo.parent().right() == nodo){
				//cout<<(*nodo.parent().right())<<"hoja hasta aqui funciona hijo dcha"<<endl;
				arbol.prune_right(nodo.parent(),aux);
				rama = 0;
			}

			int pos_personaje=-1;
			int pos_atri=-1;
			bool encontrado =false;

			//busco la posicion del personaje en el vector de personajes
			for(int i=0; i<personajes.size() && !encontrado; i++){
				//cout<<"pos"<<pos_personaje<<endl;
				if(personajes[i]==(*aux.root()).obtener_personaje()){
					pos_personaje = i;
					encontrado = true;
					//cout<<"pos"<<personajes[i]<<"=="<<(*aux.root()).obtener_personaje()<<endl;
				}

			}
			//cout<<"pos"<<pos_personaje<<endl;

			//busco la posicion del atributo en que difiere con el personaje que hemos cortado, para insertar esa pregunta			
			if(pos_personaje != -1){
				for(int i=0; i<atributos.size(); i++){
					if(tablero[i][pos_personaje] !=caracteristicas[i])
						pos_atri=i;
				}
				//cout<<"pos"<<pos_atri<<endl;

				if(pos_atri != -1){
					Pregunta p(atributos[pos_atri],2);
					bintree<Pregunta> modificado(p);

					//creo el subarbol con la pregunta nueva y los dos personajes
					if(tablero[pos_atri][pos_personaje] == 0){
						modificado.insert_right(modificado.root(),aux);
						Pregunta personaje(nombre,1);
						modificado.insert_left(modificado.root(),personaje);
					}
					if(tablero[pos_atri][pos_personaje]== 1){
						modificado.insert_left(modificado.root(),aux);
						Pregunta personaje(nombre,1);
						modificado.insert_right(modificado.root(),personaje);
					}

					//inserto en el arbol el subarbol anterior
					if(rama)
						arbol.insert_left(papa,modificado);
					else
						arbol.insert_right(papa,modificado);
				}
			}
		}
	}
	else{
		cout<<"ESE PERSONAJE YA EXISTE!!"<<endl;
	}
}


void QuienEsQuien::elimina_personaje(string nombre){
	
	bintree<Pregunta> aux;
	bintree<Pregunta>::node nodo = arbol.root();
	bintree<Pregunta>::node nodo_aux;
	bintree<Pregunta>::level_iterator it;
	vector<bool>::const_iterator it1;
	vector<bool> cam;
	bool encontrado = false;
	int pos = -1;

	for(unsigned int i = 0; i < personajes.size(); i++)
		if(personajes[i] == nombre)
			pos = i;


	if(pos!=-1){
		for(it = arbol.begin_level(); it != arbol.end_level() && !encontrado; ++it){
			if((**it).obtener_num_personajes() == 1 && (**it).obtener_personaje() == nombre){
				cam = camino(*it);
				encontrado = true;
			}
		}

		(*nodo).set_num_personajes((*nodo).obtener_num_personajes()-1);

		for(it1 = cam.cbegin(); it1 != cam.cend(); ++it1){
			if(*it1 == 0){
				nodo = nodo.right();
				if((*nodo).obtener_num_personajes() !=1)
						(*nodo).set_num_personajes((*nodo).obtener_num_personajes()-1);
			}
			else{
				nodo = nodo.left();
				if((*nodo).obtener_num_personajes() !=1)
						(*nodo).set_num_personajes((*nodo).obtener_num_personajes()-1);
			}
		}

		if((*nodo).obtener_personaje() == nombre)
			if(nodo.parent().left() == nodo)
				arbol.prune_left(nodo.parent(),aux);
			else
				arbol.prune_right(nodo.parent(),aux);

				
		eliminar_nodos_redundantes();

		// Ahora se elimina el personaje del tablero y del vector
		personajes.erase(personajes.begin()+pos);
		tablero.erase(tablero.begin()+pos);
	}
}



/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petici�n para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}

int QuienEsQuien::num_atributos(){
	return atributos.size();
}

// Aplicamos la fórmula de entropía de la Teoria de la información

double QuienEsQuien::entropia_atributo(int valor_si, int valor_no){


	int total = valor_si + valor_no; // Suma de cuantos personajes han dicho si y cuantos no

	// Ahora se calcula las probabilidades de que los posibles valores del atributo sean 0 o 1

	double probabilidad_si = (double) valor_si / total;
	double probabilidad_no = (double) valor_no / total;

	double entropia_si, entropia_no, entropia_total;
	entropia_si = entropia_no = entropia_total = 0;

	// La entropía de un atributo tiene que ser 0 si no lo es el nodo es hoja

	if(probabilidad_si != 0 && probabilidad_no != 0){
		entropia_si = - probabilidad_si * log2(probabilidad_si);
		entropia_no = - probabilidad_no * log2(probabilidad_no);
		entropia_total = entropia_si + entropia_no;
	}

	return entropia_total;

}


double QuienEsQuien::ganancia(double entropia_atributo){
	
	double ganancia = entropia_total()-entropia_atributo;
	return ganancia;
}

double QuienEsQuien::entropia_total(){

	double entropia;
	double n_ejemplos = (double) personajes.size();
	entropia = - n_ejemplos * (1/n_ejemplos) * log2(1/n_ejemplos);
	return entropia;
}


int QuienEsQuien::mejor_atributo(vector<int> atr_quedan){

	int si,no;
	double max_ganancia = 0;
	double ganancia_atributo = 0;
	int indice;
	

	for(auto it = atr_quedan.begin(); it != atr_quedan.cend(); ++it){

		si = no = 0;

		for(unsigned int columna = 0; columna < tablero.size(); columna++)
			if(tablero[*it][columna] == 1)
				si++;
			else
				no++;

		ganancia_atributo = ganancia(entropia_atributo(si,no));
		
		if(ganancia_atributo > max_ganancia){

			max_ganancia = ganancia_atributo;
			indice = *it;

		}

	}

	return indice;

}


void QuienEsQuien::ID3(vector<int> mis_personajes, vector<int> mis_atributos, bintree<Pregunta>::node nodo, int atributo_mejor){


		vector<int> descartes_izda;
		vector<int> descartes_dcha;
		vector<int> atr;
		int mejor = mejor_atributo(mis_atributos);


		for(unsigned int i = 0; i < mis_atributos.size(); i++)
			if(mis_atributos[i] != mejor)
				atr.push_back(mis_atributos[i]);

	
		for(unsigned int i = 0; i < mis_personajes.size(); i++){
			if(tablero[mis_personajes[i]][atributo_mejor] == 1)
				descartes_izda.push_back(mis_personajes[i]);
		}

		for(unsigned int i = 0; i < mis_personajes.size(); i++){
			if(tablero[mis_personajes[i]][atributo_mejor] == 0)
				descartes_dcha.push_back(mis_personajes[i]);
		}
		
		if(descartes_izda.size() == 0){


		}
		
		if(descartes_izda.size() == 1){ // Nodo hoja
			
			Pregunta personaje(personajes[descartes_izda[0]],1);
			arbol.insert_left(nodo,personaje);

		}
		
		if(descartes_izda.size() > 1){ // Seguimos preguntando
			Pregunta p(atributos[mejor],descartes_izda.size());
			arbol.insert_left(nodo,p);
			ID3(descartes_izda,atr,nodo.left(),mejor);
			
		}


		if(descartes_dcha.size() == 0){


		}
		
		if(descartes_dcha.size() == 1){ // Nodo hoja
			
			Pregunta personaje(personajes[descartes_dcha[0]],1);
			arbol.insert_right(nodo,personaje);

		}
		
		if(descartes_dcha.size() > 1){ // Seguimos preguntando
			Pregunta p(atributos[mejor],descartes_dcha.size());
			arbol.insert_right(nodo,p);
			ID3(descartes_dcha,atr,nodo.right(),mejor);
			
		}

		
}