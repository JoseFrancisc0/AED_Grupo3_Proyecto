#ifndef AED_PROYECTO_AVL_H
#define AED_PROYECTO_AVL_H

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

    public:
        AVL() = default;
        void insert();
        TV remove();
        TV search();
        ~AVL() = default;
};

#endif //AED_PROYECTO_AVL_H