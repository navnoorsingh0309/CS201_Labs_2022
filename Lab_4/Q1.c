#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Swapping Function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to quicksort by last element as pivot
// Return value is (K-1)th index element in sorted list
int func1(int Arr[], int N, int K)
{
    // Partitioning list
    if (N > 0)
    {
        // Let pivot be last element
        int pivot = Arr[N - 1];
        // Partitioning algorithm
        int i = -1;
        for (int j = 0; j <= N - 1; j++)
        {
            // Swap if small
            if (Arr[j] < pivot)
            {
                i++;
                swap(&Arr[i], &Arr[j]);
            }
        }
        // Swap pivot
        swap(&Arr[i + 1], &Arr[N - 1]);
        // breaking Arr into two arrays for recursive quick sort
        int Arr1[i + 1], Arr2[N - (i + 1)];
        for (int j = 0; j < i + 1; j++)
            Arr1[j] = Arr[j];
        for (int j = i + 2, k = 0; j < N; j++, k++)
            Arr2[k] = Arr[j];
        func1(Arr1, i + 1, K);
        func1(Arr2, (N - (i + 2)), K);
        // Putting values of Arr1 and Arr2 back to Arr
        for (int j = 0; j < i + 1; j++)
            Arr[j] = Arr1[j];
        for (int j = i + 2, k = 0; j < N; j++, k++)
            Arr[j] = Arr2[k];
        if (K <= N)
            return Arr[K - 1];
        else
            return -1;
    }
    else
        return -1;
}

// Function for Medians od Medians algo
int func2(int Arr[], int N, int K)
{
    int chunks = ceil((double)N / 5); // Number of chunks broken into
    int ArrChunks[chunks][5], Medians[chunks];
    for (int i = 0; i < N; i++)
        ArrChunks[(int)floor((double)i / 5)][i % 5] = Arr[i];

    //Finding median of each chunk
    for (int i = 0; i < chunks; i++)
    {
        if (i != chunks - 1 || (N % 5)==0)
            Medians[i] = func1(ArrChunks[i], 5, 3);
        else
            Medians[i] = func1(ArrChunks[i], (N % 5), ceil((double)(N % 5)/2));            
    }
    
    // Median of Medians(pivot)
    int pivot = func1(Medians, chunks, ceil((double)chunks / 2));
    
    int pivotIndex = -1;
    // Partitioning algorithm
    int i = -1;
    for (int j = 0; j <= N - 1; j++)
    {
        // Swap if small
        if (Arr[j] < pivot)
        {
            i++;
            swap(&Arr[i], &Arr[j]);
            if(i==pivotIndex)
                pivotIndex = j;
        }
        else if (Arr[j] == pivot)
            //If Pivot position changes
            pivotIndex = j;
    }
    // Swap pivot
    swap(&Arr[i + 1], &Arr[pivotIndex]);
    
    // breaking Arr into two arrays for recursive quick sort
    int Arr1[i + 1], Arr2[N - (i + 1)];
    for (int j = 0; j < i + 1; j++)
        Arr1[j] = Arr[j];
    for (int j = i + 2, k = 0; j < N; j++, k++)
        Arr2[k] = Arr[j];

    // Comparing if we need left half or right one
    if ((i + 1) > K - 1)
        func2(Arr1, i + 1, K);
    else if ((i + 1) < K - 1)
        func2(Arr2, N - (i + 2), K - (i + 2));
    else
        return Arr[i + 1];
}

void main()
{
    int N, K;
    // N: Total number of Inputs
    // K: Have to find Kth smallest number
    // Reading File
    FILE *fptr;
    fptr = fopen("ExampleFile.txt", "r");
    char line[255];
    size_t len = 255;
    int lineNo = 0;
    // line: getting file line by line
    // len: length of each line
    // lineNo: retrive Line number
    fgets(line, len, fptr);
    N = atoi(line);
    lineNo++;
    // Creating an array
    int Arr[N];
    int numbers = 0;
    // numbers: getting numbers in array
    // Reading whole file line by line
    while (fgets(line, len, fptr))
    {
        if (lineNo == 1)
            K = atoi(line);
        else
        {
            Arr[numbers] = atoi(line);
            numbers++;
        }
        lineNo++;
    }
    printf("The size of array is %d\nThe value of K is %d\nCalling func1:", N, K);
    int Arr1[N]; // As said in question for quicksort
    // Copying Arr to Arr1
    for (int i = 0; i < N; i++)
        Arr1[i] = Arr[i];
    // For Timing Calculation
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    printf("The %dth smallest element returned by func1 is %d\n", K, func1(Arr1, N, K));
    end = clock();
    cpu_time_used = ((double)(start - end)) / CLOCKS_PER_SEC;
    printf("The time taken by func1 is %f\nCalling func2:", clock());
    // Func2
    start = clock();
    printf("The %dth smallest element returned by func2 is %d\n", K, func2(Arr, N, K));
    end = clock();
    cpu_time_used = ((double)(start - end)) / CLOCKS_PER_SEC;
    printf("The time taken by func2 is %f", clock());
}
