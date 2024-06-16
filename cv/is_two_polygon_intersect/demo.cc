#include <iostream>
#include <vector>

struct Point
{
	float x;
	float y;

	Point(float _x, float _y) : x(_x), y(_y) {}
};


void sort_convex_polygon_points(std::vector<Point>)
{
	/* angle = atan2(pt.y, pt.x);*/

}

/* https://stackoverflow.com/questions/10962379/how-to-check-intersection-between-2-rotated-rectangles */
/* https://github.com/lilanxiao/Rotated_IoU */
bool is_polygons_intersect(std::vector<Point> poly0, std::vector<Point> poly1)
{
	/* */

}

int main(int argc, char** argv)
{

}
