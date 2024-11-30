#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
    BSTree<TableEntry<V>>* tree;
        // ...

    public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }
    ~BSTreeDict() {
        delete tree;
    }
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << "BSTreeDict: " << *bs.tree;  // Suponiendo que BSTree tiene un operador << adecuado
        return out;
    }
    V operator[](std::string key) {
        return search(key);  // Delegamos la operación al método search
    }
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);  // Delegamos al método insert() del ABB
    }

    // Implementación del método search()
    V search(std::string key) override {
        TableEntry<V> entry(key);
        TableEntry<V> foundEntry = tree->search(entry);  // Delegamos al método search() del ABB
        if (foundEntry.key == "") {  // Si no se encuentra la clave
            throw std::runtime_error("Key not found");
        }
        return foundEntry.value;
    }

    // Implementación del método remove()
    V remove(std::string key) override {
        TableEntry<V> entry(key);
        TableEntry<V> removedEntry = tree->search(entry);  // Delegamos al método remove() del ABB
        tree->remove(entry);
        return removedEntry.value;
    }

    // Implementación del método entries() (puede ser una operación que recorra el árbol)
    int entries() override {
        return tree->size();  // Asumimos que BSTree tiene un método size() que devuelve el número de nodos
    }
};
        // ...
        

#endif