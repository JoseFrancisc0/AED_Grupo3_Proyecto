#ifndef TRIE_H
#define TRIE_H

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Trie{
    private:
        struct TrieNode{
            char value;
            bool endWord;
            unordered_map<char, TrieNode*> children;

            TrieNode(char _val) : value(_val), endWord(false) {};
        };
        TrieNode* root;

        void searchDFS(TrieNode* _node, string _prefix, vector<string>& result){
            if(_node->endWord)
                result.push_back(_prefix);

            for(auto& pair : _node->children){
                char c = pair.first;
                TrieNode* child = pair.second;
                searchDFS(child, _prefix + c, result);
            }
        }

        void clearDFS(TrieNode* node){
            for(auto& pair : node->children){
                TrieNode* child = pair.second;
                clearDFS(child);
                delete child;
            }
        }

    public:
        Trie(): root(nullptr){};

        void insert(string _string){
            if(_string.empty())
                throw std::invalid_argument("The prefix is empty.");

            if(root == nullptr)
                root = new TrieNode('\0');

            TrieNode* current = root;
            for(char c : _string){
                if(current->children.find(c) == current->children.end())
                    current->children[c] = new TrieNode(c);

                current = current->children[c];
            }

            current->endWord = true;
        }

        vector<string> search(string _prefix){
            vector<string> result;

            TrieNode* current = root;
            for(char c : _prefix){
                if(current->children.find(c) == current->children.end())
                    return result;

                current = current->children[c];
            }

            searchDFS(current, _prefix, result);

            return result;
        }

        void clear(){
            if(root != nullptr){
                clearDFS(root);
                root = nullptr;
            }
        }

        ~Trie() = default;
};

#endif //TRIE_H