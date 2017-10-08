#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <vector>
#include <random>
#include <cstdio>

template <typename T>
struct Point
{
    T x, y, z;
};

template <typename T>
struct PointCloud
{

    std::vector<Point<T>> pts;

    inline size_t size() { return pts.size(); }

    inline size_t kdtree_get_point_count() { return pts.size(); }

    inline T kdtree_get_pt(const size_t idx, size_t dim) const
    {
        switch (dim) {
        case 0:
            return pts[idx].x;
        case 1:
            return pts[idx].y;
        default:
            return pts[idx].z;
        }
    }

    template <class BBOX>
    inline T kdtree_get_bbox(BBOX) const { return false; }
};

template <typename T>
T randomPoint(const T a, const T b, int distribution)
{
    static std::random_device rd;
    switch (distribution) {
    case 0:
        if(std::is_same<T,int>::value)
        {
            static std::uniform_int_distribution<> dist(a,b);
            T ret = dist(rd);
            return ret;
        }
        else
        {
            static std::uniform_real_distribution<T> dist(a,b);
            T ret = dist(rd);
            return ret;
        }
    default:
            static std::normal_distribution<T> dist(a,b);
            T ret = dist(rd);
            return ret;
    }
}

template <typename T>
void generateRandomPointCloud(PointCloud<T> &cloud, const size_t N,
                              const T a = 0, const T b = 10,
                              int distribution = 0)
{
    cloud.pts.resize(N);
    for(size_t i=0; i<N; i++)
    {
        cloud.pts[i].x = randomPoint(a,b,distribution);
        cloud.pts[i].y = randomPoint(a,b,distribution);
        cloud.pts[i].z = 0.0;
//        cloud.pts[i].z = randomPoint(a,b,distribution);
    }
}

#endif // POINTCLOUD_H
