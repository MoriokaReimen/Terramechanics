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
#include "angle.hpp"
#include "wheel_soil.hpp"
#include <boost/python.hpp>
using namespace boost::python;

/* define namespace for python module */
class pybevameter{};
/* end of define namespace */

BOOST_PYTHON_MODULE(pyterramechanics)
{
  /* define angle manupulation functions */
  def("degToRad", degToRad);
  def("radToDeg", radToDeg);

  /* define wheel soil functions */
  class_<Soil>("Soil")
    .def_readwrite("phi", &Soil::phi)
    .def_readwrite("c", &Soil::phi)
    .def_readwrite("K", &Soil::phi)
    .def_readwrite("k1", &Soil::phi)
    .def_readwrite("k2", &Soil::phi)
    .def_readwrite("n", &Soil::phi)
    .def_readwrite("gamma", &Soil::phi);


  class_<Wheel>("Wheel")
    .def_readwrite("r", &Wheel::r)
    .def_readwrite("b", &Wheel::b)
    .def_readwrite("w", &Wheel::w);


  class_<WheelSoil>("WheelSoil", init<Soil, Wheel>())
    .def("getSigma", &WheelSoil::getSigma)
    .def("getTau", &WheelSoil::getTau)
    .def("getTraction", &WheelSoil::getTraction)
    .def("getTorque", &WheelSoil::getTorque)
    .def("getDrawbar", &WheelSoil::getDrawbar);

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

