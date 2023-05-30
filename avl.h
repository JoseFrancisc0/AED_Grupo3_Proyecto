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
            NodeAVL* left = nullptr;
            NodeAVL* right = nullptr;

            NodeAVL(UK _key, UV _value): key(_key), value(_value){};

            ~NodeAVL(){
                if(left != nullptr)
                    delete left;
                if(right != nullptr)
                    delete right;
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
                throw std::out_of_range("AVL empty");

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

        void remove(NodeAVL<TK,TV> *&node, TK key){
            if(node==nullptr)
                throw std::out_of_range("AVL empty.");

            if(key < node->key)
                remove(node->left, key);
            else if(key > node->key)
                remove(node->right, key);
            else if((node->left!=nullptr) && (node->right!=nullptr)){
                NodeAVL<TK,TV>* temp = minValue(node->right);
                node->key=temp->key;
                node->value=temp->value;
                remove(node->right, temp->key);
            }
            else{
                NodeAVL<TK,TV>* old = node;
                if(node->left != nullptr)
                    node=node->left;
                else
                    node=node->right;
                delete old;
            }

            balance(node);
        }

        void range_search(NodeAVL<TK,TV>* node, TK begin, TK end, vector<TV>& v){
            if(node == nullptr)
                throw std::out_of_range("AVL empty");

            if(node->key >= begin && node->key <= end)
                v.push_back(node->value);

            if(node->key > begin)
                range_search(node->left, begin, end, v);
            if(node->key < end)
                range_search(node->right, begin, end, v);
        }

    public:
        AVL<TK,TV>() : root(nullptr) {}

        void insert(TK key, TV value){
            insert(this->root, key, value);
        }

        void remove(TK key){
            remove(this->root, key);
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

#endif //AED_PROYECTO_AVL_H