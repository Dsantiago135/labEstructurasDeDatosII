/**
* @file
* @brief Implementacion de la prueba de recorridos DFS y BFS
* @author Erwin Meza Vega <emezav@unicauca.edu.co>
*/

#include <iostream>
#include <list> // Lista
#include <queue> // Cola
#include <stack> // Pila
#include <string>

#include "bfs.h"
#include "dfs.h"
#include "grafo.h"
#include "prueba_recorridos.h"

using std::cout;
using std::endl;
using std::list;
using std::stack;
using std::queue;
using std::string;

using grafo::denso;
using grafo::disperso;


namespace prueba_recorridos {

/**
* @brief Crea el grafo dirigido ED2__Tema_4__GRAFOS__03_Recorridos 1.
* @return Grafo no dirigido sin peso
*/

denso<string, int> crear_grafo_1();


void prueba_dfs_1() {
  cout << "Recorrido en profundidad, grafo no dirigido sin peso" << endl;
  denso<string, int> g = crear_grafo_1();
  
  cout << g;
  //cout << g.peso("a", "b") << endl;
  //cout << g.conectado("a", "b") << endl;
  //cout << g.conectado("a", "d") << endl;
  
  // Realizar el recorrido en profunidad desde un nodo
  string inicio =  "e";
  dfs(g, inicio);
  
}

void prueba_bfs_1() {
  cout << "Recorrido en amplitud, grafo no dirigido sin peso" << endl;
  denso<string, int> g = crear_grafo_1();
  
  cout << g;
  //cout << g.peso("a", "b") << endl;
  //cout << g.conectado("a", "b") << endl;
  //cout << g.conectado("a", "d") << endl;
  
  // Realizar el recorrido en profunidad desde un nodo
  string inicio =  "e";
  bfs<string, int>(g, inicio);
  
}

denso<string, int> crear_grafo_1() {
  denso<string, int> g;
  
  g.agregar_nodo("a");
  g.agregar_nodo("b");
  g.agregar_nodo("c");
  g.agregar_nodo("d");
  g.agregar_nodo("e");
  
  g.conectar("a", "d", 1);
  g.conectar("a", "e", 1);
  g.conectar("b", "c", 1);
  g.conectar("b", "e", 1);
  g.conectar("c", "d", 1);
  
  return g;
}





}
