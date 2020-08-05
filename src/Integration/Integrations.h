/**
 * @file Integrations.h
 * @author C. H. Egerland
 */

#ifndef SPIKE_INTEGRATIONS_H
#define SPIKE_INTEGRATIONS_H

#include <cmath>
#include <functional>
#include <gsl/gsl_math.h>
#include <iostream>

template <typename F> class gsl_function_pp : public gsl_function {
public:
  explicit gsl_function_pp(const F &func) : gsl_function_struct(), _func(func) {
    function = &gsl_function_pp::invoke;
    params = this;
  }

private:
  const F &_func;
  static double invoke(double x, void *params) {
    return static_cast<gsl_function_pp *>(params)->_func(x);
  }
};

// wrapper functions for integration routines of the gsl
double cquad(const std::function<double(double)> &f, double a, double b,
             double relerr, double epsabs);
double qags(const std::function<double(double)> &f, double a, double b,
            double relerr, double epsabs);
double qagil(const std::function<double(double)> &f, double a, double relerr,
             double epsabs);

double heaviside(double x);


#endif // SPIKE_INTEGRATIONS_H
