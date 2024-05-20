#include "particle.h"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "arrayoperate.h"
#include "constant.h"
std::random_device seed; 
std::mt19937 engine(seed()); 
std::uniform_real_distribution<> dis_r(0.0,1.0), dis_theta(0.0,2*pi), dis_phi(0.0,pi); 
std::vector<int> find_cutoff
(
    double rcutoff /*中心粒子搜索范围*/, 
    int index /*中心粒子索引*/, 
    std::vector<particle>&a /*粒子搜索列表（包含中心粒子*/
)
{
    std::vector<int> result;
    for (auto& point : a) 
    {
        if (point.getindex() != index) {
            double distance = sqrt(pow(point.getx() - a[index - 1].getx(), 2) + pow(point.gety() - a[index - 1].gety(), 2) + pow(point.getz() - a[index - 1].getz(), 2));
            if (distance <= rcutoff) {
                result.push_back(point.getindex());
            }
        }
    }
    return result; 
}
std::vector<double> displacementonestep(double max/*最大位移*/)  /*一步随机位移*/
{
    std::vector<double> result; 
    double r = max*dis_r(engine); 
    double theta = dis_theta(engine); 
    double phi = dis_phi(engine); 
    result.push_back(r*sin(phi)*cos(theta)); 
    result.push_back(r*sin(phi)*sin(theta)); 
    result.push_back(r*cos(phi)); 
    return result; 
}


    void particle::addneighboutlist(int index_in) /*向邻居列表中添加粒子索引*/
    {
        if (index_in != index && findindex(neighbourlist,index_in) == -1)
        {
            neighbourlist.push_back(index_in); 
        }
    }
    void particle::deleteneighboutlist(int index_in) /*从邻居列表中删除粒子索引*/
    {
        if (index_in != index && findindex(neighbourlist,index_in) != -1)
        {
           neighbourlist.erase(neighbourlist.begin() + findindex(neighbourlist,index_in)); 
        }
    }
    void particle::setneighboutlist(std::vector<unsigned int> in) /*初始化邻居列表*/
    {
        if (findindex(in,index) != -1)/*检查输入是否包含本粒子索引，如有则删除*/
        {
            in.erase(in.begin() + findindex(in,index)); 
        }
        
        neighbourlist = in; 
    }
    void particle::showmessage()/*显示粒子信息*/
    {
        std::cout<<"粒子id："<<index<<std::endl; 
        std::cout<<"类型："<<type<<std::endl; 
        std::cout<<"直径："<<D<<std::endl; 
        std::cout<<"坐标：("<<x<<","<<y<<","<<z<<")"<<std::endl; 
        std::cout<<"速度：("<<vx<<","<<vy<<","<<vz<<")"<<std::endl; 
        if (neighbourlist.begin() != neighbourlist.end())
        {
            std::cout<<"邻居列表："; 
            for(int i = 0; i != neighbourlist.size(); i++)
            {
                if (i != neighbourlist.size() - 1)
                {
                    std::cout<<neighbourlist[i]<<","; 
                }
                else
                {
                    std::cout<<neighbourlist[i]<<std::endl; 
                }
            }
        }
        else
        {
            std::cout<<"邻居列表：无"<<std::endl; 
        }
        
        
    }
    void particle::particledisplacement(std::vector<double> displacement) /*粒子的一步位移*/
    {
        x += displacement[0]; 
        y += displacement[1]; 
        z += displacement[2]; 
    }
    void particle::particledisplacement(double max)/*粒子的一步位移*/
    {
        std::vector<double> displacement = displacementonestep(max); 
        x += displacement[0]; 
        y += displacement[1]; 
        z += displacement[2]; 
    }