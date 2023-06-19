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

    void dfs(STNode* node, string pattern, string currMatch, vector<string>& matches){
        if(node->endPattern)
            matches.push_back(currMatch);

        for(auto& pair : node->children){
            char c = pair.first;
            STNode* child = pair.second;

            string nextMatch = currMatch + c;
            dfs(child, pattern, nextMatch, matches);
        }
    }

    void clearHelper(STNode* node){
        if(node == nullptr)
            return;

        for(auto& pair : node->children)
            clearHelper(pair.second);

        delete node;
    }

public:
    SuffixTree() : root(nullptr) {};

    void insert(string _str){
        _str += "$";

        for(int i=0; i<_str.length(); i++){
            string suffix = _str.substr(i);
            STNode* current = root;

            for(char c :suffix){
                if(current->children.find(c) == current->children.end())
                    current->children[c] = new STNode();

                current = current->children[c];
            }

            current->endPattern = true;
        }
    }

    vector<string> search(string _pattern){
        vector<string> matches;

        STNode* current = root;
        string pattern = _pattern + "$";

        for(char c : pattern){
            if(current->children.find(c) == current->children.end())
                return matches;

            current = current->children[c];
        }

        dfs(current, _pattern, "", matches);

        return matches;
    }

    void clear(){
        clearHelper(root);
        root = nullptr;
    }

    ~SuffixTree(){
        clear();
    };
};

#endif //AED_PROYECTO_SUFFIXTREE_H