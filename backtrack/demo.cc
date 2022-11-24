#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_2d_vec(const std::vector<std::vector<int>>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
        {
            std::cout << " " << vec[i][j];
        }

        std::cout << std::endl;
    }
}

/*
   "7" => 7;
   "(2+2)" => 4
   "(1+(2*4))" => 9
   "((1+3)+((1+2)*5))" => 19

    single-digit integer
    operators: + or *
    no space around integer or operator.

    expr = (expr+expr) recursion
    base case: expr=single-digit integer
    return result of expr
*/
int evaluate_helper(const std::string& expr, int& curr_idx)
{
    if (curr_idx == expr.size()) return 0;

    char ch = expr[curr_idx];
    if (ch == '(')
    {
        ++curr_idx; // move past ( char
        int left = evaluate_helper(expr, curr_idx);
        char opr = expr[curr_idx];
        ++curr_idx; // move to righ expr
        int right = evaluate_helper(expr, curr_idx);
        ++curr_idx; // move past ) char

        if ('+' == opr)
        {
            return left + right;
        }
        else
        {
            /* * */
            return left * right;
        }

        return left + right;
    }
    else
    {
        /* Digit */
        ++curr_idx; // points to operator
        return ch - '0';

    }
}

int evaluate(std::string expr)
{
    int curr_idx = 0;
    return evaluate_helper(expr, curr_idx);
}

void print_all_binary(int digit_cnt, std::string& curr_binary)
{
    if (digit_cnt == 0)
    {
        /* base case: all digits are chosen as 0 or 1*/
        std::cout << curr_binary << std::endl;
    }
    else
    {
        /* decision for the current digit:
           choice 1: select 1
           choice 2: select 0
        */
        for (int i = 0; i < 2; ++i)
        {
            char digit = '0' + i;
            curr_binary.push_back(digit);
            print_all_binary(digit_cnt - 1, curr_binary);
            curr_binary.pop_back();
        }
    }

}

void dice_sum_helper(int roll_cnt, int target_sum, std::vector<int>& curr_die_val,
        std::vector<std::vector<int>>& result)
{
    /* Both roll_cnt and target_sum are remaining values. */
    if (0 == target_sum && roll_cnt == 0)
    {
        result.push_back(curr_die_val); // call copy constructor.
    }

    if (roll_cnt > 0 && target_sum > 0)
    {
        for (int i = 1; i < 7; ++i)
        {
            /* roll_cnt and target_sum are passed by value such that you don't need to backgtrack!*/
            curr_die_val.push_back(i);
            dice_sum_helper(roll_cnt - 1, target_sum - i, curr_die_val, result);
            curr_die_val.pop_back();
        }
    }
}

/**
  * \brief  Dice Roll Sum
  * \param[in] roll_cnt the number of dices to roll.
  * \param[in] target_sum the desired sum of all die values.
  * \param[out] all combinations of die values that adds up to exactly that sum.
  */
void dice_sum(int roll_cnt, int target_sum)
{
    std::vector<std::vector<int>> results;
    std::vector<int> curr_die_val;
    dice_sum_helper(roll_cnt, target_sum, curr_die_val, results);
    print_2d_vec(results);
}

int main()
{
    /* std::cout << "7" << " = " << evaluate("7") << std::endl; */
    /* std::cout << "(2+2)" << " = "<< evaluate("2+2") << std::endl; */
    /* std::cout << "(1+(2*4))" << " = " << evaluate("(1+(2*4))") << std::endl; */
    /* std::cout << "((1+3)+((1+2)*5))" << " = " << evaluate("((1+3)+((1+2)*5))") << std::endl; */

    /* int digit_cnt = 3; */
    /* std::string curr_binary=""; */
    /* print_all_binary(3, curr_binary); */

    dice_sum(3, 7);

    return 0;
}
