/**
* @file
* @brief TAD Grafo
* @author Erwin Meza Vega
* @copyright MIT License
*/

#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::ostream;

using std::endl;
namespace grafo {

    /**
    * @brief Grafo denso mediante matriz de adyacencia
    * @tparam T Tipo de datos que almacena el grafo
    * @tparam TP Tipo de datos del peso asociado a los arcos
    */
    template <class T, class TP = int>
    class denso {
    public:
        /**
        * @brief Crea una nueva instancia de un grafo
        * @param dirigido true si el grafo es dirigido, false en caso contrario
        */
        denso(bool dirigido = false) : dirigido(dirigido) {

        }
        /**
        * @brief Adiciona un nuevo nodo al grafo
        * @param dato Dato a almacenar dentro del nodo
        */
        void agregar_nodo(T dato) {
            // 1. Verificar si el dato ya existe
            if (existe(dato)) return;

            // PRE: El dato no existe
            // 2. Adicionar el nuevo dato
            nodos.push_back(dato);

            // 3. Aumentar la matriz de adyacencia
            size_t n = conteo();

            // 3.1 Aumentar una fila a la matriz
            adyacencia.resize(n);

            // 3.2 Para cada fila, adicionar una columna
            for (auto& fila : adyacencia) fila.resize(n);

        }
        /**
        * @brief Conecta dos nodos
        * @param inicio Nodo inicial
        * @param fin Nodo final
        * @param peso Peso de la conexion
        */
        void conectar(T inicio, T fin, TP peso) {
            int i = llave(inicio);
            int j = llave(fin);

            // Verificar si los dos nodos existen
            if (i == no_existe() || j == no_existe()) {
                return;
            }
            // Asignar el peso al arco inicio -> fin
            adyacencia[i][j] = peso;
            if (!dirigido) {
                // Si el grafo es no dirigido, asignar el peso al arco fin -> inicio
                adyacencia[j][i] = peso;
            }
        }
        /**
        * @brief Permite obtener la cantidad de nodos
        * @return Cantidad de nodos dentro del grafo
        */
        size_t conteo() {
            return nodos.size();
        }
        /**
        * @brief Permite verificar si el grafo contiene un dato
        * @param dato Dato a buscar
        * @return true si el dato se encuentra en el grafo, false en caso contrario
        */
        bool existe(T dato) {
            return llave(dato) != no_existe();
        }
        /**
        * @brief Elimina el nodo que contiene el dato y sus conexiones
        * @param dato Dato a eliminar
        */
        void eliminar(T dato) {


            int k = llave(dato);

            // Verificar si el dato existe
            if (k == no_existe()) return;

            // 1. Borrar la columna en cada fila
            for (auto& fila : adyacencia) fila.erase(fila.begin() + k);

            // 2. Borrar la fila      
            adyacencia.erase(adyacencia.begin() + k);

            // 3. Borrar el dato
            nodos.erase(nodos.begin() + k);
        }
        /**
        * @brief Retorna una llave inexistente
        * @return -1 (indicador que la llave no existe)
        */
        inline auto no_existe() {
            return -1;
        }
        /**
        * @brief Sobrecarga del operador de flujo de salida de datos
        * @param os Flujo de salida de datos
        * @param g Grafo a enviar al flujo de salida
        * @return Flujo de salida al cual se ha enviado el grafo
        */
        friend ostream& operator<<(ostream& os, denso& g) {
            if (g.conteo() == 0) {
                return os;
            }

            size_t n = g.conteo();

            for (size_t i = 0; i < n; i++) {
                os << g.nodos[i] << " [";
                for (size_t j = 0; j < n; j++) {
                    os << " " << g.adyacencia[i][j];
                }
                os << " ]" << endl;
            }

            return os;
        }
        /**
        *
        */
        bool conectado(T inicio, T fin) {
            TP p{0};
            return (peso(inicio, fin) != p);
        }
        /**
        *
        */
        TP peso(T inicio, T fin) {
            TP p{0};
            auto i = llave(inicio);
            auto j = llave(fin);
            if (i == no_existe() || j == no_existe()) return p;

            return adyacencia[i][j];
        }
        /**
        * @brief Busca la llave que le corresponde a un dato
        * @param dato a buscar
        * @return Llave (posicion del nodo), o -1 si el dato no existe
        */
        int llave(T dato) {
            for (int i = 0; i < conteo(); i++) {
                if (nodos[i] == dato) {
                    return i;
                }
            }
            return no_existe();
        }
        vector<T> vecinos(T dato) {
            vector<T> v;
            auto k = llave(dato);

            if (k == no_existe()) {
                return v;
            }

            for (size_t i = 0; i < conteo();i++) {
                if (conectado(nodos[k], nodos[i])) v.push_back(nodos[i]);
            }

            return v;
        }
    private:
        bool dirigido; /*!< true = grafo dirigido, false = grafo no dirigido*/
        vector<T> nodos; /*!< Arreglo de nodos */
        vector<vector<TP>> adyacencia; /*!< Matriz de adyacencia y pesos */
    };
    /**
    * @brief Grafo disperso mediante lista de adyacencia
    * @tparam T Tipo de datos a almacenar en los nodos
    * @tparam TP Tipo de datos del peso asociado a los arcos
    */
    template <class T, class TP = int>
    class disperso {
    public:
        /**
        * @brief Crea una nueva instancia de un grafo
        * @param dirigido true si el grafo es dirigido, false en caso contrario
        */
        disperso(bool dirigido = false) : dirigido(dirigido) {

        }
        /**
        * @brief Adiciona un nuevo nodo al grafo
        * @param dato Dato a almacenar dentro del nodo
        */
        void agregar_nodo(T dato) {

            // 1. Verificar si el dato ya existe
            auto k = nodos.find(dato);

            if (k != no_existe()) {
                return;
            }

            // 2. Adicionar el nuevo nodo con una lista de adyacencia vacia
            nodos.emplace(dato, map<T, TP> {});

        }
        /**
        * @brief Conecta dos nodos
        * @param inicio Nodo inicial
        * @param fin Nodo final
        * @param peso Peso de la conexion
        */
        void conectar(T inicio, T fin, TP peso) {
            auto i = llave(inicio);
            auto j = llave(fin);

            // Verificar si los nodos existen
            if (i == no_existe() || j == no_existe()) {
                return;
            }

            // Asignar el peso al arco inicio -> fin
            nodos[inicio][fin] = peso;

            if (!dirigido) {
                // Si el grafo es no dirigido, asignar el peso a fin -> inicio
                nodos[fin][inicio] = peso;
            }
        }
        /**
        * @brief Permite obtener la cantidad de datos (nodos) que contiene el grafo
        * @return Cantidad de datos (nodos) presentes en el grafo
        */
        size_t conteo() {
            return nodos.size();
        }
        /**
        * @brief Permite verificar si el grafo contiene un dato
        * @param dato Dato a buscar
        * @return true si el dato se encuentra en el grafo, false en caso contrario
        */
        bool existe(T dato) {
            return (nodos.find(dato) != no_existe());
        }
        /**
        * @brief Elimina el nodo que contiene el dato y sus conexiones
        * @param dato Dato a eliminar
        */
        void eliminar(T dato) {

            //1. Buscar el nodo con el dato
            auto k = llave(dato);

            // 1.1 Si el nodo no existe, terminar.
            if (k == no_existe()) { return; }

            // 1. Borrar las conexiones al nodo con el dato
            // Recorrer el mapa de nodos
            for (auto& n : nodos) {
                // Obtener la lista de adyacencia del nodo
                auto& lista = n.second;
                // Buscar el dato del nodo que se esta eliminando
                auto it = lista.find(dato);
                // Si este nodo esta conectado con el nodo a eliminar, quitar la conexion
                if (it != lista.end()) {
                    lista.erase(it);
                }
            }
            // 1. Borrar el nodo con el dato
            nodos.erase(k);

        }
        /**
        * @brief Sobrecarga del operador de flujo de salida de datos
        * @param os Flujo de salida de datos
        * @param g Grafo a enviar al flujo de salida
        * @return Flujo de salida al cual se ha enviado el grafo
        */
        friend ostream& operator<<(ostream& os, disperso& g) {
            if (g.conteo() == 0) {
                return os;
            }

            // Obtener un iterador que referencia los nodos
            for (auto& it : g.nodos) {
                // Obtener una referencia a la lista de adyacencia
                map<T, TP>& lista = it.second;
                os << it.first;
                os << " [ ";
                // Obtener una referencia a cada nodo
                for (auto& n : lista) {
                    os << " " << n.first << "(" << n.second << ")";
                }
                os << " ] " << endl;
            }

            return os;
        }
    protected:
        bool dirigido; /*!< true = grafo dirigido, false = grafo no dirigido */
        map<T, map<T, TP>>nodos; /*!< Diccionario con las listas de adyacencia */
        /**
        * @brief Permite obtener el iterador del nodo que contiene un dato
        * @param dato Dato a buscar
        * @return Iterador al nodo que contiene el dato, nodos.end() si el dato no se encuentra en el grafo
        */
        auto llave(T dato) {
            return nodos.find(dato);
        }
        /**
        * @brief Retorna una llave inexistente
        * @return nodos.end() (indicador que la llave no existe)
        */
        inline auto no_existe() {
            return nodos.end();
        }
    };
}
