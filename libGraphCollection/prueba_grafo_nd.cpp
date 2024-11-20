/**
* @file
* @brief Implementacion de las pruebas de grafos no dirigidos
* @author Erwin Meza Vega <emezav@unicauca.edu.co>
* @copyright MIT License
*/

#include <iostream>
#include <string>

#include "grafo.h"
#include "prueba_grafo_nd.h"

using std::cerr;
using std::cout;
using std::endl;

using std::string;

using grafo::denso;
using grafo::disperso;

void prueba_nd_sin_peso() {
  
  cout << "Grafos no dirigidos sin peso mediante matriz de adyacencia" << endl;
  
  denso<string, int> g;
  // Crear los nodos
  g.agregar_nodo("a");
  g.agregar_nodo("b");
  g.agregar_nodo("c");
  g.agregar_nodo("d");
  g.agregar_nodo("e");
  
  // Crear los arcos
  g.conectar("a", "b", 1);
  g.conectar("a", "c", 1);
  g.conectar("a", "d", 1);
  g.conectar("b", "d", 1);
  g.conectar("b", "e", 1);
  g.conectar("c", "d", 1);
  g.conectar("d", "e", 1);
  g.conectar("e", "e", 1);
  
  cout << g ;
  
  size_t expected = 5;
  cout << "Cantidad de nodos: " << g.conteo() << endl;
  if (g.conteo() != expected) {
    cerr << "FALLO: la cantidad " 
      << expected <<  " es diferente a " 
      << g.conteo() << endl;
  }else {
    cerr << "OK: El grafo contiene " 
      << expected <<  " datos"
      << endl;
  }
  
  string dato = "c";
  g.eliminar(dato);
  cout << "Despues de eliminar " << dato << " : " << g.conteo() << endl;
  cout << g ;
  
  if (g.existe(dato)) {
    cout << "FALLO: " << dato << " eliminado todavia existe!! "<< endl;
  }else {
    cout << "OK: " << dato << " eliminado correctamente "<< endl;
  }
  
  cout <<  "===========================" << endl;
}

void prueba_nd_con_peso() {
  cout << "Grafos no dirigidos con peso mediante lista de adyacencia" << endl;
  disperso<string, float> g;
  // Crear los nodos
  g.agregar_nodo("a");
  g.agregar_nodo("b");
  g.agregar_nodo("c");
  g.agregar_nodo("d");
  g.agregar_nodo("e");
  
  // Crear los arcos
  g.conectar("a", "b", 2.3f);
  g.conectar("a", "c", 3.1f);
  g.conectar("a", "d", 5.7f);
  g.conectar("b", "d", 7.2f);
  g.conectar("b", "e", 8.9f);
  g.conectar("c", "d", 9.1f);
  g.conectar("d", "e", 4.4f);
  g.conectar("e", "e", 2.3f);
  
  cout << g ;
  
  size_t expected = 5;
  cout << "Cantidad de nodos: " << g.conteo() << endl;
  if (g.conteo() != expected) {
    cerr << "FALLO: la cantidad " 
      << expected <<  " es diferente a " 
      << g.conteo() << endl;
  }else {
    cerr << "OK: El grafo contiene " 
      << expected <<  " datos"
      << endl;
  }
  
  string dato = "a";
  g.eliminar(dato);
  cout << "Despues de eliminar " << dato << " : " << g.conteo() << endl;
  cout << g ;
  
  if (g.existe(dato)) {
    cout << "FALLO: " << dato << " eliminado todavia existe!! "<< endl;
  }else {
    cout << "OK: " << dato << " eliminado correctamente "<< endl;
  }
  
  cout <<  "===========================" << endl;
}
