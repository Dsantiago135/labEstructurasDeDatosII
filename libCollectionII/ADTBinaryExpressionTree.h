#pragma once
#include <iostream>
#include "ADTBinaryTree.h"
#include <stack>
#include <string>

using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
    template <class T>
    /*@brief �rbol binario de Expresiones (es una subclase de �rbol binario)*/
    class clsBinaryExpressionTree : public ADTBinaryTree<T> {
    protected:
        using typename ADTBinaryTree<T>::strNode;

    public:
        virtual void opInsert(T prmData) override {
            // Implementaci�n b�sica: inserta como un nuevo nodo
            strNode* varNewNode = new strNode(prmData);
            if (this->opItsEmpty()) {
                this->attRoot = varNewNode;
            }
            else {
                // En un �rbol de expresiones, podr�as definir la l�gica de inserci�n m�s espec�fica
                cout << "Insertar " << prmData << endl;
                // Aqu� puedes decidir c�mo insertar nodos en el �rbol de expresi�n.
                // Por simplicidad, se insertar� en el lado izquierdo
                if (this->attRoot->attLeft == nullptr) {
                    this->attRoot->attLeft = varNewNode;
                }
                else {
                    this->attRoot->attRight = varNewNode;
                }
            }
        }

        virtual void opRemove(T prmData) override {
            // Implementaci�n b�sica: no se puede eliminar un nodo en esta versi�n
            cout << "Eliminar " << prmData << " no est� implementado en este �rbol de expresiones." << endl;
        }

        void opShowTree() {
            // Mostrar el �rbol como una expresi�n infija
            std::stack<strNode*> stack;
            strNode* curr = this->attRoot;

            while (curr != nullptr || !stack.empty()) {
                while (curr != nullptr) {
                    stack.push(curr);
                    curr = curr->attLeft;
                }

                curr = stack.top();
                stack.pop();

                cout << curr->attData << " ";

                curr = curr->attRight;
            }
            cout << endl;
        }
    };
}
