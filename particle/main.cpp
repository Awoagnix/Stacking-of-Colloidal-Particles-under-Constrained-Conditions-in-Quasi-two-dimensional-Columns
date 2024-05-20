#include <vector>
#include <random>
#include <iostream>
#include "particle.h"
#include "cylinder.h"
#include "output.h"
#include "montecarlo.h"
#include "constant.h"
using namespace std; 
double R1 = 3.4, h = 0.8, rho = 0.95, H = 8.0; 
double R2 = R1 - h - 2; 
int num = round(rho*pi*H*(pow(R1 - 0.5,2) + pow(R2 - 0.5,2))); ; 
int MCS = 10000; 
default_random_engine m; 
uniform_int_distribution<int> ind(1,num); 
int main()
{

    vector<double> temp; 
    temp.push_back(10.0); 
    int tempnum = 80; 
    for (int i = 0; i < tempnum; i++)
    {
        temp.push_back(*(temp.end() - 1)*0.8); 
    }
    
    vector<particle> ps; 
    cylinder cyl(R1,R2,H); 
    ps = cyl.createparticles(num); 
    ps[0].settype(2); 
    output out("E:\\mycode\\C++\\particle\\d.dump"); 
    out.number(num); 
    out.open(); 

    double acceptpossibility = 0.0; 
    
    cout<<"R1 = "<<R1<<endl; 
    cout<<"R2 = "<<R2<<endl; 
    cout<<"H = "<<H<<endl; 
    cout<<"rho = "<<rho<<endl; 
    cout<<"MCS = "<<MCS<<endl; 

for (int time = 1; time < tempnum + 2; time++)
{
    cout<<endl; 
    cout<<"Temperature = "<<temp[time - 1]<<endl;
    cout<<endl; 
    out.timestep(time); 
    for (int j = 0; j < MCS; j++)
    {
        /*1MCS*/
        // out.timestep(time); 
        for (int i = 0; i < num; i++)
        {
            int indexi = ind(m); 
            particle pari(ps[indexi - 1]); 
            pari.E = cyl.E_particle(ps,indexi) + cyl.E_wall(ps[indexi - 1],1.12246); 
            ps[indexi - 1].particledisplacement(0.2); 
            cyl.twistedperiodicboundarycondition(ps[indexi - 1]); 
            ps[indexi - 1].E = cyl.E_particle(ps,indexi) + cyl.E_wall(ps[indexi - 1],1.12246); 
            if (!accept(pari.E,ps[indexi - 1].E,temp[time - 1]))
            {
                ps[indexi - 1].resetposition(pari.getx(),pari.gety(),pari.getz()); 
            }
            else
            {
                acceptpossibility++; 
            }
        }
    // out.outputhead(); 
    // out.add(""); 
    // for (particle &i : ps)
    // {
    //     out.dump(i); 
    //     std::vector<double> item; 
    //     out.dumpitem(item); 
    // }
        
        if (j%1000 == 0)
        {
            cout<<"MonteCarlo Step:"<<j<<endl; 
            double E = 0.0; 
            for (int i = 0; i < num; i++)
            {
                E += cyl.E_particle(ps,i + 1) + cyl.E_wall(ps[i],1.12246); 
            }
            cout<<"Total Energy:"<<E<<endl; 
            cout<<"Acceptance Probability:"<<acceptpossibility/(10.0*num)<<"%"<<endl;
            acceptpossibility = 0; 
        }
        
    }
    out.outputhead(); 
    out.add(""); 
    for (particle &i : ps)
    {
        out.dump(i); 
        std::vector<double> item; 
        out.dumpitem(item); 
    }
}
out.out<<endl; 
out.out<<"R1 = "<<R1<<endl; 
out.out<<"R2 = "<<R2<<endl; 
out.out<<"H = "<<H<<endl; 
out.out<<"rho = "<<rho<<endl; 
out.out<<"MCS = "<<MCS<<endl; 
out.close(); 
}