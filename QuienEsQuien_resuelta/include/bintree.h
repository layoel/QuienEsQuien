#ifndef __BINTREE_H__
#define __BINTREE_H__

/**
   TDA bintree.

   Representa un �rbol binario con nodos etiquetados con datos del tipo T.

   T debe tener definidas las operaciones:

   - T & operator=(const T & e);
   - bool operator!=(const T & e);
   - bool opertaor==(const T & e);

   Son mutables.
   Residen en memoria din�mica.
   
   Un ejemplo de su uso:
   @include usobintree.cpp
   @author{Miguel Garcia Silvente}
   @author{Juan F. Huete Guadix}
*/

#include <queue>
#include <sstream>


template <typename T>
class bintree {
public:
  class node;

  typedef unsigned int size_type;
  
  /**
     @brief Constructor primitivo por defecto.
     
     Crea un �rbol nulo.
  */
  bintree();

  /**
     @brief Constructor primitivo.
     
     @param e Etiqueta para la ra�z.
     
     Crea un �rbol con un �nico nodo etiquetado con e.
  */
  bintree(const T & e);

  /**
     @brief Constructor de copia.
     
     @param a �rbol que se copia.
     
     Crea un �rbol duplicado exacto de a.
  */
  bintree (const bintree<T> & a);

  /**
     @brief Reemplaza el receptor por una copia de sub�rbol.

     @param a Arbol desde el que se copia.
     @param n nodo ra�z del sub�rbol que se copia.

     El receptor se hace nulo y despu�s se le asigna una copia
     del sub�rbol de a cuya ra�z es n.
  */
  void assign_subtree(const bintree<T> & a, node n);

  /**
     @brief Destructor.

     Destruye el receptor liberando los recursos que ocupaba.
  */
  ~bintree();

  /**
     @brief Operador de asignaci�n.
     
     @param a: �rbol que se asigna.
     
     Destruye el contenido previo del receptor y le asigna un
     duplicado de a.
  */
  bintree<T> & operator=(const bintree<T> & a);

  /**
     @brief Obtener el nodo ra�z.
     
     @return nodo ra�z del receptor.
  */
  node root() const;
  
  /**
     @brief Podar el sub�rbol a la izquierda de un nodo.

     @param n: nodo del receptor. !n.null().
     @param dest: sub�rbol a la izquierda de n. Es MODIFICADO.

     Desconecta el sub�rbol a la izquierda de n, que pasa a
     ser un �rbol nulo. El sub�rbol anterior se devuelve sobre
     dest.
  */
  void prune_left(node n, bintree<T> & dest);

  /**
     @brief Podar el sub�rbol a la derecha de un nodo.

     @param n: nodo del receptor. !n.null().
     @param dest: sub�rbol a la derecha de n. Es MODIFICADO.

     Desconecta el sub�rbol a la derecha de n, que pasa a
     ser un �rbol nulo. El sub�rbol anterior se devuelve sobre
     dest.
  */
  void prune_right(node n, bintree<T> & dest);

  /**
     @brief Insertar un nodo como hijo a la izquierda de un nodo.
     
     @param n: nodo del receptor. !n.null().
     @param e: etiqueta del nuevo nodo.
     
     Desconecta y destruye el sub�rbol a la izquierda de n, inserta
     un nuevo nodo con etiqueta e como hijo a la izquierda
  */
  void insert_left(const bintree<T>::node & n, const T & e);

  /**
     @brief Insertar un �rbol como sub�rbol a la izquierda de un nodo.

     @param n: nodo del receptor. n != nodo_nulo.
     @param rama: sub�rbol que se inserta. Es MODIFICADO.

     Desconecta y destruye el sub�rbol a la izquierda de n, le
     asigna el valor de rama como nuevo sub�rbol a la izquierda
     y rama se hace �rbol nulo.
  */
  void insert_left(node n, bintree<T> & rama);

  /**
     @brief Insertar un nodo como hijo a la derecha de un nodo.

     @param n: nodo del receptor. !n.Nulo().
     @param e: etiqueta del nuevo nodo.

     Desconecta y destruye el sub�rbol a la derecha de n, inserta
     un nuevo nodo con etiqueta e como hijo a la derecha
  */
  void insert_right(node n, const T & e);

  /**
     @brief Insertar un �rbol como sub�rbol a la derecha de un nodo.

     @param n: nodo del receptor. !n.Nulo().
     @param rama: sub�rbol que se inserta. Es MODIFICADO.

     Desconecta y destruye el sub�rbol a la izquierda de n, le
     asigna el valor de rama como nuevo sub�rbol a la derecha
     y rama se hace �rbol nulo.
  */
  void insert_right(node n, bintree<T> & rama);

  /**
     @brief Hace nulo un �rbol.

     Destruye todos los nodos del �rbol receptor y lo hace
     un �rbol nulo.
  */
  void clear();

  /**
     @brief Obtiene el n�mero de nodos.

     @return n�mero de nodos del receptor.
  */
  size_type size() const;

