/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* sortList(ListNode* head)
	{
		if (nullptr != head && nullptr != head->next)
		{
			/* TODO: To consider head or head->next?*/
			ListNode* right = split(head);
			head = sortList(head);
			right = sortList(right);
			return merge(head, right);
		}
		else
		{
			/* Empty list or singleton is sorted*/
			return head;
		}
	}

private:
	ListNode* split(ListNode* head)
	{
		/* Split the list head into two halves. */
		if (nullptr == head) return nullptr;

		ListNode* slow = head;
		ListNode* fast = head->next;

		/* Check fast and fast->next to see if go ahead. */
		while (nullptr != fast && nullptr != fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		ListNode* right = slow->next;
		slow->next = nullptr;

		return right;
	}

	ListNode* merge(ListNode* left, ListNode* right)
	{
		ListNode* ptr_left = left;
		ListNode* ptr_right = right;
		ListNode dummy_node = ListNode();
		ListNode* curr = &dummy_node;

		/* Scan both left and right sorted list from smaller to larger*/
		while (nullptr != ptr_left && nullptr != ptr_right)
		{
			if (ptr_left->val < ptr_right->val)
			{
				curr->next = ptr_left;
				ptr_left = ptr_left->next;
				curr = curr->next;
			}
			else
			{
				curr->next = ptr_right;
				ptr_right = ptr_right->next;
				curr = curr->next;
			}
		}

		if (nullptr != ptr_left)
		{
			curr->next = ptr_left;
		}

		if (nullptr != ptr_right)
		{
			curr->next = ptr_right;
		}

		return dummy_node.next;
	}
};
