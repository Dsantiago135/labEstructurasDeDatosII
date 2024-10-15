#pragma once

#include <iostream>
#include "ADTN_AryTree.h"

using std::cout;
using std::endl;

namespace arbol {
	template <class T>
	class arbol_123 : public arbol_n<T, 2> {
		using parent = arbol_n<T, 2>;
		using nodo_n = typename parent::nodo_n;
		using dato_n = typename parent::dato_n;
	protected:

		/**
		* @brief Inserta un nuevo dato en un nodo
		* @param pos_padre Posicion de insercion en el padre
		* @param padre Padre del nodo en el cual se va a insertar el dato
		* @param n Nodo en el cual se va a insertar el dato
		* @param dato Dato a insertar
		*/
		virtual nodo_n* insertar(int pos_padre, nodo_n* padre, nodo_n* n, T dato) {
			// TODO
			return n;
		}


		/**
		* @brief Se invoca luego de insertar un nuevo dato
		* @param n Nodo en el cual se inserto el nuevo dato
		*/
		void insertado(nodo_n* n) {
			// TODO
		}

		/**
		* @brief Elimina un dato en un nodo
		* @param n Nodo en el cual se puede encontrar el dato
		* @param dato Dato a eliminar
		*/
		void eliminar(nodo_n* n, T dato) {
			// TODO
		}

		/**
		* @brief Se invoca luego de eliminar un dato
		* @param padre Padre del nodo en el cual se elimino el dato
		*/
		void eliminado(nodo_n* padre) {

		}

	public:


		/**
		* @brief Inserta un nuevo dato en el arbol
		* @param dato Dato a insertar
		*/
		void insertar(T dato) {
			// TODO 
		}

		/**
		* @brief Elimina un dato del arbol
		* @param dato Dato a eliminar
		*/
		void eliminar(T dato) {
			// TODO
		}
	};
};

#endif
