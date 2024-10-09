#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cctype>  // Para verificar si es un operando u operador
#include "ADTBinaryTree.h"

using std::string;
using std::stack;
using std::cout;
using std::endl;

namespace libBinaryTree {
	class clsBinaryExpressionTree : public ADTBinaryTree<char> {
		using typename ADTBinaryTree<char>::strNode;
	public:
		/**
		* @brief Constructor Arbol de Expresion
		* @param prmExpression Expresion a convertir en el arbol
		*/
		clsBinaryExpressionTree(string prmExpression) {
			// Construir el árbol de expresión
			strNode* varRoot = opbuildExpressionTree(prmExpression);
			this->attRoot = varRoot;
			if (varRoot) {
				// Recorrer el árbol en orden
				cout << "El arbol de expresion esta en orden: ";
				opInOrder(varRoot);
				cout << endl;
			}
		}
		/**
		* @brief Permite verificar si c es un operador
		* @return true si c es un operador
		*/
		// Función para verificar si un carácter es un operador
		bool isOperator(char c) {
			return (c == '+' || c == '-' || c == '*' || c == '/');
		}
		/**
		* @brief Permite identificar la prioridad de los operadores
		* @return 1 si el operador es de mayor prioridad o 2 si es de menor prioridad
		*/
		// Función para definir la prioridad de los operadores
		int opGetPriority(char c) {
			if (c == '+' || c == '-') return 1;
			if (c == '*' || c == '/') return 2;
			return 0;
		}
		/**
		* @brief Funcion que construye el arbol de expresion
		* @param str Expresion a convertir en el arbol
		* @return root Arbol de expresion
		*/
		// Función para construir el árbol de expresión
		strNode* opbuildExpressionTree(const string& prmStr) {
			stack<strNode*> nodeStack;  // Pila para nodos
			stack<char> operatorStack; // Pila para operadores
			strNode* root = nullptr;
			int openParentheses = 0;  // Contador de paréntesis abiertos

			for (size_t i = 0; i < prmStr.length(); ++i) {
				char c = prmStr[i];

				// Ignorar espacios
				if (isspace(c)) continue;

				if (c == '(') {
					// Paréntesis abierto
					operatorStack.push(c);
					openParentheses++;
				}
				else if (c == ')') {
					// Paréntesis cerrado
					if (openParentheses <= 0) {
						// Parentesis no balanceados
						cout << "Parentesis no balanceados" << endl;
						opFreeTree(root);  // Liberar el árbol
						return nullptr;  // Terminar el proceso
					}
					while (!operatorStack.empty() && operatorStack.top() != '(') {
						char op = operatorStack.top();
						operatorStack.pop();

						// Crear nuevo nodo para el operador
						strNode* newNode = new strNode(op);
						newNode->attRight = nodeStack.top(); nodeStack.pop();
						newNode->attLeft = nodeStack.top(); nodeStack.pop();
						nodeStack.push(newNode);

					}
					operatorStack.pop(); // Quitar '('
					openParentheses--;
				}
				else if (isdigit(c) || isalpha(c)) {
					// Es un operando
					nodeStack.push(new strNode(c));
				}
				else if (isOperator(c)) {
					// Es un operador
					while (!operatorStack.empty() &&
						opGetPriority(operatorStack.top()) >= opGetPriority(c)) {
						char op = operatorStack.top();
						operatorStack.pop();

						// Crear nuevo nodo para el operador
						strNode* newNode = new strNode(op);
						newNode->attRight = nodeStack.top(); nodeStack.pop();
						newNode->attLeft = nodeStack.top(); nodeStack.pop();
						nodeStack.push(newNode);
					}
					operatorStack.push(c); // Agregar operador a la pila
				}
			}

			// Procesar cualquier operador restante
			while (!operatorStack.empty()) {
				char op = operatorStack.top();
				operatorStack.pop();

				strNode* newNode = new strNode(op);
				newNode->attRight = nodeStack.top(); nodeStack.pop();
				newNode->attLeft = nodeStack.top(); nodeStack.pop();
				nodeStack.push(newNode);
			}

			// La raíz será el único nodo en la pila de nodos
			if (!nodeStack.empty()) {
				root = nodeStack.top();
			}

			return root;
		}
		/**
		* @brief Imprime el recorrido en inorden (izq, dato, der)
		* @param prmNode Raiz del arbol de expresion
		*/
		// Función para recorrer el árbol en orden y mostrar la expresión
		void opInOrder(strNode* prmRoot) {
			if (prmRoot == nullptr) {
				return;
			}

			//Invocar recursivamente inorden en el hijo izquierdo
			opInOrder(prmRoot->attLeft);
			cout << " " << prmRoot->attData;
			//Invocar recursivamente inorden en el hijo derecho
			opInOrder(prmRoot->attRight);
		}
		/**
		* @brief Borra el arbol para liberar memoria
		* @param prmNode Raiz del arbol de expresion
		*/
		// Liberar memoria del árbol
		void opFreeTree(strNode* prmRoot) {
			if (prmRoot) {
				opFreeTree(prmRoot->attLeft);
				opFreeTree(prmRoot->attRight);
				delete prmRoot;
			}
		}
		void opShowExpressionTree() {
			opShowPreOrder();
			opShowInOrder();
			opShowPosOrder();
		}
	};
}