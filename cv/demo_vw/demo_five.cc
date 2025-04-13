#include <iostream>
#include <vector>
#include <unordered_set>

struct Point
{
    int x;
    int y;
};


// rows 100, cols = 100
std::vector<Point> points;

std::vector<Point> search(std::vector<Point> const & in)
{
    std::vector<Point> result;

    for (const auto pt: in)
    {
        for (int i = 0; i < points.size(); ++i)
        {
            // case 1: same Point
            // case 2: one of x and y diff is one
            if (pt.x == points[i].x && pt.y == points[i].y)
            {
                result.push_back(pt);
                break;
            }
            else if ((pt.x == points[i].x && 1 == std::abs(pt.y - points[i].y)) ||
                    (pt.y == points[i].y && 1 == std::abs(pt.x - points[i].x)))
            {
                result.push_back(pt);
                break;
            }
            else
            {
                // do nothing.
            }
        }
    }
    return result;
}


class NN
{
    public:
        NN(std::vector<Point> _points)
        {
            for (const auto& pt : _points)
            {
                points.push_back(pt);
            }

            for (const auto pt: points)
            {
                pt_exist.insert(pt.x * 100 + pt.y);
            }
        }

        std::vector<Point> search_v2(std::vector<Point> const & in)
        {
            std::vector<Point> result;

            for (const auto& pt : in)
            {
                for (const auto& dir : dirs)
                {
                    int n_x = pt.x + dir[0];
                    int n_y = pt.y + dir[1];

                    if (n_x >= 0 && n_x <=99 && n_y >= 0 && n_y <= 99 && (pt_exist.end() != pt_exist.find(n_x * 100 + n_y)))
                    {
                        result.push_back(pt);
                        break;
                    }
                }
            }

            return result;
        }

    private:
        std::vector<Point> points;
        std::unordered_set<int> pt_exist;
        std::vector<std::vector<int>> dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0}};
};

int main()
{

}
