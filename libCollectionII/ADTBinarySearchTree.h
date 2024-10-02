#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T>
	/*@brief Árbol binario de busqueda (es una subclase de árbol binario)*/
	class clsBinarySearchTree {
#pragma region Attributes
	protected:
		/*@brief Estructura de nodo binario*/
		struct strNode {
			T attData; /*!< Dato almacenado >*/
			strNode* attLeft; /*!< Referencia al hijo izquierdo >*/
			strNode* attRight; /*!< Referencia al hijo derecho >*/
#pragma region OperationsOfStrNode
			strNode(T prmData) :attData(prmData), attLeft(nullptr), attRight(nullptr) {}
			/**
			*@brief Verifica si el nodo una hoja
			*/
			bool opItsLeaf() {
				return(attLeft == nullptr && attRight == nullptr);
			}
			/**
			*@brief Verifica si el dato esta contenido en el nodo
			*@param Dato a comparar
			*/
			bool opContain(T prmData) {
				return(this->attData == prmData);
			}
#pragma endregion
		};
		/*@brief Nodo Raiz del árbol*/
		strNode* attRoot = nullptr;
#pragma endregion
#pragma region Operations
	protected:
	#pragma region CRUD
		/*
*@brief Intenta insertar un nuevo dato a partir de prmDadNode
* @param prmDadNode Potencial padre del nodo
* @param prmNewNode Nuevo nodo
* @return true si prmNewNode pudo ser insertado
*/
		bool opInsert(strNode* prmDadNode, strNode* prmNewNode)override {
			// Verificar si el dato ya esta en el arbol
			if (prmDadNode->attData == prmNewNode->attData) return false;

			//Tratar de insertar en los hijos
			if (prmDadNode->attData > prmNewNode->attData) {
				//Insertar a la izquierda
				//El hijo izquierdo es nulo?
				if (prmDadNode->attLeft == nullptr) {
					//El nuevo nodo se convierte en el hijo izquierdo
					prmDadNode->attLeft = prmNewNode;
					return true;
				}
				else {
					return opInsert(prmDadNode->attLeft, prmNewNode);
				}
			}
			else {
				//Insertar a la derecha
				//El hijo derecho es nulo?
				if (prmDadNode->attRight == nullptr) {
					// El nuevo nodo se convierte en el hijo derecho
					prmDadNode->attRight = prmNewNode;
					return true;
				}
				else {
					return opInsert(prmDadNode->attRight, prmNewNode);
				}
			}
		}
		/*
		*@brief Verificar si el nodo contiene al dato y lo elimina
		*@param Nodo padre del que en dado caso se quitará la referencia
		*@param Nodo que se eliminará
		*@param Dato a eliminar
		*/
		void opRemove(strNode* prmNode, T prmData)override {
			//Si el nodo es nulo el dato no está en el árbol
			if (prmNode == nullptr) return;
			//Si el nodo SI contiene el dato
			if (prmNode->opContain(prmData))
			{
				//Si el nodo es una hoja elimina el nodo y termina
				if (prmNode->opItsLeaf()) {
					prmNode = nullptr;
					delete prmNode;
					return;
				}
				//Si el nodo no es hoja 
				//Si el nodo tiene hijos izquierdos se trabajaran con ellos, de lo contrario se usaran los hijos derechos
				if (prmNode->attLeft != nullptr) {
					//Intercambio del dato del nodo a eliminar y del nodo más grande de la izquierda

					return;

				}
				else {
					//Intercambio del dato del nodo a eliminar y del nodo más pequeño de la derecha

					return;
				};
			}
			//Si el nodo NO contiene el dato
			else {
				//Llama recursivamente para eliminar un dato mayor al nodo dado 
				if (prmNode->attData < prmData) {
					opRemove(prmNode->attRight, prmData);
				}
				////Llama recursivamente para eliminar un dato menor al nodo dado 
				else
				{
					opRemove(prmNode->attLeft, prmData);
				};
			};
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
			return opGoExtremeRight(prmNode);
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
			return opGoExtremeLeft(prmNode);
		}
#pragma endregion 	
	#pragma region ShowTree
		/**
			* @brief Recorrido recursivo en preorden a partir de prmNode (prmNode->dato, prmNode->izq, prmNode->der)
			* @param prmNode Nodo de inicio del recorrido
			*/
		void opPreOrder(strNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}
			cout << " " << prmNode->attData;
			//Invocar recursivamente 
			opPreOrder(prmNode->attLeft);
			opPreOrder(prmNode->attRight);
		}
		/**
			* @brief Recorrido recursivo en inorden a partir de prmNode (prmNode->izq, prmNode->dato, prmNode->der)
			* @param prmNode Nodo de inicio del recorrido
			*/
		void opInOrder(strNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}

			//Invocar recursivamente inorden en el hijo izquierdo
			opInOrder(prmNode->attLeft);
			cout << " " << prmNode->attData;
			//Invocar recursivamente inorden en el hijo derecho
			opInOrder(prmNode->attRight);
		}
		/**
			*@brief Recorrido recursivo en Posorden a partir de prmNode (prmNode->izq, prmNode->der, prmNode->dato)
			*@param prmNode Nodo de inicio del recorrido
			*/
		void opPosOrder(strNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}
			//Invocar recursivamente inorden en el hijo izquierdo
			opPosOrder(prmNode->attLeft);
			//Invocar recursivamente inorden en el hijo derecho
			opPosOrder(prmNode->attRight);
			cout << " " << prmNode->attData;
		}
