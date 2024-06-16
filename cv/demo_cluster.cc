#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;


void cluster(const vector<vector<bool>>& mat)
{
  int rows = mat.size();
  int cols = mat[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  unordered_map<int, vector<int>> cluster2pixel;

  int cluster_id = 0;
  stack<int> stack;

  for (size_t r = 0; r < rows; ++r)
  {
    for (size_t c = 0; c < cols; ++c)
    {
      /* Skip if the current pixel is already visisted or balck. */
      if (true == visited[r][c] || false == mat[r][c]) continue;

      visited[r][c] = true;
      stack.push(std::move(r * rows + c));
      cluster2pixel[cluster_id].push_back(r * rows + c);

      vector<vector<int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
      while (!stack.empty())
      {
        int top_idx = stack.top();
        stack.pop();
        int top_row = top_idx / rows;
        int top_col = top_idx % rows;

        for (const auto& dir: dirs)
        {
          int n_r = top_row + dir[0];
          int n_c = top_col + dir[1];

          if ( n_r >= 0 && n_r < rows && n_c >= 0 && n_c < cols &&
              false == visited[r][c] && true == mat[r][c])
          {
            visited[r][c] = true;
            stack.push(std::move(n_r * rows + n_c));
            cluster2pixel[cluster_id].push_back(n_r * rows + n_c);
          }
        }
      }

      ++cluster_id;
    }
  }
}


int main()
{
  cout << "Hello, World!" << endl;
  return 0;
}

