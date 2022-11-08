#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;


class Solution {
public:
    int evaluate(const int& lhs, const int& rhs, const string& ops)
    {
        if (ops == "+")
        {
            return lhs + rhs;
        }
        else if (ops == "-")
        {
            return lhs - rhs;
        }
        else if (ops == "*")
        {
            return lhs * rhs;
        }
        else
        {
            /* rhs != 0 */
            /* / */
            return lhs / rhs;
        }
    }
    int evalRPN(vector<string>& tokens)
    {
        /* Binary operator leads to length of tokens >= 3. */
        stack<int> operands;
        int number;
        int res = 0;
        bool is_start = false;

        if (1 == tokens.size())
        {
            istringstream(tokens[0]) >> number;
            return number;
        }

        for (uint i = 0; i < tokens.size(); ++i)
        {
            if (tokens[i] != "+"
                    && tokens[i] != "-"
                    && tokens[i] != "*"
                    && tokens[i] != "/")
            {
                istringstream(tokens[i]) >> number;
                operands.push(std::move(number));
            }
            else
            {
                if (!is_start)
                {
                    int rhs = operands.top();
                    operands.pop();
                    int lhs = operands.top();
                    operands.pop();
                    res = evaluate(lhs, rhs, tokens[i]);
                    is_start = true;
                }
                else
                {
                    int lhs = operands.top();
                    operands.pop();
                    res = evaluate(lhs, res, tokens[i]);
                }

            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    /* vector<string> tokens = {"2","1","+","3","*"}; */
    /* vector<string> tokens = {"4","13","5","/","+"}; */
    vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    std::cout << "res " << sol.evalRPN(tokens) << std::endl;
    return 0;
}
