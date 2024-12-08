#include <vector>
#include <unordered_map>
using namespace std;

vector<int> FindGreatestSumOfSubArray(vector<int> &array)
{
    // write code here
    int n = array.size();
    if (n == 0)
        return {};

    int maxSum = array[0];
    int curSum = array[0];
    int start = 0, end = 0;
    int tempStart = 0;
    for (int i = 1; i < n; i++)
    {
        if (curSum < 0)
        {
            curSum = array[i];
            tempStart = i;
        }
        else
        {
            curSum += array[i];
        }
        if (curSum >= maxSum)
        {
            maxSum = curSum;
            start = tempStart;
            end = i;
        }
    }
    return vector<int>(array.begin() + start, array.begin() + end + 1);
}

// jz69 跳台阶
int jumpFloor(int number)
{
    // write code here
    vector<int> dp(number + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < number + 1; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[number];
}

// jz10 斐波那契数列
int Fibonacci(int n)
{
    // write code here
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 1;
    for (int i = 3; i < n + 1; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// jz71 跳台阶扩展问题
int jumpFloorII(int number)
{
    // write code here
    vector<int> dp(number + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < number + 1; i++)
    {
        for (int j = 0; j < i; j++)
        {
            dp[i] += dp[j];
        }
    }
    return dp[number];
}

// jz70 矩形覆盖
int rectCover(int number)
{
    vector<int> dp(number + 1, 0);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < number + 1; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[number];
}

// jz47 礼物的最大价值
int maxValue(vector<vector<int>> &grid)
{
    // write code here
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
        }
    }
    return dp[m][n];
}

int lengthOfLongestSubstring(string s)
{
    // write code here

    int n = s.size();
    if (n == 0)
        return 1;
    unordered_map<char, int> hash; // char和出现的下标
    vector<int> dp(n, 0);
    dp[0] = 1;
    hash[s[0]] = 0;
    int result = dp[0];
    for (int i = 1; i < n; i++)
    {
        // abba
        //   2
        if (hash.count(s[i]) && hash[s[i]] >= i - dp[i - 1])
        {
            dp[i] = i - hash[s[i]];
        }
        else
        { // 没有
            dp[i] = dp[i - 1] + 1;
        }
        hash[s[i]] = i;
        result = max(result, dp[i]);
    }
    return result;
}

int getNum(string &nums, int index)
{
    if (index < 1)
    {
        return 0;
    }
    else
    {
        char cur = nums[index];
        char bef = nums[index - 1];
        int single = cur - '0';
        int ten = (bef - '0') * 10;
        return single + ten;
    }
}
// 3131
// cac
// cm

// 26
// be z

// 27
// bf

// 1227
// abb
// lb
//
// 320
// 111
int solve(string nums)
{
    if (nums == "0")
        return 0;
    if (nums == "10" || nums == "20")
        return 1;
    // 当0前面不是1和2
    for (int i = 1; i < nums.length(); i++)
    {
        if (nums[i] == '0')
            if (nums[i - 1] != '1' && nums[i - 1] != '2')
                return 0;
    }

    vector<int> dp(nums.length() + 1, 1);
    for (int i = 2; i <= nums.length(); i++)
    {
        if ((nums[i - 2] == '1' && nums[i - 1] != '0') ||
            (nums[i - 2] == '2' && nums[i - 1] > '0' && nums[i - 1] < '7'))
        {
            // 是11-19， 21-26
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        else
        {
            //20而言 你2取了几个 变成20是一样的
            dp[i] = dp[i - 1];
        }
    }
    return dp[nums.length()];
}