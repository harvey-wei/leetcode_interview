#include <iostream>
#include <vector>
#include <stack>

int island_cnt(std::vector<std::vector<int>>& grid)
{
    int island_cnt = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<bool>>
        visisted(rows, std::vector<bool>(cols, false));

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            /* skip if already visisted or it is zero. */
            if (visisted[r][c] || grid[r][c] == 0) continue;

            std::stack<int> stack_idx;
            int idx = r * cols +  c;
            stack_idx.push(idx);
            visisted[r][c] = true;

            int curr_idx;
            int curr_row;
            int curr_col;

            /* index offset */
            std::vector<std::vector<int>> neighbors = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

            while (!stack_idx.empty())
            {
                curr_idx = stack_idx.top();
                stack_idx.pop();

                curr_row = curr_idx / cols;
                curr_col = curr_idx % cols;

                /* Check its neighbor */
                for (const auto& neighbor : neighbors)
                {
                    int n_r = curr_row + neighbor[0];
                    int n_c = curr_col + neighbor[1];

                    if ((n_r >= 0 && n_r < rows) &&
                            (n_c >= 0 && n_c < cols) &&
                            grid[n_r][n_c] == 1 &&
                            (!visisted[n_r][n_c]))
                    {
                        visisted[n_r][n_c] = true;

                        /* Push linear index */
                        stack_idx.push(n_r * cols + n_c);
                    }
                }
            }

            /* One connected component is found! */
            ++island_cnt;
        }
    }

    return island_cnt;

}

int
main(int argc, char** argv)
{
    std::vector<std::vector<int>> grid =
            {{1, 1, 1, 1, 0},
             {1, 1, 0, 1, 0},
             {1, 1, 0, 0, 0},
             {0, 0, 0, 0, 0}};

    std::cout << "island_cnt: " << island_cnt(grid) << std::endl;

    grid = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
    std::cout << "island_cnt: " << island_cnt(grid) << std::endl;

    return 0;
}
