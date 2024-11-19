#pragma once

#include <iostream>
#include <stack>
#include "prueba_recorridos.h"

using std::cout;
using std::endl;
using std::stack;
using std::string;

denso<string, int> crear_grafo_1();

void dfs (const denso<string, int> & g,string inicio);

void prueba_dfs_1() {
	cout<< "Recorrido en profundidas, grafo no dirigido sin peso" << endl;
	denso<string, int> g = crear_grafo_1();
	cout << g;

	//cout << g.peso("a", "b") << endl;
	//cout << g.conectado("a", "b") << endl;
	string inicio = "e";
	dfs(g,inicio);
}

denso<string, int> crear_grafo_1(){
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

void dfs(denso<string, int>& g, string inicio) {

	if (g.llave(inicio) == g.no_existe()) return;

	stack<string> stack;

	stack.push(inicio);

	cout << "Inicio en: " << inicio << endl;

	vector<bool> visitado(g.conteo());
	
	while (!stack.empty()) {
		string dato = stack.top();
		stack.pop();

		int k = g.llave(dato);
		visitado[k] = true;

		cout << dato << endl;

		vector<string> vecinos = g.vecinos(dato);

		for (int i = g.vecinos(dato).size() - 1; i >= 0; i--) {
			if (visitado[g.llave(vecinos[i])] == false) {
				stack.push(vecinos[i]);
			}
		}
	}
}