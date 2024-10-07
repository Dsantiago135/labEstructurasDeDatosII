#include <iostream>
#include "ADTBinarySearchTree.h"
#include "ADTBinaryExpressionTree.h"
#include "ADTBinaryHuffmanTree.h"

using namespace libBinaryTree;

int main() {
    cout <<"Prueba arbol de Busqueda: " << endl << endl;
    clsBinarySearchTree<int> varSearchTree;
    varSearchTree.opInsert(20);
    varSearchTree.opInsert(35);
    varSearchTree.opInsert(1);
    varSearchTree.opInsert(19);
    varSearchTree.opInsert(47);
    varSearchTree.opInsert(10);
    varSearchTree.opInsert(19);
    varSearchTree.opShowInOrder();

    varSearchTree.opDelete(4);
    varSearchTree.opDelete(35);
    varSearchTree.opShowPreOrder();
    varSearchTree.opShowInOrder();
    varSearchTree.opShowPosOrder();

    cout << endl << endl <<"Prueba arbol de Huffman:" << endl ;
    clsBinaryHuffmanTree varHuffmanTree("programa");
    varHuffmanTree.opShowTree();
    varHuffmanTree.opShowPreOrder();
//   cout << endl << "arbol en Preorden" << endl;
//    varTree.opShowPreOrder();
//    cout << endl << "arbol en Inorden" << endl;
//    varTree.opShowInOrder();
//    cout << endl << "arbol en Posorden" << endl;
//    varTree.opShowPosOrder();
//    cout << endl <<"Prueba arbol de expresiones" << endl;
    cout << endl << endl << "Prueba arbol de Expresiones:" << endl ;

    clsBinaryExpressionTree varExpresionTree("(a+((b-c)*(d+e))+f)+g");

    cout << endl << "Prueba arbol AVL:"<< endl;
    return 0;
}
