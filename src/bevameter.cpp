/**
-----------------------------------------------------------------------------
@file    bevameter.cpp
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
 ###    @@@@@               @date Dec. 24. 2014
 /-\     @@
|   |      %%                      Authors:
 \-/##    %%%%%             @author Kei Nakata
   #### %%%                 menschenjager.mark.neun@gmail.com
     ###%%       *
      ##%%     *****
       #%%      ***
        %%     *   *
         %%
          %%%%%
           %%%
-----------------------------------------------------------------------------
@brief functions for bevameter experiment
-----------------------------------------------------------------------------
*/
#include "bevameter.hpp"
#include <cmath>
using std::pow;
#define _USE_MATH_DEFINES

/*
*    @detail Calculate horizontal shear force from bevameter experiment
*    @param [in] a bevameter struct
*    @param [in] b bevameter struct
*    @return horizontal shear force
*/
double bevameter::getShear_h(const bevameter& a, const bevameter& b)
{
  double shear = (a.m * pow(b.d, 3) - b.m * pow(a.d, 3))
    / ( M_PI / 2 * pow(a.d, 2) * pow(b.d, 2) * (a.h * b.d - b.h * a.d));

    return shear;
}

/*
*    @detail Calculate vertical shear force from bevameter experiment
*    @param [in] a bevameter struct
*    @param [in] b bevameter struct
*    @return vertical shear force
*/
double bevameter::getShear_v(const bevameter& a, const bevameter& b)
{
  double shear = (a.m * b.h * pow(b.d, 2) - b.m * a.h * pow(a.d, 2))
    / ( M_PI / 6 * pow(a.d, 2) * pow(b.d, 2) * (b.h * a.d - a.h * b.d));

    return shear;
}
