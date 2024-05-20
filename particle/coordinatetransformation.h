#ifndef COORDINATETRANSFORMATION_H
#define COORDINATETRANSFORMATION_H
#include<vector>
std::vector<double> cart2cyl(std::vector<double> cart);
std::vector<double> cart2cyl(double x, double y); 
double cart2cyl_r(double x, double y); 
double cart2cyl_theta(double x, double y); 
std::vector<double> cart2sph(std::vector<double> cart);
std::vector<double> cart2sph(double x, double y, double z); 
double cart2sph_r(double x, double y, double z); 
double cart2sph_theta(double x, double y); 
double cart2sph_phi(double x, double y, double z); 
std::vector<double> cyl2cart(std::vector<double> cyl);
std::vector<double> cyl2cart(double r, double theta); 
double cyl2cart_x(double r, double theta); 
double cyl2cart_y(double r, double theta); 
std::vector<double> sph2cart(std::vector<double> sph);
std::vector<double> sph2cart(double r, double theta, double phi); 
double sph2cart_x(double r, double theta, double phi); 
double sph2cart_y(double r, double theta, double phi); 
double sph2cart_z(double r, double phi); 
#endif