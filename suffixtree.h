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
        vector<string> words;
    };

    STNode* root;

    void clear(STNode* node){
        for(auto child : node->children)
            clear(child.second);

        delete node;
    }

public:
    SuffixTree() : root(nullptr) {};

    void insert(string _str){
        for (size_t i = 0; i < _str.length(); i++) {
            STNode* current = root;
            for (size_t j = i; j < _str.length(); j++) {
                if (current->children.find(_str[j]) == current->children.end()) {
                    current->children[_str[j]] = new STNode();
                }
                current = current->children[_str[j]];
                current->words.push_back(_str);
            }
        }
    }

    vector<string> search(string _pattern){
        STNode* current = root;
        for (char c : _pattern) {
            if (current->children.find(c) == current->children.end()) {
                return {}; // pattern not found
            }
            current = current->children[c];
        }
        return current->words;
    }

    void clear(){
        clear(root);
        root = new STNode();
    }

    ~SuffixTree(){
        clear(root);
    };
};

#endif //AED_PROYECTO_SUFFIXTREE_H