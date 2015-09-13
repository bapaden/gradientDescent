#include <cstdio>
#include <vector>
// #include <array>
// #include <cmath>
// #include <string.h>
// #include <limits>
#include <ctime>
//#include <assert.h>

std::vector<double> add(const std::vector<double>& x,const std::vector<double>& y)
{
    std::vector<double> z(x.size());
    if(x.size()!=y.size())
    {
        printf("Adding vectors of mismatched size\n");
        //assert(x.size()==y.size());
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
        //assert(x.size()==y.size());
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