#ifndef AED_PROYECTO_MINHEAP_H
#define AED_PROYECTO_MINHEAP_H

#include <vector>
using namespace std;

template<typename TK, typename TV>
class MinHeap{
    private:
        vector<pair<TK, TV>> heap;

        int parent(int i);
        void heapifyUp(int i);

    public:
        MinHeap() = default;
        void insert(TK _key, TV _value);
        TV getMin();
        ~MinHeap() = default;
};

#endif //AED_PROYECTO_MINHEAP_H