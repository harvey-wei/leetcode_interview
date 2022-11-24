#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/* ref: https://en.wikipedia.org/wiki/DBSCAN */

struct Point
{
    float x;
    float y;

    Point(float _x, float _y)
        : x(_x), y(_y)
    {}
};

void l2_norm(const Point& pt_one, const Point& pt_two, float& dist)
{
    dist = std::sqrt((pt_one.x - pt_two.x) * (pt_one.x - pt_two.x) + (pt_one.y - pt_two.y)
            * (pt_one.y - pt_two.y));

    return;
}

void neighbor_query(const std::vector<Point>& points, const int& eps, const int& min_pt_cnt,
        const int& curr_pt_idx, std::vector<int>& neighbors)
{
    /* TODO: Optimize it using kd tree R-tree or ball tree*/
    for (size_t pt_idx = 0; pt_idx < points.size(); ++pt_idx)
    {
        float dist;
        l2_norm(points[pt_idx], points[curr_pt_idx], dist);
        if (dist <= eps)
        {
            neighbors.push_back(pt_idx);
        }
    }
}

void neighbor_expand(const std::vector<Point>& points, std::vector<int>& neighbors_of_core,
        int curr_cluster_id, const float& eps, const int& min_pt_cnt, std::vector<int>& labels)
{
    /*
       The point in the neighborhood of core point is directly reachable from core point.
       The neighbors of other core points in the neighborhood of the current core point is
       reachable from the current core point through its neighboring core point.
       Hence, we can merge them into the same cluster.
    */

    for (size_t i = 0; i < neighbors_of_core.size(); ++i)
    {
        /* Change noise to border point. */
        if (labels[neighbors_of_core[i]] == 0) labels[neighbors_of_core[i]] = curr_cluster_id;

        /* Skip if it is already labeled. */
        if (labels[neighbors_of_core[i]] != -1) continue;

        labels[neighbors_of_core[i]] = curr_cluster_id;

        std::vector<int> neighbors;
        neighbor_query(points, eps, min_pt_cnt, neighbors_of_core[i], neighbors);

        if (neighbors.size() >= min_pt_cnt)
        {
            neighbors_of_core.insert(neighbors_of_core.end(), neighbors.begin(), neighbors.end());
        }

    }
}

void dbscan(const std::vector<Point>& points, const float& eps, const int& min_pt_cnt,
        std::vector<int>& labels)
{
    assert(points.size() == labels.size());

    for (auto& label: labels)
    {
        label = -1;
    }

    /*
       -1 means unlabeled.
        0 means noise.
        1, 2, 3 ... cluster ID
    */
    int cluster_id = 1;

    for (size_t pt_idx = 0; pt_idx < points.size(); ++pt_idx)
    {
        /* Skip labeled points. */
        if (labels[pt_idx] != -1) continue;

        /* Get neighbors. */
        std::vector<int> neighbors;
        neighbor_query(points, eps, min_pt_cnt, pt_idx, neighbors);

        if (neighbors.size() < min_pt_cnt)
        {
            /* Mark sparse point as noise. */
            labels[pt_idx] = 0;
            continue;
        }
        else
        {
            /* The curren point is core point
               But its neighboring point
            */
            labels[pt_idx] = cluster_id;

            /* Expand and label border points. */
            neighbor_expand(points, neighbors, cluster_id, eps, min_pt_cnt, labels);
        }

        ++cluster_id;
    }

    return;
}

int main()
{
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(0.5, 0.5);
    points.emplace_back(-0.6, 0);
    points.emplace_back(10.0, 10.0);
    points.emplace_back(10.5, 10.5);
    points.emplace_back(100, 100);

    std::vector<int> labels(points.size(), -1);

    int eps = 1.0;
    int min_pt_cnt = 2;

    dbscan(points, eps, min_pt_cnt, labels);

    for (size_t i = 0; i < points.size(); ++i)
    {
        std::cout << "point " << "(" << points[i].x << ", " << points[i].y << ")" <<
            " is in cluster " << labels[i] << std::endl;
    }

    return 0;
}
