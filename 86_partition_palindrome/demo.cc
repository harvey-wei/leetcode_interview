#include <string>
#include <vector>
using namespace std;

class Solution
{
	public:
		bool is_palindrome(const string&str, int start, int end)
		{
			while (start < end)
			{
				if (str[start++] != str[end--])
				{
					return false;
				}
			}

			return true;
		}

		void partitionHelper(const string&s, int start, std::vector<std::string>& curr_partition,
				vector<vector<string>>& results)
		{
			if (start == s.size())
			{
				results.push_back(curr_partition);
			}
			else
			{
				for (int i = start; i < s.size(); ++i)
				{
					// check [start, i]
					if (is_palindrome(s, start, i))
					{
						// choose s[start, i]
						curr_partition.push_back(s.substr(start, i - start + 1));

						// unexplore start = i + 1
						partitionHelper(s, i + 1, curr_partition, results);

						// unchoose
						curr_partition.pop_back();
					}

				}
			}

		}

		vector<vector<string>> partition(string s)
		{
			vector<string> strs;
			vector<vector<string>> results;
			partitionHelper(s, 0, strs, results);

			return results;
		}
};

class Solution_ {
public:
    bool is_palindrome(const string& str, int start, int end)
    {
        while (start < end)
        {
            if (str[start] != str[end])
            {
                return false;
            }
            else
            {
                ++start;
                --end;
            }
        }

        /* Single-char string is also a palindrome. */
        return true;
    }

    void helper(const string& s, int start, vector<string>& strs, vector<vector<string>>& result)
    {
        if (start == s.size())
        {
            result.push_back(strs);
        }
        else
        {
            for (int i = start; i < s.size(); ++i)
            {
                if (is_palindrome(s, start, i))
                {
					// if [start, i] is palindrome check chars  char start at i + 1
					// choose [start, i] as a partiion
                    strs.push_back(s.substr(start, i - start + 1));
                    helper(s, i + 1, strs, result);

					// unchoose
                    strs.pop_back();
                }
            }

        }

        return;
    }

    vector<vector<string>> partition(string s) {
        vector<string> strs;
        vector<vector<string>> results;
        helper(s, 0, strs, results);

        return results;
    }
};

int main()
{
    return 0;
}
