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

        size_t hashCode(TK key){
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

        size_t openAddressing(TK& key, size_t index){
            int i = 1;
            while(table[index].first != TK{} && table[index].first != key){
                index = (index + i*i) % capacity;
                i++;
            }
            return index;
        }

    public:
        HashTable() = default;

        void insert(TK key, TV value) {
            if(size*maxFillFactor >= capacity)
                rehash();

            size_t index = hashCode(key);
            index = openAddressing(key, index);

            if(table[index].first == TK{})
                size++;

            table[index] = make_pair(key,value);
        }

        void remove(TK key){
            size_t index = hashCode(key);
            index = openAddressing(key, index);

            if(table[index].first == key) {
                table[index].first = TK{};
                size--;
            }
        }

        ~HashTable() = default;
};

#endif //HASHTABLE_H
