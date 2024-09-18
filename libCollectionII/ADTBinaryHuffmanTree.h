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
			T attData; /*!< Dato almacenado >*/
			int attRef; /*!< N�mero de referencia del dato>*/
		};
#pragma endregion 
#pragma region Operations
	protected:
		bool opInsert(strNode* prmDadNode, strNode* prmNewNode) override {
		}
		void opRemove(strNode* prmNode, T prmData) override {
		}
	public:
		void opInsert(T prmData) {
		}
		void opRemove(T prmData) {
		}
#pragma endregion
	};
}