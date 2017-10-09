#include "rrt.h"

#define MIN -300
#define MAX 300

#define STEP 0.01

RRT::RRT() :
    rd_gen_x(uniform_real_distribution<double>(MIN,MAX)),
    rd_gen_y(uniform_real_distribution<double>(MIN,MAX))
{
    addPoint({0.0,0.0,0.0});
    parent_map.push_back(-1);
    child_map.push_back({});
}

void RRT::grow(size_t N)
{
    for(size_t i=0; i<N; i++)
    {
        auto x = rd_gen_x(rd_x);
        auto y = rd_gen_y(rd_y);
        auto z = 0.0;
        size_t idx = 0;
        auto nearest_pt = nearest({x,y,z},&idx);
        auto start = cloud.pts.size();
        addEdge({x,y,z},idx);
        auto end = cloud.pts.size();
        index->addPoints(start-1,end-1);
    }
}

void RRT::clear()
{
    parent_map.clear();
    child_map.clear();
//    (*index) = KDTreeIndex(3, cloud, KDTreeSingleIndexAdaptorParams());
//    for(size_t i=0; i<cloud.pts.size(); i++)
//        index->removePoint(i);
    cloud.pts.clear();
    delete index;
    index = new KDTreeIndex(3, cloud, KDTreeSingleIndexAdaptorParams());
    addPoint({0.0,0.0,0.0});
    parent_map.push_back(-1);
    child_map.push_back({});
}

void RRT::addEdge(const Point<double> &new_point, size_t nearest_idx)
{
    size_t parent_idx = nearest_idx;
    auto& parent = cloud.pts[parent_map[nearest_idx]];
    auto& nearest_pt = cloud.pts[nearest_idx];

    auto dis = L2Distance(new_point, nearest_pt);
    Point<double> *insert_point = nullptr;
    int insert_assign = 0; //insert in parent(0) of nearest or child(i) of nearest
    int insert_point_parent = nearest_idx;
    int insert_point_child = -1;
    //if nearest has parent
    if(parent_map[nearest_idx]>=0)
    {
        auto l = 0.0;
        double dx, dy, dz;
        double length;
        unitVector(dx,dy,dz,nearest_pt,parent,&length);
        while(l<length)
        {
            auto current_point = Point<double>({parent.x+l*dx,parent.y+l*dy,parent.z+l*dz});
            auto current_dis = L2Distance(new_point,current_point);
            if(current_dis<dis)
            {
                dis = current_dis;
                if(!insert_point)
                    insert_point = new Point<double>({0.0,0.0,0.0});
                *insert_point = current_point;
                insert_point_parent = parent_map[nearest_idx];
                insert_point_child = nearest_idx;
            }
            l += STEP;
        }
    }
    //if nearest has child
    for(size_t i=0; i<child_map[nearest_idx].size(); i++)
    {
        const auto& child = cloud.pts[child_map[nearest_idx][i]];
        auto l = 0.0;
        double dx, dy, dz;
        double length;
        unitVector(dx,dy,dz,nearest_pt,child,&length);
        while(l<length)
        {
            auto current_point = Point<double>({child.x+l*dx,child.y+l*dy,child.z+l*dz});
            auto current_dis = L2Distance(new_point,current_point);
            if(current_dis<dis)
            {
                dis = current_dis;
                if(!insert_point)
                    insert_point = new Point<double>({0.0,0.0,0.0});
                *insert_point = current_point;
                insert_assign = i;
                insert_point_parent = nearest_idx;
                insert_point_child = child_map[nearest_idx][i];
            }
            l += STEP;
        }
    }

    if(insert_point)
    {
        parent_idx = cloud.pts.size();
        insertPoint(*insert_point,insert_point_parent,insert_point_child);
        delete insert_point;
    }
    parent_map.push_back(parent_idx);
    child_map[parent_idx].push_back(cloud.pts.size());
    cloud.pts.push_back(new_point);
    child_map.push_back({});
}

inline
double RRT::L2Distance(const Point<double> &p1, const Point<double> &p2)
{
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    auto dz = p1.z - p2.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

inline
void RRT::insertPoint(const Point<double> &p, int parent)
{
    cloud.pts.push_back(p);
    parent_map.push_back(parent);
    child_map[parent].push_back(cloud.pts.size()-1);
    child_map.push_back({});
}

//insert point p, swap child & parent
inline
void RRT::insertPoint(const Point<double> &p, int parent, int child)
{
    cloud.pts.push_back(p);
    parent_map.push_back(parent);
    parent_map[child] = cloud.pts.size()-1;
    for(size_t i=0; i<child_map[parent].size(); ++i)
        if(child_map[parent][i]==child)
        {
            child_map[parent][i]=cloud.pts.size()-1;
            break;
        }
    child_map.push_back({child});
}

inline
void RRT::unitVector(double &ux, double &uy, double &uz, const Point<double> &p1, const Point<double> &p2, double* l)
{
    auto dx = (p1.x - p2.x);
    auto dy = (p1.y - p2.y);
    auto dz = (p1.z - p2.z);
    auto length = sqrt(dx*dx+dy*dy+dz*dz);
    ux = dx/length;
    uy = dy/length;
    uz = dz/length;
    if(l)
        *l=length;
}
