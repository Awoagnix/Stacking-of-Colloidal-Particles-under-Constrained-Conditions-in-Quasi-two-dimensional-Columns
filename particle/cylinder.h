#ifndef CYLINDER_H
#define CYLINDER_H
#include "particle.h"
#include <vector>
#include "constant.h"
class cylinder
{
private:
    double R1; /*外层*/
    double R2; /*内层*/
    double H; 
    double twistangle; 
public:
    cylinder(double R1_in, double R2_in, double H_in, double twistangle_in = pi):R1(R1_in), R2(R2_in), H(H_in), twistangle(twistangle_in){}
    void twistedperiodicboundarycondition(particle &p); 
    std::vector<double> wallparticleR1(particle &p, double rcutoff); 
    std::vector<double> wallparticleR2(particle &p, double rcutoff); 
    double E_wall(particle &p, double rcutoff); 
    double E_particle(std::vector<particle> &ps, int index, double rcutoff = 2.0); 
    std::vector<particle> createparticles(int num); 
}; 
#endif