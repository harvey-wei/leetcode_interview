#include <vector>
#include <mutex>

// Multithreading
struct Counter
{
    Counter()
    {
        ref_cnt = 0;
    }

    int ref_cnt;
};


/**
 * constructor(T*)
 * ~SharedPointer(){}
 * copy constructor
 * T& operator=()
 */
template<typename T>
class SharedPointer
{
    public:
        SharedPointer<T>(T* _ptr)
        {
            ptr = _ptr;

            ref_counter = new Counter;
            ref_counter->ref_cnt = 1;
        }

        /* Copy constructor */
        SharedPointer<T>(const SharedPointer<T>& rhs)
        {
            ptr = rhs.ptr;
            ref_counter = rhs.ref_counter;

            ref_counter->ref_cnt += 1;
        }

        SharedPointer<T>& operator=(const SharedPointer<T>& rhs)
        {
            if (this == &rhs) return *this;

            ptr = rhs.ptr;
            ref_counter = rhs.ref_counter;

            ref_counter->ref_cnt += 1;

            return *this;
        }

        ~SharedPointer()
        {
            ref_counter->ref_cnt -= 1;

            if (0 == ref_counter->ref_cnt)
            {
                if (nullptr != ptr)
                {
                    delete ptr;
                }

                if (nullptr != ref_counter)
                {
                    delete ref_counter;
                }
            }
        };

    private:
        T* ptr;
        Counter* ref_counter;

        static std::mutex mtx;
};


int main()
{
    SharedPointer<int> int_sp(new int(10));
}
