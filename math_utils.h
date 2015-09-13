#include <cstdio>
#include <vector>
#include <cassert>

std::vector<double> add(const std::vector<double>& x,const std::vector<double>& y)
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

double dot(const std::vector<double>& x,const std::vector<double>& y)
{
    double z;
    if(x.size()!=y.size())
    {
        printf("Inner product of vectors of mismatched size\n");
        assert(x.size()==y.size());
    }   
    else
    { 
        for(int i=0;i<x.size();i++)
        {
            z += x.at(i)*y.at(i);
        }
    }
    return z;
}

std::vector<double> scalarMult(const double c,const std::vector<double>& x)
{ 
    std::vector<double> y=x;
    for(int i=0;i<x.size();i++)
    {
        y.at(i)*=c;
    }
    
    return y;
}