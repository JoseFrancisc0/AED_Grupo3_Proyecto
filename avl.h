#ifndef AED_PROYECTO_AVL_H
#define AED_PROYECTO_AVL_H

#include <vector>
#include <stdexcept>
using namespace std;

template<typename TK, typename TV>
class AVL{
    private:
        template<typename UK, typename UV>
        struct NodeAVL{
            UK key;
            UV value;
            int height = 0;
            NodeAVL<UK,UV>* left = nullptr;
            NodeAVL<UK,UV>* right = nullptr;

            NodeAVL(UK _key, UV _value): key(_key), value(_value){};

            void killSelf(){
                if(left != nullptr)
                    left->killSelf();
                if(right != nullptr)
                    right->killSelf();
                delete this;
            }
        };

        NodeAVL<TK,TV>* root;

        int height(NodeAVL<TK,TV> *node){
            if (node == nullptr)
                return -1;
            else
                return node->height;
        }

        void updateHeight(NodeAVL<TK,TV> *node){
            node->height = max(height(node->left), height(node->right)) +1;
        }

        void left_rota(NodeAVL<TK,TV> *&node){
            NodeAVL<TK,TV> *k1 = node->left;
            node->left = k1->right;
            k1->right = node;
            node->height = max(height(node->left), height(node->right)) + 1;
            k1->height = max(height(k1->left), node->height) + 1;
            node = k1;
        }

        void right_rota(NodeAVL<TK,TV> *&node){
            NodeAVL<TK,TV> *k1 = node->right;
            node->right = k1->left;
            k1->left = node;
            node->height = max(height(node->right), height(node->left)) + 1;
            k1->height = max(height(k1->right), node->height) + 1;
            node = k1;
        }

        void balance(NodeAVL<TK,TV> *&node){
            if(node==nullptr)
                return;

            if(height(node->left)-height(node->right)>1){
                if(height(node->left->left) >= height(node->left->right))
                    left_rota(node);
                else{
                    right_rota(node->left);
                    left_rota(node);
                }
            }
            else{
                if(height(node->left)-height(node->right)<-1){
                    if(height(node->right->right) >= height(node->right->left))
                        right_rota(node);
                    else{
                        left_rota(node->right);
                        right_rota(node);
                    }
                }
            }

            updateHeight(node);
        }

        void insert(NodeAVL<TK,TV> *&node, TK key, TV value){
            if (node == nullptr)
                node = new NodeAVL<TK,TV>(key,value);
            else if (key < node->key)
                insert(node->left, key, value);
            else if (key > node->key)
                insert(node->right, key, value);

            balance(node);
        }

        void range_search(NodeAVL<TK,TV>* node, TK begin, TK end, vector<TV>& v){
            if(node == nullptr)
                return;
            if(node->key > begin)
                range_search(node->left, begin, end, v);
            if(node->key >= begin && node->key <= end)
                v.push_back(node->value);
            if(node->key < end)
                range_search(node->right, begin, end, v);
        }

        void print(NodeAVL<TK,TV>* node){
            if(node != nullptr){
                print(node->left);
                cout << node->key << "," << node->value << " ";
                print(node->right);
            }
        }

    public:
        AVL<TK,TV>() : root(nullptr) {}

        void insert(TK key, TV value){
            insert(this->root, key, value);
        }

        vector<TV> range_search(TK begin, TK end){
            vector<TV> result;
            range_search(this->root, begin, end, result);
            return result;
        }

        void print(){
            print(root);
        }

        void clear(){
            if(root != nullptr){
                root->killSelf();
                root = nullptr;
            }
        }

        ~AVL(){
            clear();
        }
};

#endif //AED_PROYECTO_AVL_H
