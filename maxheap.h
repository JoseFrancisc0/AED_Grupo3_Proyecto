#ifndef AED_PROYECTO_MAXHEAP_H
#define AED_PROYECTO_MAXHEAP_H

#include <vector>
using namespace std;

template<typename TK, typename TV>
class MaxHeap{
private:
    vector<pair<TK,TV>> heap;

    int parent(int i);
    void heapifyUp(int i);
public:
    MaxHeap() = default;

    void insert(TK _key, TV _value);
    TV getMax();
    void clear();

    ~MaxHeap() = default;
};

#endif //AED_PROYECTO_MAXHEAP_H