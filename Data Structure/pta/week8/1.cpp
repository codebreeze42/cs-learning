#include <iostream>
using namespace std;
int arr[2000] = {0};
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
int Partition(int arr[], int m, int n)
{
    int K = arr[m], L = m + 1, G = n;
    while (L <= G)
    {
        while (L <= n && arr[L] <= K)
            L++;
        while (arr[G] > K)
            G--;
        if (L < G)
        {
            swap(arr[L], arr[G]);
            L++;
            G--;
        }
    }
    swap(arr[m], arr[G]);
    return G;
}
void print(int arr[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void QuickSort(int arr[], int m, int n, int num)
{
    if (m < n)
    {
        int k = Partition(arr, m, n);
        print(arr, num);
        QuickSort(arr, m, k - 1, num);
        QuickSort(arr, k + 1, n, num);
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    QuickSort(arr, 1, n, n);
    print(arr, n);
    return 0;
}