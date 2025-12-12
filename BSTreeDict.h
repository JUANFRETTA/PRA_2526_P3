#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry1.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    
    BSTreeDict()  {
    
     tree = new BSTree<TableEntry<V>>();

    }

    ~BSTreeDict() {
    
	    delete tree;
    }

     friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bsd) {
        return out << *(bsd.tree);  
    }

    
    V operator[](std::string key) {
        return tree->search(key).value;
    }

      void insert(std::string key, V value) {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) {
         return tree->search(key).value;
    }

    V remove(std::string key) {
        TableEntry<V> entry(key);
         TableEntry<V> found = tree->search(entry);
	 V aux = found.value;
	 tree-> remove(found);
	 return aux;
    }

    int entries() {
        return tree->size(); 
    }
   
};
#endif
