#include <random>
#include <cmath>
std::random_device seed_monetecarlo; 
std::mt19937 engine_montecarlo(seed_monetecarlo()); 
std::uniform_real_distribution<> dis(0.0,1.0); 
bool accept(double E_present, double E_new,double Temperature)
{
    return (E_new < E_present) ? true : ((dis(engine_montecarlo) < exp(- (E_new - E_present)/Temperature)) ? true : false); 
}