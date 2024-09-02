/**
* @file
* @brief Arbol binario de busqueda
* @author David Alexander Chito <davidchito@unicauca.edu.co>
* @author David Santiago Ordo�ez M.<davidsan@unicauca.edu.co>
* @copyright
*/
#include <iostream>
#include "clsBinaryTree.h"

using std::cout;
using std::endl;

using libBinaryTree::clsBinaryTree;

int main(int argc, char* argv[]) {

	//Crear una instancia de arbol binario
	clsBinaryTree<int> varTree;

	cout << (varTree.opItsEmpty() ? "El arbol esta vacio" : "El arbol no esta vacio") << endl;

	cout << "Insertar datos" << endl;
	//Insertar datos
	varTree.opInsert(30);
	varTree.opInsert(25);
	varTree.opInsert(36);
	varTree.opInsert(47);
	varTree.opInsert(32);
	varTree.opInsert(27);

	cout << (varTree.opItsEmpty() ? "El arbol esta vacio" : "El arbol no esta vacio") << endl;
	//Imprimir en preorden
	varTree.opPreOrder();
	cout << endl;

	varTree.opInOrder();
	cout << endl;

	varTree.opPosOrder();
	cout << endl;

	return 0;
}