  /**
     @brief Comprueba si un �rbol est� vac�o (es nulo).

     @return true, si el receptor est� vac�o (es nulo).
             false, en otro caso.
  */
  bool empty() const;


  /**
     @brief Operador de comparaci�n de igualdad.

     @param a: �rbol con que se compara el receptor.
     
     @return  true, si el receptor es igual, en estructura y
                 etiquetas a a.
              false, en otro caso.
  */
  bool operator==(const bintree<T> & a) const;

  /**
     @brief Operador de comparaci�n de desigualdad.

     @param a: �rbol con que se compara el receptor.

     @return  true, si el receptor no es igual, en estructura o
                    etiquetas a a.
              false, en otro caso.
  */
  bool operator!=(const bintree<T> & a) const;
  
  
  /**
     @brief Reemplaza el sub�rbol a partir de pos por una copia de sub�rbol.

     @param pos nodo a partir del que se colagar� la copia
     @param a Arbol desde el que se copia.
     @param n nodo ra�z del sub�rbol que se copia.

     El receptor se modifica colocando a partir de pos una copia
     del sub�rbol de a cuya ra�z es n.
  */
  void replace_subtree(node pos, const bintree<T> &a, node n);
  
  /**
     Clase iterator para recorrer el �rbol en PreOrden
  */
  class preorder_iterator {
  public:
    preorder_iterator();
    preorder_iterator(const preorder_iterator & i);
    bool operator!=(const preorder_iterator & i) const;
    bool operator==(const preorder_iterator & i) const;
    preorder_iterator & operator=(const preorder_iterator & i);
    T & operator*();
    preorder_iterator & operator++();
  private:
    node elnodo;
    preorder_iterator(node n);
    friend class bintree<T>;
  };

  preorder_iterator begin_preorder();
  preorder_iterator end_preorder();

  class const_preorder_iterator
  {
  public:
    const_preorder_iterator();
    const_preorder_iterator(const const_preorder_iterator & i);
    const_preorder_iterator(const preorder_iterator & i);
    bool operator!=(const const_preorder_iterator & i) const;
    bool operator==(const const_preorder_iterator & i) const;
    const_preorder_iterator & operator=(const const_preorder_iterator & i);
    const T & operator*() const;
    const_preorder_iterator & operator++();
  private:
    node elnodo;
    const_preorder_iterator(node n);
    friend class bintree<T>;
 };

  const_preorder_iterator begin_preorder() const;
  const_preorder_iterator end_preorder() const;

  /**
     Clase iterator para recorrer el �rbol en Inorden
  */

 class inorder_iterator
 {
  public:
    inorder_iterator();
    inorder_iterator(const inorder_iterator & i);
    bool operator!=(const inorder_iterator & i) const;
    bool operator==(const inorder_iterator & i) const;
    inorder_iterator & operator=(const inorder_iterator & i);
    T & operator*();
    inorder_iterator & operator++();
  private:
    node elnodo;
    inorder_iterator(node n);
    friend class bintree<T>;
 };

  inorder_iterator begin_inorder();
  inorder_iterator end_inorder();

class const_inorder_iterator
 {
  public:
    const_inorder_iterator();
    const_inorder_iterator(const const_inorder_iterator & i);
    bool operator!=(const const_inorder_iterator & i) const;
    bool operator==(const const_inorder_iterator & i) const;
    const_inorder_iterator & operator=(const const_inorder_iterator & i);
    const T & operator*() const;
    const_inorder_iterator & operator++();
  private:
    node elnodo;
    const_inorder_iterator(node n);
    friend class bintree<T>;
 };

  const_inorder_iterator begin_inorder() const;
  const_inorder_iterator end_inorder() const;


  /**
     Clase iterator para recorrer el �rbol en PostOrden
  */

 class postorder_iterator
 {
  public:
    postorder_iterator();
    postorder_iterator(const postorder_iterator & i);
    bool operator!=(const postorder_iterator & i) const;
    bool operator==(const postorder_iterator & i) const;
    postorder_iterator & operator=(const postorder_iterator & i);
    T & operator*();
    postorder_iterator & operator++();
  private:
    node elnodo;
    postorder_iterator(node n);
    friend class bintree<T>;
  };

  postorder_iterator begin_postorder();
  postorder_iterator end_postorder();

class const_postorder_iterator
 {
  public:
    const_postorder_iterator();
    bool operator!=(const const_postorder_iterator & i) const;
    bool operator==(const const_postorder_iterator & i) const;
    const T & operator*() const;
    const_postorder_iterator & operator=(const const_postorder_iterator & i);
    const_postorder_iterator & operator++();
  private:
    node elnodo;
    const_postorder_iterator(node n);
    friend class bintree<T>;
  };
  const_postorder_iterator begin_postorder() const;
  const_postorder_iterator end_postorder() const;


  /**
     Clase iterator para recorrer el �rbol por niveles
  */

