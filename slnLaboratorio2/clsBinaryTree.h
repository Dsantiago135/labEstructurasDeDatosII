#pragma once
#include <iostream>

using std::cout;
using std::endl;

namespace libBinaryTree {
	template <class T>
	/*@brief Arbol Binario de Busqueda*/
	class clsBinaryTree {
#pragma region Attributes
	private:
		/*@brief Nodo binario*/
		struct attNode {
			T attData; /*!< Dato almacenado */
			attNode* attLeft; /*!< Referencia al hijo izquierdo */
			attNode* attRight; /*!< Referencia al hijo derecho */

			attNode(T prmData) :attData(prmData), attLeft(nullptr), attRight(nullptr) {}
		};
		/*@brief Nodo Raiz del árbol*/
		attNode* attRoot = nullptr;
#pragma endregion
#pragma region Operations
	private:
		/**
		* @brief Recorrido preorden a partir de prmNode (prmNode->dato, prmNode->izq, prmNode->der)
		* @param prmNode Nodo de inicio del recorrido
		*/
		void opPreOrder(attNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}
			cout << " " << prmNode->attData;
			//Invocar recursivamente 
			opPreOrder(prmNode->attLeft);
			opPreOrder(prmNode->attRight);
		}
		/**
		* @brief Recorrido inorden a partir de prmNode (prmNode->izq, prmNode->dato, prmNode->der)
		* @param prmNode Nodo de inicio del recorrido
		*/
		void opInOrder(attNode* prmNode) {
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
		*@brief Recorrido Posorden a partir de prmNode (prmNode->izq, prmNode->der, prmNode->dato)
		*@param prmNode Nodo de inicio del recorrido
		*/
		void opPosOrder(attNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}
			//Invocar recursivamente inorden en el hijo izquierdo
			opPosOrder(prmNode->attLeft);
			//Invocar recursivamente inorden en el hijo derecho
			opPosOrder(prmNode->attRight);
			cout << " " << prmNode->attData;
		}
		/**
		* @brief Intenta insertar un nuevo dato a partir de prmDadNode
		* @param prmDadNode Potencial padre del nodo
		* @param prmNewNode Nuevo nodo
		* @return true si prmNewNode pudo ser insertado
		*/
		bool opInsert(attNode* prmDadNode, attNode* prmNewNode) {
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
	public:
		/**
		* @brief Permite verificar si el arbol esta vacio
		* @return true si el arbol se encuentra vacio
		*/
		bool opItsEmpty() {
			return (attRoot == nullptr);
		}
		/**
		* @brief Insertar un nuevo dato en el arbol
		* @param prmData Nuevo dato a insertar
		*/
		void opInsert(T prmData) {
			cout << "Insertar " << prmData << endl;
			// Crear un nuevo nodo que contiene el dato
			attNode* varNewNode = new attNode(prmData);

			if (opItsEmpty()) {
				// Si el arbol esta vacio, varNewNode se convierte en la raiz
				attRoot = varNewNode;
			}
			else {
				// Tratar de insertar el nodo a partir de la raiz
				if (!opInsert(attRoot, varNewNode)) {
					//Liberar la memoria del nodo si no se puede insertar
					delete varNewNode;
				}
			}
		}
		/**
		* @brief Imprime el recorrido en preorden (dato, izq, der)
		*/
		void opPreOrder() {

			opPreOrder(attRoot);
		}
		/**
		* @brief Imprime el recorrido en inorden (izq, dato, der)
		*/
		void opInOrder() {

			opInOrder(attRoot);
		}
		/**
		* @brief Imprime el recorrido en posorden (izq, der, dato)
		*/
		void opPosOrder() {
			opPosOrder(attRoot);
		}
#pragma endregion
	};
};