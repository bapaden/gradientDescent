
#include "gradient_descent.h"
#include <cstdio>
#include <vector>
// #include <array>
#include <cmath>
// #include <string.h>
// #include <limits>
#include <ctime>
// #include <assert.h>
// //#include "matrix.h"
// 
// //#include "../../../Software_Libraries/boost_1_58_0/boost/concept_check.hpp"
// 
// /* State of the algorithm includes the dim of state space n, 
//   function that is optimized f, current arg value x and current gradient df */ 
// 
// std::vector<double> add(const std::vector<double>& x,const std::vector<double>& y)
// {
//     std::vector<double> z(x.size());
//     if(x.size()!=y.size())
//     {
//         printf("Adding vectors of mismatched size\n");
//         assert(x.size()==y.size());
//     }   
//     else
//     { 
//         for(int i=0;i<x.size();i++)
//         {
//             z.at(i)=x.at(i)+y.at(i);
//         }
//     }
//     return z;
// }
// 
// double dot(const std::vector<double>& x,const std::vector<double>& y)
// {
//     double z;
//     if(x.size()!=y.size())
//     {
//         printf("Inner product of vectors of mismatched size\n");
//         assert(x.size()==y.size());
//     }   
//     else
//     { 
//         for(int i=0;i<x.size();i++)
//         {
//             z += x.at(i)*y.at(i);
//         }
//     }
//     return z;
// }
// 
// std::vector<double> scalarMult(const double c,const std::vector<double>& x)
// { 
//     std::vector<double> y=x;
//     for(int i=0;i<x.size();i++)
//     {
//         y.at(i)*=c;
//     }
//     
//     return y;
// }
// 
// class algState
// {
//     
// public:
//     double (*f)(std::vector<double>);
//     std::vector<double> x;
//     std::vector<double> df;
//     unsigned int n;
//     
//     algState(double (*_f)(std::vector<double>),
//              std::vector<double> _x)
//     {
//         f=_f;//construct with ptr to function
//         x=_x;
//         n=x.size();
//         df.resize(n);
//         df.assign (n,0.0);
//     }
// };
// 
// class gradDescent
// {
// public:
//     algState* state_ptr;
//     double armijo_coeff;
//     double step_factor;
//     double step_size;//TODO add constructor which sets defaults
// 
//     void update_state(algState& state)
//     {
//         state_ptr=&state;
//     }
//     
//     double scalar_func(double s)
//     {
//         std::vector<double> x=state_ptr->x;
//         std::vector<double> df=state_ptr->df;
//         std::vector<double> temp1=scalarMult(s,df);
//         std::vector<double> temp2=add(x,temp1);
//         
//         return state_ptr->f(temp2);
//     }
//     
//     void armijo_step()
//     {
//       std::vector<double>* df_x = &(state_ptr->df);
//       std::vector<double>* xold = &(state_ptr->x);
//       std::vector<double> xnew = add(*xold,scalarMult(step_size,*df_x));
//       double f_x = state_ptr->f(*xold);
//       
//       int count=0;  
//       while(state_ptr->f(xnew)>f_x+armijo_coeff*step_size*dot(*df_x,*df_x) && count<25)
//       {
// 	count++;
// 	step_size *= step_factor;
// 	xnew.clear();
// 	xnew = add(*xold,scalarMult(step_size,*df_x));
//       }
// 
//       state_ptr->x=xnew;//modifies value pointed to by xold
//     }
//     
//     //Constructor
//     gradDescent(algState& _state, double _step_size, double _step_factor, double _armijo_coeff)
//     {
//       step_size=_step_size;
//       step_factor=_step_factor;
//       armijo_coeff=_armijo_coeff;
//       state_ptr=&_state;
//     }
//     
//     //Constructor(overloaded)
//     gradDescent(algState& _state)
//     {
//       step_size=1.0;
//       step_factor=0.5;
//       armijo_coeff=1e-4;
//       state_ptr=&_state;
//     }
//     
// };//end of step class

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
    algState state(&cost_function,x0);
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
