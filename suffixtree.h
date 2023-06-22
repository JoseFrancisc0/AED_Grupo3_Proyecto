#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

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

    void insert(string str){
        for (size_t i = 0; i < str.length(); i++) {
            STNode* current = root;
            for (size_t j = i; j < str.length(); j++) {
                if (current->children.find(str[j]) == current->children.end()) {
                    current->children[str[j]] = new STNode();
                }
                current = current->children[str[j]];
                current->words.push_back(str);
            }
        }
    }

    vector<string> search(string pattern){
        STNode* current = root;
        for (char c : pattern) {
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

#endif //SUFFIXTREE_H