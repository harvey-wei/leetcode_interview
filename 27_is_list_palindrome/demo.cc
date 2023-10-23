struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution { public: ListNode* bisect_list(ListNode* head) {
        /* zero and singleton list can not be biscected! */
        if (nullptr == head || nullptr == head->next) return nullptr;

        /* Both fast and slow start from the head in which cases we count the # of edges. */
        /*
         * Even # of nodes: 1->2->3->4->5->6
         * Fast: 1, 3, 5 but fast->next is not null
         * Slow: 1, 2, 3  but  4 as the head of second half
         * Odd # of nodes: 1->2->3->4->5
         * Fast: 1, 3, 5 fast->next == null
         * Slow: 1, 2, 3 but 4 as the head of a second half
         * But the rear half has one more nodes than the front half!
         *
         * Fail if there are only two nodes.
         * 1->2
         * Fast: 1
         * Slow: 1
         *
         * Hence, we need to start from a imagine dummy head to make the number of steps == # of
         nodes.
         * Even # of nodes: 1->2->3->4->5->6
         * Fast: 2, 4, 6 => fast->next == null
         * Slow: 1, 2, 3  but  4 as the head of second half

         * Odd # of nodes: 1->2->3->4->5
         * Fast: 2, 4 => fast->next != null
         * Slow: 1, 2 but 4 as the head of a second half
         */

        /* start from a virtual dummy head! */
        ListNode* fast = head->next;
        ListNode* slow = head;

        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode* rear;

        if (nullptr == fast->next)
        {
            /* Even # of nodes. */
            rear = slow->next;
            slow->next = nullptr;
        }
        else
        {
            /* Odd # of nodes. */
            rear = slow->next;
            slow->next = nullptr;
            ListNode* temp = rear->next;
            rear->next = nullptr;
            rear = temp;
        }

        return rear;
    }

    ListNode* reverse_list(ListNode* head)
    {
        if (nullptr == head) return nullptr;

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next;

        while (nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            /* update prev, curr, and next */
            prev = curr;
            curr = next;
        }

        /* curr == null but pev is the new head */
        return prev;
    }

    bool is_equal(ListNode* front, ListNode* rear)
    {
        /* Note that fron list may have one more nodes than that of the rear list */
        while (nullptr != rear)
        {
            if (rear->val != front->val) return false;

            // update front and rear
            rear = rear->next;
            front = front->next;
        }

        return true;

    }

    bool isPalindrome(ListNode* head) {
        /* step 1: biscect the given list.
         * work a few example to handle even-length and odd-length list.
         */
        ListNode* rear = bisect_list(head);

        /* step 2: reverse the rear half. */
        rear = reverse_list(rear);

        /* step 3: compare the front half and rear half. */

        return is_equal(head, rear);
    }
};

int
main(int argc, char** argv)
{
    return 0;
}

