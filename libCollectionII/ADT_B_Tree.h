#pragma once

#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;
using std::ostream;
using std::vector;

namespace libTree {
	template <class T, int data_limit>
	/**
	* @brief Arbol n-ario
	*/
	class clsADT_B_Tree {
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
			bool operator < (T rhs) {
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
			/**
			* @brief Sobrecaraga del operador "<" para strDataNode a strDataNode
			*/
			bool operator < (strDataNode prmNode) {
				return attValue < prmNode.attValue;
			}
			/**
			* @brief Sobrecaraga del operador ">" para strDataNode a strDataNode
			*/
			bool operator > (strDataNode prmNode) {
				return attValue > prmNode.attValue;
			}
			/**
			* @brief Sobrecaraga del operador "<=" para strDataNode a strDataNode
			*/
			bool operator <= (strDataNode prmNode) {
				return attValue <= prmNode.attValue;
			}
			/**
			* @brief Sobrecaraga del operador ">=" para strDataNode a strDataNode
			*/
			bool operator >= (strDataNode prmNode) {
				return attValue >= prmNode.attValue;
			}
			/**
			* @brief Sobrecaraga del operador "==" para strDataNode a strDataNode
			*/
			bool operator == (strDataNode prmNode) {
				return attValue == prmNode.attValue;
			}
#pragma endregion
		};
		/**
		* @brief Nodo
		*/
		struct strNode {
			int attHeight = 1; /*!< Altura del sub arbol que comienza en este nodo */
			bool attLeaf = true; /*!< Verdadero si este nodo no tiene hijos */
			vector<strDataNode> attData; /*!< Lista de datos dentro de este nodo */
			strNode* attFather = nullptr; /*!< Referencia al nodo padre */
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
				/**
				* @brief Cuenta los datos almacenados en el vector del nodo
				* @return Número de datos almacenados
				*/
				int opCount() {
					return attData.size();
				}
				/**
				* @brief Determina si el vector del nodo esta lleno
				* @return true si está lleno o false si tiene espacio
				*/
				bool opItsFull() {
					return (attData.size() == data_limit);
				}
				/**
				* @brief Determina si el nodo esta vacio
				* @return True si no tiene ningun valor o false si tiene al menos 1
				*/
				bool opItsEmpty() {
					return attData.size() == 0;
				}
				/**
				* @brief Inserta un dato de tipo strDataNode en el vector del nodo
				* @param Dato strDataNode a insertar
				*/
				void opInsertInNode(strDataNode prmData) {
					//inserta un nodo binario en el arreglo del nodo N-ario
					attData.push_back(prmData);
					//ordena de menor a mayor el vector
					sort(attData.begin(), attData.end());
				}
				/**
				* @brief Convierte un dato de tipo T en un strDataNode y lo inserta en el vector del nodo
				* @param Dato T a insertar
				* @return
				*/
				void opInsertInNode(T prmData) {
					strDataNode varNode;
					varNode.attValue = T;
					//inserta un nodo binario en el arreglo del nodo N-ario
					attData.push_back(varNode);
					//ordena de menor a mayor el vector
					sort(attData.begin(), attData.end());
				}
				/**
				* @brief Va al ultimo dato del vector
				* @return Ultimo strDataNode almacenado en el vector
				*/
				strDataNode& opLast() {
					return attData[attData.size() - 1];
				}
				/**
				* @brief Va al primer dato del vector
				* @return Primer strDataNode almacenado en el vector
				*/
				strDataNode& opFirst() {
					return attData[0];
				}
				/**
				* @brief Sobrecarga del operador "<<" para strNode a strNode
				*/
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
		strNode* attRoot = nullptr;
		/**
		@brief Limite de datos en un nodo
		*/
		int attLimit = data_limit;
	#pragma endregion
	#pragma region Operations
	private:
		// Método para insertar un dato en el árbol
		void opInsert(strNode* prmNode, strDataNode prmData) {
			// Primera inserción: crea la raíz si no existe.
			if (attRoot == nullptr) {
				strNode* newRoot = new strNode;
				newRoot->opInsertInNode(prmData);
				attRoot = newRoot;
				return;
			}

			// Si el nodo es hoja.
			if (prmNode->attLeaf) {
				// Caso 1: nodo hoja con espacio.
				if (!prmNode->opItsFull()) {
					prmNode->opInsertInNode(prmData);  // Inserta y termina.
					return;
				}

				// Caso 2: nodo hoja lleno, debe dividirse.
				prmNode->opInsertInNode(prmData); // Inserta el dato antes de dividir.

				// Obtiene el índice del valor medio.
				int midIndex = prmNode->attData.size() / 2;
				strDataNode middleData = prmNode->attData[midIndex];

				// Crea nuevo nodo derecho y mueve los datos mayores.
				strNode* rightNode = new strNode;
				for (size_t i = midIndex + 1; i < prmNode->attData.size(); ++i) {
					rightNode->opInsertInNode(prmNode->attData[i]);
				}
				prmNode->attData.erase(prmNode->attData.begin() + midIndex, prmNode->attData.end());

				// Si no hay padre, crea uno.
				if (prmNode->attFather == nullptr) {
					strNode* newRoot = new strNode;
					newRoot->opInsertInNode(middleData); // Subir el valor medio.
					attRoot = newRoot; // Actualiza la raíz.

					newRoot->attLeaf = false;
					middleData.attLeft = prmNode;
					middleData.attRight = rightNode;

					prmNode->attFather = newRoot;
					rightNode->attFather = newRoot;
				}
				else {
					// Si hay padre, subir el valor medio recursivamente.
					middleData.attLeft = prmNode;
					middleData.attRight = rightNode;

					prmNode->attFather->attLeaf = false; // El padre ya no es hoja.
					opInsert(prmNode->attFather, middleData);
				}
			}
			else {
				// Si el nodo no es hoja, recorre los hijos para encontrar dónde insertar.
				for (auto& dataNode : prmNode->attData) {
					if (prmData.attValue < dataNode.attValue) {
						opInsert(dataNode.attLeft, prmData);
						return;
					}
				}
				// Si no se insertó, va al último hijo derecho.
				opInsert(prmNode->attData.back().attRight, prmData);
			}
		}
		T opSearch(strNode* prmNode, T prmData ) {

		}
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
		virtual ostream& opInorder(ostream& os) {
			return this->opInorder(os, this->attRoot);
		}
		/**
		* @brief Inserta un dato al árbol
		* @param Dato a insetar
		*/
		void opInsert(T prmData) {
			//guarda el dato en un nodo binario y lo inserta
			strDataNode varDataNode; 
			varDataNode.attValue = prmData; 
			opInsert(attRoot,varDataNode); 
		}
		/**
		* @brief Busca un dato en el árbol
		* @param Dato a buscar
		* @return el Dato que se obtuvo
		*/
		void opSearch(T prmData) {
			T varDato = opSearch(attRoot, prmData);
		}
		#pragma endregion 
	};
}