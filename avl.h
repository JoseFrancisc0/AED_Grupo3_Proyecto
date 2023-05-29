#ifndef AED_PROYECTO_AVL_H
#define AED_PROYECTO_AVL_H

template<typename T>
struct Node{
    T data;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(T _data) : data(_data){};
};

template<typename T>
class AVL{
    private:
        Node<T> root;
    public:
        AVL() = default;
        void insert();
        T remove();
        T search();
        ~AVL() = default;
};

#endif //AED_PROYECTO_AVL_H