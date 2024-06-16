struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// https://leetcode.com/problems/add-two-numbers-ii/
class Solution {
public:
    ListNode* reverse_list(ListNode* head)
    {
        if (nullptr == head) return head;

        /* Point the curr->next to prev*/
        /* For the head, its prev is null.*/
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

        // curr == nullptr. prev is new head
        return prev;

    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode dummy_head = ListNode(0, nullptr);
        ListNode* curr = &dummy_head;

        l1 = reverse_list(l1);
        l2 = reverse_list(l2);

        ListNode* l1_ptr = l1;
        ListNode* l2_ptr = l2;
        int sum = 0;
        int carry = 0;
        ListNode* curr_sum_node;

        while (nullptr != l1_ptr && nullptr != l2_ptr)
        {
            sum = l1_ptr->val + l2_ptr->val + carry;
            carry = sum / 10;
            sum -= 10 * carry;

            curr_sum_node = new ListNode(sum);
            curr->next = curr_sum_node;

            // Advance l1_ptr and l2_ptr
            l1_ptr = l1_ptr->next;
            l2_ptr = l2_ptr->next;

            curr = curr->next;
        }

        while (nullptr != l1_ptr)
        {
            sum = l1_ptr->val + carry;
            carry = sum / 10;
            sum -= 10 * carry;

            curr_sum_node = new ListNode(sum);
            curr->next = curr_sum_node;

            l1_ptr = l1_ptr->next;
            curr = curr->next;
        }

        while (nullptr != l2_ptr)
        {
            sum = l2_ptr->val + carry;
            carry = sum / 10;
            sum -= 10 * carry;

            curr_sum_node = new ListNode(sum);
            curr->next = curr_sum_node;

            l2_ptr = l2_ptr->next;
            curr = curr->next;
        }

        // Trailing carry
        if (0 != carry)
        {
            curr_sum_node = new ListNode(carry);
            curr->next = curr_sum_node;
        }

        ListNode* result = dummy_head.next;
        return reverse_list(result);
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
