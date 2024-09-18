#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

using libBinaryTree::ADTBinaryTree;
namespace libBinaryTree {
	template <class T>
	/*@brief Árbol binario de Huffman (es una subclase de árbol binario)*/
	class clsBinaryHuffmanTree : protected ADTBinaryTree<T> {
	protected:
		using typename ADTBinaryTree<T>::strNode;
#pragma region Attribute
	private:
		/*@brief Estrcutura para dato Huffman*/
		struct strHuffman {
			T attData; /*!< caracter almacenado >*/
			int attRef; /*!< Frecuencua del caracter en la palabra>*/
			string attCode; /*!< Código Huffman asociado al caracter>*/
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
#pragma endregion
	};
}