#pragma once

#include <iostream>
#include <cstddef>
#include <vector>

using std::cout;
using std::endl;

using std::ostream;
using std::vector;

namespace libTree{
	template <class T, int data_limit>
	/**
	* @brief Arbol n-ario
	*/
	class ADTN_AryTree {

	protected:
		#pragma region Atributes and structs
		// Declaracion hacia adelante de un nodo
		struct strNode;
		/**
		* @brief Dato almacenado en un nodo de arbol-n
		*/
		struct strDataNode {
			T attValue; /*!< Valor almacenado */
			strNode* attLeft = nullptr; /*!< Apuntador al hijo izquierdo del dato */
			strNode* attRight = nullptr; /*!< Apuntador al hijo derecho del dato */
#pragma region OperatorsDataNode
			/**
* @brief Sobrecarga del operador ==
* @param rhs Dato a comparar
* @return true si el valor almacenado en este dato es igual al dato
*/
			bool operator == (T rhs) {
				return attValue == rhs;
			}
			/**
			* @brief Sobrecarga del operador =
			* @param rhs Dato a comparar
			* @return true si el valor almacenado en este dato es diferente al dato
			*/
			bool operator != (T rhs) {
				return attValue != rhs;
			}
			/**
			* @brief Sobrecarga del operador <
			* @param rhs Dato a comparar
			* @return true si el valor almacenado en este dato es menor al dato
			*/
			bool operator<(T rhs) {
				return attValue < rhs;
			}
			/**
			* @brief Sobrecarga del operador <
			* @param rhs Dato a comparar
			* @return true si el valor almacenado en este dato es menor o igual al dato
			*/
			bool operator <= (T rhs) {
				return attValue <= rhs;
			}
			/**
			* @brief Sobrecarga del operador <
			* @param rhs Dato a comparar
			* @return true si el valor almacenado en este dato es mayor al dato
			*/
			bool operator > (T rhs) {
				return attValue > rhs;
			}
			/**
			* @brief Sobrecarga del operador <
			* @param rhs Dato a comparar
			* @return true si el valor almacenado en este dato es mayor o igual al dato
			*/
			bool operator >= (T rhs) {
				return attValue >= rhs;
			}
#pragma endregion
		};
		/**
		* @brief Nodo
		*/
		struct StrNode {
			int attHeight = 1; /*!< Altura del sub arbol que comienza en este nodo */
			bool attLeaf = true; /*!< Verdadero si este nodo no tiene hijos */
			vector<strDataNode> attData; /*!< Lista de datos dentro de este nodo */
			StrNode* attFather = nullptr; /*!< Referencia al nodo padre */
			int attLimit = data_limit; /*!< Cantidad maxima de datos que se pueden almacenar en este nodo */
#pragma region OperationsNode
			/**
* @brief Verifica si este nodo contiene un dato
* @param dato a buscar
* @return true si este nodo contiene el dato, false en caso contrario
*/
			bool opContains(T prmData) {
				for (auto& d : attData) {
					if (d == prmData) {
						return true;
					}
				}
				return false;
			}
			int opCount() {
				return attData.size();
			}
			bool opItsFull() {
				return (attData.size() == data_limit);
			}
			bool opItsEmpty() {
				return attData.size() == 0;
			}
			strDataNode& ultimo() {
				return attData[attData.size() - 1];
			}
			strDataNode& primero() {
				return attData[0];
			}
			friend ostream& operator<<(ostream& os, strNode& n) {
				os << "[";
				for (auto d : n.attData) {
					os << " " << d.attValue;
				}
				os << " ]";
				return os;
			}
#pragma endregion

		};
		/**
		* @brief Raiz del arbol.
		*/
		StrNode* attRoot = nullptr;
		/** @brief Limite de datos en un nodo */
		int attLimit = data_limit;
		#pragma endregion

		ostream& opInorder(ostream& os, strNode* prmNode) {
			if (prmNode == nullptr) return os;

			for (size_t i = 0; i < prmNode->attData.size(); i++) {
				// Sub arbol izquierdo
				if (i == 0) {
					opInorder(os, prmNode->attData[i].attLeft);
				}
				//Dato
				os << prmNode->attData[i].attValue << " ";
				// Sub arbol derecho
				opInorder(os, prmNode->attData[i].attRight);
			}
			return os;
		}
	public:
		/**
		* @brief Recorrido inorden del arbol
		* @param os Fujo de salida
		* @return Flujo de salida luego de enviar el arbol
		*/
		virtual ostream& opInorder(ostream& os) {
			return this->opInorder(os, this->attRoot);
		}
	};
};