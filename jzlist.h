#include <vector>
#include <set>
#include <unordered_set>
struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};
using namespace std;

#if 0
// jz6 从尾到头打印链表
vector<int> result;
void myPrint(ListNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    myPrint(node->next);
    result.push_back(node->val);
}
vector<int> printListFromTailToHead(ListNode *head)
{
    if (head == nullptr)
        return {};
    myPrint(head);
    return result;
}
#endif 
// jz24 反转链表
// 迭代版本
ListNode *ReverseList1(ListNode *head)
{
    // write code here
    ListNode *cur = head;
    ListNode *prev = nullptr;
    while (cur)
    {
        ListNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

ListNode *ReverseList(ListNode *head)
{
    // write code here
    if (!head)
        return nullptr;
    if (head->next == nullptr)
        return head;
    ListNode *ret = ReverseList(head->next);
    ListNode *nxt = head->next;
    nxt->next = head;
    head->next = nullptr;
    return ret;
}

// jz25 合并两个排序的链表
ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
    // write code here
    ListNode *dummy = new ListNode(0);
    ListNode *k = dummy;
    while (pHead1 && pHead2)
    {
        if (pHead1->val < pHead2->val)
        {
            k->next = new ListNode(pHead1->val);
            pHead1 = pHead1->next;
            k = k->next;
        }
        else
        {
            k->next = new ListNode(pHead2->val);
            pHead2 = pHead2->next;
            k = k->next;
        }
    }
    if (pHead1)
    {
        k->next = pHead1;
    }
    if (pHead2)
    {
        k->next = pHead2;
    }
    return dummy->next;
}

// jz52 两个链表的第一个公共结点
ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
    // unordered_set<ListNode*> mySet;
    // while(pHead1){
    //     mySet.insert(pHead1);
    //     pHead1 = pHead1->next;
    // }

    // while(pHead2){
    //     if(mySet.find(pHead2) != mySet.end()){
    //         return pHead2;
    //     }
    //     pHead2 = pHead2->next;
    // }
    // return nullptr;
    ListNode *l1 = pHead1, *l2 = pHead2;
    while (l1 != l2)
    {
        l1 = (l1 == nullptr) ? pHead2 : l1->next;
        l2 = (l2 == nullptr) ? pHead1 : l2->next;
    }
    return l1;
}

// jz23 链表中环的入口节点
ListNode *EntryNodeOfLoop(ListNode *pHead)
{
    if (pHead == nullptr || pHead->next == nullptr)
    {
        return nullptr;
    }
    ListNode *slow = pHead, *fast = pHead;
    while (fast != nullptr || fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            break;
        }
    }
    slow = pHead;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// jz22 链表中的倒数最后k个结点
ListNode *FindKthToTail(ListNode *pHead, int k)
{
    if (pHead == nullptr)
        return pHead;
    if (k == 0)
        return nullptr;
    // write code here
    ListNode *dummy = new ListNode(0);
    dummy->next = pHead;
    ListNode *slow = dummy;
    ListNode *fast = dummy;
    for (int i = 0; i < k; i++)
    {
        fast = fast->next;
    }
    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
struct RandomListNode
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL)
    {
    }
};
// jz35 复杂链表的复制
RandomListNode *Clone(RandomListNode *pHead)
{
    if (pHead == nullptr)
        return nullptr;
    unordered_map<RandomListNode *, RandomListNode *> hash;
    RandomListNode *cur = pHead;
    while (cur)
    {
        RandomListNode *temp = new RandomListNode(cur->label);
        hash[cur] = temp;
        cur = cur->next;
    }
    cur = pHead;
    while (cur)
    {
        RandomListNode *temp = hash[cur];
        if (cur->next)
            temp->next = hash[cur->next];
        if (cur->random)
            temp->random = hash[cur->random];
        cur = cur->next;
    }
    return hash[pHead];
}

ListNode *deleteDuplication(ListNode *pHead)
{
    if (!pHead)
        return nullptr;
    ListNode *dummy = new ListNode(0);
    dummy->next = pHead;
    ListNode *prev = dummy;
    ListNode *start = pHead;
    ListNode *end = pHead;
    while (start && start->next)
    {
        if (start->val == start->next->val)
        {
            // 移动到最后一个
            while (end && end->val == start->val)
            {
                end = end->next;
            }
            // 此时end位于下一个数字或者为空
            prev->next = end;
            start = end;
        }
        else
        {
            start = start->next;
            end = end->next;
            prev = prev->next;
        }
    }
    return dummy->next;
}

// 优化
ListNode *deleteDuplicationFine(ListNode *pHead)
{
    if (!pHead)
        return nullptr;
    ListNode *dummy = new ListNode(0);
    dummy->next = pHead;
    ListNode *prev = dummy;
    while (pHead)
    {
        if (pHead->next && pHead->val == pHead->next->val)
        {
            while (pHead->next && pHead->val == pHead->next->val)
            {
                pHead = pHead->next;
            }
            prev->next = pHead->next;
        }
        else
        {
            prev = prev->next;
        }
        pHead = pHead->next;
    }
    return dummy->next;
}

ListNode *deleteNode(ListNode *head, int val)
{
    // write code here
    if(head == nullptr) return head;
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* cur = head;
    ListNode* prev = dummy;
    while(cur){
        if(cur->val == val){
            prev->next = cur->next;
        }else{
            prev = prev->next;
        }
        cur = cur->next;
    }
    return dummy->next;
}