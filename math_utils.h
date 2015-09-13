#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>

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

std::vector<double> gradient(double (*f)(std::vector<double>), const std::vector<double>& x, double tol)
{
	std::vector<double> grad(x.size());
	std::vector<double> forward = x;
	std::vector<double> backward = x;
	
	
	double delta=1.0;
	double eps=1.0;
	double diff=1.0;
	double grad1, grad_approx;
	int count;
	printf("running grad\n");
	printf("f(x0):%f\n",f(x));
	
	for(int i=0;i<x.size();i++)
	{
		delta=1.0;
		eps=1.0;
		count=0;
		while(fabs(diff-1)>tol && count<10)
		{
			count++;
			
			forward.at(i)+=delta;
			backward.at(i)-=delta;
			grad_approx=(f(forward)-f(backward))/(2.0*delta);
			
			delta*=0.5;
			forward.at(i)-=delta;
			backward.at(i)+=delta;
			diff = ( (f(forward)-f(backward))/(2.0*delta) ) / grad_approx;
			
			printf("diff:%f\n",diff);
		}
		grad.at(i)=grad_approx;
	}
	
	return grad;
}









