#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelementos;
        BSNode<T>* root;

        BSNode<T>* search(BSNode<T>* n, T e) const{
            if (n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            }else if (e > n->elemento){
                return search(n->right,e);
            }else if (e < n->elemento){
                return search(n->left,e);
            }else{
                return n;
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n == nullptr){
                nelementos++;
                return new BSNode(e);
            }else if (n->elemento == e){
                throw std::runtime_error("Elemento ya insertado");
            }else if (e > n->elemento){
                n->right = insert(n->right,e);
            }else{
                n->left = insert(n->left,e);
            }
            return n;
        }
    

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);   // visitar subárbol izquierdo
                out << n->elemento << " ";        // visitar nodo actual
                print_inorder(out, n->right); // visitar subárbol derecho
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            }else if(n->elemento < e){
                n->right = remove(n->right,e);
            }else if(n->elemento > e){
                n->left = remove(n->left,e);
            }else{
                if(n->left != nullptr && n->right != nullptr){
                    n->elemento = max(n->left);
                    n->left = remove_max(n->left);
                }else{
                    BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
                    delete n;
                    nelementos--;
                    n = temp;
                }
                
            }
            return n;
        }

        T max(BSNode<T>* n) const{
            if(n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            }else{
                return (n->right != nullptr) ? max(n->right) : n->elemento;
            }
        }   
        
        BSNode<T>* remove_max(BSNode<T>* n){
            if(n->right == nullptr){
                BSNode<T>* temp = n->left;
                delete n;
                nelementos--;
                return temp;
            }else{
                n->right = remove_max(n->right);
                return n;
            }
        }

        void delete_cascade(BSNode<T>* n){
            if (n != nullptr) {
                delete_cascade(n->left);   // primero izquierda
                delete n;                         // luego raíz
                delete_cascade(n->right);   // finalmente derecha
    }
        }
        
    public:

        //Creación y tamaño

        BSTree(){           
            nelementos = 0;
            root = nullptr;
        }

        int size() const{           
            return nelementos;
        }

        //Búsqueda

        T search(T e) const {           
            return search(root,e)->elemento;
        }

        T operator[](T e) const{
            return search(e);
        }

        //Inserción

        void insert(T e){
            root = insert(root,e);
        }

        //print inorden

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
        

        //Remove

        void remove(T e){
            root = remove(root,e);
        }

        //Destruccion

        ~BSTree(){
            delete_cascade(root);
            root = nullptr;
            nelementos=0;
        }
    
};

#endif
