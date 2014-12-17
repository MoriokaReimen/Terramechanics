/**
-----------------------------------------------------------------------------
@file    intdiff.cpp
----------------------------------------------------------------------------
         @@
       @@@@@@
      @```@@@@
     @`  `@@@@@@
   @@`   `@@@@@@@@
  @@`    `@@@@@@@@@           Tohoku University
  @` `   `@@@@@@@@@       SPACE ROBOTICS LABORATORY
  @`` ## `@@@@@@@@@    http://www.astro.mech.tohoku.ac.jp/
  @` #..#`@@@@@@@@@        Planetary Robotics Group
  @` #..#`@@@@@@@@@
  @` ### `@@@@@@@@@          Professor Kazuya Yoshida
  @` ###``@@@@@@@@@      Associate Professor Keiji Nagatani
   @### ``@@@@@@@@
   ###  ` @@@@@@@
  ###  @  @@@@@                 Creation Date:
 ###    @@@@@               @date Dec. 16. 2014
 /-\     @@
|   |      %%                      Authors:
 \-/##    %%%%%             @author Kei Nakata
   #### %%%                  menschenjager.mark.neun@gmail.com
     ###%%       *
      ##%%     *****
       #%%      ***
        %%     *   *
         %%
          %%%%%
           %%%
-----------------------------------------------------------------------------
@brief integreration and differentiation functions.
-----------------------------------------------------------------------------
*/
#include "intdiff.hpp"
using std::function;

/*
*    @brief Integrate math funciton
*    @param [in] func math function to integrate
*    @param [in] start start value of variable
*    @param [in] end end value of variable
*    @param [in] max_error max error value
*    @return result result of integration
*/
double integrate(function<double(double)> func, double start, double end, double max_error)
{
    typedef function<double(double)> func_type;
    gsl_integration_workspace *w
        = gsl_integration_workspace_alloc(1000);
    double result, error;
    gsl_function F;

    F.function = [](double x, void* p) {
        return (*static_cast<func_type*>(p))(x);
    };
    F.params = &func;
    gsl_integration_qags(&F, start, end, 0, 1e-7, 1000, w, &result, &error);
    gsl_integration_workspace_free(w);

    return result;
}

/*
*    @brief differentiate math funciton
*    @param [in] func math function to integrate
*    @param [in] start start value of variable
*    @param [in] max_error max error value
*    @return result result of integration
*/
double differentiate(function<double(double)> func, double x, double max_error)
{
    typedef function<double(double)> func_type;
    double result {0}, error {0};

    gsl_function F;
    F.function = [](double x, void* p) {
        return (*static_cast<func_type*>(p))(x);
    };
    F.params = &func;

    gsl_deriv_central(&F, x, max_error, &result, &error);

    return result;
}
