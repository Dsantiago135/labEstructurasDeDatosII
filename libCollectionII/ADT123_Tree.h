#pragma once

#include <iostream>
#include "ADTN_AryTree.h"

using std::cout;
using std::endl;

namespace libTree{
	template <class T>
	class clsADT123_Tree : public clsADTN_AryTree<T, 2> {
		using parent = clsADTN_AryTree<T, 2>;
		using nodo_n = typename parent::strNode;
		using dato_n = typename parent::strDataNode;
	protected:
		/**
		* @brief Inserta un nuevo dato en un nodo
		* @param prmPos_Father Posicion de insercion en el padre
		* @param prmFather Padre del nodo en el cual se va a insertar el dato
		* @param prmNode Nodo en el cual se va a insertar el dato
		* @param prmData Dato a insertar
		*/
		virtual nodo_n* opInsert(int prmPos_Father, nodo_n* prmFather, nodo_n* prmNode, T prmData) {
			// TODO
			return prmNode;
		}
		/**
		* @brief Se invoca luego de insertar un nuevo dato
		* @param prmNode Nodo en el cual se inserto el nuevo dato
		*/
		void opInserted(nodo_n* prmNode) {
			// TODO
		}
		/**
		* @brief Elimina un dato en un nodo
		* @param prmNode Nodo en el cual se puede encontrar el dato
		* @param prmData Dato a eliminar
		*/
		void opRemove(nodo_n* prmNode, T prmData) {
			// TODO
		}
		/**
		* @brief Se invoca luego de eliminar un dato
		* @param prmFather Padre del nodo en el cual se elimino el dato
		*/
		void opRemoved(nodo_n* prmFather) {

		}
	public:
		/**
		* @brief Inserta un nuevo dato en el arbol
		* @param prmData Dato a insertar
		*/
		void opInsert(T prmData) {
			// TODO 
		}
		/**
		* @brief Elimina un dato del arbol
		* @param prmData Dato a eliminar
		*/
		void opRemove(T prmData) {
			// TODO
		}
	};
};