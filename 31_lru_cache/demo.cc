#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;


class DoublyLinkedNode
{
public:
    int key;
    int val;

    DoublyLinkedNode* prev;
    DoublyLinkedNode* next;
    DoublyLinkedNode(int _key = 0, int _val = 0, DoublyLinkedNode* _prev = nullptr,
            DoublyLinkedNode* _next = nullptr)
        : key(_key), val(_val), prev(_prev), next(_next) {}
};


class DoublyLinkedList
{
private:
    DoublyLinkedNode* head = nullptr;
    DoublyLinkedNode* tail = nullptr;

public:
    DoublyLinkedList()
    {
    }

    DoublyLinkedNode* append(int key, int val)
    {
        DoublyLinkedNode* node = new DoublyLinkedNode(key, val);

        if (nullptr == head)
        {
            /* if list is empty */
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            node->next = nullptr;
            tail = node;
        }

        return tail;
    }

    void move_to_tail(DoublyLinkedNode* node)
    {
        /* assume list is not empty and node is in the list */

        if (tail == node)
        {
            /* if node == tail, do not move! */
            return;
        }
        else
        {
            /* Besure make head = dummy.next before return! */
            DoublyLinkedNode dummy = DoublyLinkedNode(0, 0, nullptr, head);
            head->prev = &dummy;
            node->prev->next = node->next;
            node->next->prev = node->prev;

            /* Doubly Linked! */
            node->prev = tail;
            tail->next = node;
            node->next = nullptr;
            tail = node;

            head = dummy.next;
            head->prev = nullptr;
        }

    }

    int pop_head()
    {
        if (nullptr == head)
        {
            /* Empty */
            return -1;
        }
        else
        {
            if (head == tail)
            {
                int k = head->key;
                /* one node */
                delete head;
                tail = nullptr;
                head = nullptr;

                return k;
            }
            else
            {
                /* >= 2 nodes */
                DoublyLinkedNode* temp = head;
                int k = temp->key;
                head = head->next;
                delete temp;
                return k;
            }
        }
    }

    void show_list()
    {
        DoublyLinkedNode* curr = head;

        while (nullptr != curr)
        {
            std::cout << "(" << curr->key << ", " << curr->val << ")" << " ";

            curr = curr->next;
        }
        std::cout << std::endl;
        std::cout << "head: " << "(" << head->key << ", " << head->val << ")" << std::endl;
        std::cout << "tail: " << "(" << tail->key << ", " << tail->val << ")" << std::endl;
    }

};

class LRUCache_ {
private:
    unordered_map<int, DoublyLinkedNode*> key2node;
    /* DoublyLinkedList linked_list; */
    int cap;
public:
    DoublyLinkedList linked_list;
    LRUCache_(int capacity)
    {
        cap = capacity;
    }

    int get(int key)
    {
        std::cout <<  "get(" << key << ")" << std::endl;
        if (key2node.end() == key2node.find(key))
        {
            /* not exists */
            return -1;
        }
        else
        {
            /* move node to tail */
            linked_list.move_to_tail(key2node[key]);

            return key2node[key]->val;
        }
    }

    void put(int key, int value)
    {
        if (key2node.end() != key2node.find(key))
        {
            /* exists. update value and move to tail */
            key2node[key]->val = value;
            linked_list.move_to_tail(key2node[key]);
        }
        else
        {
            if (key2node.size() == cap)
            {
                std::cout << "pop_head" << std::endl;
                int removed_key = linked_list.pop_head();
                std::cout << "removed key " << removed_key << std::endl;
                key2node.erase(removed_key);
            }
            DoublyLinkedNode* node = linked_list.append(key, value);
            key2node.insert({key, node});
        }

        std::cout << "The size after putting is " << key2node.size() << std::endl;
    }
};

void test_list()
{
    DoublyLinkedList linked_list = DoublyLinkedList();
    DoublyLinkedNode* node = linked_list.append(1, 1);
    linked_list.show_list();
    linked_list.append(2, 2);
    linked_list.show_list();
    linked_list.move_to_tail(node);
    linked_list.show_list();

    linked_list.pop_head();
    linked_list.show_list();
    linked_list.append(4, 4);
    linked_list.show_list();
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main()
{
    /* LRUCache* obj = new LRUCache(2); */
    /* obj->put(1, 1); */
    /* obj->linked_list.show_list(); */
    /* obj->put(2, 2); */
    /* obj->linked_list.show_list(); */
    /**/
    /* cout << "The value of 1: " << obj->get(1) << endl; */
    /**/
    /* obj->put(3, 3); */
    /* cout << "The value of 2: " << obj->get(2) << endl; */
    /**/
    /* obj->linked_list.show_list(); */
    /* obj->put(4, 4); */
    /**/
    /* obj->linked_list.show_list(); */
    /* cout << "The value of 1: " << obj->get(1) << endl; */
    /* cout << "The value of 3: " << obj->get(3) << endl; */
    /* cout << "The value of 4: " << obj->get(4) << endl; */

    test_list();

    return 0;
}
