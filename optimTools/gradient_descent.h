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
    //Grad tolerance
    double grad_tol;
    //Termination tolerance for argument
    double x_tol;
    //Termination tolerance for function
    double f_tol;
    //Maximum iterations
    int max_iter;
    
    //Uses the gradient (df) and state (x) to determine the step size to take
    std::vector<double> armijo_step()
    {
        std::vector<double> step_data(2);
        std::vector<double>* df_x = &(cost_ptr->df);
        std::vector<double>* xold = &(cost_ptr->x);
        std::vector<double> xnew = (*xold)-(step_size*(*df_x));
        double f_x = cost_ptr->f(*xold);
        double f_new=f_x;
        
       ///* printf("grad in armijo:(%f,%f,%f)\n",df_x->at(0),df_x->at(1),df_x->at(2));
        //printf("x in armijo:(%f,%f,%f)\n",xold->at(0),xold->at(1),xold->at(2));
        //printf("xnew in armijo:(%f,%f,%f)\n",xnew.at(0),xnew.at(1),xnew.at(2));
        int count=0;  
        while(cost_ptr->f(xnew) > f_x-armijo_coeff*step_size*dot(*df_x,*df_x) && count<5)
        {
            count++;
            step_size *= step_factor;
            xnew.clear();
            xnew = (*xold)-(step_size*(*df_x));
        }
        step_data.at(0)=fabs(cost_ptr->f(xnew)-f_x);
        step_data.at(1)=dot( (step_size*(*df_x)),(step_size*(*df_x)) );
        cost_ptr->x=xnew;//modifies value pointed to by xold
        
        return step_data;
    }
    
    void optimize()
    {
        int iter_count = 0;
        std::vector<double> step_data(2);
        step_data.at(0)=f_tol+1.0;
        step_data.at(1)=x_tol+1.0;
        
        while(( step_data.at(0)>x_tol || step_data.at(1)>f_tol) && iter_count<max_iter)
        {
            cost_ptr->df=gradient(cost_ptr->f, cost_ptr->x, grad_tol);
            step_data=armijo_step();
            printf("f:%f\n",cost_ptr->f(cost_ptr->x));
            printf("x:(%f,%f,%f)\n",cost_ptr->x.at(0),cost_ptr->x.at(1),cost_ptr->x.at(2));
            
            iter_count++;
            
        }
    }
    
    //Constructor
    gradDescent(unconstrainedOptimProblem& _state,double _step_size,double _step_factor,double _armijo_coeff,double _grad_tol,double _x_tol,double _f_tol,int _max_iter)
    {
        step_size=_step_size;
        step_factor=_step_factor;
        armijo_coeff=_armijo_coeff;
        cost_ptr=&_state;
        //Does comparison with the square so don't have to do sqrt operation
        x_tol=_x_tol*_x_tol;
        f_tol=_f_tol;
        max_iter=_max_iter;
        grad_tol=_grad_tol;
    }
    
    //Constructor(overloaded)
    gradDescent(unconstrainedOptimProblem& _state)
    {
        step_size=1.0;
        step_factor=0.5;
        armijo_coeff=1e-4;
        f_tol=1e-6;
        x_tol=1e-6;
        cost_ptr=&_state;
        max_iter=100;
        grad_tol=1e-3;
    }
    
};//end of step class

#endif