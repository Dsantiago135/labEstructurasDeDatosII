#include <iostream>
#include "ADTBinarySearchTree.h"

using std::cout;
using std::endl;
using  libBinaryTree::clsBinarySearchTree; 

int main(int argc, char* argv[]) {

	//Crear una instancia de arbol binario
	clsBinarySearchTree<int> varTree;

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
	varTree.opShowPreOrder();
	cout << endl;

	varTree.opShowInOrder();
	cout << endl;

	varTree.opShowPosOrder();
	cout << endl;

	return 0;
};