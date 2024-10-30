#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>
#include "clsPerson.h"

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ostream;
using std::sort;
using std::string;
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
				size_t opCount() {
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
		/**
		* @brief Método para insertar un dato en el árbol
		* @param prmNode nodo donde se inserta el dato
		* @param prmData dato a insertar en el nodo
		* @param prmItsFather identificador si se esta insertando un dato o padre
		*/
		void opInsert(strNode* prmNode, strDataNode prmData, bool prmItsFather) {
			//si el nodo es nullo
			if (prmNode == nullptr) {
				strNode* newRoot = new strNode;
				newRoot->opInsertInNode(prmData);
				attRoot = newRoot;
				if (prmItsFather == true) {
					newRoot->attLeaf = false;
					prmData.attLeft->attFather = newRoot;
				}
				return;
			}
			//el nodo es una hoja o es una inserción de un padre
			if (prmNode->attLeaf || prmItsFather) {
				//el nodo tiene espacio
				if (!prmNode->opItsFull()) {
					if (prmItsFather == true) 
					{
						prmNode->attLeaf = false;
						prmData.attLeft->attFather = prmNode;
					}
					return prmNode->opInsertInNode(prmData);
				}
				//el nodo no tiene espacio
				else {
					//se inserta el dato y colapsa el arreglo
					prmNode->opInsertInNode(prmData);
					//se obtiene la posición del dato medio
					size_t varMiddle = (prmNode->opCount() - 1) / 2;
					//se crea el hermano que almacenara los datos mayores al dato medio
					strNode* varBrotherNode = new strNode;
					//transferencia de datos
					for (size_t i = varMiddle + 1; i < prmNode->opCount(); i++) {
						varBrotherNode->opInsertInNode(prmNode->attData[i]);
					}
					//eliminación de los datos ya pasados
					prmNode->attData.erase(prmNode->attData.begin() + varMiddle + 1, prmNode->attData.end());
					//actualización de referencias
					prmNode->attData[varMiddle].attLeft = prmNode;
					prmNode->attData[varMiddle].attRight = varBrotherNode;
					opInsert(prmNode->attFather,prmNode->attData[varMiddle], true);
					prmNode->attData.pop_back();
					varBrotherNode->attFather = prmNode->attFather;
					prmNode->attFather->attHeight++;
					return;
				}
			}
			//si el nodo no es hoja se busca al nodo correspondiente
			else {
				//el dato es menor al dato menor del nodo
				if (prmData<prmNode->opFirst()) {
					return opInsert(prmNode->opFirst().attLeft, prmData, false);
				}
				//el dato es mayor al dato mayor del nodo
				else if (prmData>prmNode->opLast()) {
					return opInsert(prmNode->opLast().attRight, prmData, false);
				}
				//la posición del dato es entre 2 datos del nodo
				else {
					//recorre el vector buscardo el dato que apunte al nodo necesario(donde se insertará el dato)
					for (int i = 0; prmData < prmNode->attData[i]; i++) {
						if (prmData < prmNode->attData[i]) {
							return opInsert(prmNode->attData[i].attLeft, prmData, false);
						}
					}
				}
			}
		}
		/*
		* @brief Itera en el árbol bucando el dato y al encontrarlo lo muestra por pantalla
		* @param prmNode Nodo donde se buscará el dato
		* @param prmData dato a buscar
		*/
		void opSearch(strNode* prmNode, int prmData) {
			//si el nodo es nulo no haga nada 
			if (prmNode == nullptr) return ;
			//el dato esta en el nodo
			if (prmNode->opContains(prmData)) {
				for (int i = 0;i<prmNode->opCount();i++) {
					if (prmNode->attData[i] == prmData) {
						cout<<"Dato encontrado ;D" << endl;
						cout<<prmNode->attData[i].attValue<<endl;
						return;
					}
				}
			}
			//el dato no esta en el nodo
			else {
				//el dato a buscar es menor al primer dato del arreglo
				if (prmNode->opFirst() > prmData) {
					return opSearch(prmNode->opFirst().attLeft, prmData);
				}
				//el dato a buscar es mayor al ultimo dato del arreglo
				else if (prmNode->opLast() < prmData) {
					return opSearch(prmNode->opLast().attRight, prmData);
				}
				//el dato a buscar esta en un nodo hijo intermedio
				else {
					for (int i = 1; i < prmNode->opCount(); i++) {
						if (prmNode->attData[i] > prmData) {
							return opSearch(prmNode->attData[i].attLeft, prmData);
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
			opInsert(attRoot,varDataNode,false);
		}
		/**
		* @brief Busca un dato en el árbol
		* @param Dato a buscar (en este caso se usa int porque se usara la identificación de una persona)
		* @return el Dato que se obtuvo 
		*/
		void opSearch(int prmData) {
			opSearch(attRoot, prmData);
		}
		/**
		* @brief llena un árbol con un archivo csv (debido al requerimiento del proyecto se usaran objetos persona para llenar el árbol)
		* @param prmFilePath Archivo a deserializar
		*/
		void opDeserialize(string prmFilePath) {
			ifstream archivo(prmFilePath);
			string linea;
			char delimitador = ';';
			if (!archivo.is_open()) {
				cout << "No se pudo abrir el archivo." << endl;
				return;
			}
			// Leemos todas las líneas
			while (getline(archivo, linea))
			{
				std::istringstream stream(linea); // Convertir la cadena a un stream 
				string identificacion, nombre, apellido, telefono, direccion, longitud, latitud;
				// Extraer todos los valores de esa fila
				getline(stream, identificacion, delimitador);
				getline(stream, nombre, delimitador);
				getline(stream, apellido, delimitador);
				getline(stream, telefono, delimitador);
				getline(stream, direccion, delimitador);
				getline(stream, longitud, delimitador);
				getline(stream, latitud, delimitador);
				int intIdentificacion = std::stoi(identificacion); // Convierte el string a un int
				clsPerson varPerson(intIdentificacion, nombre, apellido, telefono, direccion, longitud, latitud);
				opInsert(varPerson);
			}
			archivo.close();
		}
		#pragma endregion 
	};
}