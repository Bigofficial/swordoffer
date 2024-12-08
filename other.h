#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<int> multiply(vector<int> &A)
{
    // write code here
    int n = A.size();
    vector<int> result(n, 1);

    for (int i = 1; i < n; i++)
    {
        result[i] *= result[i - 1];
        result[i] *= A[i - 1];
    }

    int temp = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        temp *= A[i + 1];
        result[i] *= temp;
    }
    return result;
}

int FirstNotRepeatingChar(string str)
{
    // write code here
    unordered_map<char, int> hash;
    for (char c : str)
    {
        hash[c]++;
    }
    for (int i = 0; i < str.size(); i++)
    {
        if (hash.count(str[i]) == 1)
        {
            return i;
        }
    }
    return -1;
}

// jz5 替换空格
string replaceSpace(string s)
{
    // write code here
    string sb;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            sb += '%20';
        }
        else
        {
            sb += s[i];
        }
    }
    return sb;
}

vector<int> reOrderArray(vector<int> &array)
{
    // write code here
    int j = 0; // 奇数的下一个位置
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] % 2 == 1)
        {
            int temp = array[i];

            for (int k = i - 1; k >= j; k--)
            {
                array[k + 1] = array[k];
            }

            array[j++] = temp;
        }
    }
    return array;
}

// jz39 数组中出现次数超过一半的
int MoreThanHalfNum_Solution(vector<int> &numbers)
{
    // write code here
    sort(numbers.begin(), numbers.end());
    int mid = 0 + (numbers.size() - 1 - 0) / 2;
    return numbers[mid];
}

struct cmp
{
    bool operator()(string &a, string &b)
    {
        return a + b < b + a;
    }
};
// a, b
// return a < b;
string PrintMinNumber(vector<int> numbers)
{
    string res = "";
    if (numbers.size() == 0)
        return res;
    vector<string> nums;
    for (int i = 0; i < numbers.size(); i++)
    {
        nums.push_back(to_string(numbers[i]));
    }

    sort(nums.begin(), nums.end(), cmp());

    for (int i = 0; i < nums.size(); i++)
        res += nums[i];
    return res;
}

int GetUglyNumber_Solution(int index)
{
    // write code here
    if (index <= 6)
        return index;
    int i2 = 0, i3 = 0, i5 = 0;
    vector<int> res(index);
    res[0] = 1;
    for (int i = 1; i < index; i++)
    {
        res[i] = min(res[i2] * 2, min(res[i3] * 3, res[i5] * 5));
        if (res[i] == res[i2] * 2)
        {
            i2++;
        }
        if (res[i] == res[i3] * 3)
        {
            i3++;
        }
        if (res[i] == res[i5] * 5)
        {
            i5++;
        }
    }
    return res[index - 1];
}

// jz74 合为S的连续正数序列

vector<vector<int>> FindContinuousSequence(int sum)
{
    // write code here
    vector<vector<int>> result;
    int start = 1, end = 2; // 初始化双指针
    while (start < end)
    {
        // 计算当前窗口的和
        int sum1 = (end - start + 1) * (start + end) / 2;

        if (sum1 == sum)
        {
            // 当前窗口和等于目标值，记录序列
            vector<int> temp;
            for (int i = start; i <= end; ++i)
                temp.push_back(i);
            result.push_back(temp);
            ++start; // 收缩窗口
        }
        else if (sum1 < sum)
        {
            ++end; // 扩大窗口
        }
        else
        {
            ++start; // 收缩窗口
        }
    }
    return result;
}

vector<int> FindNumbersWithSum(vector<int> array, int sum)
{
    unordered_set<int> mySet;
    for (int i = 0; i < array.size(); i++)
    {
        if (mySet.count(sum - array[i]))
        {
            // 有了
            return {array[i], sum - array[i]};
        }
        else
        {
            mySet.insert(array[i]);
        }
    }
    return {};
}

string LeftRotateString(string str, int n)
{
    if (str.size() == 0)
        return str;
    // write code here
    int size = str.size();
    n = n % size;
    if (n == 0)
        return str;

    reverse(str.begin(), str.end());
    reverse(str.begin(), str.begin() + size - n);
    reverse(str.begin() + size - n, str.end());
    return str;
}

int kids(int n, int m)
{
    if (n == 1)
        return 0;
    int x = kids(n - 1, m);
    return (m + x) % n;
}
// jz62 孩子们的游戏
int LastRemaining_Solution(int n, int m)
{
    // write code here
    if (n == 0 || m == 0)
        return -1;
    return kids(n, m);
}

class Solution_75
{
public:
    // Insert one char from stringstream
    void Insert(char ch)
    {

        // 每次插入时更新哈希表计数
        hash[ch]++;

        // 如果是第一次出现的字符，加入队列
        if (hash[ch] == 1)
        {
            que.push(ch);
        }

        // 保证队列的队首始终是第一个只出现一次的字符
        while (!que.empty() && hash[que.front()] > 1)
        {
            que.pop();
        }
    }
    // return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        if (que.empty())
            return '#';
        return que.front();
    }

private:
    queue<char> que;               // 先后顺序
    unordered_map<char, int> hash; // 次数
};

// jz14 剪绳子
// jz14 剪绳子
int cutRope(int n)
{
    // write code here
    if (n == 0 || n == 1)
        return n;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    // dp[i]: i长度的绳子可以取得的最大乘积
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            dp[i] = max(dp[i], max(dp[i - j] * j, (i - j) * j));
        }
    }
    return dp[n];
}

// jz81 调整数组顺序使奇数位于偶数前面
vector<int> reOrderArrayTwo(vector<int> &array)
{
    // write code here
    int i = 0;                // i:下一个奇数的位置
    int j = array.size() - 1; // j:下一个偶数的位置
    while (i < j)
    {
        if (array[i] % 2 == 1 && array[j] == 0)
        {
            // 左奇数 右偶数 正确指针向内收缩
            i++;
            j--;
        }
        else if (array[i] % 2 == 1 && array[j] % 2 == 1)
        {
            // 左奇数 右奇数
            i++;
        }
        else if (array[i] % 2 == 0 && array[j] % 2 == 1)
        {
            // 左偶数 右奇数
            swap(array[i], array[j]);
        }
        else
        {
            // 左偶数 右偶数
            j--;
        }
    }
    return array;
}
// jz83 剪绳子进阶版
const long long kRope = 998244353;
long long cutRope(long long number)
{
    // write code here
    if (number == 0 || number == 1)
        return number;
    vector<long long> dp(number + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    // dp[i]: i长度的绳子可以取得的最大乘积
    for (long long i = 2; i <= number; i++)
    {
        dp[i] = i;
        for (long long j = 1; j <= i / 2; j++)
        {
            dp[i] = max(dp[i], dp[i - j] * dp[j]);
        }
    }
    return dp[number] % kRope;
}

vector<int> printNumbers(int n)
{
    if (n == 0)
        return {};
    // write code here
    int temp = 9;
    vector<int> result;
    while (--n)
    {
        temp *= 10;
        temp += 9;
    }
    for(int i = 1; i <= temp; i++){
        result.push_back(i);
    }
    return result;
}