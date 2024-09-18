#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

using libBinaryTree::ADTBinaryTree;
namespace libBinaryTree {
	template <class T>
	/*@brief �rbol binario de Huffman (es una subclase de �rbol binario)*/
	class clsBinaryHuffmanTree : protected ADTBinaryTree<T> {
	protected:
		using typename ADTBinaryTree<T>::strNode;
#pragma region Attribute
	private:
		/*@brief Estrcutura para dato Huffman*/
		struct strHuffman {
			T attData; /*!< caracter almacenado >*/
			int attRef; /*!< Frecuencua del caracter en la palabra>*/
			string attCode; /*!< C�digo Huffman asociado al caracter>*/
		};
		/*!< Palabra de la cual se form� el �rbol Huffman >*/
		string attOriginalWord;
#pragma endregion 
#pragma region Operations
	public:
		/**
		*@brief Constructor por defecto de un �rbol binario de Huffman
		*@param Palabra ra�z de la cual saldra el c�digo Huffman
		*/
		clsBinaryHuffmanTree(string prmWord) {
			attOriginalWord = prmWord;

		}
#pragma endregion
	};
}