#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry1.h"

#include "/home/alumno.upv.es/jfgarurr/W/PRA/LAB/PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;
        int h(std::string key) const{
            int suma = 0;
            for(int i = 0; i<key.length(); i++){
                suma += int(key.at(i));
            }
            return suma % max;
        }


    public:
        
        HashTable(int size) : n(0), max(size) {
            table = new ListLinked<TableEntry<V>>[max];
        }

        ~HashTable(){
            delete[] table;
        }

        int capacity(){
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            out << "HashTable (" << th.n << " elementos, " 
            << th.max << " cubetas)\n";
            for (int i = 0; i < th.max; i++) {
                out << "[" << i << "]: ";
                for (int j = 0; j < th.table[i].size(); j++) {
                    const TableEntry<V>& entry = th.table[i].get(j);
                    out << "(" << entry.key << " → " << entry.value << ") ";
                }
                out << "\n";
            }
            return out;
        }

        V operator[](std::string key) const {
            int idx = h(key);
            for (int i = 0; i < table[idx].size(); i++) {
                if (table[idx].get(i).key == key) {
                    return table[idx].get(i).value;
                }
            }
            throw std::runtime_error("Clave no encontrada: " + key);
        }

        void insert(std::string key, V value) override{
            int idx = h(key);  // cubeta correspondiente

    		// Buscar si la clave ya existe en la lista
    		for (int i = 0; i < table[idx].size(); i++) {
        	TableEntry<V> entry = table[idx].get(i);
        		if (entry.key == key) {
            			throw std::runtime_error("La clave '" + key + "' ya existe en el diccionario");
        		}
    		}

    	// Si no estaba, insertar nuevo
    	table[idx].prepend(TableEntry<V>(key, value));
    	n++;
        }

	V search(std::string key) override{
		int idx = h(key);

		for(int i = 0; i < table[idx].size(); i++){
			TableEntry<V> entry = table[idx].get(i);
			if(entry.key == key){
				return entry.value;
			}
		}
		throw std::runtime_error("La clave '"+key+"' no se encuentra en el diccionario");
	}

	V remove(std::string key) override{
		int idx = h(key);
		for(int i = 0; i<table[idx].size();i++){
			TableEntry<V> entry = table[idx].get(i);
			if(entry.key == key){
				V val = entry.value;
				table[idx].remove(i);
				n--;
				return val;
			}
		}
		throw std::runtime_error("La clave '"+key+"' no existe en el diccionario");

	}

	int entries() override{
		return n;
	}


        
};

#endif
