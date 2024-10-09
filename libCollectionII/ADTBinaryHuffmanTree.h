#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include "ADTBinaryTree.h"

using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;

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
        friend ostream& operator<< (ostream& os ,strHuffman& prmData) {
            os <<"|"<< prmData.attCharacter << "-" << prmData.attFrequency << "-" << prmData.attCode << "|";
            return os;
        }
    };

    class clsBinaryHuffmanTree : public ADTBinaryTree<strHuffman>{
    using typename ADTBinaryTree<strHuffman>::strNode;
#pragma region Attributes
    private:
        string attOriginalWord; /*!< Palabra original que se codificará >*/
#pragma endregion
#pragma region Operations
    public:
    #pragma region CRUD
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
        * @brief Genera un árbol de Huffman a partir de un vector de datos Huffman
        * @param prmArray Vector que contiene los datos Huffman con frecuencia y carácter
        * @return Nodo raíz del árbol de Huffman generado
        */
        strNode* opGenerateTree(vector<strHuffman>& prmArray) {
            //ordeno el vector antes de empezar a generar nodos
            std::sort(prmArray.begin(), prmArray.end(), [](const strHuffman& a, const strHuffman& b) {
                return a.attFrequency < b.attFrequency;
                });

            //creo un vector de nodos para operar(ya ordenado por frecuencias)
            vector<strNode*> varFrequencyVector;
            for (int i = 0; prmArray.size() > i; i++) {
                strNode* varNode = new strNode(prmArray[i]);
                varFrequencyVector.push_back(varNode);
            };
            while (varFrequencyVector.size() >= 2) {
                strNode* varDadNode = new strNode(strHuffman('\0', 0)); // Nodo padre con frecuencia 0
                varDadNode->attData.attFrequency = varFrequencyVector[0]->attData.attFrequency + varFrequencyVector[1]->attData.attFrequency;
                varDadNode->attLeft = varFrequencyVector[0];
                varDadNode->attRight = varFrequencyVector[1];

                varFrequencyVector.erase(varFrequencyVector.begin(), varFrequencyVector.begin() + 2); // Elimina los dos nodos menores
                varFrequencyVector.push_back(varDadNode);  // Inserta el nuevo nodo padre al final
                std::sort(varFrequencyVector.begin(), varFrequencyVector.end(), [](strNode* a, strNode* b) {
                    return a->attData.attFrequency < b->attData.attFrequency;
                    });

            }
            this->attRoot = varFrequencyVector[0];
            return varFrequencyVector[0];
        }
    #pragma endregion
    #pragma region Code and Frequency
        /**
         * @brief Genera los códigos de Huffman de cada carácter en el árbol de forma recursiva
         * @param prmNode Nodo actual del árbol
         * @param prmDadCode Código del nodo padre acumulado hasta el nodo actual
         */
        void opGenerateCode(strNode* prmNode, string prmDadCode) {
            if (prmNode == nullptr) return;

            // Si es una hoja, asignamos el código
            if (prmNode->opItsLeaf()) {
                prmNode->attData.attCode = prmDadCode;
            }

            // Recursión para los hijos: "0" para la izquierda, "1" para la derecha
            opGenerateCode(prmNode->attLeft, prmDadCode + "0");
            opGenerateCode(prmNode->attRight, prmDadCode + "1");
        }
        /**
         * @brief Busca el código Huffman correspondiente a un carácter específico en el árbol
         * @param prmNode Nodo actual del árbol
         * @param prmCharacter Carácter que se busca
         * @param prmCode Código resultante del carácter buscado
         * @return True si el carácter fue encontrado, de lo contrario False
         */
        bool opSearchCodeWord(strNode* prmNode, char prmCharacter, string& prmCode) {
            if (prmNode == nullptr) return false;

            if (prmNode->opItsLeaf()) {
                if (prmNode->attData.attCharacter == prmCharacter) {
                    prmCode = prmCode + prmNode->attData.attCode;
                    return true;
                }
                return false;
            }
            // Llamadas recursivas a la izquierda y derecha
            if (opSearchCodeWord(prmNode->attLeft, prmCharacter, prmCode)) return true;
            return opSearchCodeWord(prmNode->attRight, prmCharacter, prmCode);
        }
        /**
         * @brief Codifica la palabra original utilizando el árbol de Huffman
         * @return String que contiene el código Huffman de la palabra original
         */
        string opCodeOriginalWord() {
            string varCode;
            // Recorre cada carácter de la palabra original y genera su código Huffman
            for (size_t i = 0; i < attOriginalWord.length(); i++) {
                // Se busca el código de cada carácter y lo concatena a la cadena varCode
                opSearchCodeWord(attRoot, attOriginalWord[i], varCode);
            }
            return varCode;  // Devuelve el código completo de la palabra original
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
    #pragma endregion
    #pragma region ShowTree
        /**
         * @brief Realiza un recorrido preorden en el árbol de Huffman, mostrando los datos de cada hoja
         * @param prmNode Nodo actual del árbol desde el cual inicia el recorrido
         */
        void opHuffmanTreePreOrder(strNode* prmNode) {
            if (prmNode == nullptr) return;

            if (prmNode->opItsLeaf()) {
                cout << "Caracter: " << prmNode->attData.attCharacter;
                cout << " - Frecuencia: " << prmNode->attData.attFrequency;
                cout << " - Codigo del caracter: " << prmNode->attData.attCode << endl;
            }

            // Llamadas recursivas para recorrer el subárbol izquierdo y derecho
            opHuffmanTreePreOrder(prmNode->attLeft);
            opHuffmanTreePreOrder(prmNode->attRight);
        }
        /**
         * @brief Muestra el árbol de Huffman y los códigos generados
         */
        void opShowTree() {
            cout << "Palabra original: " << attOriginalWord << endl;  // Muestra la palabra original
            opHuffmanTreePreOrder(attRoot);  // Realiza un recorrido en preorden para mostrar los nodos (caracteres, frecuencias, códigos)
            cout << endl << "Codigo de la palabra: ";
            cout << endl << opCodeOriginalWord();  // Muestra el código Huffman completo de la palabra original
            opShowPreOrder();
            opShowInOrder();
            opShowPosOrder();
        }
    #pragma endregion  
#pragma endregion
    };
}