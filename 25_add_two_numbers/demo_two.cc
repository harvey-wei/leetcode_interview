struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverse_list(ListNode* head)
    {
        if (nullptr == head)
        {
            return nullptr;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next;

        while (nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            // update curr and prev
            prev = curr;
            curr = next;
        }

        /* At this point, curr is empty tail node and prev is the new head. */
        return prev;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /* List is guaranteed to be non-empty. */
        l1 = reverse_list(l1);
        l2 = reverse_list(l2);

        ListNode* ptr_l1 = l1;
        ListNode* ptr_l2 = l2;

        ListNode dummy = ListNode();
        ListNode* ptr_sum = &dummy;

        int curr_sum = 0;
        int carry = 0;

        while (nullptr != ptr_l1 || nullptr != ptr_l2)
        {
            curr_sum = ((nullptr != ptr_l1) ? ptr_l1->val : 0) +
                    ((nullptr != ptr_l2) ? ptr_l2->val : 0) + carry;

            /* update curr_sum and carry */
            carry = curr_sum / 10;
            curr_sum = curr_sum % 10;

            ptr_sum->next = new ListNode(curr_sum);

            /* update ptr_l1 , ptr_l2, and ptr_sum */
            if (nullptr != ptr_l1) ptr_l1 = ptr_l1->next;
            if (nullptr != ptr_l2) ptr_l2 = ptr_l2->next;

            ptr_sum = ptr_sum->next;
        }

        /* Deal with the last non-zero carry! */
        if (carry > 0)
        {
            ptr_sum->next = new ListNode(carry);
        }

        return reverse_list(dummy.next);
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
