#pragma once
#include <iostream>
#include "ADTBinaryTree.h"
#include <vector>

using std::vector;
using std::string;
using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T>
	/*@brief Árbol binario de Huffman (es una subclase de árbol binario)*/
	class clsBinaryHuffmanTree : public ADTBinaryTree<T> {
	protected:
		using typename ADTBinaryTree<T>::strNode;
#pragma region Attribute
	private:
		/*@brief Estrcutura para dato Huffman*/
		struct strHuffman {
			T attData; /*!< caracter almacenado >*/
			int attFrequency; /*!< Frecuencua del caracter en la palabra>*/
			string attCode; /*!< Código Huffman asociado al caracter>*/

			strHuffman(T prmData,int prmFrequency) :attData(prmData), attFrequency(prmFrequency), attCode("") {}
		};
		/*!< Palabra de la cual se formó el árbol Huffman >*/
		string attOriginalWord;
#pragma endregion 
#pragma region Operations
	public:
		/**
		*@brief Constructor por defecto de un árbol binario de Huffman
		*@param Palabra raíz de la cual saldra el código Huffman
		*/
		clsBinaryHuffmanTree(string prmWord) {
			attOriginalWord = prmWord;
			vector<strHuffman> varFrequencyArray; // Array para guardar las frecuencias
			opFrequencyCharacter(prmWord, varFrequencyArray, 0); // Llenar el array con frecuencias

			// Ordenar el array de frecuencias
			opMergeSort(varFrequencyArray, 0, varFrequencyArray.size() - 1);

			
		}
		/*@brief Crea el código de Huffman de todos los caracteres del árbol
		*@param Nodo actual
		*@param Código del padre
		*@param True si el siguiente nodo está a la izquierda del nodo actual ó false si esta a la derecha
		*/
		void opGenerateCode(strNode* prmNode, string prmDadCode) {
			if (prmNode == nullptr) return;

			// Concatenar el código
			prmNode->attCode = prmDadCode;

			// Llamar recursivamente para el hijo izquierdo (agregar "0") y derecho (agregar "1")
			opGenerateCode(prmNode->attLeft, prmNode->attCode + "0");
			opGenerateCode(prmNode->attRight, prmNode->attCode + "1");
		}
		/*
		@brief
		@param
		@param
		@param
		*/
		void opFrequencyCharacter (const string& prmWord, vector <strHuffman> & prmArray, int prmIndex) {
			// Caso base: fin de la palabra
			if (prmIndex >= prmWord.length()) return;
		//@param variable la cual guarda el caracter con el que se está trabajando actualmente
		char varCurrentCharacter = prmWord[prmIndex];

		//@param variable que hace referencia si el caracter se encontró o no
		bool varFound = false;

		// Buscar si el carácter ya existe en el arreglo
		for (size_t i = 0; i < prmArray.size(); i++) {
			if (prmArray[i].attData == varCurrentCharacter) {
				// Si el carácter ya está, incrementar su frecuencia
				prmArray[i].attFrequency++;
				varFound = true;
				break;
			}
		}

		// Si el carácter no fue encontrado, añadir un nuevo nodo
		if (!varFound) {
			//@param nuevo caracter a guardar en el arreglo, y la frecuencia de 1
			strHuffman varNewData = {varCurrentCharacter, 1};
			prmArray.push_back(varNewData);
		}

		// Llamada recursiva al siguiente carácter
		opFrequencyCharacter(prmWord, prmArray, prmIndex+ 1);
	}
		void opMergeSort (vector<int>& prmArray, int prmLeft, int prmRight) {
			if (prmLeft < prmRight) {
				int varMid = prmLeft + (prmRight - prmLeft) / 2; // Encuentra el punto medio

				opMergeSort(prmArray, prmLeft, varMid); // Ordenar la mitad izquierda
				opMergeSort(prmArray, varMid + 1, prmRight); // Ordenar la mitad derecha
				opMerge(prmArray, prmLeft, varMid, prmRight); // Combinar las mitades
			}
		}
		void opMerge(vector<int>& prmArray, int prmLeft, int prmMid, int prmRight) {
			// Crear vectores temporales para las mitades izquierda y derecha
			vector<int> varLeftArray(prmArray.begin() + prmLeft, prmArray.begin() + prmMid + 1);
			vector<int> varRightprmArray(prmArray.begin() + prmMid + 1, prmArray.begin() + prmRight + 1);

			int i = 0, j = 0, k = prmLeft;

			// Combinar los subprmArrayeglos
			while (i < varLeftArray.size() && j < varRightprmArray.size()) {
				prmArray[k++] = (varLeftArray[i] <= varRightprmArray[j]) ? varLeftArray[i++] : varRightprmArray[j++];
			}

			// Copiar los elementos restantes de varLeftArray (si los hay)
			while (i < varLeftArray.size()) {
				prmArray[k++] = varLeftArray[i++];
			}

			// Copiar los elementos restantes de rightprmArray (si los hay)
			while (j < varRightprmArray.size()) {
				prmArray[k++] = varRightprmArray[j++];
			}
		}
#pragma endregion
	};
}