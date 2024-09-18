#pragma once
#include <iostream>
#include "ADTBinaryTree.h"

using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
	template <class T>
	/*@brief Árbol binario de busqueda (es una subclase de árbol binario)*/
	class clsBinarySearchTree : public ADTBinaryTree<T> {
	protected:
		using typename ADTBinaryTree<T>::strNode;
#pragma region Operations
	protected:
	#pragma region CRUD
		/*
*@brief Intenta insertar un nuevo dato a partir de prmDadNode
* @param prmDadNode Potencial padre del nodo
* @param prmNewNode Nuevo nodo
* @return true si prmNewNode pudo ser insertado
*/
		bool opInsert(strNode* prmDadNode, strNode* prmNewNode)override {
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
		*@brief Verificar si el nodo contiene al dato y lo elimina
		*@param Nodo padre del que en dado caso se quitará la referencia
		*@param Nodo que se eliminará
		*@param Dato a eliminar
		*/
		void opRemove(strNode* prmNode, T prmData)override {
			//Si el nodo es nulo el dato no está en el árbol
			if (prmNode == nullptr) return;
			//Si el nodo SI contiene el dato
			if (prmNode->opContain(prmData))
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

					return;

				}
				else {
					//Intercambio del dato del nodo a eliminar y del nodo más pequeño de la derecha

					return;
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
#pragma endregion
	#pragma region Utilities
		/**
		*@brief Va al dato más grande de la izquierda del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más grande de la izquierda de la raiz
		*/
		strNode* opGolargestOnTheLeft(strNode* prmNode) {
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode->attLeft == nullptr) return prmNode;
			//si el nodo si tiene un hijo  izquierdo se mueve a este y va lo más a la derecha posible
			prmNode = prmNode->attLeft;
			return opGoExtremeRight(prmNode);
		};
		/**
		*@brief Va al dato más pequeño de la derecha del arbol o subarbol
		*@param Dato raiz del que se iniciara la iteración
		*@return Dato más pequeño de la derecha de la raiz
		*/
		strNode* opGoSmallestOnTheRight(strNode* prmNode) {
			//si el nodo no tiene hijo izquierdo no retorna nada
			if (prmNode->attRight == nullptr) return prmNode;
			//si el nodo si tiene un hijo derecho se mueve a este y va lo más a la izquierda posible
			prmNode = prmNode->attRight;
			return opGoExtremeLeft(prmNode);
		};
#pragma endregion 	
	public:
	#pragma region CRUD
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
#pragma endregion
#pragma endregion
	};
}