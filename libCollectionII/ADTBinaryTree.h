#pragma once
#include <iostream>

using std::cout;
using std::endl;

namespace libBinaryTree {
	template <class T>
	/*@brief Dato abstracto de un árbol binario*/
	class ADTBinaryTree {
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
				return(this->attData = prmData);
			}
#pragma endregion
		};
		/*@brief Nodo Raiz del árbol*/
		strNode* attRoot = nullptr;
#pragma endregion
#pragma region Operations
	protected:
	#pragma region CRUD
		/**
		* @brief Destruye un nodo y su sub arbol, liberando la memoria asociada
		* @param n Nodo a destruir
		*/
		void opDestroy(strNode* prmNode) {
			if (prmNode == nullptr) {
				return;
			}
			// Eliminar primero el sub arbol derecho
			destroy(prmNode->attRight);
			// Eliminar el sub arbol izquierdo
			destroy(prmNode->attLeft);
			// Elimonar este nodo
			delete prmNode;
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
	#pragma region Utilities
		/*
		@brief Va a el dato más a la izquierda del árbol
		@param Dato raiz del árbol o subarbol
		*/
		strNode* opGoExtremeLeft(strNode* prmNode) {
			//si el nodo no tiene un hijo izquierda se retorna a él mismo
			if (prmNode->attLeft == nullptr) return prmNode;
			//si el nodo si tiene un hijo izquierdo la función se llama a si misma dando como nodo raiz el hijo izquierdo
			return opGoExtremeLeft(prmNode->attLeft);
		}
		/*
		@brief Va a el dato más a la derecha del árbol
		@param Dato raiz del árbol o subarbol
		*/
		strNode* opGoExtremeRight(strNode* prmNode) {
			//si el nodo no tiene un hijo derecho se retorna a él mismo
			if (prmNode->attRight == nullptr) return prmNode;
			//si el nodo si tiene un hijo derecho la función se llama a si misma dando como nodo raiz el hijo derecho
			return opGoExtremeRight(prmNode->attRight);
		}
		/*
		*@brief Cópia profunda(completa) de un nodo 
		*@param Nodo a copiar
		*@return Nuevo nodo y nuevos descendientes
		*/
		strNode* opDeepCopy(const strNode* & prmNode) {
			if (prmNode == nullptr) return nullptr;
			//Crear un nuevo nodo con los datos de prmNode
			strNode* varNode = new strNode(prmNode->attData);
			//Copia profunda del subarbol izquierdo
			varNode->attLeft = opDeepCopy(prmNode->attLeft);
			//Copia profunda del subarbol derecho
			varNode->attRight = opDeepCopy(prmNode->attRight);
			return varNode;
		}
	#pragma endregion
	public:
	#pragma region Builder
		/*@brief Constructor por defecto del árbol binario
		*/
		ADTBinaryTree() :attRoot(nullptr) {}
		/*@brief Constructor de cópia de un árbol binario
		*@param árbol al que se le desea hacer una cópia
		*/
		ADTBinaryTree(const ADTBinaryTree & prmTree) {
			if (prmTree.attRoot != nullptr) attRoot = opDeepCopy(prmTree.attRoot);
		}
#pragma endregion
	#pragma region CRUD
		virtual bool opInsert(strNode* prmDadNode, strNode* prmNewNode) = 0;
		virtual void opRemove(strNode* prmNode, T prmData) = 0;
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
		int opHeightTree() {
			return 0;
		}
		/*
		* @brief Cuenta la cantidad de nodos es el árbol (en dado caso contará nodos con datos nulos)
		*/
		int opWeightTree(strNode prmNode) {
			if (prmNode == nullptr) return 0;
			return 1 + opWeightTree(prmNode.attLeft) + opWeightTree(prmNode.attRight);
		}
	#pragma endregion
#pragma endregion
	};
}