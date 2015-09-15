#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <float.h>

//vector sum
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

//inner product
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

//multiply a vector by a scalar
std::vector<double> scalarMult(const double c,const std::vector<double>& x)
{ 
	std::vector<double> y=x;
	for(int i=0;i<x.size();i++)
	{
		y.at(i)*=c;
	}
	
	return y;
}

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
		
		while(diff>tol && 10.0*diff<DBL_MAX)
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