 class level_iterator
 {
  public:
    level_iterator();
    level_iterator(const level_iterator & i);
    bool operator!=(const level_iterator & i) const;
    bool operator==(const level_iterator & i) const;
    level_iterator & operator=(const level_iterator & i);
    typename bintree<T>::node  & operator*();
    level_iterator & operator++();
  private:
    std::queue<node> cola_Nodos;
    level_iterator(node n);
    friend class bintree<T>;
  };

  level_iterator begin_level();
  level_iterator end_level();

class const_level_iterator
 {
  public:
    const_level_iterator();
    bool operator!=(const const_level_iterator & i) const;
    bool operator==(const const_level_iterator & i) const;
    const_level_iterator & operator=(const const_level_iterator & i);
    const T & operator*() const;
    const_level_iterator & operator++();
  private:
    std::queue<node> cola_Nodos;
    const_level_iterator(node n);
    friend class bintree<T>;
  };

  const_level_iterator begin_level() const;
  const_level_iterator end_level() const ;


private:

  // Funciones auxiliares
  /**
     @brief Destruir sub�rbol.

     @param n: nodo ra�z del sub�rbol que se destruye.
     @doc:
     Destruye el sub�rbol cuya ra�z es n.
  */
  void destroy(bintree<T>::node n);
  
  
  /**
     @brief Copia sub�rbol.

     @param dest: nodo sobre el que se copia. dest.null().
            Es MODIFICADO.
     @param orig: ra�z del sub�rbol que se copia.

     @doc
     Destruye el sub�rbol con ra�z en dest. Sobre �ste realiza
     un duplicado del sub�rbol con ra�z en orig.
  */
  void copy(node & dest, const node &orig);
  
  
  /**
     @brief Cuenta el n�mero de nodos.
    
     @param n: ra�z del sub�rbol a contar.

     @return devuelve el n�mero de nodos del sub�rbol que
             tiene n como ra�z.

     Cuenta el n�mero de nodos en el sub�rbol cuuya ra�z es n.
  */
  int count(node n) const;
    
  /**
     @brief Comparaci�n de igualdad.

     @param n1: raiz del primer sub�rbol.
     @param n2: raiz del segundo sub�rbol.

     @return true, si los dos sub�rboles son iguales, en
                   estructura y etiquetas.
             false, en otro caso.
  */
  bool equals(node n1, node n2) const;

  // Representaci�n
  node laraiz;
  size_type num_nodos;

  
  /** 
      TDA nodo.
      Modela los nodos del �rbol binario.
  */
  
  class nodewrapper {
  public:
    nodewrapper();
    nodewrapper(const T & e);

    T etiqueta;
    node pad;
    node izda;
    node dcha;
  };
  
public:

  class node {
  public:
    /**
       @brief Constructor primitivo
    */
    node();
      
    /**
       @brief Constructor primitivo
       @param e: Etiqueta del nodo
    */
    node(const T & e);

    /**
       @brief Constructor de copia
       @param n: Nodo que se copia
    */
    node(const node & n);
      
    /**
       @brief Determina si el nodo es nulo
    */
    bool null() const;
      
    /**
       @brief Devuelve el padre del nodo receptor
       @pre !null()
    */
    node parent() const;
      
    /**
       @brief Devuelve el hizo izquierdo del nodo receptor
       @pre !null()
    */
    node left() const;
      
    /**
       @brief Devuelve el hizo izquierdo del nodo receptor
       @pre !null()
    */
    node right() const;
      
    /**
       @brief Devuelve la etiqueta del nodo
       @pre Si se usa como consultor, !null()
    */
    T & operator*();
      
    /**
       @brief Devuelve la etiqueta del nodo
       @pre !null()
      */
    const T & operator*() const;
      
    /**
       @brief Elimina el nodo actual
       @pre !null()
    */
    void remove();
      
    /**
       @brief Operador de asignaci�n
       @param n: el nodo a asignar
    */
    node & operator=(const node & n);
      
    /**
       @brief Operador de comparaci�n de igualdad
       @param n: el nodo con el que se compara
    */
    bool operator==(const node & n) const;
      
    /**
       @brief Operador de comparaci�n de desigualdad
       @param n: el nodo con el que se compara
    */
    bool operator!=(const node & n) const;
      
  private:
    // Las siguientes funciones son privadas para uso exclusivo en bintree
    friend class bintree<T>;

    /**
       @brief Coloca el nodo padre de un nodo
       @param n El nodo que ser~ padre del receptor. No nulo.
    */
    inline void parent(node n);

    /**
       @brief Coloca el nodo hijo izquierda de un nodo
       @param n El nodo que ser~ hijo izquierdo del receptor. No nulo
    */
    inline void left(node n);
    
    /**
       @brief Coloca el nodo hijo derecho de un nodo
       @param n El nodo que ser~ hijo derecho del receptor No nulo
    */
    inline void right(node n);

    nodewrapper * elnodo;
  };
};

#include "bintree.hxx"
#include "node.hxx"


#endif



