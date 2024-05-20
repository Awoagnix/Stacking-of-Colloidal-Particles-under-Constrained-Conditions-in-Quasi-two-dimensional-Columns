#include<cmath>
#include<vector>
#include "coordinatetransformation.h"
/*默认：
*cart:[x,y,z]
*cyl:[r,θ,z]
*sph:[r,θ,φ]
*/
std::vector<double> cart2cyl(std::vector<double> cart)
{
    std::vector<double> result; 
    result.push_back(cart2cyl_r(cart[0],cart[1])); 
    result.push_back(atan2(cart[1],cart[0])); 
    return result; 
}
std::vector<double> cart2cyl(double x, double y)
{
    std::vector<double> result; 
    result.push_back(cart2cyl_r(x,y)); 
    result.push_back(atan2(y,x)); 
    return result; 
}
double cart2cyl_r(double x, double y){return sqrt(pow(x,2) + pow(y,2)) ; }
double cart2cyl_theta(double x, double y){return atan2(y,x) ; }
std::vector<double> cart2sph(std::vector<double> cart)
{
    std::vector<double> result; 
    result.push_back(sqrt(pow(cart[0],2) + pow(cart[1],2) + pow(cart[2],2))); 
    result.push_back(atan2(cart[1],cart[0])); 
    result.push_back(atan2((pow(cart[0],2) + pow(cart[1],2)),cart[2]));
    return result; 
}
std::vector<double> cart2sph(double x, double y, double z)
{
    std::vector<double> result; 
    result.push_back(cart2sph_r(x, y, z)); 
    result.push_back(atan2(y,x)); 
    result.push_back(cart2sph_phi(x, y, z));
    return result; 
}
double cart2sph_r(double x, double y, double z){return sqrt(pow(x,2) + pow(y,2) + pow(z,2));}
double cart2sph_theta(double x, double y){return atan2(y,x);}
double cart2sph_phi(double x, double y, double z){return atan2((pow(x,2) + pow(y,2)),z);}
std::vector<double> cyl2cart(std::vector<double> cyl)
{
    std::vector<double> result; 
    result.push_back(cyl[0]*cos(cyl[1])); 
    result.push_back(cyl[0]*sin(cyl[1])); 
    return result; 
}
std::vector<double> cyl2cart(double r, double theta)
{
    std::vector<double> result; 
    result.push_back(r*cos(theta)); 
    result.push_back(r*sin(theta)); 
    return result; 
}
double cyl2cart_x(double r, double theta){return r*cos(theta);}
double cyl2cart_y(double r, double theta){return r*sin(theta);}
std::vector<double> sph2cart(std::vector<double> sph)
{
    std::vector<double> result; 
    result.push_back(sph[0]*sin(sph[2])*cos(sph[1])); 
    result.push_back(sph[0]*sin(sph[2])*sin(sph[1])); 
    result.push_back(sph[0]*cos(sph[2])); 
    return result; 
}
std::vector<double> sph2cart(double r, double theta, double phi)
{
    std::vector<double> result; 
    result.push_back(r*sin(phi)*cos(theta)); 
    result.push_back(r*sin(phi)*sin(theta)); 
    result.push_back(r*cos(phi)); 
    return result; 
}
double sph2cart_x(double r, double theta, double phi){return r*sin(phi)*cos(theta);}
double sph2cart_y(double r, double theta, double phi){return r*sin(phi)*sin(theta);}
double sph2cart_z(double r, double phi){return r*cos(phi);}