#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T>* root;
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) throw std::runtime_error("Elemento no encontrado");
            else if (e < n->elem) return search(n->izq, e);
            else if (e > n->elem) return search(n->der, e);
            else
                return n;

        }
        BSNode<T>* insert(BSNode<T>* n, T e){
            if (n == nullptr){ 
                nelem++;
                return new BSNode<T>(e);
            }
            if (e == n->elem){
                throw std::runtime_error("Elemento duplicado");
            }
            if (e < n->elem){
                n->izq = insert(n->izq, e);
            }
            else{
                n->der = insert(n->der, e);
            }
            return n;
        }
        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if (n != nullptr) {
                if (n->left != nullptr) {
                    print_inorder(out, n->left);
                }
                out << n->elem << " ";
                if (n->right != nullptr) {
                    print_inorder(out, n->right);
                }
            }
        }
        BSNode<T>* remove(BSNode<T>* n, T e){
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            }
            else if (n->elem < e){
                n->right = remove(n->right, e);
            }
            else if (n->elem > e){
                n->left = remove(n->left, e);
            }
            else{
                if (n->left != nullptr && n->right != nullptr){
                    n->elem = max(n->left);
                    n->left = remove(n->left);
                }
                else{
                   BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
                    delete n;
                    --nelem;
                    return temp;
                }
            }
        }
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("ElementNotFoundException");
            }
            return (n->right == nullptr) ? n->elem : max(n->right);
        }
        BSNode<T>* remove_max(BSNode<T>* n){
            if (n->right == nullptr) {
                BSNode<T>* temp = n->left;
                delete n;
                --nelem;
                return temp;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }


        //miembros privados
    public:
        BSTree(){
            nelem = 0;
            root = nullptr;
        }
        int size() const {
            return nelem;
        }
        T search(T e) const {
            return search(root, e)->elem;

        }
        T operator[](T e) const {
            return search(e);
        }
        void insert(T e){
            root = insert(root, e);
        }
        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
    	
        ~BSTree(){
            delete_cascade(root);
        }
        // miembros públicos
    
};

#endif