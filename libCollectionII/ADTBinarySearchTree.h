#pragma once
#include <iostream>
#include <vector>
#include "ADTBinaryTree.h"

using std::cout;
using std::endl;
using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T>
	/*@brief Árbol binario de busqueda (es una subclase de árbol binario)*/
	class clsBinarySearchTree: public ADTBinaryTree<T> {
		using typename ADTBinaryTree<T>::strNode;
#pragma region Operations
	protected:
	#pragma region CRUD
		/**
		* @brief Intenta insertar un nuevo dato a partir de padre
		* @param prmFather Potencial padre del nodo
		* @param prmNode nuevo nodo
		* @return true si n pudo ser insertado, false en caso contrario
		*/
		bool opInsert(strNode* prmFather, strNode* prmNode) {

			// Si el padre es nulo, el nuevo nodo se convierte en la raiz.
			if (prmFather == nullptr) {
				this->attRoot = prmNode;
				return true;
			}

			// Verificar si el dato ya esta en el arbol
			if (prmFather->attData == prmNode->attData) return false;

			//Tratar de insertar en los hijos
			if (prmFather->attData > prmNode->attData) {
				//Insertar a la izquierda
				// El hijo izquierdo es nulo?
				if (prmFather->attLeft == nullptr) {
					// El nuevo nodo se convierte en el hijo izquierdo					
					prmFather->attLeft = prmNode;
					// Notificar de nodo insertado
					this->opInserted(prmNode);
					return true;
				}
				else {
					// Insertar recursivamente en el hijo izquierdo
					return opInsert(prmFather->attLeft, prmNode);
				}
			}
			else {
				// Insertar a la derecha
				//El hijo derecho es nulo?
				if (prmFather == nullptr) {
					// El nuevo nodo se convierte en el hijo derecho					
					prmFather->attRight = prmNode;
					// Notificar de nodo insertado
					this->opInserted(prmNode);
					return true;
				}
				else {
					// Insertar recursivamente en el hijo derecho
					return opInsert(prmFather->attRight, prmNode);
				}
			}
		}
		/**
		* @brief Intenta eliminar un dato del árbol
		* @param prmFather padre del nodo que contiene el dato
		* @param prmNode nodo a verificar
		* @param prmData dato a aliminar
		*/
		void opDelete(strNode* prmFather, strNode* prmNode, T prmData) {
			//0. Si prmNode es nulo, el dato no esta en el arbol!! terminar
			if (prmNode == nullptr) return;

			// 1. Si prmNode contiene el dato:
			if (prmNode->opContain(prmData)) {
				// 1.1. Si n es hoja, eliminar el nodo n y terminar
				if (prmNode->opItsLeaf()) {

					if (prmFather != nullptr) {
						// El nodo tiene padre, actualizar la referencia del padre
						if (prmFather->attLeft == prmNode) {
							prmFather->attLeft = nullptr;
						}
						else {
							prmFather->attRight= nullptr;
						}
						// Informar que se elimino un nodo
						this->opRemoved(prmFather);
					}
					else {
						// El nodo es hoja y la raiz, actualizar el apuntador a la raiz
						this->attRoot = nullptr;
					}
					delete prmNode;
				}
				else {
					// 1.2  Si n no es hoja:
					//   1.2.1 buscar: el mayor de los menores O el menor de los mayores
					//   a este nodo lo denominamos "varNode"

					prmFather = prmNode;
					strNode* varNode;

					if (prmNode->attLeft != nullptr) {
						// Mayor de los menores
						varNode = prmNode->attLeft;
						while (varNode->attRight != nullptr) {
							prmFather = varNode;
							varNode = varNode->attRight;
						}
					}
					else {
						// Menor de los mayores
						varNode = prmNode->attRight;
						while (varNode->attLeft != nullptr) {
							prmFather = varNode;
							varNode = varNode->attLeft;
						}
					}
					//   1.2.2 intercambiar el dato de x con el dato de n
					std::swap(prmNode->attData, varNode->attData);
					//   1.2.3 eliminar recursivamente el dato a partir de x
					opDelete(prmFather, varNode, prmData);
				}
			}
			else if (prmNode->attData > prmData) {
				// 2. Si el dato de n es mayor al dato,
				// eliminar recursivamente hacia el hijo izquierdo
				opDelete(prmNode, prmNode->attLeft, prmData);

			}
			else {
				// 3. Si el dato de n es menor al dato,
				// eliminar recursivamente hacia el hijo derecho
				opDelete(prmNode, prmNode->attRight, prmData);
			}
		}
		/**
		* @brief Metodo de plantilla hijo eliminado
		* @param padre Padre del nodo eliminado
		*/
		virtual void opRemoved(strNode* prmFather) {

		}
		/**
		* @brief Metodo de plantilla nodo insertado
		* @param n Nuevo nodo del arbol
		*/
		virtual void opInserted(strNode* prmNode) {

		}
#pragma endregion
	#pragma region Utilities
		/**
		*@brief Va al dato más grande de la izquierda del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más grande de la izquierda de la raiz
		*/
		strNode* opGolargestOnTheLeft(strNode* prmNode) {
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode->attLeft == nullptr) return prmNode;
			//si el nodo si tiene un hijo  izquierdo se mueve a este y va lo más a la derecha posible
			prmNode = prmNode->attLeft;
			return this->opGoExtremeRight(prmNode);
		}
		/**
		*@brief Va al dato más pequeño de la derecha del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más pequeño de la derecha de la raiz
		*/
		strNode* opGoSmallestOnTheRight(strNode* prmNode) {
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode->attRight == nullptr) return prmNode;
			//si el nodo si tiene un hijo derecho se mueve a este y va lo más a la izquierda posible
			prmNode = prmNode->attRight;
			return this->opGoExtremeLeft(prmNode);
		}
		/*vector<strNode*> opGetBranch(strNode* prmNode) {
			vector<strNode*> varBranch;
			strNode* varNode = this->attRoot;
			while (varNode != nullptr && varNode->attData != prmNode->attData) {
				varBranch.insert(varBranch.begin(), varNode);
				if (varNode->attData > prmNode->attData) {
					varNode = varNode->attLeft;
				}
				else varNode = varNode->attRigth;
			}
		}
		*/
#pragma endregion 
	public:
	#pragma region CRUD
		/**
		* @brief Inserta un nuevo dato en el arbol
		* @param prmData Nuevo dato a insertar
		*/
		void opInsert(T prmData) {
			// Crear un nuevo nodo que contiene el dato
			strNode* varNode = new strNode(prmData);
			// Tratar de insertar el nodo a partir de la raiz
			if (!opInsert(this->attRoot, varNode)) {
				//Liberar la memoria del nodo si no se pudo insertar
				delete varNode;
			}
		}
		/**
		* @brief Elimina un dato del arbol
		* @param prmData Dato a eliminar
		*/
		void opDelete(T prmData) {
			//1. Si el arbol es vacio, terminar
			if (this->opItsEmpty()) {
				return;
			}
			/*
			// POST: El arbol no esta vacio
			//2. recursivamente, eliminar el dato a partir de la raiz
			*/
			opDelete(nullptr, this->attRoot, prmData);
		}
#pragma endregion
#pragma endregion
	};
}