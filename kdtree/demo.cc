#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

/**
 * Class for representing a point. coordinate_type must be a numeric type.
 */
template<typename coordinate_type, size_t dimensions>
class Point {
public:
    /**
     * fixed-size array is also a container like std::vector but fixed-size.
     * coordinate_type can be float, double, int or any other type of your choice.
     * dimensions means the number of elements in the fixed-size array.
     */
    Point(std::array<coordinate_type, dimensions> c) : coords_(c) {}

    /**
     * copy list-initialization constructor
     *
     * initializer-list is a list of comma-separated elements enclosed in braces.
     * auto il = {10, 20, 30} // il is of type initializer_list
     * Initializer-list constructors take precedence over other constructors when the
     * initializer-list constructor syntax is used:
     *
     * struct myclass {
     * myclass (int,int);
     * myclass (initializer_list<int>);
     * };
     *
     * myclass foo {10,20};  // calls initializer_list ctor
     * myclass bar (10,20);  // calls first constructor
     * https://en.cppreference.com/w/cpp/utility/initializer_list
     */
    Point(std::initializer_list<coordinate_type> list) {
        /* Avoid going beyond the total number of dimenstions. */
        size_t n = std::min(dimensions, list.size());
        /* Efficient copy. */
        std::copy_n(list.begin(), n, coords_.begin());
    }

    /**
     * Returns the coordinate in the given dimension.
     *
     * @param index dimension index (zero based)
     * @return coordinate in the given dimension
     */
    coordinate_type get(size_t index) const
    {
        return coords_[index];
    }

    /**
     * ref: https://www.geeksforgeeks.org/overloading-subscript-or-array-index-operator-in-c/
     * note the usage of const member function
     */
    coordinate_type operator[](size_t index) const
    {
        return coords_[index];
    }

    /**
     * Returns the distance squared from this point to another
     * point.
     *
     * @param pt another point
     * @return distance squared from this point to the other point
     */
    double distance(const Point& pt) const {
        double dist = 0;
        for (size_t i = 0; i < dimensions; ++i) {
            double d = get(i) - pt.get(i);
            dist += d * d;
        }
        return dist;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point<coordinate_type, dimensions>& pt)
    {
        out << '(';
        for (size_t i = 0; i < dimensions; ++i) {
            if (i > 0)
                out << ", ";
            /* out << pt.get(i); */
            out << pt[i];
        }
        out << ')';
        return out;
    }

private:
    std::array<coordinate_type, dimensions> coords_;
};

/* template<typename coordinate_type, size_t dimensions> */
/* std::ostream& operator<<(std::ostream& out, const Point<coordinate_type, dimensions>& pt) */
/* { */
/*     out << '('; */
/*     for (size_t i = 0; i < dimensions; ++i) { */
/*         if (i > 0) */
/*             out << ", "; */
/*         out << pt.get(i); */
/*     } */
/*     out << ')'; */
/*     return out; */
/* } */

/**
 * C++ k-d tree implementation, based on the C version at rosettacode.org.
 */
template<typename coordinate_type, size_t dimensions>
class kdtree {
public:
    typedef Point<coordinate_type, dimensions> point_type;
private:
    struct node {
        node(const point_type& pt) : point_(pt), left_(nullptr), right_(nullptr) {}
        coordinate_type get(size_t index) const {
            return point_.get(index);
        }
        double distance(const point_type& pt) const {
            return point_.distance(pt);
        }
        point_type point_;
        node* left_;
        node* right_;
    };
    node* root_ = nullptr;
    node* best_ = nullptr;
    double best_dist_ = 0;
    size_t visited_ = 0;
    std::vector<node> nodes_;

    struct node_cmp {
        node_cmp(size_t index) : index_(index) {}
        bool operator()(const node& n1, const node& n2) const {
            return n1.point_.get(index_) < n2.point_.get(index_);
        }
        size_t index_;
    };

    node* make_tree(size_t begin, size_t end, size_t index) {
        if (end <= begin)
            return nullptr;
        size_t n = begin + (end - begin)/2;
        auto i = nodes_.begin();
		/* iterator = i + idx */
        std::nth_element(i + begin, i + n, i + end, node_cmp(index));

		// Next dimension
        index = (index + 1) % dimensions;
        nodes_[n].left_ = make_tree(begin, n, index);
        nodes_[n].right_ = make_tree(n + 1, end, index);

        return &nodes_[n];
    }

