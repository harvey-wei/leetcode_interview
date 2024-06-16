#include <iostream>
#include <list> // doubly-linked list
#include <utility> //pair
#include <unordered_map>


using namespace std;


class LRUCache
{
private:
    int capacity;
    unordered_map<int, list<int>::iterator> map; // key to list node iterator
    // pair<key, value>
    /* list<pair<int, int>> lru; */
    list<int> lru;


public:
    LRUCache(int capacity)
    {
        /* this is a must for the same variable name. */
        this->capacity = capacity;
    }

    int get(int key)
    {
        if (map.end() == map.find(key))
        {
            return -1;
        }
        else
        {
            const auto node_it = map[key];
            int value = *node_it;

            // push <key, value > to front
            lru.erase(node_it);
            lru.push_front(value);
            map[key] = lru.begin();
            return value;
        }

    }

    void put(int key, int value)
    {
        if (map.end() != map.find(key))
        {
            /* remove the old node. */
            lru.erase(map[key]);
        }

        lru.push_front(value);
        map[key] = lru.begin();

        if (map.size() > capacity)
        {
            // Hence, we need pack key-value as pair !

        }
    }
};


class LRUCache_
{
private:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> map; // key to list node iterator
    // pair<key, value>
    list<pair<int, int>> lru;


public:
    LRUCache(int capacity)
    {
        /* this is a must for the same variable name. */
        this->capacity = capacity;
    }

    int get(int key)
    {
        const auto& it = map.find(key);

        if (map.end() == it) return -1;

        const auto& node = it->second;
        int value = node->second;

        // push to front
        // front is the most recently used while back is the least recently used.
        lru.erase(node);
        /* list.push_front(std::make_pair(k, v)); */
        lru.push_front({key, value});

        // sync to map
        map[key] = lru.begin();

        return value;
    }

    void put(int key, int value)
    {
        const auto& it = map.find(key);

        if (map.end() != map.find(key))
        {
            /* Remove the old node. */
            lru.erase(it->second);
        }

        lru.push_front({key,value});
        map[key] = lru.begin();

        if (map.size() > capacity)
        {
            const auto& back = lru.back();
            map.erase(back.first);
            lru.pop_back();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 * We need a data structure which can move a element to front or back in O(1).
 * array is not suitable.
 * doubly-linked_list OK, In C++, std::list is doubly-linked list.
 * queue
 * stack.
 * set.
 */
