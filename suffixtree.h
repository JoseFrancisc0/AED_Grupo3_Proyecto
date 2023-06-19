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

        STNode() : endPattern(false);
    };

    STNode* root;
public:
    SuffixTree() = default;

    void insert(string _str);
    vector<string> search(string _pattern);
    void clear();

    ~SuffixTree() = default;
};

#endif //AED_PROYECTO_SUFFIXTREE_H