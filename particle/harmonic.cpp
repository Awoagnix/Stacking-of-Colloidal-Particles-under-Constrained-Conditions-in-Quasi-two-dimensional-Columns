#include<math.h>
double E_harmonic(
    double x1, double x2, 
    double y1, double y2, 
    double z1, double z2, 
    double rc, double k
    )
    {
        double distance = sqrt(pow(x1 - x2,2) + pow(y1 - y2,2) + pow(z1 - z2,2)); 
        if (distance < rc)
        {
            return k*pow(rc - distance,2);
        }
        else
        {
            return 0; 
        }
    }
double E_harmonic(double distance, double rc, double k)
{
    if (distance < rc)
    {
        return k*pow(rc - distance,2);
    }
    else
    {
        return 0; 
    }
}