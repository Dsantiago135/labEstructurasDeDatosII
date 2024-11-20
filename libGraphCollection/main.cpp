/**
* @file
* @brief Grafos
* @author Erwin Meza Vega <emezav@unicauca.edu.co>
* @copyright MIT License
*/

#include "prueba_grafo_nd.h"
#include "prueba_recorridos.h"
#include "prueba_recubridor_minimo.h"
#include "prueba_costo_minimo.h"

int main (int argc, char *argv[]) {
	
  // 1. Grafo no dirigido sin peso
  prueba_nd_sin_peso();
  
  // 2. Grafo no dirigido con peso
  prueba_nd_con_peso();
  
  // 3. Prueba de recorrido DFS no dirigido sin peso
  prueba_recorridos::prueba_dfs_1();

  // 4. Prueba de recorrido BFS no dirigido sin peso
  prueba_recorridos::prueba_bfs_1();
  
  // 5. Prueba de arbol recubridor mínimo - Algoritmo de Prim
  //prueba_recubridor_minimo::prueba_prim_1();
  
  
  // 6. Prueba de arbol recubridor mínimo - Algoritmo de Kruskal
  //prueba_recubridor_minimo::prueba_kruskal_1();
  
  // 7. Prueba de arbol de costo mínimo - Algoritmo de Dijkstra
  //prueba_costo_minimo::prueba_dijkstra_1();
  
	return 0;
}

