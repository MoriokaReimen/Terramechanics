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
#include "intdiff.hpp"

using std::cos;
using std::sin;
using std::exp;
using std::bind;
using std::placeholders::_1;

/*
*    @brief Constructor of WheelSoil
*    @param [in] soil soil parameters
*    @param [in] wheel wheel parameters
*/
WheelSoil::WheelSoil(const Soil& soil, const Wheel& wheel) : soil_ {soil}, wheel_ {wheel} {
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
    double sigma {0.0};
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
    double tau {0.0};
    if(theta >= theta2 && theta <= theta1) {
        double sigma = getSigma(theta, theta1, theta2, theta_m);
        double j = ((theta1 - theta) - (1 - slip) * (sin(theta1) - sin(theta))) * wheel_.r;
        tau = (soil_.c + sigma * tan(soil_.phi)) * (1 - exp(-j / soil_.K));

    }
    return tau;
}

double WheelSoil::getTraction(const double& theta1, const double& theta2, const double& theta_m, const double& slip) const
{
  auto tau_func = bind(&WheelSoil::getTau, this, _1, theta1, theta2, theta_m, slip);
  auto sigma_func = bind(&WheelSoil::getSigma, this, _1, theta1, theta2, theta_m);
  auto traction = integrate(tau_func, theta1, theta2) + integrate(sigma_func, theta1, theta2);
  return traction;
}
