#include <iostream>
#include <vector>
#include <unordered_set>

struct Point
{
    float x;
    float y;

    Point(float _x = 0.0f, float _y = 0.0f)
        : x(_x), y(_y)
    {}
};

void mean_points(const std::vector<Point>& points, const std::vector<int>& pt_indices,
        Point& mean_point)
{
    mean_point.x = 0.0f;
    mean_point.y = 0.0f;

    for (const auto& pt_idx: pt_indices)
    {
        mean_point.x += points[pt_idx].x;
        mean_point.y += points[pt_idx].y;
    }

    if (pt_indices.size() > 0u)
    {
        mean_point.x /= (float) (pt_indices.size());
        mean_point.y /= (float) (pt_indices.size());
    }

    return;
}

void k_means(const std::vector<Point>& points, const int& k, const int& max_iter,
        std::vector<std::vector<int>>& cluster2points)
{
    assert(((size_t) (k)) <= points.size());

    std::vector<int> labels; /* */
    std::vector<Point> centroids(k);
    std::unordered_set<int> centroid_idx_set;

    for (size_t i = 0; i < k; ++i)
    {
        int random_idx = rand() % k; // [0, k);

        while (centroid_idx_set.end() != centroid_idx_set.find(random_idx))
        {
            random_idx = rand() % k;
        }

        centroid_idx_set.insert(random_idx);
        centroids[i].x = points[random_idx].x;
        centroids[i].y = points[random_idx].y;
    }

    for (int iter = 0; iter < max_iter; ++iter)
    {
        for (size_t pt_idx = 0; pt_idx < points.size(); ++pt_idx)
        {
            int min_ctr_idx = -1;
            float min_dist = std::numeric_limits<float>::max();

            for (size_t ctr_idx = 0; ctr_idx < k; ++ctr_idx)
            {
                // square of distance from to point to centroid.
                float pt2ctr_dist = (points[pt_idx].x - centroids[ctr_idx].x) * (points[pt_idx].x - centroids[ctr_idx].x)
                        + (points[pt_idx].y - centroids[ctr_idx].y) * (points[pt_idx].y - centroids[ctr_idx].y);

                if (pt2ctr_dist < min_dist)
                {
                    min_ctr_idx = (int) ctr_idx;
                    min_dist = pt2ctr_dist;
                }
            }

            // update the cluster index for the current point.
            labels[pt_idx] = min_ctr_idx;
        }

        // update the centroids by averaging the points in that cluster
        for (size_t cluster_idx = 0; cluster_idx < cluster2points.size(); ++cluster_idx)
        {
            mean_points(points, cluster2points[cluster_idx], centroids[cluster_idx]);
        }
    }

    return;
}


int main()
{
    return 0;
}

