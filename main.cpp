#include <stdio.h>
#include <vector>
#include <array>
#include <cmath>
#include <string.h>
#include <limits>
#include <ctime>
#include <assert.h>
//#include "matrix.h"

//#include "../../../Software_Libraries/boost_1_58_0/boost/concept_check.hpp"

/* State of the algorithm includes the dim of state space n, 
  function that is optimized f, current arg value x and current gradient df */ 

std::vector<double> add(std::vector<double>& x, std::vector<double>& y)
{
    std::vector<double> z(x.size());
    if(x.size()!=y.size())
    {
        printf("Adding vectors of mismatched size\n");
        assert(x.size()==y.size());
    }   
    else
    { 
        for(int i=0;i<x.size();i++)
        {
            z.at(i)=x.at(i)+y.at(i);
        }
    }
    return z;
}

std::vector<double> dot(std::vector<double>& x, std::vector<double>& y)
{
    std::vector<double> z(x.size());
    if(x.size()!=y.size())
    {
        printf("Adding vectors of mismatched size\n");
        assert(x.size()==y.size());
    }   
    else
    { 
        for(int i=0;i<x.size();i++)
        {
            z.at(i)=x.at(i)*y.at(i);
        }
    }
    return z;
}

std::vector<double> scalarMult(double c, std::vector<double>& x)
{ 
    for(int i=0;i<x.size();i++)
    {
        x.at(i)*=c;
    }
    
    return x;
}

class algState
{
    
public:
    double (*f)(std::vector<double>);
    std::vector<double> x;
    std::vector<double> df;
    unsigned int n;
    
    algState(double (*_f)(std::vector<double>),
             std::vector<double> _x)
    {
        f=_f;//construct with ptr to function
        x=_x;
        n=x.size();
        df.resize(n);
        df.assign (n,0.0);
    }
};

class lineSearch
{
public:
    algState* state_ptr;

    void update_state(algState& state)
    {
        state_ptr=&state;
    }
    
    double scalar_func(double s)
    {
        std::vector<double> x=state_ptr->x;
        std::vector<double> df=state_ptr->df;
        std::vector<double> temp1=scalarMult(s,df);
        std::vector<double> temp2=add(x,temp1);
        
        
        return state_ptr->f(temp2);
        //return state_ptr->f(add(x,scalarMult(s,df)));
    }
};

double cost_function(std::vector<double> x)
{
    double cost=0.0;
    for(int i=0;i<x.size();i++)
    {
        cost+=x.at(i)*x.at(i);
    }
    return cost;
}

int main(int argc, char **argv) {

    std::vector<double> x0;
    x0.resize(3);
    x0.at(0)=3.0;
    x0.at(1)=2.0;
    x0.at(2)=1.0;
    algState state(&cost_function,x0);
    state.df.at(0)=-3.0;
    state.df.at(1)=-2.0;
    state.df.at(2)=-1.0;
    
    lineSearch ls;
    ls.state_ptr=&state;
    printf("scalar func %f\n",ls.scalar_func(0.5));
    //next need gradient from sampling a simplex
    //use armijo, forget exact minimization
    
    printf("done");
    return 0;
}
