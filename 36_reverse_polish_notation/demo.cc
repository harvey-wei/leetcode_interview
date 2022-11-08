#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;


class Solution {
public:
    long long int evaluate(const long long int& lhs, const long long int& rhs, const string& ops)
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
    long long int evalRPN(vector<string>& tokens)
    {
        /* Binary operator leads to length of tokens >= 3. */
        stack<long long int> operands;
        bool is_start = false;

        for (uint i = 0; i < tokens.size(); ++i)
        {
            if (tokens[i] != "+"
                    && tokens[i] != "-"
                    && tokens[i] != "*"
                    && tokens[i] != "/")
            {
                operands.push(std::move(stoll(tokens[i])));
            }
            else
            {
                long long int num_one = operands.top();
                operands.pop();
                long long int num_two = operands.top();
                operands.pop();

                long long int res = evaluate(num_two, num_one, tokens[i]);
                operands.push(std::move(res));
            }
        }

        return operands.top();
    }
};

int main()
{
    Solution sol;
    /* vector<string> tokens = {"2","1","+","3","*"}; */
    /* vector<string> tokens = {"4","13","5","/","+"}; */
    /* vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"}; */
    vector<string> tokens= {"-128","-128","*","-128","*","-128","*","8","*","-1","*"};
    std::cout << "res " << sol.evalRPN(tokens) << std::endl;
    return 0;
}
