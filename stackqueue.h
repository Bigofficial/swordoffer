#include <stack>
#include <queue>
using namespace std;

#if 0
//jz9 用两个栈实现队列
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int result = stack2.top();
        stack2.pop();
        return result;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
#endif

#if 0
//jz30 包含min函数的栈
class Solution
{
public:
    void push(int value)
    {
        if(minSta.empty() ||  value < minSta.top()){
            minSta.push(value);
        }else{
            minSta.push(minSta.top());
        }
        sta.push(value);
    }
    void pop()
    {
        sta.pop();
        minSta.pop();
    }
    int top()
    {
        return sta.top();
    }
    int min()
    {
        return minSta.top();
    }
private:
    stack<int> sta;
    stack<int> minSta;
};
#endif

#if 0
// jz31 栈的压入 弹出序列
bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
{
    // write code here
    stack<int> sta;
    int j = 0;
    for (int i = 0; i < pushV.size(); i++)
    {
        sta.push(pushV[i]);
        while (!sta.empty() && popV[j] == sta.top())
        {
            sta.pop();
            j++;
        }
    }
    if (!sta.empty())
        return false;
    return true;
}
#endif

// am I

// jz73 翻转单词序列
string ReverseSentence(string str)
{
    stack<string> words;
    string word;
    for (char c : str)
    {
        if (c != ' ')
        {
            word += c;
        }
        else
        {
            if (!word.empty())
            {
                words.push(word);
                word.clear();
            }
        }
    }

    if (!word.empty())
    {
        words.push(word);
    }

    string result;
    while (!words.empty())
    {
        result += words.top();
        words.pop();
        if (!words.empty())
        {
            result += " ";
        }
    }
    return result;
}

class MyQueue
{
public:
    void push(int val)
    {
        while (!que.empty() && val > que.back())
        {
            que.pop_back();
        }
        que.push_back(val);
    }

    void pop(int val)
    {
        if (!que.empty() && que.front() == val)
        {
            que.pop_front();
        }
    }

    int front()
    {
        return que.front();
    }

private:
    deque<int> que;
};
// jz59 滑动窗口的最大值
vector<int> maxInWindows(vector<int> &num, int size)
{
    if (num.empty() || size > num.size() || size == 0)
    {
        return {};
    }
    // write code here
    vector<int> result;
    MyQueue myQueue;
    for (int i = 0; i < size; i++)
    {
        myQueue.push(num[i]);
    }
    result.push_back(myQueue.front());

    for (int i = size; i < num.size(); i++)
    {
        myQueue.push(num[i]);
        myQueue.pop(num[i - size]);
        result.push_back(myQueue.front());
    }

    return result;
}