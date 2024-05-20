#ifndef LJ_H
#define LJ_H
double E_lj(
    double x1, double x2, 
    double y1, double y2, 
    double z1, double z2, 
    double epsilon, double sigma,
    double rcutoff
    ); 
double E_lj(double distance, double epsilon, double sigma, double rcutoff); 
#endif