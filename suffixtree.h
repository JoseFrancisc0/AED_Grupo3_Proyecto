#ifndef AED_PROYECTO_SUFFIXTREE_H
#define AED_PROYECTO_SUFFIXTREE_H

#include <stdexcept>
#include <unordered_map>
#include <vector>
using namespace std;

class SuffixTree{
private:
    struct STNode{
        unordered_map<char, STNode*> children;
        bool endPattern;

        STNode() : endPattern(false) {};
    };

    STNode* root;

    void clearHelper(STNode* node){
        if(node == nullptr)
            return;

        for(auto& pair : node->children)
            clearHelper(pair.second);

        delete node;
    }

public:
    SuffixTree() : root(nullptr) {};

    void insert(string _str);
    vector<string> search(string _pattern);

    void clear(){
        clearHelper(root);
        root = nullptr;
    }

    ~SuffixTree(){
        clear();
    };
};

#endif //AED_PROYECTO_SUFFIXTREE_H