#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

#define n 4

struct MinHeapNode
{
    int element;
    int i;
    int j;
};

class MinHeap
{
    MinHeapNode *harr;
    int heap_size;

public:

    MinHeap(MinHeapNode a[], int size);

    void minHeapify(int );

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * i + 2;
    }

    MinHeapNode getMin()
    {
        return harr[0];
    }

    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        minHeapify(0);
    }

};

MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a;
    int i = (heap_size - 1) / 2;
    while(i >= 0)
    {
        minHeapify(i);
        i--;
    }
}

void MinHeap::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);

    int smallest = i;

    if(l < heap_size && harr[l].element < harr[i].element)
        smallest = l;
    if(r < heap_size && harr[r].element < harr[smallest].element)
        smallest = r;

    if(smallest != i)
    {
        swap(harr[smallest], harr[i]);
        minHeapify(smallest);
    }
}

int *mergeKArrays(int arr[][n], int k)
{
    int *output = new int[n * k];

    MinHeapNode *harr = new MinHeapNode[k];

    for(int i = 0; i < k; i++)
    {
        harr[i].element = arr[i][0];
        harr[i].i = i;
        harr[i].j = 1;
    }

    MinHeap hp(harr, k);

    for(int count = 0; count < n * k; count++)
    {
        MinHeapNode root = hp.getMin();

        output[count] = root.element;

        if(root.j < n)
        {
            root.element = arr[root.i][root.j];
            root.j += 1;
        }
        else
            root.element = INT_MAX;

        hp.replaceMin(root);
    }

    return output;
}

void printArray(int arr[], int size)
{
   for (int i=0; i < size; i++)
       cout << arr[i] << " ";
}

int main()
{
    int arr[][n] =  {{2, 6, 12, 34},
                     {1, 9, 20, 1000},
                     {23, 34, 90, 2000}};
    int k = sizeof(arr)/sizeof(arr[0]);

    int *output = mergeKArrays(arr, k);

    cout << "Merged array is " << endl;
    printArray(output, n*k);

    return 0;
}
