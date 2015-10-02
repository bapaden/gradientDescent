#ifndef OPTIM_UTILS_H
#define OPTIM_UTILS_H

#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <float.h>
#include "matrix.h"


//Compute the gradient by central difference
std::vector<double> gradient(double (*f)(std::vector<double>), const std::vector<double>& x, double tol)
{
	std::vector<double> grad(x.size());
	std::vector<double> forward = x;
	std::vector<double> backward = x;
	
	double delta;
	double diff=2.0;
	double grad_approx1,grad_approx2;
	int count;
	
	for(int i=0;i<x.size();i++)
	{
		forward = x;
		backward = x;
		delta=1e-3;
		count=0;
		diff=2.0*tol;
		
		while(diff>tol && count<10)
		{
			count++;
			forward.at(i)+=delta;
			backward.at(i)-=delta;
			grad_approx1=(f(forward)-f(backward))/(2.0*delta);
			
			delta*=0.5;
			forward.at(i)-=delta;
			backward.at(i)+=delta;
            grad_approx2=(f(forward)-f(backward))/(2.0*delta);
			diff = fabs(grad_approx2-grad_approx1) / grad_approx1;
		}
		grad.at(i)=grad_approx2;
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