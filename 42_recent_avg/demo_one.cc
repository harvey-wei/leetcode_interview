#include <iostream>
#include <queue>
#include <list>
#include <deque>
using namespace std;

class RecentCounter {
private:
    deque<int> time_deque;
    int request_cnt;

public:
    RecentCounter() {
        request_cnt = 0;
    }

    int ping(int t)
    {
        time_deque.push_back(t);
        ++request_cnt;

        int start_time = t - 3000;
        /* pop out all timestamps < start_time
           t == t no need to check the empty
        */
        while (time_deque.front() < start_time)
        {
            --request_cnt;
            time_deque.pop_front();
        }

        return request_cnt;
    }
};

class RecentCounter_list
{
private:
    list<int> time_list;
    int request_cnt;
public:
    RecentCounter_list() {
        request_cnt = 0;
    }

    int ping(int t)
    {
        time_list.push_back(t);
        ++request_cnt;

        int start_time = t - 3000;
        /* pop out all timestamps < start_time
           t == t no need to check the empty
        */
        while (time_list.front() < start_time)
        {
            --request_cnt;
            time_list.pop_front();
        }

        return request_cnt;
    }
};

/* class RecentCounter { */
/* private: */
/*     queue<int> time_queue; */
/*     int request_cnt; */
/* public: */
/*     RecentCounter() { */
/*         request_cnt = 0; */
/*     } */
/**/
/*     int ping(int t) */
/*     { */
/*         time_queue.push(t); */
/*         ++request_cnt; */
/**/
/*         int start_time = t - 3000; */
/*         // pop out all timestamps < start_time */
/*            t == t no need to check the empty */
/*         */
/*         while (time_queue.front() < start_time) */
/*         { */
/*             --request_cnt; */
/*             time_queue.pop(); */
/*         } */
/**/
/*         return request_cnt; */
/*     } */
/**/
/* }; */

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
