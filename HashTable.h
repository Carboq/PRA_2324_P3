#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n; //elementos almacenados en la tabla hash
        int max; //tamaño de la tabla hash
        ListLinked<TableEntry<V>>* table; //tabla hash
        int h(std::string key){
            int hash = 0;
            for (int i = 0; i < key.length(); i++) {
                hash += (int) key[i];
            }
            return hash % max;
        }

    public:

        HashTable(int size){
            max = size;
            table = new ListLinked<TableEntry<V>>[max];
            n = 0;
        }
        ~HashTable(){
            delete[] table;
        }
        int capacity(){
            return max;
        }
         V operator[](std::string key) {
        int bucket = h(key);
        ListLinked<TableEntry<V>>& list = table[bucket];
        int pos = list.search(TableEntry<V>(key));

        if (pos == -1) {
            throw std::runtime_error("Key not found in HashTable");
        }

        return list.get(pos).value;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; i++) {
            out << "Bucket " << i << ": ";
            out << ht.table[i] << "\n";
        }
        return out;
    }
        void insert(std::string key, V value) override{
            int pos = h(key);
            ListLinked<TableEntry<V>>& list = table[pos];
            if (list.search(TableEntry<V>(key)) != -1) {
                throw std::runtime_error("La llave ya existe en la tabla hash");
            }
            list.prepend(TableEntry<V>(key, value));
            n++;
        }
        V search(std::string key) override{
            int pos = h(key);
            ListLinked<TableEntry<V>>& list = table[pos];
            int pos2 = list.search(TableEntry<V>(key));
            if (pos2 == -1) {
                throw std::runtime_error("La llave no existe en la tabla hash");
            }
            return list.get(pos2).value;
        }
        V remove(std::string key) override{
            int pos = h(key);
            ListLinked<TableEntry<V>>& list = table[pos];
            int pos2 = list.search(TableEntry<V>(key));
            if (pos2 == -1) {
                throw std::runtime_error("La llave no existe en la tabla hash");
            }
            V value = list.get(pos2).value;
            list.remove(pos2);
            n--;
            return value;
        }
        int entries() {
            return n;
        }
        // ...
        
};

#endif
