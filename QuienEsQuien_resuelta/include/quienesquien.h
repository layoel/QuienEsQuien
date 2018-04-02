/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el �rbol de preguntas para jugar al �Qui�n es qui�n?.
 * 
 * @author Elvira Castillo Fernández (Grupo D3)
 * @author Alejandro Jerónimo Fuentes (Grupo B1)
 * 
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include <ctype.h>

#include "pregunta.h"
#include "bintree.h"

using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su �ndice en 
	  *        este vector corresponde con el �ndice de su 
	  *        descripci�n en el tablero.
	  */
	vector<string> personajes;

	/**
	  * @brief Almacena los atributos.  Su �ndice en este vector 
	  *        corresponde con el �ndice correspondiente de cada 
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para 
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada 
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;

	/**
	 * @brief Profundidad de un nodo
	 * @param n: nodo a calcular la profundidad
	 * @return Devuelve la profundidad del nodo
	 * */

	float profundidad_nodo(bintree<Pregunta>::node n);

	/**
	 * @brief Obtiene el camino desde la raiz hasta un nodo dado por argumento
	 * @param n: nodo fin de camino
	 * @return Devuelve un vector con el camino
	 * */

	vector<bool> camino (bintree<Pregunta>::node nodo);
	
	/**
	 * @brief Calcula la entropía del TOTAL de atributos
	 * */

	double entropia_total();
	
	/**
	 * @brief Calcula la entropía de un determinado atributo
	 * @param valor_si: Número de personajes que tienen el atributo
	 * @param valor_no: Número de personajes que no tienen el atributo
	 * 
	 * Devuelve la medida de incertidumbre al elegir un atributo para la 
	 * siguiente pregunta. Esta función sirve para posteriormente calcular 
	 * la ganancia de información
	 * 
	 * */

	double entropia_atributo(int valor_si, int valor_no);

	/**
	 * @brief Calcula la ganancia de un atributo a partir de la entropía de los valores posibles
	 * del atributo (0 ó 1)
	 * 
	 * @param general: Valor de la entropía del atributo 
	 * 
	 * La función devuelve la ganancia de un atributo. El atributo con mayor ganancia
	 * de información será el que se seleccione para la próxima preguta
	 * */

	double ganancia (double entropia_atributo);

	/**
	 * @brief Calcula el índice del mejor atributo 
	 * @param atr_quedan: Colección de atributos que quedan por elegir
	 * @return Devuelve el índice del mejor atributo que será la siguiente pregunta.
	 * */

	int mejor_atributo(vector<int> atr_quedan);

	/**
	 * @brief Construcción del árbol basado en el algoritmo ID3
	 * @param personajes: colección de personajes del juego 
	 * @param atributos: colección de atributos de los personajes
	 * @param nodo: Nodo a insertar
	 * @param nivel: Nivel actual del árbol
	 * @return Devuelve un nodo con el mejor atributo
	 * */

	void ID3(vector<int> mis_personajes, vector<int> mis_atributos, bintree<Pregunta>::node n, int atributo_mejor);

public:
	/**
	  * @brief Constructor b�sico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	* @brief Destructor del pregunta.
	*/
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignaci�n.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de extracci�n de flujo.
	* @param is Stream de entrada
	* @param quienEsQuien Quien es quien a leer.
	* @return Referencia al stream de entrada.
	* Lee de @e is un quien es quien y lo almacena en @e 
	* quienEsQuien. El formato aceptado para la lectura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La �ltima columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada l�nea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la �ltima columna se da el 
	* nombre del personaje.
	*/
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de inserci�n de flujo.
	* @param os Stream de salida
	* @param quienEsQuien Quien es quien a escribir.
	* @return Referencia al stream de salida.
	* 
	* Escribe en @e is un quien es quien.
	* El formato usado para la escritura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La �ltima columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada l�nea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la �ltima columna se da el 
	* nombre del personaje.
	*/
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este m�todo construye el �rbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol(bool mejora);
	
	/**
	  * @brief Sustituye el �rbol actual por el �rbol pasado por par�metro.
	  * 
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  * 
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	   @brief M�todo que modifica el �rbol de preguntas para que haya
	          preguntas redundantes.
	   @post El �rbol de preguntas se modifica.
	*/
	void eliminar_nodos_redundantes();

	/**
	 * @brief Inicializa el juego.
	 * @post  Si la partida anterior no hab�a terminado se 
	 *        pierde el progreso.
	 */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de 
	  *        los personajes que a�n no han sido tumbados en el 
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  * 
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  * 
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);
	
	/**
	  * @brief Este m�todo permite calcular la media de la profundidad de las hojas del �rbol. Este valor representa el n�mero (promedio) de preguntas necesarias para adivinar cada personaje. A menor profundidad promedio, mejor soluci�n. Esta m�trica es un indicador para evaluar la calidad de vuestra soluci�n.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas(); 

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  * 
	  * @param numero_de_personajes N�mero de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

	/**
	 * @brief Crea una nueva rama del arbol recursivamente teniendo en cuenta los personajes
	 * que quedan
	 * 
	 * @param descartes: vector de personajes que aún quedan en el tablero
	 * @param n: nodo a insertar el hijo_izda o hijo_dcha
	 * @param nivel: nivel actual del árbol
	 * 
	 * */

	void construccion_basica(vector<int> descartes, bintree<Pregunta>::node n, int nivel);

	/**
	 * @brief Obtiene una descripción de las preguntas formuladas anteriormente
	 * y las respuestas dadas por el usuario hasta ahora.
	 * 
	 * @param jugada: jugada actual desde la que se obtienen las preguntas hasta ahora
	 * */

	void preguntas_formuladas ( bintree<Pregunta>::node jugada);


	/**
	 * @brief Insertar personaje en el arbol sin rehacerlo
	 * @param nombre:  Nombre del personaje
	 * @param caracteristicas: Atributos del personaje
	 * */

	void aniade_personaje(string nombre, vector<bool> caracteristicas);

	/**
	 * @brief Borrar personaje en el arbol sin rehacerlo
	 * @param nombre:  Nombre del personaje
	 * */

	void elimina_personaje(string nombre);

	int num_atributos();

};

#endif

