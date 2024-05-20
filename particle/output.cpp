#include <fstream>
#include <iostream>
#include <vector>
#include "output.h"
#include "particle.h"
void output::open()
{
    out.open(location,std::ofstream::app);
    if(!out){std::cerr<<" "<<std::endl;}
}
void output::close()
{
    out.close(); 
}
void output::outputhead()
{
    out<<dump1<<std::endl; 
    out<<dump2<<std::endl; 
    out<<dump3<<std::endl; 
    out<<dump4<<std::endl; 
}
void output::add(std::string item)
{
    if (!item.empty())
    {
        dump5 += item; 
    }
    out<<dump5<<std::endl; 
}
void output::dump(particle &p)
{
    out<<p.getindex()<<" "<<p.gettype()<<" "<<p.getx()<<" "<<p.gety()<<" "<<p.getz(); 
}
void output::dumpitem(std::vector<double> item)
{
    if (!item.empty())
    {
        for (auto &p : item)
        {
            out<<" "<<p; 
        }
    }
    out<<" "<<std::endl; 
}