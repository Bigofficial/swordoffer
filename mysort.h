#include <vector>
#include <queue>
using namespace std;
int duplicate(vector<int> &numbers)
{
    if (numbers.size() == 0)
        return -1;
    // write code here
    int n = numbers.size();
    for (int i = 0; i < n; i++)
    {
        if (numbers[i] == i)
        {
            // 正确位置
            continue;
        }
        else
        {
            if (numbers[numbers[i]] == numbers[i])
            {
                return numbers[i];
            }
            swap(numbers[i], numbers[numbers[i]]);
            i--;
        }
    }
    return 0;
}

const int kmod = 1000000007;
void MyMerge(vector<int> &arr, vector<int> &tmp, int l, int mid, int r, int &ret)
{
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (arr[i] > arr[j])
        {
            // 归并排序这左右两侧肯定有序
            tmp[k++] = arr[j++];
            // 我比你大，后头的都比你大
            ret += (mid - i + 1);
            ret %= kmod;
        }
        else
        {
            tmp[k++] = arr[i++];
        }
    }

    while (i <= mid)
    {
        tmp[k++] = arr[i++];
    }
    while (j <= r)
    {
        tmp[k++] = arr[j++];
    }
    for (k = 0, i = l; i <= r; ++i, ++k)
    {
        arr[i] = tmp[k];
    }
}
void MyMergeSort(vector<int> &arr, vector<int> &tmp, int l, int r, int &ret)
{
    if (l >= r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    MyMergeSort(arr, tmp, l, mid, ret);
    MyMergeSort(arr, tmp, mid + 1, r, ret);
    MyMerge(arr, tmp, l, mid, r, ret);
}
// jz51
int InversePairs(vector<int> &nums)
{
    // write code here
    int ret = 0;
    vector<int> tmp(nums.size());
    MyMergeSort(nums, tmp, 0, nums.size() - 1, ret);
    return ret;
}
struct MyComp
{
public:
    bool operator()(int a, int b)
    {
        return a < b;
    }
};
// jz40 最小的k个数
vector<int> GetLeastNumbers_Solution(vector<int> &input, int k)
{
    // write code here
    vector<int> ret;
    priority_queue<int, vector<int>, MyComp> que;
    if (k == 0 || k > input.size())
        return {};
    for (auto val : input)
    {
        if (que.size() < k)
        {
            que.push(val);
        }
        else
        {
            if (val < que.top())
            {
                que.pop();
                que.push(val);
            }
        }
    }
    while (!que.empty())
    {
        ret.push_back(que.top());
        que.pop();
    }
    return ret;
}

struct BigHeapComp
{
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

struct MinHeapComp
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

class Solution
{
public:
    void Insert(int num)
    {
        if (bigHeap.empty() || num < bigHeap.top())
        {
            bigHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }

        if (bigHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(bigHeap.top());
            bigHeap.pop();
        }
        else if (minHeap.size() > bigHeap.size())
        {
            bigHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double GetMedian()
    {

        int sizeBig = bigHeap.size();
        int sizeSmall = minHeap.size();
        if ((sizeBig + sizeSmall) % 2 == 0)
        {
            // 偶数
            return (bigHeap.top() + minHeap.top()) / 2.0;
        }
        else
        {
            // 奇数
            return bigHeap.top();
        }
    }

private:
    // 放小的
    priority_queue<int, vector<int>, BigHeapComp> bigHeap;
    // 放大的
    priority_queue<int, vector<int>, MinHeapComp> minHeap;
};