#include "kdtree.h"
#include <iostream>

#define min(A, B) ((A<B)?A:B)

KDTree::KDTree()
{

}

Point<double> KDTree::nearest(const Point<double> &p, size_t *nearest_index, size_t n_neighbor)
{
    nanoflann::KNNResultSet<double> result_set(1);
    size_t indices;
    double distance;
    double query_pts[3] = {p.x,p.y,p.z};
    result_set.init(&indices,&distance);
    index->findNeighbors(result_set,query_pts,nanoflann::SearchParams(10));

    if(indices)
    {
        *nearest_index = indices;
    }
    return cloud.pts[indices];
}

void KDTree::addPoint(const Point<double> &point)
{
    cloud.pts.push_back(point);
    index->addPoints(cloud.size()-1,cloud.size()-1);
}

void KDTree::addPoints(const std::vector<Point<double> > &points)
{
    auto start = cloud.size()-1;
    auto end = start+points.size();
    cloud.pts.insert(cloud.pts.end(),points.begin(),points.end());
    index->addPoints(start,end);
}

void KDTree::addRandomPoints(size_t N)
{
    if(N>0)
    {
        PointCloud<double> new_cloud;
        auto start = cloud.size()-1;
        auto end = start+N;
        generateRandomPointCloud<double>(new_cloud,N,-300,300);
        cloud.pts.insert(cloud.pts.end(),new_cloud.pts.begin(),new_cloud.pts.end());
        index->addPoints(start,end);
    }
}
