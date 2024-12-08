#include <vector>
using namespace std;
// jz65 不用加减乘除做加法
int Add(int num1, int num2)
{
    int add = num2;
    int sum = num1;
    while (add)
    {
        int temp = sum ^ add;
        add = (sum & add) << 1;
        sum = temp;
    }
    return sum;
}

// jz15 二进制中1的个数
int NumberOf1(int n)
{
    // write code here
    int res = 0;
    for (int i = 0; i < 32; i++)
    {
        if (n & (1 << i))
            res++;
    }
    return res;
}

// jz16 数值的整数次方
double Power(double base, int exponent)
{
    double res = 1.0;
    if (exponent < 0)
    {
        base = 1 / base;
        exponent = -exponent;
    }
    for (int i = 0; i < exponent; i++)
    {
        res *= base;
    }
    return res;
}
// jz56 数组中只出现一次的两个数
vector<int> FindNumsAppearOnce(vector<int> &nums)
{
    // write code here
    // 0001 0100 0001
    // 0101
    // 0001
    // 0100
    int tmp = 0;
    for (int num : nums)
    {
        tmp ^= num;
    }
    int mask = 1;
    while ((tmp & mask) == 0)
    {
        mask << 1;
    }

    int a = 0;
    int b = 0;
    for (int num : nums)
    {
        if ((num & mask) == 0)
        {
            a ^= num;
        }
        else
        {
            b ^= num;
        }
    }
    if (a > b)
    {
        int c = a;
        a = b;
        b = c;
    }
    return {a, b};
}

// jz64  求1+2+3+...+n
int Sum_Solution(int n)
{
    n && (n += Sum_Solution(n - 1));
    return n;
}