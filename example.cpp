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
    
    //Initial condition
    std::vector<double> x0;
    x0.resize(3);
    x0.at(0)=1.0;
    x0.at(1)=2.0;
    x0.at(2)=3.0;
    
    //Initialize an optimization problem
    unconstrainedOptimProblem example_problem(&cost_function,x0);
    
    //Initial step size of armijo step
    double step_size=1.0;
    //Reduction of step size to meet armijo condition
    double step_factor=0.5;
    //Parameter for armijo condition
    double armijo_coeff=1e-4;
    //Tolerance of gradient computation
    double grad_tol=1e-3;
    //Termination conditions
    double f_tol=1e-6;
    double x_tol=1e-6;
    int max_iter=1000;
    //Initialize gradient descent solver
    gradDescent gd(example_problem,
                   step_size,
                   step_factor,
                   armijo_coeff,
                   grad_tol,
                   x_tol,
                   f_tol,
                   max_iter);
    
    //Call optimization function
    gd.optimize();
    
    return 0;
}
