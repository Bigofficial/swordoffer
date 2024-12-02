#include <vector>
#include <unordered_set>
using namespace std;

// jz53 数组在生序数组中出现的次数
int GetNumberOfK(vector<int> &nums, int k)
{
    if (nums.size() == 0)
        return 0;
    // write code here
    // find first
    int left = 0, right = nums.size() - 1;
    int first = -1, last = -2;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == k)
        {
            left = mid + 1;
            last = mid;
        }
        else if (nums[mid] < k)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == k)
        {
            right = mid - 1;
            first = mid;
        }
        else if (nums[mid] < k)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return last - first + 1;
}
// 1 0 1 1 1
//  jz11 旋转数组的最小数字
int minNumberInRotateArray(vector<int> &nums)
{
    // write code here

    int left = 0, right = nums.size() - 1;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right])
        {
            left = mid + 1;
        }
        else if (nums[mid] < nums[right])
        {
            right = mid;
        }
        else
        {
            right--;
        }
    }
    return nums[left];
}

vector<string> result;
string cur;
void backtrack(string str, unordered_set<int> myset)
{
    if (cur.size() == str.size())
    {
        result.push_back(cur);
    }

    for (int i = 0; i < str.size(); i++)
    {
        // 同层去重
        if (i > 0 && str[i] == str[i - 1] && (myset.find(i - 1) == myset.end()))
        {
            continue;
        }
        if (myset.find(i) == myset.end())
        {
            // 不存在
            myset.insert(i); // 不同层的话肯定有i，同层i就没有了
            cur += str[i];
            backtrack(str, myset);
            cur.erase(cur.end() - 1);
            myset.erase(i);
        }
    }
}
// jz38 字符串的排列
vector<string> Permutation(string str)
{
    // write code here
    if (str == "")
        return {""};
    sort(str.begin(), str.end());
    unordered_set<int> myset;
    backtrack(str, myset);
    return result;
}

// jz44 数字序列中某一位的数字
int findNthDigit(int n)
{
    // write code here
    int digit = 1;
    long start = 1; // 1, 10, 100
    long sum = 9; //当前区间总共有多少位数字
    while(n > sum){
        n -= sum;
        start *= 10;
        digit++;
        sum = 9 * start * digit; //9 * 10 * 2
    }
    // n-=sum;
    //此时n是这个区间的第几个数字 

    //n 在哪个数字上 我们上面-sum完，这里n最小就是1了，n-1就是表示第几个数字，0就是10。
    //这里我们要加上start 以start开始偏移 start这个数就是0  
    int num = start + (n - 1) / digit;
    // 1 
    // n在哪一位上
    int index = (n - 1) % digit; // 
    return to_string(num)[index] - '0';
}