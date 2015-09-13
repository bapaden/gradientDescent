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
    x0.at(0)=3.0;
    x0.at(1)=2.0;
    x0.at(2)=1.0;
    unconstrainedOptimProblem state(&cost_function,x0);
    state.df.at(0)=-3.0;
    state.df.at(1)=-2.0;
    state.df.at(2)=-1.0;
    
    gradDescent gd(state);
//     gd.state_ptr=&state;
//     gd.step_size=10.0;
//     gd.armijo_coeff=1e-3;
//     gd.step_factor=0.5;
    printf("scalar func %f\n",gd.scalar_func(0.5));
    
    printf("state: (%f,%f,%f)\n",gd.state_ptr->x.at(0),gd.state_ptr->x.at(1),gd.state_ptr->x.at(2));
    gd.armijo_step();
    printf("new state: (%f,%f,%f)\n",gd.state_ptr->x.at(0),gd.state_ptr->x.at(1),gd.state_ptr->x.at(2));
    printf("new cost: %f\n",gd.state_ptr->f(gd.state_ptr->x));
    //next need gradient from sampling a simplex
    //use armijo, forget exact minimization
    
    printf("done");
    return 0;
}
