#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include "ADTBinaryTree.h"
#include "ADTBinarySearchTree.h"

using std::ostream;
using std::cout;
using std::endl;
using std::vector;

using libBinaryTree::clsBinarySearchTree;

namespace libBinaryTree {
	template <class T>
	/**
	* @brief TAD para el dato en un nodo AVL
	*/
	struct strAVLData {
		T attContent; /*!< Contenido del usuario */
		int attHeight; /*!< Altura de este nodo */
		/**
		* @brief Crea una instancia de dato AVL
		* @param prmData Contenido del usuario
		*/
		strAVLData(T prmData) : attContent(prmData), attHeight(1) {

		}
		#pragma region operators
		/**
* @brief Envia el contenido del dato a un flujo de salida
* @param os Flujo de salida
* @param prmAVLData Dato a enviar
*/
		friend ostream& operator<<(ostream& os, const strAVLData prmAVLData) {
			os << prmAVLData.attContent << "(" << prmAVLData.attHeight << ")";
			return os;
		}
		/**
		* @brief Sobreescritura del operador ==
		* @param prmAVLDato Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator==(const strAVLData& prmAVLData) {
			return attContent == prmAVLData.attContent;
		}
		/**
		* @brief Sobreescritura del operador !==
		* @param prmAVLData Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator!=(const strAVLData& prmAVLData) {
			return attContent != prmAVLData.attContent;
		}
		/**
		* @brief Sobreescritura del operador <
		* @param prmAVLData Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator<(const strAVLData& prmAVLData) {
			return attContent < prmAVLData.attContent;
		}
		/**
		* @brief Sobreescritura del operador <=
		* @param prmAVLData Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator<=(const strAVLData& prmAVLData) {
			return attContent <= prmAVLData.attContent;
		}
		/**
		* @brief Sobreescritura del operador >
		* @param prmAVLData Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator>(const strAVLData& prmAVLData) {
			return attContent > prmAVLData.attContent;
		}
		/**
		* @brief Sobreescritura del operador <=
		* @param prmAVLData Otra instancia de dato AVL
		* @return true si se cumple la condicion de comparacion
		*/
		bool operator>=(const strAVLData& prmAVLData) {
			return attContent >= prmAVLData.attContent;
		}
		#pragma endregion
	};

	template <class T>
	/**
	* @brief Arbol Binario de Busqueda Balanceado AVL
	*/
	class clsBinaryAVLTree : public clsBinarySearchTree<strAVLData<T>> {
	protected:
		using typename clsBinarySearchTree<strAVLData<T>> ::strNode;
	#pragma region Operations
		#pragma region CRUD
		/**
		* @brief Se invoca cuando un nodo ha sido eliminado
		* @param prmFather Padre el nodo eliminado
		*/
		void opRemoved(strNode* prmFather) {
			// Camino desde padre hasta la raiz
			vector<strNode*> varBranch = this->opGetBranch(prmFather);
			// Obtener la rama desde la raiz hasta el padre del nodo eliminado
			opSwingTree(varBranch);
		}
		/**
		* @brief Se invoca cuando un nodo ha sido insertado
		* @param prmNode Nodo insertado
		*/
		void opInserted(strNode* prmNode) {
			// Camino desde padre hasta la raiz
			vector<strNode*> varBranch = this->opGetBranch(prmNode);
			// Obtener la rama desde la raiz hasta el padre del nodo eliminado
			opSwingTree(varBranch);
		}
		#pragma endregion
		#pragma region Rotations
		/**
		* @brief Rotacion a la izquierda
		* @param prmNode Nodo desbalanceado hacia la derecha
		* @return Nueva raiz del sub arbol balanceado
		*/
		strNode* opRotateLeft(strNode* prmNode) {
			// Realizar la rotacion y retornar la raiz del sub arbol balanceado
			return prmNode;
		}
		/**
		* @brief Rotacion a la derecha
		* @param prmNode Nodo desbalanceado hacia la izquierda
		* @return Nueva raiz del sub arbol balanceado
		*/
		strNode* opRotateRigth(strNode* prmNode) {
			// Realizar la rotacion y retornar la raiz del sub arbol balanceado
			return prmNode;
		}
		#pragma endregion
	private:
		#pragma region Utilities
		/**
		* @brief Actualiza la altura de un nodo con base en sus sub arboles
		* @param prmNode Nodo a actualizar
		*/
		void opUpdateHeight(strNode* prmNode) {
			// Actualizar la altura de n con base en altura(n->izq) y altura(n->der);			
		}
		/**
		* @brief Retorna la altura de un nodo
		* @param prmNode Nodo a procesar
		* @return Altura de prmNode 
		*/
		int opHeight(strNode* prmNode) {
			if (prmNode == nullptr) return 0;

			return prmNode->attData.attHeight;;
		}
		/**
		* @brief Retorna el factor de balanceo de un nodo
		* @param prmNode Nodo a procesar
		* @return Factor de balanceo: altura(prmNode->attRight) - altura(prmNode->attLeft)
		*/
		int opBalancingFactor(strNode* prmNode) {
			// Calcular y retornar el factor de balanceo
			return 0;
		}
		/**
		* @brief Verifica el factor de balanceo de un conjunto de nodos
		* Si algun nodo en el conjunto se encuentra desbalanceado,
		* realiza las rotaciones necesarias para balancearlo.
		* @param prmBranch Camino desde la raiz hasta un nodo posiblemente desbalanceado
		*/
		void opSwingTree(vector<strNode*> prmBranch) {
			// Recorrer el camino en orden inverso desde el último nodo
			// hasta la raiz
			// Para cada nodo x en branch:
			// Actualizar la altura de x  
			// actualizar_altura(x);
			// Calcular el factor de balanceo de x
			//int fb = factor_balanceo(x);   
			// Si fb = 2 o fb = -2, balancear x
			// Fin para 
		}
		#pragma endregion  
	#pragma endregion
	};
}