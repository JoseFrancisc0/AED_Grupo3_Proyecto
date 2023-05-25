#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
using namespace std;

template<typename TK, typename TV>
class HashTable{
    private:
        int capacity = 5;
        double maxFillFactor = 0.8;
        int size = 0;
        vector<pair<TK,TV>> table;

        int hashCode(TK key){
            return hash<TK>{}(key) % capacity;
        }

        void rehash();
        int openAddressing();

    public:
        HashTable() = default;
        ~HashTable() = default;
};

#endif //HASHTABLE_H
