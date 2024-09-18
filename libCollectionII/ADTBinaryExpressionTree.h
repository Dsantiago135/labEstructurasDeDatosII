#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T> 
	/*@brief Árbol binario de Expresiones(es una subclase de árbol binario)*/
	class clsBinaryExpressionTree : protected ADTBinaryTree<T> {
	protected:
		using typename ADTBinaryTree<T>::strNode;
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