#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>
#include <fstream>
#include <vector>
#include "particle.h"
class output
{
private:
    std::string location; 
    std::string dump1 = "ITEM: TIMESTEP"; 
    int dump2; 
    std::string dump3 = "ITEM: NUMBER OF ATOMS"; 
    int dump4; 
    std::string dump5 = "ITEM: ATOMS id type x y z";
public:
    std::ofstream out; 
    output(std::string location_in):location(location_in){};
    void timestep(int in){dump2 = in;}; 
    void number(int in){dump4 = in;}; 
    void open(); 
    void outputhead(); 
    void add(std::string item); 
    void dump(particle &p); 
    void dumpitem(std::vector<double> item); 
    void close(); 
};

#endif
