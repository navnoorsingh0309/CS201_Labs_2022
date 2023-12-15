#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct DArray {
    size_t len;
    int *data;
};

void query_1(int Arr[], int func) {
    //for time calculation
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    Arr[1] += 5;
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\nThe time taken for query 1 by function %d is %f seconds", func, cpu_time_used);
    printf("\nThe incremented value of the first index element is %d", Arr[1]);
}

//I didn't get the meaning of n-5
void query_2(int Arr[], int len, int func) {
    //for time calculation
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int sum = 0;
    for(int i=0;i<len-5;i++) {
        sum+=Arr[i];
    }
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\nThe time taken for query 2 by function %d is %f seconds", func, cpu_time_used);
    printf("\nThe sum of first n-5 elements is %d", sum);
}

void function_1(int Arr[], int len) {
    int CIarrT[len];
    //Cumulative Frequency
    for(int i=0;i<len;i++)
        CIarrT[i] = -1;
    int count = 0, FreqLen = 0;
    for(int i=0;i<len;i++) {
        count = 1;
        for(int j=i+1;j<len;j++) {
            if(Arr[i]==Arr[j]) {
                count++;
                CIarrT[j] = 0;
            }
        }
        if(CIarrT[i] != 0) {
            CIarrT[i] = count;
            FreqLen++;
        }
    }
    int CIarr[FreqLen];
    FreqLen = 0;
    for(int i=0;i<len;i++) {
        if(CIarrT[i] != 0) {
            CIarr[FreqLen] = CIarrT[i]*Arr[i];
            FreqLen++;
        }
    }
    query_1(CIarr, 1);
    query_2(CIarr, FreqLen, 1);
}

//Binary Index Tree
void updateBIT(int* arr, int n, int index, int val) {
    index++;
    while(index<=n) {
        arr[index] += val;
        index+= (index) & (-index);
    }
}
int *constructBinaryTree(int arr[], int n) {
    int *BITree = (int*)malloc((n+1)*sizeof(int));
    for(int i=0;i<=n;i++)
        BITree[i] = 0;
    for(int i=0;i<n;i++)
        updateBIT(BITree, n, i, arr[i]);
    return BITree;
}

void function_2(int Arr[], int len) {
    int *BITreeP = constructBinaryTree(Arr, len);
    int BITree[len+1];
    for(int i=0;i<=len;i++)
        BITree[i] = BITreeP[i];
    query_1(BITree, 2);
    query_2(BITree, len+1, 2);
}

void initiateDArray(struct DArray *Arr) {
    Arr->data = malloc(sizeof(int));
    Arr->len = 0;
}
void insertDArray(struct DArray *Arr, int element) {
    Arr->len++;
    Arr->data = realloc(Arr->data, (Arr->len)*sizeof(int));
    Arr->data[(Arr->len-1)] = element;
}   

void main() {
    char c;
    struct DArray dArray;
    initiateDArray(&dArray);
    printf("Please enter a choice:");
    c = getche();
    if(c=='a') {
        //From File
        FILE *fptr;
        fptr = fopen("File.txt", "r");
        int finput;
        while(fscanf(fptr, "%d", &finput)!=EOF) {
            insertDArray(&dArray, finput);
        }
        printf("\nThe array size is %d", dArray.len);
        int Arr[dArray.len];
        for(int i=0;i<dArray.len;i++) {
            printf("%d ", dArray.data[i]);
            Arr[i] = dArray.data[i];
        }
        printf("\nBy function_1:");
        function_1(Arr, dArray.len);
        printf("\nBy function_2:");
        function_2(Arr, dArray.len); 
    } else if(c=='b') {
        //Input Array
        printf("\nPlease input an integer array with space-separator and press Enter when done:");
        while(1) {
            int input;
            scanf("%d%c", &(input), &c);
            insertDArray(&dArray, input);
            if(c==13 || c==10)
                break;
        }
        printf("The array size is %d", (dArray.len));
        int Arr[dArray.len];
        for(int i=0;i<dArray.len;i++) {
            Arr[i] = dArray.data[i];
        }
        printf("\nBy function_1:");
        function_1(Arr, dArray.len);
        printf("\nBy function_22:");
        function_2(Arr, dArray.len);
    }
}
