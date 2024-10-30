#include <iostream>
#include "ADTBinarySearchTree.h"
#include "ADTBinaryExpressionTree.h"
#include "ADTBinaryHuffmanTree.h"
#include "ADT_B_Tree.h"
#include "clsPerson.h"

using namespace libTree;
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

    cout << endl << endl << "Prueba arbol de Expresiones:" << endl ;
    clsBinaryExpressionTree varExpresionTree("(a+((b-c)*(d+e))+f)+g");
    varExpresionTree.opShowExpressionTree();

    cout << endl << "Prueba arbol AVL:"<< endl;

    cout << endl << "Prueba arbol N_Ario:" << endl;
    clsADT_B_Tree<clsPerson, 3> directory;
    directory.opDeserialize("Prueba.csv");
    directory.opInorder(cout);
    directory.opSearch(123456432);
    cout << endl;
    return 0;
}
