#pragma once
#include <iostream>
using std::cout;
using std::endl;

namespace libBinaryTree {
	template <class T>
	/**@brief Clase abstracta de un árbol binario*/
	class ADTBinaryTree {
#pragma region Attributes
	protected:
		/*@brief Estructura de nodo binario*/
		struct strNode {
			T attData; /*!< Dato almacenado >*/
			strNode* attLeft; /*!< Referencia al hijo izquierdo >*/
			strNode* attRight; /*!< Referencia al hijo derecho >*/
#pragma region OperationsOfStrNode
			/**
			* @brief Crea una instancia de un nodo de arbol binario
			* @param prmData Dato a almacenar en el nodo
			*/
			strNode(T prmData) :attData(prmData), attLeft(nullptr), attRight(nullptr) {}
			/**
			* @brief Verifica si el nodo es una hoja
			*/
			bool opItsLeaf() {
				return(attLeft == nullptr && attRight == nullptr);
			}
			/**
			* @brief Verifica si el nodo contiene el dato especificado
			* @param prmData Dato a verificar
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
		/**
		* @brief Destruye un nodo y su sub arbol, liberando la memoria asociada
		* @param prmNode Nodo a destruir
		*/
		void opDestroy(strNode* prmNode) {

			if (prmNode == nullptr) {
				return;
			}
			// Eliminar primero el sub arbol derecho
			opDestroy(prmNode->attRight);
			// Eliminar el sub arbol izquierdo
			opDestroy(prmNode->attLeft);
			// Eliminar este nodo
			delete prmNode;
		}
		/**
		* @brief Copia profunda de un nodo
		* @param prmNode Nodo a copiar
		* @return nuevo nodo y nuevos descendientes
		*/
		strNode* opDeepCopy(const strNode* prmNode) {
			if (prmNode == nullptr) {
				return nullptr;
			}
			//Crear un nuevo nodo con los datos de prmNode
			strNode* varNode = new strNode(prmNode->attData);
			// Copia profunda del sub arbol izquierdo
			varNode->attLeft = opDeepCopy(prmNode->attLeft);
			// Copia profunda del sub arbol derecho
			varNode->attRight = opDeepCopy(prmNode->attRight);
			return varNode;
		}
	#pragma endregion
	#pragma region ShowTree
		/**
		* @brief Recorrido en preorden a partir de Nodo (prmNode->attData, prmNode->attLeft, prmNode->attRight)
		* @param os Flujo de salida al cual se envia el dato del nodo
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
		* @brief Recorrido inorden a partir de n (prmNode->attLeft, prmNode->attData, prmNode->attRight)
		* @param os Flujo de salida al cual se envia el dato del nodo
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
		* @brief Recorrido posorden a partir de n (prmNode->attLeft, prmNode->attRight, prmNode->attData)
		* @param os Flujo de salida al cual se envia el dato del nodo
		* @param prmNode Nodo de inicio del recorrido
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
		/**
		* @brief 4. Constructor de mover
		* @param prmTree Referencia al arbol que se va a mover a esta instancia
		*/
		ADTBinaryTree(ADTBinaryTree&& prmTree) {
			std::swap(attRoot, prmTree.attRoot);
		}
		/**
		* @brief 3. Destructor
		* Libera los recursos (memoria) asignados al arbol
		*/
		~ADTBinaryTree() {
			opDestroy(attRoot);
			attRoot = nullptr;
		}
#pragma endregion
	#pragma region ShowTree
		/**
		* @brief Imprime el recorrido en preorden (dato, izquierdo, derecho)
		*/	
		void opShowPreOrder() {
			opPreOrder(attRoot);
		}
		/**
		* @brief Imprime el recorrido en inorden (izquierdo, dato, derecho)
		*/
		void opShowInOrder() {
			opInOrder(attRoot);
		}
		/**
		* @brief Imprime el recorrido en posorden (izquierdo, derecho, dato)
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
	#pragma endregion
	#pragma region Operators
	/**
	* @brief Operador de asignacion de copia
	* @param prmTree Arbol a copiar
	* @return Este arbol que contiene una copia de prmNode
	*/
		ADTBinaryTree& operator=(const ADTBinaryTree& prmTree) {

			// Si las instancias son diferentes, realizar la copia.
			if (this != &prmTree) {
				// Eliminar los nodos existentes de forma recursiva
				opDestroy(attRoot);
				// Obtener una copia de los nodos de la otra instancia
				this->attRoot = opDeepCopy(prmTree.attRoot);
			}
			return *this;
		}
	/**
		* @brief Operador de asignacion de mover
		* @param prmTree Referencia al arbol que se va a mover a esta instancia
		* @return Esta instancia
		*/
		ADTBinaryTree& operator=(ADTBinaryTree&& prmTree) noexcept {

			// Si las instancias son diferentes, tomar los nodos.
			if (this != &prmTree)
			{
				// Tomar la raiz del otro arbol e intercambiarla
				// Destruir los nodos de esta instancia
				opDestroy(this->attRoot);
				// Asignar nullptr a la raiz de esta instancia
				this->attRoot = nullptr;

				// Intercambiar la raiz de esta instancia
				std::swap(this->attRoot, prmTree.attRoot);
			}
			return *this;
		}
	#pragma endregion
#pragma endregion
	};
}