#pragma endregion
	public:
	#pragma region CRUD
		/**
		* @brief Insertar un nuevo dato en el arbol
		* @param prmData Nuevo dato a insertar
		*/
		void opInsert(T prmData) {
			cout << "Insertar " << prmData << endl;
			// Crear un nuevo nodo que contiene el dato
			strNode* varNewNode = new strNode(prmData);

			if (this->opItsEmpty()) {
				// Si el arbol esta vacio, varNewNode se convierte en la raiz
				this->attRoot = varNewNode;
			}
			else {
				// Tratar de insertar el nodo a partir de la raiz
				if (!opInsert(this->attRoot, varNewNode)) {
					//Liberar la memoria del nodo si no se puede insertar
					delete varNewNode;
				}
			}
		}
		/*
		* @brief Elimina un dato del árbol
		* @param Dato a eliminar
		*/
		void opRemove(T prmData) {
			if (this->opItsEmpty())return;
			opRemove(this->attRoot, prmData);
		}
#pragma endregion
	#pragma region ShowTree
		/**
			* @brief Imprime el recorrido en preorden (dato, izq, der)
			*/
		void opShowPreOrder() {

			opPreOrder(attRoot);
		}
		/**
			* @brief Imprime el recorrido en inorden (izq, dato, der)
			*/
		void opShowInOrder() {

			opInOrder(attRoot);
		}
		/**
			* @brief Imprime el recorrido en posorden (izq, der, dato)
			*/
		void opShowPosOrder() {
			opPosOrder(attRoot);
		}
#pragma endregion
	#pragma region Query
		/**
				* @brief Permite verificar si el arbol esta vacio
				* @return true si el arbol se encuentra vacio
				*/
		bool opItsEmpty() {
			return (attRoot == nullptr);
		}
		/*
		*@brief Cuenta cual es la altura del árbol
		*@return La altura del árbol
		*/
		int opHeightTree(strNode* prmNode) {
			if (prmNode == nullptr) return 0;
			return 1 + std::max(opHeightTree(prmNode->attLeft), opHeightTree(prmNode->attRight));
		}
		/*
		* @brief Cuenta la cantidad de nodos es el árbol (en dado caso contará nodos con datos nulos)
		*/
		int opWeightTree(strNode* prmNode) {
			if (prmNode == nullptr) return 0;
			return 1 + opWeightTree(prmNode->attLeft) + opWeightTree(prmNode->attRight);
		}
		strNode* opGetRoot() {
			return attRoot;
		}
#pragma endregion
#pragma endregion
	};
}