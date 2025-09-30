//给定一个包含n个不同元素的实数数组A（下标从1开始）, 求 A 的最大和最小元素。
#include <iostream>
using namespace std;
void SelectMaxMin(int a[], int n, int& max, int& min) {
    max = a[0];
    min = a[0];
    for (int i = 1; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
        }
        if (min > a[i]) {
            min = a[i];
        }
    }
}

int main() {
    int arr[5] = { 1,2,3,4,5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int max, min;
    SelectMaxMin(arr, n, max, min);
    cout << "最大值：" << max << endl;
    cout << "最小值：" << min << endl;
    return 0;
}