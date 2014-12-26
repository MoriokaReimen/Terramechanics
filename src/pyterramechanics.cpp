/**
-----------------------------------------------------------------------------
@file    pyterramechanics.cpp
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
 ###    @@@@@               @date Dec. 25. 2014
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
@brief make python module of terramechanics functions
-----------------------------------------------------------------------------
*/
#include "bevameter.hpp"
#include <boost/python.hpp>
using namespace boost::python;

/* define namespace for python module */
class pybevameter{};
/* end of define namespace */

BOOST_PYTHON_MODULE(pyterramechanics)
{
  /* define bevameter functions */
  {
    scope bevameter = class_<pybevameter>("pybevameter");
    class_<bevameter::bevameter>("bevameter")
      .def_readwrite("h", &bevameter::bevameter::h)
      .def_readwrite("d", &bevameter::bevameter::d)
      .def_readwrite("m", &bevameter::bevameter::m);
    def("getShear_h", bevameter::getShear_h);
    def("getShear_v", bevameter::getShear_v);
  }
}

