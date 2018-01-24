#ifndef KDTREE_H
#define KDTREE_H

#include <nanoflann.hpp>
#include <pointcloud.h>

using namespace nanoflann;

class KDTree
{
protected:
    typedef KDTreeSingleIndexDynamicAdaptor<
            L2_Simple_Adaptor<double,PointCloud<double>>,
            PointCloud<double>,3>
    KDTreeIndex;
public:
    KDTree();
    size_t size() { return cloud.size(); }
    double x(size_t i) { return cloud.pts[i].x; }
    double y(size_t i) { return cloud.pts[i].y; }
    double z(size_t i) { return cloud.pts[i].z; }

protected:
    Point<double> nearest(const Point<double> &p, size_t *nearest_index = nullptr, size_t n_neighbor = 1);
    void addPoint(const Point<double> &point);
    void addPoints(const std::vector<Point<double> > &points);
    void addRandomPoints(size_t N=100);

protected:
    PointCloud<double> cloud;
    KDTreeIndex *index = new KDTreeIndex(3, cloud, KDTreeSingleIndexAdaptorParams());
};

#endif // KDTREE_H
