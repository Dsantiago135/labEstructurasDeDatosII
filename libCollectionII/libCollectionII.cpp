#include <iostream>
#include "ADTBinarySearchTree.h"
#include "ADTBinaryExpressionTree.h"
#include "ADTBinaryHuffmanTree.h"
#include "ADTN_AryTree.h"
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
    clsADTN_AryTree<int, 4> directory;
    directory.opInsert(1);
    directory.opInsert(5);
    directory.opInsert(35);
    directory.opInsert(87);
    directory.opInsert(23);
    directory.opInsert(3);
    directory.opInsert(67);
    directory.opInsert(31);
    directory.opInsert(89);
    directory.opInsert(12);
    directory.opInorder(cout);

    clsPerson varperson(2345679345,"Juan","Perez","1234567","cers34567","345678","34567");
    cout <<varperson <<endl;
    return 0;
}
