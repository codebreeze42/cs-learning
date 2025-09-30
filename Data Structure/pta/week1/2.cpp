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
void ShiftDown(int R[], int i, int left, int right)
{
    int offset = left - 1;
    while (i - offset <= (right - offset) / 2)
    {
        int maxchd = 2 * i - offset;
        if (maxchd + 1 <= right && R[maxchd] < R[maxchd + 1])
            maxchd++;
        if (R[i] >= R[maxchd])
            return;
        swap(R[maxchd], R[i]);
        i = maxchd;
    }
}

void BuildHeap(int R[], int left, int right)
{
    for (int i = (right - left) / 2 + left; i >= left; i--)
    {
        ShiftDown(R, i, left, right);
    }
    printf("Heap:");
    for (int i = left; i <= right; i++)
    {
        printf("%d ", R[i]);
    }
    printf("\n");
}
void HeapSort(int R[], int left, int right)
{
    BuildHeap(R, left, right);
    for (int i = right; i > left; i--)
    {
        swap(R[left], R[i]);
        ShiftDown(R, left, left, i - 1);
    }
}
void three(int R[], int m, int n)
{
    swap(R[(m + n) / 2], R[m + 1]);
    if (R[m + 1] > R[n])
        swap(R[m + 1], R[n]);
    if (R[m] > R[n])
        swap(R[m], R[n]);
    if (R[m + 1] > R[m])
        swap(R[m + 1], R[m]);
}
void Partition3way(int R[], int m, int n, int &i, int &k)
{
    int j, pivot;
    i = m, j = m, k = n, pivot = R[m];
    while (j <= k)
    {
        if (R[j] < pivot)
        {
            swap(R[j], R[i]);
            j++;
            i++;
        }
        else if (R[j] > pivot)
        {
            swap(R[j], R[k]);
            k--;
        }
        else
            j++;
    }
}

void QuickSort(int R[], int m, int n, int depth_limit)
{

    while (n - m + 1 > threshold)
    {
        if (depth_limit == 0)
        {
            HeapSort(R, m, n);
            return;
        }
        int i, k;
        three(R, m, n);
        Partition3way(R, m, n, i, k);

        if (i - m < n - k)
        {
            QuickSort(R, m, i - 1, depth_limit - 1);
            m = k + 1;
        }
        else
        {
            QuickSort(R, k + 1, n, depth_limit - 1);
            n = i - 1;
        }
        depth_limit--;
        if (depth_limit == 0)
        {
            HeapSort(R, m, n);
            return;
        }
    }
}
void sort(int *R, int n)
{
    double limit = log2(n);
    int depth_limit = 2.0 * limit;
    printf("depth_limit:");
    printf("%d\n", depth_limit);
    QuickSort(R, 1, n, depth_limit);
    printf("Intermediate:");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", R[i]);
    }
    printf("\n");
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
