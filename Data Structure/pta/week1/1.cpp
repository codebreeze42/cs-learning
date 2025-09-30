#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int threshold;
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void InsertionSort(int R[], int n)
{
    for (int i = 2; i <= n; i++)
    {
        int K = R[i], j = i - 1;
        while (j >= 1 && R[j] > K)
        {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = K;
    }
}
int Partition(int R[], int m, int n)
{
    int K = R[m], L = m + 1, G = n;
    while (L <= G)
    {
        while (L <= n && R[L] <= K)
            L++;
        while (R[G] > K)
            G--;
        if (L < G)
        {
            swap(R[L], R[G]);
            L++;
            G--;
        }
    }
    swap(R[m], R[G]);
    return G;
}
void ShiftDown(int R[], int left, int right)
{
    while (left <= right / 2)
    {
        int maxchd = 2 * left;
        if (maxchd + 1 <= right && R[maxchd] < R[maxchd + 1])
            maxchd++;
        if (R[left] >= R[maxchd])
            return;
        swap(R[maxchd], R[left]);
        left = maxchd;
    }
}

void BuildHeap(int R[], int left, int right)
{
    for (int i = right / 2; i >= left; i--)
    {
        ShiftDown(R, left, right);
    }
    for (int i = left; i <= right; i++)
    {
        if (i == left && i != right)
            cout << "Heap:";
        cout << R[i] << " ";
        if (i == right && i != left)
            cout << endl;
    }
}
void HeapSort(int R[], int left, int right)
{
    BuildHeap(R, left, right);
    for (int i = right; i > left; i--)
    {
        swap(R[left], R[i]);
        ShiftDown(R, left, i - 1);
    }
}

void QuickSort(int R[], int m, int n, int depth_limit)
{
    if (depth_limit == 0)
    {
        HeapSort(R, m, n);
    }
    if (n - m + 1 > threshold)
    {
        int k = Partition(R, m, n);
        QuickSort(R, m, k - 1, depth_limit - 1);
        QuickSort(R, k + 1, n, depth_limit - 1);
    }
}
void sort(int *R, int n)
{
    double limit = log2(n);
    int depth_limit = 2.0 * limit;
    cout << "depth_limit:" << depth_limit << endl;
    QuickSort(R, 1, n, depth_limit);
    cout << "Intermediate:";
    for (int i = 1; i <= n; i++)
    {
        cout << R[i] << " ";
    }
    cout << endl;
    InsertionSort(R, n);
}
int main()
{
    int n, i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    sort(a, n);

    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
