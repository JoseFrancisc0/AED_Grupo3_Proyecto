#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename TK, typename TV>
class HashTable{
    private:
        int capacity = 5;
        double maxFillFactor = 0.8;
        int size = 0;
        vector<pair<TK,TV>> table;

        size_t hashCode(const TK& key){
            return std::hash<TK>{}(key) % capacity;
        }

        void rehash() {
            int oldCap = capacity;
            vector<pair<TK,TV>> oldTable = std::move(table);
            capacity *= 2;
            table.assign(capacity, make_pair(TK(),TV()));

            for(size_t i=0; i<oldCap; i++)
                if(oldTable[i].first != TK())
                    insert(oldTable[i].first, oldTable[i].second);
        }

        size_t findIndex(const TK& key){
            size_t index = hashCode(key);
            size_t startIndex = index;

            while(table[index].first != TK() && table[index].first != key) {
                index = (index + 1) % capacity;
                if(index == startIndex)
                    throw std::runtime_error("Hash Table is full");
            }

            return index;
        }

    public:
        HashTable(){
            table = vector<pair<TK,TV>>(capacity, make_pair(TK(),TV()));
        }

        void insert(const TK& key, const TV& value) {
            if((double) size/capacity > maxFillFactor)
                rehash();

            size_t index = findIndex(key);

            if(table[index].first == TK())
                size++;

            table[index] = make_pair(key,value);
        }

        void clear(){
            capacity = 5; /// Reset capacity
            table.assign(capacity, make_pair(TK(), TV()));
            size = 0;
        }

        const TV& search(const TK& key) {
            size_t index = findIndex(key);

            if(table[index].first == key)
                return table[index].second;
            else
                throw std::out_of_range("Key not found in table.");
        }

        ~HashTable() = default;
};

#endif //HASHTABLE_H
