#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cctype>  // Para verificar si es un operando u operador

using std::string;
using std::stack;
using std::cout;
using std::endl;

class clsExpressionTree {

private:
	/**
	* @brief Nodo binario
	*/
	// Definici�n del nodo del �rbol
	struct Node {
		char attData; /*!< Caracter almacenado */
		Node* attLeft; /*!< Referencia al hijo izquierdo */
		Node* attRight; /*!< Referencia al hijo derecho */

		/**
		* @brief Crea una instancia de un nodo de arbol binario
		* @param attData Caracter a almacenar en el nodo
		*/
		Node(char c) : attData(c), attLeft(nullptr), attRight(nullptr) {}
	};

public:

	/**
	* @brief Constructor Arbol de Expresion
	* @param prmExpression Expresion a convertir en el arbol
	*/
	clsExpressionTree(string prmExpression) {
		// Construir el �rbol de expresi�n
		Node* root = buildExpressionTree(prmExpression);

		if (root) {
			// Recorrer el �rbol en orden
			cout << "El arbol de expresion esta en orden: ";
			opInOrder(root);
			cout << endl;

		}
	}

	/**
	* @brief Permite verificar si c es un operador
	* @return true si c es un operador
	*/
	// Funci�n para verificar si un car�cter es un operador
	bool isOperator(char c) {
		return (c == '+' || c == '-' || c == '*' || c == '/');
	}

	/**
	* @brief Permite identificar la prioridad de los operadores
	* @return 1 si el operador es de mayor prioridad o 2 si es de menor prioridad
	*/
	// Funci�n para definir la prioridad de los operadores
	int getPriority(char c) {
		if (c == '+' || c == '-') return 1;
		if (c == '*' || c == '/') return 2;
		return 0;
	}

	/**
	* @brief Funcion que construye el arbol de expresion
	* @param str Expresion a convertir en el arbol
	* @return root Arbol de expresion
	*/
	// Funci�n para construir el �rbol de expresi�n
	Node* buildExpressionTree(const string& prmStr) {
		stack<Node*> nodeStack;  // Pila para nodos
		stack<char> operatorStack; // Pila para operadores
		Node* root = nullptr;
		int openParentheses = 0;  // Contador de par�ntesis abiertos

		for (size_t i = 0; i < prmStr.length(); ++i) {
			char c = prmStr[i];

			// Ignorar espacios
			if (isspace(c)) continue;

			if (c == '(') {
				// Par�ntesis abierto
				operatorStack.push(c);
				openParentheses++;
			}
			else if (c == ')') {
				// Par�ntesis cerrado
				if (openParentheses <= 0) {
					// Parentesis no balanceados
					cout << "Parentesis no balanceados" << endl;
					freeTree(root);  // Liberar el �rbol
					return nullptr;  // Terminar el proceso
				}
				while (!operatorStack.empty() && operatorStack.top() != '(') {
					char op = operatorStack.top();
					operatorStack.pop();

					// Crear nuevo nodo para el operador
					Node* newNode = new Node(op);
					newNode->attRight = nodeStack.top(); nodeStack.pop();
					newNode->attLeft = nodeStack.top(); nodeStack.pop();
					nodeStack.push(newNode);

				}
				operatorStack.pop(); // Quitar '('
				openParentheses--;
			}
			else if (isdigit(c) || isalpha(c)) {
				// Es un operando
				nodeStack.push(new Node(c));
			}
			else if (isOperator(c)) {
				// Es un operador
				while (!operatorStack.empty() &&
					getPriority(operatorStack.top()) >= getPriority(c)) {
					char op = operatorStack.top();
					operatorStack.pop();

					// Crear nuevo nodo para el operador
					Node* newNode = new Node(op);
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

			Node* newNode = new Node(op);
			newNode->attRight = nodeStack.top(); nodeStack.pop();
			newNode->attLeft = nodeStack.top(); nodeStack.pop();
			nodeStack.push(newNode);
		}

		// La ra�z ser� el �nico nodo en la pila de nodos
		if (!nodeStack.empty()) {
			root = nodeStack.top();
		}

		return root;
	}


	/**
	* @brief Imprime el recorrido en inorden (izq, dato, der)
	* @param prmNode Raiz del arbol de expresion
	*/
	// Funci�n para recorrer el �rbol en orden y mostrar la expresi�n
	void opInOrder(Node* prmRoot) {
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
	// Liberar memoria del �rbol
	void freeTree(Node* prmRoot) {
		if (prmRoot) {
			freeTree(prmRoot->attLeft);
			freeTree(prmRoot->attRight);
			delete prmRoot;
		}
	}
};