#ifndef OPTIM_UTILS_H
#define OPTIM_UTILS_H

#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <float.h>
#include "matrix.h"


//Compute the gradient by central difference
std::vector<double> gradient(double (*f)(std::vector<double>&), const std::vector<double>& x, double tol)
{
	std::vector<double> grad(x.size());
	std::vector<double> forward = x;
	std::vector<double> backward = x;
	
	double delta=tol;
	double grad_approx;
	int count;
	
	for(int i=0;i<x.size();i++)
	{
		forward = x;
		backward = x;
		
        forward.at(i)+=delta;
        backward.at(i)-=delta;
        grad_approx=(f(forward)-f(backward))/(2.0*delta);
		grad.at(i)=grad_approx;
	}
	return grad;
}

void print_sol(double fval ,int iters,std::vector<double>& x)
{
    printf("Solution found in %d iterations\n",iters);
    printf("Decision variables: %d\n",x.size());
    printf("Minimum cost: %f\n",fval);
    printf("Solution:\n");
    for(int i=0;i<x.size();i++)
    {
        printf("%f\n",x.at(i));
    }
    
    return;
}


#endif