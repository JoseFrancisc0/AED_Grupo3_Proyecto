#ifndef AED_PROYECTO_MAXHEAP_H
#define AED_PROYECTO_MAXHEAP_H

#include <stdexcept>
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

    void insert(TK _key, TV _value){
        heap.emplace_back(_key, _value);
        int index = heap.size() - 1;
        heapifyUp(index);
    }

    TV getMax(){
        if(heap.empty())
            throw std::out_of_range("MinHeap Empty");

        return heap[0].second;
    };

    void clear(){
        heap.clear();
    }

    ~MaxHeap() = default;
};

#endif //AED_PROYECTO_MAXHEAP_H