//算法SelectMaxMin的改进算法BinarySelect
#include <iostream>
using namespace std;
void BinarySelect(int arr[], int i, int j, int& max, int& min) {
    if (i == j) {
        min = max = arr[i];
        return;
    }
    if (i == j - 1) {
        if (arr[i] > arr[j]) {
            max = arr[i];
            min = arr[j];
            }
        else {
            max = arr[j];
            min = arr[i];
        }
        return; //if循环之后只放一个return，减少冗余
    }
    int mid = (i + j) / 2;
    int Lmax, Lmin, Rmax, Rmin;
    BinarySelect(arr, i, mid, Lmax, Lmin);
    BinarySelect(arr, mid + 1, j, Rmax, Rmin);
    if (Lmax > Rmax) {
        max = Lmax;
    }
    else {
        max = Rmax;
    }

    if (Lmin > Rmin) {
        min = Rmin;
    }
    else {
        min = Lmin;
    }
}

int main() {
    int arr[] = { 0,1,2,3,4,5 };
    int max, min;
    int i = 0;
    int j = 5;
    BinarySelect(arr, i, j, max, min);
    cout << "最大值为：" << max << endl;
    cout << "最小值为：" << min << endl;
    return 0;
}