    void nearest(node* root, const point_type& point, size_t index) {
        if (root == nullptr)
            return;

        ++visited_;
		/* d is the L2-distance */
        double d = root->distance(point);
        if (best_ == nullptr || d < best_dist_) {
            best_dist_ = d;
            best_ = root;
        }

        if (best_dist_ == 0)
            return;

		/* We find the correct position for query point by current dimension--index only*/
		/* dx > 0, go the left subtree  and update best_dist_. */
		/* dx * dx is the square of distance of query point to the splitting plane root->get(index)*/
        double dx = root->get(index) - point.get(index);
        index = (index + 1) % dimensions;

        nearest(dx > 0 ? root->left_ : root->right_, point, index);

        if (dx * dx >= best_dist_)
		{
			/* The distance to the splitting plane root->get(index) is dx * dx  */
			/* A ball centered at query point with radius as best_dist_ does not cross the splitting
			plane*/
			/* Hence no need to check the other side */
            return;
		}

		/* We also need the check the other side of the traversed side. */
        nearest(dx > 0 ? root->right_ : root->left_, point, index);
    }
public:
    kdtree(const kdtree&) = delete;
    kdtree& operator=(const kdtree&) = delete;
    /**
     * Constructor taking a pair of iterators. Adds each
     * point in the range [begin, end) to the tree.
     *
     * @param begin start of range
     * @param end end of range
     */
    template<typename iterator>
    kdtree(iterator begin, iterator end) : nodes_(begin, end) {
        root_ = make_tree(0, nodes_.size(), 0);
    }

    /**
     * Constructor taking a function object that generates
     * points. The function object will be called n times
     * to populate the tree.
     *
     * @param f function that returns a point
     * @param n number of points to add
     */
    template<typename func>
    kdtree(func&& f, size_t n) {
        nodes_.reserve(n);
        for (size_t i = 0; i < n; ++i)
            nodes_.push_back(f());
        root_ = make_tree(0, nodes_.size(), 0);
    }

    /**
     * Returns true if the tree is empty, false otherwise.
     */
    bool empty() const { return nodes_.empty(); }

    /**
     * Returns the number of nodes visited by the last call
     * to nearest().
     */
    size_t visited() const { return visited_; }

    /**
     * Returns the distance between the input point and return value
     * from the last call to nearest().
     */
    double distance() const { return std::sqrt(best_dist_); }

    /**
     * Finds the nearest point in the tree to the given point.
     * It is not valid to call this function if the tree is empty.
     *
     * @param pt a point
     * @return the nearest point in the tree to the given point
     */
    const point_type& nearest(const point_type& pt) {
        if (root_ == nullptr)
            throw std::logic_error("tree is empty");
        best_ = nullptr;
        visited_ = 0;
        best_dist_ = 0;
        nearest(root_, pt, 0);
        return best_->point_;
    }
};

void test_wikipedia() {
    typedef Point<int, 2> point2d;
    typedef kdtree<int, 2> tree2d;

    point2d points[] = { { 2, 3 }, { 5, 4 }, { 9, 6 }, { 4, 7 }, { 8, 1 }, { 7, 2 } };

    tree2d tree(std::begin(points), std::end(points));
    point2d n = tree.nearest({ 9, 2 });

    std::cout << "Wikipedia example data:\n";
    std::cout << "nearest point: " << n << '\n';
    std::cout << "distance: " << tree.distance() << '\n';
    std::cout << "nodes visited: " << tree.visited() << '\n';
}

typedef Point<double, 3> point3d;
typedef kdtree<double, 3> tree3d;

struct random_point_generator {
    random_point_generator(double min, double max)
        : engine_(std::random_device()()), distribution_(min, max) {}

    point3d operator()() {
        double x = distribution_(engine_);
        double y = distribution_(engine_);
        double z = distribution_(engine_);
        return point3d({x, y, z});
    }

    std::mt19937 engine_;
    std::uniform_real_distribution<double> distribution_;
};

void test_random(size_t count) {
    random_point_generator rpg(0, 1);
    tree3d tree(rpg, count);
    point3d pt(rpg());
    point3d n = tree.nearest(pt);

    std::cout << "Random data (" << count << " points):\n";
    std::cout << "point: " << pt << '\n';
    std::cout << "nearest point: " << n << '\n';
    std::cout << "distance: " << tree.distance() << '\n';
    std::cout << "nodes visited: " << tree.visited() << '\n';
}

int main() {
    try {
        test_wikipedia();
        std::cout << '\n';
        test_random(1000);
        std::cout << '\n';
        test_random(1000000);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}


/**
 * range search
 * ref: https://www.cs.princeton.edu/courses/archive/spr13/cos226/lectures/99GeometricSearch.pdf
 *
 * knn
 * travese the tree to section where the query point belongs to
 * push the lead to the max_heap
 * ref: https://www.colorado.edu/amath/sites/default/files/attached-files/k-d_trees_and_knn_searches.pdf
 * ref: https://www.colorado.edu/amath/sites/default/files/attached-files/k-d_trees_and_knn_searches.pdf1
 * ref: https://github.com/gvd/kdtree/blob/master/kdtree.h
 * ref: https://leetcode.com/problems/k-closest-points-to-origin/
 */
