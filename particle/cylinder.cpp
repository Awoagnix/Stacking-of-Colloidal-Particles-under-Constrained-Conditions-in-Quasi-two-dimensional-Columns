#include <cmath>
#include <random>
#include <vector>
#include "particle.h"
#include "cylinder.h"
#include "constant.h"
#include "coordinatetransformation.h"
#include "lj.h"
#include "harmonic.h"
void cylinder::twistedperiodicboundarycondition(particle &p)
/*粒子离开计算区域时按扭曲周期边界条件返回计算区域*/
    {
        if (p.getz() > H/2)
        {
            double z = p.getz() - H; 
            double theta = atan2(p.gety(),p.getx()); 
            theta += twistangle; 
            double R = sqrt(pow(p.getx(),2) + pow(p.gety(),2)); 
            double x = cos(theta)*R; 
            double y = sin(theta)*R; 
            p.resetposition(x,y,z); 
        }
        else if(p.getz() < - H/2)
        {
            double z = p.getz() + H; 
            double theta = atan2(p.gety(),p.getx()); 
            theta -= twistangle; 
            double R = sqrt(pow(p.getx(),2) + pow(p.gety(),2)); 
            double x = cos(theta)*R; 
            double y = sin(theta)*R; 
            p.resetposition(x,y,z); 
        }
    }
std::vector<double> cylinder::wallparticleR1(particle &p, double rcutoff)
/*输入粒子与墙的截断，返回虚拟的墙粒子坐标，如粒子不在截断内，返回空向量*/
{
    std::vector<double> cart = {p.getx(), p.gety()}; 
    std::vector<double> cyl = cart2cyl(cart); 
    std::vector<double> result; 
    if (cyl[0] > R1 - rcutoff)
    {
        cyl[0] = R1; 
        result = cyl2cart(cyl); 
        result.push_back(p.getz()); 
    }
    return result; 
}
std::vector<double> cylinder::wallparticleR2(particle &p, double rcutoff)
/*输入粒子与墙的截断，返回虚拟的墙粒子坐标，如粒子不在截断内，返回空向量*/
{
    std::vector<double> cart = {p.getx(), p.gety()}; 
    std::vector<double> cyl = cart2cyl(cart); 
    std::vector<double> result; 
    if (cyl[0] > R2 + rcutoff)
    {
        cyl[0] = R2; 
        result = cyl2cart(cyl); 
        result.push_back(p.getz()); 
    }
    return result; 
}
double cylinder::E_wall(particle &p, double rcutoff)
/*粒子与墙接触的势能（lj126）*/
{
    double R = sqrt(pow(p.getx(),2) + pow(p.gety(),2)); 
    double distance1 = R1 - R; 
    double distance2 = R - R2; 
    return E_lj(distance1, 1.0, 1.0, 1.12246) + E_lj(distance2, 1.0, 1.0, 1.12246); 
}
double cylinder::E_particle(std::vector<particle> &ps, int index, double rcutoff)
/*索引号为index的粒子的势能（harmonic）*/
{
    double E = 0.0, x = ps[index - 1].getx(), y = ps[index - 1].gety(), z = ps[index - 1].getz(); 
    for (int i = 0; i < ps.size(); i++)
    {
        if (i != index - 1) /*排除中心粒子*/
        {
            if (z > H/2 - rcutoff)
            {
                if (ps[i].getz() > z - rcutoff)
                {
                    double distance = sqrt(pow((x - ps[i].getx()),2) + pow((y - ps[i].gety()),2) + pow((z - ps[i].getz()),2)); 
                    E += E_harmonic(distance,2.0,1.0); 
                }
                else if (ps[i].getz() < z + rcutoff - H)
                {
                    double r = cart2cyl_r(ps[i].getx(),ps[i].gety()); 
                    double theta = cart2cyl_theta(ps[i].getx(),ps[i].gety()) - twistangle; 
                    double distance = sqrt(pow((x - cyl2cart_x(r,theta)),2) + pow((y - cyl2cart_y(r,theta)),2) + pow((z - ps[i].getz() - H),2)); 
                    E += E_harmonic(distance,2.0,1.0); 
                }
            }
            else if (z < -H/2 + rcutoff)
            {
                if (ps[i].getz() < z + rcutoff)
                {
                    double distance = sqrt(pow((x - ps[i].getx()),2) + pow((y - ps[i].gety()),2) + pow((z - ps[i].getz()),2)); 
                    E += E_harmonic(distance,2.0,1.0); 
                }
                else if (ps[i].getz() < z - rcutoff + H)
                {
                    double r = cart2cyl_r(ps[i].getx(),ps[i].gety()); 
                    double theta = cart2cyl_theta(ps[i].getx(),ps[i].gety()) + twistangle; 
                    double distance = sqrt(pow((x - cyl2cart_x(r,theta)),2) + pow((y - cyl2cart_y(r,theta)),2) + pow((z - ps[i].getz() + H),2)); 
                    E += E_harmonic(distance,2.0,1.0); 
                }
            }
            else
            {
                if (ps[i].getz() > z - rcutoff && ps[i].getz() < z + rcutoff)
                {
                    double distance = sqrt(pow((x - ps[i].getx()),2) + pow((y - ps[i].gety()),2) + pow((z - ps[i].getz()),2)); 
                    E += E_harmonic(distance,2.0,1.0); 
                }
            }
        }
    }
    return E; 
}
std::vector<particle> cylinder::createparticles(int num)
{
    std::random_device c; 
    std::mt19937 e(c()); 
    std::uniform_real_distribution<> rand_r(R2 + 1,R1 - 1), rand_theta(0,2*pi), rand_z(-H/2,H/2); 
    std::vector<particle> ps; 
    for (int i = 0; i < num; i++)
    {
        double r = rand_r(e); 
        double theta = rand_theta(e); 
        particle p(cyl2cart_x(r,theta),cyl2cart_y(r,theta),i + 1,rand_z(e)); 
        ps.push_back(p); 
    }
    return ps; 
}