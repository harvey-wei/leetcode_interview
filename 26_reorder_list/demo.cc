struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/**
 * Problems on linked list, tree, and graph need you to draw some examples by hand to understand
 * the problem statement and algorithms.
 * These problems have both recursive and iterative approaches oftentimes.
 */
class Solution {
public:
    ListNode* reverse_list(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;

        while (nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            // update curr and prev
            prev = curr;
            curr = next;
        }

        // curr == nullptr
        return prev;
    }

    void reorderList(ListNode* head)
    {
        /* Find the middle node of orignal list. */
        /**
         * Even-length list: 1->2->3->4, 3 is middle, i.e. head of second half.
         * Odd-length list: 1-2-3-4-5, 3 is middle.
         */
        if (nullptr == head || nullptr == head->next) return;

        ListNode* slow = head;
        ListNode* fast = head->next;

        while (nullptr != fast && nullptr != fast->next)
        {
            slow = slow->next;
            fast = fast->next;

            if (nullptr != fast) fast = fast->next;
        }

        /* Ensure left >= right */
        ListNode* second = slow->next;
        slow->next = nullptr;

        /* reverse the second half.*/
        /* The second is cut off from first half in th reverse_list. */
        second = reverse_list(second);

        /* Merge head of first to head of second iteratively. */
        ListNode* first = head;
        ListNode* temp;

        while (nullptr != first && nullptr != second)
        {
            // Define the repetive pattern by drawing some examples
            // Both for even-length and odd-length list.
            temp = first->next;
            first->next = second;
            first = temp;

            temp = second->next;
            second->next = first;
            second = temp;
        }

    }
};


int
main(int argc, char** argv)
{
    return 0;
}
