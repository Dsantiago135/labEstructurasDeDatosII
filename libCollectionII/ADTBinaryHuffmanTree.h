#pragma once
#include <iostream>
#include "ADTBinaryTree.h"
#include <vector>
#include <queue>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::priority_queue;
using std::pair;
using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T>
	class clsBinaryHuffmanTree : public ADTBinaryTree<T> {
	protected:
		using strNode = typename ADTBinaryTree<T>::strNode;
	protected:
		struct strHuffman {
			T attCharacter; /*!< Caracter almacenado >*/
			int attFrequency; /*!< Frecuencia del caracter >*/
			string attCode; /*!< Código Huffman asociado al caracter >*/

			strHuffman(T prmData, int prmFrequency) : attCharacter(prmData), attFrequency(prmFrequency), attCode("") {}
			//@brief sobrecarga de operador para comparar la frecuencia y facilitar el ordenamiento
			bool operator > (const strHuffman& prmOther) const {
				return attFrequency > prmOther.attFrequency;
			}
		};
		string attOriginalWord;
	public:
		/*
		*@brief Constructor por defecto de códigos Huffman
		*@param Palabra de la cual se crearan los codigo Huffman
		*/
		clsBinaryHuffmanTree(string prmWord) {

			attOriginalWord = prmWord;
			vector<strHuffman> varFrequencyArray;
			opFrequencyCharacter(prmWord, varFrequencyArray, 0);

			// Crear el árbol de Huffman
			strNode* varHuffmanTreeRoot = opGenerateTree(varFrequencyArray);
			this->attRoot = varHuffmanTreeRoot;

			// Generar los códigos de Huffman
			opGenerateCode(varHuffmanTreeRoot, "");
		}
		/*
		*@brief Determina los caracteres que componen una palabra y con cuanta frecuencia aparece el caracter en la palabra
		*@param Palabra de de la cual se sacará el vector de caracteres y su frecuencia 
		*/
		void opFrequencyCharacter(const string& prmWord, vector<strHuffman>& prmArray, int prmIndex) {
			//  Caso base para detener recursividad (es el ultimo caracter)
			if (prmIndex >= prmWord.length()) return;

			char varCurrentCharacter = prmWord[prmIndex];
			bool varFound = false;
			
			// Recorre la palabra para determinar la frecuencia del caracter actual
			for (size_t i = 0; i < prmArray.size(); i++) {
				if (prmArray[i].attCharacter == varCurrentCharacter) {
					prmArray[i].attFrequency++;
					varFound = true;
					break;
				}
			}
			
			//Si no se encontro el caracter en el arreglo de frecuencias, crea un dato Huffman y lo agrega al arreglo
			if (!varFound) {
				prmArray.emplace_back(varCurrentCharacter, 1);
			}

			opFrequencyCharacter(prmWord, prmArray, prmIndex + 1);
		}
		/*
		*@brief Genera un árbol de Huffman apartir de un vector
		*@param Vector de con los datos Huffman con los cuales se creara el árbol
		*/
		strNode* opGenerateTree(vector<strHuffman>& prmArray) {
			priority_queue<strHuffman, vector<strHuffman>, std::greater<strHuffman>> varFrequencyQueue;

			// Agregar todos los elementos al priority queue
			for (const auto& varHuffmanData : prmArray) {
				varFrequencyQueue.push(varHuffmanData);
			}

			// Crear el árbol de Huffman
			while (varFrequencyQueue.size() > 1) {
				strHuffman varNodeLeft = varFrequencyQueue.top(); varFrequencyQueue.pop();
				strHuffman varNodeRight = varFrequencyQueue.top(); varFrequencyQueue.pop();
				strHuffman varNodeCombined('\0', varNodeLeft.attFrequency + varNodeRight.attFrequency);

				strNode* newNode = new strNode(varNodeCombined);
				newNode->attLeft = new strNode(varNodeLeft);
				newNode->attRight = new strNode(varNodeRight);
				varFrequencyQueue.push(varNodeCombined);
			}

			// El nodo raíz del árbol de Huffman
			return new strNode(varFrequencyQueue.top());
		}
		/*
		* @brief Genera los códigos de cada caracter Huffman apartir de un árbol Huffman
		* @param Nodo raiz del árbol Huffman
		* @param Código del padre del Nodo (usado para recursividad) 
		*/
		void opGenerateCode(strNode* prmNode, string prmDadCode) {
			if (prmNode == nullptr) return;

			if (prmNode->opItsLeaf()) {
				prmNode->attData.attCode = prmDadCode;
			}

			opGenerateCode(prmNode->attLeft, prmDadCode + "0");
			opGenerateCode(prmNode->attRight, prmDadCode + "1");
		}
		/*@brief Implementación basica para cumpli herencia*/
		virtual bool opInsert(strNode* prmDadNode, strNode* prmNewNode) override {
			return false;
		}
		/*@brief Implementación basica para cumpli herencia*/
		virtual void opRemove(strNode* prmNode, T prmData) override {
		}
	};
}
