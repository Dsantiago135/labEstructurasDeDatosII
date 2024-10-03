#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include "ADTBinaryTree.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::priority_queue;
using std::pair;

namespace libBinaryTree {
    /*@brief Estructura de dato Huffman*/
    struct strHuffman {
        char attCharacter; /*!< Caracter almacenado >*/
        int attFrequency; /*!< Frecuencia del caracter >*/
        string attCode; /*!< Código Huffman asociado al caracter >*/

        /**
         * @brief Constructor de la estructura strHuffman
         * @param prmData Caracter almacenado
         * @param prmFrequency Frecuencia del caracter en la palabra
         */
        strHuffman(char prmData, int prmFrequency) : attCharacter(prmData), attFrequency(prmFrequency), attCode("") {}
        /**
         * @brief Sobrecarga del operador "mayor que" para comparar la frecuencia de dos objetos strHuffman
         * @param prmOther Objeto strHuffman a comparar
         * @return True si la frecuencia del objeto actual es mayor que la del objeto prmOther
         */
        bool operator > (const strHuffman& prmOther) const {
            return attFrequency > prmOther.attFrequency;
        }
    };
    class clsBinaryHuffmanTree : public ADTBinaryTree<strHuffman>{
    using typename ADTBinaryTree<strHuffman>::strNode;
    string attOriginalWord; /*!< Palabra original que se codificará >*/

