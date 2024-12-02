#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define INT_MAX 255678;
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {
    }
};

struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL)
    {
    }
};

// jz55 二叉树深度
int TreeDepth(TreeNode *pRoot)
{
    if (!pRoot)
        return 0;
    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);
    return max(left, right) + 1;
}

#if 0
vector<int> result;
void midTraversal(TreeNode* root){
    if(!root) return;
    midTraversal(root->left);
    result.push_back(root->val);
    midTraversal(root->right);
}
//jz54 二叉搜索树的第k个结点 第k小
int KthNode(TreeNode *proot, int k)
{
    // write code here
    if(!proot || k == 0) return -1;
    // 中序遍历 取第k个
    midTraversal(proot);
    if(k > result.size()) return -1;
    return result[k - 1];
}
#endif

TreeNode *myReconstruct(vector<int> &preOrder, vector<int> &vinOrder, int preStart, int preEnd, int inStart, int inEnd)
{
    if (preStart > preEnd || inStart > inEnd)
        return nullptr;
    int rootVal = preOrder[preStart];
    TreeNode *root = new TreeNode(rootVal);
    // 找到中序遍历中根结点位置
    int i = inStart;
    while (vinOrder[i] != rootVal)
    {
        i++;
    }
    // 此时i为中序遍历中根节点下标记
    int leftSize = i - inStart;
    root->left = myReconstruct(preOrder, vinOrder, preStart + 1, preStart + leftSize, inStart, i - 1);
    root->right = myReconstruct(preOrder, vinOrder, preStart + leftSize + 1, preEnd, i + 1, inEnd);
    return root;
}
// jz7 重建二叉树
TreeNode *reConstructBinaryTree(vector<int> &preOrder, vector<int> &vinOrder)
{
    if (preOrder.size() == 0 && vinOrder.size() == 0)
        return nullptr;
    // write code here
    return myReconstruct(preOrder, vinOrder, 0, preOrder.size() - 1, 0, vinOrder.size() - 1);
}
bool IsSub(TreeNode *pRoot1, TreeNode *pRoot2)
{
    // 判断两棵树是否相同
    if (!pRoot2)
        return true;
    if (!pRoot1 || pRoot1->val != pRoot2->val)
    {
        return false;
    }
    return IsSub(pRoot1->left, pRoot2->left) &&
           IsSub(pRoot1->right, pRoot2->right);
}

bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
{
    if (pRoot1 == nullptr || pRoot2 == nullptr)
        return false;
    if (IsSub(pRoot1, pRoot2))
    {
        return true;
    }
    if (HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// jz27 二叉树的镜像
TreeNode *Mirror(TreeNode *pRoot)
{
    // write code here
    if (pRoot == nullptr)
        return nullptr;
    TreeNode *left = Mirror(pRoot->left);
    TreeNode *right = Mirror(pRoot->right);
    pRoot->left = right;
    pRoot->right = left;
    return pRoot;
}

vector<int> PrintFromTopToBottom(TreeNode *root)
{
    if (root == nullptr)
        return {};
    queue<TreeNode *> que;
    vector<int> result;
    que.push(root);
    while (!que.empty())
    {
        int size = que.size();
        for (int i = 0; i < que.size(); i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            result.push_back(temp->val);
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
    }
    return result;
}

bool check(vector<int> &sequence, int l, int r)
{
    if (l >= r)
        return true; // 一个结点

    int root = sequence[r]; // 根节点
    int j = r - 1;          // 划分右子树
    while (j >= 0 && sequence[j] > root)
        j--;
    // 此时j为小于root的或者为0
    for (int i = l; i <= j; i++)
    {
        if (sequence[i] > root)
            return false;
    }
    return check(sequence, l, j) && check(sequence, j + 1, r - 1);
}
// jz33 二叉搜索树的后序遍历序列
bool VerifySquenceOfBST(vector<int> sequence)
{
    int n = sequence.size();
    if (n == 0)
        return false;
    return check(sequence, 0, n - 1);
}

#if 0
TreeNode *preNode = nullptr;
void inorder(TreeNode *root)
{
    if (!root)
        return;
    inorder(root->left);
    root->left = preNode;
    if (preNode)
    {
        preNode->right = root;
    }
    preNode = root;
    inorder(root->right);
}
// jz36 二叉搜索树与双向链表
TreeNode *Convert(TreeNode *pRootOfTree)
{
    if (!pRootOfTree)
        return nullptr;
    TreeNode *p = pRootOfTree;
    while (p->left)
        p = p->left;
    inorder(pRootOfTree);
    return p;
}
#endif

int getHeight(TreeNode *root)
{
    if (!root)
        return 0;
    int left = getHeight(root->left);
    if (left == -1)
        return -1;
    int right = getHeight(root->right);
    if (right == -1)
        return -1;
    if (abs(right - left) > 1)
        return -1;
    return max(left, right) + 1;
}
// jz79 判断是不是平衡二叉树
bool IsBalanced_Solution(TreeNode *pRoot)
{
    // write code here
    return getHeight(pRoot) != -1;
}

TreeLinkNode *GetNext(TreeLinkNode *pNode)
{
    if (pNode->right)
    {
        TreeLinkNode *rchild = pNode->right;
        while (rchild->left)
            rchild = rchild->left;
        return rchild;
    }

    else if (pNode->next && pNode->next->left == pNode)
    {
        return pNode->next;
    }
    else
    {
        if (pNode->next)
        {
            TreeLinkNode *parent = pNode->next;
            while (parent->next && parent->next->right == parent)
                parent = parent->next;
            return parent->next;
        }
        return nullptr;
    }
}

// jz78 把二叉树打印成多行
vector<vector<int>> Print(TreeNode *pRoot)
{
    // write code here
    if (!pRoot)
        return {{}};
    vector<vector<int>> result;
    queue<TreeNode *> que;
    que.push(pRoot);
    while (!que.empty())
    {
        int size = que.size();
        vector<int> level;
        for (int i = 0; i < size; i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            level.push_back(temp->val);
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
        result.push_back(level);
    }
    return result;
}

const int INF = INT_MAX;
char *Serialize(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    string result;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        if (node)
        {
            result += to_string(node->val) + "_";
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            result += to_string(INF) + "_";
        }
    }

    char *serialized = new char[result.size() + 1];
    strcpy(serialized, result.c_str());
    return serialized;
}
TreeNode *Deserialize(char *str)
{
    if (!str || strlen(str) == 0)
        return nullptr;
    vector<string> nodes; // 就是二叉树各个结点 存放的是数字to字符串
    string token;
    const char *ptr = str;
    // 放入一个个结点数字
    while (*ptr != '\0')
    {
        if (*ptr == '_')
        {
            // 12_
            nodes.push_back(token);
            token.clear();
        }
        else
        {
            token += *ptr;
        }
        ++ptr;
    }
    TreeNode *root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode *> q;
    q.push(root);
    int n = nodes.size();
    for (int i = 1; i < n - 1; i += 2)
    { // 一次出来左右结点
        TreeNode *parent = q.front();
        q.pop();

        int leftVal = stoi(nodes[i]);
        if (leftVal != INF)
        {
            parent->left = new TreeNode(leftVal);
            q.push(parent->left);
        }

        int rightVal = stoi(nodes[i + 1]);
        if (rightVal != INF)
        {
            parent->right = new TreeNode(rightVal);
            q.push(parent->right);
        }
    }
    return root;
}

#if 0
int backtrack(TreeNode *root, int sum, int curSum, unordered_map<int, int> &hash)
{
    if (!root)
        return 0;

    int result = 0;
    curSum += root->val;

    if (hash.count(curSum - sum))
    {
        result += hash[curSum - sum];
    }

    hash[curSum]++;

    result += backtrack(root->left, sum, curSum, hash);
    result += backtrack(root->right, sum, curSum, hash);

    hash[curSum]--;
    return result;
}
//{0}, 0 :1
//{0,1,1} 1: 4
int FindPath(TreeNode *root, int sum)
{
    if (!root)
        return 0;
    // write code here
    unordered_map<int, int> hash; // sum count
    hash[0] = 1;
    return backtrack(root, sum, 0, hash);
}
#endif

#if 0
TreeNode *postTraversal(TreeNode *root, int o1, int o2)
{
    if (!root || root->val == o1 || root->val == o2)
        return root;
    TreeNode *left = postTraversal(root->left, o1, o2);
    TreeNode *right = postTraversal(root->right, o1, o2);
    if (left && right)
    {
        return root;
    }
    else if (!left && right)
    {
        return right;
    }
    else if (left && !right)
    {
        return left;
    }
    else
    {
        // 都为空
        return nullptr;
    }
}
// jz86 在二叉树中找到两个结点的最近公共祖先
int lowestCommonAncestor(TreeNode *root, int o1, int o2)
{
    // write code here
    // 要看完左右孩子我们才能做决定，得用后序遍历
    return postTraversal(root, o1, o2)->val;
}
#endif

TreeNode * traversalLCA(TreeNode* root, int p, int q){
    if(!root) return nullptr;
    if(root->val > p && root->val > q){
        TreeNode* left = traversalLCA(root->left, p, q);
        if(left) return left;
    }
    if(root->val < q && root->val < p){
        TreeNode* right = traversalLCA(root->right, p, q);
        if(right) return right;
    }
    return root;
}
// jz68 二叉搜索树的最近公共祖先
int lowestCommonAncestor(TreeNode *root, int p, int q)
{
    // write code here
    TreeNode* result = traversalLCA(root, p, q);
    return result->val;

}