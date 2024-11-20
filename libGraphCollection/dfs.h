/**
* @file
* @brief Busqueda por Profundidad - BFS
* @author Erwin Meza Vega <emezav@unicauca.edu.co>
* @copyright MIT License
*/

#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <list>

#include "grafo.h"

using std::cout;
using std::endl;
using std::list;
using grafo::denso;

/**
* @brief Recorrido en profundidad
* @param g Gafo
* @param inicio Nodo inicial del recorrido
*/
template <class T, class TP>
void dfs(denso<T, TP>&g, T inicio) {
  if ( g.llave(inicio) == g.no_existe()) {
    return;
  }
  
  vector<bool> visitado(g.conteo());
  
  // Lista de nodos por visitar
  list<T> l;
  
  l.push_back(inicio);
  
  cout << "Inicio en " << inicio << endl; 
  
  while (!l.empty()) {
    
    // Obtener el valor en el inicio de la lista
    T dato =  l.front();
    // Quita el valor en el inicio de la lista
    l.pop_front();
    
    // Obtener la llave 
    auto k = g.llave(dato);
    // Marcar este nodo como visitado
    visitado[k] = true;
    
    // Mostrar el dato
    cout << "visitado " << dato << endl;
    
    // Adicionar los vecinos no visitados a la lista de vecinos
    vector<T> vecinos = g.vecinos(dato);
    
    list<T> l_vecinos;
    
    for (auto & n: vecinos) {
      cout <<  " vecino de " << dato << ": " << n << endl;
      if (visitado[g.llave(n)] == false) {
        visitado[g.llave(n)] = true;
        l_vecinos.push_back(n);
      }
    }
    // Insertar la lista de vecinos al inicio de la lista por visitar
    std::copy(l.begin(), l.end(), std::back_inserter(l_vecinos));   
    l = l_vecinos;
  }
}






#endif
