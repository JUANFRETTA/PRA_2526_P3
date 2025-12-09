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
		BSTreeDict(){
			tree = BSTree<TableEntry<V>>();
		
		}

		~BSTreeDict(){
			delete tree;
		}

		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
			out << bs->tree;
			return out;
		}

		V operator[](std::string key){
			return search(key);
	
		}

		void insert(std::string key, V value) override{
			TableEntry<V> entry(key,value);
			tree->insert(entry);
		
		}

		V search(std:: string key) override{
			TableEntry<V> entry(key);
			TableEntry<V> encontrado = tree->search(entry);
			return encontrado.value;
		
		}

		V remove(std::string key) override{
			TableEntry<V> entry(key);
			TableEntry<V> found = tree->search(entry);
			V val = found.value;
			tree->remove(entry);
			return val;
		
		}

		int entries() override{
			return tree->size();
		
		}





};


#endif