    public:
        /**
         * @brief Constructor de la clase clsBinaryHuffmanTree, que inicializa la palabra y construye el árbol de Huffman
         * @param prmWord Palabra de la cual se generarán los códigos Huffman
         */
        clsBinaryHuffmanTree(string prmWord) {
            this->attOriginalWord = prmWord;
            vector<strHuffman> varFrequencyArray;
            opFrequencyCharacter(prmWord, varFrequencyArray, 0);

            // Crear el árbol de Huffman
            strNode* varHuffmanTreeRoot = opGenerateTree(varFrequencyArray);
            this->attRoot = varHuffmanTreeRoot;

            // Generar los códigos de Huffman
            opGenerateCode(varHuffmanTreeRoot, "");
        }
        /**
         * @brief Calcula la frecuencia de cada carácter en la palabra de manera recursiva
         * @param prmWord Palabra original
         * @param prmArray Vector donde se almacenarán los datos Huffman
         * @param prmIndex Índice actual del carácter que se está procesando
         */
        void opFrequencyCharacter(const string& prmWord, vector<strHuffman>& prmArray, int prmIndex) {
            // Caso base para detener recursividad (último caracter)
            if (prmIndex >= prmWord.length()) return;

            char varCurrentCharacter = prmWord[prmIndex];
            bool varFound = false;

            // Busca si el carácter ya fue registrado
            for (size_t i = 0; i < prmArray.size(); i++) {
                if (prmArray[i].attCharacter == varCurrentCharacter) {
                    prmArray[i].attFrequency++;
                    varFound = true;
                    break;
                }
            }

            // Si no se encontró, se agrega como un nuevo objeto strHuffman
            if (!varFound) {
                prmArray.emplace_back(strHuffman(varCurrentCharacter, 1));
            }

            // Llamada recursiva para procesar el siguiente carácter
            opFrequencyCharacter(prmWord, prmArray, prmIndex + 1);
        }
        /**
         * @brief Genera un árbol de Huffman a partir de un vector de datos Huffman
         * @param prmArray Vector que contiene los datos Huffman con frecuencia y carácter
         * @return Nodo raíz del árbol de Huffman generado
         */
        strNode* opGenerateTree(vector<strHuffman>& prmArray) {
            priority_queue<strNode*, vector<strNode*>, std::function<bool(strNode*, strNode*)>> varFrequencyQueue(
                [](strNode* a, strNode* b) { return a->attData.attFrequency > b->attData.attFrequency; });

            // Agrega todos los elementos al priority queue
            for (const auto& varHuffmanData : prmArray) {
                varFrequencyQueue.push(new strNode(varHuffmanData));
            }

            // Construye el árbol de Huffman
            while (varFrequencyQueue.size() > 1) {
                strNode* varNodeLeft = varFrequencyQueue.top(); varFrequencyQueue.pop();
                strNode* varNodeRight = varFrequencyQueue.top(); varFrequencyQueue.pop();
                strHuffman varNodeCombined('\0', varNodeLeft->attData.attFrequency + varNodeRight->attData.attFrequency);

                strNode* newNode = new strNode(varNodeCombined);
                newNode->attLeft = varNodeLeft;
                newNode->attRight = varNodeRight;
                varFrequencyQueue.push(newNode);
            }

            // Retorna el nodo raíz del árbol de Huffman
            return varFrequencyQueue.top();
        }
        /**
         * @brief Genera los códigos de Huffman de cada carácter en el árbol de forma recursiva
         * @param prmNode Nodo actual del árbol
         * @param prmDadCode Código del nodo padre acumulado hasta el nodo actual
         */
        void opGenerateCode(strNode* prmNode, string prmDadCode) {
            if (prmNode == nullptr) return;

            if (prmNode->opItsLeaf()) {
                prmNode->attData.attCode = prmDadCode;
            }

            // Llamadas recursivas para los nodos hijos
            opGenerateCode(prmNode->attLeft, prmDadCode + "0");
            opGenerateCode(prmNode->attRight, prmDadCode + "1");
        }
        /**
         * @brief Realiza un recorrido preorden en el árbol de Huffman, mostrando los datos de cada hoja
         * @param prmNode Nodo actual del árbol desde el cual inicia el recorrido
         */
        void opPreOrder(strNode* prmNode) {
            if (prmNode == nullptr) return;

            if (prmNode->opItsLeaf()) {
                cout<<prmNode->attData.attCharacter << endl;
                cout << prmNode->attData.attFrequency << endl;
                cout << prmNode->attData.attCode << endl;
            }

            // Llamadas recursivas para recorrer el subárbol izquierdo y derecho
            opPreOrder(prmNode->attLeft);
            opPreOrder(prmNode->attRight);
        }
        /**
         * @brief Busca el código Huffman correspondiente a un carácter específico en el árbol
         * @param prmNode Nodo actual del árbol
         * @param prmCharacter Carácter que se busca
         * @param prmCode Código resultante del carácter buscado
         * @return True si el carácter fue encontrado, de lo contrario False
         */
        bool opCodeWord(strNode* prmNode, char prmCharacter, string& prmCode) {
            if (prmNode == nullptr) return false;
            if (prmNode->opItsLeaf()) {
                if (prmNode->attData.attCharacter == prmCharacter) {
                    prmCode += prmNode->attData.attCode;
                    return true;
                }
                return false;
            }
            // Llamadas recursivas a la izquierda y derecha
            if (opCodeWord(prmNode->attLeft, prmCharacter, prmCode)) return true;
            return opCodeWord(prmNode->attRight, prmCharacter, prmCode);
        }
        /**
         * @brief Codifica la palabra original utilizando el árbol de Huffman
         * @return String que contiene el código Huffman de la palabra original
         */
        string opCodeOriginalWord() {
            string varCode;
            // Recorre cada carácter de la palabra original y genera su código Huffman
            for (size_t i = 0; i < attOriginalWord.length(); i++) {
                // Se obtiene el código de cada carácter y se agrega a la cadena varCode
                opCodeWord(attRoot, attOriginalWord[i], varCode);
            }
            return varCode;  // Devuelve el código completo de la palabra original
        }
        /**
         * @brief Muestra el árbol de Huffman y los códigos generados
         */
        void opShowTree() {
            cout << endl << "Palabra original: " << attOriginalWord;  // Muestra la palabra original
            opPreOrder(attRoot);  // Realiza un recorrido en preorden para mostrar los nodos (caracteres, frecuencias, códigos)
            cout << endl << "Código de la palabra: ";
            cout << endl << opCodeOriginalWord();  // Muestra el código Huffman completo de la palabra original
        }
    };
}