#include <vector>
#include <string>
#include <stack>
#include <cctype>


using namespace std;

class Solution {
public:
    int eval(const int& lhs, const int& rhs, const string& op)
    {
        if (op == "+")
        {
            return lhs + rhs;
        }
        else if (op == "-")
        {
            return lhs - rhs;
        }
        else if (op == "*")
        {
            return lhs * rhs;
        }
        else
        {
            /* / */
            return lhs / rhs;
        }
    }

    int evalRPN(vector<string>& tokens)
    {
        stack<string> token_stack;

        for (int i = 0; i < tokens.size(); ++i)
        {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
            {
                int rhs = stoi(token_stack.top());
                token_stack.pop();

                int lhs = stoi(token_stack.top());
                token_stack.pop();

                string res = std::to_string(eval(lhs, rhs, tokens[i]));
                token_stack.push(res);

            }
            else
            {
                /* tokens[i] is a number and just push to stack */
                token_stack.push(tokens[i]);
            }
        }

    return stoi(token_stack.top());
    }

};
