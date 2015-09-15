#include "gradient_descent.h"

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
	
	//for debugging and testing
	std::vector<double> x0;
	x0.resize(3);
	x0.at(0)=1.0;
	x0.at(1)=2.0;
	x0.at(2)=3.0;
	unconstrainedOptimProblem state(&cost_function,x0);
	state.df.at(0)=-3.0;
	state.df.at(1)=-2.0;
	state.df.at(2)=-1.0;
	
	gradDescent gd(state);
	
// 	printf("grad: (%f,%f,%f)\n",state.df.at(0),state.df.at(1),state.df.at(2));
	state.df=gradient(&cost_function, x0, 1e-2);
	printf("grad: (%f,%f,%f)\n",state.df.at(0),state.df.at(1),state.df.at(2));
	
// 	printf("state: (%f,%f,%f)\n",gd.state_ptr->x.at(0),gd.state_ptr->x.at(1),gd.state_ptr->x.at(2));
	gd.armijo_step();
// 	printf("new state: (%f,%f,%f)\n",gd.state_ptr->x.at(0),gd.state_ptr->x.at(1),gd.state_ptr->x.at(2));
// 	printf("new cost: %f\n",gd.state_ptr->f(gd.state_ptr->x));
	
	printf("done");
	return 0;
}
