#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <cmath>
#include <iostream>

std::vector<double> displacementonestep(double max); 
class particle 
{
private:
    double x,y,z; /*粒子坐标*/
    double vx,vy,vz; /*粒子速度*/
    double D; /*粒子直径*/
    int index; /*粒子索引*/
    int type; /*粒子类型*/
    std::vector<unsigned int> neighbourlist; /*邻居列表*/
public:
    double E; /*粒子势能*/

private:
    template<class r>
    r returnin(r in){return in;}
public:
    particle(const particle &in):x(in.x), y(in.y), z(in.z), vx(in.vx), vy(in.vy), vz(in.vz), D(in.D), index(in.index), type(in.type), neighbourlist(in.neighbourlist), E(in.E){}; 
    particle(double x_in, double y_in, int index_in, double z_in = 0, int type_in = 1, double vx_in = 0, double vy_in = 0, double vz_in = 0, double E_in = 0, double D_in = 1):/*构造函数：输入坐标*/
    x(x_in), y(y_in), z(z_in), index(index_in), type(type_in), vx(vx_in), vy(vy_in), vz(vz_in), E(E_in), D(D_in) {};

    void resetposition(double x_in,double y_in,double z_in = 0)/*重设坐标*/
    {
        x = x_in; 
        y = y_in; 
        z = z_in; 
    }
    void resetvelocity(double vx_in,double vy_in,double vz_in = 0)/*重设速度*/
    {
        vx = vx_in; 
        vy = vy_in; 
        vz = vz_in; 
    }
    void settype(int type_in){type = type_in; }; 
    void addneighboutlist(int index_in);/*向邻居列表中添加粒子索引*/
    void deleteneighboutlist(int index_in);/*从邻居列表中删除粒子索引*/
    void setneighboutlist(std::vector<unsigned int> in);/*初始化邻居列表*/
    void showmessage();/*显示粒子信息*/
    void particledisplacement(std::vector<double> displacement);/*粒子的一步位移*/
    void particledisplacement(double max);/*粒子的一步位移*/
    /*输出粒子信息*/
    double getx(){return x;}
    double gety(){return y;}
    double getz(){return z;}
    double getvx(){return vx;}
    double getvy(){return vy;}
    double getvz(){return vz;}
    int getindex(){return index;}
    int gettype(){return type;}
    std::vector<unsigned int> getneighbourlist(){return neighbourlist;}

};
std::vector<int> find_cutoff(double rcutoff, int index, std::vector<particle>&a); 
#endif