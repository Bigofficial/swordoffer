#include <vector>
#include <unordered_set>
using namespace std;

vector<int> printMatrix(vector<vector<int>> matrix)
{
    vector<int> result;
    if (matrix.empty() || matrix[0].empty())
    {
        return result;
    }
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;

    while (top <= bottom && left <= right)
    {
        for (int i = left; i <= right; i++)
        {
            result.push_back(matrix[top][i]);
        }
        ++top;

        for (int i = top; i <= bottom; i++)
        {
            result.push_back(matrix[i][right]);
        }
        --right;

        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
            {
                result.push_back(matrix[bottom][i]);
            }
            --bottom;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
            {
                result.push_back(matrix[i][left]);
            }
            ++left;
        }
    }
    return result;
}

// jz61 扑克牌顺子
bool IsContinuous(vector<int> &numbers)
{
    unordered_set<int> mySet;
    sort(numbers.begin(), numbers.end());
    int zeroCount = 0;
    // write code here
    for (int num : numbers)
    {
        if (num)
        {
            if (mySet.find(num) != mySet.end())
            {
                return false;
            }
            mySet.insert(num);
        }
        else
        {
            zeroCount++;
        }
    }

    int before = numbers[zeroCount];
    for (int i = zeroCount + 1; i < numbers.size(); i++)
    {
        int gap = numbers[i] - before - 1;
        if (gap > zeroCount)
        {
            return false;
        }
        else
        {
            // 0可以填补
            zeroCount -= gap;
            before = numbers[i];
        }
    }
    return true;
}
// 检查无符号部分
bool scanUnsignedInteger(const string &str, int &index)
{
    int start = index;
    while (index < str.size() && isdigit(str[index]))
    {
        index++;
    }
    return index > start;
}
// 检查有符号部分
bool scanInteger(const string &str, int &index)
{
    if (index < str.size() && (str[index] == '+' || str[index] == '-'))
    {
        index++;
    }
    return scanUnsignedInteger(str, index);
}
bool isNumeric(string str)
{
    // write code here
    if (str.empty())
        return false;
    int index = 0;
    int n = str.size();

    while (index < n && str[index] == ' ')
    {
        index++;
    }

    bool isValid = scanInteger(str, index);
    if (index < n && str[index] == '.')
    {
        index++;
        // 小数可以没有整数部分也就是前面 但不能没有数字
        isValid = scanUnsignedInteger(str, index) || isValid;
    }

    // 科学计数法
    if (index < n && (str[index] == 'e' || str[index] == 'E'))
    {
        index++;
        isValid = isValid && scanInteger(str, index);
    }

    // 跳过结尾空格
    while (index < n && str[index] == ' ')
    {
        index++;
    }
    return isValid && index == n;
}