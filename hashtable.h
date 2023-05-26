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

        void rehash() {
            capacity *= 2;
            size = 0;
            vector<pair<TK, TV>> newTable(capacity);
            table.swap(newTable);

            for (const auto &item: newTable)
                if (item.first != TK{})
                    insert(item.first, item.second);
        }

        int openAddressing(TK& key, int index){
            int i = 1;
            while(table[index].first != TK{} && table[index].first != key){
                index = (index + i*i) % capacity;
                i++;
            }
            return index;
        }

    public:
        HashTable() = default;

        void insert(TK key, TV value);
        void remove(TK key);
        ~HashTable() = default;
};

#endif //HASHTABLE_H
