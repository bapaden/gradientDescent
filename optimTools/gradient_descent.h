#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <string.h>
#include <limits>
#include <ctime>
#include "optim_utils.h"

class unconstrainedOptimProblem
{
	
public:
	//pointer to cost function
	double (*f)(std::vector<double>);
	//current state of algorithm
	std::vector<double> x;
	//gradient at current state
	std::vector<double> df;
	//dimension of the search space
	unsigned int n;
	
	//Constructor
	unconstrainedOptimProblem(double (*_f)(std::vector<double>),
							  std::vector<double> _x)
	{
		//Assign pointer to cost function
		f=_f;
		//Assign state of algorithm to initial condition
		x=_x;
		//Dimension of search space determined by size of initial condition
		n=x.size();
		//Set dimension of gradient
		df.resize(n);
		//Initialize gradient to zero
		df.assign (n,0.0);
	}
};

class gradDescent
{
public:
	unconstrainedOptimProblem* cost_ptr;
	//Line search termination condition based on armijo rule
	double armijo_coeff;
	//How much to decrease the step while attempting to satisfy armijo rule
	double step_factor;
	//Initial step size for line search
	double step_size;
	
	//Uses the gradient (df) and state (x) to determine the step size to take
	void armijo_step()
	{
		std::vector<double>* df_x = &(cost_ptr->df);
		std::vector<double>* xold = &(cost_ptr->x);
// 		std::vector<double> xnew = add(*xold,scalarMult(-step_size,*df_x));
        std::vector<double> xnew = (*xold)-(step_size*(*df_x));
        double f_x = cost_ptr->f(*xold);
		
		printf("grad in armijo:(%f,%f,%f)\n",df_x->at(0),df_x->at(1),df_x->at(2));
		printf("x in armijo:(%f,%f,%f)\n",xold->at(0),xold->at(1),xold->at(2));
		printf("xnew in armijo:(%f,%f,%f)\n",xnew.at(0),xnew.at(1),xnew.at(2));
		int count=0;  
		while(cost_ptr->f(xnew) > f_x-armijo_coeff*step_size*dot(*df_x,*df_x) && count<25)
		{
			count++;
			step_size *= step_factor;
			xnew.clear();
// 			xnew = add(*xold,scalarMult(-step_size,*df_x));
            xnew = (*xold)-(step_size*(*df_x));
		}
		
		cost_ptr->x=xnew;//modifies value pointed to by xold
	}
	
	//Constructor
	gradDescent(unconstrainedOptimProblem& _state, double _step_size, double _step_factor, double _armijo_coeff)
	{
		step_size=_step_size;
		step_factor=_step_factor;
		armijo_coeff=_armijo_coeff;
		cost_ptr=&_state;
	}
	
	//Constructor(overloaded)
	gradDescent(unconstrainedOptimProblem& _state)
	{
		step_size=1.0;
		step_factor=0.5;
		armijo_coeff=1e-4;
		cost_ptr=&_state;
	}
	
};//end of step class

#endif