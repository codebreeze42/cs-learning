// 二分查找
int BinartSearch(int R[], int n, int k)
{
    int low = 1, high = n, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (k < R[mid])
            high = mid - 1;
        else if (k > R[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
// 斐波那契查找
int Fibsearch(int R[], int n, int K, int F[], int k)
{
    int low = 1, high = n;
    while (low <= high)
    {
        int mid = low + F[k - 1] - 1;
        if (K < R[mid])
        {
            k--;
            high = mid - 1;
        }
        else if (K > R[mid])
        {
            k -= 2;
            low = mid + 1;
        }
        else
            return mid;
    }
    return -1;
}
// 插值查找
int InterpolationSearch(int R[], int n, int k)
{
    int low = 1, high = n, mid;
    while (low <= high && k <= R[high] && k >= R[low])
    {
        if (R[low] == R[high])
            return high;
        mid = low + (high - low) / (R[high] - R[low]);
        if (k > R[mid])
            low = mid + 1;
        else if (k < R[mid])
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}