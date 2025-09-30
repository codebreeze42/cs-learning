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
    // 堆元素R[i]下沉, 数组R[ ]存储堆, n为堆包含的元素个数
    int offset = left - 1;
    while (i - offset <= (right - offset) / 2)
    {                                // i最多下行至最后一个非叶结点
        int maxchd = 2 * i - offset; // 假定最大孩子为左孩子
        if (maxchd + 1 <= right && R[maxchd] < R[maxchd + 1])
            maxchd++; // i的右孩子是最大孩子
        if (R[i] >= R[maxchd])
            return;
        swap(R[maxchd], R[i]); // R[i]的最大孩子比R[i]大
        i = maxchd;            // 结点i继续下沉
    }
}

void BuildHeap(int R[], int left, int right)
{
    // int offset=left-1;
    for (int i = (right - left) / 2 + left; i >= left; i--)
    {
        ShiftDown(R, i, left, right);
    }
    // for (int i = left; i <= right; i++)
    // {
    //     if (i == left && i != right)
    //         cout << "Heap:";
    //     cout << R[i] << " ";
    //     if (i == right && i != left)
    //         cout << endl;
    // }
    // for (int i = left; i <= right; i++)
    // {
    //     if (i == left )
    //         cout << "Heap:";
    //     cout << R[i] << " ";
    //     if (i == right)
    //         cout << endl;
    // }
    printf("Heap:");
    // cout << "Heap:";
    for (int i = left; i <= right; i++)
    {
        printf("%d ", R[i]);
        // cout << R[i] << " ";
    }
    // cout << endl;
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

void QuickSort(int R[], int m, int n, int depth_limit)
{

    if (n - m + 1 > threshold)
    {
        if (depth_limit == 0)
        {
            HeapSort(R, m, n);
            return;
        }
        int k = Partition(R, m, n);
        QuickSort(R, m, k - 1, depth_limit - 1);
        QuickSort(R, k + 1, n, depth_limit - 1);
    }
}
void sort(int *R, int n)
{
    double limit = log2(n);
    int depth_limit = 2.0 * limit;
    printf("depth_limit:");
    printf("%d\n", depth_limit);
    // cout << "depth_limit:" << depth_limit << endl;
    QuickSort(R, 1, n, depth_limit);
    printf("Intermediate:");
    // cout << "Intermediate:";
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", R[i]);
        // cout << R[i] << " ";
    }
    printf("\n");
    // cout << endl;
    InsertionSort(R, n);
}