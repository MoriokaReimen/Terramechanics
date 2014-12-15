#include "shear.hpp"
using std::tan;
using std::exp;
using std::fmin;
/*
*    @detail Maximum shear from Mohr-Coulomb failure criterion
*    @param [in] p normal stress on the sheared surface
*    @param [in] c apparent cohesion
*    @param [in] phi angle of internal shearing resistance
*    @return Shear strength
*/
double getShearStrength(const double& p, const double& c, const double& phi)
{
	return c + p * tan(phi);
}

/*
*    @brief shear from Janosi and Hanamoto function
*    @param [in] p normal stress on the sheared surface
*    @param [in] c apparent cohesion
*    @param [in] phi angle of internal shearing resistance
*    @param [in] j shear displacement
*    @param [in] k shear deformation parameter
*    @return Shear
*/
double getShear(const double& p, const double& c, const double& phi, const double& j, const double& k)
{
	auto tm = getShearStrength(p, c, phi);
	auto ts = 1.0 - exp(-j/k);
	return tm * ts;
}

/*
*    @brief shear from static friction theory
*    @param [in] p normal stress on the sheared surface
*    @param [in] mu friction coefficient
*    @param [in] j shear displacement
*    @param [in] k shear deformation parameter
*    @return Shear
*/
double getStaticShear(const double& p, const double& mu, const double& j, const double& k)
{
	auto ts = 1.0 - exp(j/k);
	auto t_out = p * mu * ts;
	return t_out;
}

/*
*    @brief shear from harnisch theory
*    @param [in] p normal stress on the sheared surface
*    @param [in] mu friction coefficient
*    @param [in] c apparent cohesion
*    @param [in] phi angle of internal shearing resistance
*    @param [in] j shear displacement
*    @param [in] k shear deformation parameter
*    @return Shear
*/
double getHarnischShear(const double& p, const double& mu, const double& c, const double& phi, const double& j, const double& k)
{
	auto ts = 1.0 - exp(-j/k);
	auto t1 = c * p * tan(phi);
	auto t2 = mu * p;
	auto t_out = fmin(t1, t2) * ts;
	return t_out;
}

/*
*    @brief shear from Justin theory
*    @param [in] p normal stress on the sheared surface
*    @param [in] mu friction coefficient
*    @param [in] j shear displacement
*    @param [in] k shear deformation parameter
*    @return Shear
*/
double getJustinShear(const double& p, const double& mu, const double& c, const double& phi, const
        double& j, const double& k, const double& kappa)
{
	auto ts = 1- exp(-j/k);
	auto t1 = c * p * tan(phi);
	auto t2 = mu * p;
	auto t_out = (kappa * t1 + (1 - kappa) * t2) * ts;
	return t_out;
}
