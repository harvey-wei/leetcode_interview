#include <vector>

struct Point
{
    float x, y;
};

class Rectangle
{
    public:
        /* Rectangle(float _x1, float _y1, float _x2, float _y2, */
        /*         float _x3, float _y3, float _x4, float _y4) */
        /*     : x1(_x1), y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3), x4(_x4), y4(_y4) */
        /* { */
        /* } */

        Rectangle(std::vector<Point> _vertices)
        {
            vertices = _vertices;
        }

        float calc_area()
        {
            /**
             * 4 choose 2
             * 1-2, 1-3, 1-4, 2-3, 2-4, 3-4,
             */
            float eps = 1e-6;

            std::vector<float> lens;
            float side_len;

            for (int i = 0; i < 4; ++i)
            {
                for (int j = i + 1; j < 4; ++j)
                {
                    side_len = sqrt((vertices[i].x - vertices[j].x) * (vertices[i].x - vertices[j].x) +
                            (vertices[i].y - vertices[j].y) * (vertices[i].y - vertices[j].y));

                    if (lens.size() == 0)
                    {
                        lens.
                    }
                }

            }

            /* float side_len = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); */
            /* lens.push_back(side_len); */
            /**/
            /* side_len = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)); */
            /**/
            /* if (abs(side_len - lens[lens.size() - 1]) > eps) */
            /* { */
            /*     lens.push_back(side_len); */
            /* } */
        }


    private:
        std::vector<Point> vertices;
};

int main()
{
    return 0;
}
