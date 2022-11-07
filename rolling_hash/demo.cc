#include <iostream>
#include <list>
using namespace std;

class RollingHash
{
    /*
       int(char) return the ASCII value of character char.
       There are total 256 extended ASCII values.

       // Note the collision exists !
       // if two string has different hash value, the must be different!
       // However, two different strings may also have the same hash value.

       // Key Idea:
       // Rolling hash to pre-compute the hashes of  consecutive substrings efficiently.
       // 
    */
    private:
        list<char> str;
        int hash_val = 0;
        const int base = 256;  // alphabet size

        // A prime: should be >= total possibilities of str.
        // pattern in a
        // https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
        const int p = 1e9 + 7;;
        int y = 1;

    public:
        void append(char ch)
        {
            str.push_back(ch);

            // update the hash_val
            hash_val = (base * (hash_val % p) + int(ch)) % p;

            if (str.size() > 1u)
            {
                y = (y * base) % p;
            }
        }

        void pop_front()
        {
            char top = str.front();
            str.pop_front();

            // update the hash_val
            hash_val = hash_val - int(top) * y;
        }

        int get_hash()
        {
            return hash_val;
        }
};

int main()
{
    return 0;
}
