#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode{
    public:

    T elemento;
    BSNode<T>* left;
    BSNode<T>* right;

    BSNode(T elemento, BSNode<T>* left, BSNode<T>* right) 
        : elemento(elemento), left(nullptr), right(nullptr)  {}
    BSNode(T elemento) : elemento(elemento), left(nullptr), right(nullptr) {}

    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
        out << "[";
        out << bsn.elemento;
        out << "]";
        return out;
    }



};

#endif
