#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int get_sum(const vector<long int>& nums)
    {
        int sum = 0;

        for (size_t i = 0; i < nums.size(); ++i)
        {
            sum += nums[i];
        }

        return sum;
    }

    int parse_number(const string&s, int& curr_idx)
    {
        long int num = 0;
        while (curr_idx < s.size() && std::isdigit(s[curr_idx]))
        {
            num = num * 10 + (s[curr_idx] - '0');
            ++curr_idx;
        }

        // curr_idx passes the end or points to next operator or ')'

        return num;
    }

    int parse_expr(const string& s, int& curr_idx)
    {
        vector<long int> nums;

        char opr = '+';

        /* opr == ')' is the base case of the parse_expr*/
        for (; curr_idx < s.size() && opr != ')'; ++curr_idx)
        {
            if (s[curr_idx] == ' ') continue;

            long int curr_num = 0;
            if (s[curr_idx] == '(')
            {
                /* (left_expr ops right_expr) */
                ++curr_idx;
                curr_num = parse_expr(s, curr_idx);
            }
            else
            {
                /* base case expr is a number or ')' */
                curr_num = parse_number(s, curr_idx);
            }

            // push to nums
            if (opr == '+')
            {
                nums.push_back(curr_num);
            }
            else if (opr == '-')
            {
                nums.push_back(-curr_num);
            }
            else if (opr == '*')
            {
                /* * associate with last num */
                nums.back() *= curr_num;
            }
            else if (opr == '/')
            {
                /* opr == '/' and associates with last num */
                nums.back() /= curr_num; // integer division
            }
            else
            {
                /* ')' Do nothing. */
            }

            // get the next operator or ')'
            if (curr_idx < s.size())
            {
                opr = s[curr_idx];
            }
        }

        return get_sum(nums);
    }

    int calculate(string s) {
        int curr_idx = 0;
        return parse_expr(s, curr_idx);
    }
};

int main()
{
    Solution sol;
    std::cout << "1+1 = " << sol.calculate("1 + 1") << std::endl;
    std::cout << "6 - 4 / 2 = " << sol.calculate("6 - 4/2") << std::endl;
    std::cout << "2*(5+5*2)/3+(6/2+8) = " << sol.calculate("2*(5+5*2)/3+(6/2+8)") << std::endl;
    return 0;
}
