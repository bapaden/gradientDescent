#include "gradient_descent.h"

double cost_function(std::vector<double> x)
{
	double cost=0.0;
	for(int i=0;i<x.size();i++)
	{
		cost+=x.at(i)*(i+1.0)*x.at(i);
	}
	return cost;
}

int main(int argc, char **argv) {
	
	//for debugging and testing
	std::vector<double> x0;
	x0.resize(3);
	x0.at(0)=1.0;
	x0.at(1)=2.0;
	x0.at(2)=3.0;
	unconstrainedOptimProblem state(&cost_function,x0);
	
	gradDescent gd(state);
	
	for(int i=0;i<5;i++)
	{
		
		printf("\ncost: %f\n",gd.cost_ptr->f(gd.cost_ptr->x));
		printf("state: (%f,%f,%f)\n",gd.cost_ptr->x.at(0),gd.cost_ptr->x.at(1),gd.cost_ptr->x.at(2));
		gd.cost_ptr->df=gradient(&cost_function, gd.cost_ptr->x, 1e-2);
		printf("grad: (%f,%f,%f)\n",gd.cost_ptr->df.at(0),gd.cost_ptr->df.at(1),gd.cost_ptr->df.at(2));
		gd.armijo_step();
		printf("new state: (%f,%f,%f)\n",gd.cost_ptr->x.at(0),gd.cost_ptr->x.at(1),gd.cost_ptr->x.at(2));
		printf("new cost: %f\n",gd.cost_ptr->f(gd.cost_ptr->x));
	}
	
	printf("done");
	return 0;
}
