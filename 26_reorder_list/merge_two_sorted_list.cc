/**
 * Definition for singly-linked list.
 */

struct ListNode
{
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode dummy_head = ListNode();
        ListNode* tail = &dummy_head;

        /* One picture is worth a thousand words. */
        while (nullptr != list1 && nullptr != list2)
        {
            if (list1->val < list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }

            // update tail
            tail = tail->next;
        }

        // trailing nullptr
        tail->next = list1 == nullptr ? list2 : list1;

        return dummy_head.next;
    }
};
