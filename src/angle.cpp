/**
-----------------------------------------------------------------------------
@file    angle.cpp
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
 ###    @@@@@               @date Dec. 15. 2014
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
@brief angle unit manupulation functions
-----------------------------------------------------------------------------
*/
#include "angle.hpp"
#define _USE_MATH_DEFINES

/*
*    @detail Convert degree to radian
*    @param [in] degree angle in degree
*    @return angle in radian
*/
double degToRad(const double& degree)
{
    return degree * M_PI / 180.0;
}
    
/*
*    @detail Convert radian to degree
*    @param [in] radian angle in radian
*    @return angle in degree
*/
double radToDeg(const double& radian)
{
    return radian * 180.0 / M_PI;
}
