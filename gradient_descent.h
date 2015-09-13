#include <cstdio>
#include <vector>
#include <array>
#include <cmath>
#include <string.h>
#include <limits>
#include <ctime>
#include <cassert>"
#include "math_utils.h"

/* State of the algorithm includes the dim of state space n, 
 function that is op*timized f, current arg value x and current gradient df */ 





class unconstrainedOptimProblem
{
    
public:
    double (*f)(std::vector<double>);
    std::vector<double> x;
    std::vector<double> df;
    unsigned int n;
    
    unconstrainedOptimProblem(double (*_f)(std::vector<double>),
                              std::vector<double> _x)
    {
        f=_f;//construct with ptr to function
        x=_x;
        n=x.size();
        df.resize(n);
        df.assign (n,0.0);
    }
};

class gradDescent
{
public:
    unconstrainedOptimProblem* state_ptr;
    double armijo_coeff;
    double step_factor;
    double step_size;//TODO add constructor which sets defaults
    
    void update_state(unconstrainedOptimProblem& state)
    {
        state_ptr=&state;
    }
    
    double scalar_func(double s)
    {
        std::vector<double> x=state_ptr->x;
        std::vector<double> df=state_ptr->df;
        std::vector<double> temp1=scalarMult(s,df);
        std::vector<double> temp2=add(x,temp1);
        
        return state_ptr->f(temp2);
    }
    
    void armijo_step()
    {
        std::vector<double>* df_x = &(state_ptr->df);
        std::vector<double>* xold = &(state_ptr->x);
        std::vector<double> xnew = add(*xold,scalarMult(step_size,*df_x));
        double f_x = state_ptr->f(*xold);
        
        int count=0;  
        while(state_ptr->f(xnew)>f_x+armijo_coeff*step_size*dot(*df_x,*df_x) && count<25)
        {
            count++;
            step_size *= step_factor;
            xnew.clear();
            xnew = add(*xold,scalarMult(step_size,*df_x));
        }
        
        state_ptr->x=xnew;//modifies value pointed to by xold
    }
    
    //Constructor
    gradDescent(unconstrainedOptimProblem& _state, double _step_size, double _step_factor, double _armijo_coeff)
    {
        step_size=_step_size;
        step_factor=_step_factor;
        armijo_coeff=_armijo_coeff;
        state_ptr=&_state;
    }
    
    //Constructor(overloaded)
    gradDescent(unconstrainedOptimProblem& _state)
    {
        step_size=1.0;
        step_factor=0.5;
        armijo_coeff=1e-4;
        state_ptr=&_state;
    }
    
};//end of step class