#include <cmath>
double E_lj(
    double x1, double x2, 
    double y1, double y2, 
    double z1, double z2, 
    double epsilon, double sigma,
    double rcutoff
    )
{
    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
    if (distance < rcutoff)
    {
        return 4*epsilon*(pow(sigma/distance,12) - pow(sigma/distance,6));
    }
    else
    {
        return 0; 
    }
        
}
double E_lj(double distance, double epsilon, double sigma, double rcutoff)
{
    if (distance < rcutoff)
    {
        return 4*epsilon*(pow(sigma/distance,12) - pow(sigma/distance,6));
    }
    else
    {
        return 0; 
    }
}