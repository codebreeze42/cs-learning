#include <iostream>
using namespace std;

void rearrangeArray(int arr[], int n)
{
    int left = 0, right = n - 1;

    while (left < right)
    {
        // 找到第一个非负数
        while (left < n && arr[left] < 0)
        {
            left++;
        }

        // 找到第一个负数
        while (right >= 0 && arr[right] >= 0)
        {
            right--;
        }

        // 如果 left < right，交换两个元素
        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
    }
}