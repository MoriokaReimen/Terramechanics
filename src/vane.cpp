/**
-----------------------------------------------------------------------------
@file    vane.cpp
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
@brief fuctions for analyzing vane shear test
-----------------------------------------------------------------------------
*/
#include "vane.hpp"
#define _USE_MATH_DEFINES
using std::cos;
using std::sin;
using std::pow;

/*
*    @brief Get max shear
*    @param [in] m torque[Nm]
*    @param [in] h height of vane
*    @param [in] d diameter of vane
*    @return tau_max max shear on the vane
*/
double getTauMax(const double& m, const double& h, const double& d)
{
  double tau_max = m / (M_PI * h * d * d / 2 + M_PI / 6 * pow(d, 3));
  return tau_max;
}
