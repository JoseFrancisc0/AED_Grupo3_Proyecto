#ifndef AED_PROYECTO_AVL_H
#define AED_PROYECTO_AVL_H

#include <vector>
using namespace std;

template<typename TK, typename TV>
class AVL{
    private:
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
        Node<TK,TV>* root = nullptr;

        void insert(Node<TK,TV>* _node, TK _key, TV _value);
        void remove(Node<TK,TV>* _node, TK _key);
        void range_search(Node<TK,TV>* _node, TK _begin, TK _end, vector<TV>& v);


    public:
        AVL() = default;

        void insert(TK _key, TV _value){
            insert(this->root, _key, _value);
        }

        void remove(TK _key){
            remove(this->root, _key);
        }

        vector<TV> range_search(TK begin, TK end){
            vector<TV> result;
            range_search(root, begin, end, result);
            return result;
        }

        ~AVL() = default;
};

#endif //AED_PROYECTO_AVL_H