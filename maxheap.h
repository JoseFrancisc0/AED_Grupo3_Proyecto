#ifndef AED_PROYECTO_MAXHEAP_H
#define AED_PROYECTO_MAXHEAP_H

#include <vector>
using namespace std;

template<typename TK, typename TV>
class MaxHeap{
private:
    vector<pair<TK,TV>> heap;

    int parent(int i){
        return (i - 1)/2;
    }

    void heapifyUp(int i){
        while(i > 0 && heap[parent(i)].first < heap[i].first){
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
public:
    MaxHeap() = default;

    void insert(TK _key, TV _value);
    TV getMax();
    void clear();

    ~MaxHeap() = default;
};

#endif //AED_PROYECTO_MAXHEAP_H