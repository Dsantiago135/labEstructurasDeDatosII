#include <iostream>
#include "ADTBinarySearchTree.h"
#include "ADTBinaryExpressionTree.h"
#include "ADTBinaryHuffmanTree.h"

int main() {
    // Pruebas para clsBinarySearchTree
    std::cout << "=== �rbol de B�squeda Binaria ===" << std::endl;
    libBinaryTree::clsBinarySearchTree<int> bst;
    bst.opInsert(5);
    bst.opInsert(3);
    bst.opInsert(7);
    bst.opInsert(2);
    bst.opInsert(4);

    std::cout << "Recorrido PreOrden del �rbol de B�squeda: ";
    bst.opShowPreOrder();
    std::cout << std::endl;

    bst.opRemove(3);
    std::cout << "Recorrido PreOrden despu�s de eliminar 3: ";
    bst.opShowPreOrder();
    std::cout << std::endl;

    // Pruebas para clsBinaryExpressionTree
    std::cout << "=== �rbol de Expresiones ===" << std::endl;
    libBinaryTree::clsBinaryExpressionTree<std::string> expressionTree;
    expressionTree.opInsert("a");
    expressionTree.opInsert("+");
    expressionTree.opInsert("b");

    std::cout << "Mostrar �rbol de expresiones (en orden): ";
    expressionTree.opShowTree();
    std::cout << std::endl;

    // Pruebas para clsBinaryHuffmanTree
    std::cout << "=== �rbol de Huffman ===" << std::endl;
    libBinaryTree::clsBinaryHuffmanTree<char> huffmanTree;
    huffmanTree.opInsert('a', 5);
    huffmanTree.opInsert('b', 9);
    huffmanTree.opInsert('c', 12);

    std::cout << "Mostrar �rbol de Huffman (preorden): ";
    huffmanTree.opShowTree();
    std::cout << std::endl;

    return 0;
}
