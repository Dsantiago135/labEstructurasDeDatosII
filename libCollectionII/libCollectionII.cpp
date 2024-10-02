#include <iostream>
#include "ADTBinarySearchTree.h"
#include "ADTBinaryExpressionTree.h"
#include "ADTBinaryHuffmanTree.h"
using namespace libBinaryTree;

int main() {
    // Pruebas para clsBinarySearchTree
    std::cout << "=== Árbol de Búsqueda Binaria ===" << std::endl;
    libBinaryTree::clsBinarySearchTree<int> bst;
    bst.opInsert(5);
    bst.opInsert(3);
    bst.opInsert(7);
    bst.opInsert(2);
    bst.opInsert(4);

    std::cout << "Recorrido PreOrden del Árbol de Búsqueda: ";
    bst.opShowPreOrder();
    std::cout << std::endl;

    bst.opRemove(3);
    std::cout << "Recorrido PreOrden después de eliminar 3: ";
    bst.opShowPreOrder();
    std::cout << std::endl;

    // Pruebas para clsBinaryExpressionTree
    std::cout << "=== Árbol de Expresiones ===" << std::endl;
    libBinaryTree::clsBinaryExpressionTree<std::string> expressionTree;
    expressionTree.opInsert("a");
    expressionTree.opInsert("+");
    expressionTree.opInsert("b");

    std::cout << "Mostrar árbol de expresiones (en orden): ";
    expressionTree.opShowTree();
    std::cout << std::endl;

    std::cout << "=== Arbol de Huffman ===" << std::endl;
    clsBinaryHuffmanTree huffmanTree = clsBinaryHuffmanTree("supercalifragilisticoespialidoso");
    std::cout << "Mostrar caracteres y codigos: ";
    huffmanTree.opShowTree();
    std::cout << std::endl;
    return 0;
}
