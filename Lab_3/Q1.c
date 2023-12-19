#include <stdio.h>
#include <stdlib.h>

struct HeapStruct {
    int *arr;
    int size;
    int capacity;
};
typedef struct HeapStruct Heap;

void swap(int* a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyMax(Heap* heap, int i) {
    int largest = i;
    int l = 2*largest + 1;
    int r = 2*largest + 2;

    if(l<heap->size && heap->arr[l]>heap->arr[largest]) 
        largest = l;

    if(r<heap->size && heap->arr[r]>heap->arr[largest]) 
        largest = r;

    if(largest!=i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapifyMax(heap, largest);
    }
}

void heapifyMin(Heap* heap, int i) {
    int smallest = i;
    int l = 2*smallest + 1;
    int r = 2*smallest + 2;

    if(l<heap->size && heap->arr[l]<heap->arr[smallest])
        smallest = l;

    if(r<heap->size && heap->arr[r]<heap->arr[smallest])
        smallest = r;

    if(smallest!=i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapifyMax(heap, smallest);
    }
}

Heap* createHeap(int capacity, int* array1, int maxmin) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    for (int i = 0; i < capacity; i++) {
        heap->arr[i] = array1[i];
    }
    
   heap->size = capacity;
   //Building Heap
   //Last leaf node
   int i = (heap->size/2) - 1;
   while(i>=0) {
    if(maxmin==1)
        heapifyMax(heap, i);
    else
        heapifyMin(heap, i);
    i--;
   } 
   return heap;
}

int extractHeap(Heap* heap, int maxmin) {
    int deletedItem;
    deletedItem = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    if(maxmin==1)
        heapifyMax(heap, 0);
    else
        heapifyMin(heap, 0);
    return deletedItem;
}

void main() {
    int n, k;
    printf("Enter number of elements n and k: ");
    scanf("%d %d", &n, &k);
    int Arr[n];
    printf("Enter %d numbers: ", n);
    for(int i=0;i<n;i++)
        scanf("%d", &Arr[i]);
    //Algorithm 1
    //Build Max Heap
    Heap* h = createHeap(n, Arr, 1);
    //Extract Max Algorithm
    int maxOne;
    for(int i=0;i<k;i++) 
        maxOne = extractHeap(h, 1);    
    printf("%dth largest element is: %d", k, maxOne);

    //Algorithm 2
    //Adding to Heap
    int Arrk[k];
    for(int i=0;i<k;i++)
        Arrk[i] = Arr[i];
    Heap* hk = createHeap(k, Arrk, 2);
    //insertion of next one
    int minOne;
    for(int i=k;i<n;i++) {
        if(hk->arr[0]<Arr[i]) {
            hk->arr[0] = Arr[i];
            hk = createHeap(k, hk->arr, 2);
        }
    }
    printf("\n%dth largest element is: %d", k, hk->arr[0]);
}
