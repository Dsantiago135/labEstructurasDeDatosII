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
				return(this->attData = prmData);
			}
#pragma endregion
		};
		/*@brief Nodo Raiz del árbol*/
		strNode* attRoot = nullptr;
#pragma endregion
#pragma region Operations
	private:
		/**
		* @brief Intenta insertar un nuevo dato a partir de prmDadNode
		* @param prmDadNode Potencial padre del nodo
		* @param prmNewNode Nuevo nodo
		* @return true si prmNewNode pudo ser insertado
		*/
		bool opInsert(strNode* prmDadNode, strNode* prmNewNode) {
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
		* @brief Verificar si el nodo contiene al dato y lo elimina
		* @param Nodo a verficar
		* @param Dato a eliminar
		*/
		void opRemove(strNode* prmNode,T prmData) {
			//Si el nodo es nulo el dato no está en el árbol
			if (prmNode== nullptr) return;
			//Si el nodo SI contiene el dato
			if (prmNode->attData == prmData)
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
					prmNode->attData = opGolargestOnTheLeft(prmNode)->attData;
				}
				else {
					//Intercambio del dato del nodo a eliminar y del nodo más pequeño de la derecha
					prmNode->attData = opGoSmallestOnTheRight(prmNode)->attData;
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
		/**
		* @brief Recorrido preorden a partir de prmNode (prmNode->dato, prmNode->izq, prmNode->der)
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
		* @brief Recorrido inorden a partir de prmNode (prmNode->izq, prmNode->dato, prmNode->der)
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
		*@brief Recorrido Posorden a partir de prmNode (prmNode->izq, prmNode->der, prmNode->dato)
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
		/*
		@brief Va a el dato más a la izquierda del árbol
		@param Dato raiz del árbol o subarbol
		*/
		strNode opGoExtremeLeft(strNode prmNode) {
			//si el nodo no tiene un hijo izquierda se retorna a él mismo
			if (prmNode->attLeft == nullptr) return prmNode;
			//si el nodo si tiene un hijo izquierdo la función se llama a si misma dando como nodo raiz el hijo izquierdo
			return opGoExtremeLeft(prmNode->attLeft);
		}
		/*
		@brief Va a el dato más a la derecha del árbol
		@param Dato raiz del árbol o subarbol
		*/
		strNode opGoExtremeRight(strNode prmNode) {
			//si el nodo no tiene un hijo derecho se retorna a él mismo
			if (prmNode->attRight == nullptr) return prmNode;
			//si el nodo si tiene un hijo derecho la función se llama a si misma dando como nodo raiz el hijo derecho
			return opGoExtremeRight(prmNode->attRight);
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
			strNode* varNewNode = new strNode(prmData);

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
		/*
		* @brief Elimina un dato del árbol
		* @param Dato a eliminar
		*/
		void opRemove(T prmData) {
			if (opItsEmpty())return;
			opRemove(attRoot, prmData);
		}
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
		/**
		*@brief Va al dato más grande de la izquierda del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más grande de la izquierda de la raiz
		*/
		strNode opGolargestOnTheLeft(strNode prmNode){
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode.attLeft == nullptr) return;
			//si el nodo si tiene un hijo  izquierdo se mueve a este y va lo más a la derecha posible
			prmNode = prmNode.attLeft; 
			return opGoExtremeRight(prmNode);
		}
		/**
		*@brief Va al dato más pequeño de la derecha del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más pequeño de la derecha de la raiz
		*/
		strNode opGoSmallestOnTheRight(strNode prmNode) {
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode.attRight == nullptr) return;
			//si el nodo si tiene un hijo derecho se mueve a este y va lo más a la izquierda posible
			prmNode = prmNode.attRight;
			return opGoExtremeLeft(prmNode);
		}
#pragma endregion
	};
};