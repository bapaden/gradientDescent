#include "optimTools/gradient_descent.h"
#include <memory>

typedef std::shared_ptr<double> dblPtr;
class myProblem: public cost_function
{
public:
    myProblem()
    {
        return;
    }
    double cost(decisionVar& x)
    {
        double c=0.0;
        for(int i=0;i<x.size();i++)
        {
            c+=x[i]*x[i]*(1.0+10.0*(double) i);
        }
        return c;
    }
};

int main(int argc, char **argv) {
    
    //Cost object
    myProblem myCost;
    //Initial condition
    std::vector<double> x0;
    x0.resize(20);
    for(int i=0;i<x0.size();i++)
    {
        x0.at(i)=4.0;
    }
    
    //Initialize an optimization problem
//     unconstrainedOptimProblem example_problem(&myCost,x0);
    
    //Initial step size of armijo step
    double step_size=1.0;
    //Reduction of step size to meet armijo condition
    double step_factor=0.5;
    //Parameter for armijo condition
    double armijo_coeff=1e-3;
    //Tolerance of gradient computation
    double grad_tol=1e-6;
    //Termination conditions
    double f_tol=1e-6;
    double x_tol=1e-6;
    int max_iter=500;
    //Initialize gradient descent solver
    gradDescent gd(&myCost,
                   x0,
                   step_size,
                   step_factor,
                   armijo_coeff,
                   grad_tol,
                   x_tol,
                   f_tol,
                   max_iter);
    
    //Call optimization function
    gd.optimize();
    //Print the solution to terminal
    print_sol(gd.f->cost(gd.x),gd.max_iter,gd.x);
    
    return 0;
}
