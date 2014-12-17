/**
-----------------------------------------------------------------------------
@file    wheel_soil.cpp
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
@brief Encapsulates Bekker-Wong Theory for Vehicle-Wheel Interactionshear
-----------------------------------------------------------------------------
*/
#include "wheel_soil.hpp"
using std::cos;
using std::sin;
using std::exp;
using std::function;

/*
*    @brief Constructor of WheelSoil
*    @param [in] soil soil parameters
*    @param [in] wheel wheel parameters
*/
WheelSoil::WheelSoil(const Soil& soil, const Wheel& wheel) : soil_{soil}, wheel_{wheel}
{
}
        
/*
*    @brief Get the normal stress along the front of the wheel for a given
*    @param [in] theta angle[radian]
*    @param [in] theta1 entry angle[radian]
*    @return radial stress in the front region of the soil[Pa]
*/
double WheelSoil::getSigma1_(const double& theta, const double& theta1) const
{
    double z = (cos(theta) - cos(theta1)) * wheel_.r; //! sinkage
    double sigma1 = (soil_.k1 + soil_.k2 * wheel_.b) * pow(z / wheel_.b, soil_.n);
    return sigma1;
}
        
/*
*    @brief Get the normal stress along the back of the wheel for a given
*    @param [in] theta normal stress on the sheared surface
*    @param [in] theta1 entry angle[radian]
*    @param [in] theta2 exit angle[radian]
*    @param [in] theta_m angular position of the maximum radial stress[radian]
*    @return radial stress in the rear region of the soil
*/
double WheelSoil::getSigma2_(const double& theta, const double& theta1, const double& theta2,
    const double& theta_m) const
{
    double z = (cos(theta1 - ((theta - theta2) / (theta_m - theta2)) * (theta1 - theta_m))
        - cos(theta1)) * wheel_.r;
    double sigma_2 = soil_.k1 * pow(z / wheel_.b, soil_.n); //! k1 is k_eq here
    return sigma_2;
}
        
/*
*    @brief Get the normal stress at any angle on the wheel
*    @param [in] theta normal stress on the sheared surface
*    @param [in] theta1 entry angle[radian]
*    @param [in] theta2 exit angle[radian]
*    @param [in] theta_m angular position of the maximum radial stress[radian]
*    @return radial stress in the any region of the soil
*/
double WheelSoil::getSigma(const double& theta, const double& theta1, const double& theta2,
        const double& theta_m) const
{
    double sigma{0.0};
    if(theta > theta_m && theta <= theta1)
        sigma = getSigma1_(theta, theta1);
    else if(theta >= theta2 && theta < theta_m)
        sigma = getSigma2_(theta, theta1, theta2, theta_m);

    return sigma;
}
        
/*
*    @brief Get the shear stress at any angle on the wheel
*    @param [in] theta normal stress on the sheared surface
*    @param [in] theta1 entry angle[radian]
*    @param [in] theta2 exit angle[radian]
*    @param [in] theta_m angular position of the maximum radial stress[radian]
*    @param [in] slip  slip ratio
*    @return radial stress in the any region of the soil
*/
double WheelSoil::getTau(const double& theta, const double& theta1, const double& theta2,
        const double& theta_m, const double& slip) const
{
    double tau{0.0};
    if(theta >= theta2 && theta <= theta1)
    {
        double sigma = getSigma(theta, theta1, theta2, theta_m);
        double j = ((theta1 - theta) - (1 - slip) * (sin(theta1) - sin(theta))) * wheel_.r;
        tau = (soil_.c + sigma * tan(soil_.phi)) * (1 - exp(-j / soil_.K));

    }
    return tau;
}

/*
*    @brief Integrate math funciton
*    @param [in] func math function to integrate
*    @param [in] start start value of variable
*    @param [in] end end value of variable
*    @return result result of integration
*/
double integrate(function<double(double)> func, double start, double end)
{
    typedef function<double(double)> func_type;
    gsl_integration_workspace *w
        = gsl_integration_workspace_alloc(1000);
    double result, error;
    gsl_function F;

    F.function = [](double x, void* p){ return (*static_cast<func_type*>(p))(x);};
    F.params = &func;
    gsl_integration_qags(&F, start, end, 0, 1e-7, 1000, w, &result, &error);
    return result;
}
