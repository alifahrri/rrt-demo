#ifndef RRT_H
#define RRT_H

#include "kdtree.h"
#include <vector>
#include <random>

using namespace std;

class RRT : public KDTree
{
public:
    RRT();
    void grow(size_t N);
    const vector<Point<double>>& getPoints() { return cloud.pts; }
    const vector<int>& getParentMap() { return parent_map; }
    const vector<vector<int>>& getChildMap() { return child_map; }
private:
    void addEdge(const Point<double> &new_point, size_t nearest_idx);
    double L2Distance(const Point<double>& p1, const Point<double>& p2);
    void insertPoint(const Point<double>& p, int parent);
    void insertPoint(const Point<double> &p, int parent, int child);
private:
    vector<int> parent_map;
    vector<vector<int>> child_map;
    random_device rd_x, rd_y;
    uniform_real_distribution<double> rd_gen_x;
    uniform_real_distribution<double> rd_gen_y;
};

#endif // RRT_H
