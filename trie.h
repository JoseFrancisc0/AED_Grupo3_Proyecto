#ifndef AED_PROYECTO_TRIE_H
#define AED_PROYECTO_TRIE_H

#include <string>
#include <vector>
using namespace std;

class Trie{
private:
    struct TrieNode{};
    TrieNode* root;
public:
    Trie() = default;
    void insert(string _string);
    vector<string> search(string _prefix);
    void clear();
    ~Trie() = default;
};

#endif //AED_PROYECTO_TRIE_H