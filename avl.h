#ifndef AED_PROYECTO_AVL_H
#define AED_PROYECTO_AVL_H

#include <vector>
using namespace std;
template<typename UK, typename UV>
struct Node{
    UK key;
    UV value;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(UK _key, UV _value): key(_key), value(_value){};

    void killself(){
        if(left != nullptr)
            left->killself();
        if(right != nullptr)
            right->killself();
        delete this;
    }
};

template<typename TK, typename TV>
class AVL{
    private:  
        Node<TK,TV>* root;;
        void insert(Node<TK,TV> *&node, TK key, TV value);
        void remove(Node<TK,TV> *&node, TK key);
        void range_search(Node<TK,TV>* node, TK begin, TK end, vector<TV>& v);
        void search(Node<TK,TV>* node, TK key);
        void balance(Node<TK,TV> *&node);

    public:
        AVLTree() : root(nullptr) {}

        void insert(TK key, TV value){
            insert(this->root, key, value);
        }

        void remove(TK key){
            remove(this->root, key);
        }

        TV search(TK _key){
            return search(this->root, key);
        }

        vector<TV> range_search(TK begin, TK end){
            vector<TV> result;
            range_search(this->root, begin, end, result);
            return result;
        }

        ~AVL(){
            if(this->root != nullptr)
                this->root->killSelf();
        }
};

template<typename TK, typename TV>
void insert(Node<TK,TV> *&node, TK key, TV value){
    if (node == nullptr)
        node = new Node<TK,TV>(key,value);
    else if (key < node->key)
        insert(node->left, key, value);
    else if (key > node->key)
        insert(node->right, key, value);
    
    balance(node);
}

template<typename TK, typename TV>
void balance(Node<TK,TV> *&node){
    
}
