//数组R由n个元素组成（下标从1开始），每个元素均为整数，现给定一个整数K，设计算法确定K是否是R的元素。
#include <iostream>
using namespace std;
bool isin(int arr[], int n, int K) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == K) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[5] = { 1,2,3,4,5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int K = 1;
    if (isin(arr, n, K)) {
        cout << "整数" << K << "在数组里" << endl;
    }
    else {
        cout << "整数" << K << "不在数组里" << endl;
    }
    return 0;
}