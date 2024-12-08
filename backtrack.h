#include <vector>

using namespace std;

#if 0 
vector<vector<int>> direction = {
    {0, 1},  // 上
    {1, 0},  // 右
    {0, -1}, // 下
    {-1, 0}  // 左
};

// bool backtrack(vector<vector<char>> &matrix, const string &word, vector<vector<bool>> &visited, int x, int y, int index)
// {
//     if (index == word.size()) // 找到完整路径
//         return true;

//     if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size() ||
//         visited[x][y] || matrix[x][y] != word[index])
//         return false;

//     visited[x][y] = true; // 标记为访问
//     for (auto &dir : direction)
//     {
//         int newX = x + dir[0], newY = y + dir[1];
//         if (backtrack(matrix, word, visited, newX, newY, index + 1))
//             return true;
//     }
//     visited[x][y] = false; // 回溯恢复状态
//     return false;
// }

// bool hasPath(vector<vector<char>> &matrix, string word)
// {
//     if (matrix.empty() || word.empty())
//         return false;

//     int m = matrix.size(), n = matrix[0].size();
//     vector<vector<bool>> visited(m, vector<bool>(n, false));

//     for (int i = 0; i < m; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             if (matrix[i][j] == word[0] && backtrack(matrix, word, visited, i, j, 0))
//                 return true;
//         }
//     }
//     return false;
// }

bool backtrack(vector<vector<char>> &matrix, string &word, vector<vector<bool>> visited, int x, int y, int index)
{
    if (index == word.size())
    {
        return true;
    }

    if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size() || visited[x][y] || matrix[x][y] != word[index])
    {
        return false;
    }

    visited[x][y] = true;
    for (auto &dir : direction)
    {
        int newX = x + dir[0], newY = y + dir[1];
        if (backtrack(matrix, word, visited, newX, newY, index + 1))
            return true;
    }
    visited[x][y] = false;
    return false;
}
bool hasPath(vector<vector<char>> &matrix, string word)
{
    // write code here

    if (matrix.empty() || word.empty())
    {
        return false;
    }

    int m = matrix.size(), n = matrix[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == word[0] && backtrack(matrix, word, visited, i, j, 0))
            {
                return true;
            }
        }
    }
    return false;
}
#endif

vector<vector<int>> direction = {
    {0, 1},  // 上
    {1, 0},  // 右
    {0, -1}, // 下
    {-1, 0}  // 左
};

int getDigit(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}
bool check(int threshold, int rows, int cols, int row, int col, vector<vector<bool>> &visited)
{
    if (row >= 0 && row < rows && col >= 0 && col < cols && getDigit(row) + getDigit(col) <= threshold && !visited[row][col])
    {
        return true;
    }
    return false;
}
int movingCountCore(int threshold, int rows, int cols, int row, int col, vector<vector<bool>> &visited)
{
    int count = 0;
    if (check(threshold, row, cols, row, col, visited))
    {
        visited[row][col] = true;
        count++;
        for (auto dir : direction)
        {
            int newRow = row + dir[0], newCol = col + dir[1];
            count += movingCountCore(threshold, rows, cols, newRow, newCol, visited);
        }
    }
    return count;
}
// jz13 机器人的运动范围
int movingCount(int threshold, int rows, int cols)
{
    if (threshold < 0 || rows <= 0 || cols <= 0)
        return 0;

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int count = movingCountCore(threshold, rows, cols, 0, 0, visited);

    return count;
}