#pragma once
#include <iostream>
#include "ADTBinaryTree.h"
#include <stack>
#include <string>

using libBinaryTree::ADTBinaryTree;

namespace libBinaryTree {
    template <class T>
    /*@brief Árbol binario de Expresiones (es una subclase de árbol binario)*/
    class clsBinaryExpressionTree : public ADTBinaryTree<T> {
    protected:
        using typename ADTBinaryTree<T>::strNode;

    public:
        virtual void opInsert(T prmData) override {
            // Implementación básica: inserta como un nuevo nodo
            strNode* varNewNode = new strNode(prmData);
            if (this->opItsEmpty()) {
                this->attRoot = varNewNode;
            }
            else {
                // En un árbol de expresiones, podrías definir la lógica de inserción más específica
                cout << "Insertar " << prmData << endl;
                // Aquí puedes decidir cómo insertar nodos en el árbol de expresión.
                // Por simplicidad, se insertará en el lado izquierdo
                if (this->attRoot->attLeft == nullptr) {
                    this->attRoot->attLeft = varNewNode;
                }
                else {
                    this->attRoot->attRight = varNewNode;
                }
            }
        }

        virtual void opRemove(T prmData) override {
            // Implementación básica: no se puede eliminar un nodo en esta versión
            cout << "Eliminar " << prmData << " no está implementado en este árbol de expresiones." << endl;
        }

        void opShowTree() {
            // Mostrar el árbol como una expresión infija
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
