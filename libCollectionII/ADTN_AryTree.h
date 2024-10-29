#pragma once

#include <iostream>
#include <cstddef>
#include <vector>
#include<algorithm>

using std::cout;
using std::endl;

using std::sort;
using std::ostream;
using std::vector;

namespace libTree{
	template <class T, int data_limit>
	/**
	* @brief Arbol n-ario
	*/
	class clsADTN_AryTree {
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
			/**/
			bool operator < (strDataNode prmNode) {
				return attValue < prmNode.attValue;
			}
			bool operator > (strDataNode prmNode) {
				return attValue > prmNode.attValue;
			}
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
			int opCount() {
				return attData.size();
			}
			bool opItsFull() {
				return (attData.size() == data_limit);
			}
			bool opItsEmpty() {
				return attData.size() == 0;
			}
			void opInsertInNode(strDataNode prmData) {
				//inserta un nodo binario en el arreglo del nodo N-ario
				attData.push_back(prmData);
				//ordena de menor a mayor el vector
				sort(attData.begin(), attData.end());
			}
			void opInsertInNode(T prmData) {
				strDataNode varNode;
				varNode.attValue = T;
				//inserta un nodo binario en el arreglo del nodo N-ario
				attData.push_back(varNode);
				//ordena de menor a mayor el vector
				sort(attData.begin(), attData.end());
			}
			strDataNode& opLast() {
				return attData[attData.size() - 1];
			}
			strDataNode& opFirst() {
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
		strNode* attRoot = nullptr;
		/** @brief Limite de datos en un nodo */
		int attLimit = data_limit;
		#pragma endregion
		void opInsert(strNode* prmNode, strDataNode prmData) {
			//si el nodo es nulo se crea un nodo y pone como raiz (el unico momento cuando nodo es nulo es cuando no hay raiz)//
			if (prmNode == nullptr) {
				strNode* varNewNode = new strNode;
				varNewNode->opInsertInNode(prmData);
				this->attRoot = varNewNode;
				return;
			}
			//el nodo tiene espacio
			if (prmNode->attLeaf) {
				if (!prmNode->opItsFull()) {
					prmNode->opInsertInNode(prmData);
					return;
				}
			}
			//el nodo esta lleno
			else {
				//el dato es menor al primer valor del nodo
				if (prmData<prmNode->opFirst()) {
					//el primer nodo no tiene izquierdo
					if (prmNode->opFirst().attLeft == nullptr) {
						strNode* varNode = new strNode;
						prmNode->attData[0].attLeft = varNode;
						prmNode->attHeight++;
						prmNode->attLeaf = false;
						varNode->attFather = prmNode;
						opInsert(prmNode->opFirst().attLeft, prmData);
						return;
					}
					//ya hay un hijo a donde insertar
					else {
						opInsert(prmNode->opFirst().attLeft, prmData);
						return;
					}
				}
				//el dato es mayor al ultimo valor del nodo
				else if (prmData > prmNode->opLast()) {
					//el ultimo nodo no tiene derecho
					if (prmNode->opLast().attRight == nullptr) {
						strNode* varNode = new strNode;
 						prmNode->opLast().attRight = varNode;
						prmNode->attHeight++;
						prmNode->attLeaf = false;
						varNode->attFather = prmNode;
						opInsert(prmNode->opLast().attRight, prmData);
						return;
					}
					//ya hay un hijo a donde insertar
					else {
						opInsert(prmNode->opLast().attRight, prmData);
						return;
					}
				}
				//el dato es mayor al primer valor del nodo y menor al ultimo valor del nodo
				else  {
					//busca el nodo al que corresponde
					for (int i = 1; i < prmNode->attData.size()-1; i++) {
						if (prmData<prmNode->attData[i]){
							//el nodo hijo no existe
							if(prmNode->attData[i].attLeft==nullptr) {
								strNode* varNode = new strNode;
								prmNode->attData[i].attLeft = varNode;
								prmNode->attData[i-1].attRight= varNode;
								prmNode->attHeight++;
								prmNode->attLeaf = false;
								varNode->attFather = prmNode;
								opInsert(prmNode->attData[i].attLeft, prmData);
								return;
							}
							//el nodo hijo existe
							else {
								return opInsert(prmNode->attData[i].attLeft, prmData);
							}
						}
					}
				}
			}
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
		void opInsert(T prmData) {
			strDataNode varNewDataNode;
			varNewDataNode.attValue = prmData;
			opInsert(attRoot, varNewDataNode);
		}
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