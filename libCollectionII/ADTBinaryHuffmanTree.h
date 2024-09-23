#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

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

		}
		/*@brief Crea el código de Huffman de todos los caracteres del árbol
		*@param Nodo actual
		*@param Código del padre
		*@param True si el siguiente nodo está a la izquierda del nodo actual ó false si esta a la derecha
		*/
		void opGenerateCode(strNode* prmNode, string prmDadCode, bool prmSite) {
			if (prmNode == nullptr) return;

			if (prmSite) prmNode->attCode = prmDadCode + "1";
			else prmNode->attCode = prmDadCode + "0";

			opGenerateCode(prmNode->attLeft, prmNode->attCode, false);
			opGenerateCode(prmNode->attRigth, prmNode->attCode, true);
		}
#pragma endregion
	